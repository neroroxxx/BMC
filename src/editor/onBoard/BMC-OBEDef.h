/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_DEF_H
#define BMC_OBE_DEF_H

#include "utility/BMC-Def.h"



#define BMC_COLOR_EDITOR_GRAY 0x18C3
#define BMC_COLOR_EDITOR_TXT 0xDEFB

// 7=diamond, 14=music note, 16=carret right, 26=arrow right
#define BMC_OBE_SEL_CHAR_HEART 3
#define BMC_OBE_SEL_CHAR_DIAMOND 7
#define BMC_OBE_SEL_CHAR_MUSIC 14
#define BMC_OBE_SEL_CHAR_CARET 16
#define BMC_OBE_SEL_CHAR_ARROW 26

#define BMC_OBE_SEL_CHAR BMC_OBE_SEL_CHAR_ARROW

#define BMC_OBE_MAX_LEVELS 8

// menu types
#define BMC_OBE_MENU_LIST             0
#define BMC_OBE_EDIT_LIST             1
#define BMC_OBE_MENU_DYNAMIC_LIST     2
#define BMC_OBE_MENU_DYNAMIC_EDIT     3

// display dimensions
#define BMC_OBE_W 320
#define BMC_OBE_H 240

// MENU HEADER
// header height
#define BMC_OBE_ROW_HEAD_H 32
// header font
//#define BMC_OBE_HEAD_FONT BMCLiberationSansNarrow_18_Bold
#define BMC_OBE_HEAD_FONT Arial_18_Bold
// y coordinate of header text
#define BMC_OBE_HEAD_TXT_Y 7
// header background color
#define BMC_OBE_HEAD_BACKGROUND 0xCC21
// header text color
#define BMC_OBE_HEAD_COLOR BMC_ILI9341_BLACK
// header text color
#define BMC_OBE_HEAD_SEL_COLOR BMC_ILI9341_WHITE

// ********************************************************
// MENU ITEMS LIST
// height of area that list fits into
#define BMC_OBE_ROW_AREA (BMC_OBE_H-BMC_OBE_ROW_HEAD_H)
// list font
//#define BMC_OBE_ROW_FONT BMCLiberationSansNarrow_18
#define BMC_OBE_ROW_FONT Arial_16
#define BMC_OBE_ROW_SEL_FONT Arial_16_Bold
// y coordinate of text inside each list item
#define BMC_OBE_ROW_TXT_Y 5
// how many items will fit in the list, this must be a float
#define BMC_OBE_ROWS_PER_PAGE 4
// height of every list item
#define BMC_OBE_ROW_H ((uint16_t)(BMC_OBE_ROW_AREA/BMC_OBE_ROWS_PER_PAGE))
// header background color
//#define BMC_OBE_ROW_BACKGROUND 0x0841
#define BMC_OBE_ROW_BACKGROUND 0x0000
// header text color
//#define BMC_OBE_ROW_COLOR BMC_ILI9341_WHITE
#define BMC_OBE_ROW_COLOR BMC_ILI9341_GRAY_22
// lines between rows
#define BMC_OBE_ROW_DIVIDER BMC_ILI9341_BLACK

//#define BMC_OBE_ROW_VALUE_FONT BMCLiberationSansNarrow_16_Bold
#define BMC_OBE_ROW_VALUE_FONT Arial_14
#define BMC_OBE_ROW_SEL_VALUE_FONT Arial_14_Bold

#define BMC_OBE_SIDEBAR_WIDTH 8
#define BMC_OBE_CARET_BOX_X (BMC_OBE_W - BMC_OBE_SIDEBAR_WIDTH - 24)
#define BMC_OBE_CARET_CHAR_X (BMC_OBE_W - BMC_OBE_SIDEBAR_WIDTH - 20)


#define BMC_OBE_HEAD_SEL_BACKGROUND  0xfa80

// background color when you select an item for editing
#define BMC_OBE_ROW_EDITABLE_BACKGROUND 0x680d

//#define BMC_OBE_ROW_EDITABLE_BACKGROUND 0xA801
// header text color
#define BMC_OBE_ROW_EDITABLE_COLOR 0xDEFB
//#define BMC_OBE_ROW_EDITABLE_COLOR 0x0194
// header text color
#define BMC_OBE_ROW_EDITING_COLOR 0xff40


// header background color
//#define BMC_OBE_SEL_BACKGROUND 0xB801
//#define BMC_OBE_SEL_BACKGROUND 0x3186
//#define BMC_OBE_SEL_BACKGROUND 0x0841
#define BMC_OBE_SEL_BACKGROUND BMC_ILI9341_GRAY_1

// header text color
#define BMC_OBE_SEL_COLOR 0xFFFF

#define BMC_OBE_BORDER_RADIUS 9


// header font
#define BMC_OBE_CONFIRMATION_FONT BMCLiberationSansNarrow_24_Bold





#define BMC_OBE_LEVEL_MAIN 0
#define BMC_OBE_LEVEL_SETTINGS 1
#define BMC_OBE_LEVEL_EVENTS 2
#define BMC_OBE_LEVEL_NAMES 3
#define BMC_OBE_LEVEL_DEVICES 4
#define BMC_OBE_LEVEL_PAGES 5
#define BMC_OBE_LEVEL_NAMES_EDITOR 6


