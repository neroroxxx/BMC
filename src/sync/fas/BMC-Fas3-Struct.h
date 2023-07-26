/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Wrapper to control/read from Fractal Audio Devices

  Currently only supports Axe Fx II/XL/+ and AX8

  Support for Axe Fx 3 and FM3 is planned for the future
*/
#ifndef BMC_FAS3_STRUCT_H
#define BMC_FAS3_STRUCT_H

#include "utility/BMC-Def.h"

#if defined(BMC_USE_FAS) && defined(BMC_USE_FAS3)

#include "sync/fas/BMC-Fas-Def.h"

#if !defined(BMC_FAS3_POLL_TIME)
  #define BMC_FAS3_POLL_TIME 2000
#endif

// Fractal Device ID
// ------------------------
// 0x10 Axe-Fx III
// 0x11 FM3
struct BMCFas3Device {
  uint8_t id = 0;
  uint8_t port = 0;
  uint8_t channel = 1;
  uint8_t flags = 0;
  uint16_t max = 512;
  // BMCTunerData tuner;
  BMCLooperData looper;
  BMCTimer syncTimer;
  BMCTimer resyncTimer;
  uint8_t getId(){
    return id;
  }
  uint8_t getPort(){
    return port;
  }
  uint8_t getMidiChannel(){
    return channel;
  }
  void setMidiChannel(uint8_t t_value){
    channel = t_value;
  }
  bool connectionLost(){
    return syncTimer.active() && syncTimer.complete();
  }
  void connectionActive(){
    syncTimer.start(5000);
  }
  void getDeviceName(char * buff){
    switch(id){
      case BMC_FAS_DEVICE_ID_AXE_FX_III:
        strcpy(buff, "Axe FX III");
        break;
      case BMC_FAS_DEVICE_ID_FM3:
        strcpy(buff, "FM3");
        break;
      case BMC_FAS_DEVICE_ID_FM9:
        strcpy(buff, "FM9");
        break;
    }
  }

  bool syncReady(){
    return resyncTimer.active() && resyncTimer.complete();
  }
  
  void reSync(uint16_t t_time = BMC_FAS3_POLL_TIME){
    resyncTimer.start(t_time);
    syncTimer.start(5000);
  }
  bool connected(){
    return bitRead(flags, 0);
  }
  bool connect(uint8_t t_id, uint8_t t_port){
    if(connected()){
      return true;
    }
    switch(t_id){
      case BMC_FAS_DEVICE_ID_AXE_FX_III:
      case BMC_FAS_DEVICE_ID_FM3:
      case BMC_FAS_DEVICE_ID_FM9:
        reset();
        id = t_id;
        port = t_port;
        bitWrite(flags, 0, 1);
        bitWrite(flags, 1, 1);
        bitWrite(flags, 2, 1);
        return true;
    }
    return false;
  }
  void disconnect(){
    reset();
    bitWrite(flags, 1, 1);
  }
  bool connectionChanged(){
    bool val = bitRead(flags, 1);
    if(val){
      bitWrite(flags, 1, 0);
    }
    return val;
  }
  bool syncing(){
    return bitRead(flags, 0);
  }
  void reset(){
    id = 0;
    port = 0;
    // do not reset the channel when the device is reset
    // this is assigned in settings
    // channel = 1;
    flags = 0;
    max = 512;
    // tuner.reset();
    looper.reset();
    syncTimer.stop();
    resyncTimer.stop();
  }
};

struct BMCFas3Preset {
  uint16_t id = 0xFFFF;
  uint8_t scene = 0xFF;
  int8_t sceneCount = -1;
  char name[BMC_FAS_MAX_PRESET_NAME] = "";
  char sceneName[8][BMC_FAS3_MAX_SCENE_NAME];

  // char prevName[33] = "";
  // char nextName[33] = "";

  // BMCFas3Block blocks[32];
  uint8_t blockStates[91];
  uint8_t lastBlockCrc = 0xFF;
  uint8_t flags = 0;
  void reset(){
    id = 0xFFFF;
    scene = 0xFF;
    flags = 0;
    for(uint8_t i=0;i<8;i++){
      strcpy(sceneName[i], "");
    }
    strcpy(name, "");
    
    memset(blockStates, 0, sizeof(blockStates));
    lastBlockCrc = 0xFF;
    sceneCount = -1;
    // blockStates
  }
  void setPreset(uint16_t t_value, char * txt){
    if(t_value > 1023){
      return;
    }
    if(id != t_value){
      bitWrite(flags, 0, 1);
    }
    id = t_value;
    strcpy(name, txt);
    BMCTools::strTrimTail(name);
  }
  bool presetHasChanged(){
    bool t = bitRead(flags, 0);
    if(t){
      bitWrite(flags, 0, 0);
    }
    return t;
  }
  uint16_t getPresetNumber(){
    if(id < 1024){
      return id;
    }
    return 0;
  }
  void getPresetName(char * str){
    if(id < 1024){
      strcpy(str, name);
    }
  }

  void setScene(uint8_t t_value){
    if(t_value < 8){
      scene = t_value;
    }
  }
  void setScene(uint8_t t_value, char * str, bool isCurrent){
    if(t_value < 8){
      if(isCurrent){
        scene = t_value;
      }
      strcpy(sceneName[t_value], str);
      BMCTools::strTrimTail(sceneName[t_value]);
    }
  }
  uint8_t getSceneNumber(){
    return scene;
  }
  void getSceneName(char * str){
    if(scene < 8){
      strcpy(str, sceneName[scene]);
    }
  }
  void getSceneName(uint8_t t_scene, char * str){
    if(t_scene < 8){
      strcpy(str, sceneName[t_scene]);
    }
  }
  bool queryNextScene(){
    sceneCount++;
    if(sceneCount == scene){
      sceneCount++;
    }
    if(sceneCount > 7){
      sceneCount = -1;
      return false;
    }
    return true;
  }
  // **************
  // ***** BLOCKS
  // **************
  void setBlockData(uint8_t t_id, uint8_t t_flags){
    blockStates[t_id] = t_flags;
  }
  // bitRead(flags, 0); // 0 = engaged, 1 = bypassed
  // ((flags >> 1) & 0x07); // channel
  // ((flags >> 4) & 0x07); // number of channels supported for this effect (0-7).
  bool getBlockState(uint8_t t_id){
    return bitRead(blockStates[t_id], 0)==0;
  }
  uint8_t getBlockChannel(uint8_t t_id){
    return ((blockStates[t_id] >> 1) & 0x07);
  }
  uint8_t getBlockChannelMax(uint8_t t_id){
    return ((blockStates[t_id] >> 4) & 0x07);
  }
  uint8_t getLastBlocksCrc(){
    return lastBlockCrc;
  }
  void setLastBlocksCrc(uint8_t t_crc){
    lastBlockCrc = t_crc;
  }
  void setBlockBypass(uint8_t t_id, bool t_value){
    bitWrite(blockStates[t_id], 0, t_value);
  }
  void setBlockChannel(uint8_t t_id, uint8_t t_value){
    BMC_WRITE_BITS(blockStates[t_id], t_value, 0x07, 1);
  }
};
struct BMCFas3Block {
  uint8_t id = 0;
  char name[5] = "";
  uint8_t index = 0;
  uint8_t flags = 0;
};
#endif
#endif
