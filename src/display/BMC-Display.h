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
#define BMC_ILI9341_VU_GREY 0x39C7
#define BMC_ILI9341_VU_METER_H 2
#define BMC_ILI9341_VU_METER_Y 28

class BMCDisplay {
public:
  BMCDisplay(BMCMidi& t_midi, bmcStore& t_store, BMCCallbacks& cb
    #ifdef BMC_USE_SYNC
      ,BMCSync& t_sync
    #endif
    #if BMC_MAX_PRESETS > 0
      ,BMCPresets& t_presets
    #endif
    #if BMC_MAX_SETLISTS > 0
      ,BMCSetLists& t_setlists
    #endif
  ):midi(t_midi),store(t_store), callback(cb)
    #ifdef BMC_USE_SYNC
      ,sync(t_sync)
    #endif
    #if BMC_MAX_PRESETS > 0
      ,presets(t_presets)
    #endif
    #if BMC_MAX_SETLISTS > 0
      ,setLists(t_setlists)
    #endif
  {

  }
  void begin(){
    BMC_PRINTLN("BMCDisplay:begin()");
#if defined(BMC_USE_DAW_LC)
    dawMetersBlock = -1;
    dawVuOverload = 0;
    dawSelectedTrack = -1;
    memset(dawVPotLevel, 0, 8);
    memset(dawVPotBits, 0, 8);
    memset(dawVuLevel, 0, 8);
    memset(dawVuLevelBits, 0, 8);
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
    tft.begin(BMCBuildData::getIliDisplayPosition(2));
    tft.clear();
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      block[i].begin(i);
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
        uint8_t addr = 0x3C + BMCBuildData::getOledDisplayPosition(i, 3);
        uint8_t rotation = BMCBuildData::getOledDisplayPosition(i, 2);
    #if BMC_MAX_OLED > 1
        selectMux(i);
    #endif
        oled[i].begin(BMC_SSD1306_SWITCHCAPVCC, addr, rotation);
      }
      /*
      oled[0].display.setFont(&BMCDisplay_Font);
      oled[0].display.setTextWrap(false);
      oled[0].display.setTextColor(BMC_SSD1306_WHITE);
      oled[0].display.setTextSize(2);
      oled[0].display.setCursor(10, 16);
      oled[0].display.println("0123456789");
      oled[0].display.println("0123456789");
      oled[0].display.drawLine(0, 0, 10, 0, BMC_SSD1306_WHITE);
      oled[0].display.drawLine(0, 6, 10, 6, BMC_SSD1306_WHITE);
      oled[0].display.display();
      */
  }
#endif
  void reassign(uint8_t page){
#if defined(BMC_USE_DAW_LC)
      dawMetersBlock = -1;
      dawVuOverload = 0;
      dawSelectedTrack = -1;
      memset(dawVPotLevel, 0, 8);
      memset(dawVPotBits, 0, 8);
      memset(dawVuLevel, 0, 8);
      memset(dawVuLevelBits, 0, 8);
      memset(dawChStates, 0, 8);
      for(uint8_t i=0;i<8;i++){
        memset(dawChName[i], 0, 8);
      }
#endif
#if BMC_MAX_OLED > 0
// not needed just yet

    for(uint8_t i=0;i<BMC_MAX_OLED;i++){
#if defined(BMC_USE_DAW_LC)
      if(store.pages[page].oled[i].type==BMC_DISPLAY_EVENT_TYPE_DAW){

      }
    }
#endif

#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){

#if defined(BMC_USE_DAW_LC)
      if(store.pages[page].ili[i].type==BMC_DISPLAY_EVENT_TYPE_DAW){
        if(store.pages[page].ili[i].value==0){
          // make sure this is a 320 x 80 block
          if(dawMetersBlock == -1 && BMCBuildData::getIliDisplayBlockPosition(i, 2) == 0){
            dawMetersBlock = i;
            initDawMeters();
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
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t y = block[dawMetersBlock].getY();
    //uint16_t w = block[dawMetersBlock].getWidth();
    //uint8_t h = block[dawMetersBlock].getHeight();
    // clear the block
    tft.display.fillRect(x, y, 320, 80, BMC_ILI9341_BLACK);
    //tft.display.drawRect(x, y, 320, 80, BMC_ILI9341_WHITE);
    //uint8_t tY = (y+80)-7;
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint16_t bX = (x + 7) + (i*39);
      uint16_t bY = y+BMC_ILI9341_VU_METER_Y;

      //tft.display.drawFastVLine(bX+35, y+2, 78, BMC_ILI9341_VU_GREY);

      // VPOT
      uint8_t vuHeight = 9;
      uint16_t vuWidth = 3;
      for(uint8_t e = 0 ; e < 11 ; e++){
        if(e < 6){ // decrease
          //y += e > 0 ? 1 : 0;
          vuHeight -= e > 0 ? 1 : 0;
        } else {// increase
          //y -= 1;
          vuHeight += 1;
        }
        tft.display.fillRect(bX + (vuWidth*e), y+4, vuWidth, vuHeight, BMC_ILI9341_VU_GREY);
        //y+4
      }

      tft.display.setTextSize(1);
      tft.display.setTextColor(BMC_ILI9341_VU_GREY);

      tft.display.setCursor(bX+2, y+16);
      tft.display.print("R ");
      tft.display.setCursor(bX+14, y+16);
      tft.display.print("S ");
      tft.display.setCursor(bX+26, y+16);
      tft.display.print("M");

      // VU METERS
      for(uint8_t e = 0 ; e < 13 ; e++){
        tft.display.fillRect(bX, bY+(e*(BMC_ILI9341_VU_METER_H+1)), 33, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
      }
      // print names tho not needed at reset
      //tft.display.setCursor(bX-1, tY);
      //tft.display.print("");
    }
  }
  void updateDawMeters(){
    if(dawMetersBlock==-1){
      return;
    }
    uint16_t x = block[dawMetersBlock].getX();
    uint8_t  y = block[dawMetersBlock].getY();
    uint8_t tY = (y+80)-7;
    uint8_t sel = sync.daw.controller.getSelectedChannel();
    for(uint8_t i = 0 ; i < 8 ; i++){
      uint8_t value = sync.daw.controller.getMeter(i);
      uint8_t overload = sync.daw.controller.getMeterOverload(i);
      uint8_t vPotValue = sync.daw.controller.getVPot(i);
      // for testing
      //uint8_t value = random(0, 13);
      //uint8_t overload = random(0, 2);
      uint16_t bX = (x + 7) + (i*39);
      uint16_t bY = y+BMC_ILI9341_VU_METER_Y;

      bool rec = sync.daw.controller.getRecState(i);
      bool solo = sync.daw.controller.getSoloState(i);
      bool mute = sync.daw.controller.getMuteState(i);

      tft.display.setTextSize(1);
      if(bitRead(dawChStates[i], 0) != rec){
        tft.display.setTextColor(rec ? BMC_ILI9341_RED : BMC_ILI9341_VU_GREY);
        tft.display.setCursor(bX+2, y+16);
        tft.display.print("R ");
        bitWrite(dawChStates[i], 0, rec);
      }
      if(bitRead(dawChStates[i], 1) != solo){
        tft.display.setTextColor(solo ? BMC_ILI9341_YELLOW : BMC_ILI9341_VU_GREY);
        tft.display.setCursor(bX+14, y+16);
        tft.display.print("S ");
        bitWrite(dawChStates[i], 1, solo);
      }
      if(bitRead(dawChStates[i], 2) != mute){
        tft.display.setTextColor(mute ? BMC_ILI9341_CYAN : BMC_ILI9341_VU_GREY);
        tft.display.setCursor(bX+26, y+16);
        tft.display.print("M");
        bitWrite(dawChStates[i], 2, mute);
      }
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
              tft.display.fillRect(bX, bY+(e*(BMC_ILI9341_VU_METER_H+1)), 33, BMC_ILI9341_VU_METER_H, color);
            } else {
              tft.display.fillRect(bX, bY+(e*(BMC_ILI9341_VU_METER_H+1)), 33, BMC_ILI9341_VU_METER_H, BMC_ILI9341_VU_GREY);
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
      if(dawVPotLevel[i] != vPotValue){
        uint8_t vuHeight = 9;
        uint16_t vuWidth = 3;
        for(uint8_t e = 0 ; e < 11 ; e++){
          if(e < 6){ // decrease
            //y += e > 0 ? 1 : 0;
            vuHeight -= e > 0 ? 1 : 0;
          } else {// increase
            //y -= 1;
            vuHeight += 1;
          }
          bool l = sync.daw.controller.getVPotValue(i, e+1)>0;
          if(bitRead(dawVPotBits[i], e) != l){
            tft.display.fillRect(bX + (vuWidth*e), y+4, vuWidth, vuHeight, l ? BMC_ILI9341_DARKGREEN : BMC_ILI9341_VU_GREY);
            bitWrite(dawVPotBits[i], e, l);
          }
        }
        dawVPotLevel[i] = vPotValue;
      }
      char str[10] = "";
      sync.daw.getLcdTrackName(i, str);
      str[6] = 0;
      // update the track name if this track was the last selected
      // or the currently selected track
      bool isSel = ((sel==i || dawSelectedTrack==i) && dawSelectedTrack != sel);

      if(strlen(dawChName[i]) != strlen(str) || !BMC_STR_MATCH(dawChName[i], str) || isSel){
        BMC_PRINTLN(i, "dawChName[i]",dawChName[i], strlen(dawChName[i]), "str", str, strlen(str));
        tft.display.setTextSize(1);
        tft.display.setCursor(bX-1, tY);
        tft.display.setTextColor(BMC_ILI9341_BLACK);
        tft.display.print(dawChName[i]);
        tft.display.setCursor(bX-1, tY);

        tft.display.setTextColor(sel == i ? BMC_ILI9341_YELLOW : BMC_ILI9341_WHITE);
        tft.display.print(str);
        strcpy(dawChName[i], str);
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
#if BMC_MAX_OLED > 0
    for(uint8_t i=0;i<BMC_MAX_OLED;i++){
      uint8_t type = store.pages[page].oled[i].type;
      uint8_t value = store.pages[page].oled[i].value;
      runEvents(page, true, i, type, value);
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_ILI9341_BLOCKS ; i++){
      uint8_t type = store.pages[page].ili[i].type;
      uint8_t value = store.pages[page].ili[i].value;
      runEvents(page, false, i, type, value);
    }
#endif
  }
  void renderPresetNumber(bmcPreset_t n){

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
#endif


private:
  BMCMidi& midi;
  bmcStore& store;
  BMCCallbacks& callback;
#ifdef BMC_USE_SYNC
  BMCSync& sync;
#endif
#if BMC_MAX_PRESETS > 0
  BMCPresets& presets;
#endif
#if BMC_MAX_SETLISTS > 0
  BMCSetLists& setLists;
#endif
  uint8_t last[BMC_MAX_OLED+BMC_MAX_ILI9341_BLOCKS];
#if BMC_MAX_OLED > 0
  BMC_OLED oled[BMC_MAX_OLED];
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  BMC_ILI9341 tft = BMC_ILI9341();
  BMC_ILI9341_BLOCK block[BMC_MAX_ILI9341_BLOCKS];
#endif
#if defined(BMC_USE_DAW_LC) && BMC_MAX_ILI9341_BLOCKS > 0
  int8_t dawSelectedTrack = -1;
  int8_t dawMetersBlock = -1;
  uint8_t dawVPotLevel[8];
  uint16_t dawVPotBits[8];
  uint8_t dawVuLevel[8];
  uint16_t dawVuLevelBits[8];
  uint8_t dawVuOverload = 0;
  uint8_t dawChStates[8];
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

  void runEvents(uint8_t page, bool isOled, uint8_t index, uint8_t type, uint8_t value){
    bool blank = true;
    switch(parseEventType(type)){
      case BMC_NONE:
        break;
      case BMC_DISPLAY_EVENT_TYPE_KEYWORD:
        {
          value = constrain(value, 0, 21);
          renderText(index, isOled, type, keyword[value]);
          blank = false;
        }
        break;
      case BMC_DISPLAY_EVENT_TYPE_ICON:
        {
          renderIcon(index, isOled, type, value);
          blank = false;
        }
        break;
      case BMC_DISPLAY_EVENT_TYPE_BPM:
        {
          char str[4] = "";
          sprintf(str, "%03u", midi.globals.bpm);
          renderTextWithBox(index, isOled, type, str, 10, 0, "BPM");
          blank = false;
        }
        break;
      case BMC_DISPLAY_EVENT_TYPE_BUTTON:
    #if BMC_MAX_BUTTONS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.pages[page].buttons[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_GLOBAL_BUTTON:
    #if BMC_MAX_GLOBAL_BUTTONS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.global.buttons[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_ENCODER:
    #if BMC_MAX_ENCODERS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.pages[page].encoders[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_GLOBAL_ENCODER:
    #if BMC_MAX_GLOBAL_ENCODERS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.global.encoders[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_POT:
    #if BMC_MAX_POTS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.pages[page].pots[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_GLOBAL_POT:
    #if BMC_MAX_GLOBAL_POTS > 0 && BMC_NAME_LEN_BUTTONS > 1
        renderText(index, isOled, type, store.global.pots[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_LED:
    #if BMC_MAX_LEDS > 0 && BMC_NAME_LEN_LEDS > 1
        renderText(index, isOled, type, store.pages[page].leds[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_GLOBAL_LED:
    #if BMC_MAX_GLOBAL_LEDS > 0 && BMC_NAME_LEN_LEDS > 1
        renderText(index, isOled, type, store.global.leds[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PWM_LED:
    #if BMC_MAX_PWM_LEDS > 0 && BMC_NAME_LEN_LEDS > 1
        renderText(index, isOled, type, store.pages[page].pwmLeds[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PIXEL:
    #if BMC_MAX_PIXELS > 0 && BMC_NAME_LEN_LEDS > 1
        renderText(index, isOled, type, store.pages[page].pixels[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_RGB_PIXEL:
    #if BMC_MAX_RGB_PIXELS > 0 && BMC_NAME_LEN_LEDS > 1
        renderText(index, isOled, type, store.pages[page].rgbPixels[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_NL_RELAY:
    #if BMC_MAX_NL_RELAYS > 0 && BMC_NAME_LEN_RELAYS > 1
        renderText(index, isOled, type, store.global.relaysNL[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_L_RELAY:
    #if BMC_MAX_L_RELAYS > 0 && BMC_NAME_LEN_RELAYS > 1
        renderText(index, isOled, type, store.global.relaysL[value].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_LIBRARY:
    #if BMC_MAX_LIBRARY > 0 && BMC_MAX_PRESETS > 0 && BMC_NAME_LEN_LIBRARY > 1
        {
          char str[BMC_NAME_LEN_LIBRARY] = "";
          presets.getPresetItemName(value, str);
          renderText(index, isOled, type, str);
          BMC_PRINTLN("BMC_DISPLAY_EVENT_TYPE_LIBRARY",value, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PRESET:
    #if BMC_MAX_PRESETS > 0 && BMC_NAME_LEN_PRESETS > 1
        {
          char str[BMC_NAME_LEN_PRESETS] = "";
          presets.getName(value, str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_PRESET:
    #if BMC_MAX_PRESETS > 0
        {
          char str[4] = "";
          #if BMC_MAX_PRESETS < 10
            sprintf(str, "%01u", presets.get()+1);
          #elif BMC_MAX_PRESETS < 100
            sprintf(str, "%02u", presets.get()+1);
          #else
            sprintf(str, "%03u", presets.get()+1);
          #endif
          renderTextWithBox(index, isOled, type, str, 10, 0, "PRST");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_PRESET_NAME:
    #if BMC_MAX_PRESETS > 0 && BMC_NAME_LEN_PRESETS > 1
        {
          char str[BMC_NAME_LEN_PRESETS] = "";
          presets.getName(str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PRESET_BANK:
    #if BMC_MAX_PRESETS > 0
        {
          char str[4] = "";
          sprintf(str, "%02u", presets.getBank()+1);
          renderTextWithBox(index, isOled, type, str, 10, 0, "BANK");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PRESET_IN_BANK:
    #if BMC_MAX_PRESETS > 0 && BMC_NAME_LEN_PRESETS > 1
        {
          char str[BMC_NAME_LEN_PRESETS] = "";
          presets.getNameInBank(value, str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;

      case BMC_DISPLAY_EVENT_TYPE_SETLIST_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLISTS > 1
        {
          char str[BMC_NAME_LEN_SETLISTS] = "";
          setLists.getSetName(value, str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_SETLIST:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLISTS > 1
        {
          char str[4] = "";
          sprintf(str, "%02u", setLists.getSet()+1);
          renderTextWithBox(index, isOled, type, str, 14, 0, "SET");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_SETLIST_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLISTS > 1
        {
          char str[BMC_NAME_LEN_SETLISTS] = "";
          setLists.getSetName(str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;

      // ********************
      // SET LIST SONGS
      // ********************
      case BMC_DISPLAY_EVENT_TYPE_SONG_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLIST_SONG > 1
        {
          char str[BMC_NAME_LEN_SETLIST_SONG] = "";
          setLists.getSongName(value, str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_SONG:
    #if BMC_MAX_SETLISTS > 0
        {
          char str[4] = "";
          sprintf(str, "%02u", setLists.getSong()+1);
          renderTextWithBox(index, isOled, type, str, 14, 0, "SONG");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_SONG_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLIST_SONG_PART > 1
        {
          char str[BMC_NAME_LEN_SETLIST_SONG] = "";
          setLists.getSongName(str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;

      // ********************
      // SET LIST SONGS
      // ********************

      case BMC_DISPLAY_EVENT_TYPE_PART_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLIST_SONG_PART > 1
        {
          char str[BMC_NAME_LEN_SETLIST_SONG_PART] = "";
          setLists.getPartName(value, str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_PART:
    #if BMC_MAX_SETLISTS > 0
        {
          char str[4] = "";
          sprintf(str, "%02u", setLists.getPart()+1);
          renderTextWithBox(index, isOled, type, str, 14, 0, "PART");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_PART_NAME:
    #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLIST_SONG_PART > 1
        {
          char str[BMC_NAME_LEN_SETLIST_SONG_PART] = "";
          setLists.getPartName(str);
          renderText(index, isOled, type, str);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_STRING_LIBRARY:
    #if BMC_MAX_STRING_LIBRARY > 0 && BMC_NAME_LEN_STRING_LIBRARY > 1
        if(value < BMC_MAX_STRING_LIBRARY){
          renderText(index, isOled, type, store.global.stringLibrary[value].name);
          blank = false;
        }

    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PAGE:
    #if BMC_MAX_PAGES > 1
        {
          char str[4] = "";
          #if BMC_MAX_PAGES < 10
            sprintf(str, "%01u", page+1);
          #elif BMC_MAX_PAGES < 100
            sprintf(str, "%02u", page+1);
          #else
            sprintf(str, "%03u", page+1);
          #endif
          renderTextWithBox(index, isOled, type, str, 14, 0, "PAGE");
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_PAGE_NAME:
    #if BMC_MAX_PAGES > 1 && BMC_NAME_LEN_PAGES > 1
        if(value < BMC_MAX_PAGES &&  strlen(store.pages[value].name) > 0){
          renderText(index, isOled, type, store.pages[value].name);
          blank = false;
        }
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_CURRENT_PAGE_NAME:
    #if BMC_MAX_PAGES > 1 && BMC_NAME_LEN_PAGES > 1
        renderText(index, isOled, type, store.pages[page].name);
        blank = false;
    #endif
        break;
      case BMC_DISPLAY_EVENT_TYPE_DAW:
        blank = false;
    #if defined(BMC_USE_DAW_LC)
        if(value==0){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(!isOled){
              updateDawMeters();
            }
          #endif
        } else if(value == 1){
          //selected daw track
          char str[10] = "";
          sync.daw.getLcdTrackName(str);
          renderText(index, isOled, type, str);

        } else if(value<10){
          char str[10] = "";
          sync.daw.getLcdTrackName(value - 2, str);
          renderText(index, isOled, type, str);

        }
    #endif
        break;
      case BMC_EVENT_TYPE_CUSTOM:
        // DO NOTHING THIS DISPLAY WILL BE FULL CONTROLLED USING THE API
        break;
    }
    if(blank){
      char str[2] = "-";
      renderText(index, isOled, type, str);
    }
  }
  uint8_t parseEventType(uint8_t t_type){
    return (t_type > 0x7F && t_type < 0xF0) ? (t_type & 0xF0) : t_type;
  }
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
  void renderTextWithBox(uint8_t n, bool isOled, uint8_t type, char * str, uint8_t xShift, uint8_t yShift, const char * sideStr){
#if BMC_MAX_OLED > 1
    if(isOled){
      selectMux(n);
    }
#endif
    uint8_t crc = checkLast(type, str);
    uint8_t displayN = n + (isOled ? 0 : BMC_MAX_OLED);
    if(last[displayN] != crc){
      last[displayN] = crc;
      if(strlen(str)==0){
        strcpy(str, "-");
      }
#if BMC_MAX_OLED > 0
      if(isOled){
        oled[n].print(str, xShift, yShift);
        oled[n].printLeftBox(sideStr);
        return;
      }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
      if(!isOled){
        block[n].print(tft.display, str, xShift, yShift);
        block[n].printLeftBox(tft.display, sideStr);
      }
#endif
    }
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
    n = BMCBuildData::getOledDisplayPosition(n, 4);
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
