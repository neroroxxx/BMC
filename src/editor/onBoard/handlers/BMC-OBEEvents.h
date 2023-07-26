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
  uint16_t constrainValue(uint16_t value, uint16_t t_min, uint16_t t_max){
    if(value < t_min){
      return t_min;
    }
    if(value > t_max){
      return t_max;
    }
    return value;
  }
  uint16_t setNextFieldValue(uint8_t fieldN){
    uint16_t min = getData(5, fieldN, 1);
    uint16_t max = getData(5, fieldN, 2);
    tempValue = getData(5, fieldN, 3);
    tempValue = constrainValue(tempValue, min, max);
    if(!hasCustomScrollFieldValue(true, fieldN)){
      if(tempValue < max){
        tempValue++;
      } else {
        tempValue = min;
      }
    }
    getData(5, fieldN, 4);
    return tempValue;
  }
  uint16_t setPrevFieldValue(uint8_t fieldN){
    uint16_t min = getData(5, fieldN, 1);
    uint16_t max = getData(5, fieldN, 2);
    tempValue = getData(5, fieldN, 3);
    tempValue = constrainValue(tempValue, min, max);
    if(!hasCustomScrollFieldValue(false, fieldN)){
      if(tempValue > min){
        tempValue--;
      } else {
        tempValue = max;
      }
    }
    getData(5, fieldN, 4);
    return tempValue;
  }
  uint16_t hasCustomScrollFieldValue(bool direction, uint8_t fieldN){
    return getData(5, fieldN, direction ? 6 : 7);
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
          if(tempEvent.name == 0){
            strcpy(str, "None");
          } else {
            char str2[40];
            strcpy(str2, "...");
            if(tempValue <= BMC_MAX_NAMES_LIBRARY){
              editor.getDeviceNameFromIndex(tempEvent.name, str2);
            }
            sprintf(str, "#%u ", tempEvent.name);
            strcat(str, str2);
          }
          
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
    return eventGetSettingsFieldYesNo(str, "Scroll Enable", request, 0);
  }
  uint16_t eventGetScrollDirectionField(char* str, uint8_t request){
    // return eventGetSettingsFieldYesNo(str, "Scroll Up", request, 1);
    uint8_t value = bitRead(tempEvent.settings, 1);
    switch(request){
      case 0: strcpy(str, "Scroll Direction"); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 1; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        bitWrite(tempEvent.settings, 1, tempValue);
        return 1;
      case 5: /* formatted value */
        strcpy(str, (value == 0) ? "Down" : "Up");
        return 1;
    }
    return 0;
  }
  uint16_t eventGetScrollWrapField(char* str, uint8_t request){
    return eventGetSettingsFieldYesNo(str, "Scroll Wrap", request, 2);
  }
  uint16_t eventGetDawChannelField(char* str, uint8_t request){
    uint8_t value = BMC_GET_BYTE(1, tempEvent.event);
    switch(request){
      case 0: strcpy(str, "Channel #"); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 8; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
        return 1;
      case 5: /* formatted value */
        if(value == 8){
          strcpy(str, "Selected Channel");
        } else {
          sprintf(str, "# %u", value + offset);
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
    uint16_t value = BMC_GET_BYTE_2(bytePos, tempEvent.event);
    switch(request){
      case 0: strcpy(str, str2); return 1; /* label */
      case 1: return min; /* min */
      case 2: return max; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFFFF, bytePos*8);
        return 1;
      case 5: /* formatted value */
        sprintf(str, "%u", value + (useOffset ? offset : 0));
        return 1;
    }
    return 0;
  }
  uint16_t eventGetSettingsFieldYesNo(char* str, const char* str2, uint8_t request, uint8_t bitPos){
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
  uint16_t eventGetFieldYesNo(char* str, const char* str2, uint8_t request, uint8_t bitPos){
    uint8_t value = bitRead(tempEvent.event, bitPos);
    switch(request){
      case 0: strcpy(str, str2); return 1; /* label */
      case 1: return 0; /* min */
      case 2: return 1; /* max */
      case 3: return value; /* get stored value */
      case 4: /* set stored value */
        bitWrite(tempEvent.event, bitPos, tempValue);
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
        else if(request==4){ /* name */ strcpy(str, "None"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeNameOnly(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 7; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return true; }
        else if(request==4){ /* name */ strcpy(str, "Program Change"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeMidiProgramChange(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 8; }
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

      case BMC_EVENT_TYPE_PROGRAM_BANKING_SET:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Program Banking Set"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeProgramBankingSet(str, fieldRequest, field);}
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

      case BMC_EVENT_TYPE_LAYER:
        if(request==0){ /* available */ return BMC_MAX_LAYERS > 1; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Layer #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeLayer(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_PRESET:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 6; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Preset #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePreset(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_BANK:
        if(request==0){ /* available */ return BMC_MAX_PRESETS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Bank #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBank(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SETLIST:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "SetList #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSetlist(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_SONG:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeSong(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_PART:
        if(request==0){ /* available */ return BMC_MAX_SETLISTS > 0; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Song Part #"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypePart(str, fieldRequest, field);}
        break;

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
        
      case BMC_EVENT_TYPE_CUSTOM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Custom"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeCustom(str, fieldRequest, field);}
        break;

#if defined(BMC_HAS_DISPLAY)
      case BMC_EVENT_TYPE_DEVICE_NAME:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Device Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDeviceName(str, fieldRequest, field);}
        break;

      case BMC_EVENT_TYPE_NAME:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Name"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeName(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_DAW_LC)
      case BMC_EVENT_TYPE_DAW_COMMAND:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "DAW Command"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeDawCommand(str, fieldRequest, field);}
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

#if defined(BMC_USE_FAS)
      case BMC_EVENT_TYPE_FAS:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 1; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "FAS Cmd/Status"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeFasCommand(str, fieldRequest, field);}
        break;
      case BMC_EVENT_TYPE_FAS_SCENE:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 6; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "FAS Scene"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeFasScene(str, fieldRequest, field);}
        break;
      case BMC_EVENT_TYPE_FAS_PRESET:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "FAS Preset"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeFasPreset(str, fieldRequest, field);}
        break;
      case BMC_EVENT_TYPE_FAS_BLOCK:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 2; }
        else if(request==2){ /* scroll */ return false; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "FAS Block"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeFasBlock(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_HELIX)
      case BMC_EVENT_TYPE_HELIX:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 6; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Helix Cmd/Status"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeHelixCommand(str, fieldRequest, field);}
        break;
#endif

#if defined(BMC_USE_BEATBUDDY)
      case BMC_EVENT_TYPE_BEATBUDDY:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 5; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Beatbuddy Cmd/Status"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBeatbuddyCommand(str, fieldRequest, field);}
        break;
      case BMC_EVENT_TYPE_BEATBUDDY_BPM:
        if(request==0){ /* available */ return true; }
        else if(request==1){ /* fields */ return 4; }
        else if(request==2){ /* scroll */ return true; }
        else if(request==3){ /* ports */ return false; }
        else if(request==4){ /* name */ strcpy(str, "Beatbuddy BPM"); return 1;}
        else if(request==5){ /* field */ return eventBmcEventTypeBeatbuddyBpm(str, fieldRequest, field);}
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
        switch(fieldRequest){
          case 0: strcpy(str, "Program B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 128; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(2, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 16);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(2, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint8_t) BMC_GET_BYTE(2, tempEvent.event));
            }
            return 1;
        }
        break;
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollWrapField(str, fieldRequest);
      case 7:
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
        switch(fieldRequest){
          case 0: strcpy(str, "Value B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 128; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(3, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 24);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(3, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint8_t) BMC_GET_BYTE(3, tempEvent.event));
            }
            return 1;
        }
        break;
      case 5:
        return eventGetScrollEnableField(str, fieldRequest);
      case 6:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 7:
        return eventGetScrollWrapField(str, fieldRequest);
      case 8:
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
  uint16_t eventBmcEventTypeProgramBankingSet(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Program", fieldRequest, 0, 0, 127, false);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Program B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 128; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint8_t) BMC_GET_BYTE(1, tempEvent.event));
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
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
                  strcpy(str, "Set Layer"); return 1;
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
                strcpy(str, "Set Layer");
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
          case 0: strcpy(str, "Value"); return 1; /* label */
          case 1: return sb.min; /* min */
          case 2: return sb.max; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            BMCTools::getSketchByteFormat(str, index, tempValue);
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeLayer(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Layer", fieldRequest, 0, 0, BMC_MAX_LAYERS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Layer B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_LAYERS; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  // uint16_t eventBmcEventTypeLayerName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField16BitValueRange(str, "Layer", fieldRequest, 0, 0, BMC_MAX_LAYERS-1, true);
  //   }
  //   return 0;
  // }
  uint16_t eventBmcEventTypePreset(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Preset", fieldRequest, 0, 0, BMC_MAX_PRESETS_PER_BANK-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Preset B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_PRESETS_PER_BANK; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
            }
            return 1;
        }
        break;

      case 3:
        switch(fieldRequest){
          case 0: strcpy(str, "Scroll ALL"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(2, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 2);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(2, tempEvent.event)){
              case 0: strcpy(str, "OFF"); return 1;
              case 1: strcpy(str, "ON"); return 1;
            }
            return 1;
        }
        break;
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  // uint16_t eventBmcEventTypePresetName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField8BitValueRange(str, "Preset", fieldRequest, 0, 0, BMC_MAX_PRESETS_PER_BANK-1, true);
  //   }
  //   return 0;
  // }
  uint16_t eventBmcEventTypeBank(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      // case 1:
        // return eventGetField8BitValueRange(str, "Bank", fieldRequest, 0, 0, BMC_MAX_PRESET_BANKS-1, true);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Bank"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_PRESET_BANKS-1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            // char letter[3] = "";
            BMCTools::getBankLetter(BMC_GET_BYTE(0, tempEvent.event), str);
            // sprintf(str, "%s", letter);
            return 1;
        }
        break;
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Bank B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_PRESET_BANKS; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              // sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
              BMCTools::getBankLetter(BMC_GET_BYTE(1, tempEvent.event)-1, str);
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
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
        switch(fieldRequest){
          case 0: strcpy(str, "Setlist B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_SETLISTS; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  // uint16_t eventBmcEventTypeSetlistName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField8BitValueRange(str, "SetList", fieldRequest, 0, 0, BMC_MAX_SETLISTS-1, true);
  //   }
  //   return 0;
  // }
  // uint16_t eventBmcEventTypeSetlistSelectedName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField8BitValueRange(str, "SetList", fieldRequest, 0, 0, BMC_MAX_SETLISTS-1, true);
  //   }
  //   return 0;
  // }
  uint16_t eventBmcEventTypeSong(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Song", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONGS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Song B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_SETLISTS_SONGS; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  // uint16_t eventBmcEventTypeSongName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField8BitValueRange(str, "Song", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONGS-1, true);
  //   }
  //   return 0;
  // }
  uint16_t eventBmcEventTypePart(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Part", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONG_PARTS-1, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Part B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_SETLISTS_SONG_PARTS; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            if(BMC_GET_BYTE(1, tempEvent.event) == 0){
              strcpy(str, "OFF");
            } else {
              sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
            }
            return 1;
        }
        break;
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  // uint16_t eventBmcEventTypePartName(char* str, uint8_t fieldRequest, uint8_t field){
  //   switch(field){
  //     case 0:
  //       return eventNameField(str, fieldRequest, field);
  //     case 1:
  //       return eventGetField8BitValueRange(str, "Part", fieldRequest, 0, 0, BMC_MAX_SETLISTS_SONG_PARTS-1, true);
  //   }
  //   return 0;
  // }
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
  uint16_t eventBmcEventTypeCustom(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "ID", fieldRequest, 0, 0, 255, true);
    }
    return 0;
  }
  
  uint16_t eventBmcEventTypeName(char* str, uint8_t fieldRequest, uint8_t field){
switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Text"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_MAX_NAMES_LIBRARY; /* max */
          case 3: /* get stored value */
            return tempEvent.event & 0xFFFF;
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFFFF, 0);
            return 1;
          case 5: /* formatted value */
            {
              uint16_t index = tempEvent.event & 0xFFFF;
              if(index<BMC_MAX_NAMES_LIBRARY){
                if(strlen(display.midi.globals.store.global.names[index].name)>0){
                  sprintf(str, "#%u %s", index, display.midi.globals.store.global.names[index].name);
                } else {
                  sprintf(str, "#%u *EMPTY*", index);
                }
              }
            }
            
            return 0;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDeviceName(char* str, uint8_t fieldRequest, uint8_t field){
    uint16_t len = 0;
    for(uint8_t i = 0, n = editor.devicesDataLength ; i < n ; i++){
      if(editor.devicesData[i].hardware && editor.devicesData[i].group!=BMC_DEVICE_GROUP_DISPLAY){
        len++;
      }
    }
    if(len == 0){
      len = 1;
    }

    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Device"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return len-1; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            {
              uint16_t deviceLen = 0;
              bool updateD = false;
              uint16_t _tempValue = BMC_GET_BYTE(0, tempEvent.event);
              while(!checkIfDeviceIsValidForNameEvent(_tempValue)){
                updateD = true;
                _tempValue++;
                if(_tempValue >= 40){
                  _tempValue = 0;
                }
              }
              if(updateD){
                BMC_WRITE_BITS(tempEvent.event, _tempValue, 0xFF, 0);
              }
              for(uint8_t i = 0, n = editor.devicesDataLength ; i < n ; i++){
                if(editor.devicesData[i].hardware && editor.devicesData[i].group!=BMC_DEVICE_GROUP_DISPLAY){
                  if(editor.devicesData[i].id == _tempValue){
                    deviceLen = editor.devicesData[i].length;
                    strcpy(str, editor.devicesData[i].label);
                    break;
                  }
                }
              }
              if(BMC_GET_BYTE_2(1, tempEvent.event) >= deviceLen){
                BMC_WRITE_BITS(tempEvent.event, 0, 0xFFFF, 8);
              }
            }
            return 1;
          case 6:
            {
              tempValue++;
              if(tempValue >= 40){
                tempValue = 0;
              }
              while(!checkIfDeviceIsValidForNameEvent(tempValue)){
                tempValue++;
                if(tempValue >= 40){
                  tempValue = 0;
                }
              }
            }
            return 1;
          case 7:
            {
              if(tempValue > 0){
                tempValue--;
              } else {
                tempValue = 39;
              }
              while(!checkIfDeviceIsValidForNameEvent(tempValue)){
                if(tempValue > 0){
                  tempValue--;
                } else {
                  tempValue = 39;
                }
              }
            }
            return 1;
        }
        break;
      case 2:
        {
          uint8_t deviceLen = 0;
          for(uint8_t i = 0, n = editor.devicesDataLength ; i < n ; i++){
            if(editor.devicesData[i].hardware && editor.devicesData[i].group!=BMC_DEVICE_GROUP_DISPLAY){
              if(editor.devicesData[i].id == BMC_GET_BYTE(0, tempEvent.event)){
                deviceLen = editor.devicesData[i].length;
                break;
              }
            }
          }
          if(deviceLen == 0){
            deviceLen = 1;
          }
          return eventGetField16BitValueRange(str, "Device Index", fieldRequest, 1, 0, deviceLen-1, true);
        }
        break;
        
    }
    return 0;
  }
  bool checkIfDeviceIsValidForNameEvent(int16_t id){
    bool valid = false;
    for(uint8_t i = 0, n = editor.devicesDataLength ; i < n ; i++){
      if(editor.devicesData[i].hardware && editor.devicesData[i].group!=BMC_DEVICE_GROUP_DISPLAY){
        if(editor.devicesData[i].id == id){
          valid = true;
          break;
        }
      }
    }
    return valid;
  }
  uint16_t eventBmcEventTypeDawCommand(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Cmd/Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_DAW_CMD_SYNCED; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_DAW_CMD_REC: strcpy(str, "Ch. REC"); return 1;
              case BMC_DAW_CMD_SOLO: strcpy(str, "Ch. SOLO"); return 1;
              case BMC_DAW_CMD_MUTE: strcpy(str, "Ch. MUTE"); return 1;
              case BMC_DAW_CMD_SELECT: strcpy(str, "Ch. SELECT"); return 1;
              case BMC_DAW_CMD_VPOT_SELECT: strcpy(str, "Ch. VPot"); return 1;
              case BMC_DAW_CMD_ASSIGN_TRACK: strcpy(str, "VPot Assgn TRACK"); return 1;
              case BMC_DAW_CMD_ASSIGN_SEND: strcpy(str, "VPot Assgn SEND"); return 1;
              case BMC_DAW_CMD_ASSIGN_PAN: strcpy(str, "VPot Assgn PAN"); return 1;
              case BMC_DAW_CMD_ASSIGN_PLUGIN: strcpy(str, "VPot Assgn PLUGIN"); return 1;
              case BMC_DAW_CMD_ASSIGN_EQ: strcpy(str, "VPot Assgn EQ"); return 1;
              case BMC_DAW_CMD_ASSIGN_INSTR: strcpy(str, "VPot Assgn INSTR"); return 1;
              case BMC_DAW_CMD_BANK_LEFT: strcpy(str, "Bank NEXT"); return 1;
              case BMC_DAW_CMD_BANK_RIGHT: strcpy(str, "Bank PREV"); return 1;
              case BMC_DAW_CMD_CHANNEL_LEFT: strcpy(str, "Ch. NEXT"); return 1;
              case BMC_DAW_CMD_CHANNEL_RIGHT: strcpy(str, "Ch. PREV"); return 1;
              case BMC_DAW_CMD_FLIP: strcpy(str, "FLIP"); return 1;
              case BMC_DAW_CMD_GLOBAL_VIEW: strcpy(str, "GLOBAL"); return 1;
              case BMC_DAW_CMD_NAMEVAL: strcpy(str, "NAMEVAL"); return 1;
              case BMC_DAW_CMD_SMPTEBEATS: strcpy(str, "SMPTEBEATS"); return 1;
              case BMC_DAW_CMD_F1: strcpy(str, "F1"); return 1;
              case BMC_DAW_CMD_F2: strcpy(str, "F2"); return 1;
              case BMC_DAW_CMD_F3: strcpy(str, "F3"); return 1;
              case BMC_DAW_CMD_F4: strcpy(str, "F4"); return 1;
              case BMC_DAW_CMD_F5: strcpy(str, "F5"); return 1;
              case BMC_DAW_CMD_F6: strcpy(str, "F6"); return 1;
              case BMC_DAW_CMD_F7: strcpy(str, "F7"); return 1;
              case BMC_DAW_CMD_F8: strcpy(str, "F8"); return 1;
              case BMC_DAW_CMD_VIEW_MIDI: strcpy(str, "View MIDI"); return 1;
              case BMC_DAW_CMD_VIEW_INPUTS: strcpy(str, "View INPUTS"); return 1;
              case BMC_DAW_CMD_VIEW_AUDIO: strcpy(str, "View AUDIO"); return 1;
              case BMC_DAW_CMD_VIEW_INSTR: strcpy(str, "View INSTR"); return 1;
              case BMC_DAW_CMD_VIEW_AUX: strcpy(str, "View AUX"); return 1;
              case BMC_DAW_CMD_VIEW_BUS: strcpy(str, "View BUS"); return 1;
              case BMC_DAW_CMD_VIEW_OUT: strcpy(str, "View OUT"); return 1;
              case BMC_DAW_CMD_VIEW_USER: strcpy(str, "View USER"); return 1;
              case BMC_DAW_CMD_MOD_SHIFT: strcpy(str, "Mod SHIFT"); return 1;
              case BMC_DAW_CMD_MOD_OPTION: strcpy(str, "Mod OPTION"); return 1;
              case BMC_DAW_CMD_MOD_CONTROL: strcpy(str, "Mod CONTROL"); return 1;
              case BMC_DAW_CMD_MOD_CMD_ALT: strcpy(str, "Mod CMD"); return 1;
              case BMC_DAW_CMD_AUTOMATION_READ: strcpy(str, "READ"); return 1;
              case BMC_DAW_CMD_AUTOMATION_WRITE: strcpy(str, "WRITE"); return 1;
              case BMC_DAW_CMD_AUTOMATION_TRIM: strcpy(str, "TRIM"); return 1;
              case BMC_DAW_CMD_AUTOMATION_TOUCH: strcpy(str, "TOUCH"); return 1;
              case BMC_DAW_CMD_AUTOMATION_LATCH: strcpy(str, "LATCH"); return 1;
              case BMC_DAW_CMD_AUTOMATION_GROUP: strcpy(str, "GROUP"); return 1;
              case BMC_DAW_CMD_UTILITY_SAVE: strcpy(str, "SAVE"); return 1;
              case BMC_DAW_CMD_UTILITY_UNDO: strcpy(str, "UNDO"); return 1;
              case BMC_DAW_CMD_UTILITY_CANCEL: strcpy(str, "CANCEL"); return 1;
              case BMC_DAW_CMD_UTILITY_ENTER: strcpy(str, "ENTER"); return 1;
              case BMC_DAW_CMD_TRANSPORT_MARKER: strcpy(str, "MARKER"); return 1;
              case BMC_DAW_CMD_TRANSPORT_NUDGE: strcpy(str, "NUDGE"); return 1;
              case BMC_DAW_CMD_TRANSPORT_CYCLE: strcpy(str, "CYCLE"); return 1;
              case BMC_DAW_CMD_TRANSPORT_DROP: strcpy(str, "DROP"); return 1;
              case BMC_DAW_CMD_TRANSPORT_REPLACE: strcpy(str, "REPLACE"); return 1;
              case BMC_DAW_CMD_TRANSPORT_CLICK: strcpy(str, "CLICK"); return 1;
              case BMC_DAW_CMD_TRANSPORT_SOLO: strcpy(str, "SOLO"); return 1;
              case BMC_DAW_CMD_TRANSPORT_REWIND: strcpy(str, "REWIND"); return 1;
              case BMC_DAW_CMD_TRANSPORT_FORWARD: strcpy(str, "FORWARD"); return 1;
              case BMC_DAW_CMD_TRANSPORT_STOP: strcpy(str, "STOP"); return 1;
              case BMC_DAW_CMD_TRANSPORT_PLAY: strcpy(str, "PLAY"); return 1;
              case BMC_DAW_CMD_TRANSPORT_REC: strcpy(str, "REC"); return 1;
              case BMC_DAW_CMD_CURSOR_UP: strcpy(str, "Cursor UP"); return 1;
              case BMC_DAW_CMD_CURSOR_DOWN: strcpy(str, "Cursor DOWN"); return 1;
              case BMC_DAW_CMD_CURSOR_LEFT: strcpy(str, "Cursor LEFT"); return 1;
              case BMC_DAW_CMD_CURSOR_RIGHT: strcpy(str, "Cursor RIGHT"); return 1;
              case BMC_DAW_CMD_CURSOR_ZOOM: strcpy(str, "Cursor ZOOM"); return 1;
              case BMC_DAW_CMD_SCRUB: strcpy(str, "SCRUB"); return 1;
              case BMC_DAW_CMD_FADER_TOUCH: strcpy(str, "FADER TOUCH"); return 1;
              case BMC_DAW_CMD_FADER_TOUCH_MASTER: strcpy(str, "FADER TOUCH MASTER"); return 1;
              case BMC_DAW_CMD_SMPTE: strcpy(str, "SMPTE LED"); return 1;
              case BMC_DAW_CMD_BEATS: strcpy(str, "BEATS LED"); return 1;
              case BMC_DAW_CMD_RUDE_SOLO: strcpy(str, "RUDE SOLO LED"); return 1;
              case BMC_DAW_CMD_RELAY: strcpy(str, "RELAY LED"); return 1;
              case BMC_DAW_CMD_METER_LED_PEAK: strcpy(str, "METER LED PEAK"); return 1;
              case BMC_DAW_CMD_METER_LED_1: strcpy(str, "METER LED 1"); return 1;
              case BMC_DAW_CMD_METER_LED_2: strcpy(str, "METER LED 2"); return 1;
              case BMC_DAW_CMD_METER_LED_3: strcpy(str, "METER LED 3"); return 1;
              case BMC_DAW_CMD_METER_LED_4: strcpy(str, "METER LED 4"); return 1;
              case BMC_DAW_CMD_METER_LED_5: strcpy(str, "METER LED 5"); return 1;
              case BMC_DAW_CMD_METER_LED_6: strcpy(str, "METER LED 6"); return 1;
              case BMC_DAW_CMD_METER_LED_7: strcpy(str, "METER LED 7"); return 1;
              case BMC_DAW_CMD_METER_LED_8: strcpy(str, "METER LED 8"); return 1;
              case BMC_DAW_CMD_METER_LED_9: strcpy(str, "METER LED 9"); return 1;
              case BMC_DAW_CMD_METER_LED_10: strcpy(str, "METER LED 10"); return 1;
              case BMC_DAW_CMD_METER_LED_11: strcpy(str, "METER LED 11"); return 1;
              case BMC_DAW_CMD_METER_LED_12: strcpy(str, "METER LED 12"); return 1;
              case BMC_DAW_CMD_VPOT_LED_1: strcpy(str, "VPOT LED 1"); return 1;
              case BMC_DAW_CMD_VPOT_LED_2: strcpy(str, "VPOT LED 2"); return 1;
              case BMC_DAW_CMD_VPOT_LED_3: strcpy(str, "VPOT LED 3"); return 1;
              case BMC_DAW_CMD_VPOT_LED_4: strcpy(str, "VPOT LED 4"); return 1;
              case BMC_DAW_CMD_VPOT_LED_5: strcpy(str, "VPOT LED 5"); return 1;
              case BMC_DAW_CMD_VPOT_LED_6: strcpy(str, "VPOT LED 6"); return 1;
              case BMC_DAW_CMD_VPOT_LED_7: strcpy(str, "VPOT LED 7"); return 1;
              case BMC_DAW_CMD_VPOT_LED_8: strcpy(str, "VPOT LED 8"); return 1;
              case BMC_DAW_CMD_VPOT_LED_9: strcpy(str, "VPOT LED 9"); return 1;
              case BMC_DAW_CMD_VPOT_LED_10: strcpy(str, "VPOT LED 10"); return 1;
              case BMC_DAW_CMD_VPOT_LED_11: strcpy(str, "VPOT LED 11"); return 1;
              case BMC_DAW_CMD_VPOT_LED_CENTER: strcpy(str, "VPOT LED CENTERED"); return 1;
              case BMC_DAW_CMD_PREV_MARKER: strcpy(str, "PREV MARKER"); return 1;
              case BMC_DAW_CMD_NEXT_MARKER: strcpy(str, "NEXT MARKER"); return 1;
              case BMC_DAW_CMD_SYNCED: strcpy(str, "SYNCED"); return 1;
              
            }
            return 0;
        }
        break;
      case 2:
        return eventGetDawChannelField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeDawDisplay(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Status"); return 1; /* label */
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
        return eventGetDawChannelField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeFasCommand(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Cmd/Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_FAS_CMD_LOOPER_ONCE; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_FAS_CMD_CONNECTION:   strcpy(str, "Connection");return 1;
              case BMC_FAS_CMD_TUNER_ON:   strcpy(str, "Tuner On");return 1;
              case BMC_FAS_CMD_TUNER_OFF:   strcpy(str, "Tuner Off");return 1;
              case BMC_FAS_CMD_TUNER_TOGGLE:   strcpy(str, "Tuner Toggle");return 1;
              case BMC_FAS_CMD_TUNER_IN_TUNE:   strcpy(str, "Tuner In Tune");return 1;
              case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:   strcpy(str, "Tuner Out of Tune");return 1;
              case BMC_FAS_CMD_TUNER_FLAT:   strcpy(str, "Tuner Flat");return 1;
              case BMC_FAS_CMD_TUNER_FLATTER:   strcpy(str, "Tuner Flatter");return 1;
              case BMC_FAS_CMD_TUNER_FLATTEST:   strcpy(str, "Tuner Flattest");return 1;
              case BMC_FAS_CMD_TUNER_SHARP:   strcpy(str, "Tuner Sharp");return 1;
              case BMC_FAS_CMD_TUNER_SHARPER:   strcpy(str, "Tuner Sharper");return 1;
              case BMC_FAS_CMD_TUNER_SHARPEST:   strcpy(str, "Tuner Sharpest");return 1;
              case BMC_FAS_CMD_LOOPER_PLAY:  strcpy(str, "Looper PLAY");return 1;
              case BMC_FAS_CMD_LOOPER_REC:  strcpy(str, "Looper REC");return 1;
              case BMC_FAS_CMD_LOOPER_DUB:  strcpy(str, "Looper DUB");return 1;
              case BMC_FAS_CMD_LOOPER_REV:  strcpy(str, "Looper REVERSE");return 1;
              case BMC_FAS_CMD_LOOPER_HALF:  strcpy(str, "Looper HALF");return 1;
              case BMC_FAS_CMD_LOOPER_UNDO:  strcpy(str, "Looper UNDO");return 0; // looper undo
              case BMC_FAS_CMD_LOOPER_RDP:  strcpy(str, "Rec/Dub/Ply");return 0; // looper undo
              case BMC_FAS_CMD_LOOPER_RPD:  strcpy(str, "Rec/Ply/Dub");return 0; // looper undo
              case BMC_FAS_CMD_LOOPER_STOP:  strcpy(str, "Looper STOP");return 0; // looper undo
              case BMC_FAS_CMD_LOOPER_CLEAR:  strcpy(str, "Looper CLEAR");return 0; // looper undo
              case BMC_FAS_CMD_LOOPER_ONCE:  strcpy(str, "Looper ONCE");return 0; // looper once
              case BMC_FAS_CMD_TAP:  strcpy(str, "Tap Tempo");return 0; // tap tempo
            }
            return 0;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeFasScene(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField8BitValueRange(str, "Scene", fieldRequest, 0, 0, 7, true);
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Scene Toggle"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 8; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(1, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(1, tempEvent.event)){
              case 0:
                strcpy(str, "OFF");
                return 1;
              case 1: case 2:
              case 3: case 4:
              case 5: case 6:
              case 7: case 8:
                sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(1, tempEvent.event)-1)+offset));
                return 1;
            }
            return 0;
        }
      case 3:
        return eventGetFieldYesNo(str, "Revert", fieldRequest, 16);
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeFasPreset(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        return eventGetField16BitValueRange(str, "Preset", fieldRequest, 0, 0, 767, true);
      case 2:
        {
          uint16_t value = BMC_GET_BYTE_2(2, tempEvent.event) & 0x3FF;
          switch(fieldRequest){
            case 0: strcpy(str, "Preset Toggle"); return 1; /* label */
            case 1: return 0; /* min */
            case 2: return 768; /* max */
            case 3: /* get stored value */
              return value;
              // return (tempEvent.event >> 16) & 0x3FF;
            case 4: /* set stored value */
              BMC_WRITE_BITS(tempEvent.event, tempValue, 0x7FF, 16);
              return 1;
            case 5: /* formatted value */
              if(value == 0){
                strcpy(str, "OFF");
              } else {
                sprintf(str, "%u", (value-1)+offset);
              }
              return 1;
          }
        }
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeFasBlock(char* str, uint8_t fieldRequest, uint8_t field){
    
    #if !defined(BMC_USE_FAS3)
      uint8_t paramCount = 5;
      uint16_t blockMin = 100;
      uint16_t blockMax = 170;
    #else
      uint8_t paramCount = 8;
      uint16_t blockMin = 37;
      uint16_t blockMax = 196;
    #endif
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Cmd/Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return paramCount; /* max */
          case 3: /* get stored value */
            {
              uint8_t b = BMC_GET_BYTE(0, tempEvent.event);
              return constrain(b, 0, paramCount);
            }
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            #if !defined(BMC_USE_FAS3)
              switch(BMC_GET_BYTE(0, tempEvent.event)){
                case 0: strcpy(str, "Bypass"); return 1;
                case 1: strcpy(str, "Engage"); return 1;
                case 2: strcpy(str, "Toggle Bypass"); return 1;
                case 3: strcpy(str, "Set to X"); return 1;
                case 4: strcpy(str, "Set to Y"); return 1;
                case 5: strcpy(str, "Toggle X/Y"); return 1;
              }
            #else
              switch(BMC_GET_BYTE(0, tempEvent.event)){
                case 0: strcpy(str, "Bypass"); return 1;
                case 1: strcpy(str, "Engage"); return 1;
                case 2: strcpy(str, "Toggle Bypass"); return 1;
                case 3: strcpy(str, "Set Channel A"); return 1;
                case 4: strcpy(str, "Set Channel B"); return 1;
                case 5: strcpy(str, "Set Channel C"); return 1;
                case 6: strcpy(str, "Set Channel D"); return 1;
                case 7: strcpy(str, "Toggle Channel A / B"); return 1;
                case 8: strcpy(str, "Toggle Channel C / D"); return 1;
              }
            #endif
            return 0;
        }
        break;
      case 2:
        switch(fieldRequest){
          case 0: strcpy(str, "Block"); return 1; /* label */
          case 1: return blockMin; /* min */
          case 2: return blockMax; /* max */
          case 3: /* get stored value */
            {
              uint8_t b = BMC_GET_BYTE(1, tempEvent.event);
              return constrain(b, blockMin, blockMax);
            }
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 8);
            return 1;
          case 5: /* formatted value */
            {
              uint8_t b = BMC_GET_BYTE(1, tempEvent.event);
              b = constrain(b, blockMin, blockMax);

              switch(b){
              #if !defined(BMC_USE_FAS3)
                case 100: strcpy(str, "CPR"); return 1;
                case 101: strcpy(str, "CPR 2"); return 1;
                case 102: strcpy(str, "GEQ"); return 1;
                case 103: strcpy(str, "GEQ 2"); return 1;
                case 104: strcpy(str, "PEQ"); return 1;
                case 105: strcpy(str, "PEQ 2"); return 1;
                case 106: strcpy(str, "AMP"); return 1;
                case 107: strcpy(str, "AMP 2"); return 1;
                case 108: strcpy(str, "CAB"); return 1;
                case 109: strcpy(str, "CAB 2"); return 1;
                case 110: strcpy(str, "REV"); return 1;
                case 111: strcpy(str, "REV 2"); return 1;
                case 112: strcpy(str, "DLY"); return 1;
                case 113: strcpy(str, "DLY 2"); return 1;
                case 114: strcpy(str, "MTD"); return 1;
                case 115: strcpy(str, "MTD 2"); return 1;
                case 116: strcpy(str, "CHO"); return 1;
                case 117: strcpy(str, "CHO 2"); return 1;
                case 118: strcpy(str, "FLG"); return 1;
                case 119: strcpy(str, "FLG 2"); return 1;
                case 120: strcpy(str, "ROT"); return 1;
                case 121: strcpy(str, "ROT 2"); return 1;
                case 122: strcpy(str, "PHA"); return 1;
                case 123: strcpy(str, "PHA 2"); return 1;
                case 124: strcpy(str, "WAH"); return 1;
                case 125: strcpy(str, "WAH 2"); return 1;
                case 126: strcpy(str, "FRM"); return 1;
                case 127: strcpy(str, "VOL"); return 1;
                case 128: strcpy(str, "TRM"); return 1;
                case 129: strcpy(str, "TRM 2"); return 1;
                case 130: strcpy(str, "PIT"); return 1;
                case 131: strcpy(str, "FIL"); return 1;
                case 132: strcpy(str, "FIL 2"); return 1;
                case 133: strcpy(str, "DRV"); return 1;
                case 134: strcpy(str, "DRV 2"); return 1;
                case 135: strcpy(str, "ENH"); return 1;
                case 136: strcpy(str, "FXL"); return 1;
                case 137: strcpy(str, "MIX"); return 1;
                case 138: strcpy(str, "MIX 2"); return 1;
                case 139: strcpy(str, "ING not used"); return 1;
                case 140: strcpy(str, "OUT not used"); return 1;
                case 141: strcpy(str, "CTR not used"); return 1;
                case 142: strcpy(str, "SND not used"); return 1;
                case 143: strcpy(str, "RTN not used"); return 1;
                case 144: strcpy(str, "SYN"); return 1;
                case 145: strcpy(str, "SYN 2"); return 1;
                case 146: strcpy(str, "VOC"); return 1;
                case 147: strcpy(str, "MGT"); return 1;
                case 148: strcpy(str, "XVR"); return 1;
                case 149: strcpy(str, "XVR 2"); return 1;
                case 150: strcpy(str, "GTE"); return 1;
                case 151: strcpy(str, "GTE 2"); return 1;
                case 152: strcpy(str, "RNG"); return 1;
                case 153: strcpy(str, "PIT 2"); return 1;
                case 154: strcpy(str, "MBC"); return 1;
                case 155: strcpy(str, "MBC 2"); return 1;
                case 156: strcpy(str, "QCH"); return 1;
                case 157: strcpy(str, "QCH 2"); return 1;
                case 158: strcpy(str, "RES"); return 1;
                case 159: strcpy(str, "RES2"); return 1;
                case 160: strcpy(str, "GEQ 3"); return 1;
                case 161: strcpy(str, "GEQ 4"); return 1;
                case 162: strcpy(str, "PEQ 3"); return 1;
                case 163: strcpy(str, "PEQ 4"); return 1;
                case 164: strcpy(str, "FIL 3"); return 1;
                case 165: strcpy(str, "FIL 4"); return 1;
                case 166: strcpy(str, "VOL 2"); return 1;
                case 167: strcpy(str, "VOL 3"); return 1;
                case 168: strcpy(str, "VOL 4"); return 1;
                case 169: strcpy(str, "LPR"); return 1;
                case 170: strcpy(str, "TMA"); return 1;
              #else
                case 37: strcpy(str, "IN 1"); return 1;
                case 38: strcpy(str, "IN 2"); return 1;
                case 39: strcpy(str, "IN 3"); return 1;
                case 40: strcpy(str, "IN 4"); return 1;
                case 41: strcpy(str, "IN 5"); return 1;
                case 42: strcpy(str, "OUT 1"); return 1;
                case 43: strcpy(str, "OUT 2"); return 1;
                case 44: strcpy(str, "OUT 3"); return 1;
                case 45: strcpy(str, "OUT 4"); return 1;
                case 46: strcpy(str, "CMP 1"); return 1;
                case 47: strcpy(str, "CMP 2"); return 1;
                case 48: strcpy(str, "CMP 3"); return 1;
                case 49: strcpy(str, "CMP 4"); return 1;
                case 50: strcpy(str, "GEQ 1"); return 1;
                case 51: strcpy(str, "GEQ 2"); return 1;
                case 52: strcpy(str, "GEQ 3"); return 1;
                case 53: strcpy(str, "GEQ 4"); return 1;
                case 54: strcpy(str, "PEQ 1"); return 1;
                case 55: strcpy(str, "PEQ 2"); return 1;
                case 56: strcpy(str, "PEQ 3"); return 1;
                case 57: strcpy(str, "PEQ 4"); return 1;
                case 58: strcpy(str, "AMP 1"); return 1;
                case 59: strcpy(str, "AMP 2"); return 1;
                case 62: strcpy(str, "CAB 1"); return 1;
                case 63: strcpy(str, "CAB 2"); return 1;
                case 66: strcpy(str, "REV 1"); return 1;
                case 67: strcpy(str, "REV 2"); return 1;
                case 70: strcpy(str, "DLY 1"); return 1;
                case 71: strcpy(str, "DLY 2"); return 1;
                case 72: strcpy(str, "DLY 3"); return 1;
                case 73: strcpy(str, "DLY 4"); return 1;
                case 74: strcpy(str, "MTD 1"); return 1;
                case 75: strcpy(str, "MTD 2"); return 1;
                case 78: strcpy(str, "CHO 1"); return 1;
                case 79: strcpy(str, "CHO 2"); return 1;
                case 82: strcpy(str, "FLG 1"); return 1;
                case 83: strcpy(str, "FLG 2"); return 1;
                case 86: strcpy(str, "ROT 1"); return 1;
                case 87: strcpy(str, "ROT 2"); return 1;
                case 90: strcpy(str, "PHA 1"); return 1;
                case 91: strcpy(str, "PHA 2"); return 1;
                case 94: strcpy(str, "WAH 1"); return 1;
                case 95: strcpy(str, "WAH 2"); return 1;
                case 98: strcpy(str, "FOR 1"); return 1;
                case 99: strcpy(str, "FOR 2"); return 1;
                case 102: strcpy(str, "VOL 1"); return 1;
                case 103: strcpy(str, "VOL 2"); return 1;
                case 104: strcpy(str, "VOL 3"); return 1;
                case 105: strcpy(str, "VOL 4"); return 1;
                case 106: strcpy(str, "TRM 1"); return 1;
                case 107: strcpy(str, "TRM 2"); return 1;
                case 110: strcpy(str, "PIT 1"); return 1;
                case 111: strcpy(str, "PIT 2"); return 1;
                case 114: strcpy(str, "FIL 1"); return 1;
                case 115: strcpy(str, "FIL 2"); return 1;
                case 116: strcpy(str, "FIL 3"); return 1;
                case 117: strcpy(str, "FIL 4"); return 1;
                case 118: strcpy(str, "DRV 1"); return 1;
                case 119: strcpy(str, "DRV 2"); return 1;
                case 120: strcpy(str, "DRV 3"); return 1;
                case 121: strcpy(str, "DRV 4"); return 1;
                case 122: strcpy(str, "ENH 1"); return 1;
                case 123: strcpy(str, "ENH 2"); return 1;
                case 130: strcpy(str, "SYN 1"); return 1;
                case 131: strcpy(str, "SYN 2"); return 1;
                case 134: strcpy(str, "VOC 1"); return 1;
                case 138: strcpy(str, "MGT 1"); return 1;
                case 139: strcpy(str, "MGT 2"); return 1;
                case 142: strcpy(str, "XVR 1"); return 1;
                case 143: strcpy(str, "XVR 2"); return 1;
                case 146: strcpy(str, "GTE 1"); return 1;
                case 147: strcpy(str, "GTE 2"); return 1;
                case 148: strcpy(str, "GTE 3"); return 1;
                case 149: strcpy(str, "GTE 4"); return 1;
                case 150: strcpy(str, "RNG 1"); return 1;
                case 154: strcpy(str, "MBC 1"); return 1;
                case 155: strcpy(str, "MBC 2"); return 1;
                case 158: strcpy(str, "TTD 1"); return 1;
                case 159: strcpy(str, "TTD 2"); return 1;
                case 162: strcpy(str, "RES 1"); return 1;
                case 163: strcpy(str, "RES 2"); return 1;
                case 166: strcpy(str, "LPR 1"); return 1;
                case 170: strcpy(str, "TMA 1"); return 1;
                case 178: strcpy(str, "PLX 1"); return 1;
                case 179: strcpy(str, "PLX 2"); return 1;
                case 182: strcpy(str, "SND 1"); return 1;
                case 183: strcpy(str, "SND 2"); return 1;
                case 186: strcpy(str, "RTN 1"); return 1;
                case 187: strcpy(str, "RTN 2"); return 1;
                case 195: strcpy(str, "IRP 1"); return 1;
                case 196: strcpy(str, "IRP 2"); return 1;
              #endif
              }
            }
            return 0;
        }
        break;
    }
    return 0;
  }
  uint16_t eventBmcEventTypeHelixCommand(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Cmd/Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_FAS_CMD_TAP; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(0, tempEvent.event)){
              case BMC_HELIX_CMD_TAP:   strcpy(str, "Tap");return 1;
              case BMC_HELIX_CMD_TUNER:   strcpy(str, "Tuner");return 1;
              case BMC_HELIX_CMD_SNAPSHOT:   strcpy(str, "Snapshot");return 1;
              case BMC_HELIX_CMD_SNAPSHOT_TOGGLE:   strcpy(str, "Snapshot Toggle");return 1;
            }
            return 0;
        }
        break;
      case 2:
        return eventGetField8BitValueRange(str, "Snapshot", fieldRequest, 1, 0, 7, true);
      case 3:
        switch(fieldRequest){
          case 0: strcpy(str, "Snapshot B"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return 8; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(2, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 16);
            return 1;
          case 5: /* formatted value */
            switch(BMC_GET_BYTE(2, tempEvent.event)){
              case 0:
                strcpy(str, "OFF");
                return 1;
              case 1: case 2:
              case 3: case 4:
              case 5: case 6:
              case 7: case 8:
                sprintf(str, "%u", (uint16_t)((BMC_GET_BYTE(2, tempEvent.event)-1)+offset));
                return 1;
            }
            return 0;
        }
        break;
      case 4:
        return eventGetScrollEnableField(str, fieldRequest);
      case 5:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 6:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBeatbuddyCommand(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "Cmd/Status"); return 1; /* label */
          case 1: return 0; /* min */
          case 2: return BMC_BEATBUDDY_CMD_TRANS_NEXT; /* max */
          case 3: /* get stored value */
            return BMC_GET_BYTE(0, tempEvent.event);
          case 4: /* set stored value */
            BMC_WRITE_BITS(tempEvent.event, tempValue, 0xFF, 0);
            return 1;
          case 5: /* formatted value */
          {
            uint8_t d = BMC_GET_BYTE(0, tempEvent.event);
            if(d>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && d<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
              sprintf(str,"Part %u",(d-BMC_BEATBUDDY_CMD_TRANS_PART_1)+offset);
              return 1;
            }
            switch(d){
              case BMC_BEATBUDDY_CMD_START: strcpy(str, "Start"); return 1;
              case BMC_BEATBUDDY_CMD_STOP: strcpy(str, "Stop"); return 1;
              case BMC_BEATBUDDY_CMD_BPM_DEC: strcpy(str, "BPM Dec"); return 1;
              case BMC_BEATBUDDY_CMD_BPM_INC: strcpy(str, "BPM Inc"); return 1;
              case BMC_BEATBUDDY_CMD_PAUSE: strcpy(str, "Pause"); return 1;
              case BMC_BEATBUDDY_CMD_UNPAUSE: strcpy(str, "Unpause"); return 1;
              case BMC_BEATBUDDY_CMD_PAUSE_TOGGLE: strcpy(str, "Pause Toggle"); return 1;
              case BMC_BEATBUDDY_CMD_DRUM_FILL: strcpy(str, "Drum Fill"); return 1;
              case BMC_BEATBUDDY_CMD_TAP: strcpy(str, "Tap"); return 1;
              case BMC_BEATBUDDY_CMD_OUTRO: strcpy(str, "Outtro"); return 1;
              case BMC_BEATBUDDY_CMD_MIX_VOL: strcpy(str, "Mix Vol"); return 1;
              case BMC_BEATBUDDY_CMD_HP_VOL: strcpy(str, "HP Vol"); return 1;
              case BMC_BEATBUDDY_CMD_ACCENT_HIT: strcpy(str, "Accent Hit"); return 1;
              case BMC_BEATBUDDY_CMD_DRUMSET_SELECT: strcpy(str, "Drumset Sel"); return 1;
              case BMC_BEATBUDDY_CMD_NORMAL_TIME: strcpy(str, "Normal Time"); return 1;
              case BMC_BEATBUDDY_CMD_HALF_TIME: strcpy(str, "Half Time"); return 1;
              case BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE: strcpy(str, "Half Time Tggle"); return 1;
              case BMC_BEATBUDDY_CMD_DOUBLE_TIME: strcpy(str, "Double Time"); return 1;
              case BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE: strcpy(str, "Dble Time Tggle"); return 1;
              case BMC_BEATBUDDY_CMD_FOLDER_ENTER: strcpy(str, "Folder Enter"); return 1;
              case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN: strcpy(str, "Song Scroll Down"); return 1;
              case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP: strcpy(str, "Song Scroll Up"); return 1;
              case BMC_BEATBUDDY_CMD_TRANS_END: strcpy(str, "Trans End"); return 1;
              case BMC_BEATBUDDY_CMD_TRANS_PREV: strcpy(str, "Trans Prev"); return 1;
              case BMC_BEATBUDDY_CMD_TRANS_NEXT: strcpy(str, "Trans Next"); return 1;
            }
            return 1;
          }
            
          case 6: /* scroll value down */
            if(tempValue == 21){
              tempValue = 100;
            } else if (tempValue == BMC_BEATBUDDY_CMD_TRANS_NEXT){
              tempValue = 0;
            } else {
              tempValue++;
            }
            return 1;
          case 7: /* scroll value up */
            if(tempValue == 100){
              tempValue = 21;
            } else if (tempValue == 0){
              tempValue = BMC_BEATBUDDY_CMD_TRANS_NEXT;
            } else {
              tempValue--;
            }
            return 1;
        }
        break;
      case 2:
        return eventGetField8BitValueRange(str, "Data", fieldRequest, 1, 0, 127, false);
      case 3:
        return eventGetScrollEnableField(str, fieldRequest);
      case 4:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 5:
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }
  uint16_t eventBmcEventTypeBeatbuddyBpm(char* str, uint8_t fieldRequest, uint8_t field){
    switch(field){
      case 0:
        return eventNameField(str, fieldRequest, field);
      case 1:
        switch(fieldRequest){
          case 0: strcpy(str, "BPM"); return 1; /* label */
          case 1: return 40; /* min */
          case 2: return 300; /* max */
          case 3: /* get stored value */
            {
              uint16_t value = BMC_GET_BYTE_2(0, tempEvent.event);
              return constrain(value, 40, 300);
            }
          case 4: /* set stored value */
            tempEvent.event = tempValue;
            return 1;
          case 5: /* formatted value */
            {
              uint16_t value = BMC_GET_BYTE_2(0, tempEvent.event);
              value = constrain(value, 40, 300);
              sprintf(str, "%u", value);
              return 1;
            }
        }
      case 2:
        return eventGetScrollEnableField(str, fieldRequest);
      case 3:
        return eventGetScrollDirectionField(str, fieldRequest);
      case 4:
        return eventGetScrollWrapField(str, fieldRequest);
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
          case 2: return 2; /* max */
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
        return eventGetScrollWrapField(str, fieldRequest);
    }
    return 0;
  }


};
#endif
#endif