// *****************************************************************************
// *  See https://www.roxxxtar.com/bmc for more details
// *  Created: 2023
// *  RoxXxtar.com / BadassMIDI.com
// *  Licensed under the MIT license.
// *  See LICENSE file in the project root for full license information.
// *****************************************************************************

#ifndef BMC_DISPLAY_HANDLER_DAW_H
#define BMC_DISPLAY_HANDLER_DAW_H
#include "utility/BMC-Def.h"

#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_DAW_LC)


// values for the DAW VU Meters and other 8 channel display events
// these are use no matter the screen dimensions

  // lighter gray 0x39C7
  #define BMC_ILI9341_VU_GREY BMC_ILI9341_GRAY_7
  #define BMC_ILI9341_FADER_CAP_COLOR BMC_ILI9341_GRAY_24

  // For meters
  #define BMC_ILI9341_VU_METER_S 6 // blank space between meter blocks


#if BMC_MAX_ILI9341_BLOCKS > 0

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
    
    #define BMC_ILI9341_VPOT_INDICATOR_W 4
    #define BMC_ILI9341_VPOT_INDICATOR_X 5
    // For Faders
    #define BMC_ILI9341_FADER_W 7 // width of the fader cap
    #define BMC_ILI9341_FADER_H 10 // height of the fader cap
  #endif

#else
  // mini displays only
  // how many pixels each of the 8 channels will take
  #define BMC_ILI9341_VU_METER_BLOCK_WIDTH (128/8)
  #define BMC_ILI9341_VU_METER_FULL_WIDTH (BMC_ILI9341_VU_METER_BLOCK_WIDTH-BMC_ILI9341_VU_METER_S) // 33 for full width
  #define BMC_ILI9341_VU_METER_H 4 // height of each meter led
  #define BMC_ILI9341_VU_METER_Y 3 // y coordinate of each meter led

  #define BMC_ILI9341_CHANNEL_BUTTON_W 128 //width of solo,rec,mute buttons
  #define BMC_ILI9341_CHANNEL_BUTTON_X 0 // x coordinate of buttons
#endif





class BMCDisplayHandlerDaw {
public:
  BMCMidi& midi;
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCSync& sync;
  bmcDawChannelsInfo chInfo[9];
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
  

  BMCDisplayHandlerDaw(BMCMidi& t_midi, BMCSync& t_sync):
    midi(t_midi),
    globals(t_midi.globals),
    store(t_midi.globals.store),
    settings(t_midi.globals.settings),
    sync(t_sync)
  {
    
  }
  void begin(){
    BMC_PRINTLN(" - BMCDisplayHandlerDaw::begin()");
    reassign();
  }
  void update(){
    
  }
  void reassign(){
    for(uint8_t i = 0 ; i < 9 ; i++){
      chInfo[i].reset();
    }

#if BMC_MAX_ILI9341_BLOCKS > 0
    dawSelectedTrack = -1;
    dawChannelsBlock = -1;
    dawMetersBlock = -1;
    dawVuOverload = 0;
    memset(dawVPotLevel, 0, sizeof(dawVPotLevel[0])*8);
    memset(dawVPotBits, 0, sizeof(dawVPotBits[0])*8);
    memset(dawVuLevel, 0, sizeof(dawVuLevel[0])*8);
    memset(dawVuLevelBits, 0, sizeof(dawVuLevelBits[0])*8);
    memset(dawFaderLevel, 0, sizeof(dawFaderLevel[0])*8);
    memset(dawChStates, 0, sizeof(dawChStates[0])*8);
#endif
  }

// *****************************************************************************
// ********************************* For OLED **********************************
// *****************************************************************************
#if BMC_MAX_OLED > 0
  bool renderChannelBlockOled(BMC_OLED& oled, BMCDataContainer d, uint8_t index){
    if(d.byteB > 8){
      return false;
    }
    BMC_SSD1306& display = oled.display;
    bool reset = false;
    uint8_t n = d.byteB;
    if(chInfo[n].index < 0){
      reset = true;
      chInfo[n].reset();
      chInfo[n].index = index;
      chInfo[n].type = BMC_DEVICE_ID_OLED;
    }

    if(chInfo[n].index != index || !chInfo[n].isOled()){
      return false;
    }

    bool show = false;
    uint8_t channel = n>=8 ? sync.daw.controller.getSelectedChannel() : n;
    // uint8_t index = chInfo[n].index;
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
    // #if BMC_MAX_OLED > 1
    //   selectMux(index);
    // #endif
    if(reset){
      vPotValue = 255;
      vuValue = 255;
      chInfo[n].vPotBits = 0xFFFF;
      chInfo[n].vuBits = 0xFFFF;
      display.fillRect(0, 0, 128, BMC_OLED_HEIGHT, BMC_OLED_BLACK);
      display.fillRect(25, (small ? 24 : 56), 101, 8, BMC_OLED_WHITE);
      display.fillRect(71, (small ? 26 : 58), 9, 4, BMC_OLED_WHITE);
    }
    // track name
    if(!BMC_STR_MATCH(t.name, chInfo[n].name)){
      strcpy(chInfo[n].name, t.name);
      uint8_t fontSize = small ? 2 : 3;
      oled.printCenteredXY(t.name, 23, 1, 105, (fontSize * 8), 0);
      show = true;
    }
    // channel value
    if(!BMC_STR_MATCH(t2.name, chInfo[n].value)){
      strcpy(chInfo[n].value, t2.name);
      if(!small){
        oled.printCenteredXY(t2.name, 35, 31, 82, 16, 0);
        show = true;
      }
    }
    // Meter
    if(vuValue != chInfo[n].vuValue){
      chInfo[n].vuValue = vuValue;
      for(int8_t e = 13 ; e --> 1 ;){
        int8_t ee = abs(e-12) + 1;
        bool v = sync.daw.controller.getMeter(channel, ee)>0;
        if(bitRead(chInfo[n].vuBits, e) != v){
          bitWrite(chInfo[n].vuBits, e, v);
          if(!small){
            display.fillRect(2, (e*5), 12, 4, v ? BMC_OLED_WHITE : BMC_OLED_BLACK);
          } else {
            display.fillRect(2, (e*2)+6, 12, 2, v ? BMC_OLED_WHITE : BMC_OLED_BLACK);
          }
          show = true;
        }
      }
    }
    // vPot
    if(vPotValue != chInfo[n].vPotLevel){
      chInfo[n].vPotLevel = vPotValue;
      for(uint8_t e = 0 ; e < 11 ; e++){
        bool l = sync.daw.controller.getVPotValue(channel, e+1)>0;
        if(bitRead(chInfo[n].vPotBits, e) != l){
          bitWrite(chInfo[n].vPotBits, e, l);
          display.fillRect(26+(e*9), (small ? 26 : 58), 9, 4, l ? BMC_OLED_WHITE : BMC_OLED_BLACK);
        }
      }
      show = true;
    }
    if(show){
      display.display();
    }
    return true;
  }

#endif


// *****************************************************************************
// ***************************** For Mini Display ******************************
// *****************************************************************************
#if BMC_MAX_MINI_DISPLAY > 0
  bool renderChannelBlockMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d){
    BMC_MD_DRIVER& display = block.display;
    if(d.byteB > 8){
      return false;
    }

    bool reset = false;
    uint8_t n = d.byteB;
    if(chInfo[n].index < 0){
      reset = true;
      chInfo[n].reset();
      chInfo[n].index = d.index;
      chInfo[n].type = BMC_DEVICE_ID_MINI_DISPLAY;
      BMC_PRINTLN("Setting Channel Block to", d.index, "channel", n)
    }
    if(chInfo[n].index != d.index || !chInfo[n].isMiniDisplay()){
      return false;
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
    uint16_t w = block.getWidth();
    uint16_t h = block.getHeight();
    uint16_t x = block.getX();
#if BMC_MINI_DISPLAY_H == 128
    // 10 pixel padding
    uint16_t y = block.getY()+10;
    uint16_t vPotYPos = 92;
#else
    uint16_t y = block.getY();
    uint16_t vPotYPos = y + 55;
#endif

    uint16_t txtArea = w-20;
    uint16_t xVPot = x + 20;

    if(reset){
      vPotValue = 0xFF;
      vuValue = 0xFF;
      chInfo[n].vPotBits = 0xFFFF;
      chInfo[n].vuBits = 0xFFFF;
      chInfo[n].stateBits = 0xFF;
      display.fillRect(x, block.getY(), w, h, BMC_ILI9341_BLACK);
      display.drawRect(xVPot, vPotYPos, w-24, 8, BMC_ILI9341_VU_GREY);
    }

    // channel name
    if(!BMC_STR_MATCH(t.name, chInfo[n].name)){
      strcpy(chInfo[n].name, t.name);
#if BMC_MINI_DISPLAY_H == 128
      uint16_t tY = y+3;
      uint8_t tH = 48;
      display.setFont(BMC_FONT_MD);
#else
      uint16_t tY = y+5;
      uint8_t tH = 30;
      display.setFont(BMC_FONT_SM);
#endif
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(display, t.name))/2;
      while(BMC_TFT_STR_LEN(display, t.name) >= (w-20)){
        t.name[strlen(t.name)-1] = 0;
        bX = 20+((w-20)-BMC_TFT_STR_LEN(display, t.name))/2;
      }
      display.fillRect(x+20, block.getY(), txtArea, tH, BMC_ILI9341_BLACK);
      display.setCursor(x+bX, tY);
      display.setTextColor(BMC_ILI9341_WHITE);
      display.setTextWrap(false);
      display.print(t.name);
    }

    // vPot Value
    if(!BMC_STR_MATCH(t2.name, chInfo[n].value)){
      strcpy(chInfo[n].value, t2.name);
      
#if BMC_MINI_DISPLAY_H == 128
      uint16_t tY = y+38; // account for padding
      uint16_t tY2 = y+48;
      uint8_t tH = 40;
      display.setFont(BMC_FONT_SM);
#else
      uint16_t tY = y+30;
      uint16_t tY2 = y+37;
      uint8_t tH = 24;
      display.setFont(BMC_FONT_XS);
#endif
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(display, t2.name))/2;
      display.fillRect(x+20, tY, txtArea, tH, BMC_ILI9341_BLACK);
      display.setCursor(x+bX, tY2);
      display.setTextColor(BMC_ILI9341_GRAY_22);
      display.setTextWrap(false);
      display.print(t2.name);
    }
    if(vPotValue != chInfo[n].vPotLevel){
      chInfo[n].vPotLevel = vPotValue;
      xVPot += 2;
      uint16_t vpotDot = (w-24)/11;
      for(uint8_t e = 0 ; e < 11 ; e++){
        bool l = sync.daw.controller.getVPotValue(channel, e+1)>0;
        if(bitRead(chInfo[n].vPotBits, e) != l){
          bitWrite(chInfo[n].vPotBits, e, l);
          display.fillRect(xVPot+(e*vpotDot), vPotYPos+2, vpotDot, 4, l ? BMC_ILI9341_GREEN : BMC_ILI9341_BLACK);
        }
      }
    }
    if(vuValue != chInfo[n].vuValue){
#if BMC_MINI_DISPLAY_H == 128
      uint16_t meterY = y;
      uint8_t tY = 6;
      uint8_t tH = tY-1;
      display.setFont(BMC_FONT_SM);
#else
      uint16_t meterY = y-2;
      uint8_t tY = 5;
      uint8_t tH = tY-1;
      display.setFont(BMC_FONT_XS);
#endif
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
          display.fillRect(x, meterY+(e*tY), 12, tH, v ? color : BMC_ILI9341_VU_GREY);
        }
      }
    }
    
    // uint8_t btnW = 36;
    #if BMC_MINI_DISPLAY_H == 128
      uint8_t btnW = w/3.5;
      uint8_t btnH = 22;
      // display.setFont(BMC_FONT_XS);
      bool rec = sync.daw.controller.getRecState(channel);
      bool solo = sync.daw.controller.getSoloState(channel);
      bool mute = sync.daw.controller.getMuteState(channel);
      uint16_t buttonsY = 106;
      if(bitRead(chInfo[n].stateBits, 0) != rec){
        bitWrite(chInfo[n].stateBits, 0, rec);
        renderButtonHelper<BMC_MD_DRIVER>(display, x, buttonsY, rec, "R", BMC_ILI9341_RED, btnW, btnH);
      }
      if(bitRead(chInfo[n].stateBits, 1) != solo){
        bitWrite(chInfo[n].stateBits, 1, solo);
        renderButtonHelper<BMC_MD_DRIVER>(display, ((w-btnW)/2), buttonsY, solo, "S", BMC_ILI9341_ORANGE, btnW, btnH);
      }
      if(bitRead(chInfo[n].stateBits, 2) != mute){
        bitWrite(chInfo[n].stateBits, 2, mute);
        renderButtonHelper<BMC_MD_DRIVER>(display, w-btnW, buttonsY, mute, "M", BMC_ILI9341_BLUE, btnW, btnH);
      }
    #endif
    
    return true;
  }
  
#endif









// *****************************************************************************
// ******************************** For ILI9341 ********************************
// *****************************************************************************
#if BMC_MAX_ILI9341_BLOCKS > 0
  bool renderChannelBlockIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, uint8_t crc, uint8_t index){
    BMC_TFT& display = tft.display;
    if(d.byteB > 8 || block.getWidth() < 120 || block.getHeight() < 80){
      return false;
    }
    bool reset = false;
    uint8_t n = d.byteB;
    if(chInfo[n].index < 0){
      reset = true;
      chInfo[n].reset();
      chInfo[n].index = index;
      chInfo[n].type = BMC_DEVICE_ID_ILI;
      // BMC_PRINTLN("Setting Channel Block to", index, "channel", n)
    }
    if(chInfo[n].index != index || !chInfo[n].isIli()){
      return false;
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

    // uint8_t index = chInfo[n].index;
    uint16_t x = block.getX();
    uint16_t y = block.getY();
    uint16_t w = block.getWidth();
    uint16_t h = block.getHeight();
    uint16_t txtArea = w-20;
    txtArea = (txtArea > 140) ? 140 : txtArea;
    uint16_t xVPot = x + 20 + ((txtArea-92)/2);
    if(reset){
      vPotValue = 0xFF;
      vuValue = 0xFF;
      chInfo[n].vPotBits = 0xFFFF;
      chInfo[n].vuBits = 0xFFFF;
      chInfo[n].stateBits = 0xFF;
      display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
      display.drawRect(xVPot, y+68, 92, 8, BMC_ILI9341_VU_GREY);
    }
    if(!BMC_STR_MATCH(t.name, chInfo[n].name)){
      strcpy(chInfo[n].name, t.name);
      display.setFont(BMC_FONT_MD);
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(tft.display, t.name))/2;
      while(BMC_TFT_STR_LEN(tft.display, t.name) >= (w-20)){
        t.name[strlen(t.name)-1] = 0;
        bX = 20+((w-20)-BMC_TFT_STR_LEN(tft.display, t.name))/2;
      }
      display.fillRect(x+20, y+1, txtArea, 30, BMC_ILI9341_BLACK);
      display.setCursor(x+bX, y+3);
      display.setTextColor(BMC_ILI9341_WHITE);
      display.setTextWrap(false);
      display.print(t.name);
    }
    if(!BMC_STR_MATCH(t2.name, chInfo[n].value)){
      strcpy(chInfo[n].value, t2.name);
      display.setFont(BMC_FONT_SM);
      uint16_t bX = 20+(txtArea-BMC_TFT_STR_LEN(tft.display, t2.name))/2;
      display.fillRect(x+20, y+31, txtArea, 30, BMC_ILI9341_BLACK);
      display.setCursor(x+bX, y+40);
      display.setTextColor(BMC_ILI9341_GRAY_22);
      display.setTextWrap(false);
      display.print(t2.name);
    }
    if(vPotValue != chInfo[n].vPotLevel){
      chInfo[n].vPotLevel = vPotValue;
      xVPot += 2;
      for(uint8_t e = 0 ; e < 11 ; e++){
        bool l = sync.daw.controller.getVPotValue(channel, e+1)>0;
        if(bitRead(chInfo[n].vPotBits, e) != l){
          bitWrite(chInfo[n].vPotBits, e, l);
          display.fillRect(xVPot+(e*8), y+70, 8, 4, l ? BMC_ILI9341_GREEN : BMC_ILI9341_BLACK);
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
          display.fillRect(x+4, y+(e*6), 12, 5, v ? color : BMC_ILI9341_VU_GREY);
        }
      }
    }
    if(w > 160){
      bool rec = sync.daw.controller.getRecState(channel);
      bool solo = sync.daw.controller.getSoloState(channel);
      bool mute = sync.daw.controller.getMuteState(channel);
      uint16_t btnX = x+162;
      uint8_t btnW = 36;
      uint8_t btnH = 22;
      if(bitRead(chInfo[n].stateBits, 0) != rec){
        bitWrite(chInfo[n].stateBits, 0, rec);
        // renderButton(tft, x+162, y+2, rec, "R", BMC_ILI9341_RED, 36, 22);
        renderButtonHelper<BMC_TFT>(tft.display, btnX, y+2, rec, "R", BMC_ILI9341_RED, btnW, btnH);
      }
      if(bitRead(chInfo[n].stateBits, 1) != solo){
        bitWrite(chInfo[n].stateBits, 1, solo);
        // renderButton(tft, x+162, y+29, solo, "S", BMC_ILI9341_ORANGE, 36, 22);
        renderButtonHelper<BMC_TFT>(tft.display, btnX, y+29, solo, "S", BMC_ILI9341_ORANGE, btnW, btnH);
      }
      if(bitRead(chInfo[n].stateBits, 2) != mute){
        bitWrite(chInfo[n].stateBits, 2, mute);
        // renderButton(tft, x+162, y+55, mute, "M", BMC_ILI9341_BLUE, 36, 22);
        renderButtonHelper<BMC_TFT>(tft.display, btnX, y+55, mute, "M", BMC_ILI9341_BLUE, btnW, btnH);
      }
    }
    block.setCrc(d.crc);
    return true;
  }
  bool render8ChannelBlock(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, uint8_t crc, uint8_t index){
    BMC_TFT& display = tft.display;
    if(block.getWidth() < BMC_TFT_WIDTH  || block.getHeight() < 80){
      return false;
    }
    uint16_t x = block.getX();
    uint16_t y = block.getY();
    uint16_t w = block.getWidth();
    uint16_t h = block.getHeight();
    bool reset = false;
    if(dawChannelsBlock == -1){
      dawChannelsBlock = index;
      display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
      reset = true;
    }
    if(dawChannelsBlock != index){
      return false;
    }

    x = x + BMC_ILI9341_VU_METER_LEFT_MARGIN;
    // uint16_t y = block.getY();
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
      if((bitRead(dawChStates[i], 0) != rec) || reset){
        bitWrite(dawChStates[i], 0, rec);
        // renderButton(tft, buttonsX, buttonsY, rec, "R", BMC_ILI9341_RED);
        renderButtonHelper<BMC_TFT>(tft.display, buttonsX, buttonsY, rec, "R", BMC_ILI9341_RED);
      }
      if((bitRead(dawChStates[i], 1) != solo) || reset){
        bitWrite(dawChStates[i], 1, solo);
        // renderButton(tft, buttonsX, buttonsY+20, solo, "S", BMC_ILI9341_ORANGE);
        renderButtonHelper<BMC_TFT>(tft.display, buttonsX, buttonsY+20, solo, "S", BMC_ILI9341_ORANGE);
      }
      if((bitRead(dawChStates[i], 2) != mute) || reset){
        bitWrite(dawChStates[i], 2, mute);
        // renderButton(tft, buttonsX, buttonsY+40, mute, "M", BMC_ILI9341_BLUE);
        renderButtonHelper<BMC_TFT>(tft.display, buttonsX, buttonsY+40, mute, "M", BMC_ILI9341_BLUE);
      }
      if((dawVPotLevel[i] != vPotValue) || reset){
        for(uint8_t e = 0 ; e < 11 ; e++){
          bool l = sync.daw.controller.getVPotValue(i, e+1)>0;
          if(bitRead(dawVPotBits[i], e) != l || reset){
            uint16_t color = l ? BMC_ILI9341_GREEN : BMC_ILI9341_VU_GREY;
            display.fillRect(bX +  BMC_ILI9341_VPOT_INDICATOR_X + (BMC_ILI9341_VPOT_INDICATOR_W*e), y+6, BMC_ILI9341_VPOT_INDICATOR_W, 4, color);
            bitWrite(dawVPotBits[i], e, l);
          }
        }
        dawVPotLevel[i] = vPotValue;
      }
    }
    block.setCrc(d.crc);
    dawSelectedTrack = sel;
    return true;
  }

  bool render8MeterBlock(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d, uint8_t crc, uint8_t index){
    BMC_TFT& display = tft.display;
    if(block.getWidth() < BMC_TFT_WIDTH  || block.getHeight() < 80){
      return false;
    }
    uint16_t x = block.getX();
    uint16_t y = block.getY();
    uint16_t w = block.getWidth();
    uint16_t h = block.getHeight();
    bool reset = false;
    if(dawMetersBlock == -1){
      dawMetersBlock = index;
      display.fillRect(x, y, w, h, BMC_ILI9341_BLACK);
      reset = true;
    }
    if(dawMetersBlock != index){
      return false;
    }

    x = x + BMC_ILI9341_VU_METER_LEFT_MARGIN;
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
              display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, color);
            } else {
              display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY+(e*(BMC_ILI9341_VU_METER_H+1)), BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
            }
            bitWrite(dawVuLevelBits[i], e, l);
          }
        }
        dawVuLevel[i] = value;
      }
      if(bitRead(dawVuOverload, i) != overload || reset){
        bitWrite(dawVuOverload, i, overload);
        uint16_t overloadColor = overload ? BMC_ILI9341_RED : BMC_ILI9341_VU_GREY;
        display.fillRect(bX+BMC_ILI9341_VU_METER_X, bY, BMC_ILI9341_VU_METER_W, BMC_ILI9341_VU_METER_H, overloadColor);
      }
      if(dawFaderLevel[i] != faderLevel || reset){
        uint16_t faderX = bX + (BMC_ILI9341_VU_METER_FULL_WIDTH-BMC_ILI9341_FADER_W)-BMC_ILI9341_FADER_RIGHT_MARGIN;
        uint16_t faderY = (bY+faderLength) - faderLevel;

        display.fillRect(faderX, bY, BMC_ILI9341_FADER_W, faderLength, BMC_ILI9341_BLACK);
        display.drawFastVLine(faderX+(BMC_ILI9341_FADER_W/2), bY, faderLength, BMC_ILI9341_VU_GREY);
        
        display.fillRect(faderX, faderY, BMC_ILI9341_FADER_W, BMC_ILI9341_FADER_H, BMC_ILI9341_FADER_CAP_COLOR);
        display.drawFastHLine(faderX, faderY+(BMC_ILI9341_FADER_H/2), BMC_ILI9341_FADER_W, BMC_ILI9341_BLACK);
        dawFaderLevel[i] = faderLevel;
      }
      if(dawSelectedTrack != sel || reset){
        display.fillRect(bX, selY-4, BMC_ILI9341_VU_METER_FULL_WIDTH, 2, sel==i ? BMC_ILI9341_ORANGE : BMC_ILI9341_VU_GREY);
      }
    }
    block.setCrc(d.crc);
    dawSelectedTrack = sel;
    return true;
  }

  // void renderButton(BMC_ILI& tft, uint16_t x, uint16_t y, uint8_t value, const char * t_str, uint16_t color, uint8_t cW=0, uint8_t cH=0){
  //   BMC_TFT& display = tft.display;
  //   // convert const char array to char array
  //   char str[strlen(t_str)+1] = "";
  //   strcpy(str, t_str);
  //   uint8_t buttonWidth = cW==0 ? BMC_ILI9341_CHANNEL_BUTTON_W : cW;
  //   uint8_t buttonHeight = cH==0 ? 16 : cH;
  //   // set the font to be used
  //   display.setFont(BMC_FONT_XS);
  //   display.setTextColor(value ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
  //   display.fillRect(x, y, buttonWidth, buttonHeight, value ? color : BMC_ILI9341_BLACK);
  //   if(!value){
  //     display.drawRect(x, y, buttonWidth, buttonHeight, BMC_ILI9341_VU_GREY);
  //   }
  //   // uint16_t w = BMC_TFT_STR_LEN(tft.display, str);
  //   // display.setCursor(x + ((buttonWidth - w)/2), y+((buttonHeight-12)/2));
  //   BMCTextPixelSize tt = display.getCurrentCenteredXY(t_str, x, y, buttonWidth, buttonHeight, 0);
  //   display.setCursor(tt.x, tt.y);


  //   display.print(str);
  // }
#endif


// *****************************************************************************
// ************************ For ILI9341 & Mini Display *************************
// *****************************************************************************
#if BMC_MAX_ILI9341_BLOCKS > 0 || BMC_MAX_MINI_DISPLAY > 0
  template <typename T>
  void renderButtonHelper(T& display, uint16_t x, uint16_t y, uint8_t value, const char * t_str, uint16_t color, uint8_t cW=0, uint8_t cH=0){
    // convert const char array to char array
    display.setFont(BMC_FONT_XS);
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    uint8_t buttonWidth = cW == 0 ? BMC_ILI9341_CHANNEL_BUTTON_W : cW;
    // uint8_t buttonWidth = cW;
    uint8_t buttonHeight = cH == 0 ? 16 : cH;
    // set the font to be used
    
    display.setTextColor(value ? BMC_ILI9341_WHITE : BMC_ILI9341_VU_GREY);
    display.fillRect(x, y, buttonWidth, buttonHeight, value ? color : BMC_ILI9341_BLACK);
    if(!value){
      display.drawRect(x, y, buttonWidth, buttonHeight, BMC_ILI9341_VU_GREY);
    }
    uint16_t w = BMC_TFT_STR_LEN(display, str);
    display.setCursor(x + ((buttonWidth - w)/2), y+((buttonHeight-12)/2));
    display.print(str);
  }
#endif
  
};
#endif
#endif
