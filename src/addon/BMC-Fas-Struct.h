/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Wrapper to control/read from Fractal Audio Devices
*/
#ifndef BMC_FAS_STRUCT_H
#define BMC_FAS_STRUCT_H

#include "utility/BMC-Def.h"

#if defined(BMC_USE_FAS)

#include "addon/BMC-Fas-Def.h"

// Fractal Device ID, only AX8 supported at the moment
// ------------------------
// 0x00 Axe-Fx Standard
// 0x01 Axe-Fx Ultra
// 0x02 MFC-101
// 0x03 Axe-Fx II
// 0x04 MFC-101 mk3
// 0x05 FX8
// 0x06 Axe-Fx II XL
// 0x07 Axe-Fx II XL+
// 0x08 AX8
// 0x0A FX8 mk2
// 0x10 Axe-Fx III

struct BMCFasBlocks {
  uint8_t id = 0;
  char name[4] = "";
  uint8_t index = 0;
  uint8_t flags = 0;
  void reset(){
    id = 0;
    index = 0;
    flags = 0;
    strcpy(name, "");
  }
};
struct BMCFasBlockStates {
  uint8_t crc = 0;
  uint8_t loaded[9];
  uint8_t state[9];
  uint8_t xy[9];

  void set(uint8_t n, bool t_engaged, bool t_isY){
    if(n<100 || n>170){
      return;
    }
    n -= 100;
    uint8_t a = floor(n/8.0);
    uint8_t b = n - (a*8);
    bitWrite(loaded[a], b, 1);
    bitWrite(state[a], b, t_engaged);
    bitWrite(xy[a], b, t_isY);
  }
  void reset(){
    memset(loaded, 0, 9);
    memset(state, 0, 9);
    memset(xy, 0, 9);
    crc = 0;
    // blocks 139, 140, and 141 are always available they are:
    // 139 Input Noise Gate
    // 140 Output
    // 141 Controllers
    // These are always "loaded" so we always set them have the block loaded
    // they still can't be bypassed or X/Y but they are always available
    bitWrite(loaded[4], 7, 1);
    bitWrite(loaded[5], 0, 1);
    bitWrite(loaded[5], 1, 1);
  }
  void createCRC(){
    crc = 0;
    for(uint8_t i=0;i<9;i++){
      crc ^= loaded[i] & 0xFF;
    }
    for(uint8_t i=0;i<9;i++){
      crc ^= state[i] & 0xFF;
    }
    for(uint8_t i=0;i<9;i++){
      crc ^= xy[i] & 0xFF;
    }
  }
  uint8_t getCRC(){
    return crc;
  }
  // Loaded in preset
  bool isLoaded(uint8_t n){
    return getBit(n, loaded);
  }
  // bypass state
  bool isOn(uint8_t n){
    return isLoaded(n) && getBit(n, state);
  }
  bool isOff(uint8_t n){
    return !isOn(n);
  }
  bool isBypassed(uint8_t n){
    return isOff(n);
  }
  bool isEngaged(uint8_t n){
    return isOn(n);
  }
  // XY
  bool isY(uint8_t n){
    return isLoaded(n) && getBit(n, xy);
  }
  bool isX(uint8_t n){
    return !isY(n);
  }
  bool getBit(uint8_t n, uint8_t* arr){
    if(n<100 || n>170){
      return false;
    }
    n -= 100;
    uint8_t a = floor(n/8.0);
    uint8_t b = n - (a*8);
    return bitRead(arr[a], b);
  }
};
struct BMCFasLooper {
  uint8_t data;
  uint8_t position;
  void set(uint8_t t_data, uint8_t t_position){
    data = t_data;
    position = t_position;
  }
  bool recording(){ return bitRead(data, 0); }
  bool play(){ return bitRead(data, 1); }
  bool once(){ return bitRead(data, 2); }
  bool overdub(){ return bitRead(data, 3); }
  bool reverse(){ return bitRead(data, 4); }
  bool half(){ return bitRead(data, 5); }
  bool undo(){ return bitRead(data, 6); }
  uint8_t getPosition(){ return position; }
  void reset(){
    data = 0;
    position = 0;
  }
};

struct BMCFasData {
  //BMCFlags <uint8_t> flags;
  uint8_t id = 0; // device id
  uint8_t port = 0;
  uint8_t channel = 0;
  uint8_t scene = 0;
  uint16_t version = 0;
  uint16_t preset = 0xFFFF;
  uint16_t maxPresets = 0;
  char presetName[32] = "";
  BMCFasBlockStates blocks;
  BMCFasLooper looper;


  uint16_t parameters[8];
  uint16_t parametersX[8];
  uint16_t parametersY[8];
  uint8_t parametersSyncedX = 0;
  uint8_t parametersSyncedY = 0;
  void paramReset(){
    parametersSyncedX = 0;
    parametersSyncedY = 0;
  }
  void paramSet(uint8_t slot, uint8_t block, uint8_t param){
    slot &= 0x07;
    parameters[slot] = (block<<8) | param;
    bitWrite(parametersSyncedX, slot, 0);
    bitWrite(parametersSyncedY, slot, 0);
  }
  bool paramReceived(uint8_t block, uint8_t param, uint16_t value){
    uint8_t slot = paramFindSlot(block, param);
    if(slot>7){
      return false;
    }
    if(blocks.isX(block)){
      parametersX[slot] = value;
      bitWrite(parametersSyncedX, slot, 1);
    } else {
      parametersY[slot] = value;
      bitWrite(parametersSyncedY, slot, 1);
    }
    return true;
  }
  bool paramIsSynced(uint8_t block, uint8_t param){
    uint8_t slot = paramFindSlot(block, param);
    if(slot>7){
      return true;
    }
    if(blocks.isX(block)){
      return bitRead(parametersSyncedX, slot);
    }
    return bitRead(parametersSyncedY, slot);
  }
  uint16_t paramGetValue(uint8_t block, uint8_t param){
    return paramGetValue(paramFindSlot(block, param));
  }
  uint16_t paramGetValue(uint8_t slot){
    if(slot>7){
      return 0;
    }
    uint8_t block = (parameters[slot]>>8) & 0xFF;
    if(blocks.isX(block)){
      return parametersX[slot];
    } else {
      return parametersY[slot];
    }
    return 0;
  }
  uint8_t paramFindSlot(uint8_t block, uint8_t param){
    for(uint8_t i=0;i<8;i++){
      if(parameters[i]==((block<<8) | param)){
        return i;
      }
    }
    return 255;
  }



  void setIdAndPort(uint8_t t_id, uint8_t t_port){
    if(id!=0 || port!=0){
      return;
    }
    switch(t_id){
      case BMC_FAS_DEVICE_ID_AXE_FX_II:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS:
      case BMC_FAS_DEVICE_ID_AX8:
        id = t_id;
        port = t_port;
        break;
    }
    switch(t_id){
      case BMC_FAS_DEVICE_ID_AXE_FX_II:
        maxPresets = 384;
        break;
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS:
        maxPresets = 768;
        break;
      case BMC_FAS_DEVICE_ID_AX8:
        maxPresets = 512;
        break;
    }
  }
  uint8_t getId(){
    return id;
  }
  uint8_t getPort(){
    return port;
  }
  void reset(){
    blocks.reset();
    looper.reset();
    //flags.reset();
    strcpy(presetName, "");
    id = 0; // device id
    port = 0;
    version = 0;
    channel = 0;
    preset = 0xFFFF;
    scene = 0;
  }
};
#endif
#endif
