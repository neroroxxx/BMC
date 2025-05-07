/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Handle all the global incoming MIDI Messages and spit out all others.
*/
#include "editor/BMC-Editor.h"

void BMCEditor::globalProcessMessage(){
  switch(getMessageRequestId()){
    case BMC_GLOBALF_CONNECT:
      connectEditor();
      break;
    case BMC_GLOBALF_DISCONNECT:
      disconnectEditor();
      break;
    case BMC_GLOBALF_FORCE_DISCONNECT:
      forceDisconnectEditor();
      break;
    case BMC_GLOBALF_EDITOR_FETCH_COMPLETE:
      if(isValidGlobalMessage() && isWriteMessage()){
        BMC_INFO("BMCEditor Fetch Complete");
        flags.off(BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR);
      }
      break;
    case BMC_GLOBALF_BUILD_INFO:
      globalBuildInfoMessage();
      break;
    case BMC_GLOBALF_BACKUP:
      globalBackupMessage(isWriteMessage());
      break;
    case BMC_GLOBALF_SETTINGS:
      globalSettingsMessage(isWriteMessage());
      break;
    //case BMC_GLOBALF_STARTUP:
      //globalStartup(isWriteMessage());
      //break;
    case BMC_GLOBALF_STORE_ADDRESS:
      globalStoreAddress(isWriteMessage());
      break;
    case BMC_GLOBALF_POT_CALIBRATION:
      globalPotCalibration();
      break;
    case BMC_GLOBALF_SKETCH_BYTES_DATA:
      globalSketchBytesData();
      break;
    case BMC_GLOBALF_TIME:
      globalSetTime(isWriteMessage());
      break;
    case BMC_GLOBALF_EDITOR_FEEDBACK:
      globalEditorFeedback(isWriteMessage());
      break;
    case BMC_GLOBALF_EDITOR_GET_METRICS:
      globalEditorMetrics();
      break;
    case BMC_GLOBALF_EDITOR_MESSENGER:
      globalEditorMessenger(isWriteMessage());
      break;
    case BMC_GLOBALF_EDITOR_PERFORM_MODE:
      // no yet implemented, its meant to be a customizable screen
      // for easy editing that only loads the data of the current layer and
      // loads things as needed instead of loading all data from EEPROM
      // into the editor app as it does normally
      //globalEditorPerformMode(isWriteMessage());
      break;
    case BMC_EDITOR_FUNCTION_EVENT:
      incomingMessageEvent(isWriteMessage());
      break;
    case BMC_EDITOR_FUNCTION_NAME:
      incomingMessageName(isWriteMessage());
      break;
    case BMC_EDITOR_FUNCTION_DEVICE:
      incomingMessageDevice(isWriteMessage());
      break;
    case BMC_EDITOR_FUNCTION_ERASE:
      globalEditorErase(isWriteMessage());
      break;
    case BMC_EDITOR_FUNCTION_LINK:
      incomingMessageLinks();
      break;
    case BMC_EDITOR_FUNCTION_CONNECTION_ALIVE:
      #if defined(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT)
        // connectionAliveTimer.start(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT);
        editorHasConnectionAliveOption = true;
        keepConnectionAlive();
      #endif
      break;
  }
}
void BMCEditor::incomingMessageLinks(){
  if(!isValidGlobalMessage()){
    return;
  }
  
  uint16_t index = getMessageLayerNumber();
  if(index>0 && index>=BMC_MAX_LINKS){
    sendNotification(BMC_NOTIFY_INVALID_LINK, index, true);
    return;
  }

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_LINK, 0,
    index
  );
  buff.appendToSysEx14Bits(BMC_MAX_LINKS);
  #if BMC_MAX_LINKS > 0
    BMCLinkData item = BMCBuildData::getLinkData(index);
  #else
    BMCLinkData item;
  #endif
  buff.appendToSysEx14Bits(item.id1);
  buff.appendToSysEx14Bits(item.index1);
  buff.appendToSysEx14Bits(item.id2);
  buff.appendToSysEx14Bits(item.index2);
  buff.appendToSysEx14Bits(item.id3);
  buff.appendToSysEx14Bits(item.index3);
  buff.appendToSysEx14Bits(item.id4);
  buff.appendToSysEx14Bits(item.index4);
  
  sendToEditor(buff);
}
void BMCEditor::incomingMessageEvent(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 24;
  // handle backup
  if(write && backupActive()){
    backupEventMessage(sysExLength);
    return;
  }
  uint16_t index = getMessageLayerNumber();
  if(index>0 && index>=BMC_MAX_EVENTS_LIBRARY){
    sendNotification(BMC_NOTIFY_INVALID_EVENT, index, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreEvent& item = store.global.events[index];
    item.name     = incoming.get14Bits(9);
    item.settings = incoming.get8Bits(11);
    item.type     = incoming.get8Bits(13);
    item.ports    = incoming.get8Bits(15);
    item.event    = incoming.get32Bits(17);
    saveEvent(index);
    reloadData();
  }

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_EVENT, 0,
    index
  );
  buff.appendToSysEx14Bits(BMC_MAX_EVENTS_LIBRARY);
  bmcStoreEvent& item = store.global.events[index];
  buff.appendToSysEx14Bits(item.name);
  buff.appendToSysEx8Bits(item.settings);
  buff.appendToSysEx8Bits(item.type);
  buff.appendToSysEx8Bits(item.ports);
  buff.appendToSysEx32Bits(item.event);
  sendToEditor(buff);
}
void BMCEditor::incomingMessageName(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 12;
  // handle backup
  if(write && backupActive()){
    backupNameMessage(sysExLength);
    return;
  }
  //BMC_MAX_NAMES_LENGTH
  uint16_t index = getMessageLayerNumber();
  if(index>0 && index>=BMC_MAX_NAMES_LIBRARY){
    sendNotification(BMC_NOTIFY_INVALID_NAME, index, true);
    return;
  }
  sysExLength += BMC_MAX_NAMES_LENGTH;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreName& item = store.global.names[index];
    // byte 9 is the length of the string
    // byte 10 has the string
    incoming.getStringFromSysEx(10, item.name, BMC_MAX_NAMES_LENGTH);
    saveName(index);
    reloadData();
  }

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_NAME, 0,
    index
  );
  buff.appendToSysEx14Bits(BMC_MAX_NAMES_LIBRARY);
  bmcStoreName& item = store.global.names[index];
  buff.appendToSysEx7Bits(BMC_MAX_NAMES_LENGTH);
  buff.appendCharArrayToSysEx(item.name, BMC_MAX_NAMES_LENGTH);
  sendToEditor(buff);
}