#define BMC_OBE_DEVICE_OPT_LABEL         	 0
#define BMC_OBE_DEVICE_OPT_VALUE         	 1
#define BMC_OBE_DEVICE_OPT_EDITED_VALUE  	 2
#define BMC_OBE_DEVICE_OPT_MIN           	 3
#define BMC_OBE_DEVICE_OPT_MAX           	 4
#define BMC_OBE_DEVICE_OPT_CHANGED       	 5
#define BMC_OBE_DEVICE_CUSTOM_SCROLL_UP  	 6
#define BMC_OBE_DEVICE_CUSTOM_SCROLL_DOWN	 7
#define BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_UP 8
#define BMC_OBE_DEVICE_CUSTOM_ROW_SCROLL_DOWN 9
#define BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR   10
#define BMC_OBE_DEVICE_OPT_CUSTOM_EDITOR_MODE 11





// main
#define BMC_OBE_ID_SETTINGS        	 1
// main > settings
#define BMC_OBE_ID_SETTINGS_GENERAL	 2
// main > settings > general
#define BMC_OBE_ID_S_BTN_HOLD_TIME 	 3
#define BMC_OBE_ID_S_STARTUP_PRESET	 4
#define BMC_OBE_ID_S_DIM_LEDS      	 5
#define BMC_OBE_ID_S_DISPLAY_OFFSET	 6
#define BMC_OBE_ID_S_TRIG_1ST_SONG 	 7
#define BMC_OBE_ID_S_TRIG_1ST_PART 	 8
// main > settings
#define BMC_OBE_ID_SETTINGS_MIDI   	 9
// main > settings > general
#define BMC_OBE_ID_S_IN_CTRL       	 10
#define BMC_OBE_ID_S_IN_CTRL_CH    	 11
#define BMC_OBE_ID_S_IN_CTRL_ACTION	 12
#define BMC_OBE_ID_S_CLOCK_IN_PORT 	 13
#define BMC_OBE_ID_S_MASTER_CLOCK  	 14
#define BMC_OBE_ID_S_ACTIVE_SENSE  	 15
#define BMC_OBE_ID_S_BLOCK_RT_IN   	 16
#define BMC_OBE_ID_S_BLOCK_RT_OUT  	 17
// main
#define BMC_OBE_ID_CHANGE_PAGE     	 18
// main > change page
#define BMC_OBE_ID_CP_GO_TO_PAGE   	 19
// main
#define BMC_OBE_ID_GLOBAL          	 20
// main > global
#define BMC_OBE_ID_GLOBAL_ITEMS    	 21
// main > global > items
#define BMC_OBE_ID_G_ITEM_LIST     	 22
// main > global > items > editor
#define BMC_OBE_ID_G_ITEM_EDIT     	 23
// main
#define BMC_OBE_ID_PAGES           	 24
// main > pages
#define BMC_OBE_ID_PAGES_ITEMS     	 25
// main > pages > items
#define BMC_OBE_ID_P_ITEM_LIST     	 26
// main > pages > items > editor
#define BMC_OBE_ID_P_ITEM_EDIT     	 27



struct BMCOBEMenuItem {
  int16_t level[BMC_OBE_MAX_LEVELS] = {0,-1,-1,-1,-1,-1,-1,-1};
  uint16_t id = 0;
  char label[25] = "";
  uint8_t type = 0; // 0=not editable, 1=editable
  uint8_t min = 0;
  uint16_t max = 0;
  uint8_t steps = 0;
};
struct BMCOBEData {
  BMCDeviceData activeDevice;
  BMCTimer encoderQueue;
  uint8_t queueAction = 0;
  char headerTitle[33] = "";
  uint16_t level[BMC_OBE_MAX_LEVELS];
  int16_t lastRowPage[BMC_OBE_MAX_LEVELS];
  //int16_t lastMaxRowPages[BMC_OBE_MAX_LEVELS];
  int8_t lastActiveRow[BMC_OBE_MAX_LEVELS];
  uint16_t visibleRowId[BMC_OBE_ROWS_PER_PAGE];
  uint8_t visibleRowIdLength = 0;
  uint16_t rowEditValue = 0;
  uint16_t rowId = 0;
  uint8_t deviceType = 0;
  uint16_t deviceIndex = 0;

  int16_t rowPage = 0;
  int16_t maxRowPages = 0;
  int8_t activeRow = 1;
  int8_t activeRowPrev = 1;

