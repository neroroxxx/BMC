/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Read and write a file to LittleFS (Filesystem)
  This file is a Raw hex with the EEPROM-style Store data
*/
#pragma once

#ifndef BMC_FS_H
#define BMC_FS_H

#include "utility/BMC-Def.h"

#if BMC_MCU_HAS_FS == true && defined(BMC_FS_ENABLED)

#if !defined(BMC_FS_PROG_FLASH_BLOCKS)
  #define BMC_FS_PROG_FLASH_BLOCKS 128
#endif

#define BMC_FS_PROG_FLASH_SIZE (BMC_FS_PROG_FLASH_BLOCKS * 1024) // Specify size to use of onboard Teensy Program Flash chip

#include <LittleFS.h>

#if defined(BMC_FOR_TEENSY)
  #define BMC_LITTLE_FS_HANDLER bmcLittleFS
  extern LittleFS_Program BMC_LITTLE_FS_HANDLER;
  #define BMC_FS_STORE_ID_FILE_NAME "BMC.dat"
  #define BMC_LITTLEFS_FILE_NAME "BMC000.dat"
  #define BMC_FILE_WRITE_ FILE_WRITE_BEGIN
#else
  #define BMC_LITTLE_FS_HANDLER LittleFS
  #define BMC_FS_STORE_ID_FILE_NAME "/BMC.dat"
  #define BMC_LITTLEFS_FILE_NAME "/BMC000.dat"
  #define BMC_FILE_WRITE_ FILE_WRITE
#endif

extern File bmcFsStoreFile;

class BMC_FS {
public:
  BMC_FS() {}

  void begin();

  void setFileId(uint8_t id);

  uint8_t getFileId();

  template <typename T>
  T &get(T &t) {
    return get(fileId, t);
  }

  template <typename T>
  T &get(uint8_t index, T &t) {
    // setFileId(index);
    if (!BMC_LITTLE_FS_HANDLER.exists(fileName)) {
      BMC_PRINTLN("   - ", fileName, "doesn't exist");
      clear();
    } else {
      bmcFsStoreFile = BMC_LITTLE_FS_HANDLER.open(fileName, FILE_READ);
      if (!bmcFsStoreFile) {
        bmcFsStoreFile.close();
        clear();
      } else {
        bmcFsStoreFile.read((uint8_t *)&t, sizeof(t));
        bmcFsStoreFile.close();
      }
    }
    return t;
  }

  template <typename T>
  const T &put(const T &t) {
    return put(fileId, t);
  }

  template <typename T>
  const T &put(uint8_t index, const T &t) {
    // setFileId(index);  // Ensure fileName is correct for this index
    BMC_PRINTLN("   - BMC_FS::put()", fileName);

    // Clean up old file to avoid file growth or wear-level trash
    if (BMC_LITTLE_FS_HANDLER.exists(fileName)) {
      BMC_LITTLE_FS_HANDLER.remove(fileName);
    }
    // Truncating write (forces file size to match exactly sizeof(t))
    File file = BMC_LITTLE_FS_HANDLER.open(fileName, BMC_FILE_WRITE_);
    if (!file) {
      BMC_PRINTLN("   - BMC_FS::put() Failed to open file", fileName);
      return t;
    }

    int written = file.write((const uint8_t *)&t, sizeof(t));
    file.close();

    BMC_PRINTLN("   - BMC_FS::put() written", written, "expected:", sizeof(t));
    if (written != sizeof(t)) {
      printError(written);
    }

    showDirectory();  // Optional: for debug

    return t;
  }
#if defined(BMC_DEBUG)
  void printInfo(){
    showDirectory();
  }
#endif

  void clear();
  void showDirectory();
  void listDirectory(File dir);

  uint16_t length();

private:

  // File bmcFsStoreFile;
  uint8_t fileId = 0;
#if defined(BMC_DEBUG)
  uint8_t directoryCount = 0;
#endif
  char fileName[12] = BMC_LITTLEFS_FILE_NAME; // "BMC000.bin" + null

  void loadFileId();

  void saveFileId();

  void printError(int val){
    switch(val){
      case 0:   BMC_ERROR("BMC_FS No error");                     break;
      case -5:  BMC_ERROR("BMC_FS Error: Device I/O failure");    break;
      case -84: BMC_ERROR("BMC_FS Error: Corrupted filesystem");  break;
      case -2:  BMC_ERROR("BMC_FS Error: Entry not found");       break;
      case -17: BMC_ERROR("BMC_FS Error: Entry already exists");  break;
      case -20: BMC_ERROR("BMC_FS Error: Not a directory");       break;
      case -21: BMC_ERROR("BMC_FS Error: Is a directory");        break;
      case -39: BMC_ERROR("BMC_FS Error: Directory not empty");   break;
      case -9:  BMC_ERROR("BMC_FS Error: Bad file number");       break;
      case -27: BMC_ERROR("BMC_FS Error: File too large");        break;
      case -22: BMC_ERROR("BMC_FS Error: Invalid parameter");     break;
      case -28: BMC_ERROR("BMC_FS Error: No space left");         break;
      case -12: BMC_ERROR("BMC_FS Error: Out of memory");         break;
      case -61: BMC_ERROR("BMC_FS Error: No attribute/data");     break;
      case -36: BMC_ERROR("BMC_FS Error: Filename too long");     break;
      default:  BMC_ERROR("BMC_FS Error: Unknown");               break;
    }
    if(val < 0){
      BMC_HALT();
    }
  }
};

#endif
#endif