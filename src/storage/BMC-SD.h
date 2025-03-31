/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Read and write a file to the built-in SD card on Teensy 3.6/3.5/4.0/4.1
  This file is a Raw hex with the EEPROM data
*/
#ifndef BMC_SD_H
#define BMC_SD_H

#include "utility/BMC-Def.h"

#if defined(BMC_SD_CARD_ENABLED)

#include <SD.h>
#include <SPI.h>

class BMC_SD {
public:
  BMC_SD(){

  }
  void begin(){
    if(!SD.begin(BUILTIN_SDCARD)){
      BMC_ERROR("BMC_SD: NO SD CARD DETECTED");
      BMC_HALT();
    }
    loadFileId();
    BMC_PRINTLN("BMC_SD: BEGIN file id:",fileId,"file name:",fileName);
  }
  void setFileId(uint8_t id){
    if(fileId != id && id<BMC_FS_MAX_STORES){
      fileId = id;
      sprintf(fileName,"BMC%03u.HEX",(uint8_t)id);
      saveFileId();
    }
  }
  uint8_t getFileId(){
    return fileId;
  }
  template <typename T> T &get(T &t){
    return get(fileId,t);
  }
  template <typename T> T &get(uint8_t index, T &t){
    setFileId(index);
    if(!SD.exists(fileName)){
      clear();
    } else {
      bmcFile = SD.open(fileName,FILE_READ);
      if(bmcFile.size()!=sizeof(t)){
        bmcFile.close();
        clear();
      }
    }
    bmcFile = SD.open(fileName,FILE_READ);
    bmcFile.read((uint8_t *)&t,sizeof(t));
    bmcFile.close();
    return t;
  }
  template <typename T> const T &put(const T &t){
    return put(fileId,t);
  }
  template <typename T> const T &put(uint8_t index, const T &t){
    setFileId(index);
    if(SD.exists(fileName)){
      SD.remove(fileName);
    }
    bmcFile = SD.open(fileName, FILE_WRITE);
    bmcFile.write((uint8_t *)&t,sizeof(t));
    bmcFile.close();
    return t;
  }
  void clear(){
    if(SD.exists(fileName)){
      SD.remove(fileName);
    }
    bmcFile = SD.open(fileName, FILE_WRITE);
    uint8_t x = 0;
    for(uint16_t i=0,n=sizeof(bmcStore);i<n;i++){
      bmcFile.write(x);
    }
    bmcFile.close();
  }
  uint16_t length(){
    #if BMC_MCU_RAM_SIZE >= 256000 && defined(BMC_STORAGE_PARTITION_SIZE_32K)
      return 32000;
    #else
      return 16000;
    #endif
  }
private:
  File bmcFile;
  uint8_t fileId = 0;
  char fileName[11];

  void loadFileId(){
    if(!SD.exists(BMC_FS_FILE_NAME)){
      fileId = 0;
      saveFileId();
      return;
    }
    bmcFile = SD.open(BMC_FS_FILE_NAME);
    bmcFile.read(&fileId,1);
    bmcFile.close();
    sprintf(fileName,"BMC%03u.HEX",fileId);
  }
  void saveFileId(){
    if(SD.exists(BMC_FS_FILE_NAME)){
      SD.remove(BMC_FS_FILE_NAME);
    }
    bmcFile = SD.open(BMC_FS_FILE_NAME, FILE_WRITE);
    bmcFile.write(fileId);
    bmcFile.close();
    loadFileId();
  }
};
#endif

#endif
