/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
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
#define BMC_FLAGS_PAGE_CHANGED 1
#define BMC_FLAGS_FIRST_LOOP 2
#define BMC_FLAGS_STATUS_LED 3


#ifndef BMC_DEBUG_MAX_TIMING
  #define BMC_DEBUG_MAX_TIMING 1
#endif

// Includes
#include "utility/BMC-Def.h"
#include "midi/BMC-Midi.h"
#include "midi/BMC-MidiClock.h"
#include "midi/BMC-MidiActiveSense.h"
#include "editor/BMC-Editor.h"

#if defined(BMC_USE_FAS)
  #include "sync/fas/BMC-Fas.h"
#endif

#if defined(BMC_USE_KEMPER)
  #include "sync/kemp/BMC-Kemp.h"
#endif

#if defined(BMC_USE_BEATBUDDY)
  #include "sync/beatbuddy/BMC-BeatBuddy.h"
#endif

#if defined(BMC_USE_HELIX)
  #include "sync/helix/BMC-Helix.h"
#endif

#if defined(BMC_MUX_AVAILABLE)
  #include "mux/BMC-Mux.h"
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  #include "hardware/BMC-Button.h"
  // delays for buttons are only available if buttons have more
  // than 1 event compiled
  #if defined(BMC_BUTTON_DELAY_ENABLED)
    #include "hardware/BMC-ButtonsDelayHandler.h"
  #endif
  #if BMC_MAX_BUTTONS > 0
    #include "hardware/BMC-ButtonsDualHandler.h"
  #endif
#endif


#if BMC_MAX_LEDS > 0 || BMC_MAX_GLOBAL_LEDS > 0
  #include "hardware/BMC-Led.h"
#endif

#if BMC_PIXELS_PORT > 0 && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0)
  #include "hardware/BMC-Pixels.h"
#endif

#if BMC_MAX_PWM_LEDS > 0
  #include "hardware/BMC-PwmLed.h"
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  #include "hardware/BMC-Encoder.h"
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  #include "hardware/BMC-Pot.h"
  #include "hardware/BMC-PotCalibration.h"
#endif

#if BMC_MAX_NL_RELAYS > 0
  #include "hardware/BMC-RelayNL.h"
#endif

#if BMC_MAX_L_RELAYS > 0
  #include "hardware/BMC-RelayL.h"
#endif

#if BMC_MAX_AUX_JACKS > 0
  #include "hardware/BMC-AuxJacks.h"
#endif


#if BMC_MAX_LIBRARY > 0
  #include "utility/BMC-Library.h"
  #if BMC_MAX_PRESETS > 0
    #include "utility/BMC-Presets.h"
    #if BMC_MAX_SETLISTS > 0
      #include "utility/BMC-SetLists.h"
    #endif
  #endif
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
// see BMC-Api.h for API calls
class BMC {
private:
  BMCCallbacks callback;
public:
  // code @ BMC.cpp
  BMC();
  void begin();
  void update();

  // code @ BMC.page.cpp
  // get the current page number
  uint8_t getPage();
  // go to a new page
  // @reassignSettings if true will reassign all global settings
  void setPage(uint8_t page, bool reassignSettings=false);
  void nextPage();
  void prevPage();
  // scroll to a different page, either the previous or next page
  void scrollPage(uint8_t t_flags, uint8_t t_min,
                  uint8_t t_max, uint8_t t_amount);
  void scrollPage(bool t_direction, bool t_endless,
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
  // BMC data that holds flags and global variables
  BMCGlobals globals;
  // a reference to store.global
  bmcStoreGlobal& globalData;
  // it holds a reference to store.global.settings
  BMCFlags <uint8_t> flags;
  // this is wrapper to get/set data into store.global.settings
  BMCSettings settings;
  // the global midi object
  BMCMidi midi;
  // value typer object
  BMCTyper valueTyper;
  // used for the value typer when sending PC or CC
  uint8_t typerChannel = 1;
  // struct to hold messenger data sent between sketch and editor app
  BMCMessenger messenger;
  // editor handling all editing of the store
  BMCEditor editor;
  // handles master and sleve midi clock
  BMCMidiClock midiClock;
  // handles active sense
  BMCMidiActiveSense midiActiveSense;

#if defined(BMC_USE_BEATBUDDY)
  // handles beatbuddy syncing and commands
  BMCBeatBuddy beatBuddy;
#endif

#if defined(BMC_USE_HELIX)
  // handles helix commands
  BMCHelix helix;
#endif

#if defined(BMC_USE_FAS)
  // handles Fractal devices syncing
  BMCFas fas;
#endif

#if defined(BMC_USE_KEMPER)
// handles Kemper devices see src/sync/BMC-Kemper.h
  BMCKemper kemper;
#endif


#if BMC_MAX_CUSTOM_SYSEX > 0
    BMCCustomSysEx customSysEx;
#endif

#if BMC_MAX_LIBRARY > 0
  BMCLibrary library;
  #if BMC_MAX_PRESETS > 0
    BMCPresets presets;
    #if BMC_MAX_SETLISTS > 0
      BMCSetLists setLists;
    #endif
  #endif
#endif

#if BMC_MAX_TEMPO_TO_TAP > 0
    BMCTempoToTap tempoToTap;
#endif

#if BMC_MAX_TRIGGERS > 0
    BMCTriggers triggers;
#endif

  uint8_t page = 0;
  uint8_t programBank = 0;

#if BMC_MAX_PAGE > 127 || BMC_MAX_PRESETS > 127
  // used when incoming Program Change is set to Page or Preset,
  // when Control Change # 0 is received, it's value is the bank,
  // since there's a max of 255 pages or presets the CC#0 value can only be
  // 0 or 1, if say CC#0 value 0 is received then Program #0 will take you
  // to Page/Preset 0, if CC#0 is 1 then Progra#0 will take you to Page/Preset 128
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

  // code @ BMC.page.cpp
  bool pageChanged();
  bool pageChangedPeek();

#if BMC_MAX_PRESETS > 0 || BMC_MAX_PAGES > 1
  void triggerTmpScroller();
#endif
  void scrollTmpPage(uint8_t t_flags, uint8_t t_min,
                  uint8_t t_max, uint8_t t_amount);
  void scrollTmpPage(bool t_direction, bool t_endless,
                  uint8_t t_min, uint8_t t_max,
                  uint8_t t_amount);

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
  void midiProgramBankTrigger(uint8_t amount, uint8_t channel, uint8_t ports);

// TRIGGERS
// code @ BMC.triggers.cpp
#if BMC_MAX_TRIGGERS > 0
  void readTrigger();
  void processTrigger(uint8_t index);
#endif

// ** HARDWARE **
// code @ BMC.hardware.cpp
  void setupHardware();
  void readHardware();
  void assignHardware();
  uint8_t parseMidiEventType(uint8_t t_type);
  uint8_t parseUserEventType(uint8_t t_type);

#if defined(BMC_MUX_AVAILABLE)
  BMCMux mux;
#endif

// PIXELS AND LEDS
#if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 0

  #if (BMC_PIXELS_PORT > 0) && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0)
    // pixels holds both standard pixels and rgb pixels
    BMCPixels pixels;

    #if BMC_MAX_PIXELS > 0
      // code @ BMC.hardware.pixels.cpp
      #if BMC_MAX_PIXELS <= 8
        uint8_t pixelStates = 0;
      #elif BMC_MAX_PIXELS <= 16
        uint16_t pixelStates = 0;
      #else
        uint32_t pixelStates = 0;
      #endif
      uint8_t pixelCustomState[BMC_MAX_PIXELS];
      void setupPixels();
      void assignPixels();
      void readPixels();
      //void handlePixel(uint8_t index, uint32_t event);
    #endif //#if BMC_MAX_PIXELS > 0

    #if BMC_MAX_RGB_PIXELS > 0
      // code @ BMC.hardware.rgbPixels.cpp
      #if BMC_MAX_RGB_PIXELS <= 8
        uint8_t rgbPixelStatesR = 0;
        uint8_t rgbPixelStatesG = 0;
        uint8_t rgbPixelStatesB = 0;
      #elif BMC_MAX_RGB_PIXELS <= 16
        uint16_t rgbPixelStatesR = 0;
        uint16_t rgbPixelStatesG = 0;
        uint16_t rgbPixelStatesB = 0;
      #else
        uint32_t rgbPixelStatesR = 0;
        uint32_t rgbPixelStatesG = 0;
        uint32_t rgbPixelStatesB = 0;
      #endif
      uint8_t rgbPixelCustomState[BMC_MAX_RGB_PIXELS];
      void setupRgbPixels();
      void assignRgbPixels();
      void readRgbPixels();
      //void handleRgbPixel(uint8_t index, uint32_t event, uint8_t nColor);
    #endif //#if BMC_MAX_RGB_PIXELS > 0

  #endif //#if (BMC_PIXELS_PORT > 0) && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0)
  uint8_t handleLedEvent(uint8_t index, uint32_t data, uint8_t ledType);
  bool handleStatusLedEvent(uint8_t status);
  void handleClockLeds();
  void controlFirstLed(bool t_value);
  #if defined(BMC_USE_BEATBUDDY)
    bool handleBeatBuddyLedEvent(uint8_t status, uint8_t data);
  #endif //#ifdef BMC_USE_BEATBUDDY

  // code @ BMC.hardware.leds.cpp
  #if BMC_MAX_LEDS > 0
    BMCLed leds[BMC_MAX_LEDS];
    #if BMC_MAX_LEDS <= 8
      BMCFlags <uint8_t> ledCustomState;
      uint8_t ledStates = 0;
    #elif BMC_MAX_LEDS <= 16
      BMCFlags <uint16_t> ledCustomState;
      uint16_t ledStates = 0;
    #else
      BMCFlags <uint32_t> ledCustomState;
      uint32_t ledStates = 0;
    #endif

    void assignLeds();
    void readLeds();
  #endif //#if BMC_MAX_LEDS > 0

  #if BMC_MAX_GLOBAL_LEDS > 0
    BMCLed globalLeds[BMC_MAX_GLOBAL_LEDS];
    #if BMC_MAX_GLOBAL_LEDS <= 8
      BMCFlags <uint8_t> globalLedCustomState;
      uint8_t globalLedStates = 0;
    #else
      BMCFlags <uint16_t> globalLedCustomState;
      uint16_t globalLedStates = 0;
    #endif
    void assignGlobalLeds();
    void readGlobalLeds();
  #endif //if BMC_MAX_GLOBAL_LEDS > 0


#if BMC_MAX_LEDS > 0 || BMC_MAX_GLOBAL_LEDS > 0
    void setupLeds();
#endif



  #if BMC_MAX_PWM_LEDS > 0
    // code @ BMC.hardware.pwmLeds.cpp
    BMCPwmLed pwmLeds[BMC_MAX_PWM_LEDS];
    #if BMC_MAX_PWM_LEDS <= 8
      uint8_t pwmLedStates = 0;
    #else
      uint16_t pwmLedStates = 0;
    #endif
    uint8_t pwmLedCustomState[BMC_MAX_PWM_LEDS];
    void setupPwmLeds();
    void assignPwmLeds();
    void readPwmLeds();
    //void handlePwmLed(uint8_t index, uint32_t event, BMCPwmLed& item);
  #endif //#if BMC_MAX_PWM_LEDS > 0

#endif // #if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 1

#if BMC_MAX_BUTTONS > 0
  // code @ BMC.hardware.buttons.cpp
  BMCButton buttons[BMC_MAX_BUTTONS];
  #if defined(BMC_BUTTON_DELAY_ENABLED)
    BMCButtonsDelayHandler buttonsDelay;
  #endif
  #if BMC_MAX_BUTTONS > 1
    BMCButtonsDualHandler dualPress;
  #endif
  #if BMC_MAX_BUTTONS > 32
    uint32_t buttonStates = 0;
    uint32_t buttonStates2 = 0;
  #elif BMC_MAX_BUTTONS > 16
    uint32_t buttonStates = 0;
  #elif BMC_MAX_BUTTONS > 8
    uint16_t buttonStates = 0;
  #else
    uint8_t buttonStates = 0;
  #endif

  void assignButtons();
  void readButtons();
  void handleButton(uint8_t index, uint8_t t_trigger=0);
#endif


#if BMC_MAX_GLOBAL_BUTTONS > 0
  // code @ BMC.hardware.buttons.cpp
  BMCButton globalButtons[BMC_MAX_GLOBAL_BUTTONS];
  #if defined(BMC_BUTTON_DELAY_ENABLED)
    BMCButtonsDelayHandler globalButtonsDelay;
  #endif
  #if BMC_MAX_GLOBAL_BUTTONS > 1
    BMCButtonsDualHandler dualPressGlobal;
  #endif
  #if BMC_MAX_GLOBAL_BUTTONS > 16
    uint32_t globalButtonStates = 0;
  #elif BMC_MAX_GLOBAL_BUTTONS > 8
    uint16_t globalButtonStates = 0;
  #else
    uint8_t globalButtonStates = 0;
  #endif
  void setupGlobalButtons();
  void assignGlobalButtons();
  void readGlobalButtons();
  void handleGlobalButton(uint8_t index=0, uint8_t t_trigger=0);
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  void setupButtons();
  void assignButton(BMCButton& button, bmcStoreButton& data);
  void handleButtonEvent(uint8_t type, bmcStoreButtonEvent data);
#endif

#if BMC_MAX_NL_RELAYS > 0
  BMCRelayNL relaysNL[BMC_MAX_NL_RELAYS];
  BMCRelayMidiTrigger relaysNLTmp[BMC_MAX_NL_RELAYS];
  #if BMC_MAX_NL_RELAYS > 16
    uint32_t relayNLStates = 0;
  #elif BMC_MAX_NL_RELAYS > 8
    uint16_t relayNLStates = 0;
  #elif BMC_MAX_NL_RELAYS > 0
    uint8_t relayNLStates = 0;
  #endif
  void setupRelaysNL();
  void assignRelaysNL();
  void checkRelaysNLMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2);
  void readRelaysNL();
  void handleRelaysNL(uint8_t index=0);
#endif

#if BMC_MAX_L_RELAYS > 0
  BMCRelayL relaysL[BMC_MAX_L_RELAYS];
  BMCRelayMidiTrigger relaysLTmp[BMC_MAX_L_RELAYS];
  #if BMC_MAX_L_RELAYS > 16
    uint32_t relayLStates = 0;
  #elif BMC_MAX_L_RELAYS > 8
    uint16_t relayLStates = 0;
  #elif BMC_MAX_L_RELAYS > 0
    uint8_t relayLStates = 0;
  #endif
  void setupRelaysL();
  void assignRelaysL();
  void checkRelaysLMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2);
  void readRelaysL();
  void handleRelaysL(uint8_t index=0);
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  void handleRelay(uint8_t index, bool latching, uint32_t event);
  void setRelay(uint8_t index, bool latching, uint8_t cmd);
  bool getRelayState(uint8_t index, bool latching);
  void checkRelaysMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2);
  void checkRelaysMidiInput(BMCMidiMessage message);
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  BMCPotCalibration potCalibration;
  void setupPots();
  void assignPot(BMCPot& pot, bmcStorePot& storeData, bmcStoreGlobalPotCalibration& calibration);
  void handlePot(bmcStorePot& data, uint8_t value=0);
#endif

#if BMC_MAX_POTS > 0
  // code @ BMC.hardware.pots.cpp
  BMCPot pots[BMC_MAX_POTS];
  void assignPots();
  void readPots();
  void potParseToeSwitch(uint16_t event, bool on, uint8_t ports);
  uint16_t getPotAnalogValue(uint8_t n=255);
  void potCalibrationToggle(uint8_t n=255);
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  // code @ BMC.hardware.pots.cpp
  BMCPot globalPots[BMC_MAX_GLOBAL_POTS];
  void assignGlobalPots();
  void readGlobalPots();
  uint16_t getGlobalPotAnalogValue(uint8_t n=255);
  void globalPotCalibrationToggle(uint8_t n=255);
#endif



#if BMC_MAX_ENCODERS > 0
  // code @ BMC.hardware.encoders.cpp
  BMCEncoder encoders[BMC_MAX_ENCODERS];
  void assignEncoders();
  void readEncoders();

#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  // code @ BMC.hardware.encoders.cpp
  BMCEncoder globalEncoders[BMC_MAX_GLOBAL_ENCODERS];
  void assignGlobalEncoders();
  void readGlobalEncoders();
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  void setupEncoders();
  void assignEncoder(BMCEncoder& encoder, bmcStoreEncoder& data);
  void handleEncoder(bmcStoreEncoder& data, bool increased=false);
  uint16_t getNewEncoderValue(uint8_t mode, uint16_t value,
                              uint16_t lowest, uint16_t highest,
                              uint16_t min, uint16_t max,
                              bool increased, bool endless);
#endif

#if BMC_MAX_AUX_JACKS > 0
  BMCAuxJacks auxJacks;
  uint8_t auxJacksStates = 0;
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

  BMCTmpScroller tmpScroller;

  // code @ BMC.sketchStream.cpp
  // Value stream handlers
  // used to send data to the sketch for use with displays
  void streamToSketch(uint8_t t_id, int t_value);
  void streamToSketch(uint8_t t_id, int t_value, const char* str);
  void streamToSketch(uint8_t t_id, int t_value, char* str);
  void streamMidi(uint8_t status, uint8_t channel, uint8_t data1, uint8_t data2=255);
  void streamRawValue(uint16_t t_value);
  void streamTmpScrollerPage(uint8_t value);
  void streamTmpScrollerPreset(uint8_t value);
  void streamMidiProgram(uint8_t channel, uint8_t program);
  void streamMidiControl(uint8_t channel, uint8_t control, uint8_t value);
  void streamMidiClockBPM(uint16_t value);

};


// you can use BMC_DEFAULT(); at the top of your sketch
// to declare a default instance named "bmc"
// this include the API class which handles all the actual calls other than
#include "BMC-Api.h"
#define BMC_DEFAULT() BMCApi bmc = BMCApi();

#endif
