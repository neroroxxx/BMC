/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DISPLAY_H
#define BMC_DISPLAY_H
#include "utility/BMC-Def.h"


#if defined(BMC_HAS_DISPLAY)

// lighter gray 0x39C7
#define BMC_ILI9341_VU_GREY 0x39C7

#define BMC_ILI9341_FADER_ACTIVE 0xC81F
#define BMC_ILI9341_FADER_GREY 0x18C3
#define BMC_ILI9341_VU_METER_W 23 // 33 for full width
#define BMC_ILI9341_VU_METER_H 4

#define BMC_ILI9341_VU_METER_X 2
#define BMC_ILI9341_VU_METER_Y 3

class BMCDisplay {
public:
  BMCDisplay(BMCMidi& t_midi, BMCGlobals& t_globals, BMCCallbacks& cb
    #ifdef BMC_USE_SYNC
      ,BMCSync& t_sync
    #endif
  ):midi(t_midi),globals(t_globals), callback(cb)
    #ifdef BMC_USE_SYNC
      ,sync(t_sync)
    #endif
  {

  }
  void begin(){
    BMC_PRINTLN("BMCDisplay::begin()");
#if defined(BMC_USE_DAW_LC)
    dawChannelsBlock = -1;
    dawMetersBlock = -1;
    dawVuOverload = 0;
    dawSelectedTrack = -1;
    memset(dawVPotLevel, 0, 8);
    memset(dawVPotBits, 0, 8);
    memset(dawVuLevel, 0, 8);
    memset(dawVuLevelBits, 0, 8);
    memset(dawFaderLevel, 0, 8);
    
    memset(dawChStates, 0, 8);
    for(uint8_t i=0;i<8;i++){
      memset(dawChName[i], 0, 8);
    }
#endif
#if BMC_MAX_OLED > 0
    initOled();
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
    initILI9341();
#endif
  }

#if BMC_MAX_ILI9341_BLOCKS > 0
  void initILI9341(){
    BMC_PRINTLN("BMCDisplay::initILI9341()");
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, -1);
    //tft.begin(BMCBuildData::getIliDisplayPosition(2));
    tft.begin(ui.rotation);
    tft.clear();
    /*
    uint8_t textSize = 3;
    tft.display.setTextSize(textSize);
    while(1){
      tft.clear();
      for(uint8_t i=1;i<32;i++){
        tft.display.setCursor(10, 10);
        tft.display.print(i);
        tft.display.setTextColor(0xFFFF, 0);
        tft.display.drawChar(10, (textSize*8)+20, (char) i, 0xFFFF, 0, textSize);
        delay(1000);
      }
    }
    */
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      block[i].begin(i);
    }
     //7 16 26
  }
#endif

#if BMC_MAX_OLED > 0
  void initOled(){
    BMC_PRINTLN("BMCDisplay::initOled()");
    #if BMC_MAX_OLED > 1
      Wire.begin();
    #endif
      for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
        // display can be address 0x3C or 0x3D
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_OLED, i);
        //uint8_t addr = 0x3C + BMCBuildData::getOledDisplayPosition(i, 3);
        //uint8_t rotation = BMCBuildData::getOledDisplayPosition(i, 2);
    #if BMC_MAX_OLED > 1
        selectMux(i);
    #endif
        //oled[i].begin(BMC_SSD1306_SWITCHCAPVCC, addr, rotation);
        //ui.other1 = address, ui.other2 = mux port
        oled[i].begin(BMC_SSD1306_SWITCHCAPVCC, 0x3C + ui.other1, ui.rotation);
      }
  }
#endif
  void reassign(uint8_t page){
      
      memset(last, 0, BMC_MAX_OLED+BMC_MAX_ILI9341_BLOCKS);
#if defined(BMC_USE_DAW_LC)
      dawChannelsBlock = -1;
      dawMetersBlock = -1;
      dawVuOverload = 0;
      dawSelectedTrack = -1;
      memset(dawVPotLevel, 0, 8);
      memset(dawVPotBits, 0, 8);
      memset(dawVuLevel, 0, 8);
      memset(dawVuLevelBits, 0, 8);
      memset(dawFaderLevel, 0, 8);
      memset(dawChStates, 0, 8);
      for(uint8_t i=0;i<8;i++){
        memset(dawChName[i], 0, 8);
      }
#endif

#if defined(BMC_USE_ON_BOARD_EDITOR)
    if(globals.onBoardEditorActive()){
      return;
    }
#endif
    clearAll();

#if BMC_MAX_ILI9341_BLOCKS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
#if defined(BMC_USE_DAW_LC)
      bmcStoreEvent e = globals.getDeviceEventType(globals.store.pages[page].ili[i].events[0]);
      if(e.type == BMC_EVENT_TYPE_DAW_DISPLAY){
        if(BMC_GET_BYTE(0, e.event) == 0){
          // make sure this is a 320 x 80 block
          BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, i);
          if(dawMetersBlock == -1 && ui.style == 0){
            dawMetersBlock = i;
            initDawMeters();
          }
        } else if(BMC_GET_BYTE(0, e.event) == 1){
          BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, i);
          if(dawChannelsBlock == -1 && ui.style == 0){
            dawChannelsBlock = i;
            initDawChannels();
          }
        }
      }
#endif
    }
#endif
  }
#if defined(BMC_USE_DAW_LC)
  #if BMC_MAX_ILI9341_BLOCKS > 0
  void initDawMeters(){
    if(dawMetersBlock==-1){
      return;
    }
    BMC_PRINTLN("BMCDisplay::initDawMeters");
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t y = block[dawMetersBlock].getY();
    uint8_t faderLength = (BMC_ILI9341_VU_METER_H+1)*13;
    // clear the block
    tft.display.fillRect(x, y, 320, 80, BMC_ILI9341_BLACK);
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint16_t bX = (x + 7) + (i*39);
      uint16_t bY = y+BMC_ILI9341_VU_METER_Y;
      // VU METERS
      for(uint8_t e = 0 ; e < 13 ; e++){
        tft.display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
      }
      uint16_t faderX = bX + BMC_ILI9341_VU_METER_X + BMC_ILI9341_VU_METER_W + 4;
      tft.display.fillRect(faderX, bY, 4, faderLength, BMC_ILI9341_FADER_GREY);;
    }
  }
  void updateDawMeters(){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    if(globals.onBoardEditorActive()){
      return;
    }
#endif
    if(dawMetersBlock==-1){
      return;
    }
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t  y = block[dawMetersBlock].getY();
    uint8_t tY = (y+80)-8;
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    uint8_t faderLength = (BMC_ILI9341_VU_METER_H+1)*13;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t value = sync.daw.controller.getMeter(i);
      int faderLevel16 = sync.daw.controller.getVolume(i);
      uint8_t faderLevel = map(faderLevel16, -8192, 6651, 0, 65);
      uint8_t overload = sync.daw.controller.getMeterOverload(i);
      // for testing
      uint16_t bX = (x + 7) + (i*39);
      uint16_t bY = y+BMC_ILI9341_VU_METER_Y;
      if(dawVuLevel[i] != value){
        for(int8_t e = 13 ; e --> 1 ;){
          int8_t ee = abs(e-12)+1;
          bool l = sync.daw.controller.getMeter(i, ee)>0;
          if(bitRead(dawVuLevelBits[i], e) != l){
            if(l){
              uint16_t color = BMC_ILI9341_YELLOW;
              if(ee < 6){
                color = BMC_ILI9341_GREEN;
              } else if(ee < 10){
                color = BMC_ILI9341_GREENYELLOW;
              } else if(ee < 12){
                color = BMC_ILI9341_ORANGE;
              }
              tft.display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, color);
            } else {
              tft.display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
            }
            bitWrite(dawVuLevelBits[i], e, l);
          }
        }
        dawVuLevel[i] = value;
      }
      if(bitRead(dawVuOverload, i)!= overload){
        if(overload){
          tft.display.fillRect(bX, bY, 33, BMC_ILI9341_VU_METER_H, BMC_ILI9341_RED);
        } else {
          tft.display.fillRect(bX, bY, 33, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
        }
        bitWrite(dawVuOverload, i, overload);
      }
      if(dawFaderLevel[i] != faderLevel){
        uint16_t faderX = bX + BMC_ILI9341_VU_METER_X + BMC_ILI9341_VU_METER_W + 4;
        tft.display.fillRect(faderX, bY, 4, faderLength, BMC_ILI9341_FADER_GREY);
        if(faderLevel > 0){
          uint16_t faderY = (bY+faderLength) - faderLevel;
          uint8_t faderH = faderLength - (faderLength-faderLevel);
          if(faderH > 0){

            tft.display.fillRect(faderX, faderY, 4, faderH, faderLevel==4251?BMC_ILI9341_WHITE:BMC_ILI9341_FADER_ACTIVE);
          }
        }
        dawFaderLevel[i] = faderLevel;
      }
      bmcStoreName t = sync.daw.getLcdTrackName(i);
      // update the track name if this track was the last selected
      // or the currently selected track
      bool isSel = ((sel==i || dawSelectedTrack==i) && dawSelectedTrack != sel);

      if(strlen(dawChName[i]) != strlen(t.name) || !BMC_STR_MATCH(dawChName[i], t.name) || isSel){
        tft.display.setTextSize(1);
        tft.display.setCursor(bX, tY);
        tft.display.setTextColor(BMC_ILI9341_BLACK);
        tft.display.print(dawChName[i]);
        tft.display.setCursor(bX, tY);
        tft.display.setTextColor(sel == i ? BMC_ILI9341_YELLOW : BMC_ILI9341_WHITE);
        tft.display.print(t.name);
        strcpy(dawChName[i], t.name);
      }
    }
    dawSelectedTrack = sel;
  }

  void initDawChannels(){
    if(dawChannelsBlock==-1){
      return;
    }
    BMC_PRINTLN("BMCDisplay::initDawChannels");
    uint16_t x = block[dawChannelsBlock].getX();
    uint8_t y = block[dawChannelsBlock].getY();
    // clear the block
    tft.display.fillRect(x, y, 320, 80, BMC_ILI9341_BLACK);
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint16_t bX = (x + 7) + (i*39);
      //uint16_t bY = y+BMC_ILI9341_VU_METER_Y;
      // VPOT
      uint8_t vuHeight = 9;
      uint16_t vuWidth = 3;
      for(uint8_t e = 0 ; e < 11 ; e++){
        if(e < 6){ // decrease
          vuHeight -= e > 0 ? 1 : 0;
        } else {// increase
          vuHeight += 1;
        }
        tft.display.fillRect(bX + (vuWidth*e), y+6, vuWidth, vuHeight, BMC_ILI9341_VU_GREY);
      }

      uint8_t buttonsY = y+6;

      tft.display.setTextSize(1);
      tft.display.setTextColor(BMC_ILI9341_VU_GREY);

      tft.display.fillRect(bX, buttonsY+16, 33, 16, BMC_ILI9341_BLACK);
      tft.display.drawRect(bX, buttonsY+16, 33, 16, BMC_ILI9341_VU_GREY);
      tft.display.setCursor(bX+8, buttonsY + 20);
      tft.display.print("REC");

      tft.display.fillRect(bX, buttonsY+36, 33, 16, BMC_ILI9341_BLACK);
      tft.display.drawRect(bX, buttonsY+36, 33, 16, BMC_ILI9341_VU_GREY);
      tft.display.setCursor(bX+5, buttonsY + 40);
      tft.display.print("SOLO");

      tft.display.fillRect(bX, buttonsY+56, 33, 16, BMC_ILI9341_BLACK);
      tft.display.drawRect(bX, buttonsY+56, 33, 16, BMC_ILI9341_VU_GREY);
      tft.display.setCursor(bX+5, buttonsY + 60);
      tft.display.print("MUTE");
    }
  }
  void updateDawChannels(){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    if(globals.onBoardEditorActive()){
      return;
    }
#endif
    if(dawChannelsBlock==-1){
      return;
    }
    uint16_t x = block[dawChannelsBlock].getX();
    uint8_t  y = block[dawChannelsBlock].getY();
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    uint8_t buttonsY = y+6;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t vPotValue = sync.daw.controller.getVPot(i);
      // for testing
      uint16_t bX = (x + 7) + (i*39);
      //uint16_t bY = y+BMC_ILI9341_VU_METER_Y;

      bool rec = sync.daw.controller.getRecState(i);
      bool solo = sync.daw.controller.getSoloState(i);
      bool mute = sync.daw.controller.getMuteState(i);

      tft.display.setTextSize(1);

      if(bitRead(dawChStates[i], 0) != rec){
        tft.display.setTextColor(rec ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
        tft.display.fillRect(bX, buttonsY+16, 33, 16, rec ? BMC_ILI9341_RED : BMC_ILI9341_BLACK);
        if(!rec){
          tft.display.drawRect(bX, buttonsY+16, 33, 16, BMC_ILI9341_VU_GREY);
        }
        tft.display.setCursor(bX+8, buttonsY + 20);
        tft.display.print("REC");
        bitWrite(dawChStates[i], 0, rec);
      }

      if(bitRead(dawChStates[i], 1) != solo){
        tft.display.setTextColor(solo ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
        tft.display.fillRect(bX, buttonsY+36, 33, 16, solo ? BMC_ILI9341_ORANGE : BMC_ILI9341_BLACK);
        if(!solo){
          tft.display.drawRect(bX, buttonsY+36, 33, 16, BMC_ILI9341_VU_GREY);
        }
        tft.display.setCursor(bX+5, buttonsY + 40);
        tft.display.print("SOLO");
        bitWrite(dawChStates[i], 1, solo);

      }

      if(bitRead(dawChStates[i], 2) != mute){
        tft.display.setTextColor(mute ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
        tft.display.fillRect(bX, buttonsY+56, 33, 16, mute ? BMC_ILI9341_BLUE : BMC_ILI9341_BLACK);
        if(!mute){
          tft.display.drawRect(bX, buttonsY+56, 33, 16, BMC_ILI9341_VU_GREY);
        }
        tft.display.setCursor(bX+5, buttonsY + 60);
        tft.display.print("MUTE");
        bitWrite(dawChStates[i], 2, mute);
      }
      if(dawVPotLevel[i] != vPotValue){
        uint8_t vuHeight = 9;
        uint16_t vuWidth = 3;
        for(uint8_t e = 0 ; e < 11 ; e++){
          if(e < 6){ // decrease
            vuHeight -= e > 0 ? 1 : 0;
          } else {// increase
            vuHeight += 1;
          }
          bool l = sync.daw.controller.getVPotValue(i, e+1)>0;
          if(bitRead(dawVPotBits[i], e) != l){
            tft.display.fillRect(bX + (vuWidth*e), y+6, vuWidth, vuHeight, l ? BMC_ILI9341_DARKGREEN : BMC_ILI9341_VU_GREY);
            bitWrite(dawVPotBits[i], e, l);
          }
        }
        dawVPotLevel[i] = vPotValue;
      }
    }
    dawSelectedTrack = sel;
  }

  #endif
#endif

  void clearAll(){
#if BMC_MAX_OLED > 0
    for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
  #if BMC_MAX_OLED > 1
      selectMux(i);
  #endif
      oled[i].display.clearDisplay();
      oled[i].display.display();
    }
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      block[i].clear(tft.display);
    }
#endif
  }

  void update(uint8_t page){

  }
  void renderPresetNumber(uint16_t n){

  }
  void printHorizontalMeter(uint8_t n, uint8_t value){
#if BMC_MAX_OLED > 0
    n = constrain(n, 0, BMC_MAX_OLED-1);
  #if BMC_MAX_OLED > 1
    selectMux(n);
  #endif
    oled[n].printHorizontalMeter(value);
#endif
  }
#if BMC_MAX_OLED > 0
  BMC_SSD1306 & get(uint8_t n){
    n = constrain(n, 0, BMC_MAX_OLED-1);
#if BMC_MAX_OLED > 1
    selectMux(n);
#endif
    return oled[n].display;
  }
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
  ILI9341_t3 & getILI9341(){
    return tft.display;
  }
  void menuCommand(uint8_t cmd){
    if(cmd == 0){
      return;
    }
    /*
    #define BMC_MENU_TOGGLE	 1
    #define BMC_MENU_SELECT	 2
    #define BMC_MENU_BACK  	 3
    #define BMC_MENU_UP    	 4
    #define BMC_MENU_DOWN  	 5
    #define BMC_MENU_INC   	 6
    #define BMC_MENU_DEC   	 7
    */
  }
#endif

void renderNumber(uint8_t n, bool isOled, uint8_t type, uint16_t value, const char * format){
  char str[6] = "";
  if(value<10){
    sprintf(str, "%01u", value);
  } else if(value<100){
    sprintf(str, "%02u", value);
  } else if(value<1000){
    sprintf(str, "%03u", value);
  } else {
    sprintf(str, "%04u", value);
  }

  renderText(n, isOled, type, str);
}
void renderChar(uint8_t n, bool isOled, uint8_t type, char str){
  char c[2] = {str, 0};
  //strncpy(c, str, 1);
  renderText(n, isOled, type, c, 0, 0);
}
void renderText(uint8_t n, bool isOled, uint8_t type, const char * str, uint8_t xShift=0, uint8_t yShift=0){
  uint8_t len = strlen(str)+1;
  char c[len] = "";
  strncpy(c, str, len);
  renderText(n, isOled, type, c, xShift, yShift);
}

void renderText(uint8_t n, bool isOled, uint8_t type, char * t_str, uint8_t xShift=0, uint8_t yShift=0){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif
  char str[strlen(t_str)+2] = "-";
  if(strlen(t_str) != 0){
    strcpy(str, t_str);
  }
  uint8_t crc = checkLast(type, str);
  uint8_t displayN = n + (isOled ? 0 : BMC_MAX_OLED);
  if(last[displayN] != crc){
    last[displayN] = crc;
#if BMC_MAX_OLED > 0
    if(isOled){
      oled[n].print(str, xShift, yShift);
      return;
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      block[n].print(tft.display, str, xShift, yShift);
    }
#endif
  }
}


private:
  BMCMidi& midi;
  BMCGlobals& globals;
  BMCCallbacks& callback;
#ifdef BMC_USE_SYNC
  BMCSync& sync;
#endif
  uint8_t last[BMC_MAX_OLED+BMC_MAX_ILI9341_BLOCKS];
#if BMC_MAX_OLED > 0
  BMC_OLED oled[BMC_MAX_OLED];
#endif

public:
#if BMC_MAX_ILI9341_BLOCKS > 0
  // tft must be public for on board editor use
  BMC_ILI9341 tft = BMC_ILI9341();
  BMC_ILI9341_BLOCK block[BMC_MAX_ILI9341_BLOCKS];
#endif

private:
#if defined(BMC_USE_DAW_LC) && BMC_MAX_ILI9341_BLOCKS > 0
  int8_t dawSelectedTrack = -1;
  int8_t dawChannelsBlock = -1;
  int8_t dawMetersBlock = -1;
  uint8_t dawVPotLevel[8];
  uint16_t dawVPotBits[8];
  uint8_t dawVuLevel[8];
  uint16_t dawVuLevelBits[8];
  uint8_t dawVuOverload = 0;
  uint8_t dawChStates[8];
  uint8_t dawFaderLevel[8];
  char dawChName[8][8];
#endif
  const char keyword[23][8] = {
    "BACK",
    "MENU",
    "ENTER",
    "SELECT",
    "UP",
    "DOWN",
    "LEFT",
    "RIGHT",
    "PREV",
    "NEXT",
    "REC",
    "PLAY",
    "STOP",
    "FF",
    "RR",
    "SOLO",
    "MUTE",
    "PAN",
    "VERSE",
    "CHORUS",
    "BREAK",
    "LEAD",
    "BANK",
  };

  void renderIcon(uint8_t n, bool isOled, uint8_t type, uint8_t value){
#if BMC_MAX_OLED > 0
  if(isOled){
    #if BMC_MAX_OLED > 1
    selectMux(n);
    #endif
    oled[n].printIcon(value);
  } else {

  }
#endif
  }

  uint8_t checkLast(uint8_t type,char * str){
    uint8_t len = strlen(str);
    if(len==0){
      return 0;
    }
    uint8_t crc = 0;
    for(uint8_t i = 0 ; i < len ; i++){
      crc ^= (uint8_t) (str[i]+i+type);
    }
    return crc;
  }
#if BMC_MAX_OLED > 1
  void selectMux(uint8_t n){
#if defined(BMC_OLED_USER_DEFINED_PORTS)
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_OLED, i);
    n = ui.other2;// mux port
    //n = BMCBuildData::getOledDisplayPosition(n, 4);

#endif
    uint8_t address = 0x70 + ((n>>3) & 0x07);
    uint8_t mask = 1 << (n & 0x07);
    Wire.beginTransmission(address);
    Wire.write(mask);
    Wire.endTransmission();
  }
#endif
};
#endif
#endif
