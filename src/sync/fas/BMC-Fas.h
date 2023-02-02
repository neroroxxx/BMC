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
  also set "SEND REALTIME SYSEX" to ALL if you want to use the tuner and tempo beat led

  Currently only supports Axe Fx II/XL/+ and AX8

  Support for Axe Fx III and FM3 is planned for the future
*/
#ifndef BMC_FAS_H
#define BMC_FAS_H

#include "utility/BMC-Def.h"

#if defined(BMC_USE_FAS)

#include "midi/BMC-Midi.h"
#include "sync/fas/BMC-Fas-Def.h"
#include "sync/fas/BMC-Fas-Struct.h"

#define BMC_FAS_FLAG_DEVICE_SEARCH                0
#define BMC_FAS_FLAG_CONNECTED                    1
#define BMC_FAS_FLAG_CONNECTION_CHANGED           2
#define BMC_FAS_FLAG_SYNCING                      3
#define BMC_FAS_FLAG_LOOPER_ACTIVE                4
#define BMC_FAS_FLAG_SYNC_EXPECT_PRESET           5
#define BMC_FAS_FLAG_SYNC_EXPECT_PRESET_NAME      6
#define BMC_FAS_FLAG_SYNC_EXPECT_SCENE            7
#define BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS           8
#define BMC_FAS_FLAG_SYNC_EXPECT_PARAMETERS       9
#define BMC_FAS_FLAG_SYNC_PARAM_SYNC_BEGIN        10
#define BMC_FAS_FLAG_TEMPO_RECEIVED               11
#define BMC_FAS_FLAG_LOOPER_TRACK_AVAILABLE       12
#define BMC_FAS_FLAG_CONNECTION_LOST              13


#define BMC_FAS_TUNER_FLAG_ACTIVE                 0
#define BMC_FAS_TUNER_FLAG_FLAT                   1
#define BMC_FAS_TUNER_FLAG_FLATTER                2
#define BMC_FAS_TUNER_FLAG_FLATTEST               3
#define BMC_FAS_TUNER_FLAG_SHARP                  4
#define BMC_FAS_TUNER_FLAG_SHARPER                5
#define BMC_FAS_TUNER_FLAG_SHARPEST               6


#define BMC_FAS_RESYNC_TIMEOUT 250
#define BMC_FAS_RESYNC_QUEUE_TIMEOUT 250
#define BMC_FAS_CONNECTION_LOST_TIMEOUT 5000

// function id list for Axe Fx II and AX8
#define BMC_FAS_FUNC_ID_BLOCK_PARAM           0x02
#define BMC_FAS_FUNC_ID_FIRMWARE              0x08
#define BMC_FAS_FUNC_ID_TUNER_INFO            0x0D
#define BMC_FAS_FUNC_ID_BLOCKS_DATA           0x0E
#define BMC_FAS_FUNC_ID_PRESET_NAME           0x0F
#define BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT       0x10
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

// for Axe Fx 3
#define BMC_FAS_FUNC_ID_BLOCK_PARAM           0x02
#define BMC_FAS_FUNC_ID_FIRMWARE              0x08
#define BMC_FAS_FUNC_ID_TUNER_INFO            0x0D
#define BMC_FAS_FUNC_ID_BLOCKS_DATA           0x0E
#define BMC_FAS_FUNC_ID_PRESET_NAME           0x0F
#define BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT       0x10
#define BMC_FAS_FUNC_ID_BLOCK_CHANNEL         0x11
#define BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL      0x17
#define BMC_FAS_FUNC_ID_RESYNC                0x21
#define BMC_FAS_FUNC_ID_LOOPER                0x23
#define BMC_FAS_FUNC_ID_SCENE_NUMBER          0x29
#define BMC_FAS_FUNC_ID_SET_PRESET_NUMBER     0x3C
#define BMC_FAS_FUNC_ID_DISCONNECT            0x42
#define BMC_FAS_FUNC_ID_GENERAL_PURPOSE       0x64

class BMCFas {
private:
  BMCMidi& midi;
  BMCGlobals& globals;
  BMCFlags <uint16_t> flags;
  BMCFlags <uint8_t> tunerFlags;
  BMCTimer findDeviceTimer;
  BMCTimer startSyncTimer;
  BMCTimer resyncTimer;
  BMCTimer tunerTimeout;
  BMCTimer looperTimeout;
  BMCTimer connectionLost;
  BMCFasData device;
  BMCTunerData tunerData;
  uint8_t attempts = 0;
  bool isAxe3(uint8_t id){
    return (id==BMC_FAS_DEVICE_ID_AXE_FX_III || id==BMC_FAS_DEVICE_ID_FM3);
  }

#ifdef BMC_DEBUG
  String debugPrintDeviceName(uint8_t id);
  String debugPrintPreset();
  void debugPrintFasMessageInfo(BMCMidiMessage& message);
  bool isValidFasFunction(uint8_t funcId);
#endif

  void timeConnectionStart(){
    flags.off(BMC_FAS_FLAG_CONNECTION_LOST);
    connectionLost.start(BMC_FAS_CONNECTION_LOST_TIMEOUT);
  }

public:
  BMCFas(BMCMidi& t_midi);

  void begin();
  void update();
  bool incoming(BMCMidiMessage& message);

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

  bool isTunerActive(){
    return tunerFlags.read(BMC_FAS_TUNER_FLAG_ACTIVE);
  }
  bool tunerInTune(){
    return isTunerActive() && (!tunerFlat() && !tunerSharp());
  }
  bool tunerFlat(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_FLAT);
  }
  bool tunerFlatter(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_FLATTER);
  }
  bool tunerFlattest(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_FLATTEST);
  }
  bool tunerSharp(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_SHARP);
  }
  bool tunerSharper(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_SHARPER);
  }
  bool tunerSharpest(){
    return isTunerActive() && tunerFlags.read(BMC_FAS_TUNER_FLAG_SHARPEST);
  }
  bool tempoReceived(){
    return flags.toggleIfTrue(BMC_FAS_FLAG_TEMPO_RECEIVED);
  }
  void getTunerData(BMCTunerData& buff){
    buff = tunerData;
  }
  bool connected(){
    return flags.read(BMC_FAS_FLAG_CONNECTED);
  }
  bool syncing(){
    return flags.read(BMC_FAS_FLAG_SYNCING);
  }
  bool looperEnable(bool value){
    if(value!=device.getLooperState()){
      device.looper.changeState(value);
      sendBasicSysEx(BMC_FAS_FUNC_ID_LOOPER, value?1:0);
      return true;
    }
    return false;
  }
  void looperControl(uint8_t cmd){
    if(!connected()){
      return;
    }
    switch(cmd){
      case BMC_FAS_LOOPER_CONTROL_STOP:{
        if(device.looper.getStates()>0){
          sendControlChange(BMC_FAS_CC_LOOPER_RECORD, 0);
          sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 0);
          sendControlChange(BMC_FAS_CC_LOOPER_DUB, 0);
        }
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_RECORD:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_RECORDING)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_RECORD, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_PLAY:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_PLAYING)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_PLAY, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_ONCE:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_ONCE)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_ONCE, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_OVERDUB:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_OVERDUBBING)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_DUB, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_REVERSE:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_REVERSED)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_REVERSE, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_HALF:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_HALF)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_HALF, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_UNDO:{
        uint8_t state = device.looper.getStates(BMC_FAS_LOOPER_STATE_UNDO)?0:127;
        sendControlChange(BMC_FAS_CC_LOOPER_UNDO, state);
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_REC_PLAY_DUB:
      case BMC_FAS_LOOPER_CONTROL_REC_DUB_PLAY:{
        //cmd==BMC_FAS_LOOPER_CONTROL_REC_DUB_PLAY
        if(device.looper.getStates()==0){
          if(flags.read(BMC_FAS_FLAG_LOOPER_TRACK_AVAILABLE)){
            sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 127);
          } else {
            sendControlChange(BMC_FAS_CC_LOOPER_RECORD, 127);
          }
        } else if(device.looper.getStates(BMC_FAS_LOOPER_STATE_RECORDING)){
          if(cmd==BMC_FAS_LOOPER_CONTROL_REC_DUB_PLAY){
            sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 127);
            sendControlChange(BMC_FAS_CC_LOOPER_DUB, 127);
          } else {
            sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 127);
          }
        } else if(device.looper.getStates(BMC_FAS_LOOPER_STATE_PLAYING)){
          if(device.looper.getStates(BMC_FAS_LOOPER_STATE_OVERDUBBING)){
            sendControlChange(BMC_FAS_CC_LOOPER_DUB, 0);
          } else {
            sendControlChange(BMC_FAS_CC_LOOPER_DUB, 127);
          }
        }
        break;
      }
      case BMC_FAS_LOOPER_CONTROL_CLEAR:{
        flags.off(BMC_FAS_FLAG_LOOPER_TRACK_AVAILABLE);
        if(device.looper.getStates()>0){
          looperControl(BMC_FAS_LOOPER_CONTROL_STOP);
        }
        break;
      }
      // stop if either playing/recording/dubbing, otherwise play
      case BMC_FAS_LOOPER_CONTROL_PLAY_STOP:{
        if(device.looper.getStates()>0){
          sendControlChange(BMC_FAS_CC_LOOPER_RECORD, 0);
          sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 0);
          sendControlChange(BMC_FAS_CC_LOOPER_DUB, 0);
        } else {
          sendControlChange(BMC_FAS_CC_LOOPER_PLAY, 127);
        }
        break;
      }
    }
  }
  void getBlockName(uint8_t id, char* str){
    findBlockName(id, str);
  }
  bool looperGetState(){
    return device.looper.isEnabled();
  }
  bool looperStatus(uint8_t cmd=255){
    return device.looper.getStates(cmd);
  }
  bool looperPlaying(){
    return looperStatus(BMC_FAS_LOOPER_STATE_PLAYING);
  }
  bool looperRecording(){
    return looperStatus(BMC_FAS_LOOPER_STATE_RECORDING);
  }
  bool looperDubbing(){
    return looperStatus(BMC_FAS_LOOPER_STATE_OVERDUBBING);
  }
  bool looperRecordingOrDubbing(){
    return looperRecording() || looperDubbing();
  }
  bool looperReversed(){
    return looperStatus(BMC_FAS_LOOPER_STATE_REVERSED);
  }
  bool looperHalf(){
    return looperStatus(BMC_FAS_LOOPER_STATE_HALF);
  }
  bool looperStoppedWithTrack(){
    return looperStopped() && looperTrackRecorded();
  }
  bool looperStopped(){
    return device.looper.getStates()==0;
  }
  bool looperTrackRecorded(){
    return flags.read(BMC_FAS_FLAG_LOOPER_TRACK_AVAILABLE);
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
    // turn off looper stream if it's on
    looperEnable(false);
    sendBasicSysEx(BMC_FAS_FUNC_ID_DISCONNECT);
    device.reset();
    flags.reset();
    tunerFlags.reset();
    findDeviceTimer.stop();
    startSyncTimer.stop();
    resyncTimer.stop();
    tunerTimeout.stop();
    looperTimeout.stop();
    tunerData.reset();
    device.reset();
    attempts = 0;
    flags.on(BMC_FAS_FLAG_CONNECTION_CHANGED);
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

  // Toggle the tuner state
  void toggleTuner(){
    sendControlChange(BMC_FAS_CC_TUNER, isTunerActive()?0:127);
  }
  // Turn tuner on
  void tunerOn(){
    if(!isTunerActive()){
      sendControlChange(BMC_FAS_CC_TUNER, 127);
    }
  }
  // Turn tuner off
  void tunerOff(){
    if(isTunerActive()){
      sendControlChange(BMC_FAS_CC_TUNER, 0);
    }
  }
  // send a tap tempo cc
  void tapTempo(){
    sendControlChange(BMC_FAS_CC_TAP_TEMPO, 127);
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
      flags.on(BMC_FAS_FLAG_SYNC_EXPECT_SCENE);
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
    BMC_PRINTLN(">>>>>>>>>>>>>>>>>>>>>", blockId, canXY(blockId), connected());
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
  uint16_t getMaxPresets(){
    return device.maxPresets;
  }

  uint8_t getConnectedDeviceId(){
    if(connected()){
      return device.getId();
    }
    return 0;
  }
  bool connectionStateChanged(){
    return flags.toggleIfTrue(BMC_FAS_FLAG_CONNECTION_CHANGED);
  }
  uint8_t getPresetBankNumber(){
    switch(device.id){
      case BMC_FAS_DEVICE_ID_AXE_FX_II:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS:
        return ((device.preset>>7) & 0x7F);
      case BMC_FAS_DEVICE_ID_AX8:{
        return (device.preset>>3);
      }
    }
    return 0;
  }
  uint8_t getPresetInBankNumber(){
    switch(device.id){
      case BMC_FAS_DEVICE_ID_AXE_FX_II:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:
      case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS:{
        return (device.preset & 0x7F);
      }
      case BMC_FAS_DEVICE_ID_AX8:{
        return (device.preset & 0x07);
      }
    }
    return 0;
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
  // received the resync message
  void receivedReSync(bool quick=false){
    if(resyncTimer.active()){
      return;
    }
    BMC_INFO("FAS RE-SYNC QUEUED");
    flags.on(BMC_FAS_FLAG_SYNC_EXPECT_PRESET);
    flags.on(BMC_FAS_FLAG_SYNC_EXPECT_PRESET_NAME);
    flags.on(BMC_FAS_FLAG_SYNC_EXPECT_SCENE);
/*
    if(device.id!=BMC_FAS_DEVICE_ID_AX8){
      flags.off(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
    }
*/
    flags.on(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
    flags.on(BMC_FAS_FLAG_SYNC_EXPECT_PARAMETERS);
    // quick is only true when the actual message is reaceived from the FAS device
    // this function is also used when other messages are received in which case
    // they request updated data, in that case we wait a little longer before resyncing
    // this is in case we're changing scenes quickly etc.
    if(quick){
      resyncTimer.start(250);
    } else {
      resyncTimer.start(750);
    }
  }
  bool requestSyncParameters(){
    if(!flags.read(BMC_FAS_FLAG_SYNC_PARAM_SYNC_BEGIN)){
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
    flags.off(BMC_FAS_FLAG_SYNC_EXPECT_PARAMETERS);
    flags.off(BMC_FAS_FLAG_SYNC_PARAM_SYNC_BEGIN);
    return false;
  }
  // Request the current Scene Number
  bool requestScene(){
    return controlScene(0x7F);
  }
  // PRESET NUMBER
  void requestPresetNumber(){
    sendBasicSysEx(BMC_FAS_FUNC_ID_GET_PRESET_NUMBER);
  }
  // PRESET NAME
  void requestPresetName(){
    sendBasicSysEx(BMC_FAS_FUNC_ID_PRESET_NAME);
  }


  // Preset Sync Queue
  void presetSyncQueue(){
    // sync preset
    if(connected() && resyncTimer.complete()){
      resyncTimer.start(BMC_FAS_RESYNC_TIMEOUT);
      if(flags.read(BMC_FAS_FLAG_SYNC_EXPECT_PRESET)){
        requestPresetNumber();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECT_PRESET_NAME)){
        requestPresetName();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS)){
        sendBasicSysEx(BMC_FAS_FUNC_ID_BLOCKS_DATA);
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECT_SCENE)){
        requestScene();
      } else if(flags.read(BMC_FAS_FLAG_SYNC_EXPECT_PARAMETERS)){
        flags.on(BMC_FAS_FLAG_SYNC_PARAM_SYNC_BEGIN);
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

  void sendCustomFasSysEx(uint8_t funcId, uint8_t * bytes, uint8_t len, bool crc=true){
    if(!connected()){
      return;
    }
    BMCMidiMessage message;
    prepSysEx(message, funcId);

    for(uint8_t i=0;i<len;i++){
      message.appendToSysEx7Bits(bytes[i]);
    }
    sendFractMidiSysEx(message, crc);
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
  void sendBasicSysEx(uint8_t funcId, uint8_t extraByte=255){
    BMCMidiMessage message;
    prepSysEx(message, funcId);
    if(extraByte<=0x7F){
      message.appendToSysEx7Bits(extraByte);
    }
    sendFractMidiSysEx(message);
  }
  // change the scene or request the scene number, this is the actual function
  // that handles all scene get/set requests
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
      default: strcpy(str, "??"); break;
		}
    
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
