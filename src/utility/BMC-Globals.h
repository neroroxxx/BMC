/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

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

#define BMC_GLOBALS_FLAG_MIDI_IN 0
#define BMC_GLOBALS_FLAG_MIDI_OUT 1
#define BMC_GLOBALS_FLAG_EDITOR_CONNECTED 2
#define BMC_GLOBALS_FLAG_HOST_CONNECTED 3
#define BMC_GLOBALS_FLAG_BLE_CONNECTED 4
#define BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE 5

#define BMC_GLOBALS_DEBUG_FLAG_STORAGE 0
#define BMC_GLOBALS_DEBUG_FLAG_METRICS 1
#define BMC_GLOBALS_DEBUG_FLAG_BLE 2
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_IN 3
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_IN_WITH_CLOCK 4
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT 5
#define BMC_GLOBALS_DEBUG_FLAG_MIDI_OUT_WITH_CLOCK 6
#define BMC_GLOBALS_DEBUG_FLAG_BUTTONS 7
#define BMC_GLOBALS_DEBUG_FLAG_FAS 8
#define BMC_GLOBALS_DEBUG_FLAG_POTS 9


// https://github.com/mpflaga/Arduino-MemoryFree
// doesn't seem to be work with Teensy 4.0 unless
// Returns 4GB of Free RAM
#if BMC_TEENSY_MODEL != 40
extern char *__brkval;
#endif

class BMCGlobals {
public:
  BMCGlobals(bmcStore& t_store):store(t_store){
    reset();
  }
  void update(){
    flags.off(BMC_GLOBALS_FLAG_MIDI_IN);
    flags.off(BMC_GLOBALS_FLAG_MIDI_OUT);
    flags.off(BMC_GLOBALS_FLAG_MIDI_LOCAL_UPDATE);
    loopsPerSecond++;
  }
  void resetCPU(){
    lastLoopsPerSecond = loopsPerSecond;
    loopsPerSecond = 0;
  }
  uint32_t getCPU(){
    return lastLoopsPerSecond;
  }
  // https://github.com/mpflaga/Arduino-MemoryFree
  // doesn't seem to be work with Teensy 4.0 unless
  // Returns 4GB of Free RAM
  uint32_t getRAM(){
#if BMC_TEENSY_MODEL != 40
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

#ifdef BMC_DEBUG
  bool toggleMetricsDebug(){
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
  bool toggleButtonsDebug(){
    return debugFlags.toggle(BMC_GLOBALS_DEBUG_FLAG_BUTTONS);
  }
  bool getButtonsDebug(){
    return debugFlags.read(BMC_GLOBALS_DEBUG_FLAG_BUTTONS);
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

bmcStoreEvent getDeviceEventType(uint16_t n){
  bmcStoreEvent e;
  if(n > 0){
    return store.global.events[n-1];
  }
  return e;
}
bmcStoreName getDeviceName(uint16_t n){
  bmcStoreName name;
  strcpy(name.name, "");
  if(n==0 || n > BMC_MAX_NAMES_LIBRARY){
    return name;
  }
  strcpy(name.name, store.global.names[n-1].name);
  return name;
}

public:
  bmcStore& store;
  uint8_t page = 0;
  uint16_t bpm = 120;
#if BMC_MAX_PRESETS > 0
  bmcPreset_t preset = 0;
  #if BMC_MAX_SETLISTS > 0
    uint8_t setList = 0;
    bmcPreset_t song = 0;
    uint8_t songPart = 0;
    bmcPreset_t songInLibrary;
    uint8_t setListFlags = 0;
  #endif
#endif

#if BMC_MAX_BUTTONS > 0
  BMCBitStates <BMC_MAX_BUTTONS> buttonStates;
#endif
#if BMC_MAX_GLOBAL_BUTTONS > 0
  BMCBitStates <BMC_MAX_GLOBAL_BUTTONS> globalButtonStates;
#endif

#if BMC_MAX_LEDS > 0
  BMCBitStates <BMC_MAX_PIXELS> ledCustomState;
  BMCBitStates <BMC_MAX_PIXELS> ledStates;
#endif
#if BMC_MAX_GLOBAL_LEDS > 0
  BMCBitStates <BMC_MAX_GLOBAL_LEDS> globalLedCustomState;
  BMCBitStates <BMC_MAX_GLOBAL_LEDS> globalLedStates;
#endif
#if BMC_PIXELS_PORT > 0
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
    BMCBitStates <BMC_MAX_GLOBAL_RGB_PIXELS> globalRrgbPixelStates[3];
  #endif
#endif

private:
  BMCFlags <uint8_t> flags;
#ifdef BMC_DEBUG
  BMCFlags <uint16_t> debugFlags;
#endif

  uint32_t loopsPerSecond = 0;
  uint32_t lastLoopsPerSecond = 0;
  void reset(){
    flags.reset();
    #ifdef BMC_DEBUG
      debugFlags.reset();
    #endif
    loopsPerSecond = 0;
    lastLoopsPerSecond = 0;
  }
};
#endif
