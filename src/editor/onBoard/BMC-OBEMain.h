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

// #define BMC_OBE_DISPLAY_ROW_ID

class BMCOBE {
public:
  BMCOBE(BMCEditor& t_editor, BMCDisplay& t_display):
                  editor(t_editor),
                  display(t_display),
                  tft(display.tft.display),
                  devicesEditor(editor, display, data){

  }
  void begin(){
    // BMC_PRINTLN("BMC_OBE_ROWS_PER_PAGE", BMC_OBE_ROWS_PER_PAGE);
    data.begin();
    devicesEditor.begin();
    BMC_PRINTLN("*****BMC_OBE_ROWS_PER_PAGE",BMC_OBE_ROWS_PER_PAGE);
  }
  void update(){
#if defined(BMC_HAS_TOUCH_SCREEN)
    menuCommand(display.getTouchCommand());
#endif
    if(!display.midi.globals.onBoardEditorActive()){
      return;
    }
    devicesEditor.update();
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
    if(data.renderHead()){
      renderHeader(data.headerTitle);
    }
  }
  void render(){
    renderHeader("BMC Editor");
    //renderHeader("");
    data.totalRows = 0;
    data.visibleRowIdLength = 0;
    flags.off(BMC_OBE_FLAGS_ROW_EDIT);
    flags.off(BMC_OBE_FLAGS_DYNAMIC_LIST);
    flags.off(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST);

    for(uint16_t i = 0 ; i < totalMenuItems ; i++){
      bool allowed = true;
      uint8_t lenLevels = data.level[0] + 1;
      for(uint8_t e = 0 ; e < lenLevels ; e++){
        if(data.level[0] > 0 && items[i].level[0] == data.level[0]-1){
        }
        if(items[i].id == 0 || items[i].level[e] != data.level[e]){
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
    if(data.totalRows > 0){
      data.maxRowPages = ceil(data.totalRows / (BMC_OBE_ROWS_PER_PAGE+0.0)); // int16_t
      if(data.maxRowPages < 1){
        data.maxRowPages = 1;
      }
      if(data.rowPage >= data.maxRowPages){
        data.rowPage = 0;
      }
    }

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
              if(!devicesEditor.isCompatible(editor.devicesData[id].id)){
                continue;
              }
              if(editor.devicesData[id].global == useGlobalItems){
                if(o >= startingPage){
                  data.addToVisibleList(editor.devicesData[id].id);
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
          if(!devicesEditor.isCompatible(editor.devicesData[t].id)){
            continue;
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
    tft.setFont(BMC_OBE_ROW_FONT);
    if(!empty && data.activeRow == (n+1)){
      background = BMC_OBE_SEL_BACKGROUND;
      color = BMC_OBE_SEL_COLOR;
      // tft.setFont(BMC_OBE_ROW_SEL_FONT);
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
    tft.fillRect(0, y, BMC_OBE_W-6, BMC_OBE_ROW_H, background);
    if(empty || data.visibleRowId[n] == 0){
      return;
    }
    tft.drawFastHLine(0, y+(BMC_OBE_ROW_H-1), BMC_OBE_W-6, BMC_OBE_SEL_BACKGROUND);
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
      // tft.setFont(data.activeRow == (n+1) ? BMC_OBE_ROW_SEL_VALUE_FONT : BMC_OBE_ROW_VALUE_FONT);
      tft.setFont(BMC_OBE_ROW_VALUE_FONT);
    }
    tft.setCursor(BMC_OBE_SIDEBAR_WIDTH, (y + (rowIsEditable ? BMC_OBE_ROW_TEXT_Y/2 : BMC_OBE_ROW_TEXT_Y)));
    tft.setTextColor(color);
    #if defined(BMC_OBE_DISPLAY_ROW_ID)
      tft.print(id+1);
      tft.print(" ");
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
              tft.print(dd.label);
              uint8_t strL = strlen(dd.label);
              char lastChar = dd.label[strL-1];
              if(lastChar!='s' && lastChar!='x' && lastChar!='p'){
                tft.print("s");
              }
              renderCaret(y, color, background);
              tft.setFont(BMC_OBE_ROW_FONT);
            }
          }
          break;
        case BMC_OBE_ID_G_ITEM_LIST:
        case BMC_OBE_ID_P_ITEM_LIST:
          uint8_t offset = display.midi.globals.settings.getDisplayOffset() ? 0 : 1;
          strcpy(data.headerTitle, data.activeDevice.label);
          // tft.print(data.activeDevice.label);
          // tft.print(" # ");
          tft.print("#");
          tft.print(id + offset);

          char nameStr[40] = "";
          editor.getDeviceNameText(data.activeDevice.id, id, nameStr);
          tft.print(" ");
          tft.print(nameStr);

          if(devicesEditor.isCompatible() && devicesEditor.isEventsList()){
            devicesEditor.getEventStatusName(nameStr, id);
            tft.print(" ");
            tft.print(nameStr);
          }
          
          renderCaret(y, color, background);
          tft.setFont(BMC_OBE_ROW_FONT);
          break;
      }
      return;
    } else if(isDynamicEdit()){
      switch(items[data.dynamicListIndex].id){
        case BMC_OBE_ID_G_ITEM_EDIT:
        case BMC_OBE_ID_P_ITEM_EDIT:
          if(devicesEditor.isCompatible()){
            devicesEditor.getOptionLabel(n);
            tft.print(devicesEditor.str);
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
    tft.print(items[id].label);
    if(!rowIsEditable){
      renderCaret(y, color, background);
    } else {
      char str[40] = "";
      getEditorValueLabel(id+1, str, activeItem);
      printRowValue(y, activeItem, str);
    }
  }
  void printRowValue(uint16_t y, bool activeItem, const char * t_str){
    char str[40] = "";
    strcpy(str, t_str);
    printRowValue(y, activeItem, str);
  }
  void printRowValue(uint16_t y, bool activeItem, char * str){
    // uint16_t x = getCenteredX(str);
    int16_t textWidth = tft.strPixelLen(str);
    int16_t x = (BMC_OBE_W-BMC_OBE_SIDEBAR_WIDTH)-textWidth;
    x = (x < 0) ? 0 : x-6;
    //x += (BMC_OBE_SIDEBAR_WIDTH*3);
    tft.setTextColor(activeItem?BMC_OBE_ROW_EDITING_COLOR:BMC_OBE_ROW_EDITABLE_COLOR);
    // tft.setTextColor(BMC_OBE_ROW_EDITING_COLOR);
    tft.setCursor(x, (y + 29));
    // tft.setCursor(x, y+16);
    tft.print(str);
    // tft.setFont(BMC_OBE_ROW_FONT);
    // tft.drawFastVLine(0, 0, 240, BMC_ILI9341_RED);
    // tft.drawFastVLine(106, 0, 240, BMC_ILI9341_RED);
    // tft.drawFastVLine(212, 0, 240, BMC_ILI9341_RED);
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
    tft.fillRect(BMC_OBE_W-w, BMC_OBE_ROW_HEAD_H, w, BMC_OBE_SCROLL_BAR_AREA_H, 0x0841);
    if(data.maxRowPages <= 1){
      return;
    }
    uint16_t scrollHandle = BMC_OBE_SCROLL_BAR_AREA_H / data.maxRowPages;
    uint16_t pos = scrollHandle * data.rowPage;
    if(scrollHandle < 2){
      scrollHandle = 2;
    }
    tft.fillRect(BMC_OBE_W-w, BMC_OBE_ROW_HEAD_H+pos, w, scrollHandle, 0xB596);
  }
  void renderCaret(uint16_t y, uint16_t color, uint16_t background){
    tft.fillRect(BMC_OBE_CARET_BOX_X, y+1, 24, BMC_OBE_ROW_H-2, background);
#if BMC_TFT_SIZE == 1
    tft.drawChar(BMC_OBE_CARET_CHAR_X , y+17, BMC_OBE_SEL_CHAR_CARET_RIGHT, color, background, 2);
#else
    tft.drawChar(BMC_OBE_CARET_CHAR_X , y+17, BMC_OBE_SEL_CHAR_CARET_RIGHT, color, background, 2, 2);
#endif
  }
  void renderHeader(const char* title){
    char buff[strlen(title)+1];
    strcpy(buff, title);
    renderHeader(buff);
  }
  void renderHeader(char* title){
    data.triggerHeaderRender = false;
    if(strlen(title) > 0){
      strcpy(data.headerTitle, title);
    }
    
    char buff[strlen(title)+1];
    strcpy(buff, title);
    if(data.isHeaderSelected()){
      strcpy(buff, (data.level[0] == 0) ? "Exit Menu" : "Back");
    } else if(data.level[0] == 0){
      strcpy(buff, "BMC Editor");
    }
    tft.setFont(BMC_OBE_HEAD_FONT);
    uint16_t x = getCenteredX(buff);
    uint16_t color = BMC_OBE_HEAD_COLOR;
    uint16_t background = BMC_OBE_HEAD_BACKGROUND;
    if(data.isHeaderSelected()){
      background = BMC_OBE_HEAD_SEL_BACKGROUND;
      color = BMC_OBE_SEL_COLOR;
    }
    tft.fillRect(0, 0, BMC_OBE_W, BMC_OBE_ROW_HEAD_H, background);
    tft.setTextColor(color);
    tft.setCursor(x, BMC_OBE_HEAD_TXT_Y);
    tft.print(buff);

    

    #if defined(BMC_HAS_TOUCH_SCREEN)
      // render a footer with controls
      bmcRenderTouchButtons buttons;
      buttons.renderV(tft);
    #endif
  }
  // @queue is used for encoders to avoid the values being unstable
  void menuCommand(uint8_t cmd, bool queue=false){
    if(cmd==0){
      return;
    }
    if(cmd==BMC_MENU_TOGGLE){
      if(confirmSave()){
        exitEditor();
        return;
      }
      if(display.midi.globals.editorConnected()){
        display.renderUnavailableBanner("Unavailable","While Editor App in Use");
        return;
      }
      display.midi.globals.toggleOnBoardEditor();
      if(display.midi.globals.onBoardEditorActive()){
        enterEditor();
      } else {
        exitEditor();
      }
      return;
    } else if(cmd==BMC_MENU_SELECT){
      if(!display.midi.globals.onBoardEditorActive()){
        menuCommand(BMC_MENU_TOGGLE);
        return;
      }
    } else if(!display.midi.globals.onBoardEditorActive()){
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
      case BMC_MENU_CANCEL:
        if(waitingForConfirmation()){
          data.saveConfirmationValue = 0;
          handleConfirmation();
        }
        break;
      case BMC_MENU_SAVE:
        if(waitingForConfirmation()){
          data.saveConfirmationValue = 1;
          handleConfirmation();
        }
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
          if(devicesEditor.hasCustomEditor(0)){
            devicesEditor.setCustomEditorMode(isEditModeActive());
            return;
          }
          if(isEditModeActive()){
            data.rowEditValue = devicesEditor.getOptionValue(data.activeRow-1);
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
              strcpy(data.headerTitle, items[data.dynamicListIndex].label);
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
    if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
      if(devicesEditor.isCompatible()){
        if(devicesEditor.hasCustomEditor(0)){
          setChangesMade(devicesEditor.setOptionValue());
        }
        devicesEditor.handlePostSaveProcessing();
      }
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
      uint16_t id = 0;
      uint16_t min = 0;
      uint16_t max = 0;
      uint8_t steps = 0;
      if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
        if(devicesEditor.isCompatible()){
          min = devicesEditor.getMin();
          max = devicesEditor.getMax();
          steps = 1;
          BMC_PRINTLN("************************ cursorPrev");
          if(devicesEditor.handleCustomValueScroller(false, shiftActive())){
            updateRows();
            return;
          }
        }
      } else if(devicesEditor.isCompatible()){
        if(devicesEditor.handleCustomRowScroller(false, shiftActive())){
          return;
        }
      }
      id = data.getActiveVisibleRow()-1;
      min = items[id].min;
      max = items[id].max;
      steps = items[id].steps;
      if((int)(data.rowEditValue-steps) < min){
        data.rowEditValue = max;
      } else {
        data.rowEditValue -= steps;
      }
      updateRows();
      return;
    }
    if(devicesEditor.isCompatible()){
      if(devicesEditor.handleCustomRowScroller(false, shiftActive())){
        return;
      }
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
      uint16_t id = 0;
      uint16_t min = 0;
      uint16_t max = 0;
      uint8_t steps = 0;
      if(flags.read(BMC_OBE_FLAGS_DYNAMIC_EDIT_LIST)){
        if(devicesEditor.isCompatible()){
          min = devicesEditor.getMin();
          max = devicesEditor.getMax();
          steps = 1;
          if(devicesEditor.handleCustomValueScroller(true, shiftActive())){
            updateRows();
            return;
          }
        }
      } else if(devicesEditor.isCompatible()){
        if(devicesEditor.handleCustomRowScroller(true, shiftActive())){
          return;
        }
      }

      id = data.getActiveVisibleRow()-1;
      min = items[id].min;
      max = items[id].max;
      steps = items[id].steps;


      if(data.rowEditValue+steps > max){
        data.rowEditValue = min;
      } else {
        data.rowEditValue += steps;
      }
      updateRows();
      return;
    }
    if(devicesEditor.isCompatible()){
      if(devicesEditor.handleCustomRowScroller(true, shiftActive())){
        return;
      }
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
  bool active(){
    return display.midi.globals.onBoardEditorActive();
  }
private:
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_TFT& tft;
  // BMC_ILI9341& tft;
  // all variables live here
  BMCOBEData data;
  BMCOBEDevices devicesEditor;
  BMCFlags <uint8_t> flags;
  const uint16_t totalMenuItems = 36;
  const BMCOBEMenuItem items[36] = {
    {{0}, BMC_OBE_ID_GO_TO, "Go To", BMC_OBE_MENU_LIST},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_PAGE, "Page", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PAGES-1, 1},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_BANK, "Bank", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PRESETS > 0?(BMC_MAX_PRESET_BANKS-1):0, 1},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_PRESET, "Preset", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PRESETS > 0?(BMC_MAX_PRESETS_PER_BANK-1):0, 1},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_SETLIST, "Setlist", BMC_OBE_EDIT_LIST, 0, BMC_MAX_SETLISTS > 0?(BMC_MAX_SETLISTS-1):0, 1},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_SONG, "Song", BMC_OBE_EDIT_LIST, 0, BMC_MAX_SETLISTS > 0?(BMC_MAX_SETLISTS_SONGS-1):0, 1},
      {{1,0}, BMC_OBE_ID_CP_GO_TO_PART, "Song Part", BMC_OBE_EDIT_LIST, 0, BMC_MAX_SETLISTS > 0?(BMC_MAX_SETLISTS_SONG_PARTS-1):0, 1},
    {{0}, BMC_OBE_ID_SETTINGS, "Settings", BMC_OBE_MENU_LIST},
      {{1,1}, BMC_OBE_ID_SETTINGS_GENERAL, "General", BMC_OBE_MENU_LIST},
        {{2,1,0}, BMC_OBE_ID_S_BTN_HOLD_TIME, "Button Hold Time", BMC_OBE_EDIT_LIST, 0, 15, 1},
        {{2,1,0}, BMC_OBE_ID_S_DISPLAY_OFFSET, "Display Offset to 0", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_DISPLAY_BANNERS, "Display Banner", BMC_OBE_EDIT_LIST, 0, 3, 1},
        {{2,1,0}, BMC_OBE_ID_S_PREPEND_PRESET, "Prepend Preset", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_PREPEND_BANK, "Prepend Bank", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_DIM_LEDS, "Dim Off LEDs", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_STARTUP_PRESET, "Startup Preset", BMC_OBE_EDIT_LIST, 0, BMC_MAX_PRESETS-1, 1},
        {{2,1,0}, BMC_OBE_ID_S_TRIG_1ST_SONG, "Trigger 1st Song", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_TRIG_1ST_PART, "Trigger 1st Song Part", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,0}, BMC_OBE_ID_S_TOUCH_CALIBRATED, "Touch Calibrated", BMC_OBE_EDIT_LIST, 0, 1, 1},
      {{1,1}, BMC_OBE_ID_SETTINGS_MIDI, "MIDI", BMC_OBE_MENU_LIST},
        {{2,1,1}, BMC_OBE_ID_S_IN_CTRL, "MIDI In Control", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,1}, BMC_OBE_ID_S_IN_CTRL_CH, "MIDI In Ctrl Channel", BMC_OBE_EDIT_LIST, 0, 16, 1},
        {{2,1,1}, BMC_OBE_ID_S_IN_CTRL_ACTION, "MIDI In Ctrl Action", BMC_OBE_EDIT_LIST, 0, 2, 1},
        {{2,1,1}, BMC_OBE_ID_S_CLOCK_IN_PORT,  "MIDI Clock Input Port", BMC_OBE_EDIT_LIST, 0, BMC_TOTAL_AVAILABLE_PORTS-1, 1},
        {{2,1,1}, BMC_OBE_ID_S_MASTER_CLOCK, "MIDI Master Clock", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,1}, BMC_OBE_ID_S_ACTIVE_SENSE, "MIDI Active Sense", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,1}, BMC_OBE_ID_S_BLOCK_RT_IN, "MIDI Block RT In", BMC_OBE_EDIT_LIST, 0, 1, 1},
        {{2,1,1}, BMC_OBE_ID_S_BLOCK_RT_OUT, "MIDI Block RT Out", BMC_OBE_EDIT_LIST, 0, 1, 1},
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
    char str[40] = "";
    return editorValueHandler(id, str, false, false);
  }
  void setEditorValue(uint16_t id){
    char str[40] = "";
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
        originalValue = display.midi.globals.settings.getButtonHoldThreshold();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setButtonHoldThreshold(value);
        }
        sprintf(str, "%u ms", (value+2)*250);
        return value;
      case BMC_OBE_ID_S_DISPLAY_OFFSET:
        originalValue = display.midi.globals.settings.getDisplayOffset();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setDisplayOffset(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_DISPLAY_BANNERS:
        originalValue = display.midi.globals.settings.getDisplayBannerTimeout();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setDisplayBannerTimeout(value);
        }
        if(value == 0){
          strcpy(str, "Disabled");
        } else {
          sprintf(str, "%u ms", value * 500);
        }
        return value;
      case BMC_OBE_ID_S_PREPEND_PRESET:
        originalValue = display.midi.globals.settings.getAppendPresetNumberToPresetName();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setAppendPresetNumberToPresetName(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_PREPEND_BANK:
        originalValue = display.midi.globals.settings.getDisplayBankWithPreset();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setDisplayBankWithPreset(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_DIM_LEDS:
        originalValue = display.midi.globals.settings.getPwmDimWhenOff();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setPwmDimWhenOff(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_STARTUP_PRESET:
        originalValue = display.midi.globals.settings.getStartupPreset();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setStartupPreset(value);
        }
        if(value==0){
          strcpy(str, "None");
        } else {
          BMCTools::getPresetLabel((value-1), str, display.midi.globals.store.global);
        }
        return value;
      case BMC_OBE_ID_S_TRIG_1ST_SONG:
        originalValue = display.midi.globals.settings.getSetListTriggerFirstSong();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setSetListTriggerFirstSong(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_TRIG_1ST_PART:
        originalValue = display.midi.globals.settings.getSetListTriggerFirstSongPart();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setSetListTriggerFirstSongPart(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_TOUCH_CALIBRATED:
        originalValue = display.midi.globals.settings.getTouchScreenIsCalibrated();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setTouchScreenIsCalibrated(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      
      // MIDI MENU
      case BMC_OBE_ID_S_IN_CTRL: // 
        originalValue = display.midi.globals.settings.getIncomingListenerEnabled();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setIncomingListenerEnabled(value);
        }
        strcpy(str, data.onOffLabels[value]);
        return value;
      case BMC_OBE_ID_S_IN_CTRL_CH:
        originalValue = display.midi.globals.settings.getListenerChannel();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setListenerChannel(value);
        }
        if(value==0){
          strcpy(str, "Omni");
        } else {
          sprintf(str, "Channel %u", value);
        }
        return value;
      case BMC_OBE_ID_S_IN_CTRL_ACTION:
        originalValue = display.midi.globals.settings.getIncomingProgramType();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setIncomingProgramType(value);
        }
        switch(value){
          case 0: strcpy(str, "None"); break;
          case 1: strcpy(str, "Change Page"); break;
          case 2: strcpy(str, "Change Preset"); break;
        }
        return value;
      case BMC_OBE_ID_S_CLOCK_IN_PORT:
        originalValue = display.midi.globals.settings.getClockInputPortBit();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setClockInputPortBit(value);
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
        originalValue = display.midi.globals.settings.getMasterClock();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setMasterClock(value);
        }
        strcpy(str, data.onOffLabels[value]);
        return value;
      case BMC_OBE_ID_S_ACTIVE_SENSE:
        originalValue = display.midi.globals.settings.getActiveSenseAtStartup();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setActiveSenseAtStartup(value);
        }
        strcpy(str, data.onOffLabels[value]);
        return value;
      case BMC_OBE_ID_S_BLOCK_RT_IN:
        originalValue = display.midi.globals.settings.getMidiRealTimeBlockInput();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setMidiRealTimeBlockInput(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      case BMC_OBE_ID_S_BLOCK_RT_OUT:
        originalValue = display.midi.globals.settings.getMidiRealTimeBlockOutput();
        value = (!active) ? originalValue : value;
        if(setValue && setChangesMade(originalValue, value)){
          display.midi.globals.settings.setMidiRealTimeBlockOutput(value);
        }
        strcpy(str, data.yesNoLabels[value]);
        return value;
      // change pages
      case BMC_OBE_ID_CP_GO_TO_PAGE:
        {
          originalValue = display.midi.globals.page;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.page = value;
            display.midi.globals.setReloadPage(true);
            forceExitEditor();
            return value;
          }
          char buff[BMC_MAX_NAMES_LENGTH] = "";
          editor.getDeviceNameText(BMC_DEVICE_ID_PAGE, value, buff);
          sprintf(str, "#%u %s", value+(display.midi.globals.settings.getDisplayOffset()?0:1), buff);
          return value;
        }
      case BMC_OBE_ID_CP_GO_TO_BANK:
      #if BMC_MAX_PRESETS > 0
        {
          originalValue = display.midi.globals.bank;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.bank = value;
            display.midi.globals.setTriggerBank(true);
            return value;
          }
          char buff[3] = "";
          BMCTools::getBankLetter(value, buff);
          strcpy(str, buff);
          return value;
        }
      #else
        return 0;
      #endif
      case BMC_OBE_ID_CP_GO_TO_PRESET:
      #if BMC_MAX_PRESETS > 0
        {
          originalValue = display.midi.globals.preset;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.preset = value;
            display.midi.globals.setTriggerPreset(true);
            return value;
          }
          char buff[BMC_MAX_NAMES_LENGTH] = "";
          uint16_t p = BMCTools::toPresetIndex(display.midi.globals.preset, value);
          editor.getDeviceNameText(BMC_DEVICE_ID_PRESET, p, buff);
          sprintf(str, "#%u %s", value+(display.midi.globals.settings.getDisplayOffset()?0:1), buff);
          return value;
        }
      #else
        return 0;
      #endif
      case BMC_OBE_ID_CP_GO_TO_SETLIST:
      #if BMC_MAX_SETLISTS > 0
        {
          originalValue = display.midi.globals.setList;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.setList = value;
            display.midi.globals.setTriggerSetList(true);
            return value;
          }
          char buff[BMC_MAX_NAMES_LENGTH] = "";
          editor.getDeviceNameText(BMC_DEVICE_ID_SETLIST, value, buff);
          sprintf(str, "#%u %s", value+(display.midi.globals.settings.getDisplayOffset()?0:1), buff);
          return value;
        }
      #else
        return 0;
      #endif
      case BMC_OBE_ID_CP_GO_TO_SONG:
      #if BMC_MAX_SETLISTS > 0
        {
          originalValue = display.midi.globals.song;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.song = value;
            display.midi.globals.setTriggerSong(true);
            return value;
          }
          char buff[BMC_MAX_NAMES_LENGTH] = "";
          uint16_t s = display.midi.globals.store.global.setLists[display.midi.globals.setList].events[value];
          if(s > 0){
            editor.getDeviceNameText(BMC_DEVICE_ID_SETLIST_SONG_LIBRARY, s, buff);
          } else {
            strcpy(buff, "*empty");
          }
          sprintf(str, "#%u %s", value+(display.midi.globals.settings.getDisplayOffset()?0:1), buff);
          return value;
        }
      #else
        return 0;
      #endif
      case BMC_OBE_ID_CP_GO_TO_PART:
      #if BMC_MAX_SETLISTS > 0
        {
          originalValue = display.midi.globals.songPart;
          value = (!active) ? originalValue : value;
          if(setValue && originalValue != value){
            display.midi.globals.songPart = value;
            display.midi.globals.setTriggerPart(true);
            return value;
          }
          char buff[BMC_MAX_NAMES_LENGTH] = "";
          uint16_t p = display.midi.globals.store.global.songLibrary[display.midi.globals.songInLibrary].events[value];
          if(p > 0){
            editor.getDeviceNameText(BMC_DEVICE_ID_PRESET, p, buff);
          } else {
            strcpy(buff, "*empty");
          }
          sprintf(str, "#%u %s", value+(display.midi.globals.settings.getDisplayOffset()?0:1), buff);
          return value;
        }
      #else
        return 0;
      #endif

      
      default:
        break;
    }
    strcpy(str, "undefined");
    return 0;
  }
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
    display.midi.globals.setDisplayRenderDisable(true);
    display.midi.globals.setOnBoardEditorActive(true);
    tft.setFont(BMC_OBE_ROW_FONT);
    tft.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
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
      tft.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
      renderConfirmSave();
      return;
    }
    display.midi.globals.setDisplayRenderDisable(false);
    display.midi.globals.setOnBoardEditorActive(false);
    reset();
    // tft.setFontAdafruit();
    // tft.setFont(BMCLiberationSansNarrow_16);
    tft.setFont(BMCLiberationSansNarrow_24);
    tft.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    display.reassign();
  }

  void renderConfirmSave(){
    tft.fillRect(0, 0, BMC_TFT_WIDTH, BMC_TFT_HEIGHT, BMC_ILI9341_BLACK);
    char buff[18] = "Save Changes?";
    tft.setFont(BMC_OBE_CONFIRMATION_FONT);
    uint16_t x = getCenteredX(buff);
    uint16_t y = BMC_OBE_SAVE_CONFIRM_Y;
    tft.setTextColor(BMC_ILI9341_WHITE);
    tft.setCursor(x, y);
    tft.print(buff);
    bmcRenderExitButtons exitButtons;
    exitButtons.render(tft, data.saveConfirmationValue);
  }
  void handleConfirmation(){
    // get input value
    tft.fillScreen(BMC_ILI9341_BLACK);
    char buff[17] = "";
    strcpy(buff, data.saveConfirmationValue==1 ? "Saving..." : "No Changes Saved");
    tft.setFont(BMC_OBE_CONFIRMATION_FONT);
    uint16_t x = getCenteredX(buff);
    tft.setTextColor(BMC_ILI9341_WHITE);
    tft.setCursor(x, BMC_OBE_SAVE_CONFIRM_Y);
    tft.print(buff);
    if(data.saveConfirmationValue){
      editor.saveEEPROM();
    } else {
      editor.reloadPreviouslySavedStore();
    }
    display.midi.globals.setAssignStoreData(true);
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
    int16_t textWidth = tft.strPixelLen(buff);
    int16_t x = (BMC_OBE_W-textWidth) / 2;
    return (x < 0) ? 0 : x;
  }
};
#endif
#endif