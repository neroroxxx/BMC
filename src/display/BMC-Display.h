/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
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

#include "display/handlers/BMC-DisplayHandlerMain.h"

#if defined(BMC_USE_DAW_LC)
  #include "display/handlers/BMC-DisplayHandlerDaw.h"
#endif

#if defined(BMC_USE_FAS)
  #include "display/handlers/BMC-DisplayHandlerFas.h"
#endif

#if BMC_MAX_OLED > 1
  #define __oledMuxSelect(a) selectMux(a)
#else
  #define __oledMuxSelect(...)
#endif

class BMCDisplay {
public:
  BMCDisplay(BMCMidi& t_midi
    #if defined(BMC_USE_SYNC)
      ,BMCSync& t_sync
    #endif
  ):midi(t_midi),
    globals(t_midi.globals),
    store(t_midi.globals.store),
    settings(t_midi.globals.settings),
    mainHandler(t_midi
      #if defined(BMC_USE_SYNC)
        ,t_sync
      #endif
    )
    #if defined(BMC_USE_SYNC)
      ,sync(t_sync)
      #if defined(BMC_USE_DAW_LC)
        ,dawHandler(t_midi, t_sync)
      #endif
      #if defined(BMC_USE_FAS)
        ,fasHandler(t_midi, t_sync)
      #endif
    #endif

  {
    
  }

  void begin(){
    BMC_PRINTLN("BMCDisplay::begin()");
    mainHandler.begin();

#if defined(BMC_USE_DAW_LC)
    dawHandler.begin();
#endif

#if defined(BMC_USE_FAS)
    fasHandler.begin();
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
    initILI9341();
#endif

#if BMC_MAX_MINI_DISPLAY > 0
    initMiniDisplay();
#endif

#if BMC_MAX_LCD > 0
    initLCD();
#endif

#if BMC_MAX_OLED > 0
    initOled();
#endif

    delay(10);
  }

#if BMC_MAX_ILI9341_BLOCKS > 0
  void initILI9341(){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, -1);
    tft.begin(ui.rotation & 0x0F);

    #if defined(BMC_HAS_TOUCH_SCREEN)
      touchScreen.begin();
      touchScreen.setRotation(ui.rotation & 0x0F);
    #endif
    #if !defined(BMC_DISABLE_ILI_SPLASH_SCREEN)
    // render the splash screen after the touchscreen
    // otherwise you may get a white screen
    tft.renderBMCSplashScreen();
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
      cal.xM = settings.getTouchTftCalibration(0);
      cal.xC = settings.getTouchTftCalibration(1);
      cal.yM = settings.getTouchTftCalibration(2);
      cal.yC = settings.getTouchTftCalibration(3);
      
      uint16_t blockWidth = BMC_TFT_WIDTH/BMC_OBE_TOOLBAR_BUTTON_COUNT;
      // uint16_t blockPadding = 10;
      uint16_t blockPadding = (blockWidth-54)/2;
      uint16_t blockHeight = 120;
      uint16_t blockY = BMC_TFT_HEIGHT-blockHeight;
      uint16_t paddedBlockWidth = blockWidth-(blockPadding*2);
      uint16_t paddedBlockWidthEdges = blockWidth-blockPadding;

      // begin(int16_t t_x, int16_t t_y, uint16_t w, uint16_t h)
      touchHeaderBack.begin(0, 0, BMC_OBE_W*0.35, 60);
      touchHeaderExit.begin(BMC_OBE_W*0.65, 0, BMC_OBE_W*0.35, 60);
      
      touchPrev.begin(0, blockY, paddedBlockWidthEdges, blockHeight);
      #if BMC_OBE_TOOLBAR_BUTTON_COUNT == 4
        touchBack.begin(blockWidth+blockPadding, blockY, paddedBlockWidth, blockHeight);
        touchSelect.begin((blockWidth*2)+blockPadding, blockY, paddedBlockWidth, blockHeight);
      #else
        touchShift.begin(blockWidth+blockPadding, blockY, paddedBlockWidth, blockHeight);
        touchBack.begin((blockWidth*2)+blockPadding, blockY, paddedBlockWidth, blockHeight);
        touchSelect.begin((blockWidth*3)+blockPadding, blockY, paddedBlockWidth, blockHeight);
      #endif
      touchNext.begin((blockWidth*(BMC_OBE_TOOLBAR_BUTTON_COUNT-1))+blockPadding, blockY, paddedBlockWidthEdges, blockHeight);
      // used to confirm saving changes
      touchCancel.begin(BMC_OBE_CANCEL_BTN_X, BMC_OBE_SAVE_BTN_Y, BMC_OBE_SAVE_BTN_W, BMC_OBE_SAVE_BTN_H);
      touchSave.begin(BMC_OBE_SAVE_BTN_X, BMC_OBE_SAVE_BTN_Y, BMC_OBE_SAVE_BTN_W, BMC_OBE_SAVE_BTN_H);
      // enter into the menu
      touchEnter.begin(0, 0, BMC_TFT_WIDTH, BMC_TFT_HEIGHT);
      
      touchHeaderBack.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchHeaderExit.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      touchPrev.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      #if BMC_OBE_TOOLBAR_BUTTON_COUNT == 5
        touchShift.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
      #endif
      touchBack.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
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
    sprintf(line1, "Layer %u", globals.layer+globals.offset);
    bmcName_t n = store.layers[globals.layer].events[0].name;
    if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
      strcpy(line2, store.global.names[n-1].name);
    }
    renderTempBanner(line1, line2);
  }
  void renderDisplayLists(){
#if BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0
    if(globals.onBoardEditorActive()){
      return;
    }
    uint8_t listModeValue = settings.getDisplayListMode();
    if(listModeValue==0){
      globals.exitDisplayListMode();
      return;
    }
    uint8_t listId = globals.getDisplayListId();
    if(listId == 0){
      globals.exitDisplayListMode();
      return;
    }
    
    uint8_t listCount = BMC_TFT_HEIGHT==240 ? 4 : 5;
    uint16_t listCurrentValue = 0;
    uint16_t maxListCount = 0;
    uint8_t listItemHeight = BMC_TFT_HEIGHT==240 ? 47 : 54;
    uint8_t headerHeight = 50;
    uint8_t yPadding = BMC_TFT_HEIGHT==240 ? 7 : 10;
    char deviceName[16] = "";

    #if BMC_MAX_LAYERS > 1
      if(listId == BMC_DEVICE_ID_LAYER){
        strcpy(deviceName, "LAYERS");
        listCurrentValue = globals.layer;
        maxListCount = BMC_MAX_LAYERS;
      }
    #endif

    #if BMC_MAX_PRESETS > 0
      if(listId == BMC_DEVICE_ID_PRESET){
        strcpy(deviceName, "PRESETS");
        listCurrentValue = globals.presetIndex;
        maxListCount = BMC_MAX_PRESETS;
      }
      
      #if BMC_MAX_SETLISTS > 0
        if(listId == BMC_DEVICE_ID_SETLIST){
          strcpy(deviceName, "SETLISTS");
          listCurrentValue = globals.setList;
          maxListCount = BMC_MAX_SETLISTS;
        }
        if(listId == BMC_DEVICE_ID_SETLIST_SONG){
          strcpy(deviceName, "SONGS");
          listCurrentValue = globals.song;
          maxListCount = BMC_MAX_SETLISTS_SONGS;
        }
      #endif
      
    #endif
    if(maxListCount == 0){
      globals.exitDisplayListMode();
      return;
    }
    
    if(!globals.displayListsActive()){
      
      tft.display.setFont(BMC_FONT_SM);
      tft.display.fillRect(0, 0, BMC_TFT_WIDTH, headerHeight, BMC_ILI9341_BLACK);
      uint16_t x = (BMC_TFT_WIDTH - BMC_TFT_STR_LEN(tft.display, deviceName))/2;
      x = x < 4 ? 4 : x;
      tft.display.setCursor(x, headerHeight-16);
      // title color
      tft.display.setTextColor(BMC_ILI9341_YELLOW);
      tft.display.print(deviceName);
      tft.display.fillRect(0, headerHeight, BMC_TFT_WIDTH, BMC_TFT_HEIGHT-headerHeight, BMC_ILI9341_BLACK);
      tft.display.fillRect(0, headerHeight-12, BMC_TFT_WIDTH, 3, BMC_ILI9341_YELLOW);
      listPageCurrent = (uint16_t) floor(listCurrentValue / (listCount+0.0));
    }

    tft.display.setTextColor(BMC_ILI9341_ORANGE);
    tft.display.setFont(BMC_FONT_MD);
    
    // uint8_t pageTotal = (uint8_t) (BMC_MAX_SETLISTS / listCount);
    // uint8_t pageTotal = pageTotal + listCount;
    uint16_t pageCurrent = (uint16_t) floor(listCurrentValue / (listCount+0.0));
    if(listPageCurrent != pageCurrent){
      listPageCurrent = pageCurrent;
      tft.display.fillRect(0, headerHeight, BMC_TFT_WIDTH, BMC_TFT_HEIGHT-headerHeight, BMC_ILI9341_BLACK);
    }
    for(uint16_t i = 0, e = (pageCurrent*listCount) ; i < listCount; i++, e++){
      if(i >= listCount){
        break;
      }
      
      if(e < maxListCount){
        uint16_t borderColor = BMC_ILI9341_BLACK;
        uint16_t textColor = BMC_ILI9341_WHITE;
        if(listCurrentValue == e){
          // selected
          listLastSelection = e;
          borderColor = BMC_ILI9341_GRAY_11;
          textColor = BMC_ILI9341_ORANGE;
        }
        tft.display.setTextColor(textColor);

        tft.display.drawRect(4, headerHeight + (i*listItemHeight), BMC_TFT_WIDTH-8, listItemHeight, borderColor);
        tft.display.drawRect(5, headerHeight + 1 + (i*listItemHeight), BMC_TFT_WIDTH-10, listItemHeight-2, borderColor);

        // list color
        // tft.display.setCursor(14, headerHeight + ((i*listItemHeight) + yPadding));
        tft.display.setCursor(14, (headerHeight + ((i*listItemHeight) + listItemHeight) - yPadding));

        bmcName_t nameIndex = 0;
        
        #if BMC_MAX_LAYERS > 1
          if(listId == BMC_DEVICE_ID_LAYER){
            nameIndex = store.layers[e].events[0].name;
          }
        #endif
        #if BMC_MAX_PRESETS > 0
          if(listId == BMC_DEVICE_ID_PRESET){
            nameIndex = store.global.presets[e].name;
          }
        #endif
        #if BMC_MAX_SETLISTS > 0
          if(listId == BMC_DEVICE_ID_SETLIST){
            nameIndex = store.global.setLists[e].name;
          }
          if(listId == BMC_DEVICE_ID_SETLIST_SONG){
            // get the id of the song
            uint8_t currentSetlist = globals.setList;
            uint16_t songId = store.global.setLists[currentSetlist].events[e];
            nameIndex = store.global.songLibrary[songId-1].name;
            BMC_PRINTLN("******************************** songId", songId);
          }

        #endif

        

        if(nameIndex > 0){
          
          #if BMC_MAX_PRESETS > 0
            if(listId == BMC_DEVICE_ID_PRESET){
              char bankLetter[3] = "";
              BMCTools::getBankLetter(((e >> BMC_PRESET_BANK_MASK) & 0x1F), bankLetter);
              tft.display.print(bankLetter);
              tft.display.print((e & (BMC_MAX_PRESETS_PER_BANK-1))+globals.offset);
              continue;
            } else {
              tft.display.print("#");
              tft.display.print(e + globals.offset);
              tft.display.print(" ");
            }
          #else
            tft.display.print("#");
            tft.display.print(e + globals.offset);
            tft.display.print(" ");
          #endif
          
          bmcStoreName nameData = globals.getDeviceName(nameIndex);
          tft.display.print(nameData.name);
        } else {
          // no name just write Set #

          #if BMC_MAX_LAYERS > 0
            if(listId == BMC_DEVICE_ID_LAYER){
              tft.display.print("#");
            }
          #endif
          #if BMC_MAX_PRESETS > 0
            if(listId == BMC_DEVICE_ID_PRESET){
              char bankLetter[3] = "";
              BMCTools::getBankLetter(((e >> BMC_PRESET_BANK_MASK) & 0x1F), bankLetter);
              tft.display.print(bankLetter);
              tft.display.print((e & (BMC_MAX_PRESETS_PER_BANK-1))+globals.offset);
              continue;
            }
          #endif
          #if BMC_MAX_SETLISTS > 0
            if(listId == BMC_DEVICE_ID_SETLIST || listId == BMC_DEVICE_ID_SETLIST_SONG){
              tft.display.print("#");
            }
          #endif
          tft.display.print(e + globals.offset);
          tft.display.print(" ...");
        }
      }
    }
    globals.enterDisplayListMode(500+(listModeValue*500));
#endif
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
      if(globals.onBoardEditorActive()){
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
    if(globals.bank>=32 || globals.presetIndex >= BMC_MAX_PRESETS){
      return;
    }
    char line1[33] = "";
    char line2[33] = "";
    uint16_t p = globals.preset+globals.offset;
    char b = globals.alph[globals.bank];
    sprintf(line1, "Preset %c%u", b, p);
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
    // if(globals.songInLibrary >= BMC_MAX_SETLISTS_SONGS){
    //   return;
    // }
    // char line1[33] = "";
    // char line2[33] = "";
    // sprintf(line1, "Song %u", globals.song+globals.offset);
    // bmcName_t n = store.global.songLibrary[globals.songInLibrary].name;
    // if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
    //   strcpy(line2, store.global.names[n-1].name);
    // }
    // renderTempBanner(line1, line2);
    
    
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Song %u", globals.song+globals.offset);

    if(globals.songInLibrary > BMC_MAX_SETLISTS_SONGS_LIBRARY){
      strcpy(line2, "No Song Assigned");
    } else {
      bmcName_t n = store.global.songLibrary[globals.songInLibrary].name;
      if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
        strcpy(line2, store.global.names[n-1].name);
      }
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
    char line1[33] = "";
    char line2[33] = "";
    sprintf(line1, "Part %u", globals.songPart+globals.offset);


    if(globals.songInLibrary > BMC_MAX_SETLISTS_SONGS_LIBRARY){
      strcpy(line2, "No Song Assigned");
    } else {
      uint16_t songPart = store.global.songLibrary[globals.songInLibrary].events[globals.songPart];
      if(songPart > 0){
        bmcName_t n = store.global.presets[songPart-1].name;
        if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
          strcpy(line2, store.global.names[n-1].name);
        }
      }
    }
    renderTempBanner(line1, line2);
#endif
  }
  bool allowBanner(){
    if(globals.onBoardEditorActive() || globals.displayListsActive()){
      return false;
    }
    return (settings.getDisplayBannerTimeout()>0);
  }
  void renderTempBanner(const char* line1, const char* line2, bool timeout=true){
    char s1[strlen(line1)+1] = "";
    char s2[strlen(line2)+1] = "";
    strcpy(s1, line1);
    strcpy(s2, line2);
    renderTempBanner(s1, s2, timeout);
  }
  void renderTempBanner(char* line1, char* line2, bool timeout=true){
    globals.setDisplayRenderDisable(true);
    
    tft.display.fillRect(0, BMC_DISPLAY_BANNER_Y, BMC_TFT_WIDTH, 120, BMC_ILI9341_BLACK);
    tft.display.setFont(BMC_FONT_XL);
    
    uint16_t x = (BMC_TFT_WIDTH - BMC_TFT_STR_LEN(tft.display, line1))/2;
    x = x < 4 ? 4 : x;
    // 2 lines of text, divide display height by 3 and add half the font height
    tft.display.setTextColor(0xfe60);
    tft.display.setCursor(x, BMC_DISPLAY_BANNER_Y+14);
    tft.display.print(line1);
    // line 2
    if(strlen(line2) > 0){
      tft.display.setFont(BMC_FONT_MD);
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
      tempTimer.start(settings.getDisplayBannerTimeout()*500);
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
        __oledMuxSelect(i);
        oled[i].begin((i + 1), (0x3C + ui.other1), (ui.rotation & 0x0F));
      }
  }
#endif

#if BMC_MAX_MINI_DISPLAY > 0
  void initMiniDisplay(){
    BMC_PRINTLN("INIT MINI DISPLAYS");
    #if BMC_MINI_DISPLAY_W == 160
      BMC_PRINTLN("1.88\" Display");
    #else
      BMC_PRINTLN("1.44\" Display");
    #endif
    for(uint8_t i = 0 ; i < BMC_MAX_MINI_DISPLAY ; i++){
      // display can be address 0x3C or 0x3D
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_MINI_DISPLAY, i);
      int16_t rst = (BMC_TFT_RESET_PIN == 255) ? -1 : BMC_TFT_RESET_PIN;
      miniDisplay[i].begin(ui.pins[0], 9, rst, ui.rotation & 0x0F, i+1);
    }
  }
#endif


#if BMC_MAX_LCD > 0
  void initLCD(){
    lcd.begin();
    for(uint8_t i = 0 ; i < BMC_MAX_LCD ; i++){
      lcdLine[i].begin(i);
    }
  }
#endif




  void reassignOleds(){
#if BMC_MAX_OLED > 0
    clearOleds();
#endif
  }


  void reassignIliBlocks(bool clearCrc=false){
#if BMC_MAX_ILI9341_BLOCKS > 0
    clearIliBlocks(clearCrc);
#endif
  }

  void reassignMiniDisplay(){
#if BMC_MAX_MINI_DISPLAY > 0
    clearMiniDisplay();
#endif
  }

  void reassignLCD(){
#if BMC_MAX_LCD > 0
    lcd.setBacklight((settings.getLcdBacklight()+1)*16);
    clearLCD();
#endif
  }

  
  void reassign(bool full=false){
    reassignHandlers();

    reassignOleds();
    reassignIliBlocks(full);
    reassignMiniDisplay();
    reassignLCD();
  }
  void reassignHandlers(){
    mainHandler.reassign();

#if defined(BMC_USE_DAW_LC)
    dawHandler.reassign();
#endif

#if defined(BMC_USE_FAS)
    fasHandler.reassign();
#endif
  }


#if defined(BMC_USE_DAW_LC)
  #if BMC_MAX_ILI9341_BLOCKS > 0
  void renderDaw8Meters(BMCDataContainer d){
    if(allowRendering()){
      d.crc = generateCrc(d);
      dawHandler.render8MeterBlock(tft, block[d.index], d, d.crc, d.index);
    }
  }
  void renderDaw8Channel(BMCDataContainer d){
    if(allowRendering()){
      d.crc = generateCrc(d);
      dawHandler.render8ChannelBlock(tft, block[d.index], d, d.crc, d.index);
    }
  }
  #endif

  void renderDawChannel(BMCDataContainer d){
    d.crc = generateCrc(d);
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        dawHandler.renderChannelBlockOled(oled[d.index], d, d.index);
      #endif
    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          dawHandler.renderChannelBlockIli(tft, block[d.index], d, d.crc, d.index);
        }
      #endif
    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        dawHandler.renderChannelBlockMiniDisplay(miniDisplay[d.index], d);
      #endif
    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        lcdLine[d.index].print(lcd, d, d.str);
      #endif
    }
  }
  #endif

  void clearAll(){
    clearOleds();
    clearIliBlocks();
    clearMiniDisplay();
  }
  void clearOleds(){
#if BMC_MAX_OLED > 0
    for(uint8_t i = 0 ; i < BMC_MAX_OLED ; i++){
      __oledMuxSelect(i);
      uint8_t t_settings = store.layers[globals.layer].oled[i].settings[0];
      oled[i].reassign(t_settings);
    }
#endif
  }
  void clearIliBlocks(bool clearCrc=false){
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!allowRendering()){
      return;
    }
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      uint8_t t_settings = store.layers[globals.layer].ili[i].settings[0]+0;
      #if BMC_ILI_S_COUNT ==2
        uint8_t t_colors = store.layers[globals.layer].ili[i].settings[1]+0;
        t_colors = (t_colors == 0) ? 1 : t_colors;
        block[i].assignColor(t_colors & 0x0F);
        block[i].assignBackground((t_colors>>4) & 0x0F);
      #endif
      block[i].reassign(tft.display, t_settings);
      if(clearCrc){
        block[i].setCrc(0);
      }
    }
    if(clearCrc){
      reassignHandlers();
    }
#endif
  }

  void clearMiniDisplay(){
#if BMC_MAX_MINI_DISPLAY > 0
    for(uint8_t i = 0 ; i < BMC_MAX_MINI_DISPLAY ; i++){
      for(uint8_t e = 0 ; e < BMC_MAX_MINI_DISPLAY_EVENTS ; e++){
        miniDisplay[i].setLineIndex(e);
        uint8_t t_settings = store.layers[globals.layer].miniDisplay[i].settings[e*2]+0;
        uint8_t t_colors = store.layers[globals.layer].miniDisplay[i].settings[(e*2)+1]+0;
        t_colors = (t_colors == 0) ? 1 : t_colors;
        miniDisplay[i].assignColor(t_colors & 0x0F);
        miniDisplay[i].assignBackground((t_colors>>4) & 0x0F);
        miniDisplay[i].reassign(t_settings);
      }
    }
#endif
  }

  void clearLCD(){
#if BMC_MAX_LCD > 0
    // for(uint8_t i = 0 ; i < BMC_MAX_MINI_DISPLAY ; i++){
    //   lcdLine[d.index].setCrc();
    // }
    lcd.clear();
#endif
  }





#if defined(BMC_USE_FAS)
  void renderFasFxBlock(BMCDataContainer d){
    d.crc = generateCrc(d);
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        oled[d.index].print(d, d.str);
      #endif
    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          fasHandler.renderBlockIli(tft, block[d.index], d, d.crc, d.index);
        }
      #endif
    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        fasHandler.renderBlockMiniDisplay(miniDisplay[d.index], d);
      #endif
    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        lcdLine[d.index].print(lcd, d, d.str);
      #endif
    }
  }
  void renderFasStatus(BMCDataContainer d){
    if(sync.fas.connected()){
      strcpy(d.str, "Connected");
    } else {
      strcpy(d.str, "Not Connected");
    }
    d.crc = generateCrc(d);
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        fasHandler.renderStatusOled(oled[d.index], d);
      #endif

    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          fasHandler.renderStatusIli(tft, block[d.index], d);
        }
      #endif

    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        miniDisplay[d.index].print(d.crc, d.str, d.label, d.highlight);
      #endif

    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        fasHandler.renderStatusLcd(lcd, lcdLine[d.index], d);
      #endif
    }
  }
  void renderFasTuner(BMCDataContainer d){
    strcpy(d.str, "Tuner");
    d.crc = generateCrc(d);
    
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        fasHandler.renderTunerOled(oled[d.index], d);
      #endif
    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          fasHandler.renderTunerIli(tft, block[d.index], d);
        }
      #endif
    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        fasHandler.renderTunerMiniDisplay(miniDisplay[d.index], d);
      #endif
    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        fasHandler.renderTunerLcd(lcd, lcdLine[d.index], d);
      #endif
    }
  }
  void renderFasLooperIcon(BMCDataContainer d){
    d.crc = generateCrc(d);
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        fasHandler.renderLooperIconOled(oled[d.index], d);
      #endif
    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          fasHandler.renderLooperIconIli(tft, block[d.index], d);
        }
      #endif
    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        fasHandler.renderLooperIconMiniDisplay(miniDisplay[d.index], d);
      #endif
    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        lcdLine[d.index].print(lcd, d, d.str);
      #endif
    }
  }
  void renderFasLooper(BMCDataContainer d){
    d.crc = generateCrc(d);
    if(d.isOled()){
      #if BMC_MAX_OLED > 0
        __oledMuxSelect(d.index);
        fasHandler.renderLooperOled(oled[d.index], d);
      #endif
    } else if(d.isIli()){
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(allowRendering()){
          fasHandler.renderLooperIli(tft, block[d.index], d);
        }
      #endif
    } else if(d.isMiniDisplay()){
      #if BMC_MAX_MINI_DISPLAY > 0
        fasHandler.renderLooperMiniDisplay(miniDisplay[d.index], d);
      #endif
    } else if(d.isLcd()){
      #if BMC_MAX_LCD > 0
        lcdLine[d.index].print(lcd, d, d.str);
      #endif
    }
  }
#endif
  

  void update(){
#if BMC_MAX_ILI9341_BLOCKS > 0
  #if defined(BMC_HAS_TOUCH_SCREEN)
    // at boot BMC takes some time to light up all leds, start all drivers etc.
    // some of these like lighting up leds have use the delay function which
    // tends to cause issues with the touch driver causing it to 
    // think that there may have been a touch event when there was none.
    // for this reason at boot the touch screen is locked for 2 seconds
    // 2 seconds after the boot sequence is complete the touch screen will be enabled
    if(ignoreTouch){
      if(ignoreTouchTimer == 0){
        ignoreTouchTimer = millis();
      }
      if(millis()-ignoreTouchTimer >= 2000){
        BMC_PRINTLN("Touch Enabled");
        ignoreTouch = false;
      }
    }
    touchCommand = 0;
    if(touchTimer.complete()){
      touchPoint = touchScreen.getPoint();
      // BMC_PRINTLN("touch point x", touchPoint.x, "y", touchPoint.y);
      if(!globals.onBoardEditorActive()){
        if(touchEnter.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_TOGGLE;
            BMC_PRINTLN("Enter Editor");
          }
        }
      } else {

        if(touchPrev.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_PREV;
          }
          
      #if BMC_OBE_TOOLBAR_BUTTON_COUNT == 5
        } else if(touchShift.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_SHIFT;
          }
          
          // BMC_PRINTLN("SHIFT TOUCH");
      #endif
        } else if(touchHeaderBack.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_BACK;
          }
        } else if(touchHeaderExit.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_TOGGLE;
          }
          
        
        } else if(touchBack.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_BACK;
          }
          
        
        } else if(touchSelect.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_SELECT;
          }
          
        } else if(touchNext.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_NEXT;
          }
          
        } else if(touchCancel.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_CANCEL;
          }
          
        } else if(touchSave.isTouched(touchPoint.x, touchPoint.y)){
          if(!ignoreTouch){
            touchCommand = BMC_MENU_SAVE;
          }
          
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
    if(globals.onBoardEditorActive()){
      tempTimer.stop();
      return;
    }
  #endif
    if(tempTimer.complete()){
      globals.setDisplayRenderDisable(false);
      tft.display.fillScreen(BMC_ILI9341_BLACK);
      reassignIliBlocks(true);
    }
#endif
  }
  uint8_t getTouchCommand(){
#if defined(BMC_HAS_TOUCH_SCREEN)
    return touchCommand;
#else
    return 0;
#endif
  }
#if BMC_MAX_OLED > 0
  BMC_SSD1306 & get(uint8_t n){
    n = constrain(n, 0, BMC_MAX_OLED-1);
    __oledMuxSelect(n);
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

void setSelChar(uint8_t n, bool isOled, uint8_t selChar){
  #if BMC_MAX_OLED > 0
    if(isOled){
      if(selChar != oled[n].getSelChar()){
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


void renderBlock(BMCDataContainer d){
  if(d.useMeter() && d.allowMeter){
    d.value = d.valueSelected;
    renderSlider(d);
    return;
  }
  if(d.useSelected()){
    d.highlight = false;
  }
  
  char outStr[40] = "";
  d.crc = generateCrc(d);
  handleData(d, outStr);
  strcpy(d.str, outStr);

  if(d.isOled()){
    #if BMC_MAX_OLED > 0
      __oledMuxSelect(d.index);
      oled[d.index].print(d, outStr);
    #endif

  } else if(d.isIli()){
    #if BMC_MAX_ILI9341_BLOCKS > 0
      if(allowRendering()){
        block[d.index].print(tft.display, d.crc, d.str, d.label, d.highlight);
      }
    #endif

  } else if(d.isMiniDisplay()){
    #if BMC_MAX_MINI_DISPLAY > 0
      miniDisplay[d.index].print(d.crc, d.str, d.label, d.highlight);
    #endif

  } else if(d.isLcd()){
    #if BMC_MAX_LCD > 0
      lcdLine[d.index].print(lcd, d, d.str);
    #endif
  }
}


#if BMC_MAX_ILI9341_BLOCKS > 0
void blackoutIli(uint8_t index){
  if(!block[index].isCrc(0)){
    block[index].blackout(tft.display);
  }
}
void blackoutIliScreen(){
   tft.clear();
}
#endif


#if BMC_MAX_OLED > 0
void blackoutOled(uint8_t index){
  if(!oled[index].isCrc(0)){
    __oledMuxSelect(index);
    oled[index].blackout();
  }
}
#endif


#if BMC_MAX_MINI_DISPLAY > 0
void blackoutMiniDisplay(uint8_t index){
  if(!miniDisplay[index].isCrc(0)){
    miniDisplay[index].blackout();
  }
}
void setMiniDisplayLine(uint8_t index, uint8_t n){
  miniDisplay[index].setLineIndex(n);
}
#endif


#if BMC_MAX_LCD > 0
void blackoutLcd(uint8_t index){
  if(!lcdLine[index].isCrc(0)){
    lcdLine[index].blackout(lcd);
  }
}
  
#endif



void handleData(BMCDataContainer d, char * t_str){
  if(d.useStringOnly()){
    strcpy(t_str, d.str);
    return;
  }
  uint16_t value = 0;
  char str[40] = "";
  if(!d.useOffset){
    d.offset = 0;
  }
  if(d.useSelected()){
    value = d.valueSelected + d.offset;
    strcpy(str, d.strSelected);
  } else {
    value = d.value + d.offset;
    strcpy(str, d.str);
  }
  if(d.useName()){
    int len = 40-(d.digits+3);
    if(d.prependValue && len > 0){
      char buff[40] = "";
      strcpy(buff, str);
      buff[(uint8_t)len] = 0;
      if(d.digits == 4){
        sprintf(t_str, "%04u: %s", value, buff);
      } else if(d.digits == 3){
        sprintf(t_str, "%03u: %s", value, buff);
      } else if(d.digits == 2){
        sprintf(t_str, "%02u: %s", value, buff);
      } else {
        sprintf(t_str, "%01u: %s", value, buff);
      }
    } else {
      strcpy(t_str, str);
    }
    
  } else {
    if(strlen(d.format)>0){
      sprintf(t_str, d.format, value);
    } else {
      sprintf(t_str, "%u", value);
    }
  }
}


void renderSlider(BMCDataContainer d){
  char crcStr[32] = "";
  sprintf(crcStr, "sli%u/%u/%u", d.value, d.min, d.max);
  d.crc = checkLast(d.type, crcStr);
  
  if(d.isOled()){
#if BMC_MAX_OLED > 0
    __oledMuxSelect(d.index);
    mainHandler.renderSliderOled(oled[d.index], d);
#endif
  } else if(d.isIli()){
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(allowRendering()){
      mainHandler.renderSliderIli(tft, block[d.index], d);
    }
#endif
  } else if(d.isMiniDisplay()){
#if BMC_MAX_MINI_DISPLAY > 0
      mainHandler.renderSliderMiniDisplay(miniDisplay[d.index], d);
#endif
  } else if(d.isLcd()){
#if BMC_MAX_LCD > 0
    lcdLine[d.index].printSlider(lcd, d);
#endif
  }
}

bool isXlBlock(bool isOled, uint8_t n){
  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!isOled && n < BMC_MAX_ILI9341_BLOCKS){
      return (block[n].getWidth() == BMC_TFT_WIDTH && block[n].getHeight() == 80);
    }
  #endif
  return false;
}


void renderMidi(BMCDataContainer d){
  d.crc = generateCrc(d);
  if(d.isOled()){
    #if BMC_MAX_OLED > 0
      __oledMuxSelect(d.index);
      mainHandler.renderMidiOled(oled[d.index], d);
    #endif
  } else if(d.isIli()){
    #if BMC_MAX_ILI9341_BLOCKS > 0
      mainHandler.renderMidiIli(tft, block[d.index], d);
    #endif
  } else if(d.isMiniDisplay()){
    #if BMC_MAX_MINI_DISPLAY > 0
      mainHandler.renderMidiMiniDisplay(miniDisplay[d.index], d);
    #endif
  } else if(d.isLcd()){
    #if BMC_MAX_LCD > 0
      lcdLine[d.index].print(lcd, d, d.str);
    #endif
  }
}


public:
  BMCMidi& midi;
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCDisplayHandlerMain mainHandler;

#if defined(BMC_USE_SYNC)
  BMCSync& sync;

  #if defined(BMC_USE_DAW_LC)
    BMCDisplayHandlerDaw dawHandler;
  #endif
  
  #if defined(BMC_USE_FAS)
    BMCDisplayHandlerFas fasHandler;
  #endif
#endif



#if BMC_MAX_ILI9341_BLOCKS > 0
  // tft must be public for on board editor use
  BMC_ILI tft = BMC_ILI();
  BMC_ILI_BLOCK block[BMC_MAX_ILI9341_BLOCKS];
  BMCTimer tempTimer;
  #if defined(BMC_HAS_TOUCH_SCREEN)
  XPT2046_Touchscreen touchScreen = XPT2046_Touchscreen(BMC_ILI_TOUCH_CS, BMC_ILI_TOUCH_IRQ);
  TS_Point touchPoint;
  BMCTimer touchTimer;
  bool ignoreTouch = true;
  unsigned long ignoreTouchTimer = 0;
  
  bmcTouchArea touchHeaderBack;
  bmcTouchArea touchHeaderExit;
  bmcTouchArea touchPrev;
  bmcTouchArea touchBack;
  #if BMC_OBE_TOOLBAR_BUTTON_COUNT == 5
    bmcTouchArea touchShift;
  #endif
  bmcTouchArea touchSelect;
  bmcTouchArea touchNext;
  bmcTouchArea touchEnter;
  bmcTouchArea touchCancel;
  bmcTouchArea touchSave;
  uint8_t touchCommand = 0;
  #endif
#endif

#if BMC_MAX_OLED > 0
  BMC_OLED oled[BMC_MAX_OLED];
#endif

#if BMC_MAX_MINI_DISPLAY > 0
  BMC_MINI_DISPLAY miniDisplay[BMC_MAX_MINI_DISPLAY];
#endif

#if BMC_MAX_LCD > 0
  BMC_LCD lcd;
  BMC_LCD_LINE lcdLine[BMC_MAX_LCD];
#endif

private:
#if BMC_MAX_SETLISTS > 0 || BMC_MAX_PRESETS > 0 || BMC_MAX_LAYERS > 1
  uint16_t listPageCurrent = 0;
  uint16_t listLastSelection = 0;
#endif

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
    crc ^= len;
    return crc;
  }
  uint8_t generateCrc(BMCDataContainer d){
    uint8_t c = 0;
    if(d.useSelected() && !d.useStringOnly()){
      c += checkLast(d.type, d.strSelected) + (strlen(d.strSelected) * d.valueSelected);
    } else {
      c += checkLast(d.type, d.str) + (strlen(d.str) * d.value);
    }
    c += d.byteA+d.byteB+d.byteC+d.byteD;
    c += (d.highlight*2);
    c += d.prependValue;
    c ^= d.settings;
    c ^= d.colors;
    return c;
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
