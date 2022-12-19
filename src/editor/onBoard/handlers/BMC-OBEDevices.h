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
  bool isCompatible(uint8_t t_id=255){
    uint8_t id = (t_id==255) ? data.activeDevice.id : t_id;
    switch(id){
      case BMC_DEVICE_ID_EVENT:
      //case BMC_DEVICE_ID_NAME:
      case BMC_DEVICE_ID_POT_CALIBRATION:
      case BMC_DEVICE_ID_SKETCH_BYTE:
      case BMC_DEVICE_ID_SHORTCUTS:
        return false;
    }
    return true;
  }
  void setTotalRows(){
    switch(data.activeDevice.id){
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
      case BMC_DEVICE_ID_NL_RELAY:
      case BMC_DEVICE_ID_L_RELAY:
        data.totalRows = 5;
        break;
      case BMC_DEVICE_ID_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
      case BMC_DEVICE_ID_OLED:
      case BMC_DEVICE_ID_ILI:
        // for all devices that only have a name and single event
        data.totalRows = 2;// one for name and one for event
        break;
      case BMC_DEVICE_ID_LFO:
        data.totalRows = 1;
        data.totalRows += data.activeDevice.settings;
        data.totalRows += data.activeDevice.events;
        break;
    }
  }
  bool addRows(uint8_t startingPage){
    if(data.activeDevice.length == 0){
      return true;
    }
    switch(data.activeDevice.id){
      case BMC_DEVICE_ID_NAME:
      case BMC_DEVICE_ID_BUTTON:
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
      case BMC_DEVICE_ID_LED:
      case BMC_DEVICE_ID_GLOBAL_LED:
      case BMC_DEVICE_ID_PIXEL:
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
      case BMC_DEVICE_ID_PIXEL_STRIP:
      case BMC_DEVICE_ID_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
      case BMC_DEVICE_ID_OLED:
      case BMC_DEVICE_ID_ILI:
      case BMC_DEVICE_ID_NL_RELAY:
      case BMC_DEVICE_ID_L_RELAY:
      case BMC_DEVICE_ID_MAGIC_ENCODER:
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
      case BMC_DEVICE_ID_LFO:
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
  uint16_t getOptionLabel(uint16_t index, uint8_t valueType=BMC_OBE_DEVICE_OPT_LABEL){
    offset = settings.getDisplayOffset()?0:1;
    uint16_t dIndex = data.deviceIndex-1;
    switch(data.activeDevice.id){
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
          return getSingleEventDeviceOption<1,1>(store.pages[globals.page].ili[dIndex], index, valueType);
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
        break;
    }
    strcpy(str, "undefined");
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
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 5, "No Hold When Continuous", valueType);
        break;
      case 1:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 6, "No Release on Dbl Press", valueType);
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
              sprintf(str, "Btn Event # %u Mode", e+offset);
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
    // BMC_PRINTLN("getLfoOption optionId:", optionId, "index:", index);
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
  uint16_t getRelayOption(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, uint8_t valueType=0){
    strcpy(str,"");
    uint16_t optionId = data.visibleRowId[index]-1;
    switch(optionId){
      case 0:
        return getNameField<sLen,eLen,tname>(item, valueType);
      case 1:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 0, "SET at Startup", valueType);
        break;
      case 2:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 1, "Momentary", valueType);
      case 3:
        return getSettingsBitField<sLen,eLen,tname>(item, 0, 2, "Reverse State", valueType);
        break;
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
            sprintf(str, "Name # %u", (value-1)+offset);
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
          sprintf(str, "Event # %u", (eventIndex-1)+offset);
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