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
#define BMC_ILI9341_VU_GREY BMC_ILI9341_GRAY_6
#define BMC_ILI9341_FADER_CAP_COLOR BMC_ILI9341_GRAY_24

// values for the DAW VU Meters and other 8 channel display events
// these are use no matter the screen dimensions

// For Faders
#define BMC_ILI9341_FADER_W 5 // width of the fader cap
#define BMC_ILI9341_FADER_H 10 // height of the fader cap


// For meters
#define BMC_ILI9341_VU_METER_S 7 // blank space between meter blocks

// how many pixels each of the 8 channels will take
#define BMC_ILI9341_VU_METER_BLOCK_WIDTH (BMC_TFT_WIDTH/8)
#define BMC_ILI9341_VU_METER_FULL_WIDTH (BMC_ILI9341_VU_METER_BLOCK_WIDTH-BMC_ILI9341_VU_METER_S) // 33 for full width
#define BMC_ILI9341_VU_METER_H 4 // height of each meter led
#define BMC_ILI9341_VU_METER_Y 3 // y coordinate of each meter led

#if BMC_TFT_SIZE == 1
  // 320 x 240 resolution
  // these need to be changed based on the width of the screen
  #define BMC_ILI9341_VU_METER_W 10 // width of each meter led, 16 works
  #define BMC_ILI9341_VU_METER_X 6 // x coordinate of each meter led
  #define BMC_ILI9341_FADER_RIGHT_MARGIN 6 // space from right marging
  #define BMC_ILI9341_CHANNEL_BUTTON_W (BMC_ILI9341_VU_METER_FULL_WIDTH) //width of solo,rec,mute buttons
  #define BMC_ILI9341_CHANNEL_BUTTON_X 0 // x coordinate of buttons
  #define BMC_DISPLAY_BANNER_Y 60
#else
  // these need to be changed based on the width of the screen
  // 480 x 320 resolution
  #define BMC_ILI9341_VU_METER_W 16 // width of each meter led, 16 works
  #define BMC_ILI9341_VU_METER_X 3 // x coordinate of each meter led
  #define BMC_ILI9341_FADER_RIGHT_MARGIN 6 // space from right marging
  #define BMC_ILI9341_CHANNEL_BUTTON_W (BMC_ILI9341_VU_METER_FULL_WIDTH) //width of solo,rec,mute buttons
  #define BMC_ILI9341_CHANNEL_BUTTON_X 0 // x coordinate of buttons
  #define BMC_DISPLAY_BANNER_Y 100
#endif


class BMCDisplay {
public:
  BMCDisplay(bmcStore& t_store, BMCGlobals& t_globals
    #ifdef BMC_USE_SYNC
      ,BMCSync& t_sync
    #endif
  ):store(t_store),
    globals(t_globals)
    
    
    #ifdef BMC_USE_SYNC
      ,sync(t_sync)
    #endif
  {
    #if BMC_MAX_OLED > 0
    memset(last, 0, BMC_MAX_OLED);
    #endif
    begin();
  }
  void begin(){
    BMC_PRINTLN("BMCDisplay::begin()");
    
#if defined(BMC_USE_DAW_LC) && BMC_MAX_ILI9341_BLOCKS > 0
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
    delay(500);
  }

#if BMC_MAX_ILI9341_BLOCKS > 0
  void initILI9341(){
    BMC_PRINTLN("BMCDisplay::initILI9341()");
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, -1);
    tft.begin(ui.rotation);
  }
  void initILI9341Blocks(){
    tft.clear();
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      block[i].begin(i);
    }
  }
  void renderUnavailableBanner(const char* line1, const char* line2){
    if(!allowBanner()){
      return;
    }
    renderTempBanner(line1, line2);
  }
  void renderPageBanner(){
    if(!allowBanner()){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Page %u", globals.page+globals.offset);
    bmcName_t n = store.pages[globals.page].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
  }
  void renderPresetBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_PRESETS > 0
    if(globals.bank>=32 || globals.presetIndex >= BMC_MAX_PRESETS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Preset %c%u", globals.alph[globals.bank], globals.preset+globals.offset);
    bmcName_t n = store.global.presets[globals.presetIndex].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSetListBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(globals.setList >= BMC_MAX_SETLISTS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Set List %u", globals.setList+globals.offset);
    bmcName_t n = store.global.setLists[globals.setList].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSongBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(globals.songInLibrary >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Song %u", globals.song+globals.offset);
    bmcName_t n = store.global.songLibrary[globals.songInLibrary].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSongPartBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(globals.songPart >= BMC_MAX_SETLISTS_SONG_PARTS){
      return;
    }
    if(globals.songInLibrary >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Part %u", globals.songPart+globals.offset);
    uint16_t songPart = store.global.songLibrary[globals.songInLibrary].events[globals.songPart];
    if(songPart > 0){
      bmcName_t n = store.global.presets[songPart-1].name;
      if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
        strcpy(line2, store.global.names[n-1].name);
      }
    }
    renderTempBanner(line1, line2);
#endif
  }
  bool allowBanner(){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    if(globals.onBoardEditorActive()){
      return false;
    }
#endif
    return (globals.settings.getDisplayBannerTimeout()>0);
  }
  void renderTempBanner(const char* line1, const char* line2){
    char s1[strlen(line1)] = "";
    char s2[strlen(line2)] = "";
    strcpy(s1, line1);
    strcpy(s2, line2);
    renderTempBanner(s1, s2);
  }
  void renderTempBanner(char* line1, char* line2){
    globals.setDisplayRenderDisable(true);
    
    tft.display.fillRect(0, BMC_DISPLAY_BANNER_Y, BMC_TFT_WIDTH, 120, BMC_ILI9341_BLACK);
    tft.display.setFont(BMCLiberationSansNarrow_40_Bold);
    
    uint16_t x = (BMC_TFT_WIDTH - tft.display.strPixelLen(line1))/2;
    x = x < 4 ? 4 : x;
    // 2 lines of text, divide display height by 3 and add half the font height
    tft.display.setTextColor(0xfe60);
    tft.display.setCursor(x, BMC_DISPLAY_BANNER_Y+14);
    tft.display.print(line1);
    // line 2
    if(strlen(line2) > 0){
      tft.display.setFont(BMCLiberationSansNarrow_24);
      x = (BMC_TFT_WIDTH - tft.display.strPixelLen(line2))/2;
      x = x < 4 ? 4 : x;
      // 2 lines of text, divide display height by 3 and add half the font height
      tft.display.setTextColor(BMC_ILI9341_WHITE);
      tft.display.setCursor(x, BMC_DISPLAY_BANNER_Y+77);
      tft.display.print(line2);
    }
    // draw frame last
    tft.display.drawRect(0, BMC_DISPLAY_BANNER_Y, BMC_TFT_WIDTH, 120, 0xfe60);
    tft.display.drawRect(1, BMC_DISPLAY_BANNER_Y+1, BMC_TFT_WIDTH-2, 118, 0xfe60);
    tempTimer.start(globals.settings.getDisplayBannerTimeout()*500);
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
  void reassignOleds(){
    #if BMC_MAX_OLED > 0
    memset(last, 0, BMC_MAX_OLED);
    clearOleds();
    #endif
    
  }
  void reassignIliBlocks(){
#if BMC_MAX_ILI9341_BLOCKS > 0
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

    clearIliBlocks();

    uint16_t page = globals.page;
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
#if defined(BMC_USE_DAW_LC)
      if(store.pages[page].ili[i].events[0] == 0){
        continue;
      }
      bmcStoreEvent e = BMCTools::getDeviceEventType(store, store.pages[page].ili[i].events[0]);
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
  void reassign(){
    reassignOleds();
    reassignIliBlocks();
  }




#if defined(BMC_USE_DAW_LC)
  #if BMC_MAX_ILI9341_BLOCKS > 0
  void initDawMeters(){
    if(!allowRendering()){
      return;
    }
    if(dawMetersBlock==-1){
      return;
    }
    BMC_PRINTLN("************ initDawMeters");
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t y = block[dawMetersBlock].getY();
    uint8_t faderLength = (BMC_ILI9341_VU_METER_H+1)*13;
    // clear the block
    tft.display.fillRect(x, y, BMC_TFT_WIDTH, 80, BMC_ILI9341_BLACK);
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint16_t bX = (x + BMC_ILI9341_VU_METER_S) + (i*39);
      uint16_t bY = y+BMC_ILI9341_VU_METER_Y;
      // VU METERS
      for(uint8_t e = 0 ; e < 13 ; e++){
        tft.display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
      }
      // tft.display.drawRect(bX, y, 33, 80, BMC_ILI9341_RED);

      uint16_t faderX = bX + (BMC_ILI9341_VU_METER_FULL_WIDTH-BMC_ILI9341_FADER_W)-BMC_ILI9341_FADER_RIGHT_MARGIN;
      // uint16_t faderY = (bY+faderLength) - 54;
      tft.display.fillRect(faderX, bY, BMC_ILI9341_FADER_W, faderLength, BMC_ILI9341_BLACK);
      tft.display.drawFastVLine(faderX+(BMC_ILI9341_FADER_W/2), bY, faderLength, BMC_ILI9341_VU_GREY);
    }
  }
  void updateDawMeters(){
    if(!allowRendering()){
      return;
    }
    if(dawMetersBlock == -1){
      return;
    }
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t  y = block[dawMetersBlock].getY();
    uint8_t tY = (y+80)-8;
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    uint8_t faderLength = (BMC_ILI9341_VU_METER_H+1)*13;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t value = sync.daw.controller.getMeter(i);
      int16_t faderLevel16 = sync.daw.controller.getVolume(i);
      //BMC_PRINTLN("faderLevel16", i, faderLevel16);
      //delay(150);
      uint8_t faderLevel = (uint8_t) map(faderLevel16, (-8192), 6651, 0+BMC_ILI9341_FADER_H, 65);
      uint8_t overload = sync.daw.controller.getMeterOverload(i);
      uint16_t bX = (x + BMC_ILI9341_VU_METER_S) + (i*39);
      uint8_t bY = y+BMC_ILI9341_VU_METER_Y;

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
        // uint16_t faderX = bX + BMC_ILI9341_VU_METER_X + BMC_ILI9341_VU_METER_W + BMC_ILI9341_FADER_S;
        uint16_t faderX = bX + (BMC_ILI9341_VU_METER_FULL_WIDTH-BMC_ILI9341_FADER_W)-BMC_ILI9341_FADER_RIGHT_MARGIN;
        uint16_t faderY = (bY+faderLength) - faderLevel;

        tft.display.fillRect(faderX, bY, BMC_ILI9341_FADER_W, faderLength, BMC_ILI9341_BLACK);
        tft.display.drawFastVLine(faderX+(BMC_ILI9341_FADER_W/2), bY, faderLength, BMC_ILI9341_VU_GREY);
        
        tft.display.fillRect(faderX, faderY, BMC_ILI9341_FADER_W, BMC_ILI9341_FADER_H, BMC_ILI9341_FADER_CAP_COLOR);
        tft.display.drawFastHLine(faderX, faderY+(BMC_ILI9341_FADER_H/2), BMC_ILI9341_FADER_W, BMC_ILI9341_BLACK);
        dawFaderLevel[i] = faderLevel;
      }
      
      bmcStoreName t = sync.daw.getLcdTrackName(i);
      // update the track name if this track was the last selected
      // or the currently selected track
      bool isSel = ((sel==i || dawSelectedTrack==i) && dawSelectedTrack != sel);
      if(strlen(dawChName[i]) != strlen(t.name) || !BMC_STR_MATCH(dawChName[i], t.name) || isSel){
        // tft.display.setFontAdafruit();
        // tft.display.setTextSize(1);
        tft.display.setFont(BMCLiberationSansNarrow_9);
        // print the previous string in black to remove it
        tft.display.setCursor(bX, tY-1);
        tft.display.setTextColor(BMC_ILI9341_BLACK);
        tft.display.print(dawChName[i]);
        // print new string
        tft.display.setCursor(bX, tY-1);
        tft.display.setTextColor(sel == i ? BMC_ILI9341_YELLOW : BMC_ILI9341_WHITE);
        tft.display.print(t.name);
        strcpy(dawChName[i], t.name);
      }
    }
    dawSelectedTrack = sel;
  }

  void initDawChannels(){
    if(!allowRendering()){
      return;
    }
    if(dawChannelsBlock==-1){
      return;
    }
    BMC_PRINTLN("************ initDawChannels");
    uint16_t x = block[dawChannelsBlock].getX();
    uint16_t y = block[dawChannelsBlock].getY();
    // clear the block
    tft.display.fillRect(x, y, BMC_TFT_WIDTH, 80, BMC_ILI9341_BLACK);
    // tft.display.setFontAdafruit();
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint16_t bX = (x + 7) + (i*39);
      //uint16_t bY = y+BMC_ILI9341_VU_METER_Y;
      // VPOT
      uint8_t vuHeight = 9;
      uint16_t vuWidth = 3;
      for(uint8_t e = 0 ; e < 11 ; e++){
        if(e < 6){ // decrease
          vuHeight -= (e > 0) ? 1 : 0;
        } else {// increase
          vuHeight += 1;
        }
        tft.display.fillRect(bX + (vuWidth*e), y+6, vuWidth, vuHeight, BMC_ILI9341_VU_GREY);
      }
      uint16_t buttonsX = bX + BMC_ILI9341_CHANNEL_BUTTON_X;
      uint16_t buttonsY = y+4+16;
      tft.display.setFont(Arial_12_Bold);
      tft.display.setTextColor(BMC_ILI9341_VU_GREY);

      renderDawButton(buttonsX, buttonsY,    0, "R", BMC_ILI9341_BLACK);
      renderDawButton(buttonsX, buttonsY+20, 0, "S", BMC_ILI9341_BLACK);
      renderDawButton(buttonsX, buttonsY+40, 0, "M", BMC_ILI9341_BLACK);
    }
  }
  void updateDawChannels(){
    if(!allowRendering()){
      return;
    }
    if(dawChannelsBlock==-1){
      return;
    }
    
    uint16_t x = block[dawChannelsBlock].getX();
    uint16_t y = block[dawChannelsBlock].getY();
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    
    uint8_t buttonsY = y+4+16;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t vPotValue = sync.daw.controller.getVPot(i);
      // for testing
      uint16_t bX = (x + 7) + (i*39);
      uint16_t buttonsX = bX + BMC_ILI9341_CHANNEL_BUTTON_X;

      bool rec = sync.daw.controller.getRecState(i);
      bool solo = sync.daw.controller.getSoloState(i);
      bool mute = sync.daw.controller.getMuteState(i);
      if(bitRead(dawChStates[i], 0) != rec){
        bitWrite(dawChStates[i], 0, rec);
        renderDawButton(buttonsX, buttonsY, rec, "R", BMC_ILI9341_RED);
      }
      if(bitRead(dawChStates[i], 1) != solo){
        bitWrite(dawChStates[i], 1, solo);
        renderDawButton(buttonsX, buttonsY+20, solo, "S", BMC_ILI9341_ORANGE);
      }
      if(bitRead(dawChStates[i], 2) != mute){
        bitWrite(dawChStates[i], 2, mute);
        renderDawButton(buttonsX, buttonsY+40, mute, "M", BMC_ILI9341_BLUE);
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
  void renderDawButton(uint16_t x, uint16_t y, uint8_t value, const char * str, uint16_t color){
    tft.display.setFont(Arial_12_Bold);
    tft.display.setTextColor(value ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
    tft.display.fillRect(x, y, BMC_ILI9341_CHANNEL_BUTTON_W, 16, value ? color : BMC_ILI9341_BLACK);
    if(!value){
      tft.display.drawRect(x, y, BMC_ILI9341_CHANNEL_BUTTON_W, 16, BMC_ILI9341_VU_GREY);
    }
    tft.display.setCursor(x+11, y + 2);
    tft.display.print(str);
  }

  #endif
#endif
  

  void clearAll(){
    clearOleds();
    clearIliBlocks();
  }
  void clearOleds(){
#if BMC_MAX_OLED > 0
    for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
  #if BMC_MAX_OLED > 1
      selectMux(i);
  #endif
      oled[i].display.clearDisplay();
      oled[i].display.display();
    }
#endif
  }
  void clearIliBlocks(){
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!allowRendering()){
      return;
    }
    BMC_PRINTLN("clearIliBlocks");
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      BMC_PRINTLN("clearIliBlocks", i, "page", globals.page, sizeof(store.pages[globals.page].ili[i].settings), store.pages[globals.page].ili[i].events[0]);
      uint8_t iliSettings = store.pages[globals.page].ili[i].settings[0];
      // BMC_PRINTLN("clearIliBlocks", i, "page", globals.page, "settings", iliSettings);
      block[i].clear(tft.display, iliSettings);
      BMC_PRINTLN("");
    }
#endif
  }

  void update(){
#if BMC_MAX_ILI9341_BLOCKS > 0
  #if defined(BMC_USE_ON_BOARD_EDITOR)
    if(globals.onBoardEditorActive()){
      tempTimer.stop();
      return;
    }
  #endif
    if(tempTimer.complete()){
      globals.setDisplayRenderDisable(false);
      tft.display.fillScreen(BMC_ILI9341_BLACK);
      reassignIliBlocks();
    }
#endif
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

  void menuCommand(uint8_t cmd){
    if(cmd == 0){
      return;
    }
    /*
    #define BMC_MENU_TOGGLE	 1
    #define BMC_MENU_SELECT	 2
    #define BMC_MENU_BACK  	 3
    #define BMC_MENU_PREV    	 4
    #define BMC_MENU_NEXT  	 5
    #define BMC_MENU_INC   	 6
    #define BMC_MENU_DEC   	 7
    */
  }
#endif

void renderNumber(uint8_t n, bool isOled, uint8_t type, uint16_t value, const char * format, const char* label=""){
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
  renderText(n, isOled, type, str, label);
}
void renderChar(uint8_t n, bool isOled, uint8_t type, char str){
  char c[2] = {str, 0};
  //strncpy(c, str, 1);
  renderText(n, isOled, type, c);
}
void renderText(uint8_t n, bool isOled, uint8_t type, const char* str, const char* label=""){
  uint8_t len = strlen(str)+1;
  char c[len] = "";
  strncpy(c, str, len);
  renderText(n, isOled, type, c, label);
}

void renderText(uint8_t n, bool isOled, uint8_t type, char* t_str, const char* label=""){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif
  char str[strlen(t_str)+2] = "";
  if(strlen(t_str) != 0){
    strcpy(str, t_str);
  }
  uint8_t crc = checkLast(type, str);
  // uint8_t displayN = n + (isOled ? 0 : BMC_MAX_OLED);
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(last[n] != crc){
        last[n] = crc;
        oled[n].print(str, 0, 0);
      }
      return;
    }
  #endif 


  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      if(allowRendering()){
        block[n].print(tft.display, crc, str, label);
      }
    }
  #endif

}


private:
  bmcStore& store;
  BMCGlobals& globals;
#ifdef BMC_USE_SYNC
  BMCSync& sync;
#endif

public:
#if BMC_MAX_ILI9341_BLOCKS > 0
  // tft must be public for on board editor use
  BMC_ILI9341 tft = BMC_ILI9341();
  BMC_ILI9341_BLOCK block[BMC_MAX_ILI9341_BLOCKS];
  BMCTimer tempTimer;
#endif

#if BMC_MAX_OLED > 0
  uint8_t last[BMC_MAX_OLED];
  BMC_OLED oled[BMC_MAX_OLED];
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
  char dawChName[8][10];
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
  bool allowRendering(){
    return !globals.displayRenderDisabled();
  }

  uint8_t checkLast(uint8_t type, char * str){
    uint8_t len = strlen(str);
    if(len==0){
      return 0;
    }
    uint8_t crc = 0;
    for(uint8_t i = 0 ; i < len ; i++){
      crc ^= (uint8_t) ((uint8_t)str[i]+i+type);
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
