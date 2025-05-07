
#ifndef BMC_DEFBOARDS_H
#define BMC_DEFBOARDS_H


#if defined(__arm__) && defined(CORE_TEENSY)

  #define BMC_FOR_TEENSY

  #if defined(ARDUINO_TEENSY_MICROMOD)

    // *******************************************
    // *        Teensy MicroMod
    // *******************************************
    // Teensy 4.1
    // __IMXRT1062__
    #define BMC_MCU_MODEL             	 42
    #define BMC_MCU_MODEL_STR         	 "Teensy MicroMod"
    #define BMC_MCU_RAM_SIZE          	 1024000
    #define BMC_MCU_EEPROM_SIZE       	 4284
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 true
    #define BMC_MCU_HAS_SD_CARD       	 true
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 8
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 46
    #define BMC_MCU_TOTAL_PWM_PINS    	 27
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 18

  #elif defined(ARDUINO_TEENSY41)

    // *******************************************
    // *        Teensy 4.1
    // *******************************************
    // Teensy 4.1
    // __IMXRT1062__
    #define BMC_MCU_MODEL             	 41
    #define BMC_MCU_MODEL_STR         	 "Teensy 4.1"
    #define BMC_MCU_RAM_SIZE          	 1024000
    #define BMC_MCU_EEPROM_SIZE       	 4284
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 true
    #define BMC_MCU_HAS_SD_CARD       	 true
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 8
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 42
    #define BMC_MCU_TOTAL_PWM_PINS    	 27
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 18

  #elif defined(ARDUINO_TEENSY40)

    // *******************************************
    // *        Teensy 4.0
    // *******************************************
    // Teensy 4.0
    // __IMXRT1062__
    #define BMC_MCU_MODEL             	 40
    #define BMC_MCU_MODEL_STR         	 "Teensy 4.0"
    #define BMC_MCU_RAM_SIZE          	 1024000
    #define BMC_MCU_EEPROM_SIZE       	 1080
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 true
    #define BMC_MCU_HAS_SD_CARD       	 true
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 7
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 40
    #define BMC_MCU_TOTAL_PWM_PINS    	 31
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 14

  #elif defined(ARDUINO_TEENSY36)

    // *******************************************
    // *        Teensy 3.6
    // *******************************************
    // Teensy 3.6
    // __MK66FX1M0__
    #define BMC_MCU_MODEL             	 36
    #define BMC_MCU_MODEL_STR         	 "Teensy 3.6"
    #define BMC_MCU_RAM_SIZE          	 262144
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 true
    #define BMC_MCU_HAS_SD_CARD       	 true
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               false
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 6
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 58
    #define BMC_MCU_TOTAL_PWM_PINS    	 22
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 25

  #elif defined(ARDUINO_TEENSY35)

    // *******************************************
    // *        Teensy 3.5
    // *******************************************
    // Teensy 3.5
    // __MK64FX512__
    #define BMC_MCU_MODEL             	 35
    #define BMC_MCU_MODEL_STR         	 "Teensy 3.5"
    #define BMC_MCU_RAM_SIZE          	 262144
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 true
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               false
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 6
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 58
    #define BMC_MCU_TOTAL_PWM_PINS    	 20
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 27

  #elif defined(ARDUINO_TEENSY32)

    // *******************************************
    // *        Teensy 3.2
    // *******************************************
    // Teensy 3.2 / 3.1
    // __MK20DX256__
    #define BMC_MCU_MODEL             	 32
    #define BMC_MCU_MODEL_STR         	 "Teensy 3.2"
    #define BMC_MCU_RAM_SIZE          	 65536
    #define BMC_MCU_EEPROM_SIZE       	 2048
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               false
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 3
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 33
    #define BMC_MCU_TOTAL_PWM_PINS    	 12
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 21

  #elif defined(ARDUINO_TEENSYLC)

    // *******************************************
    // *        Teensy LC
    // *******************************************
    // Teensy LC
    // __MKL26Z64__
    #define BMC_MCU_MODEL             	 10
    #define BMC_MCU_MODEL_STR         	 "Teensy LC"
    #define BMC_MCU_RAM_SIZE          	 8192
    #define BMC_MCU_EEPROM_SIZE       	 128
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               false
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 3
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 27
    #define BMC_MCU_TOTAL_PWM_PINS    	 10
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 13

    #error "Teensy LC is no longer supported due to Flash size."

  #else
    #error "BMC is only Compatible with Teensy 3.2, 3.5, 3.6, 4.0, 4.1 & MicroMod"
  #endif

#elif defined(ESP32)
  
  // *******************************************
  // *        ESP32 BOARDS DEFINITIONS
  // *******************************************

  #define BMC_FOR_ESP32

  #if defined(ARDUINO_ESP32_DEV)
  
    // *******************************************
    // *        ESP32 Devkit
    // *******************************************

    #define BMC_MCU_MODEL             	 100
    #define BMC_MCU_MODEL_STR         	 "ESP32 Devkit"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       false
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     true
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #elif defined(ARDUINO_ESP32_MICROMOD)
  
    // *******************************************
    // *        ESP32 MicroMod
    // *******************************************

    #define BMC_MCU_MODEL             	 101
    #define BMC_MCU_MODEL_STR         	 "ESP32 MicroMod"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       false
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     true
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 15

  #elif defined(ARDUINO_ESP32S2_DEV)
  
    // *******************************************
    // *        ESP32-S2
    // *******************************************

    #define BMC_MCU_MODEL             	 102
    #define BMC_MCU_MODEL_STR         	 "ESP32-S2"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #elif defined(ARDUINO_ESP32S3_DEV)
  
    // *******************************************
    // *        ESP32-S3
    // *******************************************
    
    #if !defined(BMC_MIDI_BLE_ENABLED)
      #define BMC_MIDI_BLE_ENABLED
    #endif

    #define BMC_MCU_MODEL             	 103
    #define BMC_MCU_MODEL_STR         	 "ESP32-S3"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     true
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #elif defined(ARDUINO_LOLIN_S2_MINI)
  
    // *******************************************
    // *        LOLIN S2 Mini
    // *******************************************

    #define BMC_MCU_MODEL             	 104
    #define BMC_MCU_MODEL_STR         	 "ESP32 S2 Mini (lolin)"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     false
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #elif defined(ARDUINO_WAVESHARE_ESP32_S3_ZERO)
  
    // *******************************************
    // *        ESP32-S3-ZERO
    // *******************************************
    
    #if !defined(BMC_MIDI_BLE_ENABLED)
      #define BMC_MIDI_BLE_ENABLED
    #endif

    #define BMC_MCU_MODEL             	 105
    #define BMC_MCU_MODEL_STR         	 "ESP32-S3 Zero"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     true
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #elif defined(ARDUINO_BMC_SENS3)
  
    // *******************************************
    // *        BMC SENS3 ESP32-S3
    // *******************************************
    
    #if !defined(BMC_MIDI_BLE_ENABLED)
      #define BMC_MIDI_BLE_ENABLED
    #endif

    #define BMC_MCU_MODEL             	 106
    #define BMC_MCU_MODEL_STR         	 "BMC SENS3"
    #define BMC_MCU_RAM_SIZE          	 520000
    #define BMC_MCU_EEPROM_SIZE       	 4096
    #define BMC_MCU_HAS_USB      	       true
    #define BMC_MCU_HAS_USB_HOST      	 false
    #define BMC_MCU_HAS_SD_CARD       	 false
    #define BMC_MCU_HAS_BLE       	     true
    #define BMC_MCU_HAS_FS               true
    #define BMC_MCU_TOTAL_SERIAL_PORTS	 2
    #define BMC_MCU_TOTAL_DIGITAL_PINS	 25
    #define BMC_MCU_TOTAL_PWM_PINS    	 21
    #define BMC_MCU_TOTAL_ANALOG_PINS 	 20

  #else
    #error "BMC is not compatible withe the selected ESP32 board"
  #endif

#endif


#if !defined(BMC_MCU_MODEL)
  #error "BMC is only compatible with Teensy 3.2, 3.5, 3.6, 4.0, 4.1 & MicroMod, ESP32 devkit (original), ESP32 MicroMod, ESP32-S2, ESP32-S3"
#endif


#endif