void BMCEditor::incomingMessageDevice(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 19;

  uint8_t deviceType = incoming.get8Bits(9);
  uint16_t index = incoming.get14Bits(11);

  uint16_t maxDevices = checkIfHardwareAvailable(deviceType);
  uint8_t layer = getMessageLayerNumber();

  // bytes 13 and 14 have the name pointer
  sysExLength += (incoming.get7Bits(15) * 2);
  sysExLength += (incoming.get7Bits(16) * 2);

  if(index>0 && index >= maxDevices && !backupActive()){
    BMC_PRINTLN("******************* invalid device", index, maxDevices);
    sendNotification(BMC_NOTIFY_INVALID_DEVICE, index, true);
    return;
  }
  if(backupActive()){
    if(index >= maxDevices){
      sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
      return;
    }
  }
  if(write && incoming.size() != sysExLength){
    BMC_PRINTLN("******************* incoming.size()",incoming.size(),"sysExLength",sysExLength);
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write && maxDevices > 0){
    uint16_t pageToWrite = layer;
    uint16_t maxLayerToWrite = layer+1;
    if(isDeviceWriteToAllLayers() && !backupActive()){
      pageToWrite = 0;
      maxLayerToWrite = BMC_MAX_LAYERS;
      BMC_PRINTLN("Save to all layers",pageToWrite, maxLayerToWrite);
    } else {
      BMC_PRINTLN("DO NOT Save to all layers",pageToWrite, maxLayerToWrite);
    }
    if(backupActive()){
      if(pageToWrite >= BMC_MAX_LAYERS){
        sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
        return;
      }
    }
    switch(deviceType){
      case BMC_DEVICE_ID_LAYER:
      //   // write new data and save, starts at byte 13
      //   if(!backupActive()){
      //     store.layers[index].name = incoming.get14Bits(13);
      //     saveLayersAndReloadData(layer);
      //   } else {
      //     if(index<BMC_MAX_LAYERS){
      //       uint16_t e = incoming.get14Bits(13);
      //       if(e > BMC_MAX_NAMES_LIBRARY){
      //         e = 0;
      //       }
      //       store.layers[index].name = e;
      //     }
      //   }
      //   break;
        for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
          incomingMessageDeviceWrite<0,BMC_MAX_LAYER_EVENTS>(store.layers[p].events[index], index, p);
        }
        break;
      case BMC_DEVICE_ID_BUTTON:
        #if BMC_MAX_BUTTONS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>(store.layers[p].buttons[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
        #if BMC_MAX_GLOBAL_BUTTONS > 0
          incomingMessageDeviceWrite<BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>(store.global.buttons[index], index);
          if(!backupActive()){
            saveGlobalButton(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_LED:
        #if BMC_MAX_LEDS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.layers[p].leds[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_LED:
        #if BMC_MAX_GLOBAL_LEDS > 0
          incomingMessageDeviceWrite<1,1>(store.global.leds[index], index);
          if(!backupActive()){
            saveGlobalLed(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_BI_LED:
        #if BMC_MAX_BI_LEDS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<2, 2>(store.layers[p].biLeds[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          incomingMessageDeviceWrite<2, 2>(store.global.biLeds[index], index);
          if(!backupActive()){
            saveGlobalBiLed(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_TRI_LED:
        #if BMC_MAX_TRI_LEDS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<3, 3>(store.layers[p].triLeds[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          incomingMessageDeviceWrite<3, 3>(store.global.triLeds[index], index);
          if(!backupActive()){
            saveGlobalTriLed(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_ENCODER:
        #if BMC_MAX_ENCODERS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.layers[p].encoders[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
        #if BMC_MAX_GLOBAL_ENCODERS > 0
          incomingMessageDeviceWrite<1,1>(store.global.encoders[index], index);
          if(!backupActive()){
            saveGlobalEncoder(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_POT:
        #if BMC_MAX_POTS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,3>(store.layers[p].pots[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_POT:
        #if BMC_MAX_GLOBAL_POTS > 0
          incomingMessageDeviceWrite<1,3>(store.global.pots[index], index);
          if(!backupActive()){
            saveGlobalPot(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_POT_CALIBRATION:
        #if BMC_TOTAL_POTS_AUX_JACKS > 0
          incomingMessageDeviceWrite<0,2,uint16_t>(store.global.potCalibration[index], index);
          if(!backupActive()){
            savePotCalibration(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_MAGIC_ENCODER:
        #if BMC_MAX_MAGIC_ENCODERS > 0
        for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<3, 3>(store.layers[p].magicEncoders[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
        #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
          incomingMessageDeviceWrite<3,3>(store.global.magicEncoders[index], index);
          if(!backupActive()){
            saveGlobalMagicEncoder(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL:
        #if BMC_MAX_PIXELS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.layers[p].pixels[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
        #if BMC_MAX_GLOBAL_PIXELS > 0
          incomingMessageDeviceWrite<1,1>(store.global.pixels[index], index);
          if(!backupActive()){
            saveGlobalPixel(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_RGB_PIXEL:
        #if BMC_MAX_RGB_PIXELS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,3>(store.layers[p].rgbPixels[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
          incomingMessageDeviceWrite<1,3>(store.global.rgbPixels[index], index);
          if(!backupActive()){
            saveGlobalRgbPixel(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL_STRIP:
        #if BMC_MAX_PIXEL_STRIP > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.layers[p].pixelStrip[0], 0, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_NL_RELAY:
        #if BMC_MAX_NL_RELAYS > 0
          incomingMessageDeviceWrite<1,1>(store.global.relaysNL[index], index);
          if(!backupActive()){
            saveNLRelay(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_L_RELAY:
        #if BMC_MAX_L_RELAYS > 0
          incomingMessageDeviceWrite<1,1>(store.global.relaysL[index], index);
          if(!backupActive()){
            saveLRelay(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_AUX_JACK:
        #if BMC_MAX_AUX_JACKS > 0
          incomingMessageDeviceWrite<2,3>(store.global.auxJacks[index], index);
          if(!backupActive()){
            saveAuxJack(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_CUSTOM_SYSEX:
        #if BMC_MAX_CUSTOM_SYSEX > 0
          incomingMessageDeviceWrite<1, 16, uint8_t>
          (store.global.customSysEx[index], index);
          if(!backupActive()){
            saveCustomSysEx(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_OLED:
        #if BMC_MAX_OLED > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.layers[p].oled[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_MINI_DISPLAY:
        #if BMC_MAX_MINI_DISPLAY > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<BMC_MAX_MINI_DISPLAY_SETTINGS,BMC_MAX_MINI_DISPLAY_EVENTS>(store.layers[p].miniDisplay[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_ILI:
        #if BMC_MAX_ILI9341_BLOCKS > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<BMC_ILI_S_COUNT,1>(store.layers[p].ili[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_LCD:
        #if BMC_MAX_LCD > 0
          for(uint16_t p = pageToWrite ; p < maxLayerToWrite ; p++){
            incomingMessageDeviceWrite<1, 1>(store.layers[p].lcd[index], index, p);
          }
        #endif
        break;

        
      case BMC_DEVICE_ID_LFO:
        #if BMC_MAX_LFO > 0
          incomingMessageDeviceWrite<3, 5, uint8_t>
          (store.global.lfo[index], index);
          if(!backupActive()){
            flags.on(BMC_EDITOR_FLAG_EDITOR_LFO_UPDATED);
            saveLFO(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_PRESET:
        #if BMC_MAX_PRESETS > 0
          incomingMessageDeviceWrite<1,BMC_MAX_PRESET_ITEMS>
          (store.global.presets[index], index);
          if(!backupActive()){
            savePreset(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_TRIGGER:
        #if BMC_MAX_TRIGGERS > 0
          incomingMessageDeviceWrite<1,2>(store.global.triggers[index], index);
          if(!backupActive()){
            flags.on(BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED);
            saveTrigger(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
        #if BMC_MAX_TEMPO_TO_TAP > 0
          incomingMessageDeviceWrite<1, 1>(store.global.tempoToTap[index], index);
          if(!backupActive()){
            flags.on(BMC_EDITOR_FLAG_EDITOR_TEMPO_TO_TAP_UPDATED);
            saveTempoToTap(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_PORT_PRESET:
        incomingMessageDeviceWrite<0, 1, uint8_t>
          (store.global.portPresets[index], index);
        if(!backupActive()){
          saveDevicePorts(index);
          reloadData();
        }
        break;
      case BMC_DEVICE_ID_SHORTCUTS:
        incomingMessageDeviceWrite<0, 6, uint8_t>
          (store.global.shortcuts[index], index, -1, true);
        if(!backupActive()){
          saveShortCuts(index);
          reloadData();
        }
        break;
      case BMC_DEVICE_ID_PIXEL_PROGRAM:
        #if BMC_MAX_PIXEL_PROGRAMS > 0
          incomingMessageDeviceWrite<1, 8, uint8_t>
          (store.global.pixelPrograms[index], index);
          if(!backupActive()){
            savePixelProgram(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_SKETCH_BYTE:
        #if BMC_MAX_SKETCH_BYTES > 0
          incomingMessageDeviceWrite<0, BMC_MAX_SKETCH_BYTES, uint8_t>
          (store.global.sketchBytes[0], 0, -1, true);
          if(!backupActive()){
            saveSketchBytes();
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST:
        #if BMC_MAX_SETLISTS > 0
          incomingMessageDeviceWrite<1,BMC_MAX_SETLISTS_SONGS>
          (store.global.setLists[index], index);
          if(!backupActive()){
            saveSetList(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST_SONG:
        break;
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:
        #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
          incomingMessageDeviceWrite<1,BMC_MAX_SETLISTS_SONG_PARTS>
          (store.global.songLibrary[index], index);
          if(!backupActive()){
            saveSetListSong(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_TIMED_EVENT:
        #if BMC_MAX_TIMED_EVENTS > 0
          incomingMessageDeviceWrite<2, 1>
          (store.global.timedEvents[index], index);
          if(!backupActive()){
            flags.on(BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED);
            saveTimedEvent(index);
            reloadData();
          }
        #endif
        break;
    }
  }
  if(backupActive()){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_DEVICE, 0,
    layer
  );

  buff.appendToSysEx7Bits(deviceType);
  buff.appendToSysEx14Bits(index);
  buff.appendToSysEx14Bits(maxDevices);
  switch(deviceType){
    case BMC_DEVICE_ID_LAYER:
      // layer names only include the name
      // buff.appendToSysEx14Bits(store.layers[index].name);
      // break;
      deviceResponseData <0, BMC_MAX_LAYER_EVENTS>
      (store.layers[layer].events[index], buff, index, deviceType);
      break;
    case BMC_DEVICE_ID_BUTTON:
      #if BMC_MAX_BUTTONS > 0
        deviceResponseData <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>
        (store.layers[layer].buttons[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_BUTTON:
      #if BMC_MAX_GLOBAL_BUTTONS > 0
        deviceResponseData <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>
        (store.global.buttons[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_LED:
      #if BMC_MAX_LEDS > 0
        deviceResponseData <1, 1>
        (store.layers[layer].leds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_LED:
      #if BMC_MAX_GLOBAL_LEDS > 0
        deviceResponseData <1, 1>
        (store.global.leds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_BI_LED:
      #if BMC_MAX_BI_LEDS > 0
        deviceResponseData <2, 2>
        (store.layers[layer].biLeds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_BI_LED:
      #if BMC_MAX_GLOBAL_BI_LEDS > 0
        deviceResponseData <2, 2>
        (store.global.biLeds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_TRI_LED:
      #if BMC_MAX_TRI_LEDS > 0
        deviceResponseData <3, 3>
        (store.layers[layer].triLeds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_TRI_LED:
      #if BMC_MAX_GLOBAL_TRI_LEDS > 0
        deviceResponseData <3, 3>
        (store.global.triLeds[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_ENCODER:
      #if BMC_MAX_ENCODERS > 0
        deviceResponseData <1, 1>
        (store.layers[layer].encoders[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_ENCODER:
      #if BMC_MAX_GLOBAL_ENCODERS > 0
        deviceResponseData <1, 1>
        (store.global.encoders[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_POT:
      #if BMC_MAX_POTS > 0
        deviceResponseData <1, 3>
        (store.layers[layer].pots[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_POT:
      #if BMC_MAX_GLOBAL_POTS > 0
        deviceResponseData <1, 3>
        (store.global.pots[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_POT_CALIBRATION:
      #if BMC_TOTAL_POTS_AUX_JACKS > 0
        deviceResponseData <0,2,uint16_t>
        (store.global.potCalibration[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_MAGIC_ENCODER:
      #if BMC_MAX_MAGIC_ENCODERS > 0
        deviceResponseData <3, 3>
        (store.layers[layer].magicEncoders[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
      #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
        deviceResponseData <3, 3>
        (store.global.magicEncoders[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_PIXEL:
      #if BMC_MAX_PIXELS > 0
        deviceResponseData <1, 1>
        (store.layers[layer].pixels[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_PIXEL:
      #if BMC_MAX_GLOBAL_PIXELS > 0
        deviceResponseData <1, 1>
        (store.global.pixels[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_RGB_PIXEL:
      #if BMC_MAX_RGB_PIXELS > 0
        deviceResponseData <1, 3>
        (store.layers[layer].rgbPixels[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
      #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
        deviceResponseData <1, 3>
        (store.global.rgbPixels[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_PIXEL_STRIP:
      #if BMC_MAX_PIXEL_STRIP > 0
        deviceResponseData <1, 1>
        (store.layers[layer].pixelStrip[0], buff, 0, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_NL_RELAY:
      #if BMC_MAX_NL_RELAYS > 0
        deviceResponseData <1, 1>
        (store.global.relaysNL[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_L_RELAY:
      #if BMC_MAX_L_RELAYS > 0
        deviceResponseData <1, 1>
        (store.global.relaysL[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_AUX_JACK:
      #if BMC_MAX_AUX_JACKS > 0
        deviceResponseData <2, 3>
        (store.global.auxJacks[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_OLED:
      #if BMC_MAX_OLED > 0
        deviceResponseData <1, 1>
        (store.layers[layer].oled[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_MINI_DISPLAY:
      #if BMC_MAX_MINI_DISPLAY > 0
        deviceResponseData <BMC_MAX_MINI_DISPLAY_SETTINGS, BMC_MAX_MINI_DISPLAY_EVENTS>
        (store.layers[layer].miniDisplay[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_LCD:
      #if BMC_MAX_LCD > 0
        deviceResponseData <1, 1>
        (store.layers[layer].lcd[index], buff, index, deviceType);
      #endif
      break;

    case BMC_DEVICE_ID_ILI:
      {
        // write new data and save, starts at byte 9
        #if BMC_MAX_ILI9341_BLOCKS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_ILI");
          bmcStoreDevice <BMC_ILI_S_COUNT,1>& item = store.layers[layer].ili[index];
          BMCUIData ui = BMCBuildData::getUIData(deviceType, -1);
          buff.appendToSysEx16Bits(ui.x);
          buff.appendToSysEx16Bits(ui.y);
          buff.appendToSysEx7Bits(ui.style);
          buff.appendToSysEx7Bits(ui.rotation);
          BMCUIData uiBlock = BMCBuildData::getUIData(deviceType, index);
          buff.appendToSysEx16Bits(uiBlock.x); // block x
          buff.appendToSysEx16Bits(uiBlock.y); // block y
          buff.appendToSysEx7Bits(uiBlock.style); // block size
          buff.appendToSysEx16Bits(uiBlock.other1); // block background
          buff.appendToSysEx16Bits(uiBlock.other2); // block color
          // name
          buff.appendToSysEx14Bits(item.name);
          buff.appendToSysEx7Bits(BMC_ILI_S_COUNT);// settings length
          buff.appendToSysEx7Bits(1);// events length
          // settings bytes
          for(uint8_t i=0;i<BMC_ILI_S_COUNT;i++){
            buff.appendToSysEx8Bits(item.settings[i]);
          }
          // events bytes
          for(uint8_t i=0;i<1;i++){
            buff.appendToSysEx14Bits(item.events[i]);
          }
        #endif
      }
      break;
    case BMC_DEVICE_ID_LFO:
      #if BMC_MAX_LFO > 0
        deviceResponseData<3, 5, uint8_t>
        (store.global.lfo[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_PRESET:
      #if BMC_MAX_PRESETS > 0
        deviceResponseData <1, BMC_MAX_PRESET_ITEMS>
        (store.global.presets[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_CUSTOM_SYSEX:
      #if BMC_MAX_CUSTOM_SYSEX > 0
        deviceResponseData <1, 16, uint8_t>
        (store.global.customSysEx[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_TRIGGER:
      #if BMC_MAX_TRIGGERS > 0
        deviceResponseData <1, 2>
        (store.global.triggers[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_TEMPO_TO_TAP:
      #if BMC_MAX_TEMPO_TO_TAP > 0
        deviceResponseData <1, 1>
        (store.global.tempoToTap[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_PORT_PRESET:
      deviceResponseData <0, 1, uint8_t>
        (store.global.portPresets[index], buff, index, deviceType);
      break;
    case BMC_DEVICE_ID_SHORTCUTS:
      deviceResponseData <0, 6, uint8_t>
        (store.global.shortcuts[index], buff, index, deviceType);
      break;
    case BMC_DEVICE_ID_PIXEL_PROGRAM:
      #if BMC_MAX_PIXEL_PROGRAMS > 0
        deviceResponseData <1, 8, uint8_t>
          (store.global.pixelPrograms[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_SKETCH_BYTE:
      #if BMC_MAX_SKETCH_BYTES > 0
        deviceResponseData <0, BMC_MAX_SKETCH_BYTES, uint8_t>
          (store.global.sketchBytes[0], buff, 0, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_SETLIST:
      #if BMC_MAX_SETLISTS > 0
        deviceResponseData <1, BMC_MAX_SETLISTS_SONGS>
        (store.global.setLists[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_SETLIST_SONG:

      break;
    case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:
      #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
        deviceResponseData <1, BMC_MAX_SETLISTS_SONG_PARTS>
        (store.global.songLibrary[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_TIMED_EVENT:
      #if BMC_MAX_TIMED_EVENTS > 0
        deviceResponseData <2, 1>
        (store.global.timedEvents[index], buff, index, deviceType);
      #endif
      break;
  }
  sendToEditor(buff);
}
// template <uint8_t sLen, uint8_t eLen, typename tname>
// void BMCEditor::incomingMessageDeviceWrite(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, int16_t layer, bool allowAnyValueForEvent){
//   uint16_t name = incoming.get14Bits(13);

//   item.name = (name <= BMC_MAX_NAMES_LIBRARY) ? name : 0;

//   uint8_t lenSettings = BMCTools::getMax(incoming.get7Bits(15), sLen);
//   uint8_t lenEvents = BMCTools::getMax(incoming.get7Bits(16), eLen);
//   uint8_t lenCount = 17;

//   for(uint8_t i = 0 ; i < lenSettings ; i++){
//     if(sLen > 0 && i < sLen){
//       item.settings[i] = incoming.get8Bits(lenCount);
//     }
//     lenCount += 2;
//   }

//   for(uint8_t i = 0 ; i < lenEvents ; i++){
//     if(eLen > 0 && i < eLen){
//       uint16_t e = incoming.get14Bits(lenCount);
//       if(!allowAnyValueForEvent && e > BMC_MAX_EVENTS_LIBRARY){
//         e = 0;
//       }
//       item.events[i] = e;
//     }
//     lenCount += 2;
//   }

//   if(layer >= 0 && !backupActive()){
//     saveLayersAndReloadData(layer);
//     reloadData();
//   }
// }

template <uint8_t sLen, uint8_t eLen, typename tname>
void BMCEditor::incomingMessageDeviceWrite(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, int16_t layer, bool allowAnyValueForEvent){
  uint16_t name = incoming.get14Bits(13);

  item.name = (name <= BMC_MAX_NAMES_LIBRARY) ? name : 0;

  uint8_t lenSettings = BMCTools::getMax(incoming.get7Bits(15), sLen);
  uint8_t lenEvents = BMCTools::getMax(incoming.get7Bits(16), eLen);
  uint8_t lenCount = 17;

  for(uint8_t i = 0 ; i < lenSettings ; i++, lenCount += 2){
    if(sLen > 0 && i < sLen){
      item.settings[i] = incoming.get8Bits(lenCount);
    }
  }

  for(uint8_t i = 0 ; i < lenEvents ; i++, lenCount += 2){
    if(eLen > 0 && i < eLen){
      uint16_t eventValue = incoming.get14Bits(lenCount);
      item.events[i] = (!allowAnyValueForEvent && eventValue > BMC_MAX_EVENTS_LIBRARY) ? 0 : eventValue;
    }
  }

  if(layer >= 0 && !backupActive()){
    saveLayersAndReloadData(layer);
    reloadData();
  }
}

template <uint8_t sLen, uint8_t eLen, typename tname>
void BMCEditor::deviceResponseData(bmcStoreDevice<sLen, eLen, tname>& item,
                                    BMCMidiMessage& buff,
                                    uint16_t index, uint8_t deviceType){
  BMCUIData ui = BMCBuildData::getUIData(deviceType, index);
  buff.appendToSysEx14Bits(ui.pins[0]);
  buff.appendToSysEx14Bits(ui.pins[1]);
  buff.appendToSysEx14Bits(ui.pins[2]);
  
  buff.appendToSysEx16Bits(ui.x);
  buff.appendToSysEx16Bits(ui.y);
  buff.appendToSysEx7Bits(ui.style);
  buff.appendToSysEx7Bits(ui.rotation);
  buff.appendToSysEx7Bits(ui.mergeType);
  buff.appendToSysEx14Bits(ui.mergeIndex);
  // other1 is used for color, so only other1 is sent
  buff.appendToSysEx7Bits(ui.other1);
  buff.appendToSysEx14Bits(item.name);// name
  buff.appendToSysEx7Bits(sLen);// settings length
  buff.appendToSysEx7Bits(eLen);// events length
  // settings bytes
  for(uint8_t i=0;i<sLen;i++){
    buff.appendToSysEx8Bits(item.settings[i]);
  }
  // events bytes
  for(uint8_t i=0;i<eLen;i++){
    buff.appendToSysEx14Bits(item.events[i]);
  }
}
void BMCEditor::connectEditor(){
  
  if(isWriteMessage()){
    // editor trying to connect
    if(midi.globals.editorConnected()){
      // send a notification that editor is already connected
      BMC_WARNING(
        "Already Connected to Editor",
        BMCTools::getPortName(incoming.getPort())
      );
      sendNotification(BMC_NOTIFY_CONNECTION, 2, true, true);
      return;
    } else if(midi.globals.onBoardEditorActive()){
      sendNotification(BMC_NOTIFY_CONNECTION, 3, true, true);
      BMC_WARNING(
        "On Board Editor is Active",
        BMCTools::getPortName(incoming.getPort())
      );
      return;
    }
  } else {
    // return editor connection state
    sendNotification(BMC_NOTIFY_CONNECTION, 1);
    return;
  }

  BMC_INFO(
    "Connecting to Editor on",
    BMCTools::getPortName(incoming.getPort())
  );

  port = incoming.getPort();
  midi.globals.setEditorConnected(true);
  flags.on(BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR);
  flags.on(BMC_EDITOR_FLAG_CONNECTION_HAS_CHANGED);
  // respond with a connection message with the sysex id as the code
  sendNotification(BMC_NOTIFY_CONNECTION, BMC_EDITOR_SYSEX_ID);
}

void BMCEditor::keepConnectionAlive(){
  #if defined(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT)
    if(connected() && editorHasConnectionAliveOption){
      // BMC_PRINTLN("Reset editor connection timer");
      connectionAliveTimer.start(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT);
    }
  #endif
}

void BMCEditor::disconnectEditor(){
  if(isValidGlobalMessage()){
    if(!isWriteMessage()){
      // notify if message doesnt have a write flag
      return;
    }
  } else {
    sendNotification(BMC_NOTIFY_CONNECTION, 1);
    return;
  }
  BMC_INFO("Disconnecting from Editor... Bye!!");
  disconnect();
}
void BMCEditor::forceDisconnectEditor(){
  // to force disconnect all we really need is to make sure that the device id
  // is the same
  if(!isWriteMessage() || !midi.globals.editorConnected() || getMessageDeviceId() != deviceId){
    // notify: message not properly set up
    return;
  }

  BMC_INFO("FORCED: Disconnecting from Editor... Bye!!");

  disconnect();
}
void BMCEditor::disconnect(bool t_notify){
  // cancel the back if it's active
  backupCancel();
  // request this to reset all variables properly
  getBackupStatus();

  // send notification before resetting the editor port
  if(t_notify){
    sendNotification(BMC_NOTIFY_CONNECTION, 0);
  }

  port = 0;
  midi.globals.setEditorConnected(false);
  flags.off(BMC_EDITOR_FLAG_EDITOR_FEEDBACK);
  flags.off(BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR);
  flags.on(BMC_EDITOR_FLAG_CONNECTION_HAS_CHANGED);
  flags.on(BMC_EDITOR_FLAG_EDITOR_DISCONNECTED);
  #if defined(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT)
    connectionAliveTimer.stop();
    editorHasConnectionAliveOption = false;
  #endif
}
void BMCEditor::globalBuildInfoMessage(){// BMC_GLOBALF_BUILD_INFO
  if(!isValidGlobalMessage()){
    return;
  }

  // build info flags will return all the compiled settings for this build
  uint16_t itemId = getMessageLayerNumber();
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_BUILD_INFO, 0,
    itemId
  );

  // first 2 bytes is the number of items
  if(itemId == BMC_GLOBALF_BUILD_INFO_FLAGS){
    uint32_t buildData = 0;
    #ifdef BMC_USB_HOST_ENABLED
      bitWrite(buildData,0,1);
    #endif
    #ifdef BMC_MIDI_SERIAL_A_ENABLED
      bitWrite(buildData,1,1);
    #endif
    #ifdef BMC_MIDI_SERIAL_B_ENABLED
      bitWrite(buildData,2,1);
    #endif
    #ifdef BMC_MIDI_SERIAL_C_ENABLED
      bitWrite(buildData,3,1);
    #endif
    #ifdef BMC_MIDI_SERIAL_D_ENABLED
      bitWrite(buildData,4,1);
    #endif
    #ifdef BMC_MIDI_BLE_ENABLED
      bitWrite(buildData,5,1);
    #endif
    #ifdef BMC_SD_CARD_ENABLED
      bitWrite(buildData,6,1);
    #endif
    #ifdef BMC_USE_24LC256
      bitWrite(buildData,7,1);
    #endif
    #ifdef BMC_DEBUG
      bitWrite(buildData,8,1);
    #endif
    #ifdef BMC_USE_CLICK_TRACK
      bitWrite(buildData,9,1);
    #endif
    #ifdef BMC_HAS_HARDWARE
      bitWrite(buildData,10,1);
    #endif
    #ifdef BMC_USE_TIME
      bitWrite(buildData,11,1);
    #endif
    #ifdef BMC_USE_HELIX
      bitWrite(buildData,12,1);
    #endif
    #ifdef BMC_USE_BEATBUDDY
      bitWrite(buildData,13,1);
    #endif
    #ifdef BMC_USE_FAS
      bitWrite(buildData,14,1);
    #endif
    #ifdef BMC_USE_KEMP
      bitWrite(buildData,15,1);
    #endif
    #ifdef BMC_USE_FAS3
      bitWrite(buildData, 16, 1);
    #endif

    bitWrite(buildData, 17, BMC_ILI_S_COUNT == 2 ? 1 : 0);


   
    #ifdef BMC_USE_CUSTOM_UI
      bitWrite(buildData, 18, 1);
    #endif
    
    #ifdef BMC_USE_DAW_LC
      bitWrite(buildData, 19, 1);
    #endif
    #ifdef BMC_USE_ILI9341
      bitWrite(buildData, 20, 1);
    #endif
    #ifdef BMC_HAS_TOUCH_SCREEN
      bitWrite(buildData, 21, 1);
    #endif
    #if defined(BMC_TFT_SIZE) && BMC_TFT_SIZE != 1
      bitWrite(buildData, 22, 1);
    #endif
    #if BMC_OLED_HEIGHT==32
      bitWrite(buildData, 23, 1);
    #endif

    #if BMC_MAX_MINI_DISPLAY > 0 && BMC_MAX_MINI_DISPLAY_EVENTS == 2
      bitWrite(buildData, 24, 1);
    #endif

    #if defined(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT)
      bitWrite(buildData, 25, 1);
    #endif

    #ifdef BMC_FS_ENABLED
      bitWrite(buildData, 26, 1);
    #endif

    

    // remove after out of beta
    bitWrite(buildData, 31, 1);

    // byte 9
    buff.appendToSysEx7Bits(BMC_MCU_MODEL);
    buff.appendToSysEx32Bits(BMC_SEM_VERSION);
    buff.appendToSysEx16Bits(store.version);
    buff.appendToSysEx32Bits(sizeof(bmcStore));
    buff.appendToSysEx32Bits(buildData);
    
    // BMC 2.0
    buff.appendToSysEx14Bits(BMC_MAX_EVENTS_LIBRARY);
    buff.appendToSysEx14Bits(BMC_MAX_NAMES_LIBRARY);
    buff.appendToSysEx7Bits(BMC_MAX_NAMES_LENGTH);

    buff.appendToSysEx14Bits(BMC_MAX_PRESETS);
    buff.appendToSysEx7Bits(BMC_MAX_PRESET_BANKS);
    buff.appendToSysEx7Bits(BMC_MAX_PRESETS_PER_BANK);
    buff.appendToSysEx7Bits(BMC_MAX_PRESET_ITEMS);

    buff.appendToSysEx7Bits(BMC_MAX_CUSTOM_SYSEX);
    buff.appendToSysEx7Bits(BMC_MAX_TRIGGERS);
    buff.appendToSysEx7Bits(BMC_MAX_TEMPO_TO_TAP);
    buff.appendToSysEx7Bits(BMC_MAX_SKETCH_BYTES);
    buff.appendToSysEx7Bits(BMC_MAX_PIXEL_PROGRAMS);
    buff.appendToSysEx7Bits(BMC_MAX_TIMED_EVENTS);
    // setlist
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS);
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONGS);
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONG_PARTS);
    buff.appendToSysEx14Bits(BMC_MAX_SETLISTS_SONGS_LIBRARY);
    //layers
    buff.appendToSysEx14Bits(BMC_MAX_LAYERS);
    // hardware
    buff.appendToSysEx14Bits(BMC_MAX_BUTTON_EVENTS);
    buff.appendToSysEx14Bits(BMC_MAX_BUTTONS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_BUTTONS);
    buff.appendToSysEx14Bits(BMC_MAX_ENCODERS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_ENCODERS);
    buff.appendToSysEx14Bits(BMC_MAX_POTS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_POTS);

    buff.appendToSysEx14Bits(BMC_MAX_LEDS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_LEDS);

    buff.appendToSysEx14Bits(BMC_MAX_BI_LEDS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_BI_LEDS);

    buff.appendToSysEx14Bits(BMC_MAX_TRI_LEDS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_TRI_LEDS);

    buff.appendToSysEx14Bits(BMC_MAX_PIXELS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_PIXELS);
    buff.appendToSysEx14Bits(BMC_MAX_RGB_PIXELS);
    buff.appendToSysEx14Bits(BMC_MAX_GLOBAL_RGB_PIXELS);
    buff.appendToSysEx14Bits(BMC_MAX_NL_RELAYS);
    buff.appendToSysEx14Bits(BMC_MAX_L_RELAYS);
    buff.appendToSysEx14Bits(BMC_MAX_AUX_JACKS);
    buff.appendToSysEx7Bits(BMC_MAX_OLED);
    buff.appendToSysEx7Bits(BMC_MAX_ILI9341_BLOCKS);
    buff.appendToSysEx7Bits(BMC_MAX_LFO);
    buff.appendToSysEx7Bits(BMC_MAX_PIXEL_STRIP);
    buff.appendToSysEx7Bits(BMC_MAX_MAGIC_ENCODERS);
    buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_MAGIC_ENCODERS);
    buff.appendToSysEx7Bits(BMC_MAX_LAYER_EVENTS);
    buff.appendToSysEx7Bits(BMC_MAX_LINKS);
    buff.appendToSysEx7Bits(BMC_MAX_MINI_DISPLAY);
    buff.appendToSysEx7Bits(BMC_MAX_LCD);
    buff.appendToSysEx7Bits(BMC_LCD_CHARS);
    buff.appendToSysEx7Bits(BMC_CUSTOM_UI_ID);
    buff.appendToSysEx14Bits(BMC_PIXELS_MAX_CURRENT);
    
    

  } else if(itemId==BMC_GLOBALF_BUILD_INFO_DEVICE_NAME){
    String name = BMC_DEVICE_NAME;
    buff.appendToSysEx7Bits(name.length()+1);
    buff.appendCharArrayToSysEx(name);
  }
  sendToEditor(buff);
}
// See info in BMC-Editor.cpp
void BMCEditor::globalStoreAddress(bool write){
  if(!isValidGlobalMessage(false)){
    return;
  }
  uint8_t sysExLength = 12;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    // write new data and save, starts at byte 9
    if(maxStoreAddresses()>1 && incoming.sysex[9] != storeAddress){
      BMC_PRINTLN("change store address received");
      if(changeStoreLocal(incoming.sysex[9])){
        BMC_PRINTLN("Store changed to",incoming.sysex[9]);
        reloadData();
      }
    }
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_STORE_ADDRESS, 0,
    0
  );
  buff.appendToSysEx7Bits(storeAddress);
  sendToEditor(buff);
}

void BMCEditor::globalBackupMessage(bool write){
  if(!midi.globals.editorConnected() || !isValidGlobalMessage(false) || !write){
    return;
  }
  uint8_t sysExLength = 12;
  if(incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  // 0 = ignored
  // 1 = start backup
  // 2 = backup complete
  // 3 = cancel backup
  uint8_t newStatus = incoming.sysex[9];
  bool isComplete = false;
  // check and/or change the status of the backup
  if(newStatus == 1){
    backupStart();
  } else if(newStatus == 2){
    isComplete = backupComplete();
  } else if(newStatus == 3){
    backupCancel();
  }
  globalSendBackupStatus();
  if(isComplete){
    saveStore();
    reloadData();
  }
}
void BMCEditor::globalSendBackupStatus(){
  BMCEditorMidiFlags flag;
  flag.setWrite(true);
  flag.setBackup(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_BACKUP, flag, 0
  );
  // is the backup active? byte 9
  buff.appendToSysEx7Bits( flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE) );
  // send the status in byte 10
  buff.appendToSysEx7Bits( getBackupStatus() );
  sendToEditor(buff);
}


void BMCEditor::globalSettingsMessage(bool write){// BMC_GLOBALF_SETTINGS
  if(!isValidGlobalMessage(false)){
    return;
  }
  // used if the deviceId has changed
  bool triggerDisconnect = false;

  uint8_t sysExLength = 77;
  // BMC_PRINTLN("Settings Length",incoming.size(),"required",sysExLength);
  // handle backup
  if(write && backupActive()){
    backupGlobalSettings(sysExLength);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalSettings& item = store.global.settings;
    item.flags = incoming.get32Bits(9);
    uint8_t e = 14;
    for(uint8_t i = 0; i < 8 ; i++){
      item.data[i] = incoming.get32Bits(e);
      e += 5;
    }
    for(uint8_t i = 0; i < 7 ; i++){
      item.routing[i] = incoming.get16Bits(e);
      e += 3;
    }
    if(deviceId != settings.getDeviceId()){
      triggerDisconnect = true;
    }
    saveSettings();
    reloadData();
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_SETTINGS, 0,
    layer
  );
  buff.appendToSysEx7Bits(maxStoreAddresses());
  buff.appendToSysEx7Bits(storeAddress);
  // settings flags, 32 bits, 4 (7-bit) bytes
  buff.appendToSysEx32Bits(store.global.settings.flags);
  // settings data blocks, 8 * 32 bits, 5 (7-bit) bytes per block
  for(uint8_t i = 0 ; i < 8 ; i++){
    buff.appendToSysEx32Bits(store.global.settings.data[i]);
  }
  for(uint8_t i = 0 ; i < 7 ; i++){
    buff.appendToSysEx16Bits(store.global.settings.routing[i]);
  }
  sendToEditor(buff);

  if(triggerDisconnect){
    //if the device id has changed we'll disconnect then set the new device id
    BMC_INFO("Disconnecting from Editor... Bye!!");
    disconnect(true);
    deviceId = settings.getDeviceId();
  }
}
/*
void BMCEditor::globalStartup(bool write){
  if(!isValidGlobalMessage(false)){
    return;
  }
  uint8_t sysExLength = 13;
  // handle backup
  if(write && backupActive()){
    backupGlobalStartup(sysExLength);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_PRESETS > 0
  if(write){
    uint16_t index = incoming.get14Bits(9);
    if(index >= BMC_MAX_PRESETS){
      sendNotification(BMC_NOTIFY_INVALID_PRESET, index, true);
      return;
    }
    // write new data and save, starts at byte 9
    // index of the library message we are writting to
    store.global.startup = index;
    if(!backupActive()){
      saveStartup();
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_STARTUP, 0, 0);
  #if BMC_MAX_PRESETS > 0
    buff.appendToSysEx14Bits(store.global.startup);
  #else
    buff.appendToSysEx14Bits(0);
  #endif

  sendToEditor(buff);
}
*/
void BMCEditor::globalPotCalibration(){//BMC_GLOBALF_POT_CALIBRATION
/*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t index = getMessageLayerNumber();
  if(index >= BMC_TOTAL_POTS_AUX_JACKS){
    BMC_PRINTLN("BMC_NOTIFY_INVALID_POT", index);
    sendNotification(BMC_NOTIFY_INVALID_POT, index, true);
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_POT_CALIBRATION, 0,
    index
  );
  buff.appendToSysEx7Bits(BMC_TOTAL_POTS_AUX_JACKS); // 9
  #if BMC_TOTAL_POTS_AUX_JACKS > 0
    buff.appendToSysEx16Bits(store.global.potCalibration[index].min);
    buff.appendToSysEx16Bits(store.global.potCalibration[index].max);
  #endif
  sendToEditor(buff);
  */
}

void BMCEditor::globalSketchBytesData(){
  if(!isValidGlobalMessage()){
    return;
  }
  uint16_t index = getMessageLayerNumber();
  if(index>0 && index>=BMC_MAX_SKETCH_BYTES){
    sendNotification(BMC_NOTIFY_INVALID_SKETCH_BYTE_DATA, index, true);
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_SKETCH_BYTES_DATA, 0,
    index
  );
  buff.appendToSysEx7Bits(BMC_MAX_SKETCH_BYTES);
  #if BMC_MAX_SKETCH_BYTES > 0
    BMCSketchByteData data = BMCBuildData::getSketchByteData(index);
    buff.appendCharArrayToSysEx(data.name, BMC_NAME_LEN_SKETCH_BYTES);
    buff.appendToSysEx8Bits(data.min);
    buff.appendToSysEx8Bits(data.max);
    buff.appendToSysEx8Bits(data.step);
    buff.appendToSysEx8Bits(data.formatType);
    buff.appendToSysEx8Bits(data.formatValue);
    buff.appendToSysEx8Bits(data.formatAppend);
  #endif
  sendToEditor(buff);
}

void BMCEditor::globalSetTime(bool write){
  //BMC_GLOBALF_TIME
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t valid = 0;
  #if defined(BMC_USE_TIME)
    uint8_t sysExLength = 18;
    if(write){
      if(incoming.size() >= sysExLength){
        valid = 2;
        uint8_t n = 9;
        uint8_t h = incoming.get7Bits(n++);
        uint8_t m = incoming.get7Bits(n++);
        uint8_t s = incoming.get7Bits(n++);
        uint8_t d = incoming.get7Bits(n++);
        uint8_t mo = incoming.get7Bits(n++);
        uint16_t y = incoming.get16Bits(n);
        setRTCTime(h,m,s,d,mo,y);
      }
    } else {
      valid = 1;
    }
  #endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_TIME, 0,
    valid
  );
  #if defined(BMC_USE_TIME)
    buff.appendToSysEx7Bits(getHour());
    buff.appendToSysEx7Bits(getMinute());
    buff.appendToSysEx7Bits(getSecond());
    buff.appendToSysEx7Bits(getDay());
    buff.appendToSysEx7Bits(getMonth());
    buff.appendToSysEx16Bits(getYear());
  #endif
  sendToEditor(buff);
}
void BMCEditor::globalEditorFeedback(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = BMC_EDITOR_SYSEX_MIN_LENGTH+1;
  if(write && incoming.size()>=sysExLength){
    uint8_t status = incoming.get7Bits(9);
    flags.write(BMC_EDITOR_FLAG_EDITOR_FEEDBACK,status > 0);
    BMC_INFO("Editor Feedback:", status?"Enabled":"Disabled");
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_EDITOR_FEEDBACK, 0, 0
  );
  buff.appendToSysEx7Bits(flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK));
  sendToEditor(buff);
}
void BMCEditor::globalEditorMetrics(){
  if(!isValidGlobalMessage()){
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_EDITOR_GET_METRICS, 0, 0
  );
  buff.appendToSysEx32Bits(midi.globals.getCPU());
  buff.appendToSysEx32Bits(midi.globals.getRAM());
  sendToEditor(buff);
}
void BMCEditor::globalEditorErase(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  BMC_PRINTLN("EEPROM ERASE");

  bool success = false;
  if(getMessageLayerNumber() == 0x3FFF){
    BMC_PRINTLN("ERASE OK");
    success = true;
    storeErase(false);
    delay(1000);
  } else {
    BMC_PRINTLN("ERASE ERROR");
  }
  
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_ERASE, 0, 0
  );
  buff.appendToSysEx7Bits(success);
  sendToEditor(buff);
}
void BMCEditor::globalEditorMessenger(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t accepted = 0;
  uint8_t sysExLength = BMC_EDITOR_SYSEX_MIN_LENGTH+1;
  if(write && incoming.size()>=sysExLength){
    messenger.reset();
    messenger.status = incoming.get16Bits(9);
    messenger.value = incoming.get32Bits(12);
    messenger.strLen = incoming.get7Bits(17);
    if(messenger.strLen>0){
      incoming.getStringFromSysEx(18, messenger.string, messenger.strLen);
    }
    accepted = 1;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_EDITOR_MESSENGER, 0, 0
  );
  // send a 0 as the first data byte to notify the app that this a response
  // not a message from the app
  buff.appendToSysEx7Bits(0);
  buff.appendToSysEx7Bits(accepted);
  sendToEditor(buff);

  if(accepted==1 && midi.callback.messengerReceived){
    midi.callback.messengerReceived(messenger);
  }
}

void BMCEditor::globalEditorPerformMode(bool write){
  //
}
