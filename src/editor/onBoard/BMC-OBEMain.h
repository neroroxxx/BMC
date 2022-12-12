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
      render(settingsEditor.getTargetPage());
    } else if(settingsEditor.renderLevel()){
      resetIndex();
      render(level);
    }
    namesEditor.update();
    if(namesEditor.confirmSave()){
      resetIndex();
      renderConfirmSave();
    } else if(namesEditor.switchToPage()){
      resetIndex();
      render(namesEditor.getTargetPage());
    }
  }
  void resetIndex(){
    listIndex = 0;
    listIndexPage = 0;
  }
  void render(uint16_t t_level){
    level = t_level;
    char title[20] = "";

    switch(level){
      case BMC_OBE_LEVEL_MAIN:
        strcpy(title, "BMC Editor");
        listLength = 5;
        listTotalPages = 1;
        break;
      case BMC_OBE_LEVEL_SETTINGS:
        settingsEditor.getHeaderTitle(title);
        listLength = settingsEditor.getListLength();
        break;
      case BMC_OBE_LEVEL_EVENTS:
        strcpy(title, "Events");
        listLength = namesEditor.getListLength();
        break;
      case BMC_OBE_LEVEL_NAMES:
        strcpy(title, "Names");
        listLength = BMC_MAX_NAMES_LIBRARY;
        break;
      case BMC_OBE_LEVEL_DEVICES:
        strcpy(title, "Devices");
        listLength = editor.devicesDataLength;
        break;
      case BMC_OBE_LEVEL_PAGES:
        strcpy(title, "Change Pages");
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
    listTotalPages = ceil(listLength/BMC_OBE_LIST_LENGTH);
    if(listTotalPages==0){
      listTotalPages = 1;
    }
    renderHeader(title);
    // set color for menu options
    tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
    tft.display.setTextSize(BMC_OBE_LIST_TXT_SIZE);    
    uint16_t y = BMC_OBE_LIST_HEAD_H+8;
    
    uint8_t valueOffset = settings.getDisplayOffset()?0:1;
    bool highlight = false;
    for(uint16_t i = (listIndexPage*BMC_OBE_LIST_LENGTH), e = 0 ; e < BMC_OBE_LIST_LENGTH ; i++, e++){
      
      if(highlight){
        highlight = false;
        tft.display.setTextColor(BMC_COLOR_EDITOR_TXT);
      }
      // black out the entire row
      tft.display.fillRect(0, y, 320, BMC_OBE_LIST_H, BMC_ILI9341_BLACK);
      if(i >= listLength){
        y += BMC_OBE_LIST_H;
        continue;
      }
      //add a little block to note which row has been selected
      if(listIndex == i){
        //drawSelChar(y+BMC_OBE_LIST_TXT_Y, true);
        drawSelChar(y, true);
      }
      //tft.display.drawFastHLine(0, y, 320, BMC_COLOR_EDITOR_GRAY);
      tft.display.setCursor(8, y+BMC_OBE_LIST_TXT_Y);

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
      y += BMC_OBE_LIST_H;
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
    uint16_t y = BMC_OBE_LIST_HEAD_H+8;
    for(uint16_t i = (listIndexPage*BMC_OBE_LIST_LENGTH), e = 0 ; e < BMC_OBE_LIST_LENGTH ; i++, e++){
      // black out the entire row
      tft.display.fillRect(0, y, 320, BMC_OBE_LIST_H, BMC_ILI9341_BLACK);
      if(i >= listLength){
        y += BMC_OBE_LIST_H;
        continue;
      }
      //add a little block to note which row has been selected
      if(listIndex == i){
        drawSelChar(y, true);
      }
      //tft.display.drawFastHLine(0, y, 320, BMC_COLOR_EDITOR_GRAY);
      tft.display.setCursor(8, y+BMC_OBE_LIST_TXT_Y);
      if(e<2){
        //yesNoLabels
        tft.display.print(yesNoLabels[e]);
      }
      //tft.display.print((e==0) ? "No" : "Yes");
      y += BMC_OBE_LIST_H;
    }
  }
  void updateListIndex(){
    uint16_t y = BMC_OBE_LIST_HEAD_H+8;
    for(uint16_t i=(listIndexPage*BMC_OBE_LIST_LENGTH), e=0;i<listLength;i++, e++){
      drawSelChar(y, (listIndex == i));
      y += BMC_OBE_LIST_H;
      //drawSelChar(y+BMC_OBE_LIST_TXT_Y, (listIndex == i));
    }
  }
  void drawSelChar(uint16_t y, bool on){
    uint16_t color = on ? BMC_ILI9341_ORANGE : BMC_ILI9341_BLACK;
    tft.display.fillRect(0, y, 4, BMC_OBE_LIST_H, color);
    //tft.display.drawChar(1, y, BMC_OBE_SEL_CHAR, color, 0, BMC_OBE_LIST_TXT_SIZE);
  }
  void renderHeader(const char* title){
    //tft.display.setFontAdafruit();
    tft.display.setFont(BMC_OBE_HEAD_FONT);
    tft.display.fillRect(0, 0, 320, BMC_OBE_LIST_HEAD_H, BMC_OBE_HEAD_COLOR);
    tft.display.setTextSize(BMC_OBE_LIST_HEAD_TXT_SIZE);
    uint16_t x = (320-((strlen(title)*BMC_OBE_LIST_HEAD_CHAR_WIDTH)-BMC_OBE_LIST_HEAD_TXT_SIZE))/2;
    tft.display.setCursor(x, BMC_OBE_LIST_HEAD_TXT_Y);
    tft.display.setTextColor(BMC_ILI9341_WHITE);
    tft.display.print(title);
    
    //tft.display.setFontAdafruit();
    tft.display.setFont(BMC_OBE_LIST_FONT);
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
      render(level);

    } else if(level==BMC_OBE_LEVEL_PAGES){
      if(listIndex < BMC_MAX_PAGES && BMC_MAX_PAGES>1){
        if(listIndex != globals.page){
          globals.page = listIndex;
          exitEditor();
          globals.setReloadPage(true);
        }
      }
    } else if(level == BMC_OBE_LEVEL_NAMES){

      render(BMC_OBE_LEVEL_NAMES_EDITOR);

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
      render(BMC_OBE_LEVEL_MAIN);
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
      if(listTotalPages > 1){
        listIndexPage--;
        if(listIndexPage < 0){
          listIndexPage = listTotalPages-1;
        }
        listIndex = (listIndexPage*BMC_OBE_LIST_LENGTH);
        render(level);
        return;
      }
    }
    listIndex--;
    if(listIndex < 0){
      listIndex = listLength-1;
      if(listTotalPages>1){
        listIndexPage = listTotalPages-1;
        render(level);
      } else {
        updateListIndex();
      }
    } else {
      if(listIndex < (listIndexPage*BMC_OBE_LIST_LENGTH)){
        if(listIndexPage>0){
          listIndexPage--;
          render(level);
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
        listIndex = (listIndexPage*BMC_OBE_LIST_LENGTH);
        render(level);
        return;
      }
    }
    listIndex++;
    if(listIndex >= listLength){
      resetIndex();
      if(listTotalPages>1){
        render(level);
      } else {
        updateListIndex();
      }
    } else {
      if(listIndex >= ((listIndexPage+1)*BMC_OBE_LIST_LENGTH)){
        if(listIndexPage < listTotalPages){
          listIndexPage++;
          render(level);
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
    "pgDevices",
    "Change Page"
  };
  const char onOffLabels[2][4] = {
    "Off",
    "On"
  };
  const char yesNoLabels[2][4] = {
    "No",
    "Yes"
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
    tft.display.setFont(BMC_OBE_LIST_FONT);
    tft.display.fillRect(0, 0, 320, 240, BMC_ILI9341_BLACK);
    render(0);
  }
  void exitEditor(){
    settingsEditor.shutDown();
    namesEditor.shutDown();
    globals.setOnBoardEditorActive(false);
    reset();
    tft.display.setFontAdafruit();
    tft.display.fillRect(0, 0, 320, 240, BMC_ILI9341_BLACK);
    display.reassign(globals.page);
  }
};
#endif
#endif