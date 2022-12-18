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
#include "editor/onBoard/handlers/BMC-OBEDevices.h"

#define BMC_OBE_FLAGS_SHIFT              	 0
#define BMC_OBE_FLAGS_ROW_EDIT           	 1
#define BMC_OBE_FLAGS_ROW_EDIT_ACTIVE    	 2
#define BMC_OBE_FLAGS_ROW_EDIT_CHANGED   	 3
#define BMC_OBE_FLAGS_WAITING_FOR_CONFIRM	 4
#define BMC_OBE_FLAGS_DYNAMIC_LIST       	 5
#define BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST  	 6
#define BMC_OBE_FLAGS_NO_SCROLL_BAR      	 7

#define BMC_OBE_DISPLAY_ROW_ID

class BMCOBE {
public:
  BMCOBE(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft),
                  devicesEditor(globals, settings, editor, display, data){

  }
  void begin(){
    devicesEditor.begin();
  }
  void update(){
    if(!globals.onBoardEditorActive()){
      return;
    }
    uint8_t queued = data.update();
    switch(queued){
      case 1:
        // prev
        cursorPrev();
        break;
      case 2:
        // next
        cursorNext();
        break;
    }
  }
  void render(){
    renderHeader("BMC Editor");
    data.totalRows = 0;
    data.visibleRowIdLength = 0;
    flags.off(BMC_OBE_FLAGS_ROW_EDIT);
    flags.off(BMC_OBE_FLAGS_DYNAMIC_LIST);
    flags.off(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST);

    for(uint16_t i = 0 ; i < totalMenuItems ; i++){
      bool allowed = true;
      for(uint8_t e = 0 ; e < (data.level[0]+1) ; e++){
        if(data.level[0] >= 3 && (items[i].id == 23 || items[i].id == 27)){
          //BMC_PRINTLN(">>>",e, items[i].id, items[i].label, items[i].level[e], data.level[e]);
        }
        if(items[i].id == 0 || items[i].level[e] != data.level[e]){
          if(data.level[0] >= 3 && (items[i].id == 23 || items[i].id == 27)){
            //BMC_PRINTLN("not allowed");
          }
          allowed = false;
          break;
        }
      }
      if(!allowed){
        continue;
      }
      bool breakLoop = false;
      switch(items[i].type){
        case BMC_OBE_EDIT_LIST:
          flags.on(BMC_OBE_FLAGS_ROW_EDIT);
          break;
        case BMC_OBE_MENU_DYNAMIC_LIST:
          flags.on(BMC_OBE_FLAGS_DYNAMIC_LIST);
          data.totalRows = items[i].max;
          data.dynamicListIndex = i;
          handleDynamicListRows();
          breakLoop = true;
          break;
        case BMC_OBE_MENU_DYNAMIC_EDIT:
          flags.on(BMC_OBE_FLAGS_ROW_EDIT);
          flags.on(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST);
          data.dynamicListIndex = i;
          handleDynamicEditRows();
          breakLoop = true;
          break;
      }
      if(breakLoop){
        break;
      }
      data.totalRows++;
    }
    //BMC_PRINTLN("data.totalRows", data.totalRows);
    
    if(data.totalRows > 0){
      data.maxRowPages = ceil(data.totalRows / (BMC_OBE_ROWS_PER_PAGE+0.0)); // int16_t
      if(data.maxRowPages < 1){
        data.maxRowPages = 1;
      }
      if(data.rowPage >= data.maxRowPages){
        data.rowPage = 0;
      }
    }

    // BMC_PRINTLN("-----------");

    if(isDynamicList()){
      uint8_t startingPage = (data.rowPage*BMC_OBE_ROWS_PER_PAGE);
      uint16_t length = items[data.dynamicListIndex].max;
      for(uint16_t i = 0, e = 0, o=0 ; i < length ; i++){
        uint16_t id = i;
        if(e >= BMC_OBE_ROWS_PER_PAGE){
          break;
        }
        bool breakLoop = false;
        uint16_t dID = items[data.dynamicListIndex].id;
        switch(dID){
          case BMC_OBE_ID_GLOBAL_ITEMS:
          case BMC_OBE_ID_PAGES_ITEMS:
            {
              bool useGlobalItems = (dID == BMC_OBE_ID_GLOBAL_ITEMS);
              if(editor.devicesData[id].id==0 || editor.devicesData[id].length==0){
                breakLoop = true;
                break;
              }
              if(editor.devicesData[id].global == useGlobalItems){
                if(o >= startingPage){
                  data.addToVisibleList(editor.devicesData[id].id);
                  // BMC_PRINTLN("add to visible list", id, editor.devicesData[id].id, editor.devicesData[id].label, data.visibleRowIdLength, data.totalRows);
                  e++;
                }
                o++;
              } 
            }
            break;
          case BMC_OBE_ID_G_ITEM_LIST:
          case BMC_OBE_ID_P_ITEM_LIST:
            if(i >= data.activeDevice.length){
              breakLoop = true;
              break;
            }
            if(o >= startingPage){
              // BMC_PRINTLN("add to visible list", data.activeDevice.label, o);
              data.addToVisibleList(o+1);
              e++;
            }
            o++;
            break;
        }
        if(breakLoop){
          break;
        }
      }
      goto continueToRenderRows;
    } else if(isDynamicEdit()){
      uint8_t startingPage = (data.rowPage * BMC_OBE_ROWS_PER_PAGE);
      uint16_t length = items[data.dynamicListIndex].max;
      for(uint16_t i = 0, e = 0 ; i < length ; i++){
        //uint16_t id = i;
        if(e >= BMC_OBE_ROWS_PER_PAGE){
          break;
        }
        bool breakLoop = false;
        uint16_t dID = items[data.dynamicListIndex].id;
        switch(dID){
          case BMC_OBE_ID_G_ITEM_EDIT:
          case BMC_OBE_ID_P_ITEM_EDIT:
            if(devicesEditor.isCompatible()){
              breakLoop = devicesEditor.addRows(startingPage);
            }
            // if(data.activeDevice.length == 0){
            //   breakLoop = true;
            //   break;
            // }
            // if(data.activeDevice.id == BMC_DEVICE_ID_BUTTON || data.activeDevice.id == BMC_DEVICE_ID_GLOBAL_BUTTON){
            //   for(uint8_t i = startingPage ; i < 2+data.activeDevice.settings+data.activeDevice.events ; i++){
            //     data.addToVisibleList(i+1);
            //     e++;
            //     if(e >= BMC_OBE_ROWS_PER_PAGE){
            //       break;
            //     }
            //   }
            // }
            break;
        }
        if(breakLoop){
          break;
        }
      }
      goto continueToRenderRows;
    }

    {
      uint16_t startAt = 0;
      for(uint16_t l = 0, u = 0 ; l < BMC_OBE_ROWS_PER_PAGE ; l++){
        for(uint16_t i = startAt ; i < totalMenuItems ; i++){
          startAt = (i + 1);
          bool allowed = true;
          for(uint8_t e = 0 ; e < (data.level[0]+1) ; e++){
            if(items[i].id == 0 || items[i].level[e] != data.level[e]){
              allowed = false;
              break;
            }
          }
          if(!allowed){
            continue;
          }
          if(data.maxRowPages==1){
            data.addToVisibleList(i + 1);
            break;
          }
          if(u >= (data.rowPage*BMC_OBE_ROWS_PER_PAGE)){
            data.addToVisibleList(i + 1);
            break;
          }
          u++;
        }
      }
    }
    
    continueToRenderRows: {
      if(data.activeRow > data.visibleRowIdLength){
        data.activeRow = data.visibleRowIdLength;
      }
      for(uint8_t row = 0 ; row < BMC_OBE_ROWS_PER_PAGE ; row++){
        renderRow(row);
      }
      renderScrollBar();
    }
    
  }
  void handleDynamicListRows(){
    uint16_t dID = items[data.dynamicListIndex].id;
    switch(dID){
      case BMC_OBE_ID_GLOBAL_ITEMS:
      case BMC_OBE_ID_PAGES_ITEMS:
        data.totalRows = 0;
        for(uint16_t t = 0 ; t < editor.getDevicesDataLength() ; t++){
          if(editor.devicesData[t].id==0 || editor.devicesData[t].length==0){
            break;
          }
          if(editor.devicesData[t].global == (dID == BMC_OBE_ID_GLOBAL_ITEMS)){
            data.totalRows++;
          }
        }
        break;
      case BMC_OBE_ID_G_ITEM_LIST:
      case BMC_OBE_ID_P_ITEM_LIST:
        data.totalRows = data.activeDevice.length;
        break;
    }
  }
  void handleDynamicEditRows(){
    uint16_t dID = items[data.dynamicListIndex].id;
    switch(dID){
      case BMC_OBE_ID_G_ITEM_EDIT:
      case BMC_OBE_ID_P_ITEM_EDIT:
        if(devicesEditor.isCompatible()){
          devicesEditor.setTotalRows();
        }
        break;
    }
  }
  void renderRow(uint8_t n){
    bool empty = false;
    if(n >= data.visibleRowIdLength){
      empty = true;
    }
    uint16_t y = BMC_OBE_ROW_HEAD_H + (n * BMC_OBE_ROW_H);
    uint16_t color = BMC_OBE_ROW_COLOR;
    uint16_t background = BMC_OBE_ROW_BACKGROUND;
    tft.display.setFont(BMC_OBE_ROW_FONT);
    if(!empty && data.activeRow == (n+1)){
      background = BMC_OBE_SEL_BACKGROUND;
      color = BMC_OBE_SEL_COLOR;
      tft.display.setFont(BMC_OBE_ROW_SEL_FONT);
    }
    bool activeItem = isEditModeActive() && data.activeRow == (n+1);
    if(activeItem){
      background = BMC_OBE_ROW_EDITABLE_BACKGROUND;
    }
    if(isDynamicEdit()){
      switch(items[data.dynamicListIndex].id){
        case BMC_OBE_ID_G_ITEM_EDIT:
        case BMC_OBE_ID_P_ITEM_EDIT:
          if(devicesEditor.hasCustomEditor(n)){
            flags.on(BMC_OBE_FLAGS_NO_SCROLL_BAR);
            return;
          }
      }
    }
    tft.display.fillRect(0, y, BMC_OBE_W-6, BMC_OBE_ROW_H, background);
    
    //tft.display.fillRoundRect(0, y, BMC_OBE_W, BMC_OBE_ROW_H, BMC_OBE_BORDER_RADIUS, background);
    //tft.display.drawRoundRect(0, y, BMC_OBE_W, BMC_OBE_ROW_H, BMC_OBE_BORDER_RADIUS, BMC_OBE_ROW_DIVIDER);
    
    if(empty || data.visibleRowId[n] == 0){
      // BMC_PRINTLN("renderRow() empty row");
      return;
    }
    uint16_t id = data.visibleRowId[n]-1;

    bool rowIsEditable = false;

    if(isDynamicList()){
      rowIsEditable = false;
    } else if(isDynamicEdit()){
      rowIsEditable = true;
    } else {
      rowIsEditable = (items[id].type == BMC_OBE_EDIT_LIST);
    }

    if(rowIsEditable){
      tft.display.setFont(data.activeRow == (n+1) ? BMC_OBE_ROW_SEL_VALUE_FONT : BMC_OBE_ROW_VALUE_FONT);
    }
    tft.display.setCursor(BMC_OBE_SIDEBAR_WIDTH, (y + (rowIsEditable ? 9 : 16)));
    tft.display.setTextColor(color);
    #if defined(BMC_OBE_DISPLAY_ROW_ID)
      tft.display.print(id+1);
      tft.display.print(" ");
    #endif


    if(isDynamicList()){
      uint16_t dID = items[data.dynamicListIndex].id;
      switch(dID){
        case BMC_OBE_ID_GLOBAL_ITEMS:
        case BMC_OBE_ID_PAGES_ITEMS:
          {
            BMCDeviceData dd = editor.getDeviceData(id+1);
            // BMC_PRINTLN("renderRow()", id+1, dd.label);
            if(dd.id != 0){
              tft.display.print(dd.label);
              uint8_t strL = strlen(dd.label);
              char lastChar = dd.label[strL-1];
              if(lastChar!='s' && lastChar!='x' && lastChar!='p'){
                tft.display.print("s");
              }
              renderCaret(y, color, background);
              tft.display.setFont(BMC_OBE_ROW_FONT);
            }
          }
          break;
        case BMC_OBE_ID_G_ITEM_LIST:
        case BMC_OBE_ID_P_ITEM_LIST:
          uint8_t offset = settings.getDisplayOffset() ? 0 : 1;
          tft.display.print(data.activeDevice.label);
          tft.display.print(" # ");
          tft.display.print(id + offset);
          renderCaret(y, color, background);
          tft.display.setFont(BMC_OBE_ROW_FONT);
          break;
      }
      return;
    } else if(isDynamicEdit()){
      switch(items[data.dynamicListIndex].id){
        case BMC_OBE_ID_G_ITEM_EDIT:
        case BMC_OBE_ID_P_ITEM_EDIT:
          if(devicesEditor.isCompatible()){
            devicesEditor.getOptionLabel(n);
            tft.display.print(devicesEditor.str);
            if(!isEditModeActive()){
              devicesEditor.getOptionValue(n);
            } else {
              devicesEditor.getOptionEditedValue(n);
            }
            printRowValue(y, activeItem, devicesEditor.str);
          }
          break;
      }
      return;
    }

    





    tft.display.print(items[id].label);
    if(!rowIsEditable){
      renderCaret(y, color, background);
    } else {
      char str[33] = "";
      
      getEditorValueLabel(id+1, str, activeItem);
      printRowValue(y, activeItem, str);
    }
  }
  void printRowValue(uint16_t y, bool activeItem, const char * t_str){
    char str[33] = "";
    strcpy(str, t_str);
    printRowValue(y, activeItem, str);
  }
  void printRowValue(uint16_t y, bool activeItem, char * str){
    // uint16_t x = getCenteredX(str);
    int16_t textWidth = tft.display.strPixelLen(str);
    int16_t x = (BMC_OBE_W-BMC_OBE_SIDEBAR_WIDTH)-textWidth;
    x = (x < 0) ? 0 : x-6;
    //x += (BMC_OBE_SIDEBAR_WIDTH*3);
    tft.display.setTextColor(activeItem?BMC_OBE_ROW_EDITING_COLOR:BMC_OBE_ROW_EDITABLE_COLOR);
    tft.display.setCursor(x, (y + 29));
    tft.display.print(str);
    tft.display.setFont(BMC_OBE_ROW_FONT);
  }
  void updateRows(){
    if(data.isHeaderSelected()){
      renderHeader(data.headerTitle);
    } else {
      renderRow(data.activeRow-1);
    }
    if(!isEditModeActive() && data.updatePreviousRow()){
      if(data.activeRowPrev==0){
        renderHeader(data.headerTitle);
      } else {
        renderRow(data.activeRowPrev-1);
      }
    }
    renderScrollBar();
  }
  void renderScrollBar(){
    if(flags.toggleIfTrue(BMC_OBE_FLAGS_NO_SCROLL_BAR)){
      return;
    }
    uint8_t w = BMC_OBE_SIDEBAR_WIDTH;
    tft.display.fillRect(BMC_OBE_W-w, BMC_OBE_ROW_HEAD_H, w, BMC_OBE_ROW_AREA, 0x0841);
    if(data.maxRowPages <= 1){
      return;
    }
    uint16_t scrollHandle = BMC_OBE_ROW_AREA / data.maxRowPages;
    uint16_t pos = scrollHandle * data.rowPage;
    tft.display.fillRoundRect(BMC_OBE_W-w, BMC_OBE_ROW_HEAD_H+pos, w, scrollHandle, 3, 0xB596);
  }
  void renderCaret(uint16_t y, uint16_t color, uint16_t background){
    tft.display.fillRect(BMC_OBE_CARET_BOX_X, y+1, 24, BMC_OBE_ROW_H-2, background);
    tft.display.drawChar(BMC_OBE_CARET_CHAR_X , y+17, BMC_OBE_SEL_CHAR_CARET, color, background, 2);
  }
  void renderHeader(const char* title){
    char buff[strlen(title)+1];
    strcpy(buff, title);
    renderHeader(buff);
  }
  void renderHeader(char* title){
    strcpy(data.headerTitle, title);
    char buff[strlen(title)+1];
    strcpy(buff, title);
    if(data.isHeaderSelected()){
      strcpy(buff, (data.level[0] == 0) ? "< Exit Menu" : "< Back");
    }
    tft.display.setFont(BMC_OBE_HEAD_FONT);
    // int16_t textWidth = tft.display.strPixelLen(buff);
    // int16_t x = (BMC_OBE_W-textWidth) / 2;
    // if(x < 0){
    //   x = 0;
    // }
    uint16_t x = getCenteredX(buff);
    uint16_t color = BMC_OBE_HEAD_COLOR;
    uint16_t background = BMC_OBE_HEAD_BACKGROUND;
    if(data.isHeaderSelected()){
      background = BMC_OBE_HEAD_SEL_BACKGROUND;
      color = BMC_OBE_SEL_COLOR;
    }
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_ROW_HEAD_H, background);
    tft.display.drawRect(0, 0, BMC_OBE_W, BMC_OBE_ROW_HEAD_H, BMC_OBE_ROW_DIVIDER);
    tft.display.setTextColor(color);
    tft.display.setCursor(x, BMC_OBE_HEAD_TXT_Y);
    tft.display.print(buff);
    tft.display.setFont(BMC_OBE_ROW_FONT);
  }
  // @queue is used for encoders to avoid the values being unstable
  void menuCommand(uint8_t cmd, bool queue=false){
    if(cmd==BMC_MENU_TOGGLE){
      if(confirmSave()){
        exitEditor();
        return;
      }
      if(globals.editorConnected()){
        return;
      }
      globals.toggleOnBoardEditor();
      if(globals.onBoardEditorActive()){
        enterEditor();
      } else {
        exitEditor();
      }
      return;
    } else if(cmd==BMC_MENU_SELECT){
      if(!globals.onBoardEditorActive()){
        menuCommand(BMC_MENU_TOGGLE);
        return;
      }
    } else if(!globals.onBoardEditorActive()){
      return;
    }
    switch(cmd){
      case BMC_MENU_SELECT:
        select();
        flags.off(BMC_OBE_FLAGS_SHIFT);
        break;
      case BMC_MENU_BACK:
        back();
        flags.off(BMC_OBE_FLAGS_SHIFT);
        break;
      case BMC_MENU_PREV:
        if(queue){
          data.queuePrev();
        } else {
          cursorPrev();
        }
        
        break;
      case BMC_MENU_NEXT:
        if(queue){
          data.queueNext();
        } else {
          cursorNext();
        }
        
        break;
      case BMC_MENU_SHIFT:
        flags.toggle(BMC_OBE_FLAGS_SHIFT);
        break;
      default:
        break;
    }
  }
  void select(){
    data.resetQueue();
    if(waitingForConfirmation()){
      handleConfirmation();
      return;
    }
    if(data.isHeaderSelected() || shiftActive()){
      back();
      return;
    }
    if(isEditMode()){
      uint16_t id = data.getActiveVisibleRow();
      flags.toggle(BMC_OBE_FLAGS_ROW_EDIT_ACTIVE);
      if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
        if(devicesEditor.isCompatible()){
          if(isEditModeActive()){
            data.rowEditValue = devicesEditor.getOptionValue(data.activeRow-1);
            BMC_PRINTLN("select() data.rowEditValue", data.rowEditValue, data.activeRow-1);
          } else {
            setChangesMade(devicesEditor.setOptionValue());
            data.rowEditValue = 0;
          }
        }
      } else {
        if(isEditModeActive()){
          data.rowEditValue = getEditorValue(id);
        } else {
          setEditorValue(id);
        }
      }
      updateRows();
      return;
    }
    if(data.setNextMenuLevel()){
      if(isDynamicList()){
        switch(items[data.dynamicListIndex].id){
          case BMC_OBE_ID_GLOBAL_ITEMS:
          case BMC_OBE_ID_PAGES_ITEMS:
            {
              uint16_t id = data.getActiveVisibleListItem();
              data.activeDevice = editor.getDeviceData(id);
              data.deviceType = data.activeDevice.id;
            }
            break;
          case BMC_OBE_ID_G_ITEM_LIST:
          case BMC_OBE_ID_P_ITEM_LIST:
            data.deviceIndex = data.getActiveVisibleRow();
            break;
        }
        data.setCurrentLevelValue(0);
      }
    }
    data.resetActiveRow();
    render();
  }
  void back(){
    if(data.level[0] == 0){
      exitEditor();
      return;
    }
    data.setPreviousMenuLevel();
    flags.off(BMC_OBE_FLAGS_ROW_EDIT_ACTIVE);
    render();
  }
  void cursorPrev(){
    if(waitingForConfirmation()){
      data.toggleConfirmationValue();
      renderConfirmSave();
      return;
    }
    if(isEditModeActive()){
      uint16_t id = data.getActiveVisibleRow()-1;
      uint16_t min = items[id].min;
      uint16_t max = items[id].max;
      uint8_t steps = items[id].steps;
      if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
        if(devicesEditor.isCompatible()){
          min = devicesEditor.getMin();
          max = devicesEditor.getMax();
          steps = 1;
          if(devicesEditor.handleCustomValueScroller(false)){
            updateRows();
            return;
          }
        }
      }
      if((int)(data.rowEditValue-steps) < min){
        data.rowEditValue = max;
      } else {
        data.rowEditValue -= steps;
      }
      updateRows();
      return;
    }
    if(shiftActive()){
      prevListPage();
      return;
    }
    if(data.cursorPrev()){
      updateRows();
    } else {
      prevListPage();
    }
  }
  void prevListPage(){
    if(isEditModeActive()){
      return;
    }
    if(data.prevListPage()){
      render();
    } else {
      updateRows();
    }
  }
  void cursorNext(){
    if(waitingForConfirmation()){
      data.saveConfirmationValue = !data.saveConfirmationValue;
      renderConfirmSave();
      return;
    }
    if(isEditModeActive()){
      uint16_t id = data.getActiveVisibleRow()-1;
      uint16_t min = items[id].min;
      uint16_t max = items[id].max;
      uint8_t steps = items[id].steps;
      if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
        if(devicesEditor.isCompatible()){
          min = devicesEditor.getMin();
          max = devicesEditor.getMax();
          steps = 1;
          if(devicesEditor.handleCustomValueScroller(true)){
            updateRows();
            return;
          }
        }
      }
      if(data.rowEditValue+steps > max){
        data.rowEditValue = min;
      } else {
        data.rowEditValue += steps;
      }
      updateRows();
      return;
    }
    if(shiftActive()){
      nextListPage();
      return;
    }
    if(data.cursorNext()){
      updateRows();
    } else {
      nextListPage();
    }
  }
  void nextListPage(){
    if((isEditModeActive())){
      return;
    }
    if(data.nextListPage()){
      render();
    } else {
      updateRows();
    }
  }
  bool shiftActive(){
    return flags.toggleIfTrue(BMC_OBE_FLAGS_SHIFT);
  }

private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  // all variables live here
  BMCOBEData data;

  BMCOBEDevices devicesEditor;

  BMCFlags <uint8_t> flags;
  

  const uint16_t totalMenuItems = 30;
  const BMCOBEMenuItem items[30] = {
    {{0}, BMC_OBE_ID_SETTINGS, "Settings", BMC_OBE_MENU_LIST},
      {{1,0}, BMC_OBE_ID_SETTINGS_GENERAL, "General", BMC_OBE_MENU_LIST},
        {{2,0,0}, BMC_OBE_ID_S_BTN_HOLD_TIME, "Button Hold Time", BMC_OBE_EDIT_LIST, 0, 15, 1},
        {{2,0,0}, BMC_OBE_ID_S_STARTUP_PRESET, "Startup Preset", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PRESETS-1, 1},
        {{2,0,0}, BMC_OBE_ID_S_DIM_LEDS, "Dim Off LEDs", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,0}, BMC_OBE_ID_S_DISPLAY_OFFSET, "Display Offset to 0", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,0}, BMC_OBE_ID_S_TRIG_1ST_SONG, "Trigger 1st Song", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,0}, BMC_OBE_ID_S_TRIG_1ST_PART, "Trigger 1st Song Part", BMC_OBE_EDIT_LIST, 0, 1, 1},
      {{1,0}, BMC_OBE_ID_SETTINGS_MIDI, "MIDI", BMC_OBE_MENU_LIST},
        {{2,0,1}, BMC_OBE_ID_S_IN_CTRL, "MIDI Incoming Control", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,1}, BMC_OBE_ID_S_IN_CTRL_CH, "MIDI In Ctrl Channel", BMC_OBE_EDIT_LIST, 0, 16, 1},
        {{2,0,1}, BMC_OBE_ID_S_IN_CTRL_ACTION, "MIDI In Ctrl Action", BMC_OBE_EDIT_LIST, 0, 2, 1},
        {{2,0,1}, BMC_OBE_ID_S_CLOCK_IN_PORT, "MIDI Clock Input Port", BMC_OBE_EDIT_LIST, 0, BMC_TOTAL_AVAILABLE_PORTS-1, 1},
        {{2,0,1}, BMC_OBE_ID_S_MASTER_CLOCK, "MIDI Master Clock", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,1}, BMC_OBE_ID_S_ACTIVE_SENSE, "MIDI Active Sense", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,1}, BMC_OBE_ID_S_BLOCK_RT_IN, "MIDI Block RT In", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,0,1}, BMC_OBE_ID_S_BLOCK_RT_OUT, "MIDI Block RT Out", BMC_OBE_EDIT_LIST, 0, 1, 1},

    {{0}, BMC_OBE_ID_CHANGE_PAGE, "Change Pages", BMC_OBE_MENU_LIST},
      {{1,1}, BMC_OBE_ID_CP_GO_TO_PAGE, "Go To", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PAGES-1, 1},

    {{0}, BMC_OBE_ID_GLOBAL, "Global", BMC_OBE_MENU_LIST},
      {{1,2}, BMC_OBE_ID_GLOBAL_ITEMS, "Global Devices", BMC_OBE_MENU_DYNAMIC_LIST, 0, 40, 1},
        {{2,2}, BMC_OBE_ID_G_ITEM_LIST, "Global List", BMC_OBE_MENU_DYNAMIC_LIST, 0, 0xFFFF, 1},
          {{3,2}, BMC_OBE_ID_G_ITEM_EDIT, "Global Edit", BMC_OBE_MENU_DYNAMIC_EDIT, 0, 0xFFFF, 1},

    {{0}, BMC_OBE_ID_PAGES, "Pages", BMC_OBE_MENU_LIST},
      {{1,3}, BMC_OBE_ID_PAGES_ITEMS, "Pages Devices", BMC_OBE_MENU_DYNAMIC_LIST, 0, 40, 1},
        {{2,3}, BMC_OBE_ID_P_ITEM_LIST, "Pages List", BMC_OBE_MENU_DYNAMIC_LIST, 0, 0xFFFF, 1},
          {{3,3}, BMC_OBE_ID_P_ITEM_EDIT, "Pages Edit", BMC_OBE_MENU_DYNAMIC_EDIT, 0, 0xFFFF, 1}
  };
  uint16_t getEditorValue(uint16_t id){
    char str[33] = "";
    return editorValueHandler(id, str, false, false);
  }
  void setEditorValue(uint16_t id){
    char str[33] = "";
    editorValueHandler(id, str, true, true);
  }
  void getEditorValueLabel(uint16_t id, char* str, bool active=false){
    editorValueHandler(id, str, active, false);
  }
  uint16_t editorValueHandler(uint16_t id, char* str, bool active=false, bool setValue=false){
    uint16_t value = data.rowEditValue;
    uint16_t originalValue = 0;
    uint16_t index = 0;
    if(setValue){
      index = data.getActiveVisibleRow()-1;
      data.rowEditValue = constrain(data.rowEditValue, items[index].min, items[index].max);
    }
    switch(id){
      case BMC_OBE_ID_S_BTN_HOLD_TIME:
        originalValue = settings.getButtonHoldThreshold();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setButtonHoldThreshold(value);
        }
        sprintf(str, "%u ms", (value+2)*250);
        return value;
      case BMC_OBE_ID_S_STARTUP_PRESET:
        originalValue = settings.getStartupPreset();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setStartupPreset(value);
        }
        if(value==0){
          strcpy(str, "None");
        } else {
          BMCTools::getPresetLabel((value-1), str, store.global);
        }
        return value;
      case BMC_OBE_ID_S_DIM_LEDS:
        originalValue = settings.getPwmDimWhenOff();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setPwmDimWhenOff(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_DISPLAY_OFFSET:
        originalValue = settings.getDisplayOffset();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setDisplayOffset(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_TRIG_1ST_SONG:
        originalValue = settings.getSetListTriggerFirstSong();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setSetListTriggerFirstSong(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_TRIG_1ST_PART:
        originalValue = settings.getSetListTriggerFirstSongPart();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setSetListTriggerFirstSongPart(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      // MIDI MENU
      case BMC_OBE_ID_S_IN_CTRL: // 
        originalValue = settings.getIncomingListenerEnabled();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setIncomingListenerEnabled(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_IN_CTRL_CH:
        originalValue = settings.getListenerChannel();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setListenerChannel(value);
        }
        if(value==0){
          strcpy(str, "Omni");
        } else {
          sprintf(str, "Channel %u", value);
        }
        return value;
      case BMC_OBE_ID_S_IN_CTRL_ACTION:
        originalValue = settings.getIncomingProgramType();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setIncomingProgramType(value);
        }
        switch(value){
          case 0: strcpy(str, "Do Nothing"); break;
          case 1: strcpy(str, "Change Page"); break;
          case 2: strcpy(str, "Change Preset"); break;
        }
        return value;
      case BMC_OBE_ID_S_CLOCK_IN_PORT:
        originalValue = settings.getClockInputPortBit();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setClockInputPortBit(value);
        }
        switch(data.availablePortsData[value]){
          case BMC_MIDI_PORT_USB_BIT: strcpy(str, "USB"); break;
          case BMC_MIDI_PORT_SERIAL_A_BIT: strcpy(str, "Serial A"); break;
          case BMC_MIDI_PORT_SERIAL_B_BIT: strcpy(str, "Serial B"); break;
          case BMC_MIDI_PORT_SERIAL_C_BIT: strcpy(str, "Serial C"); break;
          case BMC_MIDI_PORT_SERIAL_D_BIT: strcpy(str, "Serial D"); break;
          case BMC_MIDI_PORT_HOST_BIT: strcpy(str, "USB Host"); break;
          case BMC_MIDI_PORT_BLE_BIT: strcpy(str, "BLE"); break;
        }
        return value;
      case BMC_OBE_ID_S_MASTER_CLOCK:
        originalValue = settings.getMasterClock();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setMasterClock(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_ACTIVE_SENSE:
        originalValue = settings.getActiveSenseAtStartup();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setActiveSenseAtStartup(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_BLOCK_RT_IN:
        originalValue = settings.getMidiRealTimeBlockInput();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setMidiRealTimeBlockInput(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_BLOCK_RT_OUT:
        originalValue = settings.getMidiRealTimeBlockOutput();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          settings.setMidiRealTimeBlockOutput(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      // change pages
      case BMC_OBE_ID_CP_GO_TO_PAGE:
        originalValue = globals.page;
        value = (!active) ? originalValue : value;
        if(setValue && originalValue != value){
          globals.page = value;
          globals.setReloadPage(true);
          forceExitEditor();
          return value;
        }
        sprintf(str, "Page # %u", value+(settings.getDisplayOffset()?0:1));

        return value;
      default:
        break;
    }
    strcpy(str, "?????");
    return 0;
  }
  /*
    struct BMCOBEMenuItem {
      uint8_t level[BMC_OBE_MAX_LEVELS];
      uint16_t id = 0;
      char title[25];
      uint8_t type = 0; // 0=not editable, 1=editable
      uint8_t min = 0;
      uint16_t max = 0;
      uint8_t steps = 0;
    }
  */
  bool isEditMode(){
    return flags.read(BMC_OBE_FLAGS_ROW_EDIT);
  }
  bool isEditModeActive(){
    return flags.read(BMC_OBE_FLAGS_ROW_EDIT_ACTIVE);
  }
  bool isDynamicList(){
    return flags.read(BMC_OBE_FLAGS_DYNAMIC_LIST);
  }
  bool isDynamicEdit(){
    return flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST);
  }
  bool waitingForConfirmation(){
    return flags.read(BMC_OBE_FLAGS_WAITING_FOR_CONFIRM);
  }
  bool confirmSave(){
    return flags.read(BMC_OBE_FLAGS_ROW_EDIT_CHANGED);
  }
  bool setChangesMade(uint16_t originalValue, uint16_t newValue){
    if(originalValue != newValue){
      flags.on(BMC_OBE_FLAGS_ROW_EDIT_CHANGED);
      return true;
    }
    return false;
  }
  bool setChangesMade(uint16_t changed){
    if(changed > 0){
      flags.on(BMC_OBE_FLAGS_ROW_EDIT_CHANGED);
      return true;
    }
    return false;
  }
  void reset(){
    flags.reset();
    data.reset();
  }
  void enterEditor(){
    globals.setOnBoardEditorActive(true);
    tft.display.setFont(BMC_OBE_ROW_FONT);
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    render();
  }
  void forceExitEditor(){
    if(confirmSave()){
      editor.reloadPreviouslySavedStore();
      flags.off(BMC_OBE_FLAGS_ROW_EDIT_CHANGED);
      flags.off(BMC_OBE_FLAGS_WAITING_FOR_CONFIRM);
    }
    exitEditor();
  }
  void exitEditor(){
    BMC_PRINTLN("Exit Editor");
    if(confirmSave()){
      if(!waitingForConfirmation()){
        flags.on(BMC_OBE_FLAGS_WAITING_FOR_CONFIRM);
      }
      tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
      renderConfirmSave();
      return;
    }
    globals.setOnBoardEditorActive(false);
    reset();
    tft.display.setFontAdafruit();
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    display.reassign(globals.page);
  }

  void renderConfirmSave(){
    char buff[18] = "Save Changes?";
    tft.display.setFont(BMC_OBE_CONFIRMATION_FONT);
    uint16_t x = getCenteredX(buff);
    // int16_t textWidth = tft.display.strPixelLen(buff);
    // int16_t x = (BMC_OBE_W-textWidth) / 2;
    // if(x < 0){
    //   x = 0;
    // }
    tft.display.setTextColor(BMC_ILI9341_WHITE);
    tft.display.setCursor(x, 40);
    tft.display.print(buff);
    uint16_t c1 = !data.saveConfirmationValue ? BMC_OBE_ROW_EDITABLE_BACKGROUND : BMC_ILI9341_BLACK;
    uint16_t c2 = data.saveConfirmationValue ? BMC_OBE_ROW_EDITABLE_BACKGROUND : BMC_ILI9341_BLACK;

    tft.display.fillRoundRect(30, 120, 120, 60, 7, c1);
    tft.display.drawRoundRect(30, 120, 120, 60, 7, 0x528A);

    tft.display.fillRoundRect(170, 120, 120, 60, 7, c2);
    tft.display.drawRoundRect(170, 120, 120, 60, 7, 0x528A);

    tft.display.setCursor(73, 140);
    tft.display.print("NO");
    tft.display.setCursor(205, 140);
    tft.display.print("YES");
  }
  void handleConfirmation(){
    // get input value
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    char buff[17] = "";
    strcpy(buff, data.saveConfirmationValue ? "Saving..." : "No Changes Saved");
    tft.display.setFont(BMC_OBE_CONFIRMATION_FONT);
    // int16_t textWidth = tft.display.strPixelLen(buff);
    // int16_t x = (BMC_OBE_W-textWidth) / 2;
    // if(x < 0){
    //   x = 0;
    // }
    uint16_t x = getCenteredX(buff);
    tft.display.setTextColor(BMC_ILI9341_WHITE);
    tft.display.setCursor(x, 80);
    tft.display.print(buff);
    if(data.saveConfirmationValue){
      editor.saveEEPROM();
    } else {
      editor.reloadPreviouslySavedStore();
    }
    globals.setAssignStoreData(true);
    flags.off(BMC_OBE_FLAGS_ROW_EDIT_CHANGED);
    flags.off(BMC_OBE_FLAGS_WAITING_FOR_CONFIRM);
    exitEditor();
  }
  uint16_t getCenteredX(const char * buff){
    char str[strlen(buff)];
    strcpy(str, buff);
    return getCenteredX(str);
  }
  uint16_t getCenteredX(char * buff){
    int16_t textWidth = tft.display.strPixelLen(buff);
    int16_t x = (BMC_OBE_W-textWidth) / 2;
    return (x < 0) ? 0 : x;
  }
};
#endif
#endif