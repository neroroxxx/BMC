/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Class holding mainly flags that are used across BMC
  For example when there's MIDI IN activity a MIDI IN flag is set,
  Leds will then read that flag and if an LED has a MIDI IN event it will pulse
  the led, every time BMC::update() happens the MIDI IN and OUT flags are cleared
  by this point the LEDs will have read that flag and they won't need to read it again.
  This object is decleared by the main BMC class, then passed as a reference to
  objects that may use it.

*/
#ifndef BMC_GLOBALS_H
#define BMC_GLOBALS_H
#include <Arduino.h>
#include "utility/BMC-Metrics.h"

#define BMC_GLOBALS_FLAG_MIDI_IN                	 0
#define BMC_GLOBALS_FLAG_MIDI_OUT               	 1
#define BMC_GLOBALS_FLAG_EDITOR_CONNECTED       	 2
#define BMC_GLOBALS_FLAG_HOST_CONNECTED         	 3
#define BMC_GLOBALS_FLAG_BLE_CONNECTED          	 4
#define BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE      	 5
#define BMC_GLOBALS_FLAG_ON_BOARD_EDITOR_ACTIVE 	 6
#define BMC_GLOBALS_FLAG_DISABLE_DISPLAY_RENDER    7
#define BMC_GLOBALS_FLAG_ASSIGN_STORE_DATA      	 8
#define BMC_GLOBALS_FLAG_RELOAD_LAYER            	 9
#define BMC_GLOBALS_FLAG_TRIGGER_BANK           	 10
#define BMC_GLOBALS_FLAG_TRIGGER_PRESET         	 11
#define BMC_GLOBALS_FLAG_TRIGGER_SETLIST        	 12
#define BMC_GLOBALS_FLAG_TRIGGER_SONG           	 13
#define BMC_GLOBALS_FLAG_TRIGGER_SONG_PART      	 14
#define BMC_GLOBALS_FLAG_PAUSE_ILI      	         15
#define BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST       16


#define BMC_GLOBALS_DEBUG_FLAG_STORAGE            	 0
#define BMC_GLOBALS_DEBUG_FLAG_METRICS            	 1
#define BMC_GLOBALS_DEBUG_FLAG_BLE                	 2
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_IN            	 3
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK 	 4
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT           	 5
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK	 6
#define BMC_GLOBALS_DEBUG_FLAG_BUTTONS            	 7
#define BMC_GLOBALS_DEBUG_FLAG_FAS                	 8
#define BMC_GLOBALS_DEBUG_FLAG_POTS               	 9
#define BMC_GLOBALS_DEBUG_FLAG_ENCODERS              10
#define BMC_GLOBALS_DEBUG_FLAG_TIMER                 11
#define BMC_GLOBALS_DEBUG_DISPLAY_RENDER_TIME        12
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_CLOCK            13

// https://github.com/mpflaga/Arduino-MemoryFree
// doesn't seem to be work with Teensy 4.0 unless
// Returns 4GB of Free RAM
#if defined(BMC_FOR_TEENSY) && BMC_MCU_MODEL != 40
extern char *__brkval;
#endif

class BMCGlobals {
public:
  bmcStore& store;
  BMCSettings& settings;
  
  BMCGlobals(bmcStore& t_store, BMCSettings& t_settings):store(t_store), settings(t_settings){
    reset();
  }
  void begin(){
    // * params
    // * uint32_t reportIntervalMs = 2000
    // * uint16_t minLps = 500
    // * uint16_t maxLoopTimeUs
    metrics.begin(2000, 500, 1000);
  }
  void update(){
    metrics.update();
    flags.off(BMC_GLOBALS_FLAG_MIDI_IN);
    flags.off(BMC_GLOBALS_FLAG_MIDI_OUT);
    flags.off(BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE);
  }
  bool timerComplete(){
    #if defined(BMC_DEBUG)
      return debugFlags.toggleIfTrue(BMC_GLOBALS_DEBUG_FLAG_TIMER);
    #else
      return false;
    #endif
  }
  void setTimerComplete(){
    #if defined(BMC_DEBUG)
      debugFlags.on(BMC_GLOBALS_DEBUG_FLAG_TIMER);
    #endif
  }

  // void resetCPU(){
  //   lastLoopsPerSecond = loopsPerSecond;
  //   loopsPerSecond = 0;
  // }

  uint32_t getCPU(){
    // return lastLoopsPerSecond;
    return metrics.getLoopsPerSecond();
  }

  // https://github.com/mpflaga/Arduino-MemoryFree
  // doesn't seem to be work with Teensy 4.0 unless
  // Returns 4GB of Free RAM
  uint32_t getRAM(){
#if defined(BMC_FOR_TEENSY) && BMC_MCU_MODEL != 40
    char top;
    return &top - __brkval;
#else
    return 0;
#endif
  }
  bool hasMidiActivity(){
    return midiInActivity() || midiOutActivity();
  }
  // return the type of midi activity requested
  // @n: 0=in, 1=out, 2=any
  bool hasMidiActivity(uint8_t n){
    if(n<2){
      return n==0 ? midiInActivity() : midiOutActivity();
    }
    return hasMidiActivity();
  }
  // set/get midi Activity, d is just a dummy variable so we can use the same
  // function names for reading and writing to the flags
  void setMidiInActivity(){
    flags.on(BMC_GLOBALS_FLAG_MIDI_IN);
  }
  void clearMidiInActivity(){
    flags.off(BMC_GLOBALS_FLAG_MIDI_IN);
  }
  bool midiInActivity(){
    return flags.read(BMC_GLOBALS_FLAG_MIDI_IN);
  }
  void setMidiOutActivity(){
    flags.on(BMC_GLOBALS_FLAG_MIDI_OUT);
  }
  void clearMidiOutActivity(){
    flags.on(BMC_GLOBALS_FLAG_MIDI_OUT);
  }
  bool midiOutActivity(){
    return flags.read(BMC_GLOBALS_FLAG_MIDI_OUT);
  }
  void setEditorConnected(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_EDITOR_CONNECTED, t_state);
  }
  bool editorConnected(){
    return flags.read(BMC_GLOBALS_FLAG_EDITOR_CONNECTED);
  }
  void setHostConnected(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_HOST_CONNECTED, t_state);
  }
  bool hostConnected(){
    return flags.read(BMC_GLOBALS_FLAG_HOST_CONNECTED);
  }
  void setBleConnected(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_BLE_CONNECTED, t_state);
  }
  bool bleConnected(){
    return flags.read(BMC_GLOBALS_FLAG_BLE_CONNECTED);
  }
  void setMidiLocalUpdate(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE, t_state);
  }
  bool midiLocalUpdate(){
    return flags.read(BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE);
  }
  void setOnBoardEditorActive(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_ON_BOARD_EDITOR_ACTIVE, t_state);
  }
  bool toggleOnBoardEditor(){
    return flags.toggle(BMC_GLOBALS_FLAG_ON_BOARD_EDITOR_ACTIVE);
  }
  bool onBoardEditorActive(){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    return flags.read(BMC_GLOBALS_FLAG_ON_BOARD_EDITOR_ACTIVE);
#else
    return false;
#endif
  }
  void setDisplayRenderDisable(bool state){
#if defined(BMC_USE_ON_BOARD_EDITOR)
    flags.write(BMC_GLOBALS_FLAG_DISABLE_DISPLAY_RENDER, state);
#endif
  }
  bool displayRenderDisabled(){
    return flags.read(BMC_GLOBALS_FLAG_DISABLE_DISPLAY_RENDER);
  }

  



  void setAssignStoreData(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_ASSIGN_STORE_DATA, t_state);
  }
  bool assignStoreData(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_ASSIGN_STORE_DATA);
  }
  void setReloadLayer(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_RELOAD_LAYER, t_state);
  }
  bool reloadLayer(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_RELOAD_LAYER);
  }
  void setTriggerBank(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_TRIGGER_BANK, t_state);
  }
  bool triggerBankChange(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_TRIGGER_BANK);
  }
  void setTriggerPreset(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_TRIGGER_PRESET, t_state);
  }
  bool triggerPresetChange(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_TRIGGER_PRESET);
  }
  void setTriggerSetList(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_TRIGGER_SETLIST, t_state);
  }
  bool triggerSetListChange(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_TRIGGER_SETLIST);
  }
  void setTriggerSong(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_TRIGGER_SONG, t_state);
  }
  bool triggerSongChange(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_TRIGGER_SONG);
  }
  void setTriggerPart(bool t_state){
    flags.write(BMC_GLOBALS_FLAG_TRIGGER_SONG_PART, t_state);
  }
  bool triggerPartChange(){
    return flags.toggleIfTrue(BMC_GLOBALS_FLAG_TRIGGER_SONG_PART);
  }

  

#ifdef BMC_DEBUG
  bool toggleMetricsDebug(){
    metrics.toggle();
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_METRICS);
  }
  bool getMetricsDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_METRICS);
  }
  bool toggleStorageDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_STORAGE);
  }
  bool getStorageDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_STORAGE);
  }
  bool toggleBleDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_BLE);
  }
  bool getBleDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_BLE);
  }
  // MIDI IN DEBUG
  bool toggleMidiInDebug(){
    bool v = debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN);
    if(!v){
      debugFlags.off(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK);
    }
    return v;
  }
  bool getMidiInDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN);
  }
  bool toggleMidiInClockDebug(){
    if(!debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN)){
      debugFlags.off(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK);
      return false;
    }
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK);
  }
  bool getMidiInClockDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK);
  }
  // MIDI OUT DEBUG
  bool toggleMidiOutDebug(){
    bool v = debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT);
    if(!v){
      debugFlags.off(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK);
    }
    return v;
  }
  bool getMidiOutDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT);
  }

  bool toggleMidiOutClockDebug(){
    if(!debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT)){
      debugFlags.off(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK);
      return false;
    }
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK);
  }
  bool getMidiOutClockDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK);
  }



  bool toggleMidiClockDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_MIDI_CLOCK);
  }
  bool getMidiClockDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_MIDI_CLOCK);
  }
  



  bool toggleButtonsDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_BUTTONS);
  }
  bool getButtonsDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_BUTTONS);
  }
  bool toggleEncodersDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_ENCODERS);
  }
  bool getEncodersDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_ENCODERS);
  }
  bool toggleFasDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_FAS);
  }
  bool getFasDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_FAS);
  }
  bool togglePotsDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_POTS);
  }
  bool getPotsDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_POTS);
  }
  bool toggleDisplayRenderTimeDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_DISPLAY_RENDER_TIME);
  }
  bool getDisplayRenderTimeDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_DISPLAY_RENDER_TIME);
  }

  
#endif

bool getButtonStateBit(bool isGlobal, uint16_t n){
  if(isGlobal){
    #if BMC_MAX_GLOBAL_BUTTONS > 0
      return globalButtonStates.getBit(n);
    #endif
  } else {
    #if BMC_MAX_BUTTONS > 0
      return buttonStates.getBit(n);
    #endif
  }
  return 0;
}


bool pauseIli(){
  return flags.read(BMC_GLOBALS_FLAG_PAUSE_ILI);
}
bool pauseIli(bool value){
  flags.write(BMC_GLOBALS_FLAG_PAUSE_ILI, value);
  return value;
}
bool getRenderDisplayList(){
  return flags.toggleIfTrue(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST);
}
bool setRenderDisplayList(uint8_t id){
  if(onBoardEditorActive() || !settings.getDisplayListMode()){
    return false;
  }
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  // if(!displayListsActive() && !flags.read(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST)){
    
  // }
  if(displayListsActive() && !flags.read(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST)){
    flags.on(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST);
    return false;
  } else if(!displayListsActive() && !flags.read(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST)){
    displayListId = id;
    flags.on(BMC_GLOBALS_FLAG_RENDER_DISPLAY_LIST);
    return true;
  }
#endif
  return false;
}

uint8_t getDisplayListId(){
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  return displayListId;
#else
  return 0;
#endif
}

bool displayListsActive(){
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  return displayListsTimer.active();
#else
  return false;
#endif
}
bool displayListsComplete(){
  #if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
    return displayListsTimer.complete();
  #else
    return false;
  #endif
}
// bool displayListsActive(){
// #if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
//   return displayListsTimer.active();
// #else
//   return false;
// #endif
// }
void enterDisplayListMode(uint16_t value){
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  BMC_PRINTLN("*** Enter Display List Mode");
  displayListsTimer.start(value);
  pauseIli(true);
#endif
}
void exitDisplayListMode(){
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  BMC_PRINTLN("*** Exit Display List Mode");
  displayListsTimer.stop();
  displayListId = 0;
  pauseIli(false);
#endif
}
void setCustomState(uint8_t n, bool value){
  customStates.write(n, value);
}
void getCustomState(uint8_t n){
  return customStates.write(n);
}

bmcStoreEvent getDeviceEventType(uint16_t n){
  bmcStoreEvent e;
  if(n > 0 && n <= BMC_MAX_EVENTS_LIBRARY){
    return store.global.events[n-1];
  }
  return e;
}
bmcStoreName getDeviceName(uint16_t n){
  bmcStoreName t;
  if(n > 0 && n <= BMC_MAX_NAMES_LIBRARY){
    return store.global.names[n-1];
  }
  return t;
}

public:
  uint8_t offset = 0;
  uint8_t layer = 0;
  uint16_t bpm = 120;

#if BMC_MAX_PRESETS > 0
  uint16_t presetIndex = 0;
  uint8_t bank = 0;
  uint8_t preset = 0;
  const char alph[32] = BMC_ALPHABET;
#endif

#if BMC_MAX_SETLISTS > 0
  uint8_t setList = 0;
  uint16_t song = 0;
  uint8_t songPart = 0;
  uint16_t songInLibrary = 0;
  uint8_t songFlags = 0;
#endif

#if BMC_MAX_BUTTONS > 0
  BMCBitStates <BMC_MAX_BUTTONS> buttonStates;
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  BMCBitStates <BMC_MAX_GLOBAL_BUTTONS> globalButtonStates;
#endif

#if BMC_MAX_LEDS > 0
  BMCBitStates <BMC_MAX_LEDS> ledCustomState;
  BMCBitStates <BMC_MAX_LEDS> ledStates;
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  BMCBitStates <BMC_MAX_GLOBAL_LEDS> globalLedCustomState;
  BMCBitStates <BMC_MAX_GLOBAL_LEDS> globalLedStates;
#endif

#if BMC_MAX_BI_LEDS > 0
  BMCBitStates <BMC_MAX_BI_LEDS> biLedCustomState;
  BMCBitStates <BMC_MAX_BI_LEDS> biLedStates[2];
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  BMCBitStates <BMC_MAX_GLOBAL_BI_LEDS> globalBiLedCustomState;
  BMCBitStates <BMC_MAX_GLOBAL_BI_LEDS> globalBiLedStates[2];
#endif

#if BMC_MAX_TRI_LEDS > 0
  BMCBitStates <BMC_MAX_TRI_LEDS> triLedCustomState;
  BMCBitStates <BMC_MAX_TRI_LEDS> triLedStates[3];
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  BMCBitStates <BMC_MAX_GLOBAL_TRI_LEDS> globalTriLedCustomState;
  BMCBitStates <BMC_MAX_GLOBAL_TRI_LEDS> globalTriLedStates[3];
#endif



#if BMC_TOTAL_PIXELS > 0
  #if BMC_MAX_PIXELS > 0
    BMCBitStates <BMC_MAX_PIXELS> pixelStates;
  #endif
  #if BMC_MAX_GLOBAL_PIXELS > 0
    BMCBitStates <BMC_MAX_GLOBAL_PIXELS> globalPixelStates;
  #endif
  #if BMC_MAX_RGB_PIXELS > 0
    BMCBitStates <BMC_MAX_RGB_PIXELS> rgbPixelStates[3];
  #endif
  #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    BMCBitStates <BMC_MAX_GLOBAL_RGB_PIXELS> globalRgbPixelStates[3];
  #endif
  #if BMC_MAX_PIXEL_STRIP > 0
    BMCBitStates <1> pixelStripStates;
  #endif
#endif

#if BMC_MAX_NL_RELAYS > 0
  BMCBitStates <BMC_MAX_NL_RELAYS> relayNLStates;
#endif

#if BMC_MAX_L_RELAYS > 0
  BMCBitStates <BMC_MAX_L_RELAYS> relayLStates;
#endif

#if BMC_MAX_AUX_JACKS > 0
  BMCBitStates <BMC_MAX_AUX_JACKS> auxJackStates;
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  BMCTimer displayListsTimer;
  uint8_t displayListId = 0;
#endif

private:
  BMCFlags <uint32_t> flags;
  BMCFlags <uint32_t> customStates;
#ifdef BMC_DEBUG
  BMCFlags <uint16_t> debugFlags;
#endif

  BMCMetrics metrics;



  // uint32_t loopsPerSecond = 0;
  // uint32_t lastLoopsPerSecond = 0;

  void reset(){
    flags.reset();
    #ifdef BMC_DEBUG
      debugFlags.reset();
    #endif
    offset = 0;
    layer = 0;
    bpm = 120;
    metrics.reset();
    // loopsPerSecond = 0;
    // lastLoopsPerSecond = 0;
  }
};
#endif
