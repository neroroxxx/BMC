/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_MAIN_H
#define BMC_OBE_MAIN_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "display/BMC-Display.h"
#include "editor/onBoard/BMC-OBEDef.h"
#include "editor/onBoard/BMC-OBESettings.h"
#include "editor/onBoard/BMC-OBENames.h"

#define BMC_OBE_IS_SHIFT 0

class BMCOBE {
public:
  BMCOBE(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft),
                  settingsEditor(t_globals, settings, editor, display),
                  namesEditor(t_globals, settings, editor, display){

  }
  void begin(){
    settingsEditor.begin();
    namesEditor.begin();
  }
  void update(){
    if(!globals.onBoardEditorActive()){
      return;
    }
    settingsEditor.update();
    if(settingsEditor.confirmSave()){
      resetIndex();
      renderConfirmSave();
    } else if(settingsEditor.switchToPage()){
      resetIndex();
      renderEditorLevel(settingsEditor.getTargetPage());
    } else if(settingsEditor.renderLevel()){
      resetIndex();
      renderEditorLevel(level);
    }
    namesEditor.update();
    if(namesEditor.confirmSave()){
      resetIndex();
      renderConfirmSave();
    } else if(namesEditor.switchToPage()){
      resetIndex();
      renderEditorLevel(namesEditor.getTargetPage());
    }
  }
  void resetIndex(){
    listIndex = 0;
    listIndexPage = 0;
  }
  void renderEditorLevel(uint16_t t_level){
    level = t_level;
    char title[20] = "";

    switch(level){
      case BMC_OBE_LEVEL_MAIN:
        strcpy(title, "BMC EDITOR");
        listLength = 5;
        listTotalPages = 1;
        break;
      case BMC_OBE_LEVEL_SETTINGS:
        settingsEditor.getHeaderTitle(title);
        listLength = settingsEditor.getListLength();
        break;
      case BMC_OBE_LEVEL_EVENTS:
        strcpy(title, "EVENTS");
        listLength = namesEditor.getListLength();
        break;
      case BMC_OBE_LEVEL_NAMES:
        strcpy(title, "NAMES");
        listLength = BMC_MAX_NAMES_LIBRARY;
        break;
      case BMC_OBE_LEVEL_DEVICES:
        strcpy(title, "DEVICES");
        listLength = editor.devicesDataLength;
        break;
      case BMC_OBE_LEVEL_PAGES:
        strcpy(title, "CHANGE PAGE");
        listLength = BMC_MAX_PAGES;
        break;
      case BMC_OBE_LEVEL_NAMES_EDITOR:
        // this editor is different than all others because it has
        // the text editor
        listLength = 1;
        listTotalPages = 1;
        renderHeader("Names Editor");
        namesEditor.render(listIndex);
        return;
        break;
    }
    listTotalPages = ceil(listLength/8.0);
    if(listTotalPages==0){
      listTotalPages = 1;
    }
    renderHeader(title);
    // set color for menu options
    tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
    tft.display.setTextSize(BMC_OBE_LIST_TXT_SIZE);    
    uint16_t y = BMC_OBE_LIST_HEAD_H;
    
    uint8_t valueOffset = settings.getDisplayOffset()?0:1;
    bool highlight = false;
    for(uint16_t i = (listIndexPage*8), e = 0 ; e < 8 ; i++, e++){
      if(e>0){
        y += BMC_OBE_LIST_H;
      }
      if(highlight){
        highlight = false;
        tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
      }
      // black out the entire row
      tft.display.fillRect(0, y, 320, BMC_OBE_LIST_H, BMC_ILI9341_BLACK);
      //add a little block to note which row has been selected
      if(listIndex == i){
        drawSelChar(y+BMC_OBE_LIST_TXT_Y, true);
      }
      if(i >= listLength){
        continue;
      }
      tft.display.drawFastHLine(0, y, 320, BMC_COLOR_EDITOR_GRAY);
      tft.display.setCursor(16, y+BMC_OBE_LIST_TXT_Y);

      char strBuffer[33] = "";
      if(listLength > 99){
        sprintf(strBuffer, "%03u", i + valueOffset);
      } else if(listLength > 9){
        sprintf(strBuffer, "%02u", i + valueOffset);
      } else {
        sprintf(strBuffer, "%u", i + valueOffset);
      }

      if(level==BMC_OBE_LEVEL_SETTINGS){
        highlight = settingsEditor.getLabel(i, strBuffer);
      } else if(level==BMC_OBE_LEVEL_NAMES){
        highlight = namesEditor.getLabel(i, strBuffer);
      } else {
        highlight = getLabel(i, strBuffer);
      }
      if(highlight){
        tft.display.setTextColor(BMC_ILI9341_YELLOW);
      }
      tft.display.print(strBuffer);
    }
  }
  void renderConfirmSave(){
    waitingForSaveConfirmation = true;
    listTotalPages = 1;
    listLength = 2;
    renderHeader("Save Changes?");
    // set color for menu options
    tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
    tft.display.setTextSize(BMC_OBE_LIST_TXT_SIZE);    
    uint16_t y = BMC_OBE_LIST_HEAD_H;
    for(uint16_t i = (listIndexPage*8), e = 0 ; e < 8 ; i++, e++){
      //BMC_PRINTLN("listIndexPage", listIndexPage, e, i);
      if(e>0){
        y += BMC_OBE_LIST_H;
      }
      // black out the entire row
      tft.display.fillRect(0, y, 320, BMC_OBE_LIST_H, BMC_ILI9341_BLACK);
      //add a little block to note which row has been selected
      if(listIndex == i){
        //tft.display.setTextColor(BMC_ILI9341_ORANGE);
        //tft.display.setCursor(1, y+BMC_OBE_LIST_TXT_Y);
        //tft.display.print(">");
        //tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
        drawSelChar(y+BMC_OBE_LIST_TXT_Y, true);
      }
      if(i >= listLength){
        continue;
      }
      tft.display.drawFastHLine(0, y, 320, BMC_COLOR_EDITOR_GRAY);
      tft.display.setCursor(16, y+BMC_OBE_LIST_TXT_Y);
      if(e==0){
        tft.display.print("No");
      } else {
        tft.display.print("Yes");
      }
    }
  }
  void renderHeader(const char* title){
    tft.display.fillRect(0, 0, 320, BMC_OBE_LIST_HEAD_H, BMC_ILI9341_ORANGE);
    tft.display.setTextSize(BMC_OBE_LIST_HEAD_TXT_SIZE);
    uint16_t x = (320-((strlen(title)*BMC_OBE_LIST_HEAD_CHAR_WIDTH)-BMC_OBE_LIST_HEAD_TXT_SIZE))/2;
    tft.display.setCursor(x, BMC_OBE_LIST_HEAD_TXT_Y);
    tft.display.setTextColor(BMC_ILI9341_BLACK);
    tft.display.print(title);
    tft.display.setTextSize(BMC_OBE_LIST_TXT_SIZE);
  }
  bool getLabel(uint16_t index, char * str){
    switch(level){
      case BMC_OBE_LEVEL_MAIN:
        if(index < 5){
          strcpy(str, mainMenuList[index]);
        }
        break;
      case BMC_OBE_LEVEL_SETTINGS:
        sprintf(str, "%s", str);
        break;
      case BMC_OBE_LEVEL_EVENTS:
        sprintf(str, "%s", str);
        break;
      case BMC_OBE_LEVEL_NAMES:
        if(index < BMC_MAX_NAMES_LIBRARY){
          sprintf(str, "%s-%s", str, store.global.names[index].name);
        }
        break;
      case BMC_OBE_LEVEL_DEVICES:
        if(index < editor.devicesDataLength){
          sprintf(str, "%s", editor.devicesData[index].label);
        } else {
          strcpy(str, "Unknown");
        }
        break;
      case BMC_OBE_LEVEL_PAGES:
        char str2[5] = "";
        strcpy(str2, str);
        sprintf(str, "Page # %s", str2);
        return (globals.page==index);
    }
    return false;
  }
  void updateListIndex(){
    uint16_t y = BMC_OBE_LIST_HEAD_H;
    for(uint16_t i=(listIndexPage*8), e=0;i<listLength;i++, e++){
      if(e > 0){
        y += BMC_OBE_LIST_H;
      }
      drawSelChar(y+BMC_OBE_LIST_TXT_Y, listIndex == i);
    }
  }
  void drawSelChar(uint16_t y, bool on){
    uint16_t color = on ? BMC_ILI9341_ORANGE : BMC_ILI9341_BLACK;
    tft.display.drawChar(1, y, BMC_OBE_SEL_CHAR, color, 0, BMC_OBE_LIST_TXT_SIZE);
  }
  void menuCommandToggle(){
    if(globals.editorConnected() || waitingForSaveConfirmation){
      return;
    }
    globals.toggleOnBoardEditor();
    if(globals.onBoardEditorActive()){
      enterEditor();
    } else {
      exitEditor();
    }
  }
  void menuCommandSelect(){
    if(!globals.onBoardEditorActive()){
      menuCommand(BMC_MENU_TOGGLE);
      return;
    }
    if(inShift() && level != BMC_OBE_LEVEL_NAMES_EDITOR){
      menuCommand(BMC_MENU_BACK);
      return;
    }
    if(level == BMC_OBE_LEVEL_MAIN){
      level = listIndex+1;
      resetIndex();
      renderEditorLevel(level);

    } else if(level==BMC_OBE_LEVEL_PAGES){
      if(listIndex < BMC_MAX_PAGES && BMC_MAX_PAGES>1){
        if(listIndex != globals.page){
          globals.page = listIndex;
          exitEditor();
          globals.setReloadPage(true);
        }
      }
    } else if(level == BMC_OBE_LEVEL_NAMES){

      renderEditorLevel(BMC_OBE_LEVEL_NAMES_EDITOR);

    } else if(level == BMC_OBE_LEVEL_NAMES_EDITOR){

      namesEditor.select(listIndex, waitingForSaveConfirmation);

    } else if(level == BMC_OBE_LEVEL_SETTINGS){
      
      settingsEditor.select(listIndex, waitingForSaveConfirmation);
    }
    waitingForSaveConfirmation = false;
  }
  void menuCommandBack(){
    if(!globals.onBoardEditorActive() || waitingForSaveConfirmation){
      return;
    }
    if(level == BMC_OBE_LEVEL_MAIN){

      exitEditor();

    } else if(level == BMC_OBE_LEVEL_NAMES_EDITOR){

      namesEditor.back();

    } else if(level == BMC_OBE_LEVEL_SETTINGS){

      settingsEditor.back();

    } else {
      resetIndex();
      renderEditorLevel(BMC_OBE_LEVEL_MAIN);
    }
  }
  void menuCommandUp(){
    if(!globals.onBoardEditorActive()){
      return;
    }
    if(waitingForSaveConfirmation){
      cursorUp();
      return;
    }
    if(level == BMC_OBE_LEVEL_NAMES_EDITOR){
      namesEditor.cursorUp();
    } else {
      cursorUp();
    }
  }
  void menuCommandDown(){
    if(!globals.onBoardEditorActive()){
      return;
    }
    if(waitingForSaveConfirmation){
      cursorDown();
      return;
    }
    if(level == BMC_OBE_LEVEL_NAMES_EDITOR){
      namesEditor.cursorDown();
    } else {
      cursorDown();
    }
  }
  void menuCommandShift(){
    if(!globals.onBoardEditorActive()){
      return;
    }
    if(waitingForSaveConfirmation){
      return;
    }
    if(level == BMC_OBE_LEVEL_NAMES_EDITOR){
      namesEditor.cursorShift();
    } else {
      flags.toggle(BMC_OBE_IS_SHIFT);
    }
  }
  void menuCommand(uint8_t cmd){
    switch(cmd){
      case BMC_MENU_TOGGLE:
        menuCommandToggle();
        break;
      case BMC_MENU_SELECT:
        menuCommandSelect();
        break;
      case BMC_MENU_BACK:
        menuCommandBack();
        break;
      case BMC_MENU_UP:
        menuCommandUp();
        break;
      case BMC_MENU_DOWN:
        menuCommandDown();
        break;
      case BMC_MENU_SHIFT:
        menuCommandShift();
        break;
      default:
        break;
    }
  }
  void cursorUp(){
    if(inShift()){
      if(listTotalPages>1){
        listIndexPage--;
        if(listIndexPage < 0){
          listIndexPage = listTotalPages-1;
        }
        listIndex = (listIndexPage*8);
        renderEditorLevel(level);
        return;
      }
    }
    listIndex--;
    if(listIndex < 0){
      listIndex = listLength-1;
      if(listTotalPages>1){
        listIndexPage = listTotalPages-1;
        renderEditorLevel(level);
      } else {
        updateListIndex();
      }
    } else {
      if(listIndex < (listIndexPage*8)){
        if(listIndexPage>0){
          listIndexPage--;
          renderEditorLevel(level);
          return;
        }
      }
      updateListIndex();
    }
  }
  void cursorDown(){
    if(inShift()){
      if(listTotalPages>1){
        listIndexPage++;
        if(listIndexPage >= listTotalPages){
          listIndexPage = 0;
        }
        listIndex = (listIndexPage*8);
        renderEditorLevel(level);
        return;
      }
    }
    listIndex++;
    if(listIndex >= listLength){
      resetIndex();
      if(listTotalPages>1){
        renderEditorLevel(level);
      } else {
        updateListIndex();
      }
    } else {
      if(listIndex >= ((listIndexPage+1)*8)){
        if(listIndexPage < listTotalPages){
          listIndexPage++;
          renderEditorLevel(level);
          return;
        }
      }
      updateListIndex();
    }
  }
  bool inShift(){
    return flags.toggleIfTrue(BMC_OBE_IS_SHIFT);
  }

private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  BMCOBESettings settingsEditor;
  BMCOBENames namesEditor;
  BMCFlags <uint8_t> flags;
  int16_t level = 0;
  uint16_t selectedId = 0;
  uint16_t listLength = 0;
  int16_t listIndex = 0;
  int16_t listIndexPage = 0;
  int16_t listTotalPages = 0;
  uint8_t activeDeviceId = 0;
  uint16_t activeDeviceIndex = 0;
  bool waitingForSaveConfirmation = false;
  const char mainMenuList[5][19] = {
    "Settings",
    "Events",
    "Names",
    "Devices",
    "Change Page"
  };
  void reset(){
    flags.reset();
    level = 0;
    listLength = 0;
    listIndex = 0;
    listIndexPage = 0;
    listTotalPages = 0;
    activeDeviceId = 0;
    activeDeviceIndex = 0;
    waitingForSaveConfirmation = false;
  }
  void enterEditor(){
    tft.display.fillRect(0, 0, 320, 240, BMC_ILI9341_BLACK);
    renderEditorLevel(0);
  }
  void exitEditor(){
    settingsEditor.shutDown();
    namesEditor.shutDown();
    globals.setOnBoardEditorActive(false);
    reset();
    tft.display.fillRect(0, 0, 320, 240, BMC_ILI9341_BLACK);
    display.reassign(globals.page);
  }
};
#endif
#endif