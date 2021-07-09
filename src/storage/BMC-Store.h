/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_STORE_H
#define BMC_STORE_H
#include <Arduino.h>

  // Button Event Object
  struct __attribute__ ((packed)) bmcStoreButtonEvent {
    uint8_t mode = 0;
    uint8_t ports = 0;
    uint32_t event = 0;
  };
  // Button Object
  struct __attribute__ ((packed)) bmcStoreButton {
    bmcStoreButtonEvent events[BMC_MAX_BUTTON_EVENTS];
    #if BMC_NAME_LEN_BUTTONS> 1
      char name[BMC_NAME_LEN_BUTTONS] = "";
    #endif
  };
  // Potentiometer object
  struct __attribute__ ((packed)) bmcStorePot {
    uint8_t ports = 0;
    uint32_t event = 0;
    #if defined(BMC_USE_POT_TOE_SWITCH)
      uint32_t toeSwitch = 0;
      uint16_t toeSwitchFlags = 0;
    #endif
    #if BMC_NAME_LEN_POTS> 1
      char name[BMC_NAME_LEN_POTS] = "";
    #endif
  };
  // Encoder object
  struct __attribute__ ((packed)) bmcStoreEncoder {
    uint8_t mode = 0;
    uint8_t ports = 0;
    uint32_t event = 0;
    #if BMC_NAME_LEN_ENCODERS> 1
      char name[BMC_NAME_LEN_ENCODERS] = "";
    #endif
  };
  // Led object, used by page leds, pwm leds, global Leds & pixels
  struct __attribute__ ((packed)) bmcStoreLed {
    uint32_t event = 0;
    #if BMC_NAME_LEN_LEDS > 1
      char name[BMC_NAME_LEN_LEDS] = "";
    #endif
  };
  // RGB Led object, used by RGB Pixel maybe in the future by others
  struct __attribute__ ((packed)) bmcStoreRgbLed {
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    #if BMC_NAME_LEN_LEDS > 1
      char name[BMC_NAME_LEN_LEDS] = "";
    #endif
  };
  // Non-Latching Relay object
  struct __attribute__ ((packed)) bmcStoreGlobalRelay {
    uint32_t event = 0;
    #if BMC_NAME_LEN_RELAYS > 1
      char name[BMC_NAME_LEN_RELAYS] = "";
    #endif
  };
  // Page Object
  struct __attribute__ ((packed)) bmcStorePage {
    #if BMC_MAX_BUTTONS > 0
      bmcStoreButton   buttons[BMC_MAX_BUTTONS];
    #endif
    #if BMC_MAX_LEDS > 0
      bmcStoreLed      leds[BMC_MAX_LEDS];
    #endif
    #if BMC_MAX_PWM_LEDS > 0
      bmcStoreLed      pwmLeds[BMC_MAX_PWM_LEDS];
    #endif
    #if BMC_MAX_PIXELS > 0
      bmcStoreLed      pixels[BMC_MAX_PIXELS];
    #endif
    #if BMC_MAX_RGB_PIXELS > 0
      bmcStoreRgbLed      rgbPixels[BMC_MAX_RGB_PIXELS];
    #endif
    #if BMC_MAX_ENCODERS > 0
      bmcStoreEncoder  encoders[BMC_MAX_ENCODERS];
    #endif
    #if BMC_MAX_POTS > 0
      bmcStorePot      pots[BMC_MAX_POTS];
    #endif
    #if BMC_NAME_LEN_PAGES > 1
      char name[BMC_NAME_LEN_PAGES] = "";
    #endif
  };

  // String Library object BMC_MAX_STRING_LIBRARY
  struct __attribute__ ((packed)) bmcStoreGlobalStringLibrary {
#if BMC_MAX_STRING_LIBRARY > 0
    char name[BMC_NAME_LEN_STRING_LIBRARY] = "";
#endif
  };
  // Library object
  struct __attribute__ ((packed)) bmcStoreGlobalLibrary {
    uint32_t event = 0;
    #if BMC_NAME_LEN_LIBRARY > 1
      char name[BMC_NAME_LEN_LIBRARY] = "";
    #endif
  };
  // Presets object
  struct __attribute__ ((packed)) bmcStoreGlobalPresets {
    uint8_t length = 0;
    bmcLibrary_t events[BMC_MAX_PRESET_ITEMS];
    #if BMC_NAME_LEN_PRESETS > 1
      char name[BMC_NAME_LEN_PRESETS] = "";
    #endif
  };
  // SetList Song object
  struct __attribute__ ((packed)) bmcStoreGlobalSetList {
    uint8_t length = 0;
    bmcPreset_t songs[BMC_MAX_SETLISTS_SONGS];
    #if BMC_NAME_LEN_SETLISTS > 1
      char name[BMC_NAME_LEN_SETLISTS] = "";
    #endif
  };
  // Custom SysEx object
  struct __attribute__ ((packed)) bmcStoreGlobalCustomSysEx {
    uint8_t length = 0;
    uint8_t event[16];
  };
  // Triggers, part of the global object
  struct __attribute__ ((packed)) bmcStoreGlobalTriggers {
    uint32_t event = 0;
    uint32_t source = 0;
  };
  // Pot Calibration, part of the global object
  struct __attribute__ ((packed)) bmcStoreGlobalPotCalibration {
    uint16_t min = 0;
    uint16_t max = 1023;
  };
  // Tempo To Tap object
  struct __attribute__ ((packed)) bmcStoreGlobalTempoToTap {
    uint32_t event = 0;
  };
  // Port Presets
  struct __attribute__ ((packed)) bmcStorePortPresets {
    uint8_t preset[16];
  };
  // Pixel Programs
  struct __attribute__ ((packed)) bmcStorePixelPrograms {
    uint8_t length = 0;
    uint8_t events[8];
  };
  // Timed Events
  struct __attribute__ ((packed)) bmcStoreGlobalTimedEvents {
    uint32_t event = 0;
    uint32_t timeout = 0;
  };
  // Settings object
  struct __attribute__ ((packed)) bmcStoreGlobalSettings {
    uint32_t flags = 0;
    uint32_t data[8];
    uint16_t routing[7];
  };
  // DO NOT CHANGE THIS ORDER!!!!!!!!!
  // This order is used to read/write from EEPROM to speed up the process
  // specially when using i2c.
  struct __attribute__ ((packed)) bmcStoreGlobal {
    bmcStoreGlobalSettings settings;
    #if BMC_MAX_SKETCH_BYTES > 0
      uint8_t sketchBytes[BMC_MAX_SKETCH_BYTES];
    #endif
    #if BMC_MAX_STRING_LIBRARY > 0 && BMC_NAME_LEN_STRING_LIBRARY > 1
      bmcStoreGlobalStringLibrary stringLibrary[BMC_MAX_STRING_LIBRARY];
    #endif
    #if BMC_MAX_LIBRARY > 0
      bmcStoreGlobalLibrary library[BMC_MAX_LIBRARY];
      #if BMC_MAX_PRESETS > 0
        bmcPreset_t startup = 0;
        bmcStoreGlobalPresets presets[BMC_MAX_PRESETS];
        #if BMC_MAX_SETLISTS > 0
          bmcStoreGlobalSetList setLists[BMC_MAX_SETLISTS];
        #endif
      #endif
    #endif
    #if BMC_MAX_GLOBAL_LEDS > 0
      bmcStoreLed leds[BMC_MAX_GLOBAL_LEDS];
    #endif
    #if BMC_MAX_GLOBAL_BUTTONS > 0
      bmcStoreButton   buttons[BMC_MAX_GLOBAL_BUTTONS];
    #endif
    #if BMC_MAX_GLOBAL_ENCODERS > 0
      bmcStoreEncoder  encoders[BMC_MAX_GLOBAL_ENCODERS];
    #endif
    #if BMC_MAX_GLOBAL_POTS > 0
      bmcStorePot      pots[BMC_MAX_GLOBAL_POTS];
      bmcStoreGlobalPotCalibration globalPotCalibration[BMC_MAX_GLOBAL_POTS];
    #endif
    #if BMC_MAX_POTS > 0
      bmcStoreGlobalPotCalibration potCalibration[BMC_MAX_POTS];
    #endif
    #if BMC_MAX_CUSTOM_SYSEX > 0
      bmcStoreGlobalCustomSysEx customSysEx[BMC_MAX_CUSTOM_SYSEX];
    #endif
    #if BMC_MAX_TRIGGERS > 0
      bmcStoreGlobalTriggers triggers[BMC_MAX_TRIGGERS];
    #endif
    #if BMC_MAX_TEMPO_TO_TAP > 0
      bmcStoreGlobalTempoToTap tempoToTap[BMC_MAX_TEMPO_TO_TAP];
    #endif
    #if BMC_MAX_NL_RELAYS > 0
      bmcStoreGlobalRelay relaysNL[BMC_MAX_NL_RELAYS];
    #endif
    #if BMC_MAX_L_RELAYS > 0
      bmcStoreGlobalRelay relaysL[BMC_MAX_L_RELAYS];
    #endif
    bmcStorePortPresets portPresets;
    #if BMC_MAX_PIXEL_PROGRAMS > 0 && BMC_MAX_PIXELS > 0
      bmcStorePixelPrograms pixelPrograms[BMC_MAX_PIXEL_PROGRAMS];
    #endif
    #if BMC_MAX_TIMED_EVENTS > 0
      bmcStoreGlobalTimedEvents timedEvents[BMC_MAX_TIMED_EVENTS];
    #endif
  };


  struct __attribute__ ((packed)) bmcStore {
    uint16_t crc = 0;
    uint16_t version = 0;
    bmcStoreGlobal global;
    bmcStorePage pages[BMC_MAX_PAGES];
  };

#endif
