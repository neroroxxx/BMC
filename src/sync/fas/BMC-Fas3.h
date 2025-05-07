/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Wrapper to some sync/control Fractal Audio Guitar Processors
  
*/
#ifndef BMC_FAS3_H
#define BMC_FAS3_H

#include "utility/BMC-Def.h"

#if defined(BMC_USE_FAS) && defined(BMC_USE_FAS3)

#include "midi/BMC-Midi.h"
#include "sync/fas/BMC-Fas-Def.h"
#include "sync/fas/BMC-Fas3-Struct.h"

#define BMC_FAS3_BLOCKS_COUNT 91

#define BMC_FAS3_FLAG_LOOPER_TRACK_AVAILABLE    0
#define BMC_FAS3_FLAG_FETCH_CURRENT_SCENE       1
#define BMC_FAS3_FLAG_TEMPO_BEAT                2
#define BMC_FAS3_FLAG_FETCH_LOOPER              3
#define BMC_FAS3_FLAG_POLL_SCENE_NAMES          4

#define BMC_FAS3_FETCH_TYPE_7_BIT 0
#define BMC_FAS3_FETCH_TYPE_14_BIT 1
#define BMC_FAS3_FETCH_TYPE_14_AND_7_BIT 2

#if !defined(BMC_FAS3_LOOPER_POLL_TIME)
  #define BMC_FAS3_LOOPER_POLL_TIME 1000
#endif



