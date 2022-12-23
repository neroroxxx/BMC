/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_DEVICES_H
#define BMC_OBE_DEVICES_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "display/BMC-Display.h"
#include "editor/onBoard/BMC-OBEDef.h"

class BMCOBEDevices {
public:
  BMCOBEDevices(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display, BMCOBEData& t_data):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft),
                  data(t_data){

  }
  void begin(){

  }
  void update(){
    if(data.namesEditorActive){
      if(charBlinker.complete()){
        updateNamesEditorCursor();
      }
    }
    shiftActive = false;
  }
  bool isCompatible(uint16_t t_id=0xFFFF){
    uint8_t id = (t_id==0xFFFF) ? data.activeDevice.id : t_id;
    switch(id){
      case BMC_NONE:
      case BMC_DEVICE_ID_EVENT:
      case BMC_DEVICE_ID_POT_CALIBRATION:
      case BMC_DEVICE_ID_CUSTOM_SYSEX:
      case BMC_DEVICE_ID_SKETCH_BYTE:
      case BMC_DEVICE_ID_SHORTCUTS:
        return false;
    }
    return true;
  }
  void setTotalRows(){
    switch(data.activeDevice.id){
      case BMC_DEVICE_ID_PAGE:
        data.totalRows = 1;
        break;
      case BMC_DEVICE_ID_NAME:
        data.totalRows = data.activeDevice.length-1;
        break;
      case BMC_DEVICE_ID_BUTTON:
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
        // !add name field
        data.totalRows = 2;
        data.totalRows += data.activeDevice.settings;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_LED:
      case BMC_DEVICE_ID_GLOBAL_LED:
      case BMC_DEVICE_ID_PIXEL:
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
      case BMC_DEVICE_ID_PIXEL_STRIP:
      case BMC_DEVICE_ID_MAGIC_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
        data.totalRows = 1;
        data.totalRows += data.activeDevice.settings;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_BI_LED:
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        data.totalRows = 3;
        break;
      case BMC_DEVICE_ID_TRI_LED:
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        data.totalRows = 4;
        break;
      case BMC_DEVICE_ID_RGB_PIXEL:
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
        data.totalRows = 1;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_NL_RELAY:
      case BMC_DEVICE_ID_L_RELAY:
        data.totalRows = 5;
        break;
      case BMC_DEVICE_ID_TRIGGER:
        data.totalRows = 1;
        data.totalRows += 2;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
      case BMC_DEVICE_ID_OLED:
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
        // for all devices that only have a name and single event
        data.totalRows = 2;// one for name and one for event
        break;
      case BMC_DEVICE_ID_ILI:
        data.totalRows = 3;// one for name and one for event, 1 for settings
        break;
      case BMC_DEVICE_ID_LFO:
        data.totalRows = 1;
        data.totalRows += data.activeDevice.settings;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_TIMED_EVENT:
        // name, event, 2 settings split into 3 fields
        data.totalRows = 5;
        break;
      case BMC_DEVICE_ID_PRESET:
        // 1 setting byte but it's used for length
        data.totalRows = 1; // one for name
        data.totalRows += BMC_MAX_PRESET_ITEMS;
        break;
      case BMC_DEVICE_ID_SETLIST:
        // 1 setting byte but it's used for length
        data.totalRows = 1; // one for name
        data.totalRows += BMC_MAX_SETLISTS_SONGS;
        break;
      case BMC_DEVICE_ID_SETLIST_SONG:
        // 1 setting byte but it's used for length
        data.totalRows = 1; // one for name
        data.totalRows += BMC_MAX_SETLISTS_SONG_PARTS;
        break;
      case BMC_DEVICE_ID_AUX_JACK:
        // name, 3 events, 2 settings split into 4 fields
        data.totalRows = 1;
        data.totalRows += 4;
        data.totalRows += data.activeDevice.events;
        break;
      case BMC_DEVICE_ID_PORT_PRESET:
        data.totalRows = 1;// 1 for name
        data.totalRows += data.availablePorts;
        break;
    }
  }
  bool addRows(uint8_t startingPage){
    if(data.activeDevice.length == 0){
      return true;
    }
    switch(data.activeDevice.id){
      case BMC_DEVICE_ID_PAGE:
      case BMC_DEVICE_ID_NAME:
      case BMC_DEVICE_ID_BUTTON:
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
      case BMC_DEVICE_ID_LED:
      case BMC_DEVICE_ID_GLOBAL_LED:
      case BMC_DEVICE_ID_PIXEL:
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
      case BMC_DEVICE_ID_PIXEL_STRIP:
      case BMC_DEVICE_ID_RGB_PIXEL:
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
      case BMC_DEVICE_ID_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
      case BMC_DEVICE_ID_OLED:
      case BMC_DEVICE_ID_ILI:
      case BMC_DEVICE_ID_NL_RELAY:
      case BMC_DEVICE_ID_L_RELAY:
      case BMC_DEVICE_ID_MAGIC_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
      case BMC_DEVICE_ID_LFO:
      case BMC_DEVICE_ID_TRIGGER:
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
      case BMC_DEVICE_ID_TIMED_EVENT:
      case BMC_DEVICE_ID_PRESET:
      case BMC_DEVICE_ID_SETLIST:
      case BMC_DEVICE_ID_SETLIST_SONG:
      case BMC_DEVICE_ID_AUX_JACK:
      case BMC_DEVICE_ID_PORT_PRESET:
        for(uint8_t i = startingPage, e = 0; i < data.totalRows ; i++){
          data.addToVisibleList(i+1);
          e++;
          if(e >= BMC_OBE_ROWS_PER_PAGE){
            break;
          }
        }
        break;
    }
    return true;
  }
  uint16_t getOptionValue(uint16_t index){
    return getOptionLabel(index, BMC_OBE_DEVICE_OPT_VALUE);
  }
  uint16_t getOptionEditedValue(uint16_t index){
    return getOptionLabel(index, BMC_OBE_DEVICE_OPT_EDITED_VALUE);
  }
  bool handleCustomValueScroller(bool direction, bool t_shift){
    shiftActive = t_shift;
    if(direction){
      return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_CUSTOM_SCROLL_UP);
    }
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_CUSTOM_SCROLL_DOWN);
  }
  bool handleCustomRowScroller(bool direction, bool t_shift){
    shiftActive = t_shift;
    if(direction){
      return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_UP);
    }
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_DOWN);
  }
  bool hasCustomEditor(uint16_t index){
    return getOptionLabel(index, BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR);
  }
  bool setCustomEditorMode(bool state){
    return getOptionLabel(state, BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR_MODE);
  }
  uint16_t getMin(){
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_OPT_MIN);
  }
  uint16_t getMax(){
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_OPT_MAX);
  }
  uint16_t setOptionValue(){
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_OPT_CHANGED);
  }
  uint16_t handlePostSaveProcessing(){
    return getOptionLabel(data.activeRow-1, BMC_OBE_DEVICE_OPT_POST_SAVE);
  }
  uint16_t getOptionLabel(uint16_t index, uint8_t valueType=BMC_OBE_DEVICE_OPT_LABEL){
    offset = settings.getDisplayOffset()?0:1;
    uint16_t dIndex = data.deviceIndex-1;
    switch(data.activeDevice.id){
      case BMC_DEVICE_ID_PAGE:
        return getPageNameOption(index, valueType);
      case BMC_DEVICE_ID_EVENT:
        break;
      case BMC_DEVICE_ID_NAME:
        return getNamesEditor(store.global.names[dIndex], index, valueType);
      case BMC_DEVICE_ID_BUTTON:
        #if BMC_MAX_BUTTONS > 0
          return getButtonOption<BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>(store.pages[globals.page].buttons[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
        #if BMC_MAX_GLOBAL_BUTTONS > 0
          return getButtonOption<BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>(store.global.buttons[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_LED:
        #if BMC_MAX_LEDS > 0
          return getLedOption<1,1>(store.pages[globals.page].leds[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_LED:
        #if BMC_MAX_GLOBAL_LEDS > 0
          return getLedOption<1,1>(store.global.leds[dIndex], index, valueType);
        #endif
        break;




        
      case BMC_DEVICE_ID_BI_LED:
        #if BMC_MAX_BI_LEDS > 0
          return getBiLedOption<1,2>(store.pages[globals.page].biLeds[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          return getBiLedOption<1,2>(store.global.biLeds[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_TRI_LED:
        #if BMC_MAX_TRI_LEDS > 0
          return getTriLedOption<1,3>(store.pages[globals.page].triLeds[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          return getTriLedOption<1,3>(store.global.triLeds[dIndex], index, valueType);
        #endif
        break;




      case BMC_DEVICE_ID_ENCODER:
        #if BMC_MAX_ENCODERS > 0
          return getSingleEventDeviceOption<1,1>(store.pages[globals.page].encoders[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
        #if BMC_MAX_GLOBAL_ENCODERS > 0
          return getSingleEventDeviceOption<1,1>(store.global.encoders[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_OLED:
        #if BMC_MAX_OLED > 0
          return getSingleEventDeviceOption<1,1>(store.pages[globals.page].oled[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_ILI:
        #if BMC_MAX_ILI9341_BLOCKS > 0
          return getIliOption<1,1>(store.pages[globals.page].ili[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL:
        #if BMC_MAX_PIXELS > 0
          return getPixelOption<1,1>(store.pages[globals.page].pixels[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
        #if BMC_MAX_GLOBAL_PIXELS > 0
          return getPixelOption<1,1>(store.global.pixels[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_RGB_PIXEL:
        #if BMC_MAX_RGB_PIXELS > 0
          return getRgbPixelOption<1,3>(store.pages[globals.page].rgbPixels[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
          return getRgbPixelOption<1,3>(store.global.rgbPixels[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL_STRIP:
        #if BMC_MAX_PIXEL_STRIP > 0
          return getPixelOption<1,1>(store.pages[globals.page].pixelStrip[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_NL_RELAY:
        #if BMC_MAX_NL_RELAYS > 0
          return getRelayOption<1,1>(store.global.relaysNL[dIndex], index, valueType);
        #endif
      case BMC_DEVICE_ID_L_RELAY:
        #if BMC_MAX_L_RELAYS > 0
          return getRelayOption<1,1>(store.global.relaysL[dIndex], index, valueType);
        #endif
      case BMC_DEVICE_ID_MAGIC_ENCODER:
        #if BMC_MAX_MAGIC_ENCODERS > 0
          return getMagicEncoderOption<1,1>(store.pages[globals.page].magicEncoders[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
        #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
          return getMagicEncoderOption<1,1>(store.global.magicEncoders[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_LFO:
        #if BMC_MAX_LFO > 0
          return getLfoOption<3, 5, uint8_t>(store.global.lfo[dIndex], index, valueType);
        #endif
      case BMC_DEVICE_ID_TRIGGER:
        #if BMC_MAX_TRIGGERS > 0
          return getTriggerOption<1, 2, uint8_t>(store.global.triggers[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
        #if BMC_MAX_TEMPO_TO_TAP > 0
          return getSingleEventDeviceOption<1,1>(store.global.tempoToTap[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_TIMED_EVENT:
        #if BMC_MAX_TIMED_EVENTS > 0
          return getTimedEventOption<2,1>(store.global.timedEvents[dIndex], index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_PRESET:
        #if BMC_MAX_PRESETS > 0
          return getPresetsEditor(dIndex, index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST:
        #if BMC_MAX_SETLISTS > 0
          return getSetListsEditor(dIndex, index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST_SONG:
        #if BMC_MAX_SETLISTS > 0
          return getSongEditor(dIndex, index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_AUX_JACK:
        #if BMC_MAX_AUX_JACKS > 0
          return getAuxJackOption(dIndex, index, valueType);
        #endif
        break;
      case BMC_DEVICE_ID_PORT_PRESET:
        return getPortPresetsOption<0, 1, uint8_t>(store.global.portPresets[dIndex], index, valueType);
        break;
      /*
        #if BMC_MAX_AUX_JACKS > 0
          bmcStoreDevice <2, 3> auxJacks[BMC_MAX_AUX_JACKS];
        #endif
      */
    }
    strcpy(str, "undefined");
    return 0;
  }


  uint16_t getPresetsEditor(uint16_t deviceIndex, uint16_t index, uint8_t valueType=0){
    #if BMC_MAX_PRESETS > 0
    if(valueType == BMC_OBE_DEVICE_OPT_POST_SAVE){
      bmcEvent_t list[BMC_MAX_PRESET_ITEMS];
      memset(list, 0, BMC_MAX_PRESET_ITEMS);
      uint8_t counter = 0;
      for(uint8_t i = 0 ; i < BMC_MAX_PRESET_ITEMS ; i++){
        if(store.global.presets[deviceIndex].events[i]>0){
          list[counter++] = store.global.presets[deviceIndex].events[i];
        }
        // empty the entire preset
        store.global.presets[deviceIndex].events[i] = 0;
      }
      // set the length
      store.global.presets[deviceIndex].settings[0] = counter;
      for(uint8_t i = 0 ; i < counter ; i++){
        store.global.presets[deviceIndex].events[i] = list[i];
      }
      return 1;
    }
    uint16_t optionId = data.visibleRowId[index]-1;
    for(uint8_t i = 0, n = data.totalRows ; i < n ; i++){
      if(i==0){
        if(optionId == 0){
          return getNameField<1,BMC_MAX_PRESET_ITEMS>(store.global.presets[deviceIndex], valueType);
        }
      } else if(i == optionId){
        return getEventField<1,BMC_MAX_PRESET_ITEMS>(store.global.presets[deviceIndex], "Event", i-1, 1, valueType);
      }
    }
    #endif
    return 0;
  }
  
  uint16_t getSetListsEditor(uint16_t deviceIndex, uint16_t index, uint8_t valueType=0){
    #if BMC_MAX_SETLISTS > 0
    if(valueType == BMC_OBE_DEVICE_OPT_POST_SAVE){
      bmcEvent_t list[BMC_MAX_SETLISTS_SONGS];
      memset(list, 0, BMC_MAX_SETLISTS_SONGS);
      uint8_t counter = 0;
      for(uint8_t i = 0 ; i < BMC_MAX_SETLISTS_SONGS ; i++){
        if(store.global.setLists[deviceIndex].events[i]>0){
          list[counter++] = store.global.setLists[deviceIndex].events[i];
        }
        // empty the entire preset
        store.global.setLists[deviceIndex].events[i] = 0;
      }
      // set the length
      store.global.setLists[deviceIndex].settings[0] = counter;
      for(uint8_t i = 0 ; i < counter ; i++){
        store.global.setLists[deviceIndex].events[i] = list[i];
      }
      return 1;
    }
    uint16_t optionId = data.visibleRowId[index]-1;
    for(uint8_t i = 0, n = data.totalRows ; i < n ; i++){
      if(i==0){
        if(optionId == 0){
          return getNameField<1,BMC_MAX_SETLISTS_SONGS>(store.global.setLists[deviceIndex], valueType);
        }
      } else if(i == optionId){
        return getPartField<1,BMC_MAX_SETLISTS_SONGS>(store.global.setLists[deviceIndex], "Song", i-1, 1, valueType);
      }
    }
    #endif
    return 0;
  }
  
  uint16_t getAuxJackOption(uint16_t deviceIndex, uint16_t index, uint8_t valueType=0){
    #if BMC_MAX_AUX_JACKS > 0
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Mode");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              strcpy(str, (value==0)?"Dual Buttons":"Expression Pedal");
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 1;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 2:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Engage Mode");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? ((item.settings[1]>>6) & 0x03) : data.rowEditValue;
              strcpy(str, (value==0)?"Auto-Engage":"Toe Switch");
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 1;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t v = item.settings[0] & 0x3F;
              uint8_t newValue = v | (data.rowEditValue<<6);
              if(item.settings[1] != newValue){
                item.settings[1] = newValue;
                return 1;
              }
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 3:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Engage Value");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? (item.settings[1] & 0x07) : data.rowEditValue;
              sprintf(str, "%u", (value+1)*5);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 7;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t v = item.settings[0] & 0xF8;
              uint8_t newValue = v | data.rowEditValue;
              if(item.settings[1] != newValue){
                item.settings[1] = newValue;
                return 1;
              }
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 4:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Engage Speed");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? ((item.settings[1]>>3) & 0x07) : data.rowEditValue;
              sprintf(str, "%u ms", ((value+1)*100) + 200);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 7;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t v = item.settings[0] & 0x38;
              uint8_t newValue = v | (data.rowEditValue<<3);
              if(item.settings[1] != newValue){
                item.settings[1] = newValue;
                return 1;
              }
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 5:
        return getEventField<sLen,eLen,tname>(item, "Pot Event", 0, 0, valueType);
      case 6:
        return getEventField<sLen,eLen,tname>(item, "Btn 1 / Toe Switch Engage", 1, 0, valueType);
      case 7:
        return getEventField<sLen,eLen,tname>(item, "Btn 2 / Toe Switch Disengage", 2, 0, valueType);
      default:
        break;
    }
    return 0;
    #endif
    return 0;
  }
  uint16_t getSongEditor(uint16_t deviceIndex, uint16_t index, uint8_t valueType=0){
    #if BMC_MAX_SETLISTS > 0
    if(valueType == BMC_OBE_DEVICE_OPT_POST_SAVE){
      bmcEvent_t list[BMC_MAX_SETLISTS_SONG_PARTS];
      memset(list, 0, BMC_MAX_SETLISTS_SONG_PARTS);
      uint8_t counter = 0;
      for(uint8_t i = 0 ; i < BMC_MAX_SETLISTS_SONG_PARTS ; i++){
        if(store.global.songLibrary[deviceIndex].events[i]>0){
          list[counter++] = store.global.songLibrary[deviceIndex].events[i];
        }
        // empty the entire preset
        store.global.songLibrary[deviceIndex].events[i] = 0;
      }
      // set the length
      store.global.songLibrary[deviceIndex].settings[0] = counter;
      for(uint8_t i = 0 ; i < counter ; i++){
        store.global.songLibrary[deviceIndex].events[i] = list[i];
      }
      return 1;
    }
    uint16_t optionId = data.visibleRowId[index]-1;
    for(uint8_t i = 0, n = data.totalRows ; i < n ; i++){
      if(i==0){
        if(optionId == 0){
          return getNameField<1,BMC_MAX_SETLISTS_SONG_PARTS>(store.global.songLibrary[deviceIndex], valueType);
        }
      } else if(i == optionId){
        return getSongField<1,BMC_MAX_SETLISTS_SONG_PARTS>(store.global.songLibrary[deviceIndex], "Part", i-1, 1, valueType);
      }
    }
    #endif
    return 0;
  }
  
  uint16_t getNamesEditor(bmcStoreName& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR:
        // render
        if(!data.namesEditorActive){
          charIndex = 0;
          charValue = 0;
          charIndexState = false;
          charEditActive = false;
          charPage = 0;
          charPerPage = 0;
          memset(nameBuff, ' ', BMC_MAX_NAMES_LENGTH-1);
          strcpy(nameBuff, store.global.names[data.deviceIndex].name);
          for(uint8_t i = 0 ; i < BMC_MAX_NAMES_LENGTH-1 ; i++){
            if(nameBuff[i] == 0){
              nameBuff[i] = ' ';
            }
          }
          renderNamesEditor();
          data.namesEditorActive = true;
          charBlinker.start(300);
        }
        return 1;
      case BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR_MODE:
        charEditActive = (index>0);
        if(charEditActive){
          charValue = (uint8_t) nameBuff[charIndex];
          updateCharValue();
        } else {
          renderNamesEditor();
        }
        break;
      case BMC_OBE_DEVICE_OPT_LABEL:
        //strcpy(str, "");
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          // uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
          // strcpy(str, (value==0)?"Solid":"Blink");
          // return value;
          //renderNamesEditor(true);
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return 1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        {
          BMC_PRINT("BMC_OBE_DEVICE_OPT_CHANGED ");
          String buff = String(nameBuff);
          buff.trim();
          memset(nameBuff, 0, BMC_MAX_NAMES_LENGTH-1);
          buff.toCharArray(nameBuff, BMC_MAX_NAMES_LENGTH-1);
          bmcStoreName& nameObj = store.global.names[data.deviceIndex];
          if(strlen(nameBuff) != strlen(nameObj.name) || !BMC_STR_MATCH(nameBuff, nameObj.name)){
            strcpy(nameObj.name, nameBuff);
            return 1;
          }
        }
        BMC_PRINTLN("NO");
        return 0;
      case BMC_OBE_DEVICE_CUSTOM_SCROLL_UP:
        if(!data.namesEditorActive){
          return 0;
        } else {
          charValue++;
          if(charValue > 126){
            charValue = 32;
          }
          if(shiftActive){
            shiftActive = false;
            if(charValue < 48){
              charValue = 48;
            } else if(charValue < 65){
              charValue = 65;
            } else if(charValue < 97){
              charValue = 97;
            } else {
              charValue = 32;
            }
          }          
          nameBuff[charIndex] = (char) charValue;
          updateCharValue();
        }
        return 1;
      case BMC_OBE_DEVICE_CUSTOM_SCROLL_DOWN:
        if(!data.namesEditorActive){
          return 0;
        } else {
          charValue--;
          if(charValue < 32){
            charValue = 126;
          }
          if(shiftActive){
            shiftActive = false;
            if(charValue > 97){
              charValue = 97;
            } else if(charValue > 65){
              charValue = 65;
            } else if(charValue > 48){
              charValue = 48;
            } else if(charValue > 32){
              charValue = 32;
            } else {
              charValue = 97;
            }
          }
          nameBuff[charIndex] = (char) charValue;
          updateCharValue();
        }
        return 1;
      case BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_UP:
        if(!data.namesEditorActive){
          return 0;
        } else {
          if(data.activeRow == 0){
            data.triggerHeaderRender = true;
            data.activeRow = 1;
            charBlinker.start(300);
          }
          charIndex++;
          charIndex = (charIndex >= (BMC_MAX_NAMES_LENGTH-1)) ? 0 : charIndex;
          uint8_t p = floor((charIndex+0.0) / charPerPage);
          if(p != charPage){
            charPage = p;
            renderNamesEditor();
          } else {
            renderNamesEditorCursor();
          }
          // BMC_PRINTLN("charIndex", charIndex, "charPage", charPage);
        }
        return 1;
      case BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_DOWN:
        if(!data.namesEditorActive){
          return 0;
        } else {
          charIndex--;
          if(charIndex < 0){
            charIndex = -1;
            if(data.activeRow > 0){
              data.triggerHeaderRender = true;
              data.activeRow = 0;
            }
            charBlinker.stop();
            return 1;
          }
          charIndex = (charIndex < 0) ? (BMC_MAX_NAMES_LENGTH-2) : charIndex;
          uint8_t p = floor((charIndex+0.0) / charPerPage);
          if(p != charPage){
            charPage = p;
            renderNamesEditor();
          } else {
            renderNamesEditorCursor();
          }
          // BMC_PRINTLN("charIndex", charIndex, "charPage", charPage);
        }
        return 1;
      //case BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR_MODE:
        //return 0;
      default:
        return 0;
    }
    return 0;
  }
  void updateCharValue(){
    uint8_t fontSize = 5;
    uint8_t fontWidth = 6*fontSize;
    uint8_t fontHeight = 8*fontSize;
    uint16_t x = 10;
    uint16_t y = (BMC_OBE_ROW_HEAD_H+((BMC_OBE_ROW_AREA/2)-fontHeight));
    uint16_t charX = charIndex - (charPage*charPerPage);
    x += (charX*fontWidth);
    tft.display.setFontAdafruit();
    tft.display.setTextSize(fontSize);
    tft.display.setCursor(x, y);
    if(charEditActive){
      tft.display.setTextColor(BMC_ILI9341_YELLOW, BMC_ILI9341_BLACK);
    } else {
      tft.display.setTextColor(BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
    }
    tft.display.print(nameBuff[charIndex]);
    charIndexState = true;
    updateNamesEditorCursor();
  }
  void renderNamesEditor(){
    if(!data.namesEditorActive){
      tft.display.fillRect(0, BMC_OBE_ROW_HEAD_H, BMC_OBE_W, BMC_OBE_ROW_AREA, BMC_ILI9341_BLACK);
    }
    uint8_t fontSize = 5;
    uint8_t fontWidth = 6*fontSize;
    uint8_t fontHeight = 8*fontSize;
    uint16_t x = 10;
    uint16_t y = (BMC_OBE_ROW_HEAD_H+((BMC_OBE_ROW_AREA/2)-fontHeight));
    tft.display.setFontAdafruit();
    tft.display.setTextSize(fontSize);
    tft.display.setCursor(x, y);
    charPerPage = floor(BMC_OBE_W/(fontWidth+0.0));
    for(uint8_t i = 0; i < charPerPage ; i++){
      uint8_t c = i+(charPage*charPerPage);
      if(c==charIndex && charEditActive){
        tft.display.setTextColor(BMC_ILI9341_YELLOW, BMC_ILI9341_BLACK);
      } else {
        tft.display.setTextColor(BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
      }
      if(c >= BMC_MAX_NAMES_LENGTH){
        tft.display.print(" ");
      } else {
        if(nameBuff[c] == 0){
          tft.display.print(" ");
        } else {
          tft.display.print(nameBuff[c]);
        }
      }
    }
    charBlinker.start(300);
    renderNamesEditorCursor();
  }
  void updateCharTitle(){
    if(charIndex == -1){
      return;
    }
    tft.display.fillRect(0, BMC_OBE_ROW_HEAD_H, BMC_OBE_W, 30, BMC_ILI9341_RED);
    char buff[23] = "";
    sprintf(buff, "Char %u of %u", charIndex+offset, BMC_MAX_NAMES_LENGTH-1);
    tft.display.setTextColor(BMC_ILI9341_WHITE);
    tft.display.setFont(BMCLiberationSansNarrow_18);
    int16_t textWidth = tft.display.strPixelLen(buff);
    int16_t x = (BMC_OBE_W-textWidth) / 2;
    tft.display.setCursor(((x < 0) ? 0 : x), BMC_OBE_ROW_HEAD_H+5);
    tft.display.print(buff);
    tft.display.setFontAdafruit();
  }
  void renderNamesEditorCursor(){
    updateCharTitle();
    charIndexState = true;
    uint8_t fontSize = 5;
    uint8_t fontWidth = 6*fontSize;
    uint8_t fontHeight = 8*fontSize;
    uint16_t x = 10;
    uint16_t y = (BMC_OBE_ROW_HEAD_H+((BMC_OBE_ROW_AREA/2)-fontHeight));
    y += fontHeight+(fontSize*2);
    uint16_t charX = charIndex - (charPage*charPerPage);
    x += (charX*fontWidth);
    tft.display.fillRect(0, y, BMC_OBE_W, 3, BMC_ILI9341_BLACK);
    if(charIndex == -1){
      return;
    }
    tft.display.fillRect(x, y, fontWidth, 3, BMC_ILI9341_WHITE);
  }
  void updateNamesEditorCursor(){
    charIndexState = !charIndexState;
    uint8_t fontSize = 5;
    uint8_t fontWidth = 6*fontSize;
    uint8_t fontHeight = 8*fontSize;
    uint16_t x = 10;
    uint16_t y = (BMC_OBE_ROW_HEAD_H+((BMC_OBE_ROW_AREA/2)-fontHeight));
    y += fontHeight+(fontSize*2);
    uint16_t color = charEditActive ? BMC_ILI9341_YELLOW : BMC_ILI9341_WHITE;
    color = !charIndexState ? color : BMC_ILI9341_BLACK;
    uint16_t charX = charIndex - (charPage*charPerPage);
    x += (charX*fontWidth);
    tft.display.fillRect(x, y, fontWidth, 3, color);
    charBlinker.start(300);
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getButtonOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 5, "NoHoldOnContinuous", valueType);
        break;
      case 1:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 6, "NoReleaseOnDblPress", valueType);
        break;
      default:
        break;
    }
    // start at index 2 since 0 and 1 are flags
    for(uint8_t i = 2, e = 0, u = 0, n = data.totalRows ; i < n ; i++){
      if(i > 2){
        if(BMC_IS_ODD(i)){
          u++;
        }
      }
      e = (i-2) - u;
      if(i == optionId){
        // even index is settings, odd is event
        if(BMC_IS_EVEN(index)){
          switch(valueType){
            case BMC_OBE_DEVICE_OPT_LABEL:
              sprintf(str, "Mode # %u", e+offset);
              return 0;
            case BMC_OBE_DEVICE_OPT_VALUE:
            case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
              {
                uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? (item.settings[e] & 0x0F) : data.rowEditValue;
                BMCTools::getButtonTriggerName(value, str);
                return value;
              }
              break;
            case BMC_OBE_DEVICE_OPT_MIN: return 0;
            case BMC_OBE_DEVICE_OPT_MAX: return 12;
            case BMC_OBE_DEVICE_OPT_CHANGED:
              if(item.settings[e] != data.rowEditValue){
                item.settings[e] = data.rowEditValue;
                return 1;
              }
              return 0;
            default:
              return 0;
          }
        } else {
          return getEventField<sLen,eLen,tname>(item, e, 1, valueType);
        }
        e++;
        break;
      }
    }
    return 0;
  }
  uint16_t getPageNameOption(uint16_t index, uint8_t valueType=0){
    //getNameField
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getPageNameField(valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getLedOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Mode");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              strcpy(str, (value==0)?"Solid":"Blink");
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 1;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 2:
        return getEventField<sLen,eLen,tname>(item, 0, 0, valueType);
        break;
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getBiLedOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        return getEventField<sLen,eLen,tname>(item, 0, 1, valueType);
        break;
      case 2:
        return getEventField<sLen,eLen,tname>(item, 1, 1, valueType);
        break;
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getTriLedOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        return getEventField<sLen,eLen,tname>(item, 0, 1, valueType);
        break;
      case 2:
        return getEventField<sLen,eLen,tname>(item, 1, 1, valueType);
        break;
      case 3:
        return getEventField<sLen,eLen,tname>(item, 2, 1, valueType);
        break;
      default:
        break;
    }
    return 0;
  }


  











  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getSingleEventDeviceOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        return getEventField<sLen,eLen,tname>(item, 0, 0, valueType);
        break;
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getLfoOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Cycle Time");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              uint16_t formateValue = (value+1)*10;
              sprintf(str, "%u ms (about %u CC/sec)", formateValue, (60000/formateValue));
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 9;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 2:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Waveform");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[1] : data.rowEditValue;
              value = constrain(value, 1, 4);
              BMCTools::getLfoWaveformName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 1;
          case BMC_OBE_DEVICE_OPT_MAX: return 4;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[1] != data.rowEditValue){
              item.settings[1] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 3:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Note Division");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[2] : data.rowEditValue;
              BMCTools::getLfoNoteDivisionName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 4;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[2] != data.rowEditValue){
              item.settings[2] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 4:
        return getRangeField<sLen,eLen,tname>(item, "Channel", 0, 1, 0, 15, valueType);
      case 5:
        return getRangeField<sLen,eLen,tname>(item, "Control", 1, 0, 0, 127, valueType);
      case 6:
        return getRangeField<sLen,eLen,tname>(item, "Min Value", 2, 0, 0, 127, valueType);
      case 7:
        return getRangeField<sLen,eLen,tname>(item, "Max Value", 3, 0, 0, 127, valueType);
      case 8:
        return getPortsField<sLen,eLen,tname>(item, "Ports", 4, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getPortPresetsOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    //store.global.portPresets[deviceIndex]
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    if(optionId == 0){
      return getNameField<sLen, eLen, tname>(item, valueType);
    } else {
      for(uint8_t e = 0, i = 1 ; e < data.availablePorts ; e++, i++){
        if(i == optionId){
          switch(valueType){
            case BMC_OBE_DEVICE_OPT_LABEL:
              if(data.availablePortsData[e] == BMC_MIDI_PORT_USB_BIT){
                strcpy(str, "USB");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_SERIAL_A_BIT){
                strcpy(str, "Serial A");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_SERIAL_B_BIT){
                strcpy(str, "Serial B");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_SERIAL_C_BIT){
                strcpy(str, "Serial C");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_SERIAL_D_BIT){
                strcpy(str, "Serial D");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_HOST_BIT){
                strcpy(str, "USB Host");
              } else if(data.availablePortsData[e] == BMC_MIDI_PORT_BLE_BIT){
                strcpy(str, "BLE");
              }
              return 0;
            case BMC_OBE_DEVICE_OPT_VALUE:
            case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
              {
                uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? bitRead(item.events[0], e) : data.rowEditValue;
                value = constrain(value, 0, 1);
                strcpy(str, data.yesNoLabels[value]);
                return value;
              }
              break;
            case BMC_OBE_DEVICE_OPT_MIN: return 0;
            case BMC_OBE_DEVICE_OPT_MAX: return 1;
            case BMC_OBE_DEVICE_OPT_CHANGED:
              if(bitRead(item.events[0], e) != data.rowEditValue){
                bitWrite(item.events[0], e, data.rowEditValue);
                return 1;
              }
              return 0;
            default: return 0;
          }
          break;
        }
      }
    }
    return 0;
  }




  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getTimedEventOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Delay Time");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? (item.settings[0]) : data.rowEditValue;
              value = constrain(value, 0, 199);
              sprintf(str, "%u milliseconds", ((value + 1) * 10));
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 199;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 2:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Re-Trigger");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? (item.settings[0]&0x03) : data.rowEditValue;
              value = constrain(value, 0, 2);
              if(value == 0){
                strcpy(str, "Restart");
              } else if(value == 1){
                strcpy(str, "Stop");
              } else if(value == 2){
                strcpy(str, "Ignore");
              }
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 2;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t bitValue = item.settings[0] & 0x0C;
              uint8_t newValue = bitValue | data.rowEditValue;
              if(item.settings[0] != newValue){
                item.settings[0] = newValue;
                return 1;
              }
            }
            return 0;
          default: return 0;
        }
        break;
      case 3:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Mode");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? ((item.settings[0]>>2) & 0x03) : data.rowEditValue;
              value = constrain(value, 0, 2);
              if(value == 0){
                strcpy(str, "Once");
              } else if(value == 1){
                strcpy(str, "Loop");
              }
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 1;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t bitValue = item.settings[0] & 0x03;
              uint8_t newValue = bitValue | (data.rowEditValue<<2);
              if(item.settings[0] != newValue){
                item.settings[0] = newValue;
                return 1;
              }
            }
            return 0;
          default: return 0;
        }
        break;
      case 4:
        return getEventField<sLen,eLen,tname>(item, "Event", 0, 2, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getTriggerOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Operator");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? (item.settings[0]&0x03) : data.rowEditValue;
              value = constrain(value, 0, 3);
              if(value == 0){
                strcpy(str, "Any (Ignore Data2 Value)");
              } else if(value == 1){
                strcpy(str, "== (Equal To)");
              } else if(value == 2){
                strcpy(str, ">= (More or Equal To)");
              } else if(value == 3){
                strcpy(str, "<= (Less or Equal To)");
              }
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 3;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            {
              uint8_t bitValue = bitRead(item.settings[0], 2);
              uint8_t newValue = data.rowEditValue;
              bitWrite(newValue, 2, bitValue);
              if(item.settings[0] != newValue){
                item.settings[0] = newValue;
                return 1;
              }
            }
            return 0;
          default: return 0;
        }
        break;
      case 2:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 2, "Ignore Port", valueType);
      case 3:
        return getEventField<sLen,eLen,tname>(item, "Input Event", 0, 2, valueType);
      case 4:
        return getEventField<sLen,eLen,tname>(item, "Output Event", 1, 2, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getMagicEncoderOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Ring Color");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              BMCTools::getMagicEncoderColorName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 6;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 2:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Ring Mode");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[1] : data.rowEditValue;
              BMCTools::getMagicEncoderModeName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 3;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[1] != data.rowEditValue){
              item.settings[1] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 3:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Button Trigger");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[2] : data.rowEditValue;
              BMCTools::getMagicEncoderTriggerName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 4;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[2] != data.rowEditValue){
              item.settings[2] = data.rowEditValue;
              return 1;
            }
            return 0;
          default: return 0;
        }
        break;
      case 4:
        return getEventField<sLen,eLen,tname>(item, "Pixel Event", 0, 2, valueType);
      case 5:
        return getEventField<sLen,eLen,tname>(item, "Encoder Event", 1, 2, valueType);
      case 6:
        return getEventField<sLen,eLen,tname>(item, "Button Event", 2, 2, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getIliOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Show Label");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              strcpy(str, data.yesNoLabels[value]);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 0;
          case BMC_OBE_DEVICE_OPT_MAX: return 1;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 2:
        return getEventField<sLen,eLen,tname>(item, 0, 0, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getPixelOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        switch(valueType){
          case BMC_OBE_DEVICE_OPT_LABEL:
            strcpy(str, "Color");
            return 0;
          case BMC_OBE_DEVICE_OPT_VALUE:
          case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
            {
              uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.settings[0] : data.rowEditValue;
              value = constrain(value, 1, 10);
              BMCTools::getPixelColorName(value, str);
              return value;
            }
            break;
          case BMC_OBE_DEVICE_OPT_MIN: return 1;
          case BMC_OBE_DEVICE_OPT_MAX: return 10;
          case BMC_OBE_DEVICE_OPT_CHANGED:
            if(item.settings[0] != data.rowEditValue){
              item.settings[0] = data.rowEditValue;
              return 1;
            }
            return 0;
          default:
            return 0;
        }
        break;
      case 2:
        return getEventField<sLen,eLen,tname>(item, 0, 0, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getRgbPixelOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
      case 2:
      case 3:
        return getEventField<sLen,eLen,tname>(item, optionId-1, 0, valueType);
      default:
        break;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getRelayOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 0, "Engage @ Startup", valueType);
      case 2:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 1, "Momentary", valueType);
      case 3:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 2, "Reverse State", valueType);
      case 4:
        return getEventField<sLen,eLen,tname>(item, 0, 0, valueType);
      default:
        break;
    }
    return 0;
  }

  



















  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getNameField(bmcStoreDevice<sLen, eLen, tname>& item, uint8_t valueType=0){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        strcpy(str, "Name");
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.name : data.rowEditValue;
          if(value==0){
            strcpy(str, "None");
          } else {
            sprintf(str, "#%u ", (value-1)+offset);
            char nameStr[33] = "";
            editor.getDeviceNameText(data.activeDevice.id, (value-1), nameStr);
            strcat(str, nameStr);
          }
          return value;
        }
        return 0;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return BMC_MAX_NAMES_LIBRARY-1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.name != data.rowEditValue){
          item.name = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  uint16_t getPageNameField(uint8_t valueType=0){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        strcpy(str, "Name");
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? store.pages[globals.page].name : data.rowEditValue;
          if(value==0){
            strcpy(str, "None");
          } else {
            sprintf(str, "Name # %u", (value-1)+offset);
            char nameStr[33] = "";
            editor.getDeviceNameText(data.activeDevice.id, (value-1), nameStr);
            strcat(str, nameStr);
          }
          return value;
        }
        return 0;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return BMC_MAX_NAMES_LIBRARY-1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(store.pages[globals.page].name != data.rowEditValue){
          store.pages[globals.page].name = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getPortsField(bmcStoreDevice<sLen, eLen, tname>& item, const char* t_str, uint16_t eventIndex, uint8_t valueType){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        strcpy(str, t_str);
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
          value = constrain(value, 0, 143);
          getPortName(value);
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return 143;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.events[eventIndex] != data.rowEditValue){
          item.events[eventIndex] = data.rowEditValue;
          return 1;
        }
        return 0;
      case BMC_OBE_DEVICE_CUSTOM_SCROLL_UP:
        // data.rowEditValue++;
        // if(data.rowEditValue > 143){
        //   data.rowEditValue = 0;
        // }
        setPortBit(true);
        getPortName(data.rowEditValue);
        return 1;
      case BMC_OBE_DEVICE_CUSTOM_SCROLL_DOWN:
        // data.rowEditValue--;
        // if(data.rowEditValue < 0){
        //   data.rowEditValue = 143;
        // }
        setPortBit(false);
        getPortName(data.rowEditValue);
        return 1;
      default:
        return 0;
    }
    return 0;
  }
  void setPortBit(bool direction){
    //uint8_t prevValue = data.rowEditValue;
    
    if(direction){
      data.rowEditValue++;
      if(data.rowEditValue > 143){
        data.rowEditValue = 0;
      }
    } else {
      data.rowEditValue--;
      if(data.rowEditValue < 0 || data.rowEditValue > 143){
        data.rowEditValue = 143;
      }
    }
    uint8_t value = data.rowEditValue;
    if(value > 1 && value < 128){
      if(direction){
        uint8_t handledBit = 1;
        #if !defined(BMC_MIDI_SERIAL_A_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif

        #if !defined(BMC_MIDI_SERIAL_B_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif

        #if !defined(BMC_MIDI_SERIAL_C_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif

        #if !defined(BMC_MIDI_SERIAL_D_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif

        #if !defined(BMC_USB_HOST_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif

        #if !defined(BMC_MIDI_BLE_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, ++handledBit, 1);
          }
        #else
          handledBit++;
        #endif
      } else {
        uint8_t handledBit = 6;

        #if !defined(BMC_MIDI_BLE_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif

        #if !defined(BMC_USB_HOST_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif

        #if !defined(BMC_MIDI_SERIAL_D_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif

        #if !defined(BMC_MIDI_SERIAL_C_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif

        #if !defined(BMC_MIDI_SERIAL_B_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif

        #if !defined(BMC_MIDI_SERIAL_A_ENABLED)
          if(bitRead(value, handledBit)){
            bitWrite(value, handledBit, 0);
            bitWrite(value, --handledBit, 1);
          }
        #else
          handledBit--;
        #endif
      }
    }
    data.rowEditValue = value;
  }
  void getPortName(uint8_t value){
    strcpy(str, "");
    if(value == 0){
      strcpy(str, "None");
    } else if(value < 127){
      if(bitRead(value, 0)){
        strcpy(str, " USB");
      }
      if(bitRead(value, 1)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "A");
      }
      if(bitRead(value, 2)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "B");
      }
      if(bitRead(value, 3)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "C");
      }
      if(bitRead(value, 4)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "D");
      }
      if(bitRead(value, 5)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "HOST");
      }
      if(bitRead(value, 6)){
        if(strlen(str)>0){
          strcat(str, "+");
        }
        strcat(str, "BLE");
      }
    } else {
      sprintf(str, "Port Preset # %u", (value & 0x0F)+1);
    }
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getRangeField(bmcStoreDevice<sLen, eLen, tname>& item, const char* t_str, uint16_t eventIndex, uint8_t append, uint16_t min, uint16_t max, uint8_t valueType){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        strcpy(str, t_str);
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
          value = constrain(value, min, max);
          sprintf(str, "%u", value+append);
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return min;
      case BMC_OBE_DEVICE_OPT_MAX: return max;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.events[eventIndex] != data.rowEditValue){
          item.events[eventIndex] = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getSongField(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    return getSongField<sLen, eLen, tname>(item, "", eventIndex, appendIndex, valueType);
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getSongField(bmcStoreDevice<sLen, eLen, tname>& item, const char* t_str, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        if(appendIndex==0){
          strcpy(str, "Song");
        } else if(appendIndex==1){
          sprintf(str, "Song # %u", eventIndex+offset);
        } else {
          strcpy(str, t_str);
        }
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
          if(value==0){
            strcpy(str, "None");
          } else {
            sprintf(str, "Song # %u", (value-1)+offset);
          }
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return BMC_MAX_SETLISTS_SONGS_LIBRARY-1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.events[eventIndex] != data.rowEditValue){
          item.events[eventIndex] = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getPartField(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    return getPartField<sLen, eLen, tname>(item, "", eventIndex, appendIndex, valueType);
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getPartField(bmcStoreDevice<sLen, eLen, tname>& item, const char* t_str, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        if(appendIndex==0){
          strcpy(str, "Part");
        } else if(appendIndex==1){
          sprintf(str, "Part # %u", eventIndex+offset);
        } else {
          strcpy(str, t_str);
        }
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
          if(value==0){
            strcpy(str, "None");
          } else {
            sprintf(str, "Part # %u", (value-1)+offset);
          }
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return BMC_MAX_SETLISTS_SONG_PARTS-1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.events[eventIndex] != data.rowEditValue){
          item.events[eventIndex] = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getEventField(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    return getEventField<sLen, eLen, tname>(item, "", eventIndex, appendIndex, valueType);
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getEventField(bmcStoreDevice<sLen, eLen, tname>& item, const char* t_str, uint16_t eventIndex, uint8_t appendIndex, uint8_t valueType){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        if(appendIndex==0){
          strcpy(str, "Event");
        } else if(appendIndex==1){
          sprintf(str, "Event # %u", eventIndex+offset);
        } else {
          strcpy(str, t_str);
        }
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
          if(value==0){
            strcpy(str, "None");
          } else {
            sprintf(str, "Event # %u", (value-1)+offset);
          }
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return BMC_MAX_EVENTS_LIBRARY-1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(item.events[eventIndex] != data.rowEditValue){
          item.events[eventIndex] = data.rowEditValue;
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    return 0;
  }
  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  uint16_t getSettingsBitField(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t settingsIndex, uint8_t bitIndex, const char* label, uint8_t valueType=0){
    switch(valueType){
      case BMC_OBE_DEVICE_OPT_LABEL:
        strcpy(str, label);
        return 0;
      case BMC_OBE_DEVICE_OPT_VALUE:
      case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
        {
          uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? bitRead(item.settings[settingsIndex], bitIndex) : data.rowEditValue;
          strcpy(str, data.yesNoLabels[value]);
          return value;
        }
        break;
      case BMC_OBE_DEVICE_OPT_MIN: return 0;
      case BMC_OBE_DEVICE_OPT_MAX: return 1;
      case BMC_OBE_DEVICE_OPT_CHANGED:
        if(bitRead(item.settings[settingsIndex], bitIndex) != data.rowEditValue){
          bitWrite(item.settings[settingsIndex], bitIndex, data.rowEditValue);
          return 1;
        }
        return 0;
      default:
        return 0;
    }
    // switch(valueType){
    //   case BMC_OBE_DEVICE_OPT_LABEL:
    //     if(indexed){
    //       sprintf(str, "Event # %u", (eventIndex-1)+offset);
    //     } else {
    //       strcpy(str, "Event");
    //     }
    //     return 0;
    //   case BMC_OBE_DEVICE_OPT_VALUE:
    //   case BMC_OBE_DEVICE_OPT_EDITED_VALUE:
    //     {
    //       uint8_t value = (valueType==BMC_OBE_DEVICE_OPT_VALUE) ? item.events[eventIndex] : data.rowEditValue;
    //       if(value==0){
    //         strcpy(str, "None");
    //       } else {
    //         sprintf(str, "Event # %u", (value-1)+offset);
    //       }
    //       return value;
    //     }
    //     break;
    //   case BMC_OBE_DEVICE_OPT_MIN:
    //     return 0;
    //   case BMC_OBE_DEVICE_OPT_MAX:
    //     return BMC_MAX_EVENTS_LIBRARY-1;
    //   case BMC_OBE_DEVICE_OPT_CHANGED:
    //     if(item.events[eventIndex] != data.rowEditValue){
    //       item.events[eventIndex] = data.rowEditValue;
    //       return 1;
    //     }
    //     return 0;
    //   default:
    //     return 0;
    // }
    return 0;
  }
  void activate(){
    active = true;
  }
  void deactivate(){
    active = true;
  }
  bool isActive(){
    return active;
  }
  char str[65];
private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  BMCOBEData& data;
  BMCTimer charBlinker;
  char nameBuff[BMC_MAX_NAMES_LENGTH];
  int8_t charIndex = 0;
  uint8_t charValue = 0;
  bool charIndexState = false;
  bool charEditActive = false;
  uint8_t charPage = 0;
  uint8_t charPerPage = 0;
  uint8_t offset = 0;
  bool active = false;
  bool shiftActive = false;
};
#endif
#endif