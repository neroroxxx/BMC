/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license. See LICENSE file in the project root for full license information.

  I've tried to put a lot of comments thruout the library and all it's files
  The only metrics for BMC's performance are the number of "loops per second"
  and the Available RAM, the loops per second refers to how many times BMC::update()
  is executed per second. I shorten it to LPS in comments.

  If you are just building a basic controller with just buttons, leds, encoders,
  then the LPS won't be an issue, Teensys are very fast so they will give you alot of LPS.
  The only time that LPS would matter is if you have other peripherals connected
  that need to be updated very often.
  There's a callback on BMC that is called in the middle of the update() method
  you can setup a callback in your sketch with BMC::onMidUpdate(YouFunctionName)
  this function would be called in between the update method,
  the idea is if you need to run other code to read/write to a peripheral
  then you can put the function that reads that peripheral in your loop before BMC::update()
  and then assign that function to BMC::onMidUpdate() for each Arduino loop()
  that function would be called twice.

  TODO:
    - add more comments to the code to make it easier to understand
*/

#ifndef BMC_H
#define BMC_H

#define USE_SPI4TEENSY3 0

// Basic flags
#define BMC_FLAGS_CLICK_TRACK_RESPOND 0
#define BMC_FLAGS_LAYER_CHANGED 1
#define BMC_FLAGS_FIRST_LOOP 2
#define BMC_FLAGS_STATUS_LED 3


#ifndef BMC_DEBUG_MAX_TIMING
  #define BMC_DEBUG_MAX_TIMING 1
#endif

// Includes
// main definitions for BMC
#include "utility/BMC-Def.h"
// the LFO object
#include "utility/BMC-LFO.h"
// the MIDI I/O object
#include "midi/BMC-Midi.h"
// the MIDI clock master/slave handler
#include "midi/BMC-MidiClock.h"
// the MIDI Active Sense master/slave handler
#include "midi/BMC-MidiActiveSense.h"
// the Editor MIDI I/O and EEPROM handler
#include "editor/BMC-Editor.h"

#if defined(BMC_MUX_AVAILABLE)
  #include "mux/BMC-Mux.h"
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  #include "hardware/BMC-Button.h"

  #if BMC_MAX_BUTTONS > 1 || BMC_MAX_GLOBAL_BUTTONS > 1
    #include "hardware/BMC-ButtonsDualHandler.h"
  #endif
#endif


#if BMC_TOTAL_LEDS > 0
  #include "hardware/BMC-Led.h"
#endif

#if BMC_TOTAL_PIXELS > 0
  #include "hardware/BMC-Pixels.h"
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    #include "utility/BMC-PixelPrograms.h"
  #endif
#endif


#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  #include "hardware/BMC-Encoder.h"
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  #include "hardware/BMC-Pot.h"
#endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
  #include "hardware/BMC-PotCalibration.h"
#endif

#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  #include "hardware/BMC-MagicEncoder.h"
#endif


#if BMC_MAX_NL_RELAYS > 0
  #include "hardware/BMC-RelayNL.h"
#endif

#if BMC_MAX_L_RELAYS > 0
  #include "hardware/BMC-RelayL.h"
#endif

#if BMC_MAX_AUX_JACKS > 0
  #include "hardware/BMC-AuxJack.h"
#endif

#if BMC_MAX_PRESETS > 0
  #include "utility/BMC-Presets.h"
  #if BMC_MAX_SETLISTS > 0
    #include "utility/BMC-SetLists.h"
  #endif
#endif

#if defined(BMC_USE_SYNC)
  #include "sync/BMC-Sync.h"
#endif

#if BMC_MAX_CUSTOM_SYSEX > 0
  #include "utility/BMC-CustomSysEx.h"
#endif
#if BMC_MAX_TEMPO_TO_TAP > 0
  #include "utility/BMC-TempoToTap.h"
#endif
#if BMC_MAX_TRIGGERS > 0
  #include "utility/BMC-Triggers.h"
#endif
#if BMC_MAX_TIMED_EVENTS > 0
  #include "utility/BMC-TimedEvents.h"
#endif
#if defined(BMC_HAS_DISPLAY)
  #include "display/BMC-Display.h"
#endif

#if defined(BMC_USE_ON_BOARD_EDITOR)
  #include "editor/onBoard/BMC-OBEMain.h"
  // #include "editor/onBoard/BMC-IliSelector.h"
  
#endif

//const uint8_t bmcLogCurve[128] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,8,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,16,17,17,18,19,20,21,22,23,24,25,26,27,28,30,31,32,34,35,37,39,40,42,44,46,48,50,53,55,58,60,63,66,69,72,75,78,82,85,89,93,98,102,106,111,116,121,127,133,139,145,151,158,165,172,180,188,197,205,215,224,234,245,255};

// see BMC-Api.h for API calls
class BMC {
public:
  // code @ BMC.cpp
  BMC();
  void begin();
  void update();

  // code @ BMC.layer.cpp
  // get the current layer number
  uint8_t getLayer();
  // go to a new layer
  // @reassignSettings if true will reassign all global settings
  void setLayer(uint8_t layer, bool reassignSettings=false, bool forced=false);
  void reloadLayer();
  void nextLayer();
  void prevLayer();
  // scroll to a different layer, either the previous or next layer
  void scrollLayer(bool t_dir, bool t_endless, uint8_t t_amount);
  void scrollLayer(uint8_t t_settings, uint8_t t_amount);
  void scrollLayer(uint8_t t_flags, uint8_t t_min,
                  uint8_t t_max, uint8_t t_amount);
  void scrollLayer(bool t_direction, bool t_endless,
                  uint8_t t_min, uint8_t t_max,
                  uint8_t t_amount);

  // code @ BMC.sketchBytes.cpp
  // kept here and not in API as they are used internally by hardware
#if BMC_MAX_SKETCH_BYTES > 0
  // set a value for the specified sketch byte
  void setSketchByte(uint8_t n, uint8_t value);
  // save sketch bytes to EEPROM
  // @triggerStoreUpdateCallback will trigger the onStoreUpdated callback
  // if your
  void saveSketchBytes(bool triggerStoreUpdateCallback=false);
  // get the specified sketch byte
  uint8_t getSketchByte(uint8_t n);
  // get the defined sketch byte data for the specified byte
  BMCSketchByteData getSketchByteData(uint8_t n);
#endif

// ************************************
// ************************************
// BMC Private Methods
// ************************************
// ************************************
private:
  friend class BMCApi;
  // MAIN OBJECTS, these must remain in this order!!!!
  // the struct holding all data stored in EEPROM/SD
  bmcStore store;
  // this is wrapper to get/set data into store.global.settings
  BMCSettings settings;
  // BMC data that holds flags and global variables
  BMCGlobals globals;
  uint8_t & layer;
  // hold all callbacks for BMC
  BMCCallbacks callback;
  // it holds a reference to store.global.settings
  BMCFlags <uint8_t> flags;
  #if BMC_MAX_LFO > 0
    BMCLFO lfo[BMC_MAX_LFO];
    uint8_t lastLfo[BMC_MAX_LFO];
  #endif
  // the global midi object
  BMCMidi midi;
  // value typer object
  BMCTyper valueTyper;
  // struct to hold messenger data sent between sketch and editor app
  BMCMessenger messenger;
  // editor handling all editing of the store
  BMCEditor editor;
  // handles master and sleve midi clock
  BMCMidiClock midiClock;
  // handles active sense
  BMCMidiActiveSense midiActiveSense;

  

#if defined(BMC_ENABLE_ENCODER_BUTTON_FILTERING)
  BMCTimer encoderFixTimer;
#endif

#if BMC_MAX_PRESETS > 0
  BMCPresets presets;
#endif

#if BMC_MAX_SETLISTS > 0
  BMCSetLists setLists;
#endif

#if defined(BMC_USE_SYNC)
  BMCSync sync;
#endif

#if BMC_MAX_CUSTOM_SYSEX > 0
    BMCCustomSysEx customSysEx;
#endif

#if BMC_MAX_TEMPO_TO_TAP > 0
    BMCTempoToTap tempoToTap;
    void runTempoToTap();
#endif

#if BMC_MAX_TRIGGERS > 0
    BMCTriggers triggers;
    void readTrigger();
#endif

#if BMC_MAX_PIXEL_PROGRAMS > 0
    BMCPixelPrograms pixelPrograms;
#endif

#if BMC_MAX_TIMED_EVENTS > 0
    BMCTimedEvents timedEvents;
    void readTimedEvent();
#endif

  unsigned long heartbeat = 0;
  uint8_t programBank = 0;

#if BMC_MAX_LAYERS > 127 || BMC_MAX_PRESETS > 127
  // used when incoming Program Change is set to Layer or Preset,
  // when Control Change # 0 is received, it's value is the bank,
  // since there's a max of 255 layers or presets the CC#0 value can only be
  // 0 or 1, if say CC#0 value 0 is received then Program #0 will take you
  // to Layer/Preset 0, if CC#0 is 1 then Progra#0 will take you to Layer/Preset 128
  uint8_t bank = 0;
#endif

  // used for some tasks where we only want to excecute code once per milli second
  // Teensys can execute the update() method of BMC over 100 times per milli second
  // on some boards so this timer is used to lower that number of executions on some tasks
  // this value is set back to 0 at the end of the loop() method
  elapsedMillis oneMilliSecondtimer;
  bool oneMillisecondPassed(){
    return oneMilliSecondtimer>=1;
  }
  // used to send a callback every second and other tasks
  elapsedMillis oneSecondTimer;
  bool oneSecondPassed(){
    return oneSecondTimer>=1000;
  }
  // keeps track of how long BMC has been running, used by BMC for some tasks
  BMCRunTime runTime;
  BMCStopwatch stopwatch;

  // code @ BMC.cpp
  void stopwatchCmd(uint8_t cmd, uint8_t h=0, uint8_t m=0, uint8_t s=0);

  void runLayerChanged(){
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderLayerBanner();
    #endif

    bmcStoreDevice <0, BMC_MAX_LAYER_EVENTS>& device = store.layers[layer].events[0];
    for(uint8_t i = 0 ; i < BMC_MAX_LAYER_EVENTS ; i++){
      processEvent(BMC_DEVICE_GROUP_BUTTON,
                    BMC_DEVICE_ID_BUTTON,
                    layer,
                    device.events[i]
                  );
    }

    #if BMC_MAX_BUTTONS > 1
      dualPress.layerChanged();
    #endif
  }
  void runPresetChanged(){
#if BMC_MAX_PRESETS > 0
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderPresetBanner();
    #endif

    triggerPreset(presets.getIndex(), presets.getLength());

    if(callback.presetChanged){
      callback.presetChanged(presets.getBank(), presets.get());
    }
#endif
  }
  void triggerPreset(uint16_t t_preset, uint8_t len){
#if BMC_MAX_PRESETS > 0
    if(len > 0){
      bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS>& device = store.global.presets[t_preset];
      for(uint8_t i = 0 ; i < len ; i++){
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                      BMC_DEVICE_ID_BUTTON,
                      t_preset,
                      device.events[i]
                    );
      }
    }
    editor.utilitySendPreset(presets.getBank(), presets.get());
#endif
  }
  void runBankChanged(){
#if BMC_MAX_PRESETS > 0
    if(callback.presetBankChanged){
      callback.presetBankChanged(presets.getBank());
    }
#endif
  }
  void runSetListChanged(){
#if BMC_MAX_SETLISTS > 0
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderSetListBanner();
    #endif

/*
    char setListName[30] = "";
    setLists.getName(setLists.get(), setListName);
    streamToSketch(BMC_DEVICE_ID_SETLIST, setLists.get(), setListName);
*/
    if(callback.setListChanged){
      callback.setListChanged(setLists.get());
    }
#endif
  }
  void runSongChanged(){
#if BMC_MAX_SETLISTS > 0
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderSongBanner();
    #endif

/*
    char songName[30] = "";
    setLists.getSongName(songName);
    streamToSketch(BMC_DEVICE_ID_SETLIST_SONG, setLists.getSong(), songName);
*/
    if(callback.setListSongChanged){
      callback.setListSongChanged(setLists.getSong());
    }
#endif
  }
  void runSongPartChanged(){
#if BMC_MAX_SETLISTS > 0
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderSongPartBanner();
    #endif

    uint16_t songInLibrary = setLists.getSongInLibrary();
    uint8_t part = setLists.getPart();
    uint8_t len = store.global.songLibrary[songInLibrary].settings[0];
    uint16_t p = store.global.songLibrary[songInLibrary].events[part];
    if(len > 0 && p < BMC_MAX_PRESETS){
      bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS>& device = store.global.presets[p];
      triggerPreset(device.events[part], device.settings[0]);
    }
    if(callback.setListSongPartChanged){
      callback.setListSongPartChanged(setLists.getPart());
    }
#endif
  }

  void runBpmChanged(){
#if BMC_MAX_TEMPO_TO_TAP > 0
    tempoToTap.updateBpm(midiClock.getBpm());
#endif
    for(uint8_t i=0;i<BMC_MAX_LFO;i++){
      lfo[i].setBpm(midiClock.getBpm());
      lfo[i].sync();
    }
    if(callback.midiClockBpmChange){
      callback.midiClockBpmChange(midiClock.getBpm());
    }
    streamMidiClockBPM(midiClock.getBpm());
  }

  // code @ BMC.layer.cpp
  bool layerChanged();
  bool layerChangedPeek();

  // code @ BMC.events.cpp
  uint8_t processEvent(uint8_t group,
                        uint8_t deviceId,
                        uint16_t deviceIndex,
                        uint16_t event,
                        uint8_t value=0,
                        uint8_t dat=0
                      );
  void handleClockLeds();
  

  // EDITOR
  //BMC.editor.cpp
  void editorRead();
  void assignStoreData();
  void assignSettings();
  void controlReceived();
  void ctrlHardware();

#if BMC_MAX_PRESETS > 0
  void ctrlPreset();
#endif

#if defined(BMC_USE_CLICK_TRACK)
  void ctrlClickTrack();
#endif

// MIDI
// code @ BMC.midi.cpp
  void readMidi();
  void incomingMidi(BMCMidiMessage midiMessage);
  void handleMidiClock(bool isClock=false, bool isStartOrContinue=false);
  void midiProgramBankScroll(bool up, bool endless, uint8_t amount, uint8_t min, uint8_t max);
  void midiProgramBankTrigger(uint8_t channel, uint8_t ports);


// ** HARDWARE **
// code @ BMC.hardware.cpp
  void setupHardware();
  void readHardware();
  void assignHardware();
  void controlFirstLed(bool t_value);
  uint8_t parseMidiEventType(uint8_t t_type);
  // uint8_t parseUserEventType(uint8_t t_type);

#if defined(BMC_MUX_AVAILABLE)
  BMCMux mux;
#endif

// PIXELS AND LEDS
#if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 0

  #if BMC_TOTAL_PIXELS > 0
    // pixels holds both standard pixels and rgb pixels
    BMCPixels pixels = BMCPixels(globals);
    void setupPixels();
    void assignPixels();
    void readPixels();
  #endif //#if (BMC_PIXELS_PORT > 0) && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0)


  // uint8_t handleLedEvent(uint8_t index, uint32_t data, uint8_t ledType);

  // code @ BMC.hardware.leds.cpp
  #if BMC_MAX_LEDS > 0
    BMCLed leds[BMC_MAX_LEDS];
  #endif //#if BMC_MAX_LEDS > 0
  #if BMC_MAX_GLOBAL_LEDS > 0
    BMCLed globalLeds[BMC_MAX_GLOBAL_LEDS];
  #endif //if BMC_MAX_GLOBAL_LEDS > 0
  // code @ BMC.hardware.leds.cpp
  #if BMC_MAX_BI_LEDS > 0
    BMCLed biLeds[BMC_MAX_BI_LEDS*2];
  #endif //#if BMC_MAX_BI_LEDS > 0
  #if BMC_MAX_GLOBAL_BI_LEDS > 0
    BMCLed globalBiLeds[BMC_MAX_GLOBAL_BI_LEDS*2];
  #endif //if BMC_MAX_GLOBAL_BI_LEDS > 0
  #if BMC_MAX_TRI_LEDS > 0
    BMCLed triLeds[BMC_MAX_TRI_LEDS*3];
  #endif //#if BMC_MAX_TRI_LEDS > 0
  #if BMC_MAX_GLOBAL_TRI_LEDS > 0
    BMCLed globalTriLeds[BMC_MAX_GLOBAL_TRI_LEDS*3];
  #endif //if BMC_MAX_GLOBAL_TRI_LEDS > 0


#if BMC_TOTAL_LEDS > 0
    BMCEndlessTimer ledBlinkerTimer;
    void setupLeds();
    void assignLeds();
    void readLeds();
#endif

#endif // #if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 1

#if BMC_MAX_BUTTONS > 0
  // code @ BMC.hardware.buttons.cpp
  BMCButton buttons[BMC_MAX_BUTTONS];
  #if BMC_MAX_BUTTONS > 1
    BMCButtonsDualHandler dualPress;
  #endif
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  // code @ BMC.hardware.buttons.cpp
  BMCButton globalButtons[BMC_MAX_GLOBAL_BUTTONS];
  #if BMC_MAX_GLOBAL_BUTTONS > 1
    BMCButtonsDualHandler dualPressGlobal;
  #endif
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  void setupButtons();
  void assignButtons();
  void readButtons();
  void assignButton(BMCButton& button, bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>& data);

  template <uint8_t sLen, uint8_t eLen>
  void handleButton(bmcStoreDevice<sLen, eLen>& device,
                    uint8_t deviceType, uint16_t index, uint8_t t_trigger);
  //void handleButtonEvent(uint8_t type, bmcStoreEvent data);
#endif

#if BMC_MAX_NL_RELAYS > 0
  BMCRelayNL relaysNL[BMC_MAX_NL_RELAYS];
  //void setupRelaysNL();
  //void assignRelaysNL();
  //void readRelaysNL();
#endif

#if BMC_MAX_L_RELAYS > 0
  BMCRelayL relaysL[BMC_MAX_L_RELAYS];
  //void setupRelaysL();
  //void assignRelaysL();
  //void readRelaysL();
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  void setupRelays();
  void assignRelays();
  void readRelays();
  void setRelay(uint8_t index, bool latching, uint8_t cmd);
  bool getRelayState(uint8_t index, bool latching);
#endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
  BMCPotCalibration potCalibration;
  bool analogInputCalibrationToggle(int16_t deviceType=-1, int16_t n=-1){
    if(deviceType==-1 || n==-1){
      potCalibration.cancel();
      return false;
    }
    uint16_t len = BMC_MAX_POTS;
    if(deviceType == BMC_DEVICE_ID_GLOBAL_POT){
      len = BMC_MAX_GLOBAL_POTS;
    } else if(deviceType == BMC_DEVICE_ID_AUX_JACK){
      len = BMC_MAX_AUX_JACKS;
      #if BMC_MAX_AUX_JACKS > 0
      if(!auxJacks[n].isPotMode()){
        potCalibration.cancel();
        return false;
      }
      #endif
    }
    if(!potCalibration.active() && n < len){
      return potCalibration.toggle(deviceType, n);
    } else {
      potCalibration.cancel();
    }
    return false;
  }
#endif
#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  #if BMC_MAX_POTS > 0
    // code @ BMC.hardware.pots.cpp
    BMCPot pots[BMC_MAX_POTS];
  #endif

  #if BMC_MAX_GLOBAL_POTS > 0
    BMCPot globalPots[BMC_MAX_GLOBAL_POTS];
  #endif
  
  void setupPots();
  void assignPots();
  void readPots();
  void potParseToeSwitch(BMCPot& pot);
#endif




#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  // code @ BMC.hardware.encoders.cpp
  #if BMC_MAX_ENCODERS > 0
    BMCEncoder encoders[BMC_MAX_ENCODERS];
  #endif
  #if BMC_MAX_GLOBAL_ENCODERS > 0
    BMCEncoder globalEncoders[BMC_MAX_GLOBAL_ENCODERS];
  #endif
  void setupEncoders();
  void assignEncoders();
  void readEncoders();
#endif

#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  #if BMC_MAX_MAGIC_ENCODERS > 0
    BMCMagicEncoder magicEncoders[BMC_MAX_MAGIC_ENCODERS];
  #endif
  #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
    BMCMagicEncoder globalMagicEncoders[BMC_MAX_GLOBAL_MAGIC_ENCODERS];
  #endif
  void setupMagicEncoders();
  void assignMagicEncoders();
  void readMagicEncoders();
#endif



#if BMC_MAX_AUX_JACKS > 0
  BMCAuxJack auxJacks[BMC_MAX_AUX_JACKS];
  void setupAuxJacks();
  void assignAuxJacks();
  void readAuxJacks();
#endif

  // code @ BMC.debug.cpp
#if defined(BMC_DEBUG)
  BMCSerialMonitor serialMonitor;
  unsigned long millisTiming[BMC_DEBUG_MAX_TIMING];
  unsigned long microsTiming[BMC_DEBUG_MAX_TIMING];
  void setupDebug();
  void readDebug();
  void printBoardInfo();
  void printButtonTrigger(uint8_t n, uint8_t t_trigger, bool t_global=false);
  void printDebugHeader(char* str);
  void midiInDebug(BMCMidiMessage midiMessage);
  void printMidiInDebug(String str, BMCMidiMessage midiMessage);
  void debugStartTiming(uint8_t n, bool t_micros=false);
  unsigned long debugStopTiming(uint8_t n, bool t_micros=false);
  unsigned long getTiming(uint8_t n, bool t_micros=false);
#endif

#if defined(BMC_HAS_DISPLAY)
    BMCDisplay display;
#endif

#if defined(BMC_USE_ON_BOARD_EDITOR)
    BMCOBE obe;
    // BMCIliSelector iliSelector;
#endif

  // code @ BMC.sketchStream.cpp
  // Value stream handlers
  // used to send data to the sketch for use with displays
  void streamToSketch(uint8_t t_id, int t_value);
  void streamToSketch(uint8_t t_id, int t_value, const char* str);
  void streamToSketch(uint8_t t_id, int t_value, char* str);
  void streamMidi(uint8_t status, uint8_t channel, uint8_t data1, uint8_t data2=255);
  void streamRawValue(uint16_t t_value);
  void streamMidiProgram(uint8_t channel, uint8_t program);
  void streamMidiControl(uint8_t channel, uint8_t control, uint8_t value);
  void streamMidiClockBPM(uint16_t value);

};


// you can use BMC_DEFAULT(); at the top of your sketch
// to declare a default instance named "bmc"
// this include the API class which handles all the actual calls other than
#include "BMC-Api.h"
#define BMC_DEFAULT() BMCApi bmc = BMCApi();
// #define BMC_DEFAULT() BMC bmc = BMC();

#endif
