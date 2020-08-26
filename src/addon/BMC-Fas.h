/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Wrapper to some sync/control Fractal Audio Guitar Processors
  In this Class as BLOCK is an EFFECT like Delay, Reverb, Amp, etc.
  Fractal Sysex Anatomy
  0: 0xF0 start of sysex
  1: 0x00 sysex id
  2: 0x00 sysex id
  3: 0x00 sysex id
  4: 0xnn fas device id
  5: 0xnn fas function id
  6: (n) start of sysex data
  n+1: checksum
  n+2: 0xF7 end of sysex

  Standard FAS response is minimum 9 bytes, without checksum it's 8

  For Axe Fx 2 users: for ideal syncing you should turn off the MIDI THRU OFF,
  also to use the tuner functions you must set "SEND REALTIME SYSEX" to ALL or TUNER
*/
#ifndef BMC_FAS_H
#define BMC_FAS_H
#include "utility/BMC-Def.h"
#if defined(BMC_USE_FAS)
#include "addon/BMC-Fas-Def.h"
#include "addon/BMC-Fas-Struct.h"

#define BMC_FAS_FLAG_DEVICE_SEARCH 0
#define BMC_FAS_FLAG_CONNECTED 1
#define BMC_FAS_FLAG_SYNCING 2
#define BMC_FAS_FLAG_TUNER_ACTIVE 3
#define BMC_FAS_FLAG_SYNC_EXPECTING_PRESET 4
#define BMC_FAS_FLAG_SYNC_EXPECTING_PRESET_NAME 5
#define BMC_FAS_FLAG_SYNC_EXPECTING_SCENE 6
#define BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS 7
#define BMC_FAS_FLAG_SYNC_EXPECTING_PARAMETERS 8
#define BMC_FAS_FLAG_SYNC_PARAMETER_SYNC_BEGIN 9
#define BMC_FAS_FLAG_TEMPO_RECEIVED 10

#define BMC_FAS_RESYNC_TIMEOUT 1000
#define BMC_FAS_RESYNC_QUEUE_TIMEOUT 175

#define BMC_FAS_FUNC_ID_BLOCK_PARAM           0x02
#define BMC_FAS_FUNC_ID_FIRMWARE              0x08
#define BMC_FAS_FUNC_ID_TUNER_INFO            0x0D
#define BMC_FAS_FUNC_ID_BLOCKS_DATA           0x0E
#define BMC_FAS_FUNC_ID_PRESET_NAME           0x0F
#define BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT       0x10 // unused
#define BMC_FAS_FUNC_ID_BLOCK_XY              0x11
#define BMC_FAS_FUNC_ID_CPU                   0x13
#define BMC_FAS_FUNC_ID_GET_PRESET_NUMBER     0x14
#define BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL      0x17
#define BMC_FAS_FUNC_ID_RESYNC                0x21
#define BMC_FAS_FUNC_ID_LOOPER                0x23
#define BMC_FAS_FUNC_ID_SCENE_NUMBER          0x29
#define BMC_FAS_FUNC_ID_SET_PRESET_NUMBER     0x3C
#define BMC_FAS_FUNC_ID_DISCONNECT            0x42
#define BMC_FAS_FUNC_ID_GENERAL_PURPOSE       0x64

//#define BMC_FAS_DEBUG

#if defined(BMC_FAS_DEBUG) && !defined(BMC_DEBUG)
  #undef BMC_FAS_DEBUG
#endif

class BMCFas {
private:
  BMCMidi& midi;
  BMCFlags <uint16_t> flags;
  BMCTimer findDeviceTimer;
  BMCTimer startSyncTimer;
  BMCTimer resyncTimer;
  BMCTimer tunerTimeout;
  BMCFasData device;
  BMCTunerData tunerData;
  uint8_t attempts = 0;
#ifdef BMC_DEBUG
  void debugPrintFasMessageInfo(BMCMidiMessage& message){
    char str[50];
    switch(message.sysex[5]){
      case BMC_FAS_FUNC_ID_BLOCK_PARAM:         strcpy(str, "BMC_FAS_FUNC_ID_BLOCK_PARAM");break;
      case BMC_FAS_FUNC_ID_FIRMWARE:            strcpy(str, "BMC_FAS_FUNC_ID_FIRMWARE");break;
      case BMC_FAS_FUNC_ID_TUNER_INFO:          strcpy(str, "BMC_FAS_FUNC_ID_TUNER_INFO");break;
      case BMC_FAS_FUNC_ID_BLOCKS_DATA:         strcpy(str, "BMC_FAS_FUNC_ID_BLOCKS_DATA");break;
      case BMC_FAS_FUNC_ID_PRESET_NAME:         strcpy(str, "BMC_FAS_FUNC_ID_PRESET_NAME");break;
      case BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT:     strcpy(str, "BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT");break;
      case BMC_FAS_FUNC_ID_BLOCK_XY:            strcpy(str, "BMC_FAS_FUNC_ID_BLOCK_XY");break;
      case BMC_FAS_FUNC_ID_CPU:                 strcpy(str, "BMC_FAS_FUNC_ID_CPU");break;
      case BMC_FAS_FUNC_ID_GET_PRESET_NUMBER:   strcpy(str, "BMC_FAS_FUNC_ID_GET_PRESET_NUMBER");break;
      case BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL:    strcpy(str, "BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL");break;
      case BMC_FAS_FUNC_ID_RESYNC:              strcpy(str, "BMC_FAS_FUNC_ID_RESYNC");break;
      case BMC_FAS_FUNC_ID_LOOPER:              strcpy(str, "BMC_FAS_FUNC_ID_LOOPER");break;
      case BMC_FAS_FUNC_ID_SCENE_NUMBER:        strcpy(str, "BMC_FAS_FUNC_ID_SCENE_NUMBER");break;
      case BMC_FAS_FUNC_ID_SET_PRESET_NUMBER:   strcpy(str, "BMC_FAS_FUNC_ID_SET_PRESET_NUMBER");break;
      case BMC_FAS_FUNC_ID_DISCONNECT:          strcpy(str, "BMC_FAS_FUNC_ID_DISCONNECT");break;
      case BMC_FAS_FUNC_ID_GENERAL_PURPOSE:     strcpy(str, "BMC_FAS_FUNC_ID_GENERAL_PURPOSE");break;
      default: strcpy(str, "UNUSED");
    }
    BMC_PRINTLN("--> FAS MESSAGE RECEIVED, ID:", message.sysex[5], str, "SIZE:", message.size());
  }
  bool isValidFasFunction(uint8_t funcId){
    switch(funcId){
      case BMC_FAS_FUNC_ID_BLOCK_PARAM:
      case BMC_FAS_FUNC_ID_FIRMWARE:
      case BMC_FAS_FUNC_ID_BLOCKS_DATA:
      case BMC_FAS_FUNC_ID_TUNER_INFO:
      case BMC_FAS_FUNC_ID_PRESET_NAME:
      case BMC_FAS_FUNC_ID_BLOCK_XY:
      case BMC_FAS_FUNC_ID_CPU:
      case BMC_FAS_FUNC_ID_GET_PRESET_NUMBER:
      case BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL:
      case BMC_FAS_FUNC_ID_RESYNC:
      case BMC_FAS_FUNC_ID_LOOPER:
      case BMC_FAS_FUNC_ID_SCENE_NUMBER:
      case BMC_FAS_FUNC_ID_SET_PRESET_NUMBER:
      case BMC_FAS_FUNC_ID_DISCONNECT:
      case BMC_FAS_FUNC_ID_GENERAL_PURPOSE:
        return true;
    }
    return false;
  }
#endif

public:
  BMCFas(BMCMidi& t_midi):midi(t_midi){
    device.reset();
    flags.on(BMC_FAS_FLAG_DEVICE_SEARCH);
    findDeviceTimer.start(3000);
    BMC_PRINTLN("FAS Sync Version 1.0");
  }
  // PUBLIC

  void update(){
    // search for response from FAS device, try up to 10 times every 5 seconds
    // this message will be broadcast on all MIDI ports except USB and BLE (if available)
    if(flags.read(BMC_FAS_FLAG_DEVICE_SEARCH)){
      if(attempts<10 && findDeviceTimer.complete()){
        BMC_PRINTLN(">> Looking for FAS Device <<");
        sendDeviceSearch();
        findDeviceTimer.start(5000);
        attempts++;
      }
      return;
    }

    if(tunerTimeout.complete()){
      flags.off(BMC_FAS_FLAG_TUNER_ACTIVE);
      if(midi.callback.fasTunerStateChange){
        midi.callback.fasTunerStateChange(false);
      }
      BMC_PRINTLN("--> FAS TUNER OFF");
    }
    if(!connected()&&!syncing()){
      if(startSyncTimer.complete()){
        startSyncTimer.start(3000);
        requestFirmware();
      }
    }
    presetSyncQueue();
  }
  void setSyncedParameter(uint8_t slot, uint8_t block, uint8_t parameter){
    device.paramSet(slot, block, parameter);
  }
  uint16_t getSyncedParameterValue(uint8_t block, uint8_t parameter){
    return device.paramGetValue(block, parameter);
  }
  uint16_t getSyncedParameterValue(uint8_t slot){
    return device.paramGetValue(slot);
  }
  void sendChangeSyncedParameter(uint8_t slot, uint16_t value){
    if(slot>7){
      return;
    }
    uint8_t block = device.parameters[slot]>>8;
    uint8_t param = device.parameters[slot] & 0xFF;
    if(block==0&&param==0){
      return;
    }
    device.paramReceived(block, param, value);
    controlBlockParameter(block, param, value, true);
  }
  bool incoming(BMCMidiMessage& message){
    return parseincoming(message);
  }
  bool isTunerActive(){
    return flags.read(BMC_FAS_FLAG_TUNER_ACTIVE);
  }
  bool tempoReceived(){
    return flags.toggleIfTrue(BMC_FAS_FLAG_TEMPO_RECEIVED);
  }
  void getTunerData(BMCTunerData& buff){
    buff = tunerData;
  }
  void toggleTuner(){
    sendControlChange(BMC_FAS_CC_TUNER, isTunerActive()?0:127);
  }
  void tapTempo(){
    sendControlChange(BMC_FAS_CC_TAP_TEMPO, 127);
  }
  bool connected(){
    return flags.read(BMC_FAS_FLAG_CONNECTED);
  }
  bool syncing(){
    return flags.read(BMC_FAS_FLAG_SYNCING);
  }
  bool connect(){
    if(connected()){
      return false;
    }
    BMC_PRINTLN("--> FAS Connect");
    flags.on(BMC_FAS_FLAG_DEVICE_SEARCH);
    attempts = 0;
    findDeviceTimer.trigger();
    return true;
  }
  bool disconnect(){
    if(!connected()){
      return false;
    }
    BMC_PRINTLN("--> FAS Disconnect");
    sendDisconnect();
    device.reset();
    flags.reset();
    findDeviceTimer.stop();
    startSyncTimer.stop();
    resyncTimer.stop();
    tunerTimeout.stop();
    tunerData.reset();
    device.reset();
    attempts = 0;
    if(midi.callback.fasConnection){
      midi.callback.fasConnection(false);
    }
    return true;
  }
  void getPresetName(char* str){
    if(connected()){
      strcpy(str, device.presetName);
    }
  }
  uint16_t getPresetNumber(){
    if(connected()){
      return device.preset;
    }
    return 0;
  }
  uint8_t getSceneNumber(){
    if(connected()){
      return device.scene;
    }
    return 0;
  }
  bool isBlockEngaged(uint8_t blockId){
    if(connected()){
      return device.blocks.isEngaged(blockId);
    }
    return false;
  }
  bool isBlockBypassed(uint8_t blockId){
    return !isBlockEngaged(blockId);
  }
  bool isBlockY(uint8_t blockId){
    if(connected()){
      return device.blocks.isY(blockId);
    }
    return false;
  }
  bool isBlockX(uint8_t blockId){
    return !isBlockY(blockId);
  }
  void sendSetTempo(uint16_t tempo){
    if(tempo<30 || tempo>250){
      return;
    }
    controlBlockParameter(BMC_FAS_BLOCK_CTR, BMC_FAS_PARAM_CONTROLLERS_TAP_TEMPO, tempo, true);
  }
  // SCENE CONTROL, revert via CC
  bool setSceneNumber(uint8_t scene, bool revert=false){
    if(!connected()){
      return false;
    }
    if(revert){
      flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_SCENE);
      sendControlChange(BMC_FAS_CC_SCENE, scene&0x07);
      return false;
    }
    return controlScene(scene);
  }
  void sceneScroll(bool t_up=true, bool t_endless=true, bool t_revert=false, uint8_t t_min=0, uint8_t t_max=7){
    if(!connected()){
      return;
    }
    BMCScroller <uint8_t> scroller(0, 7);
    setSceneNumber(scroller.scroll(1, t_up, t_endless, device.scene, t_min, t_max), t_revert);
  }

  // Control Effect/Block XY State
  bool setBlockXY(uint8_t blockId, bool y){
    if(canXY(blockId) && connected()){
      BMCMidiMessage message;
      prepSysEx(message, BMC_FAS_FUNC_ID_BLOCK_XY);
      message.appendToSysEx14BitsLSBFirst(blockId);
      message.appendToSysEx7Bits(y);
      message.appendToSysEx7Bits(1);
      sendFractMidiSysEx(message);
      return true;
    }
    return false;
  }
  bool toggleBlockXY(uint8_t blockId){
    //return setBlockXY(blockId, false);
    if(canXY(blockId) && connected()){
      setBlockXY(blockId, device.blocks.isX(blockId));
      return true;
    }
    return false;
  }
  bool setBlockX(uint8_t blockId){
    return setBlockXY(blockId, false);
  }
  bool setBlockY(uint8_t blockId){
    return setBlockXY(blockId, true);
  }

  // Control Effect/Block Bypass State
  bool setBlockState(uint8_t blockId, bool bypass){
    if(canBypass(blockId) && connected()){
      sendSetBlockParameter(blockId, 255, bypass?1:0);
      return true;
    }
    return false;
  }
  bool toggleBlockState(uint8_t blockId){
    if(canBypass(blockId) && connected()){
      setBlockState(blockId, !device.blocks.isBypassed(blockId));
      return true;
    }
    return false;
  }
  bool setBlockEngage(uint8_t blockId){
    return setBlockState(blockId, false);
  }
  bool setBlockBypass(uint8_t blockId){
    return setBlockState(blockId, true);
  }

  // CONTROL BLOCK PARAM
  void sendSetBlockParameter(uint8_t blockId, uint8_t parameterId, uint16_t value){
    controlBlockParameter(blockId, parameterId, value, true);
  }
  void sendGetBlockParameter(uint8_t blockId, uint8_t parameterId){
    controlBlockParameter(blockId, parameterId, 0, false);
  }

  void setPreset(uint16_t value){
    // Send CC#0
    sendControlChange(0, (value>>7) & 0x7F);
    // Send Program Change
    sendProgramChange((value & 0x7F));
  }
  void presetScroll(bool t_up=true, bool t_endless=true, uint16_t t_min=0, uint16_t t_max=7){
    if(!connected()){
      return;
    }
    BMCScroller <uint16_t> scroller(0, device.maxPresets);
    uint16_t inc = scroller.scroll(1, t_up, t_endless, device.preset, t_min, t_max);
    // only send a preset change if we changed to a new preset
    if(device.preset!=inc){
      setPreset(inc);
    }

  }

private:
  // send the message that will trigger a response
  void sendDeviceSearch(){
    if(!flags.read(BMC_FAS_FLAG_DEVICE_SEARCH)){
      return;
    }
    //F0 00 01 74 7F 00 7A F7
    BMCMidiMessage message;
    message.setStatus(BMC_MIDI_SYSTEM_EXCLUSIVE);
    message.appendSysExByte(0x00);
    message.appendSysExByte(0x01);
    message.appendSysExByte(0x74);
    message.appendSysExByte(0x7F);
    message.appendSysExByte(0x00);
    message.appendSysExByte(0x7A);
    midi.sendSysEx(
      B00111110, // send to all ports except USB and BLE
      message.getSysEx(), // the sysex array
      message.size(), // the sysex array length
      false, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      true // should it trigger MIDI Out activity
    );
  }
  // parse incoming Sysex Messages
  bool parseincoming(BMCMidiMessage& message){
    if(flags.read(BMC_FAS_FLAG_DEVICE_SEARCH) && findDeviceTimer.active()){
      if(isFractMessage(message)){
        device.setIdAndPort(message.sysex[4], message.getPort());
        flags.off(BMC_FAS_FLAG_DEVICE_SEARCH);
        attempts = 0;
        findDeviceTimer.stop();
        startSyncTimer.start(250);
        BMC_PRINTLN("*** FAS FOUND DEVICE", device.getId(), device.getPort());
      }
      return false;
    }
    if(!isFractMessage(message) || !isValidPort(message.getPort())){
      return false;
    }

#ifdef BMC_DEBUG
    debugPrintFasMessageInfo(message);
#endif

    // messages that don't have a Checksum
    switch(message.sysex[5]){
      case BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT:
        receivedTempoBeat(message);
        return true;
      case BMC_FAS_FUNC_ID_TUNER_INFO:
        receivedTunerInfo(message);
        return true;
      case BMC_FAS_FUNC_ID_LOOPER:
        receivedLooperInfo(message);
        return true;
      case BMC_FAS_FUNC_ID_BLOCKS_DATA:
        receivedBlocksStates(message);
        return true;
    }
    // the rest require a valid CRC
    if(isValidFasFunction(message.sysex[5]) && !message.validateChecksum()){
      BMC_PRINTLN("!!!  FAS Received Bad CRC  !!!");
      return false;
    }
    switch(message.sysex[5]){
      case BMC_FAS_FUNC_ID_FIRMWARE:
        receivedFirmware(message);
        return true;
      case BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL:
        receivedMidiChannel(message);
        return true;
      case BMC_FAS_FUNC_ID_BLOCK_PARAM:
        receivedBlockParameter(message);
        return true;
      case BMC_FAS_FUNC_ID_CPU:
        receivedCPU(message);
        return true;
      case BMC_FAS_FUNC_ID_PRESET_NAME:
        receivedPresetName(message);
        return true;
      case BMC_FAS_FUNC_ID_GET_PRESET_NUMBER:
        receivedPresetNumber(message);
        return true;
      case BMC_FAS_FUNC_ID_SCENE_NUMBER:
        receivedSceneNumber(message);
        return true;
      case BMC_FAS_FUNC_ID_RESYNC:
        device.paramReset();
        BMC_WARN("FAS RE-SYNC RECEIVED");
        receivedReSync(true);
        return true;
      case BMC_FAS_FUNC_ID_BLOCK_XY:
        receivedBlockXY(message);
        return true;
      case BMC_FAS_FUNC_ID_GENERAL_PURPOSE:
        receivedGeneralPurpose(message);
        return true;
    }
    return false;
  }
  // received the resync message
  void receivedReSync(bool quick=false){
    if(resyncTimer.active()){
      return;
    }
    BMC_INFO("FAS RE-SYNC QUEUED");
    flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET);
    flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET_NAME);
    flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_SCENE);

    if(device.id!=BMC_FAS_DEVICE_ID_AX8){
      flags.off(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS);
    }

    flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_PARAMETERS);
    // quick is only true when the actual message is reaceived from the FAS device
    // this function is also used when other messages are received in which case
    // they request updated data, in that case we wait a little longer before resyncing
    // this is in case we're changing scenes quickly etc.
    if(quick){
      resyncTimer.start(500);
    } else {
      resyncTimer.start(1000);
    }
  }
  // General Purpose
  void receivedGeneralPurpose(BMCMidiMessage& message){
    if(!isFractMessage(message, 10)){
      return;
    }
    BMC_PRINTLN("--> FAS GENERAL PURPOSE FUNC:", message.get7Bits(6),"CODE:", message.get7Bits(7));
  }
  // Looper
  void receivedLooperInfo(BMCMidiMessage& message){
    BMC_PRINTLN("--> FAS Looper Info", message.sysex[6], message.sysex[7]);
    device.looper.set(message.sysex[6], message.sysex[7]);
  }
  // Tuner
  void receivedTunerInfo(BMCMidiMessage& message){
    if(connected() && isFractMessage(message, 10)){
      tunerData.note = message.sysex[6];
      tunerData.stringNumber = message.sysex[7];
      tunerData.pitch = map((message.sysex[8]&0x7F), 0, 127, -63, 64);
      tunerNote(tunerData.note, tunerData.noteName);
      tunerTimeout.start(250);
      if(!flags.read(BMC_FAS_FLAG_TUNER_ACTIVE)){
        if(midi.callback.fasTunerStateChange){
          midi.callback.fasTunerStateChange(true);
        }
        flags.on(BMC_FAS_FLAG_TUNER_ACTIVE);
        BMC_PRINTLN("--> FAS TUNER ON");
      }
      if(midi.callback.fasTunerReceived){
        midi.callback.fasTunerReceived(tunerData);
      }
    }
  }
  // Tuner
  void receivedTempoBeat(BMCMidiMessage& message){
    if(connected() && isFractMessage(message, 5)){
      flags.on(BMC_FAS_FLAG_TEMPO_RECEIVED);
    }
  }

  // used when firmware is received
  void receivedFirmware(BMCMidiMessage& message){
    if(!isFractMessage(message, 10) || connected() || syncing()){
      return;
    }
    device.version = (message.get7Bits(6)<<8) | message.get7Bits(7);
    flags.on(BMC_FAS_FLAG_SYNCING);
    startSyncTimer.stop();
    requestMidiChannel();
    BMC_PRINTLN("--> FAS FIRMWARE RECEIVED:", device.version);
  }
  // MIDI Channel received
  void receivedMidiChannel(BMCMidiMessage& message){
    //BMC_PRINTLN("receivedMidiChannel message.size()", message.size());
    if(!isFractMessage(message, 9) || connected() || !syncing()){
      return;
    }
    device.channel = message.get7Bits(6)+1;
#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> FAS CHANNEL RECEIVED:", device.channel);
#endif
    flags.on(BMC_FAS_FLAG_CONNECTED);
    flags.off(BMC_FAS_FLAG_SYNCING);
    if(midi.callback.fasConnection){
      midi.callback.fasConnection(true);
    }
    receivedReSync();
    flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS);
  }
  void receivedBlocksStates(BMCMidiMessage& message){
    if(!isFractMessage(message, 5)){
      return;
    }
    // crc used to know if there's a change within the blocks
    uint8_t crc = device.blocks.getCRC();
    device.blocks.reset();
    for(uint8_t i = 6; i < message.size()-2; i+=5){
      uint32_t block = message.get32BitsLSBFirst(i);
      bool isEngaged = bitRead(block, 0);
      bool isX = bitRead(block, 1);
      uint8_t blockId = (block>>24) & 0xFF;

#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> Received Blocks");
      uint8_t bypassCC = (block>>8) & 0x7F;
      uint8_t xyCC = (block>>16) & 0x7F;
      if(blockId>=100 && blockId<=170){
        BMC_PRINTLN("--> Block", blocksGlobalData[blockId-100].name, blockId, bypassCC, xyCC, isEngaged?"ON":"OFF", isX?"X":"Y");
      }
#endif
      device.blocks.set(blockId, isEngaged, !isX);
    }

    if(midi.callback.fasBlocksChange){
      device.blocks.createCRC();
      if(crc!=device.blocks.getCRC()){
        midi.callback.fasBlocksChange();
      }
    }

    if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS)){
      resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
    }
  }
  // received the current scene number
  void receivedSceneNumber(BMCMidiMessage& message){
    if(!isFractMessage(message, 9)){
      return;
    }
    uint8_t value = message.get7Bits(6);
    if(device.scene!=value){
      flags.on(BMC_FAS_FLAG_SYNC_PARAMETER_SYNC_BEGIN);
      requestSyncParameters();
      if(midi.callback.fasSceneChange){
        midi.callback.fasSceneChange(value);
      }
    }

    device.scene = value;
#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> FAS SCENE NUMBER", device.scene);
#endif

    if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECTING_SCENE)){
      resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
      if(device.id==BMC_FAS_DEVICE_ID_AX8){
        flags.off(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS);
      }
    } else {
      if(device.id!=BMC_FAS_DEVICE_ID_AX8){
        flags.off(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS);
        resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
      }
    }
  }

  // received CPU usage
  void receivedCPU(BMCMidiMessage& message){
    if(!isFractMessage(message, 9)){
      return;
    }
    uint8_t value = message.get7Bits(6);
#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> FAS CPU", value, "%");
#endif
    if(midi.callback.fasCpuReceived){
      midi.callback.fasCpuReceived(value);
    }
  }
  // received a block parameter value
  void receivedBlockParameter(BMCMidiMessage& message){
    if(!isFractMessage(message, 15)){
      return;
    }
    uint8_t blockId = message.get8BitsLSBFirst(6);
    uint8_t paramId = message.get8BitsLSBFirst(8);
    uint16_t value = message.get16BitsLSBFirst(10);
    if(paramId==255){
      device.blocks.set(blockId, (value==0), device.blocks.isY(blockId));
      if(midi.callback.fasBlocksChange && device.blocks.isEngaged(blockId) != (value==0)){
        midi.callback.fasBlocksChange();
      }
#ifdef BMC_FAS_DEBUG
        BMC_PRINTLN("--> FAS BLOCK Bypass Received", blockId, value==0?"engaged":"bypassed");
#endif
    } else {
      device.paramReceived(blockId, paramId, value);
      requestSyncParameters();

      if(midi.callback.fasBlockParameterReceived){
        uint8_t strLen = message.size()-(18+2);
        char str[strLen] = "";
        message.getStringFromSysEx(18, str, strLen);
        midi.callback.fasBlockParameterReceived(blockId, paramId, value, str, strLen);
#ifdef BMC_FAS_DEBUG
          BMC_PRINTLN("--> FAS Block Parameter Received: Block:", blockId,
                      "Param:", paramId, "Value:", value, "Str:", str, strLen);
#endif
      }
    }
  }
  // received the block XY state after it was changed by BMC
  void receivedBlockXY(BMCMidiMessage& message){
    if(!isFractMessage(message, 11)){
      return;
    }
    uint8_t blockId = message.get8BitsLSBFirst(6);
    uint8_t xy = message.get7Bits(8);
    device.blocks.set(blockId, device.blocks.isEngaged(blockId), xy);
    if(midi.callback.fasBlocksChange && device.blocks.isY(blockId)!=xy){
      midi.callback.fasBlocksChange();
    }
#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> FAS BLOCK XY Received", blockId, xy?"Y":"X");
#endif
  }
  // received the current preset number
  void receivedPresetNumber(BMCMidiMessage& message){
    if(!isFractMessage(message, 10)){
      return;
    }
    uint16_t value = message.get14Bits(6);

    if(device.preset!=value){
      device.paramReset();
      if(midi.callback.fasPresetChange){
        midi.callback.fasPresetChange(value);
      }
    }
    device.preset = value;
    BMC_PRINTLN("--> FAS PRESET NUMBER", device.preset);
    if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET)){
      resyncTimer.start(1000);
    } else {
      receivedReSync();
      flags.off(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET);
      flags.on(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS);
      resyncTimer.start(1000);
    }
  }
  // received the current preset name
  void receivedPresetName(BMCMidiMessage& message){
    if(!isFractMessage(message, 30)){
      return;
    }
    strcpy(device.presetName, "");
    message.getStringFromSysEx(6, device.presetName, 32);
#ifdef BMC_FAS_DEBUG
      BMC_PRINTLN("--> FAS PRESET NAME", device.presetName,"size:", message.size());
#endif
    if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET_NAME)){
      resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
    }
    if(midi.callback.fasPresetName){
      midi.callback.fasPresetName(device.presetName);
    }
  }

  bool requestSyncParameters(){
    if(!flags.read(BMC_FAS_FLAG_SYNC_PARAMETER_SYNC_BEGIN)){
      return false;
    }
    for(uint8_t i = 0 ; i < 8 ; i++){
      if(device.parameters[i]==0){
        continue;
      }
      uint8_t block = device.parameters[i] >> 8;
      uint8_t param = device.parameters[i] & 0xFF;
      if(!device.blocks.isLoaded(block) || device.paramIsSynced(block, param)){
        continue;
      }
      BMC_PRINTLN("***** FAS Request Synced Parameters",block, param);
      controlBlockParameter(block, param, 0, false);
      return true;
    }
    flags.off(BMC_FAS_FLAG_SYNC_EXPECTING_PARAMETERS);
    flags.off(BMC_FAS_FLAG_SYNC_PARAMETER_SYNC_BEGIN);
    return false;
  }









  // GET THE FIRMWARE, also activates the 0x21 message sent by the device when
  // there's a change
  void requestFirmware(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_FIRMWARE);
  }
  // Disconnect BMC from fractal device, this should only be sent if BMC_FAS_FUNC_ID_FIRMWARE
  // was sent first
  void sendDisconnect(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_DISCONNECT);
  }
  // MIDI CHANNEL OF THE DEVICE
  void requestMidiChannel(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL);
  }
  // PARSE THE BLOCKS DATA, these are the blocks loaded into the preset
  // and the bypass and X/Y of the block
  void requestBlocksData(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_BLOCKS_DATA);
  }
  // Request the current Scene Number
  bool requestScene(){
    return controlScene(0x7F);
  }
  // PRESET NUMBER
  void requestPresetNumber(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_GET_PRESET_NUMBER);
  }
  // PRESET NAME
  void requestPresetName(){
    sendSimpleSysEx(BMC_FAS_FUNC_ID_PRESET_NAME);
  }


  // Preset Sync Queue
  void presetSyncQueue(){
    // sync preset
    if(connected() && resyncTimer.complete()){
      resyncTimer.start(BMC_FAS_RESYNC_TIMEOUT);
      if(flags.read(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET)){
        requestPresetNumber();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECTING_PRESET_NAME)){
        requestPresetName();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECTING_BLOCKS)){
        requestBlocksData();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECTING_SCENE)){
        requestScene();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECTING_PARAMETERS)){
        flags.on(BMC_FAS_FLAG_SYNC_PARAMETER_SYNC_BEGIN);
        requestSyncParameters();
      } else {
        resyncTimer.stop();
        BMC_INFO("FAS RE-SYNC COMPLETE");
      }
    }
  }
  void sendControlChange(uint8_t cc, uint8_t value){
    if(connected()){
      midi.sendControlChange(device.port, device.channel, cc, value);
    }
  }
  void sendProgramChange(uint8_t program){
    if(connected()){
      midi.sendProgramChange(device.port, device.channel, program);
    }
  }

  void sendFractMidiSysEx(BMCMidiMessage& message, bool crc=true){
    if(device.getPort()==0 || device.getId()==0){
      return;
    }
    if(crc){
      message.createCrc(true);
    }
    midi.sendSysEx(
      device.getPort(), // syn port(s)
      message.getSysEx(), // the sysex array
      message.size(), // the sysex array length
      false, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      true // should it trigger MIDI Out activity
    );
  }
  void sendSimpleSysEx(uint8_t funcId){
    BMCMidiMessage message;
    prepSysEx(message, funcId);
    sendFractMidiSysEx(message);
  }
  // change the scene or request the scene number, this is the actual function
  // that handles all scene requests
  bool controlScene(uint8_t value){
    if(!connected() || (value>7 && value!=0x7F)){
      return false;
    }
    BMCMidiMessage message;
    prepSysEx(message, BMC_FAS_FUNC_ID_SCENE_NUMBER);
    message.appendToSysEx7Bits(value);
    sendFractMidiSysEx(message);
    return true;
  }
  // change or request a block parameter value
  void controlBlockParameter(uint8_t blockId, uint8_t parameterId, uint16_t value, bool write){
    if(!connected() && device.blocks.isLoaded(blockId)){
      return;
    }
    BMCMidiMessage message;
    prepSysEx(message, BMC_FAS_FUNC_ID_BLOCK_PARAM);

    message.appendToSysEx14BitsLSBFirst(blockId);
    message.appendToSysEx14BitsLSBFirst(parameterId);
    message.appendToSysEx16BitsLSBFirst(value);
    message.appendToSysEx7Bits(write);
    sendFractMidiSysEx(message);
  }
  // get a midi message ready to be sent to FAS, mainly the headers
  bool prepSysEx(BMCMidiMessage& message, uint8_t messageId){
    if(device.getId()==0){
      return false;
    }
    message.setStatus(BMC_MIDI_SYSTEM_EXCLUSIVE);
    message.appendToSysEx7Bits(0x00);
    message.appendToSysEx7Bits(0x01);
    message.appendToSysEx7Bits(0x74);
    message.appendToSysEx7Bits(device.getId());
    message.appendToSysEx7Bits(messageId);
    return true;
  }
  bool isFractMessage(BMCMidiMessage& message, uint8_t minLength=5){
    return (message.isSysEx() &&
      message.size()>=minLength &&
      message.sysex[1]==0x00 &&
      message.sysex[2]==0x01 &&
      message.sysex[3]==0x74
    );
  }
  uint8_t getDeviceId(BMCMidiMessage& message){
    if(isFractMessage(message)){
      return message.sysex[4];
    }
    return 0;
  }

  void tunerNote(uint8_t note, char* str){
		switch(note){
			case 0: strcpy(str, "A "); break;
			case 1: strcpy(str, "Bb"); break;
			case 2: strcpy(str, "B "); break;
			case 3: strcpy(str, "C "); break;
			case 4: strcpy(str, "C#"); break;
			case 5: strcpy(str, "D "); break;
			case 6: strcpy(str, "Eb"); break;
			case 7: strcpy(str, "E "); break;
			case 8: strcpy(str, "F "); break;
			case 9: strcpy(str, "F#"); break;
			case 10: strcpy(str, "G "); break;
			case 11: strcpy(str, "G#"); break;
		}
	}
  void findBlockData(uint8_t id, BMCFasBlocks& block){
    if(!isValidBlockId(id)){
      return;
    }
    id -= 100;
    block.id = blocksGlobalData[id].id;
    block.index = blocksGlobalData[id].index;
    block.flags = blocksGlobalData[id].flags;
    strcpy(block.name, blocksGlobalData[id].name);
  }
  void findBlockName(uint8_t id, char* str){
    if(!isValidBlockId(id)){
      return;
    }
    strcpy(str, blocksGlobalData[id-100].name);
  }
  bool findBlockIndex(uint8_t id){
    if(!isValidBlockId(id)){
      return 0;
    }
    return blocksGlobalData[id-100].index;
  }


  // this is the data for blocks, this is used to determine if
  // block is available on the device loaded then to either bypass/XY the block
  // total: 71, totalUsable: 64
  // id, shortname(4), index, flags
  // flag bits: (LSB)
  //        0 can bypass
  //        1 can X/Y on axe fx II
  //        2 can X/Y on axe fx IIXL+
  //        3 can X/Y on AX8
  //        6 Available on AX8
  //        7 usable by BMC
  bool canBypass(uint8_t id){
    if(!isValidBlockId(id)){
      return false;
    }
    uint8_t flags = blocksGlobalData[id-100].flags;
    // if the device is synced
    if(device.getId() != 0){
      // if we're synced to an AX8 but the block is NOT available on AX8 return false
      if(device.getId()==8 && !bitRead(flags, 6)){
        return false;
      }
      return bitRead(flags, 0);
    }
    return false;
  }
  bool canXY(uint8_t id){
    if(!isValidBlockId(id)){
      return false;
    }
    uint8_t flags = blocksGlobalData[id-100].flags;
    // if the device is synced
    if(device.getId() != 0){
      // if we're synced to an AX8 but the block is NOT available on AX8 return false
      if(device.getId()==8){
        // AX8
        return bitRead(flags, 3);
      } else if(device.getId()==3){
        // Axe FX II
        return bitRead(flags, 1);
      } else if(device.getId()==6 || device.getId()==7){
        // Axe-Fx II XL/+
        return bitRead(flags, 2);
      }
    }
    return false;
  }
  bool isValidBlockId(uint8_t id){
    return (id>=100 && id<=170);
  }
  bool isValidPort(uint8_t port){
    return port==device.getPort();
  }
  bool isValidDevice(uint8_t id){
    // Fractal Device ID, only AX8, Axe-Fx II, Axe-Fx II XL and Axe-Fx II XL+ supported at the moment
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
    return (id==3 || (id>=6 && id<=8));
  }

  // this is the data for blocks, this is used to determine if
  // block is available on the device loaded then to either bypass/XY the block
  // total: 71, totalUsable: 64
  // id, shortname(4), index, flags
  // flag bits: (LSB)
  //        0 can bypass
  //        1 can X/Y on axe fx II
  //        2 can X/Y on axe fx IIXL+
  //        3 can X/Y on AX8
  //        4 reserved
  //        5 reserved
  //        6 Available on AX8
  //        7 usable by BMC
  const BMCFasBlocks blocksGlobalData[71] = {
    {100, "CPR", 0,  205},
    {101, "CPR", 1,  141},
    {102, "GEQ", 0,  197},
    {103, "GEQ", 1,  197},
    {104, "PEQ", 0,  197},
    {105, "PEQ", 1,  197},
    {106, "AMP", 0,  207},
    {107, "AMP", 1,  143},
    {108, "CAB", 0,  207},
    {109, "CAB", 1,  143},
    {110, "REV", 0,  207},
    {111, "REV", 1,  143},
    {112, "DLY", 0,  207},
    {113, "DLY", 1,  207},
    {114, "MTD", 0,  207},
    {115, "MTD", 1,  143},
    {116, "CHO", 0,  207},
    {117, "CHO", 1,  143},
    {118, "FLG", 0,  207},
    {119, "FLG", 1,  143},
    {120, "ROT", 0,  207},
    {121, "ROT", 1,  143},
    {122, "PHA", 0,  207},
    {123, "PHA", 1,  143},
    {124, "WAH", 0,  207},
    {125, "WAH", 1,  143},
    {126, "FRM", 0,  193},
    {127, "VOL", 0,  193},
    {128, "TRM", 0,  205},
    {129, "TRM", 1,  141},
    {130, "PIT", 0,  207},
    {131, "FIL", 0,  201},
    {132, "FIL", 1,  201},
    {133, "DRV", 0,  207},
    {134, "DRV", 1,  207},
    {135, "ENH", 0,  193},
    {136, "FXL", 0,  193},
    {137, "MIX", 0,  0},
    {138, "MIX", 1,  0},
    {139, "ING", 0,  64},
    {140, "OUT", 0,  64},
    {141, "CTR", 0,  64},
    {142, "SND", 0,  0},
    {143, "RTN", 0,  0},
    {144, "SYN", 0,  193},
    {145, "SYN", 1,  129},
    {146, "VOC", 0,  129},
    {147, "MGT", 0,  129},
    {148, "XVR", 0,  129},
    {149, "XVR", 1,  129},
    {150, "GTE", 0,  205},
    {151, "GTE", 1,  141},
    {152, "RNG", 0,  193},
    {153, "PIT", 1,  143},
    {154, "MBC", 0,  129},
    {155, "MBC", 1,  129},
    {156, "QCH", 0,  129},
    {157, "QCH", 1,  129},
    {158, "RES", 0,  129},
    {159, "RES", 1,  129},
    {160, "GEQ", 2,  133},
    {161, "GEQ", 3,  133},
    {162, "PEQ", 2,  133},
    {163, "PEQ", 3,  133},
    {164, "FIL", 2,  137},
    {165, "FIL", 3,  137},
    {166, "VOL", 1,  193},
    {167, "VOL", 2,  129},
    {168, "VOL", 3,  129},
    {169, "LPR", 0,  193},
    {170, "TMA", 0,  129}
  };
};

#endif
#endif
