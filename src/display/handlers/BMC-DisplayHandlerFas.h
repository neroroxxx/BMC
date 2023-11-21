/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DISPLAY_HANDLER_FAS_H
#define BMC_DISPLAY_HANDLER_FAS_H
#include "utility/BMC-Def.h"

#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_FAS)

// can be overriden on sketch
#if !defined(BMC_DHFAS_TUNER_ARROWS)
  // tuner arrows color
  #define BMC_DHFAS_TUNER_ARROWS BMC_ILI9341_YELLOW
#endif

#if !defined(BMC_DHFAS_TUNER_NEEDLE)
  // tuner ball color
  #define BMC_DHFAS_TUNER_NEEDLE BMC_ILI9341_CYAN
#endif

#if !defined(BMC_DHFAS_TUNER_NOTE)
  // tuner border and text
  #define BMC_DHFAS_TUNER_NOTE BMC_ILI9341_WHITE
#endif

#if !defined(BMC_DHFAS_LOOPER_REC)
  #define BMC_DHFAS_LOOPER_REC BMC_ILI9341_RED
#endif

#if !defined(BMC_DHFAS_LOOPER_PLAY)
  #define BMC_DHFAS_LOOPER_PLAY BMC_ILI9341_GREEN
#endif



#if !defined(BMC_DHFAS_STATUS_PRESET_NUMBER)
  #define BMC_DHFAS_STATUS_PRESET_NUMBER BMC_ILI9341_WHITE
#endif

#if !defined(BMC_DHFAS_STATUS_PRESET_NAME)
  #define BMC_DHFAS_STATUS_PRESET_NAME BMC_ILI9341_YELLOW
#endif

#if !defined(BMC_DHFAS_STATUS_SCENE_NAME)
  #define BMC_DHFAS_STATUS_SCENE_NAME BMC_ILI9341_WHITE
#endif
   
      
       

class BMCDisplayHandlerFas {
public:
  BMCMidi& midi;
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCSync& sync;
  bmcDisplayIndexSel tunerBlock;
  bmcDisplayIndexSel looperBlock;
  bmcDisplayIndexSel statusBlock;
  bmcDisplayIndexSel statusTunerBlock;
  BMCTunerData statusTunerData;
  BMCTunerData tunerData;
  uint8_t beats = 0;
  uint8_t looperData = 0xFF;
  uint8_t statusLooperData = 0xFF;
  uint8_t looperStatesData = 0xFF;
  bool connected = false;
  uint16_t preset = 0xFFFF;
  uint8_t scene = 0xFF;
  char presetName[BMC_FAS_MAX_PRESET_NAME] = "";
  #if defined(BMC_USE_FAS3)
  char sceneName[BMC_FAS_MAX_PRESET_NAME] = "";
  #endif
  void reset(){
    tunerBlock.reset();
    looperBlock.reset();
    statusBlock.reset();
    statusTunerBlock.reset();
    looperData = 0xFF;
    statusLooperData = 0xFF;
    looperStatesData = 0xFF;
    // for status block
    connected = false;
    preset = 0xFFFF;
    scene = 0xFF;
    strcpy(presetName, "");
    #if defined(BMC_USE_FAS3)
    strcpy(sceneName, "");
    #endif
  }
  // BMCFlags <uint8_t> flags;

  BMCDisplayHandlerFas(BMCMidi& t_midi, BMCSync& t_sync):
    midi(t_midi),
    globals(t_midi.globals),
    store(t_midi.globals.store),
    settings(t_midi.globals.settings),
    sync(t_sync)
  {
    
  }
  void begin(){
    BMC_PRINTLN("BMCDisplayHandlerFas::begin()");
    reassign();
  }
  void update(){

  }
  void reassign(){
    reset();
  }


  // ******************************************************
  // *********************** STATUS ************************
  // ******************************************************
#if BMC_MAX_ILI9341_BLOCKS > 0
  bool renderStatusIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, bool t_reset=false){
    BMC_TFT& display = tft.display;
    if(block.getWidth() != BMC_TFT_WIDTH  || block.getHeight() != 80){
      block.print(display, d.crc, d.str, "FAS", sync.fas.connected());
      return false;
    }
    if(statusBlock.index < 0){
      statusBlock.reset();
      statusBlock.index = d.index;
      statusBlock.type = BMC_DEVICE_ID_ILI;
      t_reset = true;
    } else if(!statusBlock.isIli() || statusBlock.index != d.index){
      block.print(display, d.crc, d.str, "FAS", sync.fas.connected());
      return false;
    }
    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());

    if(statusBlock.active != sync.fas.connected()){
      statusBlock.active = sync.fas.connected();
      display.fillRect(t.x, t.y, t.w, t.h, BMC_ILI9341_BLACK);
      if(statusBlock.active){
        t_reset = true;
      }
    }
    if(!statusBlock.active){
      block.print(display, d.crc, d.str, "FAS", sync.fas.connected());
      return true;
    }

    if(statusTunerBlock.active != sync.fas.tuner.isOn()){
      statusTunerBlock.active = sync.fas.tuner.isOn();
      display.fillRect(t.x, t.y, t.w, t.h, BMC_ILI9341_BLACK);
      t_reset = true;
      preset = 0xFFFF;
    }

    if(statusTunerBlock.active){
      t.setColor(BMC_DHFAS_TUNER_ARROWS, BMC_DHFAS_TUNER_NEEDLE, BMC_DHFAS_TUNER_NOTE);
      renderTuner<BMC_TFT>(display, statusTunerData, t, t_reset);
      return true;
    }
    
    t.setColor(BMC_DHFAS_LOOPER_REC, BMC_DHFAS_LOOPER_PLAY, BMC_ILI9341_WHITE);
    t.mirror = true; // used for mini looper status
    renderLooper<BMC_TFT>(display, statusLooperData, t, t_reset);

    uint8_t xPadding = 50;

    #if defined(BMC_USE_FAS3)
    
    // for Axe Fx 3, FM3, FM9
    char sName[BMC_FAS3_MAX_SCENE_NAME] = "";
    sync.fas.getSceneName(sName);
    uint16_t currentScene = sync.fas.getSceneNumber();
    if(currentScene < 8 && (scene != currentScene || !BMC_STR_MATCH(sceneName, sName) || t_reset)){
      // display.fillRect(t.x+xPadding, t.y+52, t.w, t.h-52, BMC_ILI9341_BLACK);
      // if(strlen(sName) > 0){
      //   block.findFontSize(display, sName, 0, t.w, 28);
      // } else {
      //   display.setFont(BMC_FONT_MD);
      // }
      char nBuff[30];
      sprintf(nBuff,"Scene %d %s",currentScene+globals.offset, sName);

      BMCTextPixelSize tt = display.getCenteredXY(nBuff, t.x+xPadding, t.y+50, t.w-xPadding, 30, 2);
      if(!t_reset){
        display.fillRect(t.x+xPadding, t.y+50, t.w-xPadding, 30, BMC_ILI9341_BLACK);
      }
      
      display.setTextWrap(false);

      display.setCursor(t.x+xPadding, tt.y);
      display.setTextColor(BMC_ILI9341_GRAY_22);
      display.print("Scene ");
      display.print(currentScene+globals.offset);
      display.print(" ");
      display.setTextColor(BMC_DHFAS_STATUS_SCENE_NAME);
      display.print(sName);

      scene = currentScene;
      strcpy(sceneName, sName);
    }

    #else
    // for Axe Fx 2 and AX8
    uint16_t currentScene = sync.fas.getSceneNumber();
    if(scene != currentScene || t_reset){

      BMCTextPixelSize tt = display.getCenteredXY("Scene 1", t.x+xPadding, t.y+50, t.w-xPadding, 30, 2);
      if(!t_reset){
        display.fillRect(t.x+xPadding, t.y+50, t.w-xPadding, 30, BMC_ILI9341_BLACK);
      }
      display.setTextWrap(false);

      display.setCursor(t.x+xPadding, tt.y);
      display.setTextColor(BMC_ILI9341_GRAY_22);
      display.print("Scene ");
      display.setTextColor(BMC_DHFAS_STATUS_SCENE_NAME);
      display.print(currentScene+globals.offset);

      scene = currentScene;
    }

    #endif

    
    char pName[BMC_FAS_MAX_PRESET_NAME] = "";
    sync.fas.getPresetName(pName);
    uint16_t currentPreset = sync.fas.getPresetNumber();
    if(currentPreset < 0xFFFF && (preset != currentPreset || !BMC_STR_MATCH(presetName, pName) || t_reset)){
      preset = currentPreset;
      
      if(!t_reset){
        display.fillRect(t.x+xPadding, t.y, t.w-xPadding, 50, BMC_ILI9341_BLACK);
      }

      strcpy(presetName, pName);
      char num[8] = "";
      sprintf(num, "%04u", preset+globals.offset);

      char nBuff[40];
      sprintf(nBuff,"0000 %s", presetName);


      BMCTextPixelSize tt = display.getCenteredXY(nBuff, t.x+xPadding, t.y, t.w-xPadding, 50, 4);
      
      display.setTextWrap(false);

      display.setCursor(t.x+xPadding, tt.y);
      display.setTextColor(BMC_DHFAS_STATUS_PRESET_NUMBER);
      display.print(num);
      display.print(" ");

      display.setTextColor(BMC_DHFAS_STATUS_PRESET_NAME);
      display.print(pName);
    }
    t.color = BMC_ILI9341_BLUE;
    renderBeatBar<BMC_TFT>(display, beats, t, t_reset);
    block.setCrc(d.crc);
    return true;
  }
#endif

#if BMC_MAX_OLED > 0
  bool renderStatusOled(BMC_OLED& block, BMCDataContainer d){
    BMC_SSD1306& display = block.display;
    bool t_reset = false;
    if(statusBlock.index < 0){
      statusBlock.reset();
      statusBlock.index = d.index;
      statusBlock.type = BMC_DEVICE_ID_OLED;
      t_reset = true;
    } else if(!statusBlock.isOled() || statusBlock.index != d.index){
      block.print(d, d.str);
      return false;
    }
    if(statusBlock.active != sync.fas.connected()){
      statusBlock.active = sync.fas.connected();
      t_reset = true;
    }
    if(!statusBlock.active){
      block.print(d, d.str);
      return false;
    }

    if(statusTunerBlock.active != sync.fas.tuner.isOn()){
      statusTunerBlock.active = sync.fas.tuner.isOn();
      t_reset = true;
    }
    if(t_reset){
      display.fillScreen(BMC_OLED_BLACK);
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;

    if(statusTunerBlock.active){
      if(renderTuner<BMC_SSD1306>(display, statusTunerData, t, t_reset)){
        display.display();
      }
      return true;
    }
    bool show = false;
    if(renderLooper<BMC_SSD1306>(display, statusLooperData, t, t_reset)){
      show = true;
    }
    if(renderBeatBar<BMC_SSD1306>(display, beats, t, t_reset)){
      show = true;
    }
    if(show){
      display.display();
    }
    return true;
  }
#endif






#if BMC_MAX_LCD > 0
  bool renderStatusLcd(BMC_LCD& lcd, BMC_LCD_LINE& line, BMCDataContainer d, bool t_reset=false){
    // lcd.display;
    if(statusBlock.index < 0){
      statusBlock.reset();
      statusTunerData.reset();
      statusBlock.index = d.index;
      statusBlock.type = BMC_DEVICE_ID_LCD;
      t_reset = true;
    } else if(!statusBlock.isLcd() || statusBlock.index != d.index){
      
      line.print(lcd, d, d.str);
      return false;
    }

    if(statusBlock.active != sync.fas.connected()){
      statusBlock.active = sync.fas.connected();
      if(!statusBlock.active){
        line.print(lcd, d, d.str);
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!statusBlock.active){
      line.print(lcd, d, d.str);
      return true;
    }

    if(statusTunerBlock.active != sync.fas.tuner.isOn()){
      statusTunerBlock.active = sync.fas.tuner.isOn();
      t_reset = true;
      preset = 0xFFFF;
      line.clear(lcd);
    }


    if(statusTunerBlock.active){
      lcdTuner(lcd, line, statusTunerData, d.index, t_reset);
    } else {
      char pName[BMC_FAS_MAX_PRESET_NAME] = "";
      sync.fas.getPresetName(pName);
      uint16_t currentPreset = sync.fas.getPresetNumber();
      if(currentPreset < 0xFFFF && (preset != currentPreset || !BMC_STR_MATCH(presetName, pName))){
        preset = currentPreset;
        strcpy(presetName, pName);
        char buff[46] = "";
        sprintf(buff, "%04u %s", preset+globals.offset, pName);
        line.print(lcd, d, buff);
      }
    }    
    return true;
  }
  bool renderTunerLcd(BMC_LCD& lcd, BMC_LCD_LINE& line, BMCDataContainer d, bool t_reset=false){
    if(tunerBlock.index < 0){
      tunerBlock.reset();
      tunerBlock.index = d.index;
      tunerBlock.type = BMC_DEVICE_ID_LCD;
      t_reset = true;
    } else if(!statusBlock.isLcd() || statusBlock.index != d.index){
      line.print(lcd, d, "Tuner");
      return false;
    }

    if(tunerBlock.active != sync.fas.tuner.isOn()){
      tunerBlock.active = sync.fas.tuner.isOn();
      if(!tunerBlock.active){
        line.print(lcd, d, "Tuner");
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!tunerBlock.active){
      line.print(lcd, d, "Tuner");
      return true;
    }
    lcdTuner(lcd, line, tunerData, d.index, t_reset);
    return true;
  }
  void lcdTuner(BMC_LCD& lcd, BMC_LCD_LINE& line, BMCTunerData& t_tunerData, uint8_t index, bool t_reset=false){
    BMCTunerData currentTuner;
    sync.fas.getTunerData(currentTuner);
    if((currentTuner.pitchRaw != t_tunerData.pitchRaw) || t_reset){
      uint8_t pitch = map(currentTuner.pitchRaw, 0, 127, 0, BMC_LCD_CHARS-1);
      char buff[BMC_LCD_CHARS+1] = "";
      memset(buff, 32, sizeof(buff[0])*BMC_LCD_CHARS);
      lcd.display.setCursor(0, index);
      uint8_t center = (BMC_LCD_CHARS/2);
      if(pitch < (center-1)){
        buff[pitch] = '>';
      } else if(pitch > center){
        buff[pitch] = '<';
      } else {
        buff[center-1] = '>';
        buff[center] = '<';
      }
      lcd.display.print(buff);
    }
    t_tunerData = currentTuner;
  }
#endif







  // ******************************************************
  // *********************** BLOCKS ************************
  // ******************************************************

  // OLEDs will just print the block name and channel/xy
#if BMC_MAX_ILI9341_BLOCKS > 0
  bool renderBlockIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, uint8_t crc, uint8_t index, bool t_reset=false){
    BMC_TFT& display = tft.display;
    if(block.isCrc(crc)){
      return true;
    }
    block.setCrc(crc);

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    
    // uint16_t fontData = block.findFontSize(display, d.str, 0, t.w, t.h);
    // renderFxBlock<BMC_TFT>(display, d, t, fontData);
    renderFxBlock<BMC_TFT>(display, d, t);
    return true;
  }
#endif

#if BMC_MAX_MINI_DISPLAY > 0
  bool renderBlockMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d){
    BMC_MD_DRIVER& display = block.display;
    if(block.isCrc(d.crc)){
      return true;
    }
    block.setCrc(d.crc);

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    // uint16_t fontData = block.findFontSize(display, d.str, 0, t.w, t.h);
    // renderFxBlock<BMC_MD_DRIVER>(display, d, t, fontData);
    renderFxBlock<BMC_MD_DRIVER>(display, d, t);
    return true;
  }
#endif

  // ******************************************************
  // *********************** TUNER ************************
  // ******************************************************

  // ***************************
  // ********** OLED ***********
  // ***************************
#if BMC_MAX_OLED > 0
  bool renderTunerOled(BMC_OLED& block, BMCDataContainer d){
    BMC_SSD1306& display = block.display;
    bool t_reset = false;
    if(tunerBlock.index < 0){
      tunerBlock.reset();
      tunerBlock.index = d.index;
      tunerBlock.type = BMC_DEVICE_ID_OLED;
      t_reset = true;
    } else if(!tunerBlock.isOled() || (tunerBlock.index != d.index)){
      block.print(d, "Tuner");
      return false;
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;

    if(tunerBlock.active != sync.fas.tuner.isOn()){
      tunerBlock.active = sync.fas.tuner.isOn();
      tunerData.reset();
      display.fillRect(t.x, t.y, t.w, t.h, t.background);
      if(!tunerBlock.active){
        block.print(d, "Tuner");
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!tunerBlock.active){
      block.print(d, "Tuner");
      return false;
    }
    if(renderTuner<BMC_SSD1306>(display, tunerData, t, t_reset)){
      block.setCrc(millis()&0xFF);
      display.display();
      return true;
    }
    return false;
  }
  
  bool renderLooperIconOled(BMC_OLED& block, BMCDataContainer d, bool t_reset=true){
    if(block.isCrc(d.crc)){
      return false;
    }
    block.setCrc(d.crc);

    BMC_SSD1306& display = block.display;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;
    switch(d.byteA){
      case BMC_FAS_CMD_LOOPER_PLAY:
        display.clearDisplay();
        renderTriangle<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_REV:
        t.mirror = true;
        display.clearDisplay();
        renderTriangle<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_REC:
        display.clearDisplay();
        renderCircle<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_DUB:
        display.clearDisplay();
        renderCircle<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_ONCE:
        display.clearDisplay();
        renderRoundSquare<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_HALF:
        block.print(d, "1/2");
        break;
      case BMC_FAS_CMD_LOOPER_UNDO:
        block.print(d, "UNDO");
        break;
      case BMC_FAS_CMD_LOOPER_STOP:
        display.clearDisplay();
        renderSquare<BMC_SSD1306>(display, d, t, t_reset);
        display.display();
        break;
      case BMC_FAS_CMD_LOOPER_CLEAR:
        block.print(d, "CLEAR");
        break;
      default:
        return false;
    }
    return true;
  }
  bool renderLooperOled(BMC_OLED& block, BMCDataContainer d){
    BMC_SSD1306& display = block.display;
    bool t_reset = false;
    if(looperBlock.index < 0){
      looperBlock.reset();
      looperBlock.index = d.index;
      looperBlock.type = BMC_DEVICE_ID_OLED;
      t_reset = true;
      looperData = 0xFF;
    } else if(!looperBlock.isOled() || looperBlock.index != d.index){
      block.print(d, d.str);
      return false;
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;
    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    if(looperBlock.active != sync.fas.connected()){
      looperBlock.active = sync.fas.connected();
      looperData = 0xFF;

      display.fillRect(t.x, t.y, t.w, t.h, t.background);
      if(!looperBlock.active){
        block.print(d, "Not Connected");
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!looperBlock.active){
      block.print(d, "Not Connected");
      return false;
    }
    if(renderLooper<BMC_SSD1306>(display, looperData, t, t_reset)){
      display.display();
    }
    block.setCrc(d.crc);
    return true;
  }
#endif

  // ***************************
  // ****** MINI DISPLAY *******
  // ***************************


#if BMC_MAX_MINI_DISPLAY > 0
  bool renderTunerMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d){
    BMC_MD_DRIVER& display = block.display;
    bool t_reset = false;
    if(tunerBlock.index < 0){
      tunerBlock.reset();
      tunerBlock.index = d.index;
      tunerBlock.type = BMC_DEVICE_ID_MINI_DISPLAY;
      t_reset = true;
    } else if(!tunerBlock.isMiniDisplay() || tunerBlock.index != d.index){
      block.print(d.crc, "Tuner", "", sync.fas.tuner.isOn());
      return false;
    }
    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());

    if(tunerBlock.active != sync.fas.tuner.isOn()){
      tunerBlock.active = sync.fas.tuner.isOn();
      tunerData.reset();
      display.fillRect(t.x, t.y, t.w, t.h, t.background);
      if(!tunerBlock.active){
        block.print(d.crc, "Tuner", "", sync.fas.tuner.isOn());
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!tunerBlock.active){
      block.print(d.crc, "Tuner", "", sync.fas.tuner.isOn());
      return true;
    }
    t.setColor(BMC_DHFAS_TUNER_ARROWS, BMC_DHFAS_TUNER_NEEDLE, BMC_DHFAS_TUNER_NOTE);

    renderTuner<BMC_MD_DRIVER>(display, tunerData, t, t_reset);
    block.setCrc(d.crc);
    return true;
  }

  bool renderLooperIconMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d, bool t_reset=false){
    BMC_MD_DRIVER& display = block.display;

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    if(!block.isCrc(d.crc)){
      t_reset = true;
    } else {
      return false;
    }
    switch(d.byteA){
      case BMC_FAS_CMD_LOOPER_REC:
        renderCircle<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_DUB:
        renderCircle<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_PLAY:
        renderTriangle<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_REV:
        t.mirror = true;
        renderTriangle<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_STOP:
        renderSquare<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_ONCE:
        renderRoundSquare<BMC_MD_DRIVER>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_HALF:
        block.print(d.crc, "1/2", "LOOPER", d.highlight);
        break;
      case BMC_FAS_CMD_LOOPER_UNDO:
        block.print(d.crc, "UNDO", "LOOPER", false);
        break;
      case BMC_FAS_CMD_LOOPER_CLEAR:
        block.print(d.crc, "CLEAR", "LOOPER", false);
        break;
    }
    block.setCrc(d.crc);
    return true;
  }
  bool renderLooperMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d, bool t_reset=false){
    BMC_MD_DRIVER& display = block.display;

    if(looperBlock.index < 0){
      looperBlock.reset();
      looperBlock.index = d.index;
      looperBlock.type = BMC_DEVICE_ID_MINI_DISPLAY;
      t_reset = true;
      looperData = 0xFF;
    } else if(!looperBlock.isMiniDisplay() || looperBlock.index != d.index){
      block.print(d.crc, d.str, "", sync.fas.tuner.isOn());
      return false;
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(BMC_DHFAS_LOOPER_REC, BMC_DHFAS_LOOPER_PLAY, BMC_ILI9341_WHITE);

    if(looperBlock.active != sync.fas.connected()){
      looperBlock.active = sync.fas.connected();
      looperData = 0xFF;
      display.fillRect(t.x, t.y, t.w, t.h, t.background);
      if(!looperBlock.active){
        block.print(d.crc, d.str, "", false);
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!looperBlock.active){
      block.print(d.crc, "Not Connected", "", false);
      return true;
    }
    renderLooper<BMC_MD_DRIVER>(display, looperData, t, t_reset);
    block.setCrc(d.crc);
    return true;
  }
#endif

  // ***************************
  // ********** ILI ***********
  // ***************************
#if BMC_MAX_ILI9341_BLOCKS > 0
  bool renderTunerIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, bool t_reset=false){
    BMC_TFT& display = tft.display;
    if(block.getWidth() < 120){
      block.print(display, d.crc, "Tuner", "", sync.fas.tuner.isOn());
      return false;
    }
    if(tunerBlock.index < 0){
      tunerBlock.reset();
      tunerBlock.index = d.index;
      tunerBlock.type = BMC_DEVICE_ID_ILI;
      t_reset = true;
    } else if(!tunerBlock.isIli() || tunerBlock.index != d.index){
      block.print(display, d.crc, "Tuner", "", sync.fas.tuner.isOn());
      return false;
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(BMC_DHFAS_TUNER_ARROWS, BMC_DHFAS_TUNER_NEEDLE, BMC_DHFAS_TUNER_NOTE);

    // set where y will be, for 128x32 display start at 0.
    // for 128x64 start at 16
    // uint16_t x = block.getX();
    // uint16_t y = block.getY();
    // uint16_t w = block.getWidth();
    // uint16_t h = block.getHeight();

    if(tunerBlock.active != sync.fas.tuner.isOn()){
      tunerBlock.active = sync.fas.tuner.isOn();
      tunerData.reset();
      display.fillRect(t.x, t.y, t.w, t.h, t.background);
      if(!tunerBlock.active){
        block.print(display, d.crc, "Tuner", "", sync.fas.tuner.isOn());
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!tunerBlock.active){
      block.print(display, d.crc, "Tuner", "", sync.fas.tuner.isOn());
      return true;
    }
    // BMCDiplayHandlerData t;
    // t.x = x;
    // t.y = y;
    // t.w = w;
    // t.h = h;
    // t.color = BMC_ILI9341_GREEN;
    // t.color2 = BMC_ILI9341_RED;
    // t.color3 = BMC_ILI9341_WHITE;
    // t.background = BMC_ILI9341_BLACK;
    // t.colorMode = 16;
    renderTuner<BMC_TFT>(display, tunerData, t, t_reset);
    block.setCrc(d.crc);
    return true;
  }
  bool renderLooperIconIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, bool t_reset=false){
    BMC_TFT& display = tft.display;
    // BMCDiplayHandlerData t;
    // t.x = block.getX();
    // t.y = block.getY();
    // t.w = block.getWidth();
    // t.h = block.getHeight();
    // t.color = block.getColor();
    // t.background = block.getBackground();
    // t.colorMode = 16;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());
    if(!block.isCrc(d.crc)){
      t_reset = true;
    } else {
      return false;
    }
    switch(d.byteA){
      case BMC_FAS_CMD_LOOPER_REC:
        renderCircle<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_DUB:
        renderCircle<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_PLAY:
        renderTriangle<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_REV:
        t.mirror = true;
        renderTriangle<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_STOP:
        renderSquare<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_ONCE:
        renderRoundSquare<BMC_TFT>(display, d, t, t_reset);
        break;
      case BMC_FAS_CMD_LOOPER_HALF:
        block.print(tft.display, d.crc, "1/2", "LOOPER", d.highlight);
        break;
      case BMC_FAS_CMD_LOOPER_UNDO:
        block.print(tft.display, d.crc, "UNDO", "LOOPER", false);
        break;
      case BMC_FAS_CMD_LOOPER_CLEAR:
        block.print(tft.display, d.crc, "CLEAR", "LOOPER", false);
        break;
    }
    block.setCrc(d.crc);
    return true;
  }
  bool renderLooperIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, bool t_reset=false){
    BMC_TFT& display = tft.display;
    if(block.getWidth() < 120){
      block.print(display, d.crc, "Looper", "", sync.fas.looperGetState());
      return false;
    }
    if(looperBlock.index < 0){
      looperBlock.reset();
      looperBlock.index = d.index;
      looperBlock.type = BMC_DEVICE_ID_ILI;
      t_reset = true;
      looperData = 0xFF;
    } else if(!looperBlock.isIli() || looperBlock.index != d.index){
      block.print(display, d.crc, d.str, "", sync.fas.tuner.isOn());
      return false;
    }

    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(BMC_DHFAS_LOOPER_REC, BMC_DHFAS_LOOPER_PLAY, BMC_ILI9341_WHITE);

    if(looperBlock.active != sync.fas.connected()){
      looperBlock.active = sync.fas.connected();
      looperData = 0xFF;
      display.fillRect(t.x, t.y, t.w, t.h, BMC_ILI9341_BLACK);
      if(!looperBlock.active){
        block.print(display, d.crc, d.str, "", false);
        return false;
      } else {
        t_reset = true;
      }
    }
    if(!looperBlock.active){
      block.print(display, d.crc, "Not Connected", "", false);
      return true;
    }
    renderLooper<BMC_TFT>(display, looperData, t, t_reset);
    block.setCrc(d.crc);
    return true;
  }
#endif

template <typename T>
  bool renderTriangle(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
    uint16_t iconSize = t.h-4;
    uint16_t centerX = t.w/2;
    uint16_t centerY = t.h/2;
    if(t.h > t.w){
      iconSize = t.w-4;
    }
    if(t.h >= 64){
      iconSize -= 8;
    } else {
      iconSize -= 4;
    }
    uint8_t halfIcon = iconSize/2;
    uint8_t thickness = 2;
    if(!t.mirror){
      // TRIANGLE
      uint16_t x0 = (centerX-halfIcon);
      uint16_t x1 = x0;
      uint16_t x2 = (centerX+halfIcon);
      uint16_t y0 = t.h - ((t.h-iconSize)/2);
      uint16_t y1 = (t.h-iconSize)/2;
      uint16_t y2 = centerY;
      if(t_reset){
        display.fillTriangle(t.x+x0, t.y+y0, t.x+x1, t.y+y1, t.x+x2, t.y+y2, t.color);
      }
      display.fillTriangle(t.x+x0+thickness, (t.y+y0)-(thickness*2), t.x+x1+thickness, (t.y+y1)+(thickness*2), (t.x+x2)-(thickness*2), t.y+y2, d.highlight?t.color:t.background);  
    } else {
      uint16_t x0 = (centerX+halfIcon);
      uint16_t x1 = x0;
      uint16_t x2 = (centerX-halfIcon);
      uint16_t y0 = t.h - ((t.h-iconSize)/2);
      uint16_t y1 = (t.h-iconSize)/2;
      uint16_t y2 = centerY;
      if(t_reset){
        display.fillTriangle(t.x+x0, t.y+y0, t.x+x1, t.y+y1, t.x+x2, t.y+y2, t.color);
      }
      display.fillTriangle((t.x+x0)-thickness, (t.y+y0)-(thickness*2), (t.x+x1)-thickness, (t.y+y1)+(thickness*2), (t.x+x2)+(thickness*2), t.y+y2, d.highlight?t.color:t.background);  
    }
    return true;
  }
  template <typename T>
  bool renderCircle(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
    // BMC_SSD1306& display = block.display;
    uint16_t iconSize = t.h-4;
    uint16_t centerX = t.w/2;
    uint16_t centerY = t.h/2;
    if(t.h > t.w){
      iconSize = t.w-4;
    }
    if(t.h >= 64){
      iconSize -= 8;
    }
    uint8_t halfIcon = iconSize/2;
    uint8_t thickness = 2;
    // CIRCLE
    if(t_reset){
      display.fillCircle(t.x + centerX, t.y+centerY, halfIcon, t.color);
    }
    display.fillCircle(t.x + centerX, t.y+centerY, halfIcon-thickness, d.highlight?t.color:t.background);
    return true;
  }
  template <typename T>
  bool renderSquare(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
    // BMC_SSD1306& display = block.display;
    uint16_t iconSize = t.h-4;
    uint16_t centerX = t.w/2;
    // uint16_t centerY = t.h/2;
    if(t.h > t.w){
      iconSize = t.w-4;
    }
    if(t.h >= 64){
      iconSize -= 8;
    }
    uint8_t halfIcon = iconSize/2;
    uint8_t thickness = 2;
    if(t_reset){
      display.fillRect(t.x+(centerX-halfIcon), t.y+((t.h-iconSize)/2), iconSize, iconSize, t.color);
    }
    display.fillRect(t.x+(centerX-halfIcon)+thickness, t.y+((t.h-iconSize)/2)+thickness, iconSize-(thickness*2), iconSize-(thickness*2), d.highlight?t.color:t.background);
    return true;
  }
  template <typename T>
  bool renderRoundSquare(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
    // BMC_SSD1306& display = block.display;
    uint16_t iconSize = t.h-4;
    uint16_t centerX = t.w/2;
    // uint16_t centerY = t.h/2;
    if(t.h > t.w){
      iconSize = t.w-4;
    }
    if(t.h >= 64){
      iconSize -= 8;
    }
    uint8_t halfIcon = iconSize/2;
    uint8_t thickness = 2;
    if(t_reset){
      display.fillRoundRect(t.x+(centerX-halfIcon), t.y+((t.h-iconSize)/2), iconSize, iconSize, 4, t.color);
    }
    display.fillRoundRect(t.x+(centerX-halfIcon)+thickness, t.y+((t.h-iconSize)/2)+thickness, iconSize-(thickness*2), iconSize-(thickness*2), 4, d.highlight?t.color:t.background);
    return true;
  }

  template <typename T>
  bool renderFxBlock(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
  // bool renderFxBlock(T& display, BMCDataContainer d, BMCDiplayHandlerData t, uint16_t fontData, bool t_reset=false){
    if(!d.highlight){
      t.color       = BMC_ILI9341_GRAY_18;
      t.background  = BMC_ILI9341_BLACK;
    }
    display.printCenteredXY(d.str, t.x, t.y, t.w, t.h, 2, t.color, t.background);
    display.drawRect(t.x, t.y, t.w, t.h, t.color);
    return true;
  }

  template <typename T>
  bool renderTuner(T& display, BMCTunerData& t_tunerData, BMCDiplayHandlerData t, bool t_reset=false){
    uint16_t centerX = (t.w / 2);
    uint16_t centerY = (t.h / 2);
    uint16_t triW = t.w/5;
    BMCTunerData currentTuner;
    sync.fas.getTunerData(currentTuner);

    if((currentTuner.pitchRaw != t_tunerData.pitchRaw) || t_reset){
      // print note name
      if(currentTuner.note != t_tunerData.note || currentTuner.stringNumber != t_tunerData.stringNumber || t_reset){
        display.setFont();
        uint8_t fontSize = (uint8_t) floor(floor(t.h/2.0)/8.0);
        if((t.w == 128 && t.h == 64) || t.h == 40){
          fontSize = 2;
        } else if(t.w == 128 && t.h == 32){
          fontSize = 1;
        } else if(fontSize > 3){
          fontSize = 3;
        }
        uint16_t fY =  t.y+(((t.h/2.0) - (fontSize*8))/2);
        uint16_t fX = (t.x+t.w) - (fontSize*6);
        display.setTextSize(fontSize);
        display.setTextColor(t.color3);
        if(currentTuner.note != t_tunerData.note){
          display.setCursor(t.x, fY);
          display.fillRect(t.x, fY, ((fontSize*6)*2), (fontSize*8), t.background);
          display.print(currentTuner.noteName);
        }
        if(currentTuner.stringNumber != t_tunerData.stringNumber){
          display.setCursor(fX, fY);
          display.fillRect(fX, fY, (fontSize*6), (fontSize*8), t.background);
          display.print(currentTuner.stringNumber+1);
        }
        display.setTextSize(1);
      }
      uint16_t pitch = map(t_tunerData.pitchRaw, 0, 127, 12, t.w-12);
      uint16_t pitch2 = map(currentTuner.pitchRaw, 0, 127, 12, t.w-12);

      uint16_t color = (currentTuner.pitchRaw <= 64) ? t.color : t.background;
      triangleHelper(display, t.x+(centerX-(triW+6)), t.y, triW, centerY-4, color, false);

      color = (currentTuner.pitchRaw >= 62) ? t.color : t.background;
      triangleHelper(display, t.x+(centerX+6), t.y, triW, centerY-8, color, true);

      uint8_t circleY = t.y+(t.h*0.75);
      uint8_t circleRadius = (uint8_t) centerY*0.3;
      circleRadius = circleRadius < 6 ? 6 : circleRadius;
      display.fillCircle(t.x+pitch,  circleY, circleRadius, t.background);
      display.fillCircle(t.x+pitch2, circleY, circleRadius, t.color2);
      display.drawFastVLine(t.x+centerX, t.y, t.h, t.color3);
      display.drawRect(t.x+2, t.y+centerY, t.w-4, centerY, t.color3);

      t_tunerData = currentTuner;
      return true;
    }
    return false;
  }
  template <typename T>
  bool renderLooper(T& display, uint8_t& t_looperData, BMCDiplayHandlerData t, bool t_reset=false){
    sync.fas.enableLooperFetch(true);
    // space between the 2 icons
    uint8_t currentLooper = sync.fas.looperGetData();
    
    if(currentLooper != t_looperData || t_reset){
      bool recActive  = bitRead(currentLooper, 0);
      bool playActive = bitRead(currentLooper, 1);

      bool rec  = bitRead(currentLooper, 0) != bitRead(t_looperData, 0);
      bool play = bitRead(currentLooper, 1) != bitRead(t_looperData, 1);
      bool dub  = bitRead(currentLooper, 2) != bitRead(t_looperData, 2);

      BMCDataContainer d;
      BMCDiplayHandlerData tt = t;
      tt.mirror = false;

      if((rec || dub) || t_reset){
        d.highlight = recActive;
        if(!t.mirror){
          tt.x = t.x;
          tt.y = t.y;
          tt.w = t.w/2;
          tt.h = t.h;
          renderCircle(display, d, tt, t_reset);
        } else {
          // for status block
          tt.x = t.x+2;
          tt.y = t.y;
          tt.w = (t.h/2)-4;
          tt.h = tt.w;
          renderCircle(display, d, tt, t_reset);
        }
      }
      if((play || dub) || t_reset){
        d.highlight = playActive;
        tt.color = tt.color2;
        if(!t.mirror){
          tt.x = t.x + (t.w/2);
          tt.y = t.y;
          tt.w = t.w/2;
          tt.h = t.h;
          renderTriangle(display, d, tt, t_reset);
        } else {
          // for status block          
          tt.x = t.x+2;
          tt.y = t.y+(t.h*0.5);
          tt.w = (t.h/2)-4;
          tt.h = tt.w;
          renderTriangle(display, d, tt, t_reset);
        }
      }
      t_looperData = currentLooper;
      return true;
    }
    return false;
  }
  template <typename T>
  void triangleHelper(T& display, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, bool mirror=false){
    if(!mirror){
      display.fillTriangle(x, y+h, x, y, x+w, y+(h/2), color);
    } else {
      display.fillTriangle(x+w, y+h, x+w, y, x, y+(h/2), color);
    }
  }
  template <typename T>
  bool renderBeatBar(T& display, uint8_t& t_beats, BMCDiplayHandlerData t, bool t_reset=false){
    bool currentBeat = sync.fas.tempoBeat();
    if(currentBeat != bitRead(t_beats, 7) || t_reset){
      uint8_t pos = (t_beats&0x0F);

      // HORIZONTAL BAR
      uint8_t barWidth = (t.w*0.25);
      uint16_t x = barWidth*pos;
      uint16_t y = (t.y+t.h)-1;
      uint16_t x2 = (t.w*0.75);
      if(pos > 0){
        x2 = barWidth*(pos-1);
      }
      if(currentBeat){
        // render bar at the top of block
        // display.drawFastHLine(t.x + x2, t.y, barWidth, t.background);
        // display.drawFastHLine(t.x + x,  t.y, barWidth, t.color);
        
        // render bar at the bottom of block
        display.drawFastHLine(t.x + x2, y, barWidth, t.background);
        display.drawFastHLine(t.x + x,  y, barWidth, t.color);
        pos++;
        if(pos>=4){
          pos = 0;
        }
      }

      // // VERTICAL BAR
      // uint8_t barSize = (t.h*0.25);
      // // uint16_t x = t.w;
      // uint16_t y = barSize*pos;
      // uint16_t y2 = (t.h*0.75);
      // if(pos > 0){
      //   y2 = barSize*(pos-1);
      // }
      // if(currentBeat){
      //   display.drawFastVLine(t.x, t.y+y2, barSize, t.background);
      //   display.drawFastVLine(t.x, t.y+y,  barSize, t.color);
      //   pos++;
      //   if(pos>=4){
      //     pos = 0;
      //   }
      // }





      t_beats = pos | (currentBeat << 7);
      return true;
    }
    return false;
  }
  
};
#endif
#endif