  uint16_t totalRows = 0;
  uint16_t dynamicListIndex = 0;
  bool saveConfirmationValue = false;
  uint8_t availablePorts = 0;
  uint8_t availablePortsData[7];
  bool namesEditorActive = false;
  bool triggerHeaderRender = false;
  const char onOffLabels[2][4] = {
    "Off",
    "On"
  };
  const char yesNoLabels[2][4] = {
    "No",
    "Yes"
  };
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
  }
  uint8_t update(){
    if(encoderQueue.complete()){
      uint8_t t_queueAction = queueAction;
      queueAction = 0;
      if(t_queueAction!=0){
        encoderQueue.start(activeRow == 1 && t_queueAction==1 ? 500 : 200);
      }
      return t_queueAction;
    }
    return 0;
  }
  void queuePrev(){
    if(!encoderQueue.active()){
      queueAction = 1;
      encoderQueue.start(50);
    }
  }
  void queueNext(){
    if(!encoderQueue.active()){
      queueAction = 2;
      encoderQueue.start(50);
    }
  }
  void resetQueue(){
    queueAction = 0;
    encoderQueue.stop();
  }
  uint16_t getActiveVisibleListItem(){
    if(activeRow>0){
      return visibleRowId[activeRow-1];
    }
    return 0;
  }
  void addToVisibleList(uint16_t value){
    visibleRowId[visibleRowIdLength++] = value;
  }
  uint16_t getActiveVisibleRow(){
    return visibleRowId[activeRow-1];
  }
  bool updatePreviousRow(){
    return activeRow != activeRowPrev;
  }
  bool isHeaderSelected(){
    return activeRow == 0;
  }
  uint8_t getCurrentLevel(){
    return level[0];
  }
  bool renderHead(){
    return triggerHeaderRender;
  }
  void setCurrentLevelValue(uint8_t value){
    level[getCurrentLevel()] = value;
  }
  // return true to update rows
  // return false to go to next page of list
  bool cursorPrev(){
    // store the last row that was selected
    activeRowPrev = activeRow;
    // decrease row value
    activeRow--;
    if(maxRowPages == 1){
      if(activeRow < 0){
        activeRow = visibleRowIdLength;
      }
    } else {
      if(activeRow < 0){
        return false;
      }
    }
    return true;
  }
  bool prevListPage(){
    // store the last row that was selected
    if(maxRowPages == 1){
      if(activeRow < visibleRowIdLength){
        activeRow = visibleRowIdLength;
        //updateRows();
        //return false;
      }
    } else {
      activeRow = visibleRowIdLength;
      if(rowPage > 0){
        rowPage--;
      } else {
        rowPage = maxRowPages-1;
      }
      return true;
      //render();
    }
    return false;
  }
  // return true to update rows
  // return false to go to next page of list
  bool cursorNext(){
    // store the last row that was selected
    activeRowPrev = activeRow;
    // increase row value
    activeRow++;
    if(maxRowPages == 1){
      if(activeRow > visibleRowIdLength){
        activeRow = 1;
      }
    } else {
      if(activeRow > visibleRowIdLength){
        return false;
      }
    }
    return true;
  }
  bool nextListPage(){
    // store the last row that was selected
    if(maxRowPages == 1){
      if(activeRow > 0){
        activeRow = 1;
        //updateRows();
      }
    } else {
      activeRow = 1;
      if(rowPage < (maxRowPages-1)){
        rowPage++;
      } else {
        rowPage = 0;
      }
      //render();
      return true;
    }
    return false;
  }
  // return false when you are on the main menu
  // return true when it's not the main menu
  bool setNextMenuLevel(){
    uint16_t currentLevel = level[0];
    if(currentLevel==0){
      level[0]++;
      level[1] = activeRow-1;
      lastRowPage[0] = 0;
      lastActiveRow[0] = activeRow;
      return false;
    }
    level[0] = currentLevel+1;
    level[currentLevel+1] = activeRow-1;
    lastRowPage[currentLevel] = rowPage;
    lastActiveRow[currentLevel] = activeRow;
    return true;
  }
  void resetActiveRow(){
    activeRow = 1;
    activeRowPrev = 1;
    rowPage = 0;
  }
  uint8_t getLastActiveRow(){
    return activeRow;
  }
  void setPreviousMenuLevel(){
    namesEditorActive = false;
    triggerHeaderRender = false;
    if(level[0] == 0){
      return;
    }
    level[level[0]] = 0;
    level[0]--;
    uint8_t currentLevel = level[0];
    activeRow = lastActiveRow[currentLevel];
    activeRowPrev = lastActiveRow[currentLevel];
    rowPage = lastRowPage[currentLevel];
  }
  void toggleConfirmationValue(){
    saveConfirmationValue = !saveConfirmationValue;
  }
  void reset(){
    memset(level, 0, BMC_OBE_MAX_LEVELS);
    memset(lastRowPage, 0, BMC_OBE_MAX_LEVELS);
    //memset(lastMaxRowPages, 0, BMC_OBE_MAX_LEVELS);
    memset(lastActiveRow, 0, BMC_OBE_MAX_LEVELS);
    memset(visibleRowId, 0, BMC_OBE_ROWS_PER_PAGE);
    visibleRowIdLength = 0;
    rowEditValue = 0;
    rowId = 0;
    deviceType = 0;
    deviceIndex = 0;

    rowPage = 0;
    totalRows = 0;
    activeRow = 1;
    
    activeRowPrev = 1;
    maxRowPages = 0;
    dynamicListIndex = 0;
    saveConfirmationValue = false;
    namesEditorActive = false;
    triggerHeaderRender = false;

    BMCDeviceData e;
    activeDevice = e;
  }
};


#endif