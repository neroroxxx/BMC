/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  The BMCStorage class can be modified to use your own code
  for use with an external EEPROM chip, just make sure it
  always has the get, set, clear and getLength methods
  and that get and set take in a bmcStore object.
*/
#ifndef BMC_STORAGE_H
#define BMC_STORAGE_H

#include "utility/BMC-Def.h"

// for built-in SD card
#if defined(BMC_SD_CARD_ENABLED)
  #include "storage/BMC-SD.h"

// for Flash File System
#elif defined(BMC_FS_ENABLED)
  #include "storage/BMC-FS.h"

// for 24LC256 i2c EEPROM
#elif defined(BMC_USE_24LC256)
  #include "storage/BMC-24LC256.h"
  #if !defined(BMC_24LC256_ADDRESS)
    #define BMC_24LC256_ADDRESS 0x50
  #endif

// for internal EEPROM
#else
  #include <EEPROM.h>
  #define STORAGE EEPROM
#endif

#if defined(BMC_DEBUG)
  #define BMC_STORAGE_DEBUG_TIME_T micros
#endif

class BMCStorage {
public:
  #if defined(BMC_USE_24LC256)
    BMCStorage(BMCGlobals& t_globals):globals(t_globals),STORAGE(kbits_256, 1, 32, BMC_24LC256_ADDRESS){}
  #else
    BMCStorage(BMCGlobals& t_globals):globals(t_globals){}
  #endif
  void begin(){

  #if defined(BMC_SD_CARD_ENABLED)
    BMC_PRINTLN(" - BMCStorage::begin (SD CARD)");
    STORAGE.begin();
  #elif defined(BMC_FS_ENABLED)
    BMC_PRINTLN(" - BMCStorage::begin (FS)");
    STORAGE.begin();
  #elif defined(BMC_USE_24LC256)
    BMC_PRINTLN(" - BMCStorage::begin (24LC256)");
    #if BMC_I2C_FREQ == 400000
      uint8_t t = STORAGE.begin(BMC24LC256::twiClock400kHz);
    #else
      uint8_t t = STORAGE.begin(BMC24LC256::twiClock100kHz);
    #endif
    if(t){
      #ifdef BMC_DEBUG
      if(t==1){
        BMC_ERROR(
          "24LC256 Error 1:data too long to fit in transmit buffer",
          "Check the wiring to your 24LC256 Chip",
          "24LC256 Must be connected to i2c Pins"
        );
      } else if(t==2){
        BMC_ERROR(
          "24LC256 Error 2:received NACK on transmit of address",
          "Check the wiring to your 24LC256 Chip",
          "24LC256 Must be connected to i2c Pins"
        );
      } else if(t==3){
        BMC_ERROR(
          "24LC256 Error 3: received NACK on transmit of data",
          "Check the wiring to your 24LC256 Chip",
          "24LC256 Must be connected to i2c Pins"
        );
      } else if(t==4){
        BMC_ERROR(
          "24LC256 Error 4: other error",
          "Check the wiring to your 24LC256 Chip",
          "24LC256 Must be connected to i2c Pins"
        );
      } else {
        BMC_ERROR(
          "24LC256 Error ???",
          t,
          "Check the wiring to your 24LC256 Chip",
          "24LC256 Must be connected to i2c Pins"
        );
      }
      #endif
      BMC_HALT();
    }
  #else
    BMC_PRINTLN(" - BMCStorage::begin (Built In EEPROM)");
    #ifdef BMC_FOR_ESP32
      STORAGE.begin(4096);
    #endif
  #endif
  }
  void setFileId(uint8_t id){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      STORAGE.setFileId(id);
    #endif
  }
  uint8_t getFileId(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      return STORAGE.getFileId();
    #else
      return 0;
    #endif
  }

  #if defined(BMC_DEBUG)
    void printInfo(){
      BMC_PRINTLN("=====================================================");
      BMC_PRINTLN("Storage:")
      BMC_PRINTLN(" - Total:",  length(),         "Bytes.");
      BMC_PRINTLN(" - Used:",   sizeof(bmcStore), "Bytes");
      BMC_PRINTLN("=====================================================");

      #if defined(BMC_USE_24LC256) || defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
        STORAGE.printInfo();
      #endif
    }
  #endif

  void get(bmcStore &file){
    #ifdef BMC_DEBUG
      debugStartTiming("Reading");
    #endif

    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      // load the bmcStore Struct from SD Card
      STORAGE.get(file);
    #else
      // load the bmcStore Struct from EEPROM
      STORAGE.get(0, file);
    #endif

    #ifdef BMC_DEBUG
      debugStopTiming();
    #endif
  }
  void set(bmcStore &file){
    #ifdef BMC_DEBUG
      debugStartTiming("Updating");
    #endif

    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      // save the bmcStore Struct from SD Card
      STORAGE.put(file);
    #else
      // Update the bmcStore Struct in EEPROM,
      // only update bytes that have changed
      STORAGE.put(0, file);
      #if defined(BMC_FOR_ESP32) && !defined(BMC_USE_24LC256)
        STORAGE.commit();
      #endif
    #endif

    #ifdef BMC_DEBUG
      debugStopTiming();
    #endif
  }

  template <typename T> void get(uint16_t address, const T& file){
    #ifdef BMC_DEBUG
      debugStartTiming("Reading");
    #endif

    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      // load the bmcStore Struct from SD Card
      STORAGE.get(address, file);
    #else
      // load the bmcStore Struct from EEPROM
      STORAGE.get(address, file);
    #endif

    #ifdef BMC_DEBUG
      debugStopTiming();
    #endif
  }
  template <typename T> void set(uint16_t address, const T& file){
    #ifdef BMC_DEBUG
      debugStartTiming("Updating");
    #endif

    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      // save the bmcStore Struct to the SD Card
      STORAGE.put(address, file);
    #else
      // Update the bmcStore Struct in EEPROM,
      // only update bytes that have changed
      STORAGE.put(address, file);
      #if defined(BMC_FOR_ESP32) && !defined(BMC_USE_24LC256)
        STORAGE.commit();
      #endif
    #endif

    #ifdef BMC_DEBUG
      debugStopTiming();
    #endif
  }
  void clear(){
    #ifdef BMC_DEBUG
      debugStartTiming("Clearing");
    #endif

    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      STORAGE.clear();
    #elif defined(BMC_USE_24LC256)
      STORAGE.clear();
    #else
      for(uint16_t i = 0,n=STORAGE.length(); i < n; i++){
        // Set every cell to 0
        #if defined(BMC_FOR_TEENSY)
          STORAGE.update(i, 0);
        #endif

        #if defined(BMC_FOR_ESP32)
          STORAGE.write(i, 0);
        #endif
      }

      #if defined(BMC_FOR_ESP32) && !defined(BMC_USE_24LC256)
        STORAGE.commit();
      #endif
    #endif

    #ifdef BMC_DEBUG
      debugStopTiming();
    #endif
  }
  uint16_t length(){
    // Get the number of bytes of EEPROM
    return STORAGE.length();
  }
  uint16_t getLength(){
    return length();
  }
private:
  // reference to globals
  BMCGlobals& globals;
  #if defined(BMC_SD_CARD_ENABLED)
    BMC_SD STORAGE;
  #elif defined(BMC_FS_ENABLED)
    BMC_FS STORAGE;
  #elif defined(BMC_USE_24LC256)
    BMC24LC256 STORAGE;
    BMCElapsedMillis extEepromTimer;
  #endif
  #if defined(BMC_DEBUG)
    unsigned long debugTimer = 0;
    void debugStartTiming(const char * str){
      if(!globals.getStorageDebug()){
        return;
      }
      BMC_INFO_HEAD;
      BMC_PRINT("***",str,"Store...");
      debugTimer = BMC_STORAGE_DEBUG_TIME_T();
    }
    void debugStopTiming(){
      if(!globals.getStorageDebug()){
        return;
      }
      BMC_PRINTLN("took",((BMC_STORAGE_DEBUG_TIME_T()-debugTimer)/1000.0),"milliseconds");
      BMC_INFO_FOOT;
    }
  #endif
};

#endif
