/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_CONFIG_CHECK_H
#define BMC_CONFIG_CHECK_H
#include "utility/BMC-ConfigCheckPins.h"

  // the min/max values that can ever be used
  // the max for everything is 255 this is to be able to fit lengths inside
  // 8-bit unsigned integers, specially when sending these values out thru midi

  #define BMC_LIMIT_MIN_LIBRARY 0
  #define BMC_LIMIT_MAX_LIBRARY 255

  #define BMC_LIMIT_MIN_PRESETS 0
  #define BMC_LIMIT_MAX_PRESETS 255

  #define BMC_LIMIT_MIN_PRESET_ITEMS 1
  #define BMC_LIMIT_MAX_PRESET_ITEMS 16

  #define BMC_LIMIT_MIN_SETLIST 0
  #define BMC_LIMIT_MAX_SETLIST 32

  #define BMC_LIMIT_MIN_SETLIST_SONGS 0
  #define BMC_LIMIT_MAX_SETLIST_SONGS 32

  #define BMC_LIMIT_MIN_CUSTOM_SYSEX 0
  #define BMC_LIMIT_MAX_CUSTOM_SYSEX 127

  #define BMC_LIMIT_MIN_SKETCH_BYTES 0
  #define BMC_LIMIT_MAX_SKETCH_BYTES 32

  #define BMC_LIMIT_MIN_TRIGGERS 0
  #define BMC_LIMIT_MAX_TRIGGERS 127

  #define BMC_LIMIT_MIN_TEMPO_TO_TAP 0
  #define BMC_LIMIT_MAX_TEMPO_TO_TAP 32

  #define BMC_LIMIT_MIN_RELAYS 0
  #define BMC_LIMIT_MAX_RELAYS 16

  #define BMC_LIMIT_MIN_PAGES 1
  #define BMC_LIMIT_MAX_PAGES 255

  #define BMC_LIMIT_MIN_BUTTON_EVENTS 1
  #define BMC_LIMIT_MAX_BUTTON_EVENTS 8


  #if defined(BMC_I2C_FREQ_100K)
    #define BMC_I2C_FREQ 100000
  #else
    #define BMC_I2C_FREQ 400000
  #endif

  // set what the pinMode for buttons will be
  #if defined(BMC_BUTTON_NO_PULLUP)
    #define BMC_BUTTON_PIN_MODE INPUT
  #else
    #define BMC_BUTTON_PIN_MODE INPUT_PULLUP
  #endif

  // set what the pinMode for encoders will be
  #if defined(BMC_ENCODER_INPUT_PULLUP)
    #define BMC_ENCODER_PIN_MODE INPUT_PULLUP
  #else
    #define BMC_ENCODER_PIN_MODE INPUT
  #endif

  #ifndef BMC_MAX_MUX_IN
    #define BMC_MAX_MUX_IN 0
  #endif
  #if BMC_MAX_MUX_IN > 64
    #error "BMC supports up to 64 Mux In Pins"
  #endif

  #ifndef BMC_MAX_MUX_IN_ANALOG
    #define BMC_MAX_MUX_IN_ANALOG 0
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 64
    #error "BMC supports up to 64 Analog Mux Pins"
  #endif

  #if (BMC_MAX_MUX_IN+BMC_MAX_MUX_IN_ANALOG)>64
    #error "BMC supports a maximum of 64 Mux Pins total, that inclues a sum of BMC_MAX_MUX_IN and BMC_MAX_MUX_IN_ANALOG"
  #endif

  #if BMC_MAX_MUX_IN > 0 && (BMC_MAX_BUTTONS==0 && BMC_MAX_ENCODERS==0)
    #undef BMC_MAX_MUX_IN
    #define BMC_MAX_MUX_IN 0
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 0 && BMC_MAX_POTS==0
    #undef BMC_MAX_MUX_IN_ANALOG
    #define BMC_MAX_MUX_IN_ANALOG 0
  #endif

  #ifndef BMC_MUX_IN_ANALOG_CHIPSET
    #define BMC_MUX_IN_ANALOG_CHIPSET 0
  #endif

  #ifndef BMC_MUX_IN_CHIPSET
    #define BMC_MUX_IN_CHIPSET 0
  #endif



  #define BMC_TOTAL_MUX_PINS (BMC_MAX_MUX_IN+BMC_MAX_MUX_IN_ANALOG)



  // we need the size of the sysex to be at least 100 to properly work
  // with the editor functions
  #if BMC_MIDI_SYSEX_SIZE < 100
    #undef BMC_MIDI_SYSEX_SIZE
    #define BMC_MIDI_SYSEX_SIZE 100
  #endif

  #if defined(BMC_USE_TIME) && !defined(BMC_TIME_ADJUST)
    #define BMC_TIME_ADJUST 20
  #endif

  // device name
  #if !defined(BMC_DEVICE_NAME)
    #define BMC_DEVICE_NAME "BMC"
  #endif

  #if defined(BMC_USE_USB_HOST) && BMC_TEENSY_HAS_USB_HOST == true
    #define BMC_USB_HOST_ENABLED
  #endif

  #if defined(BMC_USE_MIDI_SERIAL_A) && defined(BMC_MIDI_SERIAL_IO_A)
    #define BMC_MIDI_SERIAL_A_ENABLED
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_B) && defined(BMC_MIDI_SERIAL_IO_B)
    #define BMC_MIDI_SERIAL_B_ENABLED
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_C) && defined(BMC_MIDI_SERIAL_IO_C)
    #define BMC_MIDI_SERIAL_C_ENABLED
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_D) && defined(BMC_MIDI_SERIAL_IO_D) && BMC_TEENSY_TOTAL_SERIAL_PORTS > 3
    #define BMC_MIDI_SERIAL_D_ENABLED
  #endif

  #if defined(BMC_MIDI_SERIAL_A_ENABLED) || defined(BMC_MIDI_SERIAL_B_ENABLED) || defined(BMC_MIDI_SERIAL_C_ENABLED) || defined(BMC_MIDI_SERIAL_D_ENABLED)
    #define BMC_HAS_SERIAL_MIDI
  #endif

  #if defined(BMC_USE_MIDI_BLE)
    #define BMC_MIDI_BLE_ENABLED
    /*
    #if defined(BMC_USE_MIDI_SERIAL_B) && BMC_TEENSY_TOTAL_SERIAL_PORTS < 4
      #undef BMC_MIDI_SERIAL_B_ENABLED
    #endif
    */
    #if !defined(BMC_MIDI_BLE_BOARD)
      #define BMC_MIDI_BLE_BOARD 0 // nRF8001
      // set BMC_MIDI_BLE_BOARD  to 1 for adafruit SPI Friend
    #endif
  #endif

  #ifndef BMC_MAX_SKETCH_BYTES
    #define BMC_MAX_SKETCH_BYTES 0
  #endif
  #if BMC_MAX_SKETCH_BYTES > 32
    #undef BMC_MAX_SKETCH_BYTES
    #define BMC_MAX_SKETCH_BYTES 32
  #endif

  #if defined(BMC_USE_SD_CARD) && BMC_TEENSY_HAS_SD_CARD == true
    #ifdef BMC_USE_24LC256
      #undef BMC_USE_24LC256
    #endif
    #define BMC_SD_CARD_ENABLED
  #endif

  #if defined(BMC_STORAGE_PARTITION_SIZE_32K)
    #if BMC_TEENSY_RAM_SIZE < 256000
      #undef BMC_STORAGE_PARTITION_SIZE_32K
    #endif
  #endif

  #define BMC_FS_FILE_NAME "BMC.HEX"

  // pages check
  #if !defined(BMC_MAX_PAGES)
    #define BMC_MAX_PAGES 1
  #endif
  #if BMC_MAX_PAGES==0
    #undef BMC_MAX_PAGES
    #define BMC_MAX_PAGES 1
  #endif
  #if BMC_MAX_PAGES > BMC_LIMIT_MAX_PAGES
    #undef BMC_MAX_PAGES
    #define BMC_MAX_PAGES BMC_LIMIT_MAX_PAGES
  #endif

  // custom sysex check
  #if !defined(BMC_MAX_CUSTOM_SYSEX)
    #define BMC_MAX_CUSTOM_SYSEX BMC_LIMIT_MIN_CUSTOM_SYSEX
  #endif
  #if BMC_MAX_CUSTOM_SYSEX > BMC_LIMIT_MAX_CUSTOM_SYSEX
    #undef BMC_MAX_CUSTOM_SYSEX
    #define BMC_MAX_CUSTOM_SYSEX BMC_LIMIT_MAX_CUSTOM_SYSEX
  #endif

  // triggers check
  #if !defined(BMC_MAX_TRIGGERS)
    #define BMC_MAX_TRIGGERS BMC_LIMIT_MIN_TRIGGERS
  #endif
  #if BMC_MAX_TRIGGERS > BMC_LIMIT_MAX_TRIGGERS
    #undef BMC_MAX_TRIGGERS
    #define BMC_MAX_TRIGGERS BMC_LIMIT_MAX_TRIGGERS
  #endif

  // tempo to tap check
  #if !defined(BMC_MAX_TEMPO_TO_TAP)
    #define BMC_MAX_TEMPO_TO_TAP BMC_LIMIT_MIN_TEMPO_TO_TAP
  #endif
  #if BMC_MAX_TEMPO_TO_TAP > BMC_LIMIT_MAX_TEMPO_TO_TAP
    #undef BMC_MAX_TEMPO_TO_TAP
    #define BMC_MAX_TEMPO_TO_TAP BMC_LIMIT_MAX_TEMPO_TO_TAP
  #endif

  // Sketch bytes
  #if !defined(BMC_MAX_SKETCH_BYTES)
    #define BMC_MAX_SKETCH_BYTES BMC_LIMIT_MIN_SKETCH_BYTES
  #endif
  #if BMC_MAX_SKETCH_BYTES > BMC_LIMIT_MAX_SKETCH_BYTES
    #undef BMC_MAX_SKETCH_BYTES
    #define BMC_MAX_SKETCH_BYTES BMC_LIMIT_MAX_SKETCH_BYTES
  #endif

  // string library check
  #if !defined(BMC_MAX_STRING_LIBRARY)
    #define BMC_MAX_STRING_LIBRARY 0
  #endif
  #if BMC_MAX_STRING_LIBRARY > 255
    #error "The maximum number of string library items is 255"
  #endif

  // library check
  #if !defined(BMC_MAX_LIBRARY)
    #define BMC_MAX_LIBRARY BMC_LIMIT_MIN_LIBRARY
  #endif
  #if BMC_MAX_LIBRARY > BMC_LIMIT_MAX_LIBRARY
    #error "The maximum number of library items is 255"
  #endif

  // presets check
  #if !defined(BMC_MAX_PRESETS)
    #define BMC_MAX_PRESETS BMC_LIMIT_MIN_PRESETS
    #define BMC_MAX_PRESETS_PER_BANK 0
  #endif
  #if BMC_MAX_PRESETS > BMC_LIMIT_MAX_PRESETS
    #error "The maximum number of presets is 255"
  #endif

  // if there's no library then there's no presets
  #if BMC_MAX_LIBRARY == 0
    #undef BMC_MAX_PRESETS
    #define BMC_MAX_PRESETS 0
  #endif

  #if !defined(BMC_MAX_PRESETS_PER_BANK)
    #if BMC_MAX_PRESETS > 0
      #define BMC_MAX_PRESETS_PER_BANK 8
    #else
      #define BMC_MAX_PRESETS_PER_BANK 0
    #endif
  #else
    #if BMC_MAX_PRESETS_PER_BANK > 128
      #undef BMC_MAX_PRESETS_PER_BANK
      #define BMC_MAX_PRESETS_PER_BANK 128
    #endif
  #endif

  #if defined(BMC_USE_POT_TOE_SWITCH)
    #if (BMC_MAX_POTS == 0 && BMC_MAX_GLOBAL_POTS == 0)
      #undef BMC_USE_POT_TOE_SWITCH
    #endif
  #endif


  // preset items check
  #if !defined(BMC_MAX_PRESET_ITEMS) && BMC_MAX_PRESETS > 0
    #define BMC_MAX_PRESET_ITEMS BMC_LIMIT_MIN_PRESET_ITEMS
  #elif !defined(BMC_MAX_PRESET_ITEMS) && BMC_MAX_PRESETS == 0
    #define BMC_MAX_PRESET_ITEMS 0
  #endif
  #if BMC_MAX_PRESET_ITEMS == 0 && BMC_MAX_PRESETS > 0
    #undef BMC_MAX_PRESET_ITEMS
    #define BMC_MAX_PRESET_ITEMS BMC_LIMIT_MIN_PRESET_ITEMS
  #endif
  #if BMC_MAX_PRESET_ITEMS > BMC_LIMIT_MAX_PRESET_ITEMS
    #undef BMC_MAX_PRESET_ITEMS
    #define BMC_MAX_PRESET_ITEMS BMC_LIMIT_MAX_PRESET_ITEMS
  #endif


  #if !defined(BMC_MAX_SETLISTS)
    #define BMC_MAX_SETLISTS 0
  #endif

  #if !defined(BMC_MAX_SETLISTS_SONGS)
    #define BMC_MAX_SETLISTS_SONGS 0
  #endif

  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS > BMC_LIMIT_MAX_SETLIST
    #undef BMC_MAX_SETLISTS
    #define BMC_MAX_SETLISTS BMC_LIMIT_MAX_SETLIST
  #endif

  #if BMC_MAX_SETLISTS_SONGS > 0 && BMC_MAX_SETLISTS > BMC_LIMIT_MAX_SETLIST_SONGS
    #undef BMC_MAX_SETLISTS_SONGS
    #define BMC_MAX_SETLISTS_SONGS BMC_LIMIT_MAX_SETLIST_SONGS
  #endif

  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS == 0
    #error "BMC_MAX_SETLISTS_SONGS MUST BE SET"
  #endif

  // hardware check
  #if !defined(BMC_MAX_BUTTON_EVENTS) && BMC_MAX_BUTTON > 0
    #define BMC_MAX_BUTTON_EVENTS BMC_LIMIT_MIN_BUTTON_EVENTS
  #elif !defined(BMC_MAX_BUTTON_EVENTS) && BMC_MAX_BUTTON==0
    #define BMC_MAX_BUTTON_EVENTS 0
  #endif




  #if BMC_MAX_BUTTON_EVENTS > BMC_LIMIT_MAX_BUTTON_EVENTS
    #undef BMC_MAX_BUTTON_EVENTS
    #define BMC_MAX_BUTTON_EVENTS BMC_LIMIT_MAX_BUTTON_EVENTS
  #endif

  #if BMC_MAX_BUTTONS == 0 && BMC_MAX_LEDS == 0 && BMC_MAX_PIXELS == 0 && BMC_MAX_RGB_PIXELS == 0 && BMC_MAX_PWM_LEDS == 0 && BMC_MAX_POTS == 0 && BMC_MAX_ENCODERS == 0
    #if BMC_MAX_PAGES != BMC_LIMIT_MIN_PAGES
      #undef BMC_MAX_PAGES
      #define BMC_MAX_PAGES BMC_LIMIT_MIN_PAGES
    #endif
  #else
    #define BMC_HAS_HARDWARE
  #endif

  // if BMC_PIXELS_PORT is 0 we are not using pixels
  // the value of BMC_PIXELS_PORT is the hardware serial number to be used
  // if you'll be using Serial1 then BMC_PIXELS_PORT should be 1
  // if it's going to be on Serial5 then BMC_PIXELS_PORT should be 5
  #if !defined(BMC_PIXELS_PORT)
    #define BMC_PIXELS_PORT 0
  #endif
  // make sure we don't have more than 32
  //
  // || defined(BMC_MAX_RGB_PIXELS)
  //


  #if defined(BMC_MAX_PIXELS) || defined(BMC_MAX_RGB_PIXELS)
    #if (BMC_MAX_PIXELS > 0 && BMC_MAX_PIXELS <=32) || (BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_RGB_PIXELS <=32)
      #if BMC_PIXELS_PORT == 0
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
      #endif
    #else

      #if BMC_MAX_PIXELS < 0
        #undef BMC_MAX_PIXELS
        #define BMC_MAX_PIXELS 0
      #endif

      #if BMC_MAX_RGB_PIXELS < 0
        #undef BMC_MAX_RGB_PIXELS
        #define BMC_MAX_RGB_PIXELS 0
      #endif

      #if BMC_MAX_PIXELS <= 0 && BMC_MAX_RGB_PIXELS <= 0
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
      #endif

      #if BMC_MAX_PIXELS > 32
        #undef BMC_MAX_PIXELS
        #define BMC_MAX_PIXELS 32
      #endif

      #if BMC_MAX_RGB_PIXELS > 32
        #undef BMC_MAX_RGB_PIXELS
        #define BMC_MAX_RGB_PIXELS 32
      #endif

    #endif
  #else
    #undef BMC_PIXELS_PORT
    #define BMC_PIXELS_PORT 0
    #define BMC_MAX_PIXELS 0
  #endif




  #if BMC_PIXELS_PORT > 0 && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0)
    #if BMC_TEENSY_MODEL == 10
      // Teensy LC only use Serial1
      // disabled Pixels if the value is not 1
      #if BMC_PIXELS_PORT != 1
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Only Serial 1 can be used with Pixels with Teensy LC"
      #else
        #define BMC_PIXELS_PIN 1
      #endif
    #elif BMC_TEENSY_MODEL == 32
      // Teensy 3.2
      #if BMC_PIXELS_PORT > 3
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Only Serial 1, 2 and 3 can be used with Pixels with Teensy 3.2"
      #else
        #if BMC_PIXELS_PORT == 1
          #define BMC_PIXELS_PIN 1
        #elif BMC_PIXELS_PORT == 2
          #define BMC_PIXELS_PIN 10
        #elif BMC_PIXELS_PORT == 3
          #define BMC_PIXELS_PIN 8
        #endif
      #endif
    #elif BMC_TEENSY_MODEL == 35
      // 3.5
      #if BMC_PIXELS_PORT > 6
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Only Serial 1, 2, 3, 4, 5 and 6 can be used with Pixels with Teensy 3.5"
      #else
        #if BMC_PIXELS_PORT == 1
          #define BMC_PIXELS_PIN 1
        #elif BMC_PIXELS_PORT == 2
          #define BMC_PIXELS_PIN 10
        #elif BMC_PIXELS_PORT == 3
          #define BMC_PIXELS_PIN 8
        #elif BMC_PIXELS_PORT == 4
          #define BMC_PIXELS_PIN 32
        #elif BMC_PIXELS_PORT == 5
          #define BMC_PIXELS_PIN 33
        #elif BMC_PIXELS_PORT == 6
          #define BMC_PIXELS_PIN 48
        #endif
      #endif
    #elif BMC_TEENSY_MODEL == 36
      // 3.6
      #if BMC_PIXELS_PORT > 5
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Only Serial 1, 2, 3, 4 and 5 can be used with Pixels with Teensy 3.6"
      #else
        #if BMC_PIXELS_PORT == 1
          #define BMC_PIXELS_PIN 1
        #elif BMC_PIXELS_PORT == 2
          #define BMC_PIXELS_PIN 10
        #elif BMC_PIXELS_PORT == 3
          #define BMC_PIXELS_PIN 8
        #elif BMC_PIXELS_PORT == 4
          #define BMC_PIXELS_PIN 32
        #elif BMC_PIXELS_PORT == 5
          #define BMC_PIXELS_PIN 33
        #endif
      #endif
    #elif BMC_TEENSY_MODEL == 40
      // 4.00
      #if BMC_PIXELS_PORT > 7
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Invalid Pixel Serial Port"
        #error "Only Serial 1, 2, 3, 4, 5, 6 and 7 can be used with Pixels with Teensy 4.0"
      #else
        #if BMC_PIXELS_PORT == 1
          #define BMC_PIXELS_PIN 1
        #elif BMC_PIXELS_PORT == 2
          #define BMC_PIXELS_PIN 8
        #elif BMC_PIXELS_PORT == 3
          #define BMC_PIXELS_PIN 14
        #elif BMC_PIXELS_PORT == 4
          #define BMC_PIXELS_PIN 17
        #elif BMC_PIXELS_PORT == 5
          #define BMC_PIXELS_PIN 20
        #elif BMC_PIXELS_PORT == 6
          #define BMC_PIXELS_PIN 24
        #elif BMC_PIXELS_PORT == 7
          #define BMC_PIXELS_PIN 29
        #endif
      #endif
    #elif BMC_TEENSY_MODEL == 41
      // 4.1
      #if BMC_PIXELS_PORT > 7
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_PIXELS_PORT 0
        #error "Invalid Pixel Serial Port"
        #error "Only Serial 1, 2, 3, 4, 5, 6 and 7 can be used with Pixels with Teensy 4.1"
      #else
        #if BMC_PIXELS_PORT == 1
          #define BMC_PIXELS_PIN 1
        #elif BMC_PIXELS_PORT == 2
          #define BMC_PIXELS_PIN 8
        #elif BMC_PIXELS_PORT == 3
          #define BMC_PIXELS_PIN 14
        #elif BMC_PIXELS_PORT == 4
          #define BMC_PIXELS_PIN 17
        #elif BMC_PIXELS_PORT == 5
          #define BMC_PIXELS_PIN 20
        #elif BMC_PIXELS_PORT == 6
          #define BMC_PIXELS_PIN 24
        #elif BMC_PIXELS_PORT == 7
          #define BMC_PIXELS_PIN 29
        #endif
      #endif
    #endif
  #endif



  // names check
  #if !defined(BMC_NAME_LEN_BUTTONS)
    #define BMC_NAME_LEN_BUTTONS 0
  #endif
  #if BMC_NAME_LEN_BUTTONS == 1
    #undef BMC_NAME_LEN_BUTTONS
    #define BMC_NAME_LEN_BUTTONS 0
  #endif

  #if !defined(BMC_NAME_LEN_RELAYS)
    #define BMC_NAME_LEN_RELAYS 0
  #endif
  #if BMC_NAME_LEN_RELAYS == 1
    #undef BMC_NAME_LEN_RELAYS
    #define BMC_NAME_LEN_RELAYS 0
  #endif

  #if !defined(BMC_NAME_LEN_LEDS)
    #define BMC_NAME_LEN_LEDS 0
  #endif
  #if BMC_NAME_LEN_LEDS == 1
    #undef BMC_NAME_LEN_LEDS
    #define BMC_NAME_LEN_LEDS 0
  #endif

  #if !defined(BMC_NAME_LEN_POTS)
    #define BMC_NAME_LEN_POTS 0
  #endif
  #if BMC_NAME_LEN_POTS == 1
    #undef BMC_NAME_LEN_POTS
    #define BMC_NAME_LEN_POTS 0
  #endif

  #if !defined(BMC_NAME_LEN_ENCODERS)
    #define BMC_NAME_LEN_ENCODERS 0
  #endif
  #if BMC_NAME_LEN_ENCODERS == 1
    #undef BMC_NAME_LEN_ENCODERS
    #define BMC_NAME_LEN_ENCODERS 0
  #endif

  #ifdef BMC_BUTTON_DELAY_ENABLED
    #if BMC_MAX_BUTTONS == 0 || BMC_MAX_BUTTON_EVENTS < 2
      #error "Button Delay Events require buttons and at least 2 events per button"
    #endif
  #endif


  #define _____BMC_HARDWARENAMES ((uint16_t)(0x00AA * ((BMC_NAME_LEN_BUTTONS+1)*(BMC_NAME_LEN_LEDS+2)*(BMC_NAME_LEN_POTS+3)*(BMC_NAME_LEN_ENCODERS+4)*(BMC_NAME_LEN_RELAYS+5))))
  #define _____BMC_STRINGLIBRARYNAMES 0
  #define _____BMC_LIBRARYNAMES       0
  #define _____BMC_PRESETNAMES        0
  #define _____BMC_SETLISTNAMES       0
  #define _____BMC_PAGENAMES          0


// STRING LIBRARY NAMES ****************************************************
  #ifndef BMC_NAME_LEN_STRING_LIBRARY
    #define BMC_NAME_LEN_STRING_LIBRARY 0
  #endif

  #if BMC_MAX_STRING_LIBRARY > 0 && BMC_NAME_LEN_STRING_LIBRARY < 2
    #error "String library name len can not be less than 1"
  #endif

  // create the value to use within the CRC
  #if BMC_MAX_STRING_LIBRARY > 0 && BMC_NAME_LEN_STRING_LIBRARY > 1
    #undef _____BMC_STRINGLIBRARYNAMES
    #define _____BMC_STRINGLIBRARYNAMES (0x6B6B*(BMC_NAME_LEN_STRING_LIBRARY+1))
  #endif
// STRING LIBRARY NAMES ****************************************************

// LIBRARY NAMES ****************************************************
  // if BMC_NAME_LEN_LIBRARY is not defined, define it with value of 0
  #if !defined(BMC_NAME_LEN_LIBRARY)
    #define BMC_NAME_LEN_LIBRARY 0
  #endif
  // just in case check if there are no presets compiled and reset
  // this value
  #if BMC_MAX_LIBRARY == 0
    #undef BMC_NAME_LEN_LIBRARY
    #define BMC_NAME_LEN_LIBRARY 0
  #endif
  // if the value of BMC_NAME_LEN_LIBRARY is 1 throw a compile error
  // we do this to make sure the user can't recompile and have EEPROM erased
  // becuase of this
  #if BMC_NAME_LEN_LIBRARY == 1
    #error "Library Names length can NOT be 1, it must be 0 or more than 1."
  #endif
  // create the value to use within the CRC
  #if BMC_MAX_LIBRARY > 0 && BMC_NAME_LEN_LIBRARY > 1
    #undef _____BMC_LIBRARYNAMES
    #define _____BMC_LIBRARYNAMES (0x66BB*(BMC_NAME_LEN_LIBRARY+1))
  #endif
  // LIBRARY NAMES ****************************************************




  // PRESET NAMES ****************************************************
  // if BMC_NAME_LEN_PRESETS is not defined, define it with value of 0
  #if !defined(BMC_NAME_LEN_PRESETS)
    #define BMC_NAME_LEN_PRESETS 0
  #endif
  // just in case check if there are no presets compiled and reset
  // this value
  #if BMC_MAX_PRESETS == 0
    #undef BMC_NAME_LEN_PRESETS
    #define BMC_NAME_LEN_PRESETS 0
  #endif
  // if the value of BMC_NAME_LEN_PRESETS is 1 throw a compile error
  // we do this to make sure the user can't recompile and have EEPROM erased
  // becuase of this
  #if BMC_NAME_LEN_PRESETS == 1
    #error "Preset Names length can NOT be 1, it must be 0 or more than 1."
  #endif
  // create the value to use within the CRC
  #if BMC_MAX_PRESETS > 0 && BMC_NAME_LEN_PRESETS > 1
    #undef _____BMC_PRESETNAMES
    #define _____BMC_PRESETNAMES (0x77CC*(BMC_NAME_LEN_PRESETS+1))
  #endif
  // PRESET NAMES ****************************************************


  // SETLIST NAMES ****************************************************
  // if BMC_NAME_LEN_SETLISTS is not defined, define it with value of 0
  #if !defined(BMC_NAME_LEN_SETLISTS)
    #define BMC_NAME_LEN_SETLISTS 0
  #endif
  // just in case check if there are no presets compiled and reset
  // this value
  #if BMC_MAX_SETLISTS == 0
    #undef BMC_NAME_LEN_SETLISTS
    #define BMC_NAME_LEN_SETLISTS 0
  #endif
  // if the value of BMC_NAME_LEN_SETLISTS is 1 throw a compile error
  // we do this to make sure the user can't recompile and have EEPROM erased
  // becuase of this
  #if BMC_NAME_LEN_SETLISTS == 1
    #error "Preset Names length can NOT be 1, it must be 0 or more than 1."
  #endif
  // create the value to use within the CRC
  #if BMC_MAX_SETLISTS > 0 && BMC_NAME_LEN_SETLISTS > 1
    #undef _____BMC_SETLISTNAMES
    #define _____BMC_SETLISTNAMES (0x77CC*(BMC_NAME_LEN_SETLISTS+1))
  #endif
  // SETLIST NAMES ****************************************************



  #if !defined(BMC_DEFAUL_DEVICE_ID)
    #define BMC_DEFAUL_DEVICE_ID 0
  #else
    #if BMC_DEFAUL_DEVICE_ID > 15
      #undef BMC_DEFAUL_DEVICE_ID
      #define BMC_DEFAUL_DEVICE_ID 0
    #endif
  #endif

  // as of right now no support for the clicktrack on Teensy 4.0
  // since it's hardcoded to use DAC on T3.2/T3.6
  #if BMC_TEENSY_MODEL == 40 || BMC_TEENSY_MODEL == 41
    #if defined(BMC_USE_CLICK_TRACK)
      #undef BMC_USE_CLICK_TRACK
    #endif
  #endif



  // PAGE NAMES ****************************************************
  // if BMC_NAME_LEN_PAGES is not defined, define it with value of 0
  #if !defined(BMC_NAME_LEN_PAGES)
    #define BMC_NAME_LEN_PAGES 0
  #endif
  // if the value of BMC_NAME_LEN_PAGES is 1 throw a compile error
  // we do this to make sure the user can't recompile and have EEPROM erased
  // becuase of this
  #if BMC_NAME_LEN_PAGES == 1
    #error "Page Names length can NOT be 1, it must be 0 or more than 1."
  #endif
  // create the value to use within the CRC
  #if BMC_NAME_LEN_PAGES > 1
    #undef _____BMC_PAGENAMES
    #define _____BMC_PAGENAMES (0x88DD*(BMC_NAME_LEN_PAGES+1))
  #endif
  // PAGE NAMES ****************************************************


  #define BMC_TOTAL_LEDS (BMC_MAX_LEDS+BMC_MAX_PWM_LEDS+BMC_MAX_GLOBAL_LEDS)
  #define BMC_TOTAL_PIXELS (BMC_MAX_PIXELS+BMC_MAX_RGB_PIXELS)

#if defined(BMC_USE_POT_TOE_SWITCH)
  #define _____BMC_POT_TOE_SWITCH 15
#else
  #define _____BMC_POT_TOE_SWITCH 0
#endif

  // BMC_MAX_LED_TEST_DELAY defines the delay between led's blinking when
  // they are tested by the editor or at launch, the idea is that at launch
  // the test of alls LED and PIXELS should not exceed more than 4 seconds.
  // Each LED and PIXEL will turn on and off 3 times when tested, when it turns on
  // it will be delayed by BMC_MAX_LED_TEST_DELAY then turn off and delayed again
  // by the same value and this happens 3 times per LED/PIXEL.


#if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) >= 12
  #define BMC_MAX_LED_TEST_DELAY ((4000/(BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS))/6)
#else
  #define BMC_MAX_LED_TEST_DELAY 50
#endif
  #define _____BMC_GLOBAL_HARDWARE ((BMC_MAX_GLOBAL_LEDS*11)+(BMC_MAX_GLOBAL_BUTTONS*22)+(BMC_MAX_GLOBAL_ENCODERS*33)+(BMC_MAX_GLOBAL_POTS*44)+(_____BMC_POT_TOE_SWITCH*55))

  // Create a CRC based on the current build
  #define _____BMC_NAMES (uint16_t)((_____BMC_HARDWARENAMES) + (_____BMC_PRESETNAMES) + (_____BMC_SETLISTNAMES) + (_____BMC_LIBRARYNAMES) + (_____BMC_STRINGLIBRARYNAMES))
  #define _____BMC_PAGES (uint16_t)((((BMC_MAX_BUTTONS*11)+(BMC_MAX_LEDS*22)+(BMC_MAX_PWM_LEDS*33)+(BMC_MAX_POTS*55)+(BMC_MAX_ENCODERS*66)+(BMC_MAX_BUTTON_EVENTS*77)+(BMC_MAX_PIXELS*88)+(BMC_MAX_RGB_PIXELS*99)) * BMC_MAX_PAGES))
  #define _____BMC_GLOBAL (uint16_t)((_____BMC_GLOBAL_HARDWARE)+(BMC_MAX_CUSTOM_SYSEX*11) + (BMC_MAX_TRIGGERS*22) + (BMC_MAX_TEMPO_TO_TAP*33) + (BMC_MAX_SKETCH_BYTES*44) + (BMC_MAX_STRING_LIBRARY*22) + (BMC_MAX_LIBRARY*55)+ (BMC_MAX_PRESETS*66) + (BMC_MAX_PRESET_ITEMS*77) + (BMC_MAX_SETLISTS*88) + (BMC_MAX_SETLISTS_SONGS*99))
  #define BMC_CRC (uint16_t)((((_____BMC_NAMES)+(_____BMC_GLOBAL)+(_____BMC_NAMES)+(sizeof(bmcStore))) & 0xFFFF))

#endif