class BMCFas {
private:
  BMCMidi& midi;
  BMCGlobals& globals;
  BMCFlags <uint16_t> flags;
  BMCFlags <uint8_t> tunerFlags;
  BMCTimer tempoLedTimeout;
  BMCTimer looperTimer;
  BMCFas3Device device;
  BMCFas3Preset preset;
  uint8_t scenePolled = 0;
  bool isFasMessage(BMCMidiMessage& message, uint8_t minLength=5){
    return (message.isSysEx() &&
      message.size() >= minLength &&
      message.sysex[1] == 0x00 &&
      message.sysex[2] == 0x01 &&
      message.sysex[3] == 0x74
    );
  }
  void textFromSysEx(BMCMidiMessage& message, char *buff, uint8_t t_start){
    for(int i = t_start, e=0, n = (message.size()-3) ; i < n ; i++, e++){
      if(i >= 32){
        break;
      }
      buff[e] = (char) message.sysex[i];
    }
  }
  bool validateCrc(BMCMidiMessage& message){
    uint8_t incomingCRC = message.sysex[message.size()-2];
    uint8_t crc = 0;
    for(int i = 0, n = message.size()-2 ; i < n ; i++){
      crc ^= message.sysex[i] & 0x7F;
    }
    #if defined(BMC_DEBUG)
      if(globals.getFasDebug() && crc!=incomingCRC){
        BMC_PRINTNS("> FAS3 BAD CRC (", message.size(),") ");
        for(int i=0;i<message.size();i++){
          BMC_PRINT(message.sysex[i]);
        }
        BMC_PRINTLN("<");
      }
    #endif
    return crc == incomingCRC;
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
  void fetchSysEx(uint8_t funcId){
    fetchSysEx(funcId, 0, 0, 0);
  }
  void fetchSysEx(uint8_t funcId, uint16_t t_value, uint16_t t_value2, uint8_t funcType){
    BMCMidiMessage message;
    prepSysEx(message, funcId);
    if(funcType == BMC_FAS3_FETCH_TYPE_7_BIT){
      // 7-bit value
      message.appendToSysEx7Bits(t_value & 0xFF);
    } else if(funcType == BMC_FAS3_FETCH_TYPE_14_BIT){
      // 14-bit value
      message.appendToSysEx14BitsLSBFirst(t_value);
    } else if(funcType == BMC_FAS3_FETCH_TYPE_14_AND_7_BIT){
      // 14-bit value + 7-bit value
      message.appendToSysEx14BitsLSBFirst(t_value);
      message.appendToSysEx7Bits(t_value2 & 0xFF);
    }
    sendFasSysEx(message);
  }
  void sendFasSysEx(BMCMidiMessage& message, bool appendCrc=true){
    if(device.getPort()==0 || device.getId()==0){
      return;
    }
    if(appendCrc){
      message.createCrc(true);
    }
    midi.sendSysEx(
      device.getPort(), // sync port(s)
      message.getSysEx(), // the sysex array
      message.size(), // the sysex array length
      message.sysex[0]==0xF0, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      true // should it trigger MIDI Out activity
    );
  }
  void fetchPreset(uint16_t t_value=0xFFFF){
    fetchSysEx(BMC_FAS3_FUNC_ID_PRESET_NAME, t_value, 0, BMC_FAS3_FETCH_TYPE_14_BIT);
  }
  void fetchScene(uint8_t t_value=0x7F){
    // flags.write(BMC_FAS3_FLAG_FETCH_CURRENT_SCENE, (t_value == 0x7F));
    if(t_value == 0x7F || t_value < 8){
      fetchSysEx(BMC_FAS3_FUNC_ID_SCENE_NAME, t_value, 0, BMC_FAS3_FETCH_TYPE_7_BIT);
    }
  }
  void fetchBlocks(){
    fetchSysEx(BMC_FAS3_FUNC_ID_BLOCKS);
  }
  void fetchLooper(uint8_t t_value=0x7F){
    // BMC_PRINTLN("fetch looper");
    fetchSysEx(BMC_FAS3_FUNC_ID_LOOPER, t_value, 0, BMC_FAS3_FETCH_TYPE_7_BIT);
  }
  void sendLooperCommand(uint8_t t_value){
    if(t_value < 8){
      // send it and also query it by restarting the timer
      fetchLooper(t_value);
      if(t_value == BMC_FAS_LOOPER_STATE_RECORDING){
        flags.on(BMC_FAS3_FLAG_LOOPER_TRACK_AVAILABLE);
      }
      looperTimer.start(10);
    }
  }

  /*
  BMCMidiMessage message;
  prepSysEx(message, funcId);
  // for 14 bit value
  message.appendToSysEx14BitsLSBFirst(long word);
  // for 7 bit value
  message.appendToSysEx7Bits(0x74);
  sendFasSysEx(message);
  */
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
public:
  BMCTunerData tuner;
  BMCFas(BMCMidi& t_midi):
  midi(t_midi),
  globals(midi.globals){
    
  }
  void begin(){
    // globals.toggleMidiOutDebug();
    BMC_INFO(
      "FAS3 Sync works with Axe-Fx III, FM9, and FM3.",
      "Tested with Axe-Fx III only.",
      "",
      "To enable sync, turn on 'Send Realtime Sysex'.",
      "On the Axe-Fx III front panel, go to:",
      "SETUP > MIDI/Remote > GENERAL",
      "Enable: 'Send Realtime Sysex'",
      "",
      "BMC listens for the Tempo Downbeat message.",
      "",
      "Waiting for the Axe-Fx III to announce itself..."
    );
  }
  void update(){
    if(tuner.timedout()){
      if(midi.callback.fasTunerStateChange){
        midi.callback.fasTunerStateChange(false);
      }
      BMC_PRINTLN("--> FAS3 TUNER: OFF");
    }
    if(device.syncReady()){
      fetchPreset();
      #if defined(BMC_DEBUG)
        if(globals.getFasDebug()){
          BMC_PRINTLN("***********");
          BMC_PRINTLN("FAS3 ReSync");
          BMC_PRINTLN("***********");
        }
      #endif
    }
    if(device.connectionLost()){
      device.disconnect();
      preset.reset();
      tuner.reset();
      looperTimer.stop();
      scenePolled = 0;
      BMC_PRINTLN("FAS3 Connection Lost!");
      midi.flush();
      if(midi.callback.fasConnection){
        midi.callback.fasConnection(false);
      }
    }
    if(tempoLedTimeout.complete()){
      flags.off(BMC_FAS3_FLAG_TEMPO_BEAT);
    }
    if(looperTimer.complete()){
      if(connected()){
        fetchLooper();
      }
      looperTimer.start(BMC_FAS3_LOOPER_POLL_TIME);
    }
  }
  void reassign(){
    enableLooperFetch(false);
  }

  bool incoming(BMCMidiMessage message){
    if(!isFasMessage(message)){
      return false;
    }
    bool hasCrC = true;
    switch(message.sysex[5]){
      case BMC_FAS3_FUNC_ID_TUNER:
      case BMC_FAS3_FUNC_ID_TEMPO:
        hasCrC = false;
        break;
    }
    if(hasCrC && !validateCrc(message)){
      device.reSync(500);
      return false;
    }
    if(message.sysex[5] == BMC_FAS3_FUNC_ID_TEMPO){
      if(!connected()){
        BMC_PRINTLN("");
        BMC_PRINTLN("FAS3 Connecting...");
        
        if(device.connect(message.sysex[4], message.getPort())){
          preset.reset();
        #if defined(BMC_DEBUG)
          char buff[16];
          device.getDeviceName(buff);
          BMC_PRINTLN("");
          BMC_PRINTLN("##############################################");
          BMC_PRINTLN("##############################################");
          BMC_PRINTLN("");
          BMC_PRINTLN("Connected to", buff, "on", BMCTools::printPortsNames(device.getPort()));
          BMC_PRINTLN("");
          BMC_PRINTLN("##############################################");
          BMC_PRINTLN("##############################################");
          BMC_PRINTLN("");
        #endif

          if(midi.callback.fasConnection){
            midi.callback.fasConnection(true);
          }
          device.reSync(10);
          return true;
        }
        return false;
      }
    }
    if(!connected()){
      return false;
    }
    // TO DO: check device id
    switch(message.sysex[5]){
      
      case BMC_FAS3_FUNC_ID_PRESET_NAME:{
          char txt[BMC_FAS_MAX_PRESET_NAME] = "";
          message.getStringFromSysEx(8, txt, message.size()-11);
          preset.setPreset( (message.sysex[6]& 0x7F) | ((message.sysex[7] & 0x7F)<<7), txt);
          if(preset.presetHasChanged()){
            scenePolled = 0;
            fetchScene(scenePolled);
            flags.on(BMC_FAS3_FLAG_POLL_SCENE_NAMES);
            if(midi.callback.fasPresetChange){
              midi.callback.fasPresetChange(preset.getPresetNumber());
            }
          } else {
            fetchScene();
            flags.off(BMC_FAS3_FLAG_POLL_SCENE_NAMES);
          }
          device.reSync();
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              BMC_PRINTLN("FAS3 Preset Received", preset.id, txt);
            }
          #endif
        }
        break;

      case BMC_FAS3_FUNC_ID_SCENE:{
          if(preset.setScene(message.sysex[6])){
            // setScene returns true if the scene number has changed.
            if(midi.callback.fasSceneChange){
              midi.callback.fasSceneChange(preset.getSceneNumber());
            }
          }
          fetchScene();
          
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              BMC_PRINTLN("FAS3 Scene Received", message.sysex[6]);
            }
          #endif
          break;
        }
        break;

      case BMC_FAS3_FUNC_ID_SCENE_NAME:{
          char txt[BMC_FAS3_MAX_SCENE_NAME] = "";
          uint8_t nLen = message.size()-11;
          message.getStringFromSysEx(7, txt, nLen>BMC_FAS3_MAX_SCENE_NAME ? BMC_FAS3_MAX_SCENE_NAME : nLen);
          preset.setScene(message.sysex[6], txt, (scenePolled == 0x7F));
          if(flags.read(BMC_FAS3_FLAG_POLL_SCENE_NAMES)){
            if(scenePolled < 7){
              scenePolled++;
            } else {
              scenePolled = 0x7F;
              flags.off(BMC_FAS3_FLAG_POLL_SCENE_NAMES);
            }
            fetchScene(scenePolled);
          } else {
            fetchBlocks();
          }
          device.reSync();
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              BMC_PRINTLN("FAS3 Scene Name Received", message.sysex[6], txt);
            }
          #endif
        }
        break;

      case BMC_FAS3_FUNC_ID_BLOCKS:{
          if(preset.setLastBlocksCrc(message.getCrc())){
            if(midi.callback.fasBlocksChange){
              midi.callback.fasBlocksChange();
            }
          }
          
          for(uint16_t i = 6, n = (message.size()-2); i < n; i += 3){
            uint8_t id = message.get14BitsLSBFirst(i);
            uint8_t flags = message.sysex[i+2];
            if(id < BMC_FAS_BLOCK_IN_1 || id > BMC_FAS_BLOCK_IRP_2){
              continue;
            }
            // bitRead(flags, 0); // 0 = engaged, 1 = bypassed
            // ((flags >> 1) & 0x07); // channel
            // ((flags >> 4) & 0x07); // number of channels supported for this effect (0-7).
            for(int e = 0 ; e < BMC_FAS3_BLOCKS_COUNT ; e++){
              if(blocksInfo[e].id == id){
                preset.setBlockData(e, flags);
                break;
              }
            }
          }
          
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              BMC_PRINTLN("FAS3 Blocks Received");
            }
          #endif
          device.reSync();
        }
        break;
      case BMC_FAS3_FUNC_ID_BYPASS:{
          uint16_t blockId = message.get14BitsLSBFirst(6);
          bool value = message.sysex[8]>0;
          for(int e = 0 ; e < BMC_FAS3_BLOCKS_COUNT ; e++){
            if(blocksInfo[e].id == blockId){
              preset.setBlockBypass(e, value);
              #if defined(BMC_DEBUG)
                if(globals.getFasDebug()){
                  BMC_PRINTLN("FAS3 Block Bypass Received", blocksInfo[e].name, value);
                }
              #endif
              preset.setBlockBypass(e, value);
              break;
            }
          }
          device.reSync();
        }
        break;
      case BMC_FAS3_FUNC_ID_CHANNEL:{
          uint16_t blockId = message.get14BitsLSBFirst(6);
          uint8_t value = message.sysex[8];
          for(int e = 0 ; e < BMC_FAS3_BLOCKS_COUNT ; e++){
            if(blocksInfo[e].id == blockId){
              preset.setBlockChannel(e, value);
              #if defined(BMC_DEBUG)
                if(globals.getFasDebug()){
                  BMC_PRINTLN("FAS3 Block Channel Received", blocksInfo[e].name, value);
                }
              #endif
              break;
            }
          }
          device.reSync();
        }
        break;

      case BMC_FAS3_FUNC_ID_LOOPER:{
          device.looper.set(message.sysex[6], 0);
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              Serial.print("******** Looper ");
              Serial.println(message.sysex[6], BIN);
              if(device.looper.recording()){
                BMC_PRINTLN("******** - Recording");
              }
              if(device.looper.playing()){
                BMC_PRINTLN("******** - Playing");
              }
              if(device.looper.overdubbing()){
                BMC_PRINTLN("******** - Overdubbing");
              }
            }
          #endif
        }
        break;

      case BMC_FAS3_FUNC_ID_TUNER: {
          globals.clearMidiInActivity();
          tuner.setData(message.sysex[6], message.sysex[7], message.sysex[8]);
          if(!tuner.isOn()){
            if(midi.callback.fasTunerStateChange){
              midi.callback.fasTunerStateChange(true);
            }
            BMC_PRINTLN("--> FAS3 TUNER: ON");
          }
          if(midi.callback.fasTunerReceived){
            midi.callback.fasTunerReceived(tuner);
          }
          #if defined(BMC_DEBUG)
            if(globals.getFasDebug()){
              BMC_PRINTLN("FAS3 Tuner Received", message.sysex[6], message.sysex[7], message.sysex[8]);
            }
          #endif
        }
        break;
      case BMC_FAS3_FUNC_ID_TEMPO:{
          globals.clearMidiInActivity();
          device.connectionActive();
          flags.on(BMC_FAS3_FLAG_TEMPO_BEAT);
          tempoLedTimeout.start(75);
        }
        break;
    }
    return false;
  }

  // ******************
  // ****   GENERAL
  // ******************
  bool connected(){
    return device.connected();
  }
  void toggleConnection(){
    if(connected()){
      // disconnect();
    } else {
      // connect();
    }
  }
  bool connect(){
    if(connected()){
      return false;
    }
    // handle connection
    return true;
  }
  bool disconnect(){
    if(!connected()){
      return false;
    }
    BMC_PRINTLN("--> FAS3 Disconnect");
    device.disconnect();
    tuner.reset();
    if(midi.callback.fasConnection){
      midi.callback.fasConnection(false);
    }
    return true;
  }
  uint8_t getConnectedDeviceId(){
    return device.id;
  }
  bool connectionStateChanged(){
    return device.connectionChanged();
  }
  void setMidiChannel(uint8_t t_value){
    device.setMidiChannel(t_value);
  }




  


  // ******************
  // ****   PRESETS
  // ******************
  uint16_t getMaxPresets(){
    if(!connected()){
      return 0;
    }
    return device.max;
  }
  uint16_t getPresetNumber(){
    if(!connected()){
      return 0;
    }
    return preset.id;
  }
  void getPresetName(char * buff){
    if(connected()){
      strcpy(buff, preset.name);
    } else {
      strcpy(buff, "Not Connected");
    }
  }
  uint8_t getPresetBankNumber(){
    if(!connected()){
      return 0;
    }
    return (preset.id >> 7) & 0x7F;
  }
  uint8_t getPresetInBankNumber(){
    if(!connected()){
      return 0;
    }
    return preset.id & 0x7F;
  }
  void setPreset(uint16_t t_value){
    setPresetNumber(t_value);
  }
  void setPresetNumber(uint16_t t_value){
    if(!connected()){
      return;
    }
    uint8_t bank = (t_value >> 7) & 0x7F;
    uint8_t preset = t_value & 0x7F;
    sendControlChange(0, bank);
    sendProgramChange(preset);

    device.reSync(1);
  }
  void presetScroll(bool t_direction=true, bool t_wrap=true, uint16_t t_min=0, uint16_t t_max=7){
    if(!connected()){
      return;
    }

    uint16_t newValue = BMCCycle<uint16_t>(0, getMaxPresets())
      .withAmount(1)
      .withDirection(t_direction)
      .withWrap(t_wrap)
      .withValue(preset.id)
      .withRange(t_min, t_max)
      .process();
      
    // only send a preset change if we changed to a new preset
    if(preset.id != newValue){
      setPresetNumber(newValue);
    }
  }

  // ******************
  // ****   SCENES
  // ******************
  uint8_t getSceneNumber(){
    if(!connected()){
      return 0;
    }
    return preset.scene;
  }
  void getSceneName(char * buff){
    if(connected()){
      preset.getSceneName(buff);
    } else {
      strcpy(buff, "Not Connected");
    }
  }
  void getSceneName(uint8_t t_scene, char * buff){
    if(connected()){
      preset.getSceneName(t_scene, buff);
    } else {
      strcpy(buff, "Not Connected");
    }
  }
  void setScene(uint8_t t_value, bool t_revert=false){
    if(!connected()){
      return;
    }
    setSceneNumber(t_value, t_revert);
  }
  void setSceneNumber(uint8_t t_value, bool t_revert=false){
    if(!connected()){
      return;
    }
    // if(t_value!= preset.getSceneNumber()){
    //   preset.setScene(t_value);
    // }
    fetchSysEx(BMC_FAS3_FUNC_ID_SCENE, t_value, 0, BMC_FAS3_FETCH_TYPE_7_BIT);
  }
  void sceneScroll(bool t_direction=true, bool t_wrap=true, bool t_revert=false, uint8_t t_min=0, uint8_t t_max=7){
    if(!connected()){
      return;
    }
    
    uint8_t nextScene = BMCCycle<uint8_t>(0, 7)
      .withAmount(1)
      .withDirection(t_direction)
      .withWrap(t_wrap)
      .withValue(preset.scene)
      .withRange(t_min, t_max)
      .process();

    setSceneNumber(nextScene, t_revert);
  }

  // ******************
  // ****   BLOCKS
  // ******************

  

  void toggleBlockState(uint16_t n){
    if(!connected()){
      return;
    }
    if(isBlockEngaged(n)){
      setBlockBypass(n);
    } else {
      setBlockEngage(n);
    }
  }
  void setBlockBypass(uint16_t t_block){
    if(connected()){
      fetchSysEx(BMC_FAS3_FUNC_ID_BYPASS, t_block, 1, BMC_FAS3_FETCH_TYPE_14_AND_7_BIT);
    }
  }
  void setBlockEngage(uint16_t t_block){
    if(connected()){
      fetchSysEx(BMC_FAS3_FUNC_ID_BYPASS, t_block, 0, BMC_FAS3_FETCH_TYPE_14_AND_7_BIT);
    }
  }
  bool isBlockBypassed(uint16_t n){
    if(!connected()){
      return false;
    }
    bool state = false;
    for(int e = 0; e < BMC_FAS3_BLOCKS_COUNT; e++){
      if(blocksInfo[e].id == n){
        state = !preset.getBlockState(e);
        break;
      }
    }
    return state;
  }
  bool isBlockEngaged(uint16_t n){
    return !isBlockBypassed(n);
  }


  void setBlockChannel(uint16_t t_block, uint8_t t_channel){
    if(connected()){
      fetchSysEx(BMC_FAS3_FUNC_ID_CHANNEL, t_block, t_channel, BMC_FAS3_FETCH_TYPE_14_AND_7_BIT);
      return;
    }
    
  }

  void toggleBlockChannel(uint16_t n, uint8_t c1, uint8_t c2){
    if(!connected()){
      return;
    }
    if(getBlockChannel(n) != c1){
      setBlockChannel(n, c1);
    } else {
      setBlockChannel(n, c2);
    }
  }
  
  uint8_t getBlockChannel(uint16_t n){
    if(!connected()){
      return 0;
    }
    bool value = false;
    for(int e = 0; e < BMC_FAS3_BLOCKS_COUNT; e++){
      if(blocksInfo[e].id == n){
        value = preset.getBlockChannel(e);
        break;
      }
    }
    return value;
  }
  uint8_t getBlockIndex(uint16_t n){
    if(!connected()){
      return 0;
    }
    for(int e = 0; e < BMC_FAS3_BLOCKS_COUNT; e++){
      if(blocksInfo[e].id == n){
        return blocksInfo[e].index+globals.offset;
      }
    }
    return 0;
  }
  void getBlockName(uint16_t n, char * buff, bool fullName=false){
    for(int e = 0; e < BMC_FAS3_BLOCKS_COUNT; e++){
      if(blocksInfo[e].id == n){
        if(fullName){
          char str[8] = "";
          BMCTools::getBankLetter(preset.getBlockChannel(e), str);
          sprintf(buff, "%s %u%s", blocksInfo[e].name, blocksInfo[e].index+1, str);
        } else {
          strcpy(buff, blocksInfo[e].name);
        }
        break;
      }
    }
  }
  uint8_t getBlockBits(uint16_t n){
    uint8_t b = 0;
    for(int e = 0; e < BMC_FAS3_BLOCKS_COUNT; e++){
      if(blocksInfo[e].id == n){
        b = (blocksInfo[e].index << 4) | (preset.getBlockBits(e) & 0x0F);
        break;
      }
    }
    return b;
  }
  // left here not to break API
  // x is channel 0 (1)
  // y is channel 1 (2)
  bool isBlockX(uint16_t n){
    return false;
  }
  bool isBlockY(uint16_t n){
    return false;
  }
  


  // ******************
  // ****   OTHER
  // ******************
  
  void tapTempo(){
    if(!connected()){
      return;
    }
    fetchSysEx(BMC_FAS3_FUNC_ID_TAP);
  }
  bool tempoBeat(){
    return flags.read(BMC_FAS3_FLAG_TEMPO_BEAT);
  }

  // ******************
  // ****   TUNER
  // ******************
  void getTunerData(BMCTunerData& buff){
    buff = tuner;
  }
  // Toggle the tuner state
  void toggleTuner(){
    if(!connected()){
      return;
    }
    if(!tuner.isOn()){
      tunerOn();
    } else {
      tunerOff();
    }
  }
  // Turn tuner on
  void tunerOn(){
    if(connected()){
      if(!tuner.isOn()){
        fetchSysEx(BMC_FAS3_FUNC_ID_TUNER, 1, 0, BMC_FAS3_FETCH_TYPE_7_BIT);
      }
    }
  }
  // Turn tuner off
  void tunerOff(){
    if(connected()){
      if(tuner.isOn()){
        fetchSysEx(BMC_FAS3_FUNC_ID_TUNER, 0, 0, BMC_FAS3_FETCH_TYPE_7_BIT);
      }
    }
  }
  


  // ******************
  // ****   LOOPER
  // ******************
  void enableLooperFetch(bool t_value){
    if(!flags.read(BMC_FAS3_FLAG_FETCH_LOOPER) && t_value){
      looperTimer.start(BMC_FAS3_LOOPER_POLL_TIME);
    }
    if(!t_value){
      looperTimer.stop();
    }
    flags.write(BMC_FAS3_FLAG_FETCH_LOOPER, t_value);
  }

  bool looperEnable(bool value){
    if(value != device.looper.isEnabled()){
      device.looper.changeState(value);
      return true;
    }
    return false;
  }
  void looperControl(uint8_t cmd){
    if(!connected()){
      return;
    }
    switch(cmd){
      case BMC_FAS_LOOPER_CONTROL_PLAY:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_PLAYING);
        break;
      case BMC_FAS_LOOPER_CONTROL_RECORD:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_RECORDING);
        break;
      case BMC_FAS_LOOPER_CONTROL_OVERDUB:
        if(device.looper.playing() && !device.looper.recording()){
          sendLooperCommand(BMC_FAS_LOOPER_STATE_RECORDING);
        } else if(device.looper.playing() && device.looper.recording()){
          sendLooperCommand(BMC_FAS_LOOPER_STATE_PLAYING);
        }
        // sendLooperCommand(1);
        break;
      case BMC_FAS_LOOPER_CONTROL_REVERSE:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_REVERSED);
        break;
      case BMC_FAS_LOOPER_CONTROL_HALF:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_HALF);
        break;
      case BMC_FAS_LOOPER_CONTROL_UNDO:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_UNDO);
        break;
      case BMC_FAS_LOOPER_CONTROL_ONCE:
        sendLooperCommand(BMC_FAS_LOOPER_STATE_ONCE);
        break;
      case BMC_FAS_LOOPER_CONTROL_REC_PLAY_DUB:
        if(!device.looper.playing() && !device.looper.recording()){
          if(looperTrackRecorded()){
            looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
          } else {
            looperControl(BMC_FAS_LOOPER_CONTROL_RECORD);
          }
        } else if(!device.looper.playing() && device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        } else if(device.looper.playing() && !device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_RECORD);
        } else if(device.looper.playing() && device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        }
        break;
      case BMC_FAS_LOOPER_CONTROL_REC_DUB_PLAY:
        if(!device.looper.playing() && !device.looper.recording()){
          if(looperTrackRecorded()){
            looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
          } else {
            looperControl(BMC_FAS_LOOPER_CONTROL_RECORD);
          }
        } else if(!device.looper.playing() && device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_RECORD);
        } else if(device.looper.playing() && !device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_RECORD);
        } else if(device.looper.playing() && device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        }
        break;
        
      case BMC_FAS_LOOPER_CONTROL_STOP:
        if(device.looper.recording() || device.looper.overdubbing()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        } else if(!device.looper.recording() && device.looper.playing()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        }
        break;
      case BMC_FAS_LOOPER_CONTROL_CLEAR:
        if((device.looper.getData() & 0x07) > 0){
          looperControl(BMC_FAS_LOOPER_CONTROL_STOP);
        }
        flags.off(BMC_FAS3_FLAG_LOOPER_TRACK_AVAILABLE);
        
        break;
      // stop if either playing/recording/dubbing, otherwise play
      case BMC_FAS_LOOPER_CONTROL_PLAY_STOP:{
        if(device.looper.playing() && !device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_STOP);
        } else if(!device.looper.playing() && !device.looper.recording()){
          looperControl(BMC_FAS_LOOPER_CONTROL_PLAY);
        }
        break;
      }
        
    }
  }
  bool looperGetState(){
    return device.looper.isEnabled();
  }
  uint8_t looperGetData(){
    return device.looper.getData();
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
  bool looperOnce(){
    return looperStatus(BMC_FAS_LOOPER_STATE_ONCE);
  }
  bool looperStoppedWithTrack(){
    return looperStopped() && looperTrackRecorded();
  }
  bool looperStopped(){
    return (device.looper.getStates()&0x07)==0;
  }
  bool looperTrackRecorded(){
    return flags.read(BMC_FAS3_FLAG_LOOPER_TRACK_AVAILABLE);
  }
private:
  const BMCFas3Block blocksInfo[BMC_FAS3_BLOCKS_COUNT] = {
    {37, "IN",  0, 0b00110100},
    {38, "IN",  1, 0b00110100},
    {39, "IN",  2, 0b00010100},
    {40, "IN",  3, 0b00010100},
    {41, "IN",  4, 0b00000100},
    {42, "OUT", 0, 0b00110100},
    {43, "OUT", 1, 0b00110100},
    {44, "OUT", 2, 0b00010100},
    {45, "OUT", 3, 0b00000100},
    {46, "CMP", 0, 0b00110100},
    {47, "CMP", 1, 0b00110100},
    {48, "CMP", 2, 0b00000100},
    {49, "CMP", 3, 0b00000100},
    {50, "GEQ", 0, 0b00110100},
    {51, "GEQ", 1, 0b00110100},
    {52, "GEQ", 2, 0b00010100},
    {53, "GEQ", 3, 0b00010100},
    {54, "PEQ", 0, 0b00110100},
    {55, "PEQ", 1, 0b00110100},
    {56, "PEQ", 2, 0b00010100},
    {57, "PEQ", 3, 0b00010100},
    {58, "AMP", 0, 0b00110100},
    {59, "AMP", 1, 0b00010100},
    {62, "CAB", 0, 0b00110100},
    {63, "CAB", 1, 0b00010100},
    {66, "REV", 0, 0b00110100},
    {67, "REV", 1, 0b00010100},
    {70, "DLY", 0, 0b00110100},
    {71, "DLY", 1, 0b00110100},
    {72, "DLY", 2, 0b00000100},
    {73, "DLY", 3, 0b00000100},
    {74, "MTD", 0, 0b00110100},
    {75, "MTD", 1, 0b00010100},
    {78, "CHO", 0, 0b00110100},
    {79, "CHO", 1, 0b00110100},
    {82, "FLG", 0, 0b00110100},
    {83, "FLG", 1, 0b00110100},
    {86, "ROT", 0, 0b00110100},
    {87, "ROT", 1, 0b00110100},
    {90, "PHA", 0, 0b00110100},
    {91, "PHA", 1, 0b00110100},
    {94, "WAH", 0, 0b00110100},
    {95, "WAH", 1, 0b00110100},
    {98, "FOR", 0, 0b00110100},
    {99, "FOR", 1, 0b00110100},
    {102, "VOL", 0, 0b00110100},
    {103, "VOL", 1, 0b00110100},
    {104, "VOL", 2, 0b00010100},
    {105, "VOL", 3, 0b00010100},
    {106, "TRM", 0, 0b00110100},
    {107, "TRM", 1, 0b00110100},
    {110, "PIT", 0, 0b00110100},
    {111, "PIT", 1, 0b00000100},
    {114, "FIL", 0, 0b00110100},
    {115, "FIL", 1, 0b00110100},
    {116, "FIL", 2, 0b00110100},
    {117, "FIL", 3, 0b00110100},
    {118, "DRV", 0, 0b00110100},
    {119, "DRV", 1, 0b00110100},
    {120, "DRV", 2, 0b00010100},
    {121, "DRV", 3, 0b00000100},
    {122, "ENH", 0, 0b00110100},
    {123, "ENH", 1, 0b00110100},
    {130, "SYN", 0, 0b00110100},
    {131, "SYN", 1, 0b00000100},
    {134, "VOC", 0, 0b00000001},
    {138, "MGT", 0, 0b00110010},
    {139, "MGT", 1, 0b00010010},
    {142, "XVR", 0, 0b00010010},
    {143, "XVR", 1, 0b00010100},
    {146, "GTE", 0, 0b00110100},
    {147, "GTE", 1, 0b00110100},
    {148, "GTE", 2, 0b00010100},
    {149, "GTE", 3, 0b00010100},
    {150, "RNG", 0, 0b00110010},
    {154, "MBC", 0, 0b00110100},
    {155, "MBC", 1, 0b00010100},
    {158, "TTD", 0, 0b00110100},
    {159, "TTD", 1, 0b00010100},
    {162, "RES", 0, 0b00110010},
    {163, "RES", 1, 0b00110010},
    {166, "LPR", 0, 0b00110001},
    {170, "TMA", 0, 0b00000001},
    {178, "PLX", 0, 0b00110100},
    {179, "PLX", 1, 0b00000100},
    {182, "SND", 0, 0b00110001},
    {183, "SND", 1, 0b00110001},
    {186, "RTN", 0, 0b00110001},
    {187, "RTN", 1, 0b00110001},
    {195, "IRP", 0, 0b00000100},
    {196, "IRP", 1, 0b00000100}
  };
};

#endif
#endif
