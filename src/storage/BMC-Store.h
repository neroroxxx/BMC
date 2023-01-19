/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_STORE_H
#define BMC_STORE_H
#include <Arduino.h>



  // BMC Event Object for BMC 2.0
  struct __attribute__ ((packed)) bmcStoreEvent {
    bmcName_t name = 0;
    uint8_t settings = 0;
    uint8_t type = 0;
    uint8_t ports = 0;
    uint32_t event = 0;
  };
  // BMC Name Object for BMC 2.0
  struct __attribute__ ((packed)) bmcStoreName {
    char name[BMC_MAX_NAMES_LENGTH] = "";
  };

  // BMC Device Object for BMC 2.0
  template <uint8_t sLen, uint8_t eLen, typename T=bmcEvent_t>
  struct __attribute__ ((packed)) bmcStoreDevice {
    bmcName_t name = 0;
    uint8_t settings[sLen];
    T events[eLen];
  };

  
  
  // Layer Object
  struct __attribute__ ((packed)) bmcStoreLayer {
    bmcName_t name;
    #if BMC_MAX_BUTTONS > 0
      bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS> buttons[BMC_MAX_BUTTONS];
    #endif
    #if BMC_MAX_LEDS > 0
      bmcStoreDevice <1, 1> leds[BMC_MAX_LEDS];
    #endif
    #if BMC_MAX_BI_LEDS > 0
      bmcStoreDevice <2, 2> biLeds[BMC_MAX_BI_LEDS];
    #endif
    #if BMC_MAX_TRI_LEDS > 0
      bmcStoreDevice <3, 3> triLeds[BMC_MAX_TRI_LEDS];
    #endif
    #if BMC_MAX_PIXELS > 0
      bmcStoreDevice <1, 1> pixels[BMC_MAX_PIXELS];
    #endif
    #if BMC_MAX_RGB_PIXELS > 0
      bmcStoreDevice <1, 3> rgbPixels[BMC_MAX_RGB_PIXELS];
    #endif
    #if BMC_MAX_MAGIC_ENCODERS > 0
      bmcStoreDevice <3, 3> magicEncoders[BMC_MAX_MAGIC_ENCODERS];
    #endif
    #if BMC_MAX_PIXEL_STRIP > 0
      bmcStoreDevice <1, 1> pixelStrip[1];
    #endif
    #if BMC_MAX_ENCODERS > 0
      bmcStoreDevice <1, 1> encoders[BMC_MAX_ENCODERS];
    #endif
    #if BMC_MAX_POTS > 0
      bmcStoreDevice <1, 3> pots[BMC_MAX_POTS];
    #endif
    #if BMC_MAX_OLED > 0
      bmcStoreDevice <1, 1> oled[BMC_MAX_OLED];
    #endif
    #if BMC_MAX_ILI9341_BLOCKS > 0
      bmcStoreDevice <1, 1> ili[BMC_MAX_ILI9341_BLOCKS];
    #endif
  };

  struct __attribute__ ((packed)) bmcStoreTouchSettings {
    float xM = 0.0;
    float xC = 0.0;
    float yM = 0.0;
    float yC = 0.0;
  };

 // Settings object
  struct __attribute__ ((packed)) bmcStoreGlobalSettings {
    uint32_t flags = 0;
    uint32_t data[8];
    uint16_t routing[7];
    uint16_t startup = 0;
    #ifdef BMC_HAS_TOUCH_SCREEN
    bmcStoreTouchSettings touchCalibration;
    #endif
  };
  // Pot Calibration, part of the global object
  struct __attribute__ ((packed)) bmcStoreGlobalPotCalibration {
    uint16_t min = 0;
    uint16_t max = 1023;
  };
  // DO NOT CHANGE THIS ORDER!!!!!!!!!
  // This order is used to read/write from EEPROM to speed up the process
  // specially when using i2c.
  struct __attribute__ ((packed)) bmcStoreGlobal {
    bmcStoreGlobalSettings settings;
    bmcStoreEvent events[BMC_MAX_EVENTS_LIBRARY];
    bmcStoreName names[BMC_MAX_NAMES_LIBRARY];
    bmcStoreDevice <0, 1, uint8_t> portPresets[16];
    bmcStoreDevice <0, 6, uint8_t> shortcuts[1];
    #if BMC_MAX_LFO > 0
      bmcStoreDevice <3, 5, uint8_t> lfo[BMC_MAX_LFO];
    #endif
    #if BMC_MAX_SKETCH_BYTES > 0
      bmcStoreDevice <0, BMC_MAX_SKETCH_BYTES, uint8_t> sketchBytes[1];
    #endif
    #if BMC_MAX_PRESETS > 0
      bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS> presets[BMC_MAX_PRESETS];
    #endif
    #if BMC_MAX_SETLISTS > 0
      bmcStoreDevice <1, BMC_MAX_SETLISTS_SONGS> setLists[BMC_MAX_SETLISTS];
      bmcStoreDevice <1, BMC_MAX_SETLISTS_SONG_PARTS> songLibrary[BMC_MAX_SETLISTS_SONGS_LIBRARY];
    #endif
    #if BMC_MAX_GLOBAL_BUTTONS > 0
      bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS> buttons[BMC_MAX_BUTTONS];
    #endif
    #if BMC_MAX_GLOBAL_LEDS > 0
      bmcStoreDevice <1, 1> leds[BMC_MAX_GLOBAL_LEDS];
    #endif
    #if BMC_MAX_GLOBAL_BI_LEDS > 0
      bmcStoreDevice <2, 2> biLeds[BMC_MAX_GLOBAL_BI_LEDS];
    #endif
    #if BMC_MAX_GLOBAL_TRI_LEDS > 0
      bmcStoreDevice <3, 3> triLeds[BMC_MAX_GLOBAL_TRI_LEDS];
    #endif
    #if BMC_MAX_GLOBAL_ENCODERS > 0
      bmcStoreDevice <1, 1> encoders[BMC_MAX_GLOBAL_ENCODERS];
    #endif
    #if BMC_MAX_GLOBAL_POTS > 0
      bmcStoreDevice <1, 3> pots[BMC_MAX_GLOBAL_POTS];
    #endif
    #if BMC_TOTAL_POTS_AUX_JACKS > 0
      bmcStoreDevice <0, 2, uint16_t> potCalibration[BMC_TOTAL_POTS_AUX_JACKS];
    #endif
    #if BMC_MAX_GLOBAL_PIXELS > 0
      bmcStoreDevice <1, 1> pixels[BMC_MAX_GLOBAL_PIXELS];
    #endif
    #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
      bmcStoreDevice <1, 3> rgbPixels[BMC_MAX_GLOBAL_RGB_PIXELS];
    #endif
    #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
      bmcStoreDevice <3, 3> magicEncoders[BMC_MAX_GLOBAL_MAGIC_ENCODERS];
    #endif
    #if BMC_MAX_NL_RELAYS > 0
      bmcStoreDevice <1, 1> relaysNL[BMC_MAX_NL_RELAYS];
    #endif
    #if BMC_MAX_L_RELAYS > 0
      bmcStoreDevice <1, 1> relaysL[BMC_MAX_L_RELAYS];
    #endif
    #if BMC_MAX_AUX_JACKS > 0
      bmcStoreDevice <2, 3> auxJacks[BMC_MAX_AUX_JACKS];
    #endif
    #if BMC_MAX_CUSTOM_SYSEX > 0
      bmcStoreDevice <1, 16, uint8_t> customSysEx[BMC_MAX_CUSTOM_SYSEX];
    #endif
    #if BMC_MAX_TRIGGERS > 0
      bmcStoreDevice <1, 2> triggers[BMC_MAX_TRIGGERS];
    #endif
    #if BMC_MAX_TEMPO_TO_TAP > 0
      bmcStoreDevice <1, 1> tempoToTap[BMC_MAX_TEMPO_TO_TAP];
    #endif
    #if BMC_MAX_PIXEL_PROGRAMS > 0
      bmcStoreDevice <1, 8, uint8_t> pixelPrograms[BMC_MAX_PIXEL_PROGRAMS];
    #endif
    #if BMC_MAX_TIMED_EVENTS > 0
      bmcStoreDevice <2, 1> timedEvents[BMC_MAX_TIMED_EVENTS];
    #endif
  };
  struct __attribute__ ((packed)) bmcStore {
    uint16_t crc = 0;
    uint16_t version = 0;
    bmcStoreGlobal global;
    bmcStoreLayer layers[BMC_MAX_LAYERS];
  };

#endif
