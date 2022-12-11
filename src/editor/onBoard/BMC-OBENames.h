/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_NAMES_H
#define BMC_OBE_NAMES_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "display/BMC-Display.h"
#include "editor/onBoard/BMC-OBEDef.h"
#include "editor/onBoard/BMC-OBEMain.h"

#define BMC_OBE_NAMES_BLINK_TIME 400

#define BMC_OBE_NAMES_FLAG_HAS_CHANGED      0
#define BMC_OBE_NAMES_FLAG_CONFIRM_SAVE     1
#define BMC_OBE_NAMES_FLAG_EXIT             2
#define BMC_OBE_NAMES_FLAG_SHIFT            3
#define BMC_OBE_NAMES_FLAG_BLINK_STATE      4

class BMCOBENames {
public:
  BMCOBENames(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft){
    reset();
  }
  void begin(){
    reset();
  }
  void update(){
    if(timer.complete()){
      tft.display.setCursor(activeCharX, activeCharY);
      flags.toggle(BMC_OBE_NAMES_FLAG_BLINK_STATE);
      if(flags.read(BMC_OBE_NAMES_FLAG_BLINK_STATE)){
        tft.display.setTextColor(BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
      } else {
        tft.display.setTextColor(BMC_ILI9341_DARKGREY, BMC_ILI9341_WHITE);
      }
      tft.display.print(tmpName[charIndex]);
      timer.start(BMC_OBE_NAMES_BLINK_TIME);
    }
  }
  bool render(uint16_t t_activeDeviceIndex){
    if(t_activeDeviceIndex>=BMC_MAX_NAMES_LENGTH){
      return false;
    }
    timer.start(BMC_OBE_NAMES_BLINK_TIME);
    if(asciiValue < 32 || asciiValue > 126){
      asciiValue = 32;
    }
    charIndex = 0;
    uint8_t fontSize = 3;
    uint8_t fontWidth = (6*fontSize);
    uint8_t fontHeight = (8*fontSize);
    charX = ((320 - (fontWidth*16))/2);
    charY = BMC_OBE_LIST_HEAD_H*2;
    memset(tmpName, 0, 33);
    activeDeviceIndex = t_activeDeviceIndex;
    bool zeroOut = false;
    for(uint8_t i=0;i<BMC_MAX_NAMES_LENGTH;i++){
      char t = store.global.names[activeDeviceIndex].name[i];
      if(zeroOut || t<32 || t>126){
        tmpName[i] = 0;
        zeroOut = true;
      } else {
        tmpName[i] = t;
      }
    }
    tft.display.setTextSize(fontSize);
    tft.display.fillRect(0, BMC_OBE_LIST_HEAD_H, 320, 240-BMC_OBE_LIST_HEAD_H, BMC_ILI9341_BLACK);
    for(uint8_t e = 0 ; e < BMC_MAX_NAMES_LENGTH ; e++){
      if(e < 16){
        tft.display.setCursor(charX+(fontWidth*e), charY);
        if(charIndex==e){
          activeCharX = charX+(fontWidth*e);
          activeCharY = charY;
        }
      } else {
        tft.display.setCursor(charX+(fontWidth*(e-16)), (charY+fontHeight+(fontSize*2)));
        if(charIndex==e){
          activeCharX = charX+(fontWidth*(e-16));
          activeCharY = (charY+fontHeight+(fontSize*2));
        }
      }
      if(charIndex==e){
        if(tmpName[e]==32){
          tft.display.setTextColor(BMC_ILI9341_DARKGREY, BMC_ILI9341_DARKGREY);
        } else {
          tft.display.setTextColor(BMC_ILI9341_DARKGREY, BMC_ILI9341_WHITE);
        }
      } else {
        tft.display.setTextColor(BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
      }
      if((uint8_t)tmpName[e] >= 32 && (uint8_t)tmpName[e] <= 126){
        tft.display.print(tmpName[e]);
      } else if((uint8_t)tmpName[e]==0) {
        break;
      }
    }
    flags.on(BMC_OBE_NAMES_FLAG_BLINK_STATE);
    timer.start(BMC_OBE_NAMES_BLINK_TIME);
    return true;
  }
  void updateCharIndex(){
    tmpName[charIndex] = asciiValue;
    uint8_t fontSize = 3;
    uint8_t fontWidth = (6*fontSize);
    uint8_t fontHeight = (8*fontSize);
    charX = ((320 - (fontWidth*16))/2);
    charY = BMC_OBE_LIST_HEAD_H*2;
    tft.display.setTextSize(fontSize);
    for(uint8_t e = 0 ; e < BMC_MAX_NAMES_LENGTH ; e++){
      if(e < 16){
        tft.display.setCursor(charX+(fontWidth*e), charY);
        if(charIndex==e){
          activeCharX = charX+(fontWidth*e);
          activeCharY = charY;
        }
      } else {
        tft.display.setCursor(charX+(fontWidth*(e-16)), (charY+fontHeight+(fontSize*2)));
        if(charIndex==e){
          activeCharX = charX+(fontWidth*(e-16));
          activeCharY = (charY+fontHeight+(fontSize*2));
        }
      }
      if(charIndex==e){
        tft.display.setTextColor(BMC_ILI9341_DARKGREY, BMC_ILI9341_WHITE);
      } else {
        tft.display.setTextColor(BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
      }
      if((uint8_t)tmpName[e] >= 32 && (uint8_t)tmpName[e] <= 126){
        tft.display.print(tmpName[e]);
      } else if((uint8_t)tmpName[e]==0) {
        break;
      }
    }
    flags.on(BMC_OBE_NAMES_FLAG_BLINK_STATE);
    timer.start(BMC_OBE_NAMES_BLINK_TIME);
  }
  uint16_t getListLength(){
    return BMC_MAX_NAMES_LIBRARY;
  }
  bool getLabel(uint16_t index, char * str){
    if(index < BMC_MAX_NAMES_LIBRARY){
      sprintf(str, "%s-%s", str, store.global.names[index].name);
    }
    return false;
  }
  void shutDown(){
    reset();
  }
  void save(){
    timer.stop();
    String str = String(tmpName);
    str.trim();
    str.toCharArray(tmpName, 33);
    bool zeroOut = false;
    for(uint8_t i = 0; i < 33 ; i++){
      if(zeroOut || (uint8_t)tmpName[i] < 32 || (uint8_t)tmpName[i] > 126){
        tmpName[i] = 0;
        zeroOut = true;
      }
    }
    BMC_PRINTLN("SAVED");
    strcpy(store.global.names[activeDeviceIndex].name, tmpName);
    editor.saveName(activeDeviceIndex);
  }
  void select(uint16_t t_index, bool t_confirm){
    if(t_confirm){
      if(t_index==1){
        save();
      }
      flags.on(BMC_OBE_NAMES_FLAG_EXIT);
      return;
    }
    tmpName[charIndex] = getCharValue();
    if(inShift()){
      charIndex--;
      if(charIndex < 0){
        charIndex = BMC_MAX_NAMES_LENGTH-1;
      }
    } else {
      charIndex++;
      if(charIndex >= BMC_MAX_NAMES_LENGTH){
        charIndex = 0;
      }
    }
    asciiValue = getCharValue();
    updateCharIndex();
  }
  void back(){
    if(flags.toggleIfTrue(BMC_OBE_NAMES_FLAG_HAS_CHANGED)){
      timer.stop();
      flags.on(BMC_OBE_NAMES_FLAG_CONFIRM_SAVE);
    } else {
      flags.on(BMC_OBE_NAMES_FLAG_EXIT);
    }
  }
  bool exitMenu(){
    timer.stop();
    String str = String(tmpName);
    str.trim();
    str.toCharArray(tmpName, 33);
    bool zeroOut = false;
    for(uint8_t i = 0; i < 33 ; i++){
      if(zeroOut || (uint8_t)tmpName[i] < 32 || (uint8_t)tmpName[i] > 126){
        tmpName[i] = 0;
        zeroOut = true;
      }
    }
    BMC_PRINTLN("tmpName", tmpName);
    if(confirmSave()){
      return false;
    }
    BMC_PRINTLN("EXIT NAMES EDITOR");
    reset();
    return true;
  }
  void cursorDown(){
    asciiValue = getCharValue();
    asciiValue--;
    if(asciiValue < 32){
      asciiValue = 126;
    }
    if(inShift()){
      if(asciiValue > 97){
        asciiValue = 97;
      } else if(asciiValue > 65){
        asciiValue = 65;
      } else if(asciiValue > 48){
        asciiValue = 48;
      } else if(asciiValue > 32){
        asciiValue = 32;
      } else {
        asciiValue = 97;
      }
    }
    flags.on(BMC_OBE_NAMES_FLAG_HAS_CHANGED);
    updateCharIndex();
  }
  void cursorUp(){
    asciiValue = getCharValue();
    asciiValue++;
    if(asciiValue > 126){
      asciiValue = 32;
    }
    if(inShift()){
      if(asciiValue<48){
        asciiValue = 48;
      } else if(asciiValue<65){
        asciiValue = 65;
      } else if(asciiValue<97){
        asciiValue = 97;
      } else {
        asciiValue = 32;
      }
    }
    flags.on(BMC_OBE_NAMES_FLAG_HAS_CHANGED);
    updateCharIndex();
  }
  void cursorShift(){
    flags.toggle(BMC_OBE_NAMES_FLAG_SHIFT);
  }
  bool inShift(){
    return flags.toggleIfTrue(BMC_OBE_NAMES_FLAG_SHIFT);
  }
  uint8_t getCharValue(){
    uint8_t c = (uint8_t) tmpName[charIndex];
    if(c<32 || c>126){
      c = 32;
    }
    return c;
  }
  bool confirmSave(){
    return flags.toggleIfTrue(BMC_OBE_NAMES_FLAG_CONFIRM_SAVE);
  }
  bool switchToPage(){
    if(flags.toggleIfTrue(BMC_OBE_NAMES_FLAG_EXIT)){
      reset();
      return true;
    }
    return false;
  }
  uint16_t getTargetPage(){
    return BMC_OBE_LEVEL_NAMES;
  }
private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  BMCTimer timer;
  BMCFlags <uint8_t> flags;
  char tmpName[33] = "";
  uint8_t asciiValue = 32;
  int16_t charIndex = 0;
  uint16_t activeDeviceIndex = 0;
  uint16_t charX = 0;
  uint8_t charY = 0;
  uint16_t activeCharX = 0;
  uint8_t activeCharY = 0;

  void reset(){
    memset(tmpName, 0, 33);
    charX = 0;
    charY = 0;
    asciiValue = 32;
    charIndex = 0;
    activeDeviceIndex = 0;
    flags.reset();
    timer.stop();
  }
};
#endif
#endif