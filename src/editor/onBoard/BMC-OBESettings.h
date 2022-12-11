/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_SETTINGS_H
#define BMC_OBE_SETTINGS_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "display/BMC-Display.h"
#include "editor/onBoard/BMC-OBEDef.h"
#include "editor/onBoard/BMC-OBEMain.h"

class BMCOBESettingsItem {
public:
  uint8_t id = 0;
  uint8_t level = 0;
  uint16_t length = 0;
  virtual bool getLength(){
    return false;
  }
  virtual bool valueChanged(){
    return false;
  }
  virtual void setValue(uint16_t t_value){

  }
  virtual void setValue(uint16_t t_value){

  }
  virtual void getOptionLabel(uint16_t t_value){

  }
  virtual void getHeaderLabel(uint16_t t_value){
    
  }
  virtual void getCategoryLabel(uint16_t t_value){
    
  }
};


/*
case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 16;
case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getButtonHoldThreshold();
case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setButtonHoldThreshold(activeValue);
                break;
case BMC_OBE_SETTINGS_TYPE_LABEL:
                sprintf(str, "%u ms", (id+2)*250);
                return (id == settings.getButtonHoldThreshold());
                break;
case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Button Hold Time");
                break;
case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
*/


#define BMC_OBE_SETTINGS_FLAG_HAS_CHANGED      0
#define BMC_OBE_SETTINGS_FLAG_CONFIRM_SAVE     1
#define BMC_OBE_SETTINGS_FLAG_EXIT             2
#define BMC_OBE_SETTINGS_FLAG_SHIFT            3
#define BMC_OBE_SETTINGS_FLAG_RENDER           4

#define BMC_OBE_SETTINGS_LEVEL_MAIN     0
#define BMC_OBE_SETTINGS_LEVEL_EDIT     1

#define BMC_OBE_SETTINGS_TYPE_LENGTH                 0
#define BMC_OBE_SETTINGS_TYPE_CHANGED                1
#define BMC_OBE_SETTINGS_TYPE_SET_VALUE              2
#define BMC_OBE_SETTINGS_TYPE_LABEL                  3
#define BMC_OBE_SETTINGS_TYPE_HEADER                 4
#define BMC_OBE_SETTINGS_TYPE_CATEGORY               5


#define BMC_OBE_SETTINGS_ID_GENERAL_BUTTON_HOLD                 0
#define BMC_OBE_SETTINGS_ID_GENERAL_STARTUP_PRESET              1
#define BMC_OBE_SETTINGS_ID_GENERAL_LED_DIM                     2
#define BMC_OBE_SETTINGS_ID_GENERAL_DISPLAY_OFFSET              3
#define BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG          4
#define BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG_PART     5

#define BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM             0
#define BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_CHANNEL     1
#define BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_ACTION      2
#define BMC_OBE_SETTINGS_ID_MIDI_CLOCK_INPUT_PORT       3
#define BMC_OBE_SETTINGS_ID_MIDI_MASTER_CLOCK           4
#define BMC_OBE_SETTINGS_ID_MIDI_ACTIVE_SENSE           5
#define BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_INPUT         6
#define BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_OUTPUT        7

#define BMC_OBE_SETTINGS_LENGTH                         14


class BMCOBESettings {
private:
  const char titlesList[BMC_OBE_SETTINGS_LENGTH][25] = {
    "Button Hold Time",
    "Startup Preset",
    "Dim Off LEDs",
    "Display Offset to 0",
    "Trigger 1st Song",
    "Trigger 1st Song Part",
    "MIDI Incoming Control",
    "MIDI In Ctrl Channel",
    "MIDI In Ctrl Action",
    "MIDI Clock Input Port",
    "MIDI Master Clock",
    "MIDI Active Sense",
    "MIDI Block RT In",
    "MIDI Block RT Out"
  };
  uint8_t availablePorts = 0;
  uint8_t availablePortsData[7];
    
public:
  BMCOBESettings(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft){
    reset();
  }
  void begin(){
    availablePortsData[availablePorts++] = BMC_MIDI_PORT_USB_BIT;
		#if defined(BMC_MIDI_SERIAL_A_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_A_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_B_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_B_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_C_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_C_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_D_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_D_BIT;
    #endif
		#if defined(BMC_USB_HOST_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_HOST_BIT;
    #endif
		#if defined(BMC_MIDI_BLE_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_BLE_BIT;
    #endif
    reset();
  }
  void update(){
    
  }
  uint16_t getListLength(){
    return listLength;
  }
  void prevLevel(){
    level--;
    if(level < 0){
      level = 0;
      return;
    }
    setLevelData();
    flags.on(BMC_OBE_SETTINGS_FLAG_RENDER);
  }
  void nextLevel(){
    level++;
    if(level >= maxLevels){
      level = maxLevels-1;
      return;
    }
    setLevelData();
    flags.on(BMC_OBE_SETTINGS_FLAG_RENDER);
  }
  void setLevelData(){
    listIndex = 0;
    listLength = getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_LENGTH);
    /*
    if(level == BMC_OBE_SETTINGS_LEVEL_MAIN){
      listIndex = 0;
      listLength = getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_LENGTH);
    } else if(level == BMC_OBE_SETTINGS_LEVEL_MAIN){
      listIndex = 0;
      listLength = BMC_OBE_SETTINGS_LENGTH;
    } else {
      //activeIndex = listIndex;
      listIndex = 0;
      listLength = getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_LENGTH);
    }
    */
    listTotalPages = ceil(listLength/8.0);
  }
  uint16_t getSettingData(uint16_t id, uint8_t type){
    char str[33] = "";
    return getSettingData(id, type, str);
  }
  uint16_t getSettingData(uint16_t id, uint8_t type, char* str){
    //BMC_PRINTLN("level", level, "levelId", levelId, "id", id, "activeIndex", activeIndex);
    if(level == 0){
      if(type == BMC_OBE_SETTINGS_TYPE_LENGTH){
        return 2;
      }
      switch(id){
        case 0:
          sprintf(str, "GENERAL");
          break;
        case 1:
          sprintf(str, "MIDI");
          break;
        case 2:
          sprintf(str, "ROUTING");
          break;
      }
      return 0; 
    } else if(level == 1){
      if(levelId==0){
        if(type==BMC_OBE_SETTINGS_TYPE_LENGTH){
          return 6;
        }
        switch(id){
          case BMC_OBE_SETTINGS_ID_GENERAL_BUTTON_HOLD:
            strcpy(str, "Button Hold Time");
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_STARTUP_PRESET:
            strcpy(str, "Startup Preset");
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_LED_DIM:
            strcpy(str, "Dim Off LEDs");
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_DISPLAY_OFFSET:
            strcpy(str, "Display Offset to 0");
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG:
            strcpy(str, "Trigger 1st Song");
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG_PART:
            strcpy(str, "Trigger 1st Song Part");
            break;
        }
      } else if(levelId==1){
        if(type==BMC_OBE_SETTINGS_TYPE_LENGTH){
          return 8;
        }
        switch(id){
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM:
            strcpy(str, "MIDI Incoming Control");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_CHANNEL:
            strcpy(str, "MIDI In Ctrl Channel");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_ACTION:
            strcpy(str, "MIDI In Ctrl Action");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_CLOCK_INPUT_PORT:
            strcpy(str, "MIDI Clock Input Port");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_MASTER_CLOCK:
            strcpy(str, "MIDI Master Clock");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_ACTIVE_SENSE:
            strcpy(str, "MIDI Active Sense");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_INPUT:
            strcpy(str, "MIDI Block RT In");
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_OUTPUT:
            strcpy(str, "MIDI Block RT Out");
            break;
        }
      } else if(levelId==2){
        if(type==BMC_OBE_SETTINGS_TYPE_LENGTH){
          return 0;
        }
      }
    } else if(level == 2){
      if(levelId==0){
        switch(activeIndex){
          case BMC_OBE_SETTINGS_ID_GENERAL_BUTTON_HOLD:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 16;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getButtonHoldThreshold();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setButtonHoldThreshold(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                sprintf(str, "%u ms", (id+2)*250);
                return (id == settings.getButtonHoldThreshold());
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Button Hold Time");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
            
          case BMC_OBE_SETTINGS_ID_GENERAL_STARTUP_PRESET:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return BMC_MAX_PRESETS;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getStartupPreset();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setStartupPreset(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                if(id==0){
                  strcpy(str, "None");
                } else {
                  BMCTools::getPresetLabel((id-1), str, store.global);
                }
                return (id == settings.getStartupPreset());
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                 strcpy(str, "Startup Preset");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_LED_DIM:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getPwmDimWhenOff();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setPwmDimWhenOff(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getPwmDimWhenOff(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Dim Off LEDs");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_DISPLAY_OFFSET:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getDisplayOffset();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setDisplayOffset(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getDisplayOffset(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Display Offset to 0");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getSetListTriggerFirstSong();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setSetListTriggerFirstSong(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getSetListTriggerFirstSong(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Trigger 1st Song");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_GENERAL_TRIGGER_FIRST_SONG_PART:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getSetListTriggerFirstSongPart();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setSetListTriggerFirstSongPart(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getSetListTriggerFirstSongPart(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "Trigger 1st Song Part");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "GENERAL");
                break;
            }
            break;
        }
      } else if(levelId==1){
        switch(activeIndex){
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getIncomingListenerEnabled();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setIncomingListenerEnabled(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getIncomingListenerEnabled(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Incoming Control");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_CHANNEL:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 17;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getListenerChannel();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setListenerChannel(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                if(id==0){
                  strcpy(str, "Omni");
                } else {
                  sprintf(str, "Channel %u", id);
                }
                return (id == settings.getListenerChannel());
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI In Ctrl Channel");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_IN_PROGRAM_ACTION:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 3;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getIncomingProgramType();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setIncomingProgramType(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                  switch(id){
                    case 0: strcpy(str, "Do Nothing"); break;
                    case 1: strcpy(str, "Change Page"); break;
                    case 2: strcpy(str, "Change Preset"); break;
                  }
                return (id == settings.getIncomingProgramType());
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI In Ctrl Action");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_CLOCK_INPUT_PORT:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return availablePorts;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getClockInputPortBit();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setClockInputPortBit(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                  switch(availablePortsData[id]){
                    case BMC_MIDI_PORT_USB_BIT: strcpy(str, "USB"); break;
                    case BMC_MIDI_PORT_SERIAL_A_BIT: strcpy(str, "Serial A"); break;
                    case BMC_MIDI_PORT_SERIAL_B_BIT: strcpy(str, "Serial B"); break;
                    case BMC_MIDI_PORT_SERIAL_C_BIT: strcpy(str, "Serial C"); break;
                    case BMC_MIDI_PORT_SERIAL_D_BIT: strcpy(str, "Serial D"); break;
                    case BMC_MIDI_PORT_HOST_BIT: strcpy(str, "USB Host"); break;
                    case BMC_MIDI_PORT_BLE_BIT: strcpy(str, "BLE"); break;
                  }
                return (id == settings.getClockInputPortBit());
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Clock Input Port");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_MASTER_CLOCK:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getMasterClock();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setMasterClock(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getMasterClock(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Master Clock");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_ACTIVE_SENSE:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getActiveSenseAtStartup();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setActiveSenseAtStartup(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getActiveSenseAtStartup(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Active Sense");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_INPUT:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getMidiRealTimeBlockInput();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setMidiRealTimeBlockInput(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getMidiRealTimeBlockInput(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Block RT In");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          case BMC_OBE_SETTINGS_ID_MIDI_BLOCK_RT_OUTPUT:
            switch(type){
              case BMC_OBE_SETTINGS_TYPE_LENGTH:
                return 2;
              case BMC_OBE_SETTINGS_TYPE_CHANGED:
                return activeValue != settings.getMidiRealTimeBlockOutput();
              case BMC_OBE_SETTINGS_TYPE_SET_VALUE:
                settings.setMidiRealTimeBlockOutput(activeValue);
                break;
              case BMC_OBE_SETTINGS_TYPE_LABEL:
                return getOnOffLabel(id, settings.getMidiRealTimeBlockOutput(), str);
                break;
              case BMC_OBE_SETTINGS_TYPE_HEADER:
                strcpy(str, "MIDI Block RT Out");
                break;
              case BMC_OBE_SETTINGS_TYPE_CATEGORY:
                strcpy(str, "MIDI");
                break;
            }
            break;
          default:
            break;
        }
      } else if(levelId==2){

      }
    }
    
    
    return 0;
  }
  
  bool dataHasChanged(){
    if(level == (maxLevels-1)){
      return getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_CHANGED)==0?false:true;
    }
    return false;
  }
  void save(){
    if(level == (maxLevels-1)){
      getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_SET_VALUE);
      editor.saveSettings();
      globals.setAssignStoreData(true);
    }
  }
  void getHeaderTitle(char * str){
    BMC_PRINTLN("level", level, "levelId", levelId, "activeIndex", activeIndex);
    if(level == BMC_OBE_SETTINGS_LEVEL_MAIN){
      strcpy(str, "SETTINGS");
    } else {
      level--;
      getSettingData(activeIndex, BMC_OBE_SETTINGS_TYPE_HEADER, str);
      level++;
    }
  }
  void getOptionLabel(uint16_t index, char * str){
    if(index < BMC_OBE_SETTINGS_LENGTH){
      strcpy(str, titlesList[index]);
    }
  }
  bool getLabel(uint16_t index, char * str){
    if(level == maxLevels-1){
      return getSettingData(index, BMC_OBE_SETTINGS_TYPE_LABEL, str);
    }
    getSettingData(index, BMC_OBE_SETTINGS_TYPE_LABEL, str);
    return false;
  }
  bool getOnOffLabel(uint16_t index, bool sel, char * str){
    strcpy(str, (index == 0)? "Off":"On");
    return (index == sel);
  }
  void updateListIndex(){
    uint16_t y = BMC_OBE_LIST_HEAD_H;
    tft.display.setTextSize(BMC_OBE_LIST_TXT_SIZE);
    for(uint16_t i=(listIndexPage*8), e=0;i<listLength;i++, e++){
      if(e > 0){
        y += BMC_OBE_LIST_H;
      }
      if(listIndex == i){
        tft.display.setTextColor(BMC_ILI9341_ORANGE);
      } else {
        tft.display.setTextColor(BMC_ILI9341_BLACK);
      }
      tft.display.setCursor(1, y+BMC_OBE_LIST_TXT_Y);
      tft.display.print(">");
    }
  }
  void shutDown(){
    reset();
  }
  
  void select(uint16_t t_index, bool t_confirm){
    if(t_confirm){
      if(t_index==1){
        save();
      }
      if(level==BMC_OBE_SETTINGS_LEVEL_MAIN){
        flags.on(BMC_OBE_SETTINGS_FLAG_EXIT);
      } else {
        //nextLevel();
        prevLevel();
      }
      return;
    }
    if(level==BMC_OBE_SETTINGS_LEVEL_MAIN){
      levelId = t_index;
      activeIndex = t_index;
      nextLevel();
    } else if(level==(maxLevels-1)){
      activeValue = t_index;
      if(dataHasChanged()){
        flags.on(BMC_OBE_SETTINGS_FLAG_HAS_CHANGED);
      } else {
        prevLevel();
      }
    } else {
      activeIndex = t_index;
      nextLevel();
    }
  }
  void back(){
    if(level==BMC_OBE_SETTINGS_LEVEL_MAIN){
      if(flags.toggleIfTrue(BMC_OBE_SETTINGS_FLAG_HAS_CHANGED)){
        flags.on(BMC_OBE_SETTINGS_FLAG_CONFIRM_SAVE);
      } else {
        flags.on(BMC_OBE_SETTINGS_FLAG_EXIT);
      }
    } else {
      //BMC_PRINTLN("BACK NEXT LEVEL", level);
      //nextLevel();
      prevLevel();
    }
  }
  bool confirmSave(){
    return flags.toggleIfTrue(BMC_OBE_SETTINGS_FLAG_HAS_CHANGED);
  }
  bool switchToPage(){
    if(flags.toggleIfTrue(BMC_OBE_SETTINGS_FLAG_EXIT)){
      if(level==BMC_OBE_SETTINGS_LEVEL_MAIN){
        // return to main menu
        reset();
      }
      return true;
    }
    return false;
  }
  uint16_t getTargetPage(){
    if(level != BMC_OBE_SETTINGS_LEVEL_MAIN){
      return BMC_OBE_LEVEL_SETTINGS;
    }
    return BMC_OBE_LEVEL_MAIN;
  }
  bool renderLevel(){
    return flags.toggleIfTrue(BMC_OBE_SETTINGS_FLAG_RENDER);
  }
private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  BMCFlags <uint8_t> flags;
  int8_t level = BMC_OBE_SETTINGS_LEVEL_MAIN;
  uint8_t levelId = 0;
  uint8_t maxLevels = 3;
  
  int16_t listTotalPages = 0;
  int16_t listIndex = 0;
  int16_t listIndexPage = 0;
  uint16_t listLength = 0;
  uint16_t activeIndex = BMC_OBE_SETTINGS_ID_GENERAL_BUTTON_HOLD;
  uint16_t activeValue = 0;

  

  void reset(){
    level = BMC_OBE_SETTINGS_LEVEL_MAIN;
    levelId = 0;
    maxLevels = 3;
    listTotalPages = 0;
    listIndex = 0;
    listIndexPage = 0;
    listLength = 0;
    activeIndex = BMC_OBE_SETTINGS_ID_GENERAL_BUTTON_HOLD;
    activeValue = 0;
    flags.reset();
    setLevelData();
  }

};
#endif
#endif