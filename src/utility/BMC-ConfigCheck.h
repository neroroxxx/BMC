/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_CONFIG_CHECK_H
#define BMC_CONFIG_CHECK_H
#include "utility/BMC-ConfigCheckPins.h"

  // disable the ILI display on teensy 3.2 as it will not fit
  #if BMC_TEENSY_MODEL == 32 && BMC_MAX_ILI9341_BLOCKS > 0
    #error "ILI NO SUPPORTED ON TEENSY 3.2, NOT ENOUGH FLASH"
  #endif

  // the min/max values that can ever be used
  // the max for everything is 255 this is to be able to fit lengths inside
  // 8-bit unsigned integers, specially when sending these values out thru midi

  #define BMC_LIMIT_MIN_LIBRARY 0
  #define BMC_LIMIT_MAX_LIBRARY 512

  #define BMC_LIMIT_MIN_PRESETS 0
  #define BMC_LIMIT_MAX_PRESETS 512

  #define BMC_LIMIT_MIN_PRESET_ITEMS 1
  #define BMC_LIMIT_MAX_PRESET_ITEMS 16

  #define BMC_LIMIT_MIN_SETLIST 0
  #define BMC_LIMIT_MAX_SETLIST 32

  #define BMC_LIMIT_MIN_SETLIST_SONGS 0
  #define BMC_LIMIT_MAX_SETLIST_SONGS 32

  #define BMC_LIMIT_MIN_SETLIST_SONGS_LIBRARY 0
  #define BMC_LIMIT_MAX_SETLIST_SONGS_LIBRARY 512

  #define BMC_LIMIT_MIN_SETLIST_SONGS_PARTS 0
  #define BMC_LIMIT_MAX_SETLIST_SONGS_PARTS 16

  #define BMC_LIMIT_MIN_CUSTOM_SYSEX 0
  #define BMC_LIMIT_MAX_CUSTOM_SYSEX 127

  #define BMC_LIMIT_MIN_SKETCH_BYTES 0
  #define BMC_LIMIT_MAX_SKETCH_BYTES 32

  #define BMC_LIMIT_MIN_TRIGGERS 0
  #define BMC_LIMIT_MAX_TRIGGERS 127

  #define BMC_LIMIT_MIN_TIMED_EVENTS 0
  #define BMC_LIMIT_MAX_TIMED_EVENTS 127

  #define BMC_LIMIT_MIN_TEMPO_TO_TAP 0
  #define BMC_LIMIT_MAX_TEMPO_TO_TAP 32

  #define BMC_LIMIT_MIN_RELAYS 0
  #define BMC_LIMIT_MAX_RELAYS 16

  #define BMC_LIMIT_MIN_LAYERS 1
  #define BMC_LIMIT_MAX_LAYERS 255

  #define BMC_LIMIT_MIN_BUTTON_EVENTS 1
  #define BMC_LIMIT_MAX_BUTTON_EVENTS 8

  #define BMC_LIMIT_MAX_PIXEL_PROGRAMS 32

  #if !defined(BMC_MAX_LFO)
    #define BMC_MAX_LFO 1
  #endif

  #if BMC_MAX_LFO > 2
    #undef BMC_MAX_LFO
    #define BMC_MAX_LFO 2
  #endif

  #if !defined(BMC_MAX_EVENTS_LIBRARY)
    #define BMC_MAX_EVENTS_LIBRARY 8
  #endif

  #if BMC_MAX_EVENTS_LIBRARY < 8
    #under BMC_MAX_EVENTS_LIBRARY
    #define BMC_MAX_EVENTS_LIBRARY 8
  #elif BMC_MAX_EVENTS_LIBRARY > 512
    #under BMC_MAX_EVENTS_LIBRARY
    #define BMC_MAX_EVENTS_LIBRARY 512
  #endif

  // NAMES LIBRARY STR LENGTH
  #if !defined(BMC_MAX_NAMES_LIBRARY)
    #define BMC_MAX_NAMES_LIBRARY 8
  #endif

  #if BMC_MAX_NAMES_LIBRARY < 8
    #under BMC_MAX_NAMES_LIBRARY
    #define BMC_MAX_NAMES_LIBRARY 8
  #elif BMC_MAX_NAMES_LIBRARY > 512
    #under BMC_MAX_NAMES_LIBRARY
    #define BMC_MAX_NAMES_LIBRARY 512
  #endif

  // NAMES LIBRARY STR LENGTH
  #if !defined(BMC_MAX_NAMES_LENGTH)
    #define BMC_MAX_NAMES_LENGTH 9
  #endif

  #if BMC_MAX_NAMES_LENGTH < 9
    #under BMC_MAX_NAMES_LENGTH
    #define BMC_MAX_NAMES_LENGTH 9
  #elif BMC_MAX_NAMES_LENGTH > 33
    #under BMC_MAX_NAMES_LENGTH
    #define BMC_MAX_NAMES_LENGTH 33
  #endif

  #if BMC_MAX_EVENTS_LIBRARY > 254
    typedef uint16_t bmcEvent_t;
  #else
    typedef uint8_t bmcEvent_t;
  #endif

  #if BMC_MAX_NAMES_LIBRARY > 254
    typedef uint16_t bmcName_t;
  #else
    typedef uint8_t bmcName_t;
  #endif

  #ifndef BMC_MAX_LAYER_EVENTS
    #define BMC_MAX_LAYER_EVENTS 1
  #endif

  #if BMC_MAX_LAYER_EVENTS < 1
    #undef BMC_MAX_LAYER_EVENTS
    #define BMC_MAX_LAYER_EVENTS 1
  #endif

  #if BMC_MAX_LAYER_EVENTS > 8
    #undef BMC_MAX_LAYER_EVENTS
    #define BMC_MAX_LAYER_EVENTS 8
  #endif


  #ifdef BMC_MAX_PRESETS
    #undef BMC_MAX_PRESETS
    #define BMC_MAX_PRESETS 0
  #endif

  #ifndef BMC_MAX_PRESET_BANKS
    #define BMC_MAX_PRESET_BANKS 0
  #endif

  #ifndef BMC_MAX_PRESETS_PER_BANK
    #define BMC_MAX_PRESETS_PER_BANK 0
  #endif

  #ifndef BMC_MAX_PRESET_ITEMS
    #define BMC_MAX_PRESET_ITEMS 0
  #endif

  #if BMC_MAX_PRESET_ITEMS < 0 || BMC_MAX_PRESET_ITEMS > 16
    #error "BMC_MAX_PRESET_ITEMS not properly set"
  #endif

  #if BMC_MAX_PRESET_BANKS == 0 || BMC_MAX_PRESETS_PER_BANK == 0
    //#error "BMC_MAX_PRESET_BANKS / BMC_MAX_PRESETS_PER_BANK not properly set"
  #endif

  #if BMC_MAX_PRESET_BANKS < 0 || BMC_MAX_PRESET_BANKS > 32
    #error "BMC_MAX_PRESET_BANKS not properly set"
  #endif

  #if BMC_MAX_PRESETS_PER_BANK < 0 || BMC_MAX_PRESETS_PER_BANK > 32
    #error "BMC_MAX_PRESETS_PER_BANK not properly set"
  #endif



  #if BMC_MAX_PRESETS_PER_BANK > 0
    #if BMC_MAX_PRESETS_PER_BANK == 4
      #define BMC_PRESET_BANK_MASK 2
    #elif BMC_MAX_PRESETS_PER_BANK == 8
      #define BMC_PRESET_BANK_MASK 3
    #elif BMC_MAX_PRESETS_PER_BANK == 16
      #define BMC_PRESET_BANK_MASK 4
    #elif BMC_MAX_PRESETS_PER_BANK == 32
      #define BMC_PRESET_BANK_MASK 5
    #else
      #error "BMC_MAX_PRESETS_PER_BANK must be 4, 8, 16 or 32"
    #endif
  #endif


  #if (BMC_MAX_PRESET_BANKS > 0 && BMC_MAX_PRESETS_PER_BANK > 0 && BMC_MAX_PRESET_ITEMS > 0)
    #undef BMC_MAX_PRESETS
    #define BMC_MAX_PRESETS (BMC_MAX_PRESET_BANKS * BMC_MAX_PRESETS_PER_BANK)
  #else
    #undef BMC_MAX_PRESETS
    #undef BMC_MAX_PRESET_BANKS
    #undef BMC_MAX_PRESETS_PER_BANK
    #undef BMC_MAX_PRESET_ITEMS
    #define BMC_MAX_PRESETS 0
    #define BMC_MAX_PRESET_BANKS 0
    #define BMC_MAX_PRESETS_PER_BANK 0
    #define BMC_MAX_PRESET_ITEMS 0
  #endif


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

  #ifndef BMC_MAX_MUX_OUT
    #define BMC_MAX_MUX_OUT 0
  #endif
  #if BMC_MAX_MUX_OUT > 64
    #error "BMC supports up to 64 Mux Out Pins"
  #endif


  #ifndef BMC_MAX_MUX_GPIO
    #define BMC_MAX_MUX_GPIO 0
  #endif
  #if BMC_MAX_MUX_GPIO > 64
    #error "BMC supports up to 64 Mux GPIO Pins"
  #endif

  #ifndef BMC_MAX_MUX_IN_ANALOG
    #define BMC_MAX_MUX_IN_ANALOG 0
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 127
    #error "BMC supports up to 127 Analog Mux Pins"
  #endif


  #ifndef BMC_MAX_MUX_IN_KEYPAD
    #define BMC_MAX_MUX_IN_KEYPAD 0
  #endif
  #if BMC_MAX_MUX_IN_KEYPAD > 64
    #error "BMC supports up to 64 Mux In Keypad Pins"
  #endif

  #if (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_KEYPAD)>64
    #error "BMC supports a maximum of 64 Mux Digital Pins, that inclues a sum of BMC_MAX_MUX_GPIO, BMC_MAX_MUX_IN, BMC_MAX_MUX_OUT & BMC_MAX_MUX_IN_KEYPAD"
  #endif

  #if (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG)>127
    #error "BMC supports a maximum of 127 Mux Pins total, that inclues a sum of BMC_MAX_MUX_GPIO, BMC_MAX_MUX_IN, BMC_MAX_MUX_OUT & BMC_MAX_MUX_IN_ANALOG"
  #endif

  #if BMC_MAX_MUX_IN > 0 && (BMC_MAX_BUTTONS==0 && BMC_MAX_ENCODERS==0 && BMC_MAX_GLOBAL_BUTTONS==0 && BMC_MAX_GLOBAL_ENCODERS==0)
    #undef BMC_MAX_MUX_IN
    #define BMC_MAX_MUX_IN 0
  #endif

  #if BMC_MAX_MUX_OUT > 0 && (BMC_MAX_LEDS==0 && BMC_MAX_GLOBAL_LEDS==0 && BMC_MAX_BI_LEDS==0 && BMC_MAX_GLOBAL_BI_LEDS==0 && BMC_MAX_TRI_LEDS==0 && BMC_MAX_GLOBAL_TRI_LEDS==0)
    #undef BMC_MAX_MUX_OUT
    #define BMC_MAX_MUX_OUT 0
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

  #define BMC_TOTAL_MUX_PINS (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG)

  #if (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG) > 0
    #define BMC_MUX_AVAILABLE
  #endif

  #if defined(BMC_USE_TIME) && !defined(BMC_TIME_ADJUST)
    #define BMC_TIME_ADJUST 20
  #endif

  // device name
  #if !defined(BMC_DEVICE_NAME)
    #define BMC_DEVICE_NAME "BMC"
  #endif

  
  /*
  availablePortsData[availablePorts++] = BMC_MIDI_PORT_USB_BIT;
		#if defined(BMC_MIDI_SERIAL_A_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_A_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_B_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_B_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_C_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_C_BIT;
    #endif
    #if defined(BMC_MIDI_SERIAL_D_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_SERIAL_D_BIT;
    #endif
		#if defined(BMC_USB_HOST_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_HOST_BIT;
    #endif
		#if defined(BMC_MIDI_BLE_ENABLED)
      availablePortsData[availablePorts++] = BMC_MIDI_PORT_BLE_BIT;
    #endif
  */

  #if defined(BMC_USE_MIDI_SERIAL_A) && defined(BMC_MIDI_SERIAL_IO_A)
    #define BMC_MIDI_SERIAL_A_ENABLED
    #define _BMC_MIDISERIAL_A_ 1
  #else
    #define _BMC_MIDISERIAL_A_ 0
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_B) && defined(BMC_MIDI_SERIAL_IO_B)
    #define BMC_MIDI_SERIAL_B_ENABLED
    #define _BMC_MIDISERIAL_B_ 1
  #else
    #define _BMC_MIDISERIAL_B_ 0
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_C) && defined(BMC_MIDI_SERIAL_IO_C)
    #define BMC_MIDI_SERIAL_C_ENABLED
    #define _BMC_MIDISERIAL_C_ 1
  #else
    #define _BMC_MIDISERIAL_C_ 0
  #endif
  #if defined(BMC_USE_MIDI_SERIAL_D) && defined(BMC_MIDI_SERIAL_IO_D) && BMC_TEENSY_TOTAL_SERIAL_PORTS > 3
    #define BMC_MIDI_SERIAL_D_ENABLED
    #define _BMC_MIDISERIAL_D_ 1
  #else
    #define _BMC_MIDISERIAL_D_ 0
  #endif

  #if defined(BMC_MIDI_SERIAL_A_ENABLED) || defined(BMC_MIDI_SERIAL_B_ENABLED) || defined(BMC_MIDI_SERIAL_C_ENABLED) || defined(BMC_MIDI_SERIAL_D_ENABLED)
    #define BMC_HAS_SERIAL_MIDI
  #endif

  #if defined(BMC_USE_USB_HOST) && BMC_TEENSY_HAS_USB_HOST == true
    #define BMC_USB_HOST_ENABLED
    #define _BMC_MIDIHOST_ 1
  #else
    #define _BMC_MIDIHOST_ 0
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
    #define _BMC_MIDIBLE_ 1
  #else
    #define _BMC_MIDIBLE_ 0
  #endif

  #define BMC_TOTAL_AVAILABLE_PORTS (1+_BMC_MIDISERIAL_A_+_BMC_MIDISERIAL_B_+_BMC_MIDISERIAL_C_+_BMC_MIDISERIAL_D_+_BMC_MIDIHOST_+_BMC_MIDIBLE_)

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

  // layers check
  #if !defined(BMC_MAX_LAYERS)
    #define BMC_MAX_LAYERS 1
  #endif
  #if BMC_MAX_LAYERS==0
    #undef BMC_MAX_LAYERS
    #define BMC_MAX_LAYERS 1
  #endif
  #if BMC_MAX_LAYERS > BMC_LIMIT_MAX_LAYERS
    #undef BMC_MAX_LAYERS
    #define BMC_MAX_LAYERS BMC_LIMIT_MAX_LAYERS
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

  #if !defined(BMC_MAX_SETLISTS)
    #define BMC_MAX_SETLISTS 0
  #endif

  #if !defined(BMC_MAX_SETLISTS_SONGS)
    #define BMC_MAX_SETLISTS_SONGS 0
  #endif

  #if !defined(BMC_MAX_SETLISTS_SONGS_LIBRARY)
    #define BMC_MAX_SETLISTS_SONGS_LIBRARY 0
  #endif

  #if !defined(BMC_MAX_SETLISTS_SONG_PARTS)
    #define BMC_MAX_SETLISTS_SONG_PARTS 0
  #endif








  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS > BMC_LIMIT_MAX_SETLIST
    #undef BMC_MAX_SETLISTS
    #define BMC_MAX_SETLISTS BMC_LIMIT_MAX_SETLIST
  #endif

  #if BMC_MAX_SETLISTS_SONGS > 0 && BMC_MAX_SETLISTS_SONGS > BMC_LIMIT_MAX_SETLIST_SONGS
    #undef BMC_MAX_SETLISTS_SONGS
    #define BMC_MAX_SETLISTS_SONGS BMC_LIMIT_MAX_SETLIST_SONGS
  #endif

  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS == 0
    #error "BMC_MAX_SETLISTS_SONGS MUST BE SET"
  #endif




  #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0 && BMC_MAX_SETLISTS_SONGS_LIBRARY > BMC_LIMIT_MAX_SETLIST_SONGS_LIBRARY
    #undef BMC_MAX_SETLISTS_SONGS_LIBRARY
    #define BMC_MAX_SETLISTS_SONGS_LIBRARY BMC_LIMIT_MAX_SETLIST_SONGS_LIBRARY
  #endif

  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS_LIBRARY == 0
    #error "BMC_MAX_SETLISTS_SONGS_LIBRARY MUST BE SET"
  #endif

  #if BMC_MAX_SETLISTS_SONG_PARTS > 0 && BMC_MAX_SETLISTS_SONG_PARTS > BMC_LIMIT_MAX_SETLIST_SONGS_PARTS
    #undef BMC_MAX_SETLISTS_SONG_PARTS
    #define BMC_MAX_SETLISTS_SONG_PARTS BMC_LIMIT_MAX_SETLIST_SONGS_PARTS
  #endif

  #if BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONG_PARTS == 0
    #error "BMC_MAX_SETLISTS_SONG_PARTS MUST BE SET"
  #endif


  // timed events check
  #if !defined(BMC_MAX_TIMED_EVENTS)
    #define BMC_MAX_TIMED_EVENTS BMC_LIMIT_MIN_TIMED_EVENTS
  #endif
  #if BMC_MAX_TIMED_EVENTS > BMC_LIMIT_MAX_TIMED_EVENTS
    #undef BMC_MAX_TIMED_EVENTS
    #define BMC_MAX_TIMED_EVENTS BMC_LIMIT_MAX_TIMED_EVENTS
  #endif


  // hardware check
  #if !defined(BMC_MAX_BUTTON_EVENTS) && (BMC_MAX_BUTTON > 0 || BMC_MAX_GLOBAL_BUTTONS > 0)
    #define BMC_MAX_BUTTON_EVENTS BMC_LIMIT_MIN_BUTTON_EVENTS
  #elif !defined(BMC_MAX_BUTTON_EVENTS) && (BMC_MAX_BUTTON==0 && BMC_MAX_GLOBAL_BUTTONS==0)
    #define BMC_MAX_BUTTON_EVENTS 0
  #endif

  #if BMC_MAX_BUTTON_EVENTS > BMC_LIMIT_MAX_BUTTON_EVENTS
    #undef BMC_MAX_BUTTON_EVENTS
    #define BMC_MAX_BUTTON_EVENTS BMC_LIMIT_MAX_BUTTON_EVENTS
  #endif

  #if BMC_MAX_BUTTONS == 0 && BMC_MAX_LEDS == 0 && BMC_MAX_PIXELS == 0 && BMC_MAX_RGB_PIXELS == 0 && BMC_MAX_POTS == 0 && BMC_MAX_ENCODERS == 0 && BMC_MAX_OLED == 0 && BMC_MAX_ILI9341_BLOCKS == 0 && BMC_MAX_BI_LEDS == 0 && BMC_MAX_GLOBAL_BI_LEDS == 0 && BMC_MAX_TRI_LEDS == 0 && BMC_MAX_GLOBAL_TRI_LEDS == 0 && BMC_MAX_PIXEL_STRIP == 0
    #if BMC_MAX_LAYERS != BMC_LIMIT_MIN_LAYERS
      #undef BMC_MAX_LAYERS
      #define BMC_MAX_LAYERS BMC_LIMIT_MIN_LAYERS
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


  #if defined(BMC_MAX_PIXELS) || defined(BMC_MAX_RGB_PIXELS) || defined(BMC_MAX_GLOBAL_PIXELS) || defined(BMC_MAX_GLOBAL_RGB_PIXELS) || defined(BMC_MAX_PIXEL_STRIP)
    #if (BMC_MAX_PIXELS > 0 && BMC_MAX_PIXELS <=128) || (BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_RGB_PIXELS <=128) || (BMC_MAX_PIXEL_STRIP>0 && BMC_MAX_PIXEL_STRIP<=64)
      #if BMC_PIXELS_PORT == 0
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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

      #if BMC_MAX_GLOBAL_PIXELS < 0
        #undef BMC_MAX_PIXELS
        #define BMC_MAX_PIXELS 0
      #endif

      #if BMC_MAX_GLOBAL_RGB_PIXELS < 0
        #undef BMC_MAX_RGB_PIXELS
        #define BMC_MAX_RGB_PIXELS 0
      #endif

      #if BMC_MAX_PIXEL_STRIP < 0
        #undef BMC_MAX_PIXEL_STRIP
        #define BMC_MAX_PIXEL_STRIP 0
      #endif

      

      #if BMC_MAX_PIXELS <= 0 && BMC_MAX_RGB_PIXELS <= 0 && BMC_MAX_GLOBAL_PIXELS <= 0 && BMC_MAX_GLOBAL_RGB_PIXELS <= 0 && BMC_MAX_PIXEL_STRIP <= 0
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
        #define BMC_PIXELS_PORT 0
      #endif

      #if BMC_MAX_PIXELS > 128
        #undef BMC_MAX_PIXELS
        #define BMC_MAX_PIXELS 128
      #endif

      #if BMC_MAX_RGB_PIXELS > 128
        #undef BMC_MAX_RGB_PIXELS
        #define BMC_MAX_RGB_PIXELS 128
      #endif

      #if BMC_MAX_GLOBAL_PIXELS > 128
        #undef BMC_MAX_GLOBAL_PIXELS
        #define BMC_MAX_GLOBAL_PIXELS 128
      #endif

      #if BMC_MAX_GLOBAL_RGB_PIXELS > 128
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #define BMC_MAX_GLOBAL_RGB_PIXELS 128
      #endif

      #if BMC_MAX_PIXEL_STRIP > 64
        #undef BMC_MAX_PIXEL_STRIP
        #define BMC_MAX_PIXEL_STRIP 64
      #endif

    #endif
  #else
    #undef BMC_PIXELS_PORT
    #error "%%%%%%%%%%%%%%%%%%%%%"
    #define BMC_PIXELS_PORT 0
  #endif




  #if BMC_PIXELS_PORT > 0 && (BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0 || BMC_MAX_GLOBAL_PIXELS > 0 || BMC_MAX_GLOBAL_RGB_PIXELS > 0 || BMC_MAX_PIXEL_STRIP > 0)
    #if BMC_TEENSY_MODEL == 10
      // Teensy LC only use Serial1
      // disabled Pixels if the value is not 1
      #if BMC_PIXELS_PORT != 1
        #undef BMC_MAX_PIXELS
        #undef BMC_MAX_RGB_PIXELS
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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
      #undef BMC_MAX_GLOBAL_PIXELS
      #undef BMC_MAX_GLOBAL_RGB_PIXELS
      #undef BMC_MAX_PIXEL_STRIP
      #undef BMC_PIXELS_PORT
      #define BMC_MAX_PIXELS 0
      #define BMC_MAX_RGB_PIXELS 0
      #define BMC_MAX_GLOBAL_PIXELS 0
      #define BMC_MAX_GLOBAL_RGB_PIXELS 0
      #define BMC_MAX_PIXEL_STRIP 0
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
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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
        #undef BMC_MAX_GLOBAL_PIXELS
        #undef BMC_MAX_GLOBAL_RGB_PIXELS
        #undef BMC_MAX_PIXEL_STRIP
        #undef BMC_PIXELS_PORT
        #define BMC_MAX_PIXELS 0
        #define BMC_MAX_RGB_PIXELS 0
        #define BMC_MAX_GLOBAL_PIXELS 0
        #define BMC_MAX_GLOBAL_RGB_PIXELS 0
        #define BMC_MAX_PIXEL_STRIP 0
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

  #if !defined(BMC_MAX_PIXEL_PROGRAMS)
    #define BMC_MAX_PIXEL_PROGRAMS 0
  #endif

  #if BMC_MAX_PIXEL_PROGRAMS > 0
    #if BMC_MAX_PIXEL_PROGRAMS > BMC_LIMIT_MAX_PIXEL_PROGRAMS
      #error "You can not have more than 32 Pixel Programs"
    #endif
  #endif

  #if BMC_MAX_PIXELS == 0 && BMC_MAX_GLOBAL_PIXELS == 0 && BMC_MAX_PIXEL_STRIP == 0
    #undef BMC_MAX_PIXEL_PROGRAMS
    #define BMC_MAX_PIXEL_PROGRAMS 0
  #endif


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
  #if BMC_TEENSY_MODEL > 36
    #if defined(BMC_USE_CLICK_TRACK)
      #undef BMC_USE_CLICK_TRACK
    #endif
  #endif

  

  #define BMC_TOTAL_LEDS (BMC_MAX_LEDS+BMC_MAX_GLOBAL_LEDS+BMC_MAX_BI_LEDS+BMC_MAX_GLOBAL_BI_LEDS+BMC_MAX_TRI_LEDS+BMC_MAX_GLOBAL_TRI_LEDS)
  #define BMC_TOTAL_PIXELS (BMC_MAX_PIXELS+BMC_MAX_RGB_PIXELS+BMC_MAX_GLOBAL_PIXELS+BMC_MAX_GLOBAL_RGB_PIXELS+BMC_MAX_PIXEL_STRIP)

  #if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS)>0
    #define BMC_HAS_LEDS
  #endif
  // typedef for Presets and library
  // this is used in order to increase the maximum from 255 to up to 999
  // this is for both presets and library.
  // if there are more than 255 presets then we'll need a 16-bit type to hold
  // the value, same applies to the library
  #if BMC_MAX_PRESETS > 254
    typedef uint16_t bmcPreset_t;
  #else
    typedef uint8_t bmcPreset_t;
  #endif

  #define BMC_TOTAL_POTS_AUX_JACKS (BMC_MAX_POTS + BMC_MAX_GLOBAL_POTS + BMC_MAX_AUX_JACKS)

  #if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
    #define BMC_HAS_ENCODERS
  #endif

  #if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
    #define BMC_HAS_BUTTONS
  #endif

  #if defined(BMC_HAS_ENCODERS) && defined(BMC_HAS_BUTTONS)
    #define BMC_ENABLE_ENCODER_BUTTON_FILTERING
  #endif

  #if !defined(BMC_ENCODER_BUTTON_DEBOUNCE_TIME)
    #define BMC_ENCODER_BUTTON_DEBOUNCE_TIME 50
  #endif

#if defined(BMC_HAS_DISPLAY)
  #undef BMC_HAS_DISPLAY
#endif

#if BMC_MAX_OLED > 0 || BMC_MAX_ILI9341_BLOCKS > 0
  #define BMC_HAS_DISPLAY
#endif

#ifndef BMC_SSD1306_BLACK
  #define BMC_SSD1306_BLACK               0    ///< Draw 'off' pixels
  #define BMC_SSD1306_WHITE               1    ///< Draw 'on' pixels
  #define BMC_SSD1306_INVERSE             2    ///< Invert pixels
#endif

#ifndef BMC_OLED_BLACK
  #define BMC_OLED_BLACK               0    ///< Draw 'off' pixels
  #define BMC_OLED_WHITE               1    ///< Draw 'on' pixels
  #define BMC_OLED_INVERSE             2    ///< Invert pixels
#endif

#if defined(BMC_USE_DAW_LC) || defined(BMC_USE_BEATBUDDY) || defined(BMC_USE_HELIX) || defined(BMC_USE_FAS) || defined(BMC_USE_KEMPER)
  #define BMC_USE_SYNC
#endif



#if BMC_MAX_ILI9341_BLOCKS > 0

#if !defined(BMC_USER_DISABLED_OBE)
  #define BMC_USE_ON_BOARD_EDITOR
#endif

// Teensy 3.2 doesn't have enough flash to support the on board editor
#if BMC_TEENSY_MODEL == 32 && defined(BMC_USE_ON_BOARD_EDITOR)
  #undef BMC_USE_ON_BOARD_EDITOR
#endif

#if defined(BMC_USE_ON_BOARD_EDITOR) && defined(BMC_ILI_TOUCH_ENABLED)
  #define BMC_HAS_TOUCH_SCREEN
#endif

#if !defined(BMC_TFT_TYPE)
  #define BMC_TFT_TYPE 0
#endif

#if BMC_TFT_TYPE == 0 || BMC_TFT_TYPE == 1
  #define BMC_TFT_SIZE 1
#elif BMC_TFT_TYPE == 2 || BMC_TFT_TYPE == 3
  #define BMC_TFT_SIZE 2
#endif

// BMC_TFT_TYPE == 0  >>> 2.8" (320x240 ILI9341)
// BMC_TFT_TYPE == 1  >>> 3.2" (320x240 ILI9341)
// BMC_TFT_TYPE == 2  >>> 3.5" (480x320 ILI9488)
// BMC_TFT_TYPE == 3  >>> 4.0" (480x320 ILI9488)
#if BMC_TFT_SIZE == 1
  #define BMC_TFT_WIDTH 320
  #define BMC_TFT_HEIGHT 240
  #define BMC_TFT ILI9341_t3
#else
  #define BMC_TFT_WIDTH 480
  #define BMC_TFT_HEIGHT 320
  #define BMC_TFT ILI9488_t3
#endif

#endif


  // BMC_MAX_LED_TEST_DELAY defines the delay between led's blinking when
  // they are tested by the editor or at launch, the idea is that at launch
  // the test of alls LED and PIXELS should not exceed more than 4 seconds.
  // Each LED and PIXEL will turn on and off 3 times when tested, when it turns on
  // it will be delayed by BMC_MAX_LED_TEST_DELAY then turn off and delayed again
  // by the same value and this happens 3 times per LED/PIXEL.


  // #define BMC_MAX_LED_TEST_DELAY 15
  #define BMC_MAX_LED_TEST_DELAY 50

  

  #define _____BMC_GLOBAL_HARDWARE ((BMC_MAX_GLOBAL_LEDS*11)+(BMC_MAX_GLOBAL_BI_LEDS*12)+(BMC_MAX_GLOBAL_BI_LEDS*13)+(BMC_MAX_GLOBAL_BUTTONS*22)+(BMC_MAX_GLOBAL_ENCODERS*33)+(BMC_MAX_GLOBAL_POTS*44) +(BMC_MAX_GLOBAL_MAGIC_ENCODERS*55))

  // Create a CRC based on the current build
  #define _____BMC_LAYERS (uint16_t)((((BMC_MAX_LAYER_EVENTS*3)+(BMC_MAX_BUTTONS*11)+(BMC_MAX_LEDS*22)+(BMC_MAX_BI_LEDS*23)+(BMC_MAX_TRI_LEDS*24)+(BMC_MAX_POTS*55)+(BMC_MAX_ENCODERS*66)+(BMC_MAX_BUTTON_EVENTS*77)+(BMC_MAX_PIXELS*88)+(BMC_MAX_RGB_PIXELS*99)+(BMC_MAX_PIXEL_STRIP*49)+(BMC_MAX_GLOBAL_MAGIC_ENCODERS*37)) * BMC_MAX_LAYERS))
  #define _____BMC_GLOBAL (uint16_t)((_____BMC_GLOBAL_HARDWARE)+(BMC_MAX_CUSTOM_SYSEX*11) + (BMC_MAX_TRIGGERS*22) + (BMC_MAX_TEMPO_TO_TAP*33) + (BMC_MAX_SKETCH_BYTES*44) + (BMC_MAX_PRESETS*66) + (BMC_MAX_PRESET_ITEMS*77) + (BMC_MAX_SETLISTS*88) + (BMC_MAX_SETLISTS_SONGS*99) + (BMC_MAX_SETLISTS_SONGS_LIBRARY*69)  + (BMC_MAX_TIMED_EVENTS*32) + (BMC_MAX_LFO*87) + (BMC_MAX_PIXEL_PROGRAMS*12)+(BMC_MAX_OLED*66)+(BMC_MAX_ILI9341_BLOCKS*77) +(BMC_MAX_GLOBAL_PIXELS*88)+(BMC_MAX_GLOBAL_RGB_PIXELS*99))
  #define BMC_CRC (uint16_t)((((_____BMC_GLOBAL)+(sizeof(bmcStore))) & 0xFFFF))

#endif
