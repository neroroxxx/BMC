#include "sync/fas/BMC-Fas.h"

#if defined(BMC_USE_FAS)

BMCFas::BMCFas(BMCMidi& t_midi):
  midi(t_midi),
  globals(midi.globals)
{
  device.reset();
  findDeviceTimer.stop();
}
void BMCFas::begin(){
  BMC_INFO("FAS Sync Version 1.0");
  BMC_INFO("On Axe FX II to use the tuner toggle or tempo beat you MUST enable Real Time MIDI");
  flags.on(BMC_FAS_FLAG_DEVICE_SEARCH);
  findDeviceTimer.start(1000);
}
void BMCFas::update(){
  // search for response from FAS device, try up to 10 times every 5 seconds
  // this message will be broadcast on all MIDI ports except USB and BLE (if available)
  if(flags.read(BMC_FAS_FLAG_DEVICE_SEARCH)){
    if(attempts<10 && findDeviceTimer.complete()){
#ifdef BMC_DEBUG
      if(attempts==0){
        delay(1);
        BMC_PRINTLN("");
        BMC_PRINTLN("");
        BMC_INFO("FAS Starting Device Search");
      }
#endif
      BMC_PRINTLN("   >> Looking for FAS Device <<   ");
      sendDeviceSearch();
      findDeviceTimer.start(5000);
      attempts++;
    }
    return;
  }

  if(connected()){
    // if connected
    if(connectionLost.complete()){
      // if the timer for connection lost was received
      if(flags.read(BMC_FAS_FLAG_CONNECTION_LOST)){
        // if we had already tried one more time to wait for a conection
        // then we can assume we lost the connection
        BMC_PRINTLN("No response from FAS, connection lost...");
        disconnect();
      } else {
        // in this case we waited for 5 seconds for a new message to be received
        // so we'll turn this flag on to wait for a new message one last time
        flags.on(BMC_FAS_FLAG_CONNECTION_LOST);
        sendBasicSysEx(BMC_FAS_FUNC_ID_CPU);
        connectionLost.start(BMC_FAS_CONNECTION_LOST_TIMEOUT);
      }
    }
  }
  if(tunerTimeout.complete()){
    tunerFlags.reset();
    sendBasicSysEx(BMC_FAS_FUNC_ID_LOOPER, true);
    if(midi.callback.fasTunerStateChange){
      midi.callback.fasTunerStateChange(false);
    }
    BMC_PRINTLN("--> FAS TUNER: OFF");
  }
  if(looperTimeout.complete()){
    flags.off(BMC_FAS_FLAG_LOOPER_ACTIVE);
    if(midi.callback.fasLooperStateChange){
      midi.callback.fasLooperStateChange(false);
    }
    BMC_PRINTLN("--> FAS LOOPER: STOPPED");
  }
  if(!connected()&& !syncing()){
    if(startSyncTimer.complete()){
      startSyncTimer.start(3000);
      sendBasicSysEx(BMC_FAS_FUNC_ID_FIRMWARE);
    }
  }
  presetSyncQueue();
}
// parse incoming Sysex Messages
bool BMCFas::incoming(BMCMidiMessage& message){
  if(flags.read(BMC_FAS_FLAG_DEVICE_SEARCH) && findDeviceTimer.active()){
    if(isFractMessage(message)){
      device.setIdAndPort(message.sysex[4], message.getPort());
      flags.off(BMC_FAS_FLAG_DEVICE_SEARCH);
      attempts = 0;
      findDeviceTimer.stop();
      startSyncTimer.start(250);
      timeConnectionStart();
      BMC_INFO("FAS FOUND DEVICE", debugPrintDeviceName(device.getId()), BMCTools::getPortName(device.getPort()));
    }
    return false;
  }
  if(!isFractMessage(message) || !isValidPort(message.getPort())){
    return false;
  }
#ifdef BMC_DEBUG
  debugPrintFasMessageInfo(message);
#endif

  timeConnectionStart();

  // messages that don't have a Checksum
  switch(message.sysex[5]){
    case BMC_FAS_FUNC_ID_MIDI_TEMPO_BEAT:{
      if(!connected() || !isFractMessage(message, 5)){
        return false;
      }
      flags.on(BMC_FAS_FLAG_TEMPO_RECEIVED);
      globals.clearMidiInActivity();
      return true;
    }
    case BMC_FAS_FUNC_ID_TUNER_INFO:{
      if(!connected() || !isFractMessage(message, 10)){
        return false;
      }
      globals.clearMidiInActivity();
      tunerData.note = message.sysex[6];
      tunerData.stringNumber = message.sysex[7];
      tunerData.pitchRaw = message.sysex[8] & 0x7F;
      tunerData.pitch = map(tunerData.pitchRaw, 0, 127, -63, 64);
      tunerNote(tunerData.note, tunerData.noteName);
      tunerTimeout.start(250);

      if(!tunerFlags.read(BMC_FAS_TUNER_FLAG_ACTIVE)){
        if(midi.callback.fasTunerStateChange){
          midi.callback.fasTunerStateChange(true);
        }
        tunerFlags.on(BMC_FAS_TUNER_FLAG_ACTIVE);
        // turn off looper data while tuning
        sendBasicSysEx(BMC_FAS_FUNC_ID_LOOPER, false);
        BMC_PRINTLN("--> FAS TUNER: ON");
      }
      if(midi.callback.fasTunerReceived){
        midi.callback.fasTunerReceived(tunerData);
      }
      //BMC_PRINTLN("--> FAS TUNER: ", tunerData.pitch);
      //reset tuner flags but keep state flag on
      tunerFlags.reset();
      tunerFlags.on(BMC_FAS_TUNER_FLAG_ACTIVE);
      if(tunerData.pitchRaw<62){
        tunerFlags.on(BMC_FAS_TUNER_FLAG_FLAT);
        if(tunerData.pitchRaw < 42){
          tunerFlags.on(BMC_FAS_TUNER_FLAG_FLATTER);
        }
        if(tunerData.pitchRaw < 21){
          tunerFlags.on(BMC_FAS_TUNER_FLAG_FLATTEST);
        }
      } else if(tunerData.pitchRaw>64){
        tunerFlags.on(BMC_FAS_TUNER_FLAG_SHARP);
        if(tunerData.pitchRaw > 84){
          tunerFlags.on(BMC_FAS_TUNER_FLAG_SHARPER);
        }
        if(tunerData.pitchRaw > 105){
          tunerFlags.on(BMC_FAS_TUNER_FLAG_SHARPEST);
        }
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_LOOPER:{
      if(!connected() || !isFractMessage(message, 9)){
        return false;
      }
      globals.clearMidiInActivity();
      uint8_t data = message.sysex[6];
      uint8_t position = message.sysex[7];
      device.looper.set(data, position);

      if(data>0){
        looperTimeout.start(1000);
        if(!flags.read(BMC_FAS_FLAG_LOOPER_ACTIVE)){
          if(midi.callback.fasLooperStateChange){
            midi.callback.fasLooperStateChange(true);
          }
          flags.on(BMC_FAS_FLAG_LOOPER_ACTIVE);
          BMC_PRINTLN("--> FAS LOOPER: ACTIVE", data);
        }
        if(device.looper.getStates(BMC_FAS_LOOPER_STATE_RECORDING)){
          flags.on(BMC_FAS_FLAG_LOOPER_TRACK_AVAILABLE);
        }
      }
      if(midi.callback.fasLooperReceived){
        // only send the position if it's not doing an initial recording.
        midi.callback.fasLooperReceived(data, bitRead(data,0)?0:position);
      }
#if defined(BMC_DEBUG)
      if(globals.getFasDebug()){
        BMC_PRINTLN("--> FAS Looper Info", data, position);
      }
#endif
    }
      return true;
    case BMC_FAS_FUNC_ID_BLOCKS_DATA:{
      if(!connected() || !isFractMessage(message, 5)){
        return false;
      }
      // crc used to know if there's a change within the blocks
      uint8_t crc = device.blocks.getCRC();
      device.blocks.reset();
      BMC_PRINTLN("--> FAS BLOCKS RECEIVED:", (message.size()-8)/5);
      for(uint8_t i = 6; i < message.size()-2; i+=5){
        uint32_t block = message.get32BitsLSBFirst(i);
        bool isEngaged = bitRead(block, 0);
        bool isX = bitRead(block, 1);
        uint8_t blockId = (block>>24) & 0xFF;
  #ifdef BMC_DEBUG
      if(globals.getFasDebug()){
        uint8_t bypassCC = (block>>8) & 0x7F;
        uint8_t xyCC = (block>>16) & 0x7F;
        if(blockId>=100 && blockId<=170){
          BMC_PRINTLN("--> FAS BLOCK:", blocksGlobalData[blockId-100].name, blockId, bypassCC, xyCC, isEngaged?"ON":"OFF", isX?"X":"Y");
        }
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
      if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS)){
        resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
      }
    }
      return true;
  }
  // the rest require a valid CRC
  if(isValidFasFunction(message.sysex[5]) && !message.validateChecksum()){
    BMC_PRINTLN("!!!  FAS Received Bad CRC  !!!");
    // TODO: add code to resend the message that returned the bad CRC
    return false;
  }
  switch(message.sysex[5]){
    case BMC_FAS_FUNC_ID_RESYNC:{
      device.paramReset();
      BMC_WARN("FAS RE-SYNC RECEIVED");
      receivedReSync(true);
    }

      return true;
    case BMC_FAS_FUNC_ID_FIRMWARE:{
      if(connected() || !isFractMessage(message, 10) || syncing()){
        return false;
      }
      device.version = (message.get7Bits(6)<<8) | message.get7Bits(7);
      flags.on(BMC_FAS_FLAG_SYNCING);
      startSyncTimer.stop();
      sendBasicSysEx(BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL);
      BMC_PRINTLN("--> FAS FIRMWARE:", device.version);
    }
      return true;
    case BMC_FAS_FUNC_ID_GET_MIDI_CHANNEL:{
      if(connected() || !isFractMessage(message, 9) || !syncing()){
        return false;
      }
      // turn on looper data when connecting
      // we'll use this as a way to track the state of the connection
      sendBasicSysEx(BMC_FAS_FUNC_ID_LOOPER, true);
      device.channel = message.get7Bits(6)+1;
      BMC_PRINTLN("--> FAS MIDI CHANNEL:", device.channel);
      flags.on(BMC_FAS_FLAG_CONNECTED);
      flags.on(BMC_FAS_FLAG_CONNECTION_CHANGED);
      flags.off(BMC_FAS_FLAG_SYNCING);
      if(midi.callback.fasConnection){
        midi.callback.fasConnection(true);
      }
      receivedReSync();
      flags.on(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
    }
      return true;
    case BMC_FAS_FUNC_ID_BLOCK_PARAM:{
      if(!connected() || !isFractMessage(message, 15)){
        return false;
      }
      uint8_t blockId = message.get8BitsLSBFirst(6);
      uint8_t paramId = message.get8BitsLSBFirst(8);
      uint16_t value = message.get16BitsLSBFirst(10);
      if(paramId==255){
        device.blocks.set(blockId, (value==0), device.blocks.isY(blockId));
        if(midi.callback.fasBlocksChange && device.blocks.isEngaged(blockId) != (value==0)){
          midi.callback.fasBlocksChange();
        }
        BMC_PRINTLN("--> FAS BLOCK Bypass:", blockId, value==0?"engaged":"bypassed");
      } else {
        device.paramReceived(blockId, paramId, value);
        requestSyncParameters();
        if(midi.callback.fasBlockParameterReceived){
          uint8_t strLen = message.size()-(18+2);
          char str[strLen] = "";
          message.getStringFromSysEx(18, str, strLen);
          midi.callback.fasBlockParameterReceived(blockId, paramId, value, str, strLen);
          BMC_PRINTLN("--> FAS Block Parameter Received: Block:", blockId,
                      "Param:", paramId, "Value:", value, "Str:", str, strLen);
        }
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_CPU:{
      if(!connected() || !isFractMessage(message, 9)){
        return false;
      }
      uint8_t value = message.get7Bits(6);
#if defined(BMC_DEBUG)
      if(globals.getFasDebug()){
        BMC_PRINTLN("--> FAS CPU:", value, "%");
      }
#endif
      if(midi.callback.fasCpuReceived){
        midi.callback.fasCpuReceived(value);
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_PRESET_NAME:{
      if(!connected() || !isFractMessage(message, 30)){
        return false;
      }
      strcpy(device.presetName, "");
      message.getStringFromSysEx(6, device.presetName, 32);
      BMC_PRINTLN("--> FAS PRESET NAME:", device.presetName);
      if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECT_PRESET_NAME)){
        resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
      }
      if(midi.callback.fasPresetName){
        midi.callback.fasPresetName(device.presetName);
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_GET_PRESET_NUMBER:{
      if(!connected() || !isFractMessage(message, 10)){
        return false;
      }
      uint16_t value = message.get14Bits(6);
      if(device.preset!=value){
        device.paramReset();
        if(midi.callback.fasPresetChange){
          midi.callback.fasPresetChange(value);
        }
      }
      device.preset = value;
      BMC_PRINTLN("--> FAS PRESET NUMBER:", debugPrintPreset());
      if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECT_PRESET)){
        resyncTimer.start(BMC_FAS_RESYNC_TIMEOUT);
      } else {
        receivedReSync();
        flags.off(BMC_FAS_FLAG_SYNC_EXPECT_PRESET);
        flags.on(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
        resyncTimer.start(BMC_FAS_RESYNC_TIMEOUT);
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_SCENE_NUMBER:{
      if(!connected() || !isFractMessage(message, 9)){
        return false;
      }
      uint8_t value = message.get7Bits(6);
      if(device.scene!=value){
        flags.on(BMC_FAS_FLAG_SYNC_PARAM_SYNC_BEGIN);
        requestSyncParameters();
        if(midi.callback.fasSceneChange){
          midi.callback.fasSceneChange(value);
        }
      }
      device.scene = value;
      BMC_PRINTLN("--> FAS SCENE NUMBER:", device.scene+1);
      if(flags.toggleIfTrue(BMC_FAS_FLAG_SYNC_EXPECT_SCENE)){
        resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
        if(device.id==BMC_FAS_DEVICE_ID_AX8){
          flags.off(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
        }
      } else {
        if(device.id!=BMC_FAS_DEVICE_ID_AX8){
          flags.off(BMC_FAS_FLAG_SYNC_EXPECT_BLOCKS);
          resyncTimer.start(BMC_FAS_RESYNC_QUEUE_TIMEOUT);
        }
      }
    }
      return true;
    case BMC_FAS_FUNC_ID_BLOCK_XY:{
      if(!connected() || !isFractMessage(message, 11)){
        return false;
      }
      uint8_t blockId = message.get8BitsLSBFirst(6);
      uint8_t xy = message.get7Bits(8);
      device.blocks.set(blockId, device.blocks.isEngaged(blockId), xy);
      if(midi.callback.fasBlocksChange && device.blocks.isY(blockId)!=xy){
        midi.callback.fasBlocksChange();
      }
      BMC_PRINTLN("--> FAS BLOCK XY:", blockId, xy?"Y":"X");
    }
      return true;
    case BMC_FAS_FUNC_ID_GENERAL_PURPOSE:{
      if(!isFractMessage(message, 10)){
        return false;
      }
      BMC_PRINTLN("--> FAS GENERAL PURPOSE FUNC:", message.get7Bits(6),"CODE:", message.get7Bits(7));
    }
      return true;
  }
  return false;
}







// DEBUGGING

#ifdef BMC_DEBUG
String BMCFas::debugPrintDeviceName(uint8_t id){
  switch(id){
    case BMC_FAS_DEVICE_ID_AXE_FX_II:         return "Axe Fx II";
    case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:      return "Axe Fx II XL";
    case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS: return "Axe Fx II XL+";
    case BMC_FAS_DEVICE_ID_AX8:               return "AX8";
    case BMC_FAS_DEVICE_ID_AXE_FX_III:        return "Axe Fx III";
    case BMC_FAS_DEVICE_ID_FM3:               return "FM3";
  }
  return "";
}
String BMCFas::debugPrintPreset(){
  char buff[30];
  switch(device.id){
    case BMC_FAS_DEVICE_ID_AXE_FX_II:
    case BMC_FAS_DEVICE_ID_AXE_FX_II_XL:
    case BMC_FAS_DEVICE_ID_AXE_FX_II_XL_PLUS:{
      uint8_t preset = (device.preset & 0x7F)+1;
      uint8_t bank = ((device.preset>>7) & 0x7F);
      bank = constrain(bank, 0, 25);
      sprintf(buff, "(%03u) BANK: %c | PRESET: %03u", device.preset, (char) bmcAlphabet[bank], preset);
      String output(buff);
      return output;
    }
    case BMC_FAS_DEVICE_ID_AX8:{
      uint8_t preset = (device.preset & 0x07)+1;
      uint8_t bank = (device.preset>>3)+1;
      sprintf(buff, "(%03u) BANK: %02u | PRESET: %01u", device.preset, bank, preset);
      String output(buff);
      return output;
    }
  }
  return "";
}
void BMCFas::debugPrintFasMessageInfo(BMCMidiMessage& message){
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
  if(globals.getFasDebug()){
    BMC_PRINTLN("--> FAS MESSAGE RECEIVED, ID:", message.sysex[5], str, "SIZE:", message.size());
  }
}
bool BMCFas::isValidFasFunction(uint8_t funcId){
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

#endif
