/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_EVENTS_H
#define BMC_OBE_EVENTS_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "editor/onBoard/BMC-OBEDef.h"

class BMCOBEEvents {

public:
  BMCEditor& editor;
  BMCDisplay& display;
  uint8_t& offset;
  bmcStoreEvent tempEvent;
  uint16_t tempValue = 0;
  bool _hasChanges = false;
  
  BMCOBEEvents(BMCEditor& t_editor, BMCDisplay& t_display, uint8_t& t_offset):
  editor(t_editor), display(t_display), offset(t_offset){

  }
  bool hasChanges(bmcStoreEvent& e){
    if(_hasChanges){
      e = tempEvent;
      _hasChanges = false;
      return true;
    }
    return false;
  }
  uint16_t isAvailable(){
    return getData(0);
  }
  uint16_t getFieldsCount(){
    // extra 2 fields are the event type and the event name
    return getData(1)+2;
  }
  uint16_t getFieldValueMin(uint8_t fieldN){
    return getData(5, 1, fieldN);
  }
  uint16_t getFieldValueMax(uint8_t fieldN){
    return getData(5, 2, fieldN);
  }
  void getStatusLabel(char* str){
    getData(str, 4);
  }
  void setNextStatus(){
    if(tempEvent.type < 127){
      tempEvent.type++;
    } else {
      tempEvent.type = 0;
    }
    while(!getData(0)){
      if(tempEvent.type < 127){
        tempEvent.type++;
      } else {
        tempEvent.type = 0;
      }
    }
    resetTempEventData();
  }
  void setPrevStatus(){
    if(tempEvent.type > 0){
      tempEvent.type--;
    } else {
      tempEvent.type = 127;
    }
    while(!getData(0)){
      if(tempEvent.type > 0){
        tempEvent.type--;
      } else {
        tempEvent.type = 127;
      }
    }
    if(!getData(2)){ // scroll
      BMC_WRITE_BITS(tempEvent.settings, 0, 0x07, 0);
    }
    if(!getData(3)){ // ports
      tempEvent.ports = 0;
    }
    resetTempEventData();
  }


  uint16_t setNextFieldValue(uint8_t fieldN){
    uint16_t min = getData(5, fieldN, 1);
    uint16_t max = getData(5, fieldN, 2);
    tempValue = getData(5, fieldN, 3);
    if(tempValue < max){
      tempValue++;
    } else {
      tempValue = min;
    }
    getData(5, fieldN, 4);
    return tempValue;
  }
  uint16_t setPrevFieldValue(uint8_t fieldN){
    uint16_t min = getData(5, fieldN, 1);
    uint16_t max = getData(5, fieldN, 2);
    tempValue = getData(5, fieldN, 3);
    if(tempValue > min){
      tempValue--;
    } else {
      tempValue = max;
    }
    getData(5, fieldN, 4);
    return tempValue;
  }
  void getFieldLabel(char* str, uint8_t row){
    getData(str, 5, row, 0);
  }
  void getFieldValueLabel(char* str, uint8_t row){
    getData(str, 5, row, 5);
  }
  void setTempEventData(bmcStoreEvent e){
    tempEvent = e;
  }
  void resetTempEventData(){
    tempEvent.settings = 0;
    tempEvent.event = 0;
  }
  void exitEditing(bmcStoreEvent e){
    if(tempEvent.type != e.type || tempEvent.event != e.event){
      _hasChanges = true;
    } else if(tempEvent.settings != e.settings || tempEvent.ports != e.ports){
      _hasChanges = true;
    } else if(tempEvent.name != e.name){
      _hasChanges = true;
    }
  }
  void getEventStatusName(char * str, uint8_t status){
    tempEvent.type = status;
    getData(str, 4);
  }

  
private:

  
  uint16_t eventNameField(char* str, uint8_t request, uint8_t field=0){
    uint16_t value = tempEvent.name;
    switch(request){
      case 0: strcpy(str, "Name"); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return BMC_MAX_NAMES_LIBRARY; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        if(tempValue <= BMC_MAX_NAMES_LIBRARY){
          tempEvent.name = tempValue;
        }
        return 1;
      case 5: /* formatted value */
        {
          char str2[40];
          strcpy(str2, "...");
          if(tempValue <= BMC_MAX_NAMES_LIBRARY){
            editor.getDeviceNameFromIndex(tempValue, str2);
          }
          sprintf(str, "#%u ", tempValue);
          strcat(str, str2);
        }
        return 1;
    }
    return 0;
  }
  
  uint16_t eventGetPortsField(char* str, uint8_t request, uint8_t field=0){
    uint8_t value = tempEvent.ports;
    switch(request){
      case 0: strcpy(str, "Port"); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 143; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        tempEvent.ports = tempValue;
        return 1;
      case 5: /* formatted value */
        BMCOBEData::getPortName(str, value);
        return 1;
      case 6: /* scroll value down */
        tempEvent.ports = BMCOBEData::setPortBit(false, value);
        return 1;
      case 7: /* scroll value up */
        tempEvent.ports = BMCOBEData::setPortBit(true, value);
        return 1;
    }
    return 0;
  }
  uint16_t eventGetScrollEnableField(char* str, uint8_t request){
    return eventGetFieldYesNo(str, "Scroll Enable", request, 0);
  }
  uint16_t eventGetScrollDirectionField(char* str, uint8_t request){
    return eventGetFieldYesNo(str, "Scroll Up", request, 1);
  }
  uint16_t eventGetScrollLimitField(char* str, uint8_t request){
    return eventGetFieldYesNo(str, "Scroll Endlessly", request, 2);
  }
  uint16_t eventGetDawTrackField(char* str, uint8_t request){
    uint8_t value = BMC_GET_BYTE(1, tempEvent.event);
    switch(request){
      case 0: strcpy(str, "Track #"); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 8; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
        return 1;
      case 5: /* formatted value */
        if(value == 8){
          strcpy(str, "Selected Track");
        } else {
          sprintf(str, "Track # %u", value + offset);
        }
        return 1;
    }
    return 0;
  }
  uint16_t eventGetMidiChannelField(char* str, uint8_t request, uint8_t bytePos=0){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Channel", request, bytePos, 0, 15, true);
  }
  uint16_t eventGetMidiProgramField(char* str, uint8_t request, uint8_t bytePos=1){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Program", request, bytePos, 0, 127, false);
  }
  uint16_t eventGetMidiControlField(char* str, uint8_t request, uint8_t bytePos=1){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Control", request, bytePos, 0, 127, false);
  }
  uint16_t eventGetMidiNoteField(char* str, uint8_t request, uint8_t bytePos=1){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Note", request, bytePos, 0, 127, false);
  }
  uint16_t eventGetMidiControlValueField(char* str, uint8_t request, uint8_t bytePos=2){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Value", request, bytePos, 0, 127, false);
  }
  uint16_t eventGetMidiNoteVelocityField(char* str, uint8_t request, uint8_t bytePos=2){
    // str, str2, request, bytePos, min, max, useOffset
    return eventGetField8BitValueRange(str, "Velocity", request, bytePos, 0, 127, false);
  }
  uint16_t eventGetField8BitValueRange(char* str, const char* str2, uint8_t request, uint8_t bytePos, uint8_t min, uint8_t max, bool useOffset){
    uint8_t value = BMC_GET_BYTE(bytePos, tempEvent.event);
    switch(request){
      case 0: strcpy(str, str2); return 1; /* label */
      case 1: return min; /* min */
      case 2: return max; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, bytePos*8);
        return 1;
      case 5: /* formatted value */
        sprintf(str, "%u", value + (useOffset ? offset : 0));
        return 1;
    }
    return 0;
  }
  uint16_t eventGetField16BitValueRange(char* str, const char* str2, uint8_t request, uint8_t bytePos, uint16_t min, uint16_t max, bool useOffset){
    uint16_t value = BMC_GET_BYTE(bytePos, tempEvent.event);
    switch(request){
      case 0: strcpy(str, str2); return 1; /* label */
      case 1: return min; /* min */
      case 2: return max; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFFFF, bytePos*16);
        return 1;
      case 5: /* formatted value */
        sprintf(str, "%u", value + (useOffset ? offset : 0));
        return 1;
    }
    return 0;
  }
  uint16_t eventGetFieldYesNo(char* str, const char* str2, uint8_t request, uint8_t bitPos){
    uint8_t value = bitRead(tempEvent.settings, bitPos);
    switch(request){
      case 0: strcpy(str, str2); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 1; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        bitWrite(tempEvent.settings, bitPos, tempValue);
        return 1;
      case 5: /* formatted value */
        strcpy(str, (value == 0) ? "No" : "Yes");
        return 1;
    }
    return 0;
  }
  


  



  uint16_t getData(uint8_t request, uint8_t field=0, uint8_t fieldRequest=0){
    char str[33] = "";
    return getData(str, request, field, fieldRequest);
  }
  uint16_t getData(char* str, uint8_t request, uint8_t field=0, uint8_t fieldRequest=0){
    switch(tempEvent.type){
      case BMC_NONE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "*Inactive*"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 6; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Program Change"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiProgramChange(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 7; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Control Change"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiControlChange(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_NOTE_ON:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Note On"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiNoteOn(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Note Off"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiNoteOff(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_PITCH_BEND:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 3; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Pitch Bend"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiPitchBend(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_CONTROL_TOGGLE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Control Change Toggle"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiControlToggle(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_PROGRAM_BANKING_SCROLL:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 6; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Program Banking Scroll"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeProgramBankingScroll(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Program Banking Trigger"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeProgramBankingTrigger(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_REAL_TIME_BLOCK:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Block Real Time Messages"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiRealTimeBlock(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_BANK_LSB_PROGRAM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "CC#32 + Program Change"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBankLsbProgram(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_BANK_MSB_PROGRAM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "CC#0 + Program Change"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBankMsbProgram(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_BANK_MSB_LSB:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "CC#0 + CC#32"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBankMsbLsb(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_BANK_MSB_LSB_PROGRAM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "CC#0 + CC#32 + Program"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBankMsbLsbProgram(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_ACTIVE_SENSE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "MIDI Active Sense"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemActiveSense(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_CLOCK:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "MIDI Clock"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemClock(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "MIDI Master Clock Tap"); return 1;}
        break;

      case BMC_EVENT_TYPE_SYSTEM_STATUS:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "System Status"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemStatus(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "MIDI I/O Activity"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemMidiActivity(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_SAVE_EEPROM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Save EEPROM"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_MENU:
        if(request==0){ /* available */ return BMC_MAX_ILI9341_BLOCKS>0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Menu"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemMenu(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_BUTTONS)
      case BMC_EVENT_TYPE_SYSTEM_TYPER:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 3; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Typer"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemTyper(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_MIDI_BLE_ENABLED)
      case BMC_EVENT_TYPE_SYSTEM_BLE_DISCONNECT:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Disconnect BLE Device"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_SYSTEM_STOPWATCH:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Stopwatch"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemStopwatch(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SYSTEM_LFO:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "LFO"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSystemLfo(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SKETCH_BYTE:
        if(request==0){ /* available */ return BMC_MAX_SKETCH_BYTES > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Sketch Byte Set Value"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSketchByte(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_PAGE:
        if(request==0){ /* available */ return BMC_MAX_PAGES > 1; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Page #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePage(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PAGE_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_PAGES > 1; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Page # (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PAGE_NAME:
        if(request==0){ /* available */ return BMC_MAX_PAGES > 1; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Page Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePageName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PAGE_SELECTED_NAME:
        if(request==0){ /* available */ return BMC_MAX_PAGES > 1; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Page Name (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_PRESET:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Preset #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePreset(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PRESET_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Preset # (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PRESET_NAME:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Preset Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePresetName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PRESET_SELECTED_NAME:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Preset Name (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_BANK:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Bank #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBank(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_BANK_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Bank (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_SETLIST:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "SetList #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSetlist(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SETLIST_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Number (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SETLIST_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "SetList Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSetlistName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SETLIST_SELECTED_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Name (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSetlistSelectedName(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_SONG:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Song #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSong(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SONG_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song # (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SONG_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSongName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_SONG_SELECTED_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Name (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_PART:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Song Part #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePart(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PART_SELECTED:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Part # (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PART_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Part Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePartName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_PART_SELECTED_NAME:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Part Name (SEL)"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

      case BMC_EVENT_TYPE_NL_RELAY:
        if(request==0){ /* available */ return BMC_MAX_NL_RELAYS > 0; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Non-Latching Relay Control"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNlRelay(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_L_RELAY:
        if(request==0){ /* available */ return BMC_MAX_NL_RELAYS > 0; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Latching Relay Control"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeLRelay(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_AUX_JACK:
        if(request==0){ /* available */ return BMC_MAX_AUX_JACKS > 0; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Aux Jack State"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeAuxJack(str, fieldRequest, field);}
        break;

#if defined(BMC_USE_DAW_LC) && (defined(BMC_HAS_BUTTONS) || defined(BMC_HAS_MAGIC_ENCODER) || BMC_MAX_TRIGGERS > 0)
      case BMC_EVENT_TYPE_DAW_BUTTON:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Button"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawButton(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_DAW_LC) && (defined(BMC_HAS_MAGIC_ENCODER) || defined(BMC_HAS_LEDS))
      case BMC_EVENT_TYPE_DAW_LED:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Led"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawLed(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_DAW_LC) && (defined(BMC_HAS_MAGIC_ENCODER) || defined(BMC_HAS_ENCODERS))
      case BMC_EVENT_TYPE_DAW_ENCODER:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Encoder"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawEncoder(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_DAW_LC) && defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_DAW_DISPLAY:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Display"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawDisplay(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_DAW_LC) && (defined(BMC_HAS_MAGIC_ENCODER) || defined(BMC_HAS_LEDS))
      case BMC_EVENT_TYPE_DAW_MAGIC_ENCODER:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Magic Encoder Leds"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawMagicEncoder(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_BUTTONS)
      case BMC_EVENT_TYPE_CUSTOM_SYSEX:
        if(request==0){ /* available */ return BMC_MAX_CUSTOM_SYSEX > 0 && (BMC_MAX_AUX_JACKS>0); }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Custom SysEx"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeCustomSysex(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_BUTTONS) && defined(BMC_HAS_ENCODERS)
      case BMC_EVENT_TYPE_PIXEL_PROGRAM:
        if(request==0){ /* available */ return BMC_MAX_PIXEL_PROGRAMS>0 && (BMC_MAX_PIXELS > 0 || BMC_MAX_GLOBAL_PIXELS > 0) && (BMC_MAX_AUX_JACKS>0); }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Pixel Program"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePixelProgram(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_HAS_BUTTONS) && defined(BMC_HAS_ENCODERS)
      case BMC_EVENT_TYPE_PIXEL_PROGRAM_BLACKOUT:
        if(request==0){ /* available */ return BMC_MAX_PIXEL_PROGRAMS>0 && (BMC_MAX_AUX_JACKS>0); }
        else if(request==1){ /* fields */ return 0; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Pixel Program Toggle Blackout"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;
#endif

    }
    return 0;
  }
  
  uint16_t eventBmcEventTypeNameOnly(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
    }
    return 0;
  }
  
  uint16_t eventBmcEventTypeMidiProgramChange(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetMidiProgramField(str, fieldRequest, 1);
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollLimitField(str, fieldRequest);
      case 6:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiControlChange(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetMidiControlField(str, fieldRequest, 1);
      case 3:
        return eventGetMidiControlValueField(str, fieldRequest, 2);
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollLimitField(str, fieldRequest);
      case 7:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiNoteOn(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetMidiNoteField(str, fieldRequest, 1);
      case 3:
        return eventGetMidiNoteVelocityField(str, fieldRequest, 2);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiNoteOff(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetMidiNoteField(str, fieldRequest, 1);
      case 3:
        return eventGetMidiNoteVelocityField(str, fieldRequest, 2);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiPitchBend(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 3; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case 0: strcpy(str, "Pitch Both Ways"); return 1;
              case 1: strcpy(str, "Pitch Up"); return 1;
              case 2: strcpy(str, "Pitch Down"); return 1;
            }
            return 1;
        }
        break;
      case 3:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiControlToggle(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetMidiControlField(str, fieldRequest, 1);
      case 3:
        return eventGetField8BitValueRange(str, "Value A", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetField8BitValueRange(str, "Value B", fieldRequest, 3, 0, 127, false);
      case 5:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeProgramBankingScroll(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Amount", fieldRequest, 0, 0, 127, false);
      case 2:
        return eventGetField8BitValueRange(str, "Min Program", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetField8BitValueRange(str, "Max Program", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeProgramBankingTrigger(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeMidiRealTimeBlock(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Target"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case 0: strcpy(str, "Input"); return 1;
              case 1: strcpy(str, "Output"); return 1;
            }
            return 1;
        }
        break;
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case 0: strcpy(str, "Block"); return 1;
              case 1: strcpy(str, "Allow"); return 1;
              case 2: strcpy(str, "Toggle"); return 1;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBankLsbProgram(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetField8BitValueRange(str, "CC#32 (LSB) Value", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetField8BitValueRange(str, "Program", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBankMsbProgram(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetField8BitValueRange(str, "CC#0 (MSB) Value", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetField8BitValueRange(str, "Program", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBankMsbLsb(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetField8BitValueRange(str, "CC#0 (MSB) Value", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetField8BitValueRange(str, "CC#32 (LSB) Value", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBankMsbLsbProgram(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetMidiChannelField(str, fieldRequest, 0);
      case 2:
        return eventGetField8BitValueRange(str, "CC#0 (MSB) Value", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetField8BitValueRange(str, "CC#32 (LSB) Value", fieldRequest, 2, 0, 127, false);
      case 4:
        return eventGetField8BitValueRange(str, "Program", fieldRequest, 3, 0, 127, false);
      case 5:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemActiveSense(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_ACTIVE_SENSE_STOP: strcpy(str, "Stop"); break;
              case BMC_ACTIVE_SENSE_START: strcpy(str, "Start"); break;
              case BMC_ACTIVE_SENSE_TOGGLE: strcpy(str, "Toggle"); break;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemClock(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "BPM"); return 1; /* label */
          case 1: return 30; /* min */
          case 2: return 300; /* max */
          case 3: /* get stored value */
            {
              uint16_t value = BMC_GET_BYTE_2(0, tempEvent.event);
              return constrain(value, 30, 300);
            }
          case 4: /* set stored value */
            tempEvent.event = tempValue;
            return 1;
          case 5: /* formatted value */
            {
              uint16_t value = BMC_GET_BYTE_2(0, tempEvent.event);
              value = constrain(value, 30, 300);
              sprintf(str, "%u", value);
              return 1;
            }
        }
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemStatus(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 11; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_LED_STATUS_BMC: strcpy(str, "Heartbeat"); break;
              case BMC_LED_STATUS_ALWAYS_ON: strcpy(str, "Always On"); break;
              case BMC_LED_STATUS_EDITOR_CONNECTED: strcpy(str, "Editor Connected"); break;
              case BMC_LED_STATUS_HOST_CONNECTED: strcpy(str, "Host Connected"); break;
              case BMC_LED_STATUS_BLE_CONNECTED: strcpy(str, "BLE Connected"); break;
              case BMC_LED_STATUS_ACTIVE_SENSE_SENDING: strcpy(str, "Active Sense Sending"); break;
              case BMC_LED_STATUS_ACTIVE_SENSE_READING: strcpy(str, "Active Sense Reading"); break;
              case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT: strcpy(str, "MIDI Real Time Block Input"); break;
              case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT: strcpy(str, "MIDI Real Time Block Output"); break;
              case BMC_LED_STATUS_STOPWATCH_ACTIVE: strcpy(str, "Stopwatch Active"); break;
              case BMC_LED_STATUS_STOPWATCH_STATE: strcpy(str, "Stopwatch Active or Complete"); break;
              case BMC_LED_STATUS_STOPWATCH_COMPLETE: strcpy(str, "Stopwatch Complete"); break;
              default:  strcpy(str, "undefined"); break;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemMidiActivity(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Type"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case 0: strcpy(str, "MIDI IN"); break;
              case 1: strcpy(str, "MIDI OUT"); break;
              default:  strcpy(str, "MIDI IN OR OUT"); break;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemMenu(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 1; /* min */
          case 2: return 6; /* max */
          case 3: /* get stored value */
          {
            uint8_t value = BMC_GET_BYTE(0, tempEvent.event);
            return constrain(value, 1, 6);
          }
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
          {
            uint8_t value = BMC_GET_BYTE(0, tempEvent.event);
            value = constrain(value, 1, 6);
            switch(value){
              case BMC_MENU_TOGGLE: strcpy(str,"Enter/Exit"); return 1;
              case BMC_MENU_SELECT: strcpy(str,"Select"); return 1;
              case BMC_MENU_BACK: strcpy(str,"Back"); return 1;
              case BMC_MENU_PREV: strcpy(str,"Prev"); return 1;
              case BMC_MENU_NEXT: strcpy(str,"Next"); return 1;
              case BMC_MENU_SHIFT: strcpy(str,"Shift"); return 1;
            }
            return 1;
          }
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemTyper(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 20; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            {
              uint8_t cmd = BMC_GET_BYTE(0, tempEvent.event);
              if(cmd>=10){
                if(cmd==10){
                  strcpy(str, "Clear"); return 1;
                } else if(cmd==11){
                  strcpy(str, "Set Custom"); return 1;
                } else if(cmd==12){
                  strcpy(str, "Set Page"); return 1;
                } else if(cmd==13){
                  strcpy(str, "Set Preset"); return 1;
                } else if(cmd==14){
                  strcpy(str, "Set FAS Preset (if Compiled)"); return 1;
                } else if(cmd==15){
                  strcpy(str, "Set FAS Scene (if Compiled)"); return 1;
                } else if(cmd==16){
                  strcpy(str, "Set FAS Scene Revert (if Compiled)"); return 1;
                } else if(cmd==17){
                  strcpy(str, "Set MIDI Channel"); return 1;
                } else if(cmd==18){
                  strcpy(str, "Set MIDI Program Change"); return 1;
                } else if(cmd==19){
                  strcpy(str, "Set MIDI Control Change #0"); return 1;
                } else if(cmd==20){
                  strcpy(str, "Toggle MIDI Control Change"); return 1;
                } else {
                  strcpy(str, "Invalid"); return 1;
                }
              } else {
                sprintf(str, "Type %u", cmd);
              }
            }
            return 1;
        }
        break;
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Auto Trigger"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 10; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            {
              uint8_t cmd = BMC_GET_BYTE(1, tempEvent.event);
              if(cmd==0){
                strcpy(str, "None");
              } else if(cmd==1){
                strcpy(str, "Set Custom");
              } else if(cmd==2){
                strcpy(str, "Set Page");
              } else if(cmd==3){
                strcpy(str, "Set Preset");
              } else if(cmd==4){
                strcpy(str, "Set FAS Preset (if Compiled)");
              } else if(cmd==5){
                strcpy(str, "Set FAS Scene (if Compiled)");
              } else if(cmd==6){
                strcpy(str, "Set FAS Scene Revert (if Compiled)");
              } else if(cmd==7){
                strcpy(str, "Set MIDI Channel");
              } else if(cmd==8){
                strcpy(str, "Set MIDI Program Change");
              } else if(cmd==9){
                strcpy(str, "Set MIDI Control Change #0");
              } else if(cmd==10){
                strcpy(str, "Toggle MIDI Control Change");
              } else {
                strcpy(str, "Invalid");
              }
            }
            return 1;
        }
        break;
      case 3:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemStopwatch(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 5; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_STOPWATCH_CMD_STOP: strcpy(str, "Stop"); return 1;
              case BMC_STOPWATCH_CMD_START: strcpy(str, "Start"); return 1;
              case BMC_STOPWATCH_CMD_RESET: strcpy(str, "Reset"); return 1;
              case BMC_STOPWATCH_CMD_TOGGLE: strcpy(str, "Start/Stop"); return 1;
              case BMC_STOPWATCH_CMD_TOGGLE_RESET: strcpy(str, "Start/Reset"); return 1;
            }
            return 1;
        }
        break;
      case 2:
        return eventGetField8BitValueRange(str, "Hour", fieldRequest, 1, 0, 24, false);
      case 3:
        return eventGetField8BitValueRange(str, "Minutes", fieldRequest, 2, 0, 24, false);
      case 4:
        return eventGetField8BitValueRange(str, "Seconds", fieldRequest, 3, 0, 24, false);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSystemLfo(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Target LFO", fieldRequest, 0, 0, BMC_MAX_LFO-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case 0: strcpy(str, "Toggle"); return 1;
              case 1: strcpy(str, "Start"); return 1;
              case 2: strcpy(str, "Stop"); return 1;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  void getSketchByteFormat(char* str, uint8_t n, uint8_t value){
    BMCSketchByteData t = BMCBuildData::getSketchByteData(n);
    // buffer.initialValue = 0;
    // buffer.min = 0;
    // buffer.max = 255;
    // buffer.step = 1;
    // buffer.formatType = BMC_NONE;
    // buffer.formatValue = BMC_NONE;
    // buffer.formatAppend = BMC_NONE;
    uint8_t fType = t.formatType;
    uint8_t fValue = t.formatValue;
    uint8_t fAppend = t.formatAppend;
    char txt[16] = "";

    if(fType>0){
      switch(fAppend){
        case 0: strcpy(txt, ""); break;
        case 1: strcpy(txt, "sec"); break;
        case 2: strcpy(txt, "ms"); break;
        case 3: strcpy(txt, "us"); break;
        case 4: strcpy(txt, "mm"); break;
        case 5: strcpy(txt, "cm"); break;
        case 6: strcpy(txt, "m"); break;
        case 7: strcpy(txt, "%"); break;
        case 8: strcpy(txt, "degrees"); break;
        case 9: strcpy(txt, "bpm"); break;
        case 10: strcpy(txt, "hours"); break;
        case 11: strcpy(txt, "minutes"); break;
        case 12: strcpy(txt, "seconds"); break;
        case 13: strcpy(txt, "days"); break;
        case 14: strcpy(txt, "weeks"); break;
        case 15: strcpy(txt, "hours"); break;
      }
    }
    switch(fType){
      case 1: sprintf(str, "%u %s", (value+fValue), txt); break;
      case 2: sprintf(str, "%u %s", (value-fValue), txt); break;
      case 3: sprintf(str, "%u %s", (value*fValue), txt); break;
      case 4: sprintf(str, "%u %s", (value/fValue), txt); break;
      case 5: strcpy(str, (value == 0) ? "Off" : "On"); break;
    }
  }
  uint16_t eventBmcEventTypeSketchByte(char* str, uint8_t fieldRequest, uint8_t field){
    uint8_t index = BMC_GET_BYTE(0, tempEvent.event);
    BMCSketchByteData sb = BMCBuildData::getSketchByteData(index);
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Sketch Byte", fieldRequest, 0, 0, BMC_MAX_SKETCH_BYTES-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return sb.min; /* min */
          case 2: return sb.max; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            getSketchByteFormat(str, index, tempValue);
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePage(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField16BitValueRange(str, "Page", fieldRequest, 0, 0, BMC_MAX_PAGES-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePageName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField16BitValueRange(str, "Page", fieldRequest, 0, 0, BMC_MAX_PAGES-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePreset(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Preset", fieldRequest, 0, 0, BMC_MAX_PRESETS_PER_BANK-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePresetName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Preset", fieldRequest, 0, 0, BMC_MAX_PRESETS_PER_BANK-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBank(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Bank", fieldRequest, 0, 0, BMC_MAX_PRESET_BANKS-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSetlist(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "SetList", fieldRequest, 0, 0, BMC_MAX_SETLISTS-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
      case 5:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSetlistName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "SetList", fieldRequest, 0, 0, BMC_MAX_SETLISTS-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSetlistSelectedName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "SetList", fieldRequest, 0, 0, BMC_MAX_SETLISTS-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSong(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Song", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONGS-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
      case 5:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeSongName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Song", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONGS-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePart(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Part", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONG_PARTS-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
      case 5:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePartName(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Part", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONG_PARTS-1, true);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeNlRelay(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Relay", fieldRequest, 0, 0, BMC_MAX_NL_RELAYS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case BMC_RELAY_OPEN: strcpy(str, "Open"); return 1;
              case BMC_RELAY_CLOSED: strcpy(str, "Close"); return 1;
              case BMC_RELAY_TOGGLE: strcpy(str, "Toggle"); return 1;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeLRelay(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Relay", fieldRequest, 0, 0, BMC_MAX_L_RELAYS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case BMC_RELAY_SET: strcpy(str, "Set"); return 1;
              case BMC_RELAY_RESET: strcpy(str, "Reset"); return 1;
              case BMC_RELAY_TOGGLE: strcpy(str, "Toggle"); return 1;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeAuxJack(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Aux Jack", fieldRequest, 0, 0, BMC_MAX_AUX_JACKS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 2; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case 0: strcpy(str, "Connected"); return 1;
              case 1: strcpy(str, "In Pot Mode"); return 1;
              case 2: strcpy(str, "In Dual Button Mode"); return 1;
            }
            return 1;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawButton(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 68; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_DAW_BTN_CMD_REC: strcpy(str, "Ch. REC"); return 1;
              case BMC_DAW_BTN_CMD_SOLO: strcpy(str, "Ch. SOLO"); return 1;
              case BMC_DAW_BTN_CMD_MUTE: strcpy(str, "Ch. MUTE"); return 1;
              case BMC_DAW_BTN_CMD_SELECT: strcpy(str, "Ch. SELECT"); return 1;
              case BMC_DAW_BTN_CMD_VPOT: strcpy(str, "Ch. VPot"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_TRACK: strcpy(str, "VPot Assgn TRACK"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_SEND: strcpy(str, "VPot Assgn SEND"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_PAN: strcpy(str, "VPot Assgn PAN"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_PLUGIN: strcpy(str, "VPot Assgn PLUGIN"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_EQ: strcpy(str, "VPot Assgn EQ"); return 1;
              case BMC_DAW_BTN_CMD_ASSIGN_INSTR: strcpy(str, "VPot Assgn INSTR"); return 1;
              case BMC_DAW_BTN_CMD_BANK_LEFT: strcpy(str, "Bank NEXT"); return 1;
              case BMC_DAW_BTN_CMD_BANK_RIGHT: strcpy(str, "Bank PREV"); return 1;
              case BMC_DAW_BTN_CMD_CHANNEL_LEFT: strcpy(str, "Ch. NEXT"); return 1;
              case BMC_DAW_BTN_CMD_CHANNEL_RIGHT: strcpy(str, "Ch. PREV"); return 1;
              case BMC_DAW_BTN_CMD_FLIP: strcpy(str, "FLIP"); return 1;
              case BMC_DAW_BTN_CMD_GLOBAL: strcpy(str, "GLOBAL"); return 1;
              case BMC_DAW_BTN_CMD_NAMEVAL: strcpy(str, "NAMEVAL"); return 1;
              case BMC_DAW_BTN_CMD_SMPTEBEATS: strcpy(str, "SMPTEBEATS"); return 1;
              case BMC_DAW_BTN_CMD_F1: strcpy(str, "F1"); return 1;
              case BMC_DAW_BTN_CMD_F2: strcpy(str, "F2"); return 1;
              case BMC_DAW_BTN_CMD_F3: strcpy(str, "F3"); return 1;
              case BMC_DAW_BTN_CMD_F4: strcpy(str, "F4"); return 1;
              case BMC_DAW_BTN_CMD_F5: strcpy(str, "F5"); return 1;
              case BMC_DAW_BTN_CMD_F6: strcpy(str, "F6"); return 1;
              case BMC_DAW_BTN_CMD_F7: strcpy(str, "F7"); return 1;
              case BMC_DAW_BTN_CMD_F8: strcpy(str, "F8"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_MIDI: strcpy(str, "View MIDI"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_INPUTS: strcpy(str, "View INPUTS"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_AUDIO: strcpy(str, "View AUDIO"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_INSTR: strcpy(str, "View INSTR"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_AUX: strcpy(str, "View AUX"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_BUS: strcpy(str, "View BUS"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_OUT: strcpy(str, "View OUT"); return 1;
              case BMC_DAW_BTN_CMD_VIEW_USER: strcpy(str, "View USER"); return 1;
              case BMC_DAW_BTN_CMD_MOD_SHIFT: strcpy(str, "Mod SHIFT"); return 1;
              case BMC_DAW_BTN_CMD_MOD_OPTION: strcpy(str, "Mod OPTION"); return 1;
              case BMC_DAW_BTN_CMD_MOD_CONTROL: strcpy(str, "Mod CONTROL"); return 1;
              case BMC_DAW_BTN_CMD_MOD_CMD: strcpy(str, "Mod CMD"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_READ: strcpy(str, "READ"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_WRITE: strcpy(str, "WRITE"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_TRIM: strcpy(str, "TRIM"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_TOUCH: strcpy(str, "TOUCH"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_LATCH: strcpy(str, "LATCH"); return 1;
              case BMC_DAW_BTN_CMD_AUTOMATION_GROUP: strcpy(str, "GROUP"); return 1;
              case BMC_DAW_BTN_CMD_UTILITY_SAVE: strcpy(str, "SAVE"); return 1;
              case BMC_DAW_BTN_CMD_UTILITY_UNDO: strcpy(str, "UNDO"); return 1;
              case BMC_DAW_BTN_CMD_UTILITY_CANCEL: strcpy(str, "CANCEL"); return 1;
              case BMC_DAW_BTN_CMD_UTILITY_ENTER: strcpy(str, "ENTER"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_MARKER: strcpy(str, "MARKER"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_NUDGE: strcpy(str, "NUDGE"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_CYCLE: strcpy(str, "CYCLE"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_DROP: strcpy(str, "DROP"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_REPLACE: strcpy(str, "REPLACE"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_CLICK: strcpy(str, "CLICK"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_SOLO: strcpy(str, "SOLO"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_REWIND: strcpy(str, "REWIND"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_FORWARD: strcpy(str, "FORWARD"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_STOP: strcpy(str, "STOP"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_PLAY: strcpy(str, "PLAY"); return 1;
              case BMC_DAW_BTN_CMD_TRANSPORT_REC: strcpy(str, "REC"); return 1;
              case BMC_DAW_BTN_CMD_CURSOR_UP: strcpy(str, "Cursor UP"); return 1;
              case BMC_DAW_BTN_CMD_CURSOR_DOWN: strcpy(str, "Cursor DOWN"); return 1;
              case BMC_DAW_BTN_CMD_CURSOR_LEFT: strcpy(str, "Cursor LEFT"); return 1;
              case BMC_DAW_BTN_CMD_CURSOR_RIGHT: strcpy(str, "Cursor RIGHT"); return 1;
              case BMC_DAW_BTN_CMD_CURSOR_ZOOM: strcpy(str, "Cursor ZOOM"); return 1;
              case BMC_DAW_BTN_CMD_SCRUB: strcpy(str, "SCRUB"); return 1;
              case BMC_DAW_BTN_CMD_FADER_TOUCH: strcpy(str, "FADER TOUCH"); return 1;
              case BMC_DAW_BTN_CMD_FADER_TOUCH_MASTER: strcpy(str, "FADER TOUCH MASTER"); return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetDawTrackField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawLed(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 62; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_DAW_LED_CMD_REC: strcpy(str, "Ch. REC"); return 1;
              case BMC_DAW_LED_CMD_SOLO: strcpy(str, "Ch. SOLO"); return 1;
              case BMC_DAW_LED_CMD_MUTE: strcpy(str, "Ch. MUTE"); return 1;
              case BMC_DAW_LED_CMD_SELECT: strcpy(str, "Ch. SELECT"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_TRACK: strcpy(str, "V-Pot Assgn TRACK"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_PAN: strcpy(str, "V-Pot Assgn PAN"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_EQ: strcpy(str, "V-Pot Assgn EQ"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_SEND: strcpy(str, "V-Pot Assgn SEND"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_PLUGIN: strcpy(str, "V-Pot Assgn PLUGIN"); return 1;
              case BMC_DAW_LED_CMD_ASSIGN_INSTR: strcpy(str, "V-Pot Assgn INSTR"); return 1;
              case BMC_DAW_LED_CMD_GLOBAL: strcpy(str, "GLOBAL"); return 1;
              case BMC_DAW_LED_CMD_FLIP: strcpy(str, "FLIP"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_PLAY: strcpy(str, "PLAY"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_STOP: strcpy(str, "STOP"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_REC: strcpy(str, "REC"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_FORWARD: strcpy(str, "FORWARD"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_REWIND: strcpy(str, "REWIND"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_MARKER: strcpy(str, "MARKER"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_NUDGE: strcpy(str, "NUDGE"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_CYCLE: strcpy(str, "CYCLE"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_DROP: strcpy(str, "DROP"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_REPLACE: strcpy(str, "REPLACE"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_CLICK: strcpy(str, "CLICK"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_SOLO: strcpy(str, "SOLO"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_ZOOM: strcpy(str, "ZOOM"); return 1;
              case BMC_DAW_LED_CMD_TRANSPORT_SCRUB: strcpy(str, "SCRUB"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_READ: strcpy(str, "READ"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_WRITE: strcpy(str, "WRITE"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_TRIM: strcpy(str, "TRIM"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_TOUCH: strcpy(str, "TOUCH"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_LATCH: strcpy(str, "LATCH"); return 1;
              case BMC_DAW_LED_CMD_AUTOMATION_GROUP: strcpy(str, "GROUP"); return 1;
              case BMC_DAW_LED_CMD_UTILITY_SAVE: strcpy(str, "SAVE"); return 1;
              case BMC_DAW_LED_CMD_UTILITY_UNDO: strcpy(str, "UNDO"); return 1;
              case BMC_DAW_LED_CMD_METER_PEAK: strcpy(str, "Ch. Meter Overload"); return 1;
              case BMC_DAW_LED_CMD_METER_1: strcpy(str, "Ch. Meter Level 1"); return 1;
              case BMC_DAW_LED_CMD_METER_2: strcpy(str, "Ch. Meter Level 2"); return 1;
              case BMC_DAW_LED_CMD_METER_3: strcpy(str, "Ch. Meter Level 3"); return 1;
              case BMC_DAW_LED_CMD_METER_4: strcpy(str, "Ch. Meter Level 4"); return 1;
              case BMC_DAW_LED_CMD_METER_5: strcpy(str, "Ch. Meter Level 5"); return 1;
              case BMC_DAW_LED_CMD_METER_6: strcpy(str, "Ch. Meter Level 6"); return 1;
              case BMC_DAW_LED_CMD_METER_7: strcpy(str, "Ch. Meter Level 7"); return 1;
              case BMC_DAW_LED_CMD_METER_8: strcpy(str, "Ch. Meter Level 8"); return 1;
              case BMC_DAW_LED_CMD_METER_9: strcpy(str, "Ch. Meter Level 9"); return 1;
              case BMC_DAW_LED_CMD_METER_10: strcpy(str, "Ch. Meter Level 10"); return 1;
              case BMC_DAW_LED_CMD_METER_11: strcpy(str, "Ch. Meter Level 11"); return 1;
              case BMC_DAW_LED_CMD_METER_12: strcpy(str, "Ch. Meter Level 12"); return 1;
              case BMC_DAW_LED_CMD_VPOT_1: strcpy(str, "Ch. VPot Led 1"); return 1;
              case BMC_DAW_LED_CMD_VPOT_2: strcpy(str, "Ch. VPot Led 2"); return 1;
              case BMC_DAW_LED_CMD_VPOT_3: strcpy(str, "Ch. VPot Led 3"); return 1;
              case BMC_DAW_LED_CMD_VPOT_4: strcpy(str, "Ch. VPot Led 4"); return 1;
              case BMC_DAW_LED_CMD_VPOT_5: strcpy(str, "Ch. VPot Led 5"); return 1;
              case BMC_DAW_LED_CMD_VPOT_6: strcpy(str, "Ch. VPot Led 6"); return 1;
              case BMC_DAW_LED_CMD_VPOT_7: strcpy(str, "Ch. VPot Led 7"); return 1;
              case BMC_DAW_LED_CMD_VPOT_8: strcpy(str, "Ch. VPot Led 8"); return 1;
              case BMC_DAW_LED_CMD_VPOT_9: strcpy(str, "Ch. VPot Led 9"); return 1;
              case BMC_DAW_LED_CMD_VPOT_10: strcpy(str, "Ch. VPot Led 10"); return 1;
              case BMC_DAW_LED_CMD_VPOT_11: strcpy(str, "Ch. VPot Led 11"); return 1;
              case BMC_DAW_LED_CMD_VPOT_CENTER: strcpy(str, "Ch. VPot Led Center"); return 1;
              case BMC_DAW_LED_CMD_SMPTE: strcpy(str, "SMPTE"); return 1;
              case BMC_DAW_LED_CMD_BEATS: strcpy(str, "BEATS"); return 1;
              case BMC_DAW_LED_CMD_RUDE_SOLO: strcpy(str, "RUDE SOLO"); return 1;
              case BMC_DAW_LED_CMD_RELAY: strcpy(str, "RELAY"); return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetDawTrackField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawEncoder(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_DAW_ENC_CMD_VPOT: strcpy(str, "Ch. V-Pot"); return 1;
              case BMC_DAW_ENC_CMD_FADER: strcpy(str, "Ch. Fader"); return 1;
              case BMC_DAW_ENC_CMD_FADER_MASTER: strcpy(str, "Master Fader"); return 1;
              case BMC_DAW_ENC_CMD_SCRUB: strcpy(str, "Jog Wheel"); return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetDawTrackField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawDisplay(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 3; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case 0: strcpy(str, "Meters"); return 1;
              case 1: strcpy(str, "Channels"); return 1;
              case 2: strcpy(str, "Channel Info"); return 1;
              case 3: strcpy(str, "Assignment Display"); return 1;
            }
            return 1;
        }
        break;
      case 2:
        return eventGetDawTrackField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawMagicEncoder(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Action"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case 0: strcpy(str, "Ch. V-Pot"); return 1;
              case 1: strcpy(str, "Ch. Metter"); return 1;
              case 2: strcpy(str, "Ch. Fader"); return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetDawTrackField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeCustomSysex(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Command"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case 0: strcpy(str, "Send A"); return 1;
              case 1: strcpy(str, "Send A then B"); return 1;
              case 2: strcpy(str, "Send A & B Merged"); return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetField8BitValueRange(str, "Custom SysEx A", fieldRequest, 1, 0, BMC_MAX_CUSTOM_SYSEX-1, true);
      case 3:
        return eventGetField8BitValueRange(str, "Custom SysEx B", fieldRequest, 2, 0, BMC_MAX_CUSTOM_SYSEX-1, true);
      case 4:
        return eventGetPortsField(str, fieldRequest, field);
    }
    return 0;
  }
  uint16_t eventBmcEventTypePixelProgram(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Program", fieldRequest, 0, 0, BMC_MAX_PIXEL_PROGRAMS-1, true);
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollLimitField(str, fieldRequest);
    }
    return 0;
  }


};
#endif
#endif