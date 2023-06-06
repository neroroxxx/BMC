/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DISPLAY_H
#define BMC_DISPLAY_H
#include "utility/BMC-Def.h"
#include "editor/onBoard/BMC-OBEDef.h"


#if defined(BMC_HAS_DISPLAY)

#if defined(BMC_HAS_TOUCH_SCREEN)
  #include <XPT2046_Touchscreen.h>
  #include "display/BMC-DisplayTouchCalibration.h"
#endif

// lighter gray 0x39C7
#define BMC_ILI9341_VU_GREY BMC_ILI9341_GRAY_7
#define BMC_ILI9341_FADER_CAP_COLOR BMC_ILI9341_GRAY_24

// values for the DAW VU Meters and other 8 channel display events
// these are use no matter the screen dimensions




// For meters
#define BMC_ILI9341_VU_METER_S 6 // blank space between meter blocks

// how many pixels each of the 8 channels will take
#define BMC_ILI9341_VU_METER_BLOCK_WIDTH (BMC_TFT_WIDTH/8)
#define BMC_ILI9341_VU_METER_FULL_WIDTH (BMC_ILI9341_VU_METER_BLOCK_WIDTH-BMC_ILI9341_VU_METER_S) // 33 for full width
#define BMC_ILI9341_VU_METER_H 4 // height of each meter led
#define BMC_ILI9341_VU_METER_Y 3 // y coordinate of each meter led

#if BMC_TFT_SIZE == 1
  // 320 x 240 resolution
  // these need to be changed based on the width of the screen
  #define BMC_ILI9341_VU_METER_LEFT_MARGIN 1
  #define BMC_ILI9341_VU_METER_W 10 // width of each meter led, 16 works
  #define BMC_ILI9341_VU_METER_X 6 // x coordinate of each meter led
  #define BMC_ILI9341_FADER_RIGHT_MARGIN 6 // space from right marging
  #define BMC_ILI9341_CHANNEL_BUTTON_W (BMC_ILI9341_VU_METER_FULL_WIDTH) //width of solo,rec,mute buttons
  #define BMC_ILI9341_CHANNEL_BUTTON_X 0 // x coordinate of buttons
  #define BMC_DISPLAY_BANNER_Y 60
  #define BMC_ILI9341_VPOT_INDICATOR_W 3
  #define BMC_ILI9341_VPOT_INDICATOR_X 1
  // For Faders
  #define BMC_ILI9341_FADER_W 5 // width of the fader cap
  #define BMC_ILI9341_FADER_H 10 // height of the fader cap
#else
  // these need to be changed based on the width of the screen
  // 480 x 320 resolution
  #define BMC_ILI9341_VU_METER_LEFT_MARGIN 3
  #define BMC_ILI9341_VU_METER_W 16 // width of each meter led, 16 works
  #define BMC_ILI9341_VU_METER_X 9 // x coordinate of each meter led
  #define BMC_ILI9341_FADER_RIGHT_MARGIN 9 // space from right marging
  #define BMC_ILI9341_CHANNEL_BUTTON_W (BMC_ILI9341_VU_METER_FULL_WIDTH) //width of solo,rec,mute buttons
  #define BMC_ILI9341_CHANNEL_BUTTON_X 0 // x coordinate of buttons
  #define BMC_DISPLAY_BANNER_Y 100
  #define BMC_ILI9341_VPOT_INDICATOR_W 4
  #define BMC_ILI9341_VPOT_INDICATOR_X 5
  // For Faders
  #define BMC_ILI9341_FADER_W 7 // width of the fader cap
  #define BMC_ILI9341_FADER_H 10 // height of the fader cap
#endif


class BMCDisplay {
public:
  BMCDisplay(BMCMidi& t_midi
    #ifdef BMC_USE_SYNC
      ,BMCSync& t_sync
    #endif
  ):midi(t_midi)
    #ifdef BMC_USE_SYNC
      ,sync(t_sync)
    #endif
  {
    #if BMC_MAX_OLED > 0
    memset(last, 0, sizeof(last[0])*BMC_MAX_OLED);
    #endif
    // begin();
  }
  void begin(){
    BMC_PRINTLN("BMCDisplay::begin()");
    
#if defined(BMC_USE_DAW_LC) && BMC_MAX_ILI9341_BLOCKS > 0
    dawChannelsBlock = -1;
    dawMetersBlock = -1;
    dawVuOverload = 0;
    dawSelectedTrack = -1;
    // memset(dawVPotLevel, 0, 8);
    // memset(dawVPotBits, 0, 8);
    // memset(dawVuLevel, 0, 8);
    // memset(dawVuLevelBits, 0, 8);
    // memset(dawFaderLevel, 0, 8);
    // memset(dawChStates, 0, 8);

    memset(dawVPotLevel, 0, sizeof(dawVPotLevel[0])*8);
    memset(dawVPotBits, 0, sizeof(dawVPotBits[0])*8);
    memset(dawVuLevel, 0, sizeof(dawVuLevel[0])*8);
    memset(dawVuLevelBits, 0, sizeof(dawVuLevelBits[0])*8);
    memset(dawFaderLevel, 0, sizeof(dawFaderLevel[0])*8);
    memset(dawChStates, 0, sizeof(dawChStates[0])*8);

#endif

#if BMC_MAX_OLED > 0
    initOled();
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
    initILI9341();
#endif
    delay(50);
  }

#if BMC_MAX_ILI9341_BLOCKS > 0
  void initILI9341(){
    BMC_PRINTLN("BMCDisplay::initILI9341()");
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, -1);
    tft.begin(ui.rotation & 0x0F);
    
    #if defined(BMC_HAS_TOUCH_SCREEN)
      touchScreen.begin();
      touchScreen.setRotation(ui.rotation & 0x0F);
    #endif
  }
#if defined(BMC_HAS_TOUCH_SCREEN)
  void touchCalibration(){
    BMCDisplayTouchCalibration touchCal(midi, tft.display, touchScreen);
    touchCal.begin();
  }

#endif
  void initILI9341Blocks(){
    #if defined(BMC_HAS_TOUCH_SCREEN)
      bmcStoreTouchSettings cal;
      cal.xM = midi.globals.settings.getTouchTftCalibration(0);
      cal.xC = midi.globals.settings.getTouchTftCalibration(1);
      cal.yM = midi.globals.settings.getTouchTftCalibration(2);
      cal.yC = midi.globals.settings.getTouchTftCalibration(3);
      uint16_t blockWidth = BMC_TFT_WIDTH/4;

      touchPrev.begin(0, BMC_TFT_HEIGHT-80, blockWidth, 80);
      touchToggle.begin(blockWidth, BMC_TFT_HEIGHT-80, blockWidth, 80);
      touchSelect.begin(blockWidth*2, BMC_TFT_HEIGHT-80, blockWidth, 80);
      touchNext.begin(blockWidth*3, BMC_TFT_HEIGHT-80, blockWidth, 80);
      touchCancel.begin(BMC_OBE_CANCEL_BTN_X, BMC_OBE_SAVE_BTN_Y, BMC_OBE_SAVE_BTN_W, BMC_OBE_SAVE_BTN_H);
      touchSave.begin(BMC_OBE_SAVE_BTN_X, BMC_OBE_SAVE_BTN_Y, BMC_OBE_SAVE_BTN_W, BMC_OBE_SAVE_BTN_H);
      touchEnter.begin(0, 0, BMC_TFT_WIDTH, BMC_TFT_HEIGHT);

      touchPrev.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchToggle.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchSelect.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchNext.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchCancel.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchSave.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchEnter.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    #endif



    tft.clear();
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      block[i].begin(i);
    }
  }
  void closeBanner(){
    tempTimer.start(1);
  }
  void renderUnavailableBanner(const char* line1, const char* line2){
    if(!allowBanner()){
      return;
    }
    renderTempBanner(line1, line2);
  }
  void renderLayerBanner(){
    if(!allowBanner()){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Layer %u", midi.globals.layer+midi.globals.offset);
    bmcName_t n = midi.globals.store.layers[midi.globals.layer].events[0].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, midi.globals.store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
  }
  void renderStoreClearedBanner(){
    if(!allowBanner()){
      return;
    }
    char line1[33] = "BMC";
    char line2[33] = "EEPROM ERASED";
    renderTempBanner(line1, line2);
  }
  void renderImportBanner(){
    #if defined(BMC_USE_ON_BOARD_EDITOR)
      if(midi.globals.onBoardEditorActive()){
        return;
      }
    #endif
    char line1[33] = "BMC";
    char line2[33] = "Import in Progress";
    renderTempBanner(line1, line2, false);
  }
  void renderPresetBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_PRESETS > 0
    if(midi.globals.bank>=32 || midi.globals.presetIndex >= BMC_MAX_PRESETS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    uint16_t p = midi.globals.preset+midi.globals.offset;
    char b = midi.globals.alph[midi.globals.bank];
    sprintf(line1, "Preset %c%u", b, p);
    bmcName_t n = midi.globals.store.global.presets[midi.globals.presetIndex].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, midi.globals.store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSetListBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(midi.globals.setList >= BMC_MAX_SETLISTS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Set List %u", midi.globals.setList+midi.globals.offset);
    bmcName_t n = midi.globals.store.global.setLists[midi.globals.setList].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, midi.globals.store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSongBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(midi.globals.songInLibrary >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Song %u", midi.globals.song+midi.globals.offset);
    bmcName_t n = midi.globals.store.global.songLibrary[midi.globals.songInLibrary].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, midi.globals.store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
#endif
  }
  void renderSongPartBanner(){
    if(!allowBanner()){
      return;
    }
#if BMC_MAX_SETLISTS > 0
    if(midi.globals.songPart >= BMC_MAX_SETLISTS_SONG_PARTS){
      return;
    }
    if(midi.globals.songInLibrary >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Part %u", midi.globals.songPart+midi.globals.offset);
    uint16_t songPart = midi.globals.store.global.songLibrary[midi.globals.songInLibrary].events[midi.globals.songPart];
    if(songPart > 0){
      bmcName_t n = midi.globals.store.global.presets[songPart-1].name;
      if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
        strcpy(line2, midi.globals.store.global.names[n-1].name);
      }
    }
    renderTempBanner(line1, line2);
#endif
  }
  bool allowBanner(){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    if(midi.globals.onBoardEditorActive()){
      return false;
    }
#endif
    return (midi.globals.settings.getDisplayBannerTimeout()>0);
  }
  void renderTempBanner(const char* line1, const char* line2, bool timeout=true){
    char s1[strlen(line1)+1] = "";
    char s2[strlen(line2)+1] = "";
    strcpy(s1, line1);
    strcpy(s2, line2);
    renderTempBanner(s1, s2, timeout);
  }
  void renderTempBanner(char* line1, char* line2, bool timeout=true){
    midi.globals.setDisplayRenderDisable(true);
    
    tft.display.fillRect(0, BMC_DISPLAY_BANNER_Y, BMC_TFT_WIDTH, 120, BMC_ILI9341_BLACK);
    tft.display.setFont(BMCLiberationSansNarrow_40_Bold);
    
    uint16_t x = (BMC_TFT_WIDTH - BMC_TFT_STR_LEN(tft.display, line1))/2;
    x = x < 4 ? 4 : x;
    // 2 lines of text, divide display height by 3 and add half the font height
    tft.display.setTextColor(0xfe60);
    tft.display.setCursor(x, BMC_DISPLAY_BANNER_Y+14);
    tft.display.print(line1);
    // line 2
    if(strlen(line2) > 0){
      tft.display.setFont(BMCLiberationSansNarrow_24);
      x = (BMC_TFT_WIDTH - BMC_TFT_STR_LEN(tft.display, line2))/2;
      x = x < 4 ? 4 : x;
      // 2 lines of text, divide display height by 3 and add half the font height
      tft.display.setTextColor(BMC_ILI9341_WHITE);
      tft.display.setCursor(x, BMC_DISPLAY_BANNER_Y+77);
      tft.display.print(line2);
    }
    // draw frame last
    tft.display.drawRect(0, BMC_DISPLAY_BANNER_Y, BMC_TFT_WIDTH, 120, 0xfe60);
    tft.display.drawRect(1, BMC_DISPLAY_BANNER_Y+1, BMC_TFT_WIDTH-2, 118, 0xfe60);
    if(timeout){
      tempTimer.start(midi.globals.settings.getDisplayBannerTimeout()*500);
    }
  }
#endif

#if BMC_MAX_OLED > 0
  void initOled(){
    
    #if BMC_MAX_OLED > 1
      Wire.begin();
    #endif
      for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
        // display can be address 0x3C or 0x3D
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_OLED, i);
    #if BMC_MAX_OLED > 1
        selectMux(i);
    #endif
        oled[i].begin(BMC_SSD1306_SWITCHCAPVCC, 0x3C + ui.other1, ui.rotation & 0x0F, i+1);
      }
  }
#endif
  void reassignOleds(){
#if BMC_MAX_OLED > 0
    memset(last, 0, sizeof(last[0])*BMC_MAX_OLED);
    clearOleds();

    uint16_t layer = midi.globals.layer;
    for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
      if(midi.globals.store.layers[layer].oled[i].events[0] == BMC_NONE){
        continue;
      }
#if defined(BMC_USE_DAW_LC) || defined(BMC_USE_FAS)
      bmcStoreEvent e = BMCTools::getDeviceEventType(midi.globals.store, midi.globals.store.layers[layer].oled[i].events[0]);
#endif

#if defined(BMC_USE_DAW_LC)
      if(e.type == BMC_EVENT_TYPE_DAW_DISPLAY){
        if(BMC_GET_BYTE(0, e.event) == 2){
          initDawChannelInfo(true, i, BMC_GET_BYTE(1, e.event));
          continue;
        }
      }
#endif

#if defined(BMC_USE_FAS)
      if(e.type == BMC_EVENT_TYPE_FAS){
        switch(BMC_GET_BYTE(0, e.event)){
          case BMC_FAS_CMD_TUNER_ON:
          case BMC_FAS_CMD_TUNER_OFF:
          case BMC_FAS_CMD_TUNER_TOGGLE:
          case BMC_FAS_CMD_TUNER_IN_TUNE:
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            initFasTuner(true, i);
            break;
        }
        continue;
      }
#endif
    }
#endif
  }


  void reassignIliBlocks(){
#if BMC_MAX_ILI9341_BLOCKS > 0
  #if defined(BMC_USE_DAW_LC)
    dawChannelsBlock = -1;
    dawMetersBlock = -1;
    dawVuOverload = 0;
    dawSelectedTrack = -1;
    // memset(dawVPotLevel, 0, 8);
    // memset(dawVPotBits, 0, 8);
    // memset(dawVuLevel, 0, 8);
    // memset(dawVuLevelBits, 0, 8);
    // memset(dawFaderLevel, 0, 8);
    // memset(dawChStates, 0, 8);

    memset(dawVPotLevel, 0, sizeof(dawVPotLevel[0])*8);
    memset(dawVPotBits, 0, sizeof(dawVPotBits[0])*8);
    memset(dawVuLevel, 0, sizeof(dawVuLevel[0])*8);
    memset(dawVuLevelBits, 0, sizeof(dawVuLevelBits[0])*8);
    memset(dawFaderLevel, 0, sizeof(dawFaderLevel[0])*8);
    memset(dawChStates, 0, sizeof(dawChStates[0])*8);
  #endif
    
    clearIliBlocks();

    uint16_t layer = midi.globals.layer;
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      if(midi.globals.store.layers[layer].ili[i].events[0] == 0){
        continue;
      }
      bmcStoreEvent e = BMCTools::getDeviceEventType(midi.globals.store, midi.globals.store.layers[layer].ili[i].events[0]);
#if defined(BMC_USE_DAW_LC)
      if(e.type == BMC_EVENT_TYPE_DAW_DISPLAY){
        uint16_t blockW = block[i].getWidth();
        uint16_t blockH = block[i].getHeight();
        if(blockH == 40){
          continue;
        }
        if(BMC_GET_BYTE(0, e.event) == 0){
          // make sure this is a 320 x 80 block
          if(dawMetersBlock == -1 && blockW == BMC_TFT_WIDTH){
            dawMetersBlock = i;
            initDawMeters();
          }
        } else if(BMC_GET_BYTE(0, e.event) == 1){
          if(dawChannelsBlock == -1 && blockW == BMC_TFT_WIDTH){
            dawChannelsBlock = i;
            initDawChannels();
          }
        } else if(BMC_GET_BYTE(0, e.event) == 2){
          // only works with blocks of 80 pixels height and 128+ wide blocks
          if(blockW >= 120){
            initDawChannelInfo(false, i, BMC_GET_BYTE(1, e.event));
          }
        }
      }
#endif
#if defined(BMC_USE_FAS)
      if(e.type == BMC_EVENT_TYPE_FAS){
        switch(BMC_GET_BYTE(0, e.event)){
          case BMC_FAS_CMD_TUNER_ON:
          case BMC_FAS_CMD_TUNER_OFF:
          case BMC_FAS_CMD_TUNER_TOGGLE:
          case BMC_FAS_CMD_TUNER_IN_TUNE:
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            // only works with blocks of 80 pixels height and 128+ wide blocks
            if(block[i].getWidth() >= 120){
              initFasTuner(false, i);
            }
            break;
        }
      }
#endif
    }
#endif
  }
  void reassign(){
    BMC_PRINTLN("display reassign()");
    for(uint8_t i=0;i<9;i++){
#if defined(BMC_USE_DAW_LC)
      chInfo[i].reset();
#endif
#if defined(BMC_USE_FAS)
      fasTuner.reset();
#endif
    }

    reassignOleds();
    reassignIliBlocks();
  }

#if defined(BMC_USE_DAW_LC)
  #if BMC_MAX_ILI9341_BLOCKS > 0
  void initDawMeters(){
    if(!allowRendering() || dawMetersBlock==-1){
      return;
    }
    BMC_PRINTLN("************ initDawMeters");
    uint16_t x = block[dawMetersBlock].getX();
    uint16_t y = block[dawMetersBlock].getY();
    uint16_t w = block[dawMetersBlock].getWidth();
    uint16_t h = block[dawMetersBlock].getHeight();
    tft.display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
    updateDawMeters(true);
  }
  void updateDawMeters(bool reset=false){
    // return;
    if(!allowRendering() || dawMetersBlock == -1){
      return;
    }
    uint16_t x = block[dawMetersBlock].getX()+BMC_ILI9341_VU_METER_LEFT_MARGIN;
    uint16_t y = block[dawMetersBlock].getY();
    uint8_t  h = block[dawMetersBlock].getHeight();
    uint16_t selY = (y+h);
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    uint8_t faderLength = (BMC_ILI9341_VU_METER_H+1)*13;
    
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t value = sync.daw.controller.getMeter(i);
      int16_t faderLevel16 = sync.daw.controller.getVolume(i);
      uint8_t faderLevel = (uint8_t) map(faderLevel16, (-8192), 6651, 0+BMC_ILI9341_FADER_H, 65);
      uint8_t overload = sync.daw.controller.getMeterOverload(i);
      uint16_t bX = x + (i*BMC_ILI9341_VU_METER_BLOCK_WIDTH);
      uint8_t bY = y+BMC_ILI9341_VU_METER_Y;
      if(reset){
        dawVuLevel[i] = 0xFF;
        dawVuLevelBits[i] = 0xFFFF;
        dawVuOverload = 0xFF;
        dawFaderLevel[i] = 0xFF;
      }
      if(dawVuLevel[i] != value || reset){
        for(int8_t e = 13 ; e --> 1 ;){
          int8_t ee = abs(e-12) + 1;
          bool l = sync.daw.controller.getMeter(i, ee)>0;
          if(bitRead(dawVuLevelBits[i], e) != l || reset){
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
      if(bitRead(dawVuOverload, i) != overload || reset){
        bitWrite(dawVuOverload, i, overload);
        uint16_t overloadColor = overload ? BMC_ILI9341_RED : BMC_ILI9341_VU_GREY;
        tft.display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY, BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, overloadColor);
      }
      if(dawFaderLevel[i] != faderLevel || reset){
        uint16_t faderX = bX + (BMC_ILI9341_VU_METER_FULL_WIDTH-BMC_ILI9341_FADER_W)-BMC_ILI9341_FADER_RIGHT_MARGIN;
        uint16_t faderY = (bY+faderLength) - faderLevel;

        tft.display.fillRect(faderX, bY, BMC_ILI9341_FADER_W, faderLength, BMC_ILI9341_BLACK);
        tft.display.drawFastVLine(faderX+(BMC_ILI9341_FADER_W/2), bY, faderLength, BMC_ILI9341_VU_GREY);
        
        tft.display.fillRect(faderX, faderY, BMC_ILI9341_FADER_W, BMC_ILI9341_FADER_H, BMC_ILI9341_FADER_CAP_COLOR);
        tft.display.drawFastHLine(faderX, faderY+(BMC_ILI9341_FADER_H/2), BMC_ILI9341_FADER_W, BMC_ILI9341_BLACK);
        dawFaderLevel[i] = faderLevel;
      }
      if(dawSelectedTrack != sel || reset){
        tft.display.fillRect(bX, selY-4, BMC_ILI9341_VU_METER_FULL_WIDTH, 2, sel==i ? BMC_ILI9341_ORANGE : BMC_ILI9341_VU_GREY);
      }
    }
    dawSelectedTrack = sel;
  }

  void initDawChannels(){
    if(!allowRendering() || dawChannelsBlock == -1){
      return;
    }
    BMC_PRINTLN("************ initDawChannels");
    // make background black
    uint16_t x = block[dawChannelsBlock].getX();
    uint16_t y = block[dawChannelsBlock].getY();
    uint16_t w = block[dawChannelsBlock].getWidth();
    uint16_t h = block[dawChannelsBlock].getHeight();
    tft.display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);

    updateDawChannels(true);
  }
  void updateDawChannels(bool reset=false){
    // return;
    if(!allowRendering() || dawChannelsBlock==-1){
      return;
    }
    uint16_t x = block[dawChannelsBlock].getX()+BMC_ILI9341_VU_METER_LEFT_MARGIN;
    uint16_t y = block[dawChannelsBlock].getY();
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    
    uint8_t buttonsY = y+2+16;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t vPotValue = sync.daw.controller.getVPot(i);
      uint16_t bX = x + (i*BMC_ILI9341_VU_METER_BLOCK_WIDTH);
      uint16_t buttonsX = bX + BMC_ILI9341_CHANNEL_BUTTON_X;
      bool rec = sync.daw.controller.getRecState(i);
      bool solo = sync.daw.controller.getSoloState(i);
      bool mute = sync.daw.controller.getMuteState(i);
      if(reset){
        dawChStates[i] = 0xFF;
        dawVPotLevel[i] = 0xFF;
        dawVPotBits[i] = 0xFFFF;
      }
      if(bitRead(dawChStates[i], 0) != rec || reset){
        bitWrite(dawChStates[i], 0, rec);
        renderDawButton(buttonsX, buttonsY, rec, "R", BMC_ILI9341_RED);
      }
      if(bitRead(dawChStates[i], 1) != solo || reset){
        bitWrite(dawChStates[i], 1, solo);
        renderDawButton(buttonsX, buttonsY+20, solo, "S", BMC_ILI9341_ORANGE);
      }
      if(bitRead(dawChStates[i], 2) != mute || reset){
        bitWrite(dawChStates[i], 2, mute);
        renderDawButton(buttonsX, buttonsY+40, mute, "M", BMC_ILI9341_BLUE);
      }
      if(dawVPotLevel[i] != vPotValue || reset){
        for(uint8_t e = 0 ; e < 11 ; e++){
          bool l = sync.daw.controller.getVPotValue(i, e+1)>0;
          if(bitRead(dawVPotBits[i], e) != l || reset){
            uint16_t color = l ? BMC_ILI9341_GREEN : BMC_ILI9341_VU_GREY;
            tft.display.fillRect(bX +  BMC_ILI9341_VPOT_INDICATOR_X + (BMC_ILI9341_VPOT_INDICATOR_W*e), y+6, BMC_ILI9341_VPOT_INDICATOR_W, 4, color);
            bitWrite(dawVPotBits[i], e, l);
          }
        }
        dawVPotLevel[i] = vPotValue;
      }
    }
    dawSelectedTrack = sel;
  }
  void renderDawButton(uint16_t x, uint16_t y, uint8_t value, const char * t_str, uint16_t color, uint8_t cW=0, uint8_t cH=0){
    // convert const char array to char array
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    uint8_t buttonWidth = cW==0 ? BMC_ILI9341_CHANNEL_BUTTON_W : cW;
    uint8_t buttonHeight = cH==0 ? 16 : cH;
    // set the font to be used
    tft.display.setFont(Arial_12_Bold);
    tft.display.setTextColor(value ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
    tft.display.fillRect(x, y, buttonWidth, buttonHeight, value ? color : BMC_ILI9341_BLACK);
    if(!value){
      tft.display.drawRect(x, y, buttonWidth, buttonHeight, BMC_ILI9341_VU_GREY);
    }
    uint16_t w = BMC_TFT_STR_LEN(tft.display, str);
    tft.display.setCursor(x + ((buttonWidth - w)/2), y+((buttonHeight-12)/2));
    tft.display.print(str);
  }

  #endif

  // available to both oled and ili displays
  void initDawChannelInfo(bool isOled, uint8_t n, uint8_t ch){
    if(ch > 8 || chInfo[ch].index >= 0){
      return;
    }
    // reset first then set the values
    chInfo[ch].reset();
    chInfo[ch].index = n;
    chInfo[ch].isOled = isOled;
    #if BMC_MAX_OLED > 0
    if(isOled){
      initChannelInfoOled(ch);
      return;
    }
    #endif
    #if BMC_MAX_ILI9341_BLOCKS > 0
      initChannelInfoIli(ch);
    #endif
  }
#if BMC_MAX_OLED > 0
  void initChannelInfoOled(uint8_t n){
    if(n > 8 || chInfo[n].index < 0){
      return;
    }
    renderChannelInfoOled(n, true);
  }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  void initChannelInfoIli(uint8_t n){
    if(!allowRendering() || n > 8 || chInfo[n].index < 0){
      return;
    }
    renderChannelInfoIli(n, true);
  }
#endif
  void updateDawChannelInfo(uint8_t n){
    if(n > 8 || chInfo[n].index < 0){
      return;
    }
    #if BMC_MAX_OLED > 0
    if(chInfo[n].isOled){
      renderChannelInfoOled(n, false);
      return;
    }
    #endif
    #if BMC_MAX_ILI9341_BLOCKS > 0
      renderChannelInfoIli(n, false);
    #endif
  }
  #if BMC_MAX_OLED > 0
  void renderChannelInfoOled(uint8_t n, bool reset=false){
    bool show = false;
    uint8_t channel = n>=8 ? sync.daw.controller.getSelectedChannel() : n;
    uint8_t index = chInfo[n].index;
    uint8_t vPotValue = sync.daw.controller.getVPot(channel);
    uint8_t vuValue = sync.daw.controller.getMeter(channel);
    bool small = (BMC_OLED_HEIGHT==32);
    // uint16_t y = BMC_OLED_HEIGHT==32 ? 0 : 16;
    bmcStoreName t = sync.daw.getLcdTrackName(channel);
    bmcStoreName t2 = sync.daw.getLcdTrackValue(channel);
    BMCTools::strTrim(t.name);
    if(strlen(t.name)>6){
      t.name[6] = 0;
    }
    BMCTools::strTrim(t2.name);
    if(strlen(t2.name)>6){
      t2.name[6] = 0;
    }
    #if BMC_MAX_OLED > 1
      selectMux(index);
    #endif
    if(reset){
      vPotValue = 255;
      vuValue = 255;
      chInfo[n].vPotBits = 0xFFFF;
      chInfo[n].vuBits = 0xFFFF;
      oled[index].display.fillRect(0, 0, 128, BMC_OLED_HEIGHT, BMC_OLED_BLACK);
      oled[index].display.fillRect(25, (small ? 24 : 56), 101, 8, BMC_OLED_WHITE);
      oled[index].display.fillRect(71, (small ? 26 : 58), 9, 4, BMC_OLED_WHITE);
    }
    // track name
    if(!BMC_STR_MATCH(t.name, chInfo[n].name)){
      strcpy(chInfo[n].name, t.name);
      uint8_t fontSize = small ? 2 : 3;
      uint16_t x = (105-((strlen(t.name)*(6*fontSize))-fontSize))/2;
      oled[index].display.fillRect(23, 1, 105, (fontSize * 8), BMC_OLED_BLACK);
      oled[index].display.setCursor(x+23, (fontSize * 8)+fontSize);
      oled[index].display.setTextSize(fontSize);
      oled[index].display.setTextColor(BMC_OLED_WHITE);
      oled[index].display.setTextWrap(false);
      oled[index].display.print(t.name);
      show = true;
    }
    // channel value
    if(!BMC_STR_MATCH(t2.name, chInfo[n].value)){
      strcpy(chInfo[n].value, t2.name);
      if(!small){
        uint16_t x = (82-((strlen(t2.name)*12)-2))/2;
        oled[index].display.fillRect(35, 31, 82, 16, BMC_OLED_BLACK);
        oled[index].display.setCursor(x+35, 47);
        oled[index].display.setTextSize(2);
        oled[index].display.setTextColor(BMC_OLED_WHITE);
        oled[index].display.setTextWrap(false);
        oled[index].display.print(t2.name);
        show = true;
      }
    }
    // Meter
    if(vuValue != chInfo[n].vuValue){
      chInfo[n].vuValue = vuValue;
      for(int8_t e = 13 ; e --> 1 ;){
        int8_t ee = abs(e-12) + 1;
        // int8_t ee = abs((12-e)+ 1);
        bool v = sync.daw.controller.getMeter(channel, ee)>0;
        if(bitRead(chInfo[n].vuBits, e) != v){
          bitWrite(chInfo[n].vuBits, e, v);
          if(!small){
            oled[index].display.fillRect(2, (e*5), 12, 4, v ? BMC_OLED_WHITE : BMC_OLED_BLACK);
          } else {
            oled[index].display.fillRect(2, (e*2)+6, 12, 2, v ? BMC_OLED_WHITE : BMC_OLED_BLACK);
          }
          show = true;
        }
      }
    }
    // vPot
    if(vPotValue != chInfo[n].vPotLevel){
      chInfo[n].vPotLevel = vPotValue;
      // oled[index].display.drawRect(25, (small ? 24 : 56), 101, 8, BMC_OLED_WHITE);
      // oled[index].display.fillRect(71, (small ? 26 : 58), 9, 4, BMC_OLED_WHITE);
      for(uint8_t e = 0 ; e < 11 ; e++){
        bool l = sync.daw.controller.getVPotValue(channel, e+1)>0;
        if(bitRead(chInfo[n].vPotBits, e) != l){
          bitWrite(chInfo[n].vPotBits, e, l);
          oled[index].display.fillRect(26+(e*9), (small ? 26 : 58), 9, 4, l ? BMC_OLED_WHITE : BMC_OLED_BLACK);
        }
      }
      show = true;
    }
    if(show){
      oled[index].display.display();
    }
  }
  #endif
  #if BMC_MAX_ILI9341_BLOCKS > 0
  void renderChannelInfoIli(uint8_t n, bool reset=false){
    if(!allowRendering()){
      return;
    }
    uint8_t channel = n==8 ? sync.daw.controller.getSelectedChannel() : n;
    uint8_t vPotValue = sync.daw.controller.getVPot(channel);
    uint8_t vuValue = sync.daw.controller.getMeter(channel);
    bmcStoreName t = sync.daw.getLcdTrackName(channel);
    bmcStoreName t2 = sync.daw.getLcdTrackValue(channel);
    BMCTools::strTrim(t.name);
    if(strlen(t.name)>6){
      t.name[6] = 0;
    }
    BMCTools::strTrim(t2.name);
    if(strlen(t2.name)>6){
      t2.name[6] = 0;
    }
    uint8_t index = chInfo[n].index;
    uint16_t x = block[index].getX();
    uint16_t y = block[index].getY();
    uint16_t w = block[index].getWidth();
    uint16_t h = block[index].getHeight();
    uint16_t txtArea = w-20;
    txtArea = (txtArea > 140) ? 140 : txtArea;
    uint16_t xVPot = x + 20 + ((txtArea-92)/2);
    if(reset){
      vPotValue = 255;
      vuValue = 255;
      chInfo[n].vPotBits = 0xFFFF;
      chInfo[n].vuBits = 0xFFFF;
      chInfo[n].stateBits = 0xFF;
      tft.display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
      tft.display.drawRect(xVPot, y+68, 92, 8, BMC_ILI9341_VU_GREY);
    }
    if(!BMC_STR_MATCH(t.name, chInfo[n].name)){
      strcpy(chInfo[n].name, t.name);
      tft.display.setFont(BMCLiberationSansNarrow_20_Bold);
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(tft.display, t.name))/2;
      while(BMC_TFT_STR_LEN(tft.display, t.name) >= (w-20)){
        t.name[strlen(t.name)-1] = 0;
        bX = 20+((w-20)-BMC_TFT_STR_LEN(tft.display, t.name))/2;
      }
      tft.display.fillRect(x+20, y+1, txtArea, 30, BMC_ILI9341_BLACK);
      tft.display.setCursor(x+bX, y+3);
      tft.display.setTextColor(BMC_ILI9341_WHITE);
      tft.display.setTextWrap(false);
      tft.display.print(t.name);
    }
    if(!BMC_STR_MATCH(t2.name, chInfo[n].value)){
      strcpy(chInfo[n].value, t2.name);
      tft.display.setFont(BMCLiberationSansNarrow_16);
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(tft.display, t2.name))/2;
      tft.display.fillRect(x+20, y+31, txtArea, 30, BMC_ILI9341_BLACK);
      tft.display.setCursor(x+bX, y+40);
      tft.display.setTextColor(BMC_ILI9341_GRAY_22);
      tft.display.setTextWrap(false);
      tft.display.print(t2.name);
    }
    if(vPotValue != chInfo[n].vPotLevel){
      chInfo[n].vPotLevel = vPotValue;
      xVPot += 2;
      for(uint8_t e = 0 ; e < 11 ; e++){
        bool l = sync.daw.controller.getVPotValue(channel, e+1)>0;
        if(bitRead(chInfo[n].vPotBits, e) != l){
          bitWrite(chInfo[n].vPotBits, e, l);
          tft.display.fillRect(xVPot+(e*8), y+70, 8, 4, l ? BMC_ILI9341_GREEN : BMC_ILI9341_BLACK);
        }
      }
    }
    if(vuValue != chInfo[n].vuValue){
      chInfo[n].vuValue = vuValue;
      for(int8_t e = 13 ; e --> 1 ;){
        int8_t ee = abs(e-12) + 1;
        bool v = sync.daw.controller.getMeter(channel, ee)>0;
        if(bitRead(chInfo[n].vuBits, e) != v){
          bitWrite(chInfo[n].vuBits, e, v);
          uint16_t color = BMC_ILI9341_YELLOW;
          if(ee < 6){
            color = BMC_ILI9341_GREEN;
          } else if(ee < 10){
            color = BMC_ILI9341_GREENYELLOW;
          } else if(ee < 12){
            color = BMC_ILI9341_ORANGE;
          } else {
            color = BMC_ILI9341_RED;
          }
          tft.display.fillRect(x+4, y+(e*6), 12, 5, v ? color : BMC_ILI9341_VU_GREY);
        }
      }
    }
    if(w > 160){
      bool rec = sync.daw.controller.getRecState(channel);
      bool solo = sync.daw.controller.getSoloState(channel);
      bool mute = sync.daw.controller.getMuteState(channel);
      if(bitRead(chInfo[n].stateBits, 0) != rec){
        bitWrite(chInfo[n].stateBits, 0, rec);
        renderDawButton(x+162, y+2, rec, "R", BMC_ILI9341_RED, 36, 22);
      }
      if(bitRead(chInfo[n].stateBits, 1) != solo){
        bitWrite(chInfo[n].stateBits, 1, solo);
        renderDawButton(x+162, y+29, solo, "S", BMC_ILI9341_ORANGE, 36, 22);
      }
      if(bitRead(chInfo[n].stateBits, 2) != mute){
        bitWrite(chInfo[n].stateBits, 2, mute);
        renderDawButton(x+162, y+55, mute, "M", BMC_ILI9341_BLUE, 36, 22);
      }
    }
  }
  #endif
#endif


#if defined(BMC_USE_FAS)
  // available to both oled and ili displays
  void initFasTuner(bool isOled, uint8_t n){
    BMC_PRINTLN("initFasTuner", fasTuner.index);
    if(fasTuner.index >= 0){
      return;
    }
    // reset first then set the values
    fasTuner.reset();
    fasTuner.index = n;
    fasTuner.isOled = isOled;
    #if BMC_MAX_OLED > 0
    if(isOled){
      initFasTunerOled();
      return;
    }
    #endif

    #if BMC_MAX_ILI9341_BLOCKS > 0
      initFasTunerIli();
    #endif
  }
#if BMC_MAX_OLED > 0
  void initFasTunerOled(){
    if(fasTuner.index < 0){
      return;
    }
    renderFasTunerOled(fasTuner.index, true);
  }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  void initFasTunerIli(){
    if(!allowRendering() || fasTuner.index < 0){
      return;
    }
    renderFasTunerIli(fasTuner.index, true);
  }
#endif
  void updateFasTuner(){
    if(fasTuner.index < 0){
      return;
    }
    #if BMC_MAX_OLED > 0
    if(fasTuner.isOled){
      renderFasTunerOled(fasTuner.index, false);
      return;
    }
    #endif

    #if BMC_MAX_ILI9341_BLOCKS > 0
      renderFasTunerIli(fasTuner.index, false);
    #endif
  }
#if BMC_MAX_OLED > 0
  void renderFasTunerOled(uint8_t index, bool reset=false){
    bool show = false;
    BMCTunerData currentTuner;
    sync.fas.getTunerData(currentTuner);
    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    uint16_t y = BMC_OLED_HEIGHT==32 ? 0 : 16;

    #if BMC_MAX_OLED > 1
      selectMux(index);
    #endif

    if(fasTuner.active != sync.fas.isTunerActive()){
      fasTuner.active = sync.fas.isTunerActive();
      tunerData.reset();
      oled[index].display.fillRect(0, 0, 128, BMC_OLED_HEIGHT, BMC_OLED_BLACK);
      if(!fasTuner.active){
        // Display the word Tuner
        renderText(index, true, BMC_EVENT_TYPE_FAS, "Tuner");
        return;
      } else {
        // clear the word "tuner" from the currently displayed buffer
        renderText(index, true, BMC_EVENT_TYPE_FAS, "");
        reset = true;
      }
    }
    if(!fasTuner.active){
      renderText(index, true, BMC_EVENT_TYPE_FAS, "Tuner");
      return;
    }
    if(currentTuner.pitchRaw != tunerData.pitchRaw || reset){
      uint8_t pitch = map(tunerData.pitchRaw, 0, 127, 8, 120);
      uint8_t pitch2 = map(currentTuner.pitchRaw, 0, 127, 8, 120);
      if(currentTuner.pitchRaw <= 64){
        oled[index].display.drawTriangle(45,y+0,45,y+12,59,y+6,BMC_OLED_WHITE);
      } else {
        oled[index].display.drawTriangle(45,y+0,45,y+12,59,y+6,BMC_OLED_BLACK);
      }
      if(currentTuner.pitchRaw >= 62){
        oled[index].display.drawTriangle(83,y+0,83,y+12,69,y+6, BMC_OLED_WHITE);
      } else {
        oled[index].display.drawTriangle(83,y+0,83,y+12,69,y+6, BMC_OLED_BLACK);
      }
      oled[index].display.fillCircle(pitch, y+24, 6, BMC_OLED_BLACK);
      oled[index].display.fillCircle(pitch2, y+24, 6, BMC_OLED_WHITE);
      oled[index].display.drawFastVLine(64, 0, BMC_OLED_HEIGHT, BMC_OLED_WHITE);
      oled[index].display.drawRect(0, y+16, 128, 16, BMC_OLED_WHITE);
      show = true;
    }
    if(currentTuner.note != tunerData.note || reset){
      oled[index].display.fillRect(0, y, 24, 16, BMC_OLED_BLACK);
      oled[index].display.setTextSize(2);
      oled[index].display.setTextColor(BMC_OLED_WHITE);
      oled[index].display.setCursor(0, y+16);
      oled[index].display.print(currentTuner.noteName);
      show = true;
    }
    if(currentTuner.stringNumber != tunerData.stringNumber || reset){
      oled[index].display.fillRect(116, y, 12, 16, BMC_OLED_BLACK);
      oled[index].display.setTextSize(2);
      oled[index].display.setTextColor(BMC_OLED_WHITE);
      oled[index].display.setCursor(116, y+16);
      oled[index].display.print(currentTuner.stringNumber+midi.globals.offset);
      show = true;
    }
    tunerData = currentTuner;
    if(show){
      oled[index].display.display();
    }
  }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  void renderFasTunerIli(uint8_t index, bool reset=false){
    if(!allowRendering()){
      return;
    }
    BMCTunerData currentTuner;
    sync.fas.getTunerData(currentTuner);
    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    uint16_t x = block[index].getX();
    uint16_t y = block[index].getY();
    uint16_t w = block[index].getWidth();
    uint16_t h = block[index].getHeight();

    uint16_t y1 = y + (h == 40 ? 4 : 14);
    uint16_t y2 = y + (h == 40 ? 24 : 46);
    uint16_t triW = (h == 40 ? 14 : 20);
    uint16_t triH = (h == 40 ? 12 : 18);
    uint16_t triSpace = 8;
    uint16_t half = (w / 2);

    if(fasTuner.active != sync.fas.isTunerActive()){
      fasTuner.active = sync.fas.isTunerActive();
      tunerData.reset();
      tft.display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
      if(!fasTuner.active){
        // Display the word Tuner
        renderText(index, false, BMC_EVENT_TYPE_FAS, "Tuner");
        return;
      } else {
        // clear the word "tuner" from the currently displayed buffer
        renderText(index, false, BMC_EVENT_TYPE_FAS, "");
        reset = true;
      }
    }
    if(!fasTuner.active){
      renderText(index, false, BMC_EVENT_TYPE_FAS, "Tuner");
      return;
    }
    if(currentTuner.pitchRaw != tunerData.pitchRaw || reset){
      uint16_t pitch = map(tunerData.pitchRaw, 0, 127, 12, w-12);
      uint16_t pitch2 = map(currentTuner.pitchRaw, 0, 127, 12, w-12);
      if(currentTuner.pitchRaw <= 64){
        tft.display.fillTriangle(x+(half-(triW+triSpace)), y1, x+(half-(triW+triSpace)), y1+triH, x+(half-triSpace), y1+(triH/2), BMC_ILI9341_RED);
      } else {
        tft.display.fillTriangle(x+(half-(triW+triSpace)), y1, x+(half-(triW+triSpace)), y1+triH, x+(half-triSpace), y1+(triH/2), BMC_ILI9341_BLACK);
      }
      if(currentTuner.pitchRaw >= 62){
        tft.display.fillTriangle(x+(half+(triW+triSpace)), y1, x+(half+(triW+triSpace)), y1+triH, x+(half+triSpace), y1+(triH/2), BMC_ILI9341_RED);
      } else {
        tft.display.fillTriangle(x+(half+(triW+triSpace)), y1, x+(half+(triW+triSpace)), y1+triH, x+(half+triSpace), y1+(triH/2), BMC_ILI9341_BLACK);
      }
      tft.display.fillCircle(x+pitch, y2+8, 6, BMC_ILI9341_BLACK);
      tft.display.fillCircle(x+pitch2, y2+8, 6, BMC_ILI9341_GREEN);
      tft.display.drawFastVLine(x+half, 0, h, BMC_ILI9341_WHITE);
      tft.display.drawRect(x+2, y2, w-4, 16, BMC_ILI9341_WHITE);
    }
    if(currentTuner.note != tunerData.note || reset){
      tft.display.setFont(BMCLiberationSansNarrow_16);
      tft.display.fillRect(x+2, y1, 34, 16, BMC_ILI9341_BLACK);

      tft.display.setCursor(x+4, y1);
      tft.display.setTextColor(BMC_ILI9341_BLACK);
      tft.display.print(tunerData.noteName);

      tft.display.setCursor(x+4, y1);
      tft.display.setTextColor(BMC_ILI9341_WHITE);
      tft.display.print(currentTuner.noteName);
    }
    if(currentTuner.stringNumber != tunerData.stringNumber || reset){
      tft.display.setFont(BMCLiberationSansNarrow_16);
      tft.display.fillRect(x+(w-18), y1, 18, 16, BMC_ILI9341_BLACK);

      tft.display.setCursor(x+(w-16), y1);
      tft.display.setTextColor(BMC_ILI9341_BLACK);
      tft.display.print(tunerData.stringNumber+midi.globals.offset);

      tft.display.setCursor(x+(w-16), y1);
      tft.display.setTextColor(BMC_ILI9341_WHITE);
      tft.display.print(currentTuner.stringNumber+midi.globals.offset);
    }
    tunerData = currentTuner;
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
      uint8_t settings = midi.globals.store.layers[midi.globals.layer].oled[i].settings[0];
      oled[i].reassign(settings);
    }
#endif
  }
  void clearIliBlocks(){
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!allowRendering()){
      return;
    }
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      uint8_t settings = midi.globals.store.layers[midi.globals.layer].ili[i].settings[0];
      block[i].reassign(tft.display, settings);
    }
#endif
  }
  void update(){
#if BMC_MAX_ILI9341_BLOCKS > 0
  #if defined(BMC_HAS_TOUCH_SCREEN)
    touchCommand = 0;
    if(touchTimer.complete()){
      touchPoint = touchScreen.getPoint();
      if(!midi.globals.onBoardEditorActive()){
        if(touchEnter.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_TOGGLE;
        }
      } else {
        if(touchPrev.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_PREV;
        } else if(touchToggle.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_TOGGLE;
        } else if(touchSelect.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_SELECT;
        } else if(touchNext.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_NEXT;
        } else if(touchCancel.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_CANCEL;
        } else if(touchSave.isTouched(touchPoint.x, touchPoint.y)){
          touchCommand = BMC_MENU_SAVE;
        }
      }
    }
    if(touchScreen.tirqTouched()){
      if(touchScreen.touched()){
        touchPoint = touchScreen.getPoint();
      }
      touchTimer.start(250);
    }
  #endif

  #if defined(BMC_USE_ON_BOARD_EDITOR)
    if(midi.globals.onBoardEditorActive()){
      tempTimer.stop();
      return;
    }
  #endif
    if(tempTimer.complete()){
      midi.globals.setDisplayRenderDisable(false);
      tft.display.fillScreen(BMC_ILI9341_BLACK);
      reassignIliBlocks();
    }
#endif
  }
  uint8_t getTouchCommand(){
#if defined(BMC_HAS_TOUCH_SCREEN)
    if(!firstTouch && touchCommand > 0){
      touchCommand = 0;
      firstTouch = true;
    }
    return touchCommand;
#else
    return 0;
#endif
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
  }
#endif

void renderNumber(uint8_t n, bool isOled, uint8_t type, uint16_t value, const char * format, const char* label="", bool highlight=false){
  char str[10] = "";
  if(value<10){
    sprintf(str, "%01u", value);
  } else if(value<100){
    sprintf(str, "%02u", value);
  } else if(value<1000){
    sprintf(str, "%03u", value);
  } else {
    sprintf(str, "%04u", value);
  }
  renderText(n, isOled, type, str, label, highlight);
}
void renderChar(uint8_t n, bool isOled, uint8_t type, char str){
  char c[2] = {str, 0};
  //strncpy(c, str, 1);
  renderText(n, isOled, type, c);
}
void renderText(uint8_t n, bool isOled, uint8_t type, const char* str, const char* label="", bool highlight=false){
  char c[strlen(str)+1] = "";
  // strncpy(c, str, len-1);
  strcpy(c, str);
  renderText(n, isOled, type, c, label, highlight);
}
void setSelChar(uint8_t n, bool isOled, uint8_t selChar){
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(selChar != oled[n].getSelChar()){
        last[n] = 0;
        oled[n].setSelChar(selChar);
      }
      return;
    }
  #endif 


  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      block[n].setSelChar(selChar);
    }
  #endif
}
void renderText(uint8_t n, bool isOled, uint8_t type, char* t_str, const char* label="", bool highlight=false){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif
  char str[strlen(t_str)+2] = "";
  if(strlen(t_str) != 0){
    strcpy(str, t_str);
  }
  uint8_t crc = checkLast(type, str)+highlight;
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(last[n] != crc){
        last[n] = crc;
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].oled[n].settings[0];
        oled[n].print(str, settings, highlight);
      }
      return;
    }
  #endif 


  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      if(allowRendering()){
        block[n].print(tft.display, crc, str, label, highlight);
      }
    }
  #endif
}

void renderProgramChangeValue(uint8_t n, bool isOled, uint8_t type, uint8_t ch, uint8_t pc, bool highlight=false){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif

  char str[12] = "";
  sprintf(str, "PC%u/%u", ch, pc);
  uint8_t crc = checkLast(type, str)+highlight;
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(last[n] != crc){
        last[n] = crc;
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].oled[n].settings[0];
        oled[n].printPC(ch, pc, settings, highlight);
      }
      return;
    }
  #endif
  
  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      if(allowRendering()){
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].ili[n].settings[0];
        block[n].printPC(tft.display, crc, ch, pc, settings, highlight);
      }
    }
  #endif
}
void renderControlChangeValue(uint8_t n, bool isOled, uint8_t type, uint8_t ch, uint8_t cc, uint8_t vv, bool highlight=false){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif

  char str[16] = "";
  sprintf(str, "CC%u/%u/%u", ch, cc, vv);
  uint8_t crc = checkLast(type, str)+highlight;
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(last[n] != crc){
        last[n] = crc;
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].oled[n].settings[0];
        oled[n].printCC(ch, cc, vv, settings, highlight);
      }
      return;
    }
  #endif 


  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      if(allowRendering()){
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].ili[n].settings[0];
        block[n].printCC(tft.display, crc, ch, cc, vv, settings, highlight);
      }
    }
  #endif
}
void renderNoteValue(uint8_t n, bool isOled, uint8_t type, uint8_t ch, uint8_t nn, uint8_t vv, bool highlight=false){
#if BMC_MAX_OLED > 1
  if(isOled){
    selectMux(n);
  }
#endif
  char str[16] = "";
  sprintf(str, "NN%u/%u/%u", ch, nn, vv);
  uint8_t crc = checkLast(type, str)+highlight;
#if BMC_MAX_OLED > 0
    if(isOled){
      if(last[n] != crc){
        last[n] = crc;
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].oled[n].settings[0];
        oled[n].printNote(ch, nn, vv, settings, highlight);
      }
      return;
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled){
      if(allowRendering()){
        uint8_t settings = midi.globals.store.layers[midi.globals.layer].ili[n].settings[0];
        block[n].printNote(tft.display, crc, ch, nn, vv, settings, highlight);
      }
    }
#endif
}





public:
  BMCMidi& midi;
#if defined(BMC_USE_SYNC)
  BMCSync& sync;
#endif

#if defined(BMC_USE_FAS)
  bmcDisplayFasTunerInfo fasTuner;
  BMCTunerData tunerData;
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
  // tft must be public for on board editor use
  BMC_ILI9341 tft = BMC_ILI9341();
  BMC_ILI9341_BLOCK block[BMC_MAX_ILI9341_BLOCKS];
  BMCTimer tempTimer;
  #if defined(BMC_HAS_TOUCH_SCREEN)
  XPT2046_Touchscreen touchScreen = XPT2046_Touchscreen(BMC_ILI_TOUCH_CS, BMC_ILI_TOUCH_IRQ);
  TS_Point touchPoint;
  BMCTimer touchTimer;
  bmcTouchArea touchPrev;
  bmcTouchArea touchToggle;
  bmcTouchArea touchSelect;
  bmcTouchArea touchNext;
  bmcTouchArea touchEnter;
  bmcTouchArea touchCancel;
  bmcTouchArea touchSave;
  uint8_t touchCommand = 0;
  bool firstTouch = false;
  #endif
#endif

#if BMC_MAX_OLED > 0
  uint8_t last[BMC_MAX_OLED];
  BMC_OLED oled[BMC_MAX_OLED];
#endif

private:
#if defined(BMC_USE_DAW_LC)
  #if BMC_MAX_ILI9341_BLOCKS > 0
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
  #endif
  bmcDawChannelsInfo chInfo[9];
  // uint16_t dawLedStates = 0;
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
    return !midi.globals.displayRenderDisabled();
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
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_OLED, n);
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
