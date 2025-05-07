/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Read and write a file to LittleFS (Filesystem)
  This file is a Raw hex with the EEPROM-style Store data
*/

#include "storage/BMC-FS.h"
#include <LittleFS.h>


#if defined(BMC_FOR_TEENSY)
  LittleFS_Program BMC_LITTLE_FS_HANDLER;
#endif

File bmcFsStoreFile;

void BMC_FS::begin() {
  #if defined(BMC_FOR_TEENSY)
    uint32_t diskSize = BMC_FS_PROG_FLASH_SIZE;
    if (!BMC_LITTLE_FS_HANDLER.begin(diskSize)) {
      BMC_ERROR("BMC_FS: Filesystem mount failed");
      BMC_HALT();
    }
  #elif defined(BMC_FOR_ESP32)
    if (!BMC_LITTLE_FS_HANDLER.begin(true)) {
      BMC_ERROR("BMC_FS: Filesystem mount failed");
      BMC_HALT();
    }
  #endif
  loadFileId();
  BMC_PRINTLN("   - BMC_FS::begin()");
  showDirectory();
}

void BMC_FS::setFileId(uint8_t id) {
  fileId = id;
  fileId = 0;
}

uint8_t BMC_FS::getFileId() {
  return fileId;
}



void BMC_FS::clear() {
  BMC_PRINTLN("   - BMC_FS::clear()");
  if(BMC_LITTLE_FS_HANDLER.exists(fileName)) {
    BMC_LITTLE_FS_HANDLER.remove(fileName);  // ✅ removes the file cleanly
  }
  bmcStore t = {};
  put(0, t);
}


void BMC_FS::showDirectory(){
#if defined(BMC_DEBUG)
  directoryCount = 0;
  BMC_PRINTLN("");
  BMC_INFO_HEAD;
  BMC_PRINTLN("   - File Name:", fileName);
  #if defined(BMC_FOR_TEENSY)
    BMC_PRINTLN("   - File System Size:", BMC_LITTLE_FS_HANDLER.totalSize());
  #endif
  BMC_PRINTLN("   - Directory:");
  BMC_PRINTLN("");
  listDirectory(BMC_LITTLE_FS_HANDLER.open("/"));
  BMC_PRINTLN("");
  BMC_INFO_FOOT;
  
  BMC_PRINTLN("");
#endif
}
#if defined(BMC_DEBUG)
void BMC_FS::listDirectory(File dir){
  while(true) {
    directoryCount++;
    File entry = dir.openNextFile();
    if (! entry) {
      if(directoryCount == 0){
        BMC_PRINTLN("** No Files in File System **");
      }
      break;
    }
    BMC_PRINT("      -", entry.name());
    if (entry.isDirectory()) {
      BMC_PRINTLN("/");
      listDirectory(entry);
    } else {
      // files have sizes, directories do not
      BMC_PRINTLN(" size: ", entry.size());
    }
    entry.close();
  }
}
#endif

uint16_t BMC_FS::length() {
  return 32000;
}
void BMC_FS::loadFileId() {
  // single partition
  fileId = 0;
}

void BMC_FS::saveFileId() {
  bmcFsStoreFile = BMC_LITTLE_FS_HANDLER.open(BMC_FS_STORE_ID_FILE_NAME, FILE_WRITE);
  if (bmcFsStoreFile) {
    // single partition
    fileId = 0;
    bmcFsStoreFile.write(fileId);
    bmcFsStoreFile.close();
  }
}