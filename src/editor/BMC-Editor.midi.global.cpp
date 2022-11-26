/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

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
        BMC_PRINTLN("BMC_GLOBALF_EDITOR_FETCH_COMPLETE");
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
    case BMC_GLOBALF_STRING_LIBRARY:
      globalStringLibrary(isWriteMessage());
      break;
    case BMC_GLOBALF_LIBRARY:
      globalLibrary(isWriteMessage());
      break;
    case BMC_GLOBALF_PRESET:
      globalPreset(isWriteMessage());
      break;
    case BMC_GLOBALF_STARTUP:
      globalStartup(isWriteMessage());
      break;
    case BMC_GLOBALF_STORE_ADDRESS:
      globalStoreAddress(isWriteMessage());
      break;
    case BMC_GLOBALF_BUTTON:
      globalButton(isWriteMessage());
      break;
    case BMC_GLOBALF_BUTTON_EVENT_SHIFT_POSITION:
      globalButtonEventShiftPositionMessage(isWriteMessage());
      break;
    case BMC_GLOBALF_ENCODER:
      globalEncoder(isWriteMessage());
      break;
    case BMC_GLOBALF_POT:
      globalPot(isWriteMessage());
      break;
    case BMC_GLOBALF_LEDS:
      globalLeds(isWriteMessage());
      break;
    case BMC_GLOBALF_POT_CALIBRATION:
      globalPotCalibration();
      break;
    case BMC_GLOBALF_GLOBAL_POT_CALIBRATION:
      //globalGlobalPotCalibration();
      break;
    case BMC_GLOBALF_CUSTOM_SYSEX:
      globalCustomSysEx(isWriteMessage());
      break;
    case BMC_GLOBALF_TRIGGERS:
      //globalTriggers(isWriteMessage());
      break;
    case BMC_GLOBALF_TIMED_EVENTS:
      globalTimedEvents(isWriteMessage());
      break;
    case BMC_GLOBALF_TEMPO_TO_TAP:
      //globalTempoToTap(isWriteMessage());
      break;
    case BMC_GLOBALF_SKETCH_BYTES:
      globalSketchBytes(isWriteMessage());
      break;
    case BMC_GLOBALF_SKETCH_BYTES_DATA:
      globalSketchBytesData();
      break;
    case BMC_GLOBALF_NL_RELAYS:
      globalNLRelay(isWriteMessage());
      break;
    case BMC_GLOBALF_L_RELAYS:
      globalLRelay(isWriteMessage());
      break;
    case BMC_GLOBALF_TIME:
      globalSetTime(isWriteMessage());
      break;
    case BMC_GLOBALF_PORTS_PRESETS:
      globalPortPresets(isWriteMessage());
      break;
    case BMC_GLOBALF_SETLISTS:
      globalSetList(isWriteMessage());
      break;
    case BMC_GLOBALF_SETLISTS_SONG:
      globalSetListSong(isWriteMessage());
      break;
    case BMC_GLOBALF_SETLISTS_SONG_SHIFT_POSITION:
      globalSetListSongPartShiftPosition(isWriteMessage());
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
    case BMC_GLOBALF_PIXEL_PROGRAM:
      globalPixelProgram(isWriteMessage());
      break;
    case BMC_GLOBALF_EDITOR_PERFORM_MODE:
      // no yet implemented, its meant to be a customizable screen
      // for easy editing that only loads the data of the current page and
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
  }
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
  uint16_t index = getMessagePageNumber();
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
  uint16_t index = getMessagePageNumber();
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
  // handle backup
  if(write && backupActive()){
    //backupEventMessage(sysExLength);
    return;
  }
  //BMC_PRINTLN("RECEIVED DEVICE REQUEST");

  uint8_t deviceType = incoming.get8Bits(9);
  uint16_t index = incoming.get14Bits(11);

  uint16_t maxDevices = checkIfHardwareAvailable(deviceType);
  uint8_t page = getMessagePageNumber();

  // bytes 13 and 14 have the name pointer
  sysExLength += (incoming.get7Bits(15) * 2);
  sysExLength += (incoming.get7Bits(16) * 2);

  if(index>0 && index>=maxDevices){
    sendNotification(BMC_NOTIFY_INVALID_DEVICE, index, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    BMC_PRINTLN("******************* incoming.size()",incoming.size(),"sysExLength",sysExLength);
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write && maxDevices > 0){
    uint16_t pageToWrite = page;
    uint16_t maxPageToWrite = page+1;
    if(isDeviceWriteToAllPages()){
      pageToWrite = 0;
      maxPageToWrite = BMC_MAX_PAGES;
      BMC_PRINTLN("Save to all pages",pageToWrite, maxPageToWrite);
    } else {
      BMC_PRINTLN("DO NOT Save to all pages",pageToWrite, maxPageToWrite);
    }
    switch(deviceType){
      case BMC_DEVICE_ID_PAGE:
        {
          // write new data and save, starts at byte 13
          store.pages[index].name     = incoming.get14Bits(13);
          if(!backupActive()){
            savePagesAndReloadData(page);
          }
        }
        break;
      case BMC_DEVICE_ID_BUTTON:
        {
          #if BMC_MAX_BUTTONS > 0
            for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
              incomingMessageDeviceWrite<BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>(store.pages[p].buttons[index], index, p);
            }
          #endif
        }
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
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.pages[p].leds[index], index, p);
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
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,2>(store.pages[p].biLeds[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          incomingMessageDeviceWrite<1,2>(store.global.biLeds[index], index);
          if(!backupActive()){
            saveGlobalBiLed(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_TRI_LED:
        #if BMC_MAX_TRI_LEDS > 0
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,3>(store.pages[p].triLeds[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          incomingMessageDeviceWrite<1,3>(store.global.triLeds[index], index);
          if(!backupActive()){
            saveGlobalTriLed(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_ENCODER:
        #if BMC_MAX_ENCODERS > 0
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.pages[p].encoders[index], index, p);
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
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,3>(store.pages[p].pots[index], index, p);
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
      case BMC_DEVICE_ID_PIXEL:
        #if BMC_MAX_PIXELS > 0
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.pages[p].pixels[index], index, p);
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
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,3>(store.pages[p].rgbPixels[index], index, p);
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
      case BMC_DEVICE_ID_OLED:
        #if BMC_MAX_OLED > 0
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.pages[p].oled[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_ILI:
        #if BMC_MAX_ILI9341_BLOCKS > 0
          for(uint16_t p = pageToWrite ; p < maxPageToWrite ; p++){
            incomingMessageDeviceWrite<1,1>(store.pages[p].ili[index], index, p);
          }
        #endif
        break;
      case BMC_DEVICE_ID_LIBRARY:
        {
          //
        }
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
      case BMC_DEVICE_ID_CUSTOM_SYSEX:
        {
          //
        }
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
          incomingMessageDeviceWrite<1,1>(store.global.tempoToTap[index], index);
          if(!backupActive()){
            flags.on(BMC_EDITOR_FLAG_EDITOR_TEMPO_TO_TAP_UPDATED);
            saveTempoToTap(index);
            reloadData();
          }
        #endif
        break;
      case BMC_DEVICE_ID_SKETCH_BYTES:
        {
          //
        }
        break;
      case BMC_DEVICE_ID_STRING_LIBRARY:
        {
          //
        }
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
        {
          //
        }
        break;
    }
  }

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_EDITOR_FUNCTION_DEVICE, 0,
    page
  );

  buff.appendToSysEx7Bits(deviceType);
  buff.appendToSysEx14Bits(index);
  buff.appendToSysEx14Bits(maxDevices);
  switch(deviceType){
    case BMC_DEVICE_ID_PAGE:
      {
        //BMC_PRINTLN("BMC_DEVICE_ID_PAGE");
        // page names only include the name
        buff.appendToSysEx14Bits(store.pages[index].name);
      }
      break;
    case BMC_DEVICE_ID_BUTTON:
      {
        #if BMC_MAX_BUTTONS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_BUTTON");
          deviceResponseData <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>
          (store.pages[page].buttons[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_BUTTON:
      {
        #if BMC_MAX_GLOBAL_BUTTONS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_GLOBAL_BUTTON");
          deviceResponseData <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>
          (store.global.buttons[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_LED:
      {
        #if BMC_MAX_LEDS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_LED");
          deviceResponseData <1, 1>
          (store.pages[page].leds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_LED:
      {
        #if BMC_MAX_GLOBAL_LEDS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_GLOBAL_LED");
          deviceResponseData <1, 1>
          (store.global.leds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_BI_LED:
      {
        #if BMC_MAX_BI_LEDS > 0
          deviceResponseData <1, 2>
          (store.pages[page].biLeds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_BI_LED:
      {
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          deviceResponseData <1, 2>
          (store.global.biLeds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_TRI_LED:
      {
        #if BMC_MAX_TRI_LEDS > 0
          deviceResponseData <1, 3>
          (store.pages[page].triLeds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_TRI_LED:
      {
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          deviceResponseData <1, 3>
          (store.global.triLeds[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_ENCODER:
      {
        #if BMC_MAX_ENCODERS > 0
          deviceResponseData <1, 1>
          (store.pages[page].encoders[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_ENCODER:
      {
        #if BMC_MAX_GLOBAL_ENCODERS > 0
          deviceResponseData <1, 1>
          (store.global.encoders[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_POT:
      {
        #if BMC_MAX_POTS > 0
          deviceResponseData <1, 3>
          (store.pages[page].pots[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_GLOBAL_POT:
      {
        #if BMC_MAX_GLOBAL_POTS > 0
          deviceResponseData <1, 3>
          (store.global.pots[index], buff, index, deviceType);
        #endif
      }
      break;
    case BMC_DEVICE_ID_PIXEL:
      #if BMC_MAX_PIXELS > 0
        deviceResponseData <1, 1>
        (store.pages[page].pixels[index], buff, index, deviceType);
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
        (store.pages[page].rgbPixels[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
      #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
        deviceResponseData <1, 3>
        (store.global.rgbPixels[index], buff, index, deviceType);
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
        (store.pages[page].oled[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_ILI:
      {
        // write new data and save, starts at byte 9
        #if BMC_MAX_ILI9341_BLOCKS > 0
          //BMC_PRINTLN("BMC_DEVICE_ID_ILI");
          bmcStoreDevice <1,1>& item = store.pages[page].ili[index];
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
          buff.appendToSysEx7Bits(1);// settings length
          buff.appendToSysEx7Bits(1);// events length
          // settings bytes
          for(uint8_t i=0;i<1;i++){
            buff.appendToSysEx8Bits(item.settings[i]);
          }
          // events bytes
          for(uint8_t i=0;i<1;i++){
            buff.appendToSysEx14Bits(item.events[i]);
          }
        #endif
      }
      break;
    case BMC_DEVICE_ID_LIBRARY:
      {
        //
      }
      break;
    case BMC_DEVICE_ID_PRESET:
      #if BMC_MAX_PRESETS > 0
        deviceResponseData <1, BMC_MAX_PRESET_ITEMS>
        (store.global.presets[index], buff, index, deviceType);
      #endif
      break;
    case BMC_DEVICE_ID_CUSTOM_SYSEX:
      {
        //
      }
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
    case BMC_DEVICE_ID_SKETCH_BYTES:
      {
        //
      }
      break;
    case BMC_DEVICE_ID_STRING_LIBRARY:
      {
        //
      }
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
      {
        //
      }
      break;
  }
  sendToEditor(buff);
}
template <uint8_t sLen, uint8_t eLen>
void BMCEditor::incomingMessageDeviceWrite(bmcStoreDevice<sLen, eLen>& item, uint16_t index, int16_t page){
  //BMC_PRINTLN("====================");
  uint16_t name = incoming.get14Bits(13);
  if(item.name!= name){
    item.name  = name;
  }
  uint8_t lenEvents = incoming.get7Bits(15);
  uint8_t lenSettings = incoming.get7Bits(16);
  uint8_t lenCount = 17;
  for(uint8_t i = 0 ; i < lenEvents ; i++){
    uint8_t value = incoming.get8Bits(lenCount);
    if(item.settings[i] != value){
      item.settings[i]  = value;
    }
    lenCount += 2;
  }
  for(uint8_t i = 0 ; i < lenSettings ; i++){
    uint16_t value = incoming.get14Bits(lenCount);
    if(item.events[i] != value){
      item.events[i]  = value;
    }
    lenCount += 2;
  }
  if(page >= 0){
    BMC_PRINTLN("************* SAVE PAGES AND RELOAD", page);
    savePagesAndReloadData(page);
    reloadData();
  }
}

template <uint8_t slen, uint8_t elen>
void BMCEditor::deviceResponseData(bmcStoreDevice<slen, elen>& item,
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
  buff.appendToSysEx7Bits(slen);// settings length
  buff.appendToSysEx7Bits(elen);// events length
  // settings bytes
  for(uint8_t i=0;i<slen;i++){
    buff.appendToSysEx8Bits(item.settings[i]);
  }
  // events bytes
  for(uint8_t i=0;i<elen;i++){
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
        BMCTools::getPortName(port)
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
}
void BMCEditor::globalBuildInfoMessage(){// BMC_GLOBALF_BUILD_INFO
  if(!isValidGlobalMessage()){
    return;
  }

  // build info flags will return all the compiled settings for this build
  uint16_t itemId = getMessagePageNumber();
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
    // bit 16 available
    // bit 17 available
    #ifdef BMC_USE_FAS3
      bitWrite(buildData,18,1);
    #endif
    #ifdef BMC_USE_DAW_LC
      bitWrite(buildData,19,1);
    #endif
    #ifdef BMC_USE_ILI9341
      bitWrite(buildData,20,1);
    #endif


    // remove after out of beta
    bitWrite(buildData, 31, 1);

    // byte 9
    buff.appendToSysEx7Bits(BMC_TEENSY_MODEL);
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
    buff.appendToSysEx7Bits(BMC_MAX_STRING_LIBRARY);
    buff.appendToSysEx7Bits(BMC_MAX_PIXEL_PROGRAMS);
    buff.appendToSysEx7Bits(BMC_MAX_TIMED_EVENTS);
    // setlist
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS);
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONGS);
    buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONG_PARTS);
    buff.appendToSysEx14Bits(BMC_MAX_SETLISTS_SONGS_LIBRARY);
    //pages
    buff.appendToSysEx14Bits(BMC_MAX_PAGES);
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

  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_BUTTONS){
    // byte 9
    // button pins
    buff.appendToSysEx8Bits(BMC_MAX_BUTTONS);
    #if BMC_MAX_BUTTONS > 0
      for(uint8_t i=0;i<BMC_MAX_BUTTONS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_BUTTON, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
      }
    #endif

  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_BUTTONS){
    // byte 9
    // button pins
    buff.appendToSysEx8Bits(BMC_MAX_GLOBAL_BUTTONS);
    #if BMC_MAX_GLOBAL_BUTTONS > 0
      for(uint8_t i=0;i<BMC_MAX_GLOBAL_BUTTONS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_BUTTON, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_ENCODERS){
    // encoder pins
    buff.appendToSysEx8Bits(BMC_MAX_GLOBAL_ENCODERS);
    #if BMC_MAX_GLOBAL_ENCODERS > 0
      for(uint8_t i=0;i<BMC_MAX_GLOBAL_ENCODERS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_ENCODER, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
        buff.appendToSysEx7Bits(ui.pins[1]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_2 ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_3 ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_4
  ){
    uint8_t min = 0;
    uint8_t max = 32;
    if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_2){
      min = 32;
      max = 64;
    } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_3){
      min = 64;
      max = 96;
    } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_POTS_4){
      min = 96;
      max = 128;
    }

    // pot pins
    buff.appendToSysEx8Bits(BMC_MAX_POTS);
    uint8_t numOfPinsInMessage = 0;
    for(uint8_t i=min;i<max;i++){
      if(i<BMC_MAX_POTS){
        numOfPinsInMessage++;
        continue;
      }
      break;
    }
    buff.appendToSysEx7Bits(numOfPinsInMessage);
    #if BMC_MAX_POTS > 0
      for(uint8_t i=min;i<max;i++){
        if(i<BMC_MAX_POTS){
          BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_POT, i);
          buff.appendToSysEx8Bits(ui.pins[0]);
        } else {
          break;
        }
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_2 ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_3 ||
            itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_4
  ){
    uint8_t min = 0;
    uint8_t max = 32;
    if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_2){
      min = 32;
      max = 64;
    } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_3){
      min = 64;
      max = 96;
    } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_POTS_4){
      min = 96;
      max = 128;
    }
    // pot pins
    buff.appendToSysEx8Bits(BMC_MAX_GLOBAL_POTS);
    uint8_t numOfPinsInMessage = 0;
    for(uint8_t i=min;i<max;i++){
      if(i<BMC_MAX_GLOBAL_POTS){
        numOfPinsInMessage++;
        continue;
      }
      break;
    }
    buff.appendToSysEx7Bits(numOfPinsInMessage);
    #if BMC_MAX_GLOBAL_POTS > 0
      for(uint8_t i=min;i<max;i++){
        if(i<BMC_MAX_GLOBAL_POTS){
          BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_POT, i);
          buff.appendToSysEx8Bits(ui.pins[0]);
        } else {
          break;
        }
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_LEDS){
    // led pins
    buff.appendToSysEx8Bits(BMC_MAX_LEDS);
    #if BMC_MAX_LEDS > 0
      for(uint8_t i=0;i<BMC_MAX_LEDS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_LED, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_PWM_LEDS){
    // pwm led pins
    buff.appendToSysEx8Bits(BMC_MAX_PWM_LEDS);
    #if BMC_MAX_PWM_LEDS > 0
      for(uint8_t i=0;i<BMC_MAX_PWM_LEDS;i++){
        buff.appendToSysEx7Bits(BMCBuildData::getPwmLedPin(i));
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_ENCODERS){
    // encoder pins
    buff.appendToSysEx8Bits(BMC_MAX_ENCODERS);
    #if BMC_MAX_ENCODERS > 0
      for(uint8_t i=0;i<BMC_MAX_ENCODERS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ENCODER, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
        buff.appendToSysEx7Bits(ui.pins[1]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_GLOBAL_LEDS){
    // global led pins
    buff.appendToSysEx8Bits(BMC_MAX_GLOBAL_LEDS);
    #if BMC_MAX_GLOBAL_LEDS > 0
      for(uint8_t i=0;i<BMC_MAX_GLOBAL_LEDS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_LED, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_NL_RELAYS){
    // Relay NL pins
    buff.appendToSysEx8Bits(BMC_MAX_NL_RELAYS);
    #if BMC_MAX_NL_RELAYS > 0
      for(uint8_t i=0;i<BMC_MAX_NL_RELAYS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_NL_RELAY, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_L_RELAYS){
    // Relay L pins
    buff.appendToSysEx8Bits(BMC_MAX_L_RELAYS);
    #if BMC_MAX_L_RELAYS > 0
      for(uint8_t i=0;i<BMC_MAX_L_RELAYS;i++){
        BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_L_RELAY, i);
        buff.appendToSysEx7Bits(ui.pins[0]);
        buff.appendToSysEx7Bits(ui.pins[1]);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_PIXELS){
    // pixel pins
    buff.appendToSysEx8Bits(BMC_MAX_PIXELS);
    #if BMC_MAX_L_RELAYS > 0
      for(uint8_t i=0;i<BMC_MAX_PIXELS;i++){
        buff.appendToSysEx7Bits(254);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_PINS_RGB_PIXELS){
    // pixel pins
    buff.appendToSysEx8Bits(BMC_MAX_RGB_PIXELS);
    #if BMC_MAX_L_RELAYS > 0
      for(uint8_t i=0;i<BMC_MAX_RGB_PIXELS;i++){
        buff.appendToSysEx7Bits(254);
      }
    #endif
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_DEVICE_NAME){
    String name = BMC_DEVICE_NAME;
    buff.appendToSysEx7Bits(name.length()+1);
    buff.appendCharArrayToSysEx(name);

  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BUTTON_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_BUTTON_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_BUTTON_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getButtonLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getButtonLedMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BUTTON_PIXELS){
   buff.appendToSysEx7Bits(BMC_MAX_BUTTON_PIXEL_MERGE);
   for(uint8_t i=0;i<BMC_MAX_BUTTON_PIXEL_MERGE;i++){
     //buff.appendToSysEx7Bits(BMCBuildData::getButtonPixelMergeItem(i, 0));
     //buff.appendToSysEx7Bits(BMCBuildData::getButtonPixelMergeItem(i, 1));
   }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BUTTON_RGB_PIXELS){
   buff.appendToSysEx7Bits(BMC_MAX_BUTTON_RGB_PIXEL_MERGE);
   for(uint8_t i=0;i<BMC_MAX_BUTTON_RGB_PIXEL_MERGE;i++){
     //buff.appendToSysEx7Bits(BMCBuildData::getButtonRgbPixelMergeItem(i, 0));
     //buff.appendToSysEx7Bits(BMCBuildData::getButtonRgbPixelMergeItem(i, 1));
   }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_ENCODERS){
    buff.appendToSysEx7Bits(BMC_MAX_ENCODER_MERGE);
    for(uint8_t i=0;i<BMC_MAX_ENCODER_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getEncoderMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getEncoderMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_POTS){
    buff.appendToSysEx7Bits(BMC_MAX_AUX_JACKS);
    for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getPotMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getPotMergeItem(i, 1));
      //buff.appendToSysEx7Bits(BMCBuildData::getPotMergeItem(i, 2));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BI_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_BI_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_BI_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getBiLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getBiLedMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_RGB_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_RGB_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_BI_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbLedMergeItem(i, 1));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbLedMergeItem(i, 2));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BI_GLOBAL_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_BI_GLOBAL_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_BI_GLOBAL_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getBiGlobalLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getBiGlobalLedMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_RGB_GLOBAL_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_RGB_GLOBAL_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_RGB_GLOBAL_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbGlobalLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbGlobalLedMergeItem(i, 1));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbGlobalLedMergeItem(i, 2));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_BI_PWM_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_BI_PWM_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_BI_PWM_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getBiPwmLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getBiPwmLedMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_RGB_PWM_LEDS){
    buff.appendToSysEx7Bits(BMC_MAX_RGB_PWM_LED_MERGE);
    for(uint8_t i=0;i<BMC_MAX_RGB_PWM_LED_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbPwmLedMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbPwmLedMergeItem(i, 1));
      //buff.appendToSysEx7Bits(BMCBuildData::getRgbPwmLedMergeItem(i, 2));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_RELAYS_L){
    buff.appendToSysEx7Bits(BMC_MAX_RELAY_L_MERGE);
    for(uint8_t i=0;i<BMC_MAX_RELAY_L_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getRelayLMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getRelayLMergeItem(i, 1));
    }
  } else if(itemId==BMC_GLOBALF_BUILD_INFO_MERGE_RELAYS_NL){
    buff.appendToSysEx7Bits(BMC_MAX_RELAY_NL_MERGE);
    for(uint8_t i=0;i<BMC_MAX_RELAY_NL_MERGE;i++){
      //buff.appendToSysEx7Bits(BMCBuildData::getRelayNLMergeItem(i, 0));
      //buff.appendToSysEx7Bits(BMCBuildData::getRelayNLMergeItem(i, 1));
    }
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
  // check and/or change the status of the backup
  if(newStatus == 1){
    backupStart();
  } else if(newStatus == 2){
    backupComplete();
  } else if(newStatus == 3){
    backupCancel();
  }
  globalSendBackupStatus();
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
  BMC_PRINTLN("Settings Length",incoming.size(),"required",sysExLength);
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
    page
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

void BMCEditor::globalStringLibrary(bool write){ //BMC_GLOBALF_STRING_STRING_LIBRARY
  if(!isValidGlobalMessage()){
    return;
  }

  uint8_t sysExLength = 11;
  // handle backup
  if(write && backupActive()){
    backupGlobalStringLibrary(sysExLength);
    return;
  }

  uint16_t index = getMessagePageNumber();

  if(index>0 && index>=BMC_MAX_STRING_LIBRARY){
    sendNotification(BMC_NOTIFY_INVALID_STRING_LIBRARY, index, true);
    return;
  }

  sysExLength += BMC_NAME_LEN_STRING_LIBRARY;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_STRING_LIBRARY > 0
  if(write){
    // write new data and save, starts at byte 9
    // index of the stringLibrary message we are writting to
    bmcStoreGlobalStringLibrary& item = store.global.stringLibrary[index];
    incoming.getStringFromSysEx(9, item.name, BMC_NAME_LEN_STRING_LIBRARY);
    saveStringLibrary(index);
    reloadData();
  }
#endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_STRING_LIBRARY, 0,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_STRING_LIBRARY);
#if BMC_MAX_STRING_LIBRARY > 0
  bmcStoreGlobalStringLibrary& item = store.global.stringLibrary[index];
  buff.appendCharArrayToSysEx(item.name, BMC_NAME_LEN_STRING_LIBRARY);
#endif
  sendToEditor(buff);
}

void BMCEditor::globalLibrary(bool write){
  //BMC_GLOBALF_LIBRARY
}

void BMCEditor::globalPreset(bool write){

}
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


void BMCEditor::globalSetList(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 12;
  // handle backup
  if(write && backupActive()){
    backupGlobalSetList(sysExLength);
    return;
  }
  uint8_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_SETLISTS){
    sendNotification(BMC_NOTIFY_INVALID_SETLIST, index, true);
    return;
  }
  sysExLength += (BMC_MAX_SETLISTS_SONGS*2)+BMC_NAME_LEN_SETLISTS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_SETLISTS > 0
  if(write){
    // write new data and save, starts at byte 9
    // index of the library message we are writting to
    bmcStoreGlobalSetList& item = store.global.setLists[index];
    item.length = incoming.get7Bits(9);
    if(item.length > BMC_MAX_SETLISTS_SONGS){
      item.length = BMC_MAX_SETLISTS_SONGS;
    }
    uint8_t e = 10;
    memset(item.songs, 0, BMC_MAX_SETLISTS_SONGS);
    for(uint8_t i = 0 ; i < BMC_MAX_SETLISTS_SONGS ; i++){
      item.songs[i] = (uint16_t) incoming.get14Bits(e);
      if(item.songs[i] >= BMC_MAX_PRESETS){
        item.songs[i] = 0;
      }
      e += 2;
    }
    #if BMC_NAME_LEN_SETLISTS > 1
      incoming.getStringFromSysEx(e, item.name, BMC_NAME_LEN_SETLISTS);
    #endif
    if(!backupActive()){
      saveSetList(index);
      reloadData();
    }
  }
#endif
  BMCEditorMidiFlags flag;
  flag.reset();
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_SETLISTS, flag,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_SETLISTS);
  buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONGS);
  #if BMC_MAX_SETLISTS > 0
    bmcStoreGlobalSetList& item = store.global.setLists[index];
    buff.appendToSysEx7Bits(item.length);
    // how many of the items of the preset are active
    for(uint8_t i = 0 ; i < BMC_MAX_SETLISTS_SONGS ; i++){
      buff.appendToSysEx14Bits(item.songs[i]);
    }
    #if BMC_NAME_LEN_SETLISTS > 1
      buff.appendCharArrayToSysEx(item.name, BMC_NAME_LEN_SETLISTS);
    #endif
  #endif
  sendToEditor(buff);
  */
}










void BMCEditor::globalSetListSong(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 22;
  // handle backup
  if(write && backupActive()){
    backupGlobalSetListSong(sysExLength);
    return;
  }
  uint16_t songIndex = (uint16_t) incoming.get14Bits(9);
  uint8_t partIndex = incoming.sysex[11];
  if(songIndex>0 && songIndex>=BMC_MAX_SETLISTS_SONGS_LIBRARY){
    sendNotification(BMC_NOTIFY_INVALID_SETLIST_SONG_LIBRARY, songIndex, true);
    BMC_PRINTLN("BMC_NOTIFY_INVALID_SETLIST_SONG_LIBRARY");
    return;
  } else if(partIndex>0 && partIndex>=BMC_MAX_SETLISTS_SONG_PARTS){
    sendNotification(BMC_NOTIFY_INVALID_SETLIST_SONG_PART, partIndex, true);
    BMC_PRINTLN("BMC_NOTIFY_INVALID_SETLIST_SONG_PART");
    return;
  }
  sysExLength += BMC_NAME_LEN_SETLIST_SONG + BMC_NAME_LEN_SETLIST_SONG_PART;

  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    BMC_PRINTLN("BMC_NOTIFY_INVALID_SIZE",incoming.size(),"expected:", sysExLength);
    return;
  }
#if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0 && BMC_MAX_SETLISTS_SONG_PARTS > 0
  if(write){
    // write new data and save, starts at byte 11

    bmcStoreGlobalSetListSong& song = store.global.songLibrary[songIndex];
    bmcStoreGlobalSetListSongPart& part = song.parts[partIndex];

    song.settings  = incoming.get8Bits(12);//+2
    song.length = incoming.get8Bits(14);//+2

    part.length = incoming.get8Bits(16);//+2
    part.preset = (uint16_t) incoming.get14Bits(18);

    #if BMC_NAME_LEN_SETLIST_SONG > 1
      incoming.getStringFromSysEx(20, song.name, BMC_NAME_LEN_SETLIST_SONG);
    #endif

    #if BMC_NAME_LEN_SETLIST_SONG_PART > 1
      if(part.length>0){
        strcpy(part.name, "");
        incoming.getStringFromSysEx(20+BMC_NAME_LEN_SETLIST_SONG, part.name, BMC_NAME_LEN_SETLIST_SONG_PART);
      } else {
        strcpy(part.name, "");
      }
    #endif

    if(!backupActive()){
      saveSetListSong(songIndex);
      if(partIndex >= (BMC_MAX_SETLISTS_SONG_PARTS-1)){
        reloadData();
      }
    }
  }
#endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_SETLISTS_SONG, 0, songIndex);
  buff.appendToSysEx14Bits(BMC_MAX_SETLISTS_SONGS_LIBRARY);
  buff.appendToSysEx7Bits(BMC_MAX_SETLISTS_SONG_PARTS);
#if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0 && BMC_MAX_SETLISTS_SONG_PARTS > 0
  bmcStoreGlobalSetListSong& song = store.global.songLibrary[songIndex];
  buff.appendToSysEx14Bits(songIndex);
  buff.appendToSysEx7Bits(partIndex);
  buff.appendToSysEx8Bits(song.settings);
  buff.appendToSysEx8Bits(song.length);
  buff.appendToSysEx8Bits(song.parts[partIndex].length);
  buff.appendToSysEx14Bits(song.parts[partIndex].preset);
  #if BMC_NAME_LEN_SETLIST_SONG > 1
    buff.appendCharArrayToSysEx(song.name, BMC_NAME_LEN_SETLIST_SONG);
  #endif
  #if BMC_NAME_LEN_SETLIST_SONG_PART > 1
    buff.appendCharArrayToSysEx(song.parts[partIndex].name, BMC_NAME_LEN_SETLIST_SONG_PART);
  #endif
#endif
  sendToEditor(buff);
  */
}

void BMCEditor::globalSetListSongPartShiftPosition(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  // 11 minimumlength + 3 bytes
  uint8_t sysExLength = 15;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  uint8_t resp = 0;
#if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0 && BMC_MAX_SETLISTS_SONG_PARTS > 1
  if(write){
    uint16_t songIndex = (uint16_t) incoming.get14Bits(9);
    uint8_t partSource = incoming.sysex[11];
    uint8_t partTarget = incoming.sysex[12];
    if(songIndex < BMC_MAX_SETLISTS_SONGS_LIBRARY && partSource < BMC_MAX_SETLISTS_SONG_PARTS && partTarget < BMC_MAX_SETLISTS_SONG_PARTS){
      if(partSource != partTarget){
        bmcStoreGlobalSetListSongPart source = store.global.songLibrary[songIndex].parts[partSource];
        if(partSource>partTarget){
          // moved up
          for(int i=(partSource-1);i>=partTarget;i--){
            if(i>=0 && (i+1) < BMC_MAX_SETLISTS_SONG_PARTS){
              bmcStoreGlobalSetListSongPart tmp = store.global.songLibrary[songIndex].parts[i];
              store.global.songLibrary[songIndex].parts[i+1] = tmp;
            }
          }
        } else if(partSource<partTarget){
          // moved down
          for(uint8_t i=partSource;i<partTarget;i++){
            if((i+1)<BMC_MAX_SETLISTS_SONG_PARTS){
              bmcStoreGlobalSetListSongPart tmp = store.global.songLibrary[songIndex].parts[i+1];
              store.global.songLibrary[songIndex].parts[i] = tmp;
            }

          }
        }
        store.global.songLibrary[songIndex].parts[partTarget] = source;
        resp = 1;
      }
      saveSetListSong(songIndex);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_SETLISTS_SONG_SHIFT_POSITION, 0, 0);
  buff.appendToSysEx7Bits(resp);
  sendToEditor(buff);
  */
}























void BMCEditor::globalLeds(bool write){//BMC_GLOBALF_LEDS
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 16;
  // handle backup
  if(write && backupActive()){
    backupGlobalLed(sysExLength);
    return;
  }
  uint8_t index = getMessagePageNumber();
  if(index > 0 && index >= BMC_MAX_GLOBAL_LEDS){
    sendNotification(BMC_NOTIFY_INVALID_GLOBAL_LED, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_GLOBAL_LEDS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreLed& item = store.global.leds[index];
    //item.event = BMC_MIDI_ARRAY_TO_32BITS(9,incoming.sysex);
    item.event = incoming.get32Bits(9);
    #if BMC_NAME_LEN_LEDS > 1
      incoming.getStringFromSysEx(14, item.name, BMC_NAME_LEN_LEDS);
    #endif
    if(!backupActive()){
      saveGlobalLed(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_LEDS, 0, index);
  buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_LEDS);//9
#if BMC_MAX_GLOBAL_LEDS > 0
  bmcStoreLed& item = store.global.leds[index];
  buff.appendToSysEx7Bits(BMCBuildData::getGlobalLedColor(index));
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalLedPosition(index, true));
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalLedPosition(index, false));
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_LEDS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_LEDS);
  #endif
#endif
  sendToEditor(buff);
  */
}
void BMCEditor::globalPixelProgram(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 28;
  // handle backup
  if(write && backupActive()){
    backupPixelProgram(sysExLength);
    return;
  }
  uint8_t index = getMessagePageNumber();
  if(index > 0 && index >= BMC_MAX_PIXEL_PROGRAMS){
    sendNotification(BMC_NOTIFY_INVALID_PIXEL_PROGRAM, index, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_PIXEL_PROGRAMS > 0
  if(write){
    // write new data and save, starts at byte 9
    // index of the library message we are writting to
    bmcStorePixelPrograms& item = store.global.pixelPrograms[index];
    item.length = incoming.get7Bits(9);
    if(item.length > 8){
      item.length = 8;
    }
    memset(item.events, 0, 8);
    for(uint8_t i = 0, e = 10 ; i < 8 ; i++, e += 2){
      item.events[i] = incoming.get8Bits(e);
    }
    if(!backupActive()){
      savePixelProgram(index);
      reloadData();
    }
  }
#endif
  BMCEditorMidiFlags flag;
  flag.reset();
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_PIXEL_PROGRAM, flag,
    index
  );
  buff.appendToSysEx7Bits(BMC_MAX_PIXEL_PROGRAMS);
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    bmcStorePixelPrograms& item = store.global.pixelPrograms[index];
    buff.appendToSysEx7Bits(item.length);
    // how many of the items of the preset are active
    for(uint8_t i = 0 ; i < 8 ; i++){
      buff.appendToSysEx8Bits(item.events[i]);
    }
  #endif
  sendToEditor(buff);
}
void BMCEditor::globalButton(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 22;
  // handle backup
  if(write && backupActive()){
    backupGlobalButton(sysExLength);
    return;
  }
  uint8_t buttonIndex = incoming.sysex[9];
  uint8_t eventIndex = incoming.sysex[10];
  if(buttonIndex>0 && buttonIndex>=BMC_MAX_GLOBAL_BUTTONS){
    sendNotification(BMC_NOTIFY_INVALID_GLOBAL_BUTTON, buttonIndex, true);
    return;
  } else if(eventIndex>0 && eventIndex>=BMC_MAX_BUTTON_EVENTS){
    sendNotification(BMC_NOTIFY_INVALID_BUTTON_EVENT, eventIndex, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_BUTTONS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_GLOBAL_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  if(write){
    // write new data and save, starts at byte 9
    // we only want to store the mode on the current button event
    // the flags are always stored on the first event of the page button
    bmcStoreButton& button = store.global.buttons[buttonIndex];
    bmcStoreButtonEvent& event = button.events[eventIndex];
    event.mode  = incoming.get8Bits(11) & 0x0F;//+2
    event.ports = incoming.get8Bits(13);//+2
    event.event = incoming.get32Bits(15);

    // add the button flags to the first button
    uint8_t m = button.events[0].mode & 0x0F;
    m |= (incoming.get8Bits(11) & 0xF0);//+2
    button.events[0].mode = m;

    #if BMC_NAME_LEN_BUTTONS > 1
      incoming.getStringFromSysEx(20, button.name, BMC_NAME_LEN_BUTTONS);
    #endif
    if(!backupActive()){
      saveGlobalButton(buttonIndex);
      reloadData();
    }
  }
#endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_BUTTON, 0, buttonIndex);
  buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_BUTTONS);
  buff.appendToSysEx7Bits(BMC_MAX_BUTTON_EVENTS);
#if BMC_MAX_GLOBAL_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  bmcStoreButton& button = store.global.buttons[buttonIndex];
  buff.appendToSysEx7Bits(buttonIndex);
  buff.appendToSysEx7Bits(eventIndex);
  BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_BUTTON, buttonIndex);
  buff.appendToSysEx16Bits(ui.x);
  buff.appendToSysEx16Bits(ui.y);
  buff.appendToSysEx7Bits(ui.style);

  uint8_t mode = button.events[eventIndex].mode & 0x0F;
  mode |= (button.events[0].mode & 0xF0);//+2
  buff.appendToSysEx8Bits(mode);
  buff.appendToSysEx8Bits(button.events[eventIndex].ports);
  buff.appendToSysEx32Bits(button.events[eventIndex].event);
  #if BMC_NAME_LEN_BUTTONS > 1
    buff.appendCharArrayToSysEx(button.name, BMC_NAME_LEN_BUTTONS);
  #endif
#endif
  sendToEditor(buff);
  */
}

void BMCEditor::globalButtonEventShiftPositionMessage(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  // 11 minimumlength + 3 bytes
  uint8_t sysExLength = 14;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  uint8_t resp = 0;
#if BMC_MAX_GLOBAL_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 1
  if(write){
    uint8_t buttonIndex = incoming.sysex[9];
    uint8_t eventSource = incoming.sysex[10];
    uint8_t eventTarget = incoming.sysex[11];
    if(buttonIndex<BMC_MAX_GLOBAL_BUTTONS && eventSource<BMC_MAX_BUTTON_EVENTS && eventTarget<BMC_MAX_BUTTON_EVENTS){
      if(eventSource!=eventTarget){
        bmcStoreButtonEvent source = store.global.buttons[buttonIndex].events[eventSource];
        if(eventSource>eventTarget){
          // moved up
          for(int i=(eventSource-1);i>=eventTarget;i--){
            if(i>=0 && (i+1) < BMC_MAX_BUTTON_EVENTS){
              bmcStoreButtonEvent tmp = store.global.buttons[buttonIndex].events[i];
              store.global.buttons[buttonIndex].events[i+1] = tmp;
            }
          }
        } else if(eventSource<eventTarget){
          // moved down
          for(uint8_t i=eventSource;i<eventTarget;i++){
            if((i+1)<BMC_MAX_BUTTON_EVENTS){
              bmcStoreButtonEvent tmp = store.global.buttons[buttonIndex].events[i+1];
              store.global.buttons[buttonIndex].events[i] = tmp;
            }

          }
        }
        BMC_PRINTLN("Moved Global button event from",eventSource,"to",eventTarget);
        store.global.buttons[buttonIndex].events[eventTarget] = source;
        resp = 1;
      }
      savePagesAndReloadData(page);
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_BUTTON_EVENT_SHIFT_POSITION, 0, 0);
  buff.appendToSysEx7Bits(resp);
  sendToEditor(buff);
  */
}

void BMCEditor::globalEncoder(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 21;
  // handle backup
  if(write && backupActive()){
    backupGlobalEncoder(sysExLength);
    return;
  }
  uint8_t index = incoming.sysex[9];
  if(index>0 && index>=BMC_MAX_GLOBAL_ENCODERS){
    sendNotification(BMC_NOTIFY_INVALID_GLOBAL_ENCODER, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_ENCODERS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_GLOBAL_ENCODERS > 0
  if(write){
    bmcStoreEncoder& item = store.global.encoders[index];
    item.mode = incoming.get8Bits(10);//2
    item.ports = incoming.get8Bits(12);//2
    item.event = incoming.get32Bits(14);
    #if BMC_NAME_LEN_ENCODERS > 1
      incoming.getStringFromSysEx(19, item.name, BMC_NAME_LEN_ENCODERS);
    #endif
    if(!backupActive()){
      saveGlobalEncoder(index);
      reloadData();
    }
  }
#endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_ENCODER, 0, index);
  buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_ENCODERS);//9
#if BMC_MAX_GLOBAL_ENCODERS > 0
  bmcStoreEncoder& item = store.global.encoders[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalEncoderPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalEncoderPosition(index,false));
  buff.appendToSysEx8Bits(item.mode);
  buff.appendToSysEx8Bits(item.ports);
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_ENCODERS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_ENCODERS);
  #endif
#endif
  sendToEditor(buff);
  */
}
void BMCEditor::globalPot(bool write){
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 19;
  // handle backup
  if(write && backupActive()){
    backupGlobalPot(sysExLength);
    return;
  }
  uint8_t index = incoming.sysex[9];

  if(index>0 && index>=BMC_MAX_GLOBAL_POTS){
    sendNotification(BMC_NOTIFY_INVALID_GLOBAL_POT, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_POTS;
  #if defined(BMC_USE_POT_TOE_SWITCH)
    sysExLength += 8;
  #endif
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_GLOBAL_POTS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStorePot& item = store.global.pots[index];
    item.ports = incoming.get8Bits(10);
    item.event = incoming.get32Bits(12);
    #if defined(BMC_USE_POT_TOE_SWITCH)
      item.toeSwitch = incoming.get32Bits(17);
      item.toeSwitchFlags = incoming.get16Bits(22);
      #if BMC_NAME_LEN_POTS > 1
        incoming.getStringFromSysEx(25, item.name, BMC_NAME_LEN_POTS);
      #endif
    #else
      #if BMC_NAME_LEN_POTS > 1
        incoming.getStringFromSysEx(17, item.name, BMC_NAME_LEN_POTS);
      #endif
    #endif

    if(!backupActive()){
      saveGlobalPot(index);
      reloadData();
    }
  }
#endif

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_GLOBALF_POT, 0, index);
  buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_POTS);//9
#if BMC_MAX_GLOBAL_POTS > 0
  bmcStorePot& item = store.global.pots[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalPotPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getGlobalPotPosition(index,false));
  buff.appendToSysEx7Bits(BMCBuildData::getGlobalPotStyle(index));
  buff.appendToSysEx8Bits(item.ports);
  buff.appendToSysEx32Bits(item.event);
  #if defined(BMC_USE_POT_TOE_SWITCH)
    buff.appendToSysEx32Bits(item.toeSwitch);
    buff.appendToSysEx16Bits(item.toeSwitchFlags);
  #endif
  #if BMC_NAME_LEN_POTS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_POTS);
  #endif
#endif
  sendToEditor(buff);
  */
}
void BMCEditor::globalGlobalPotCalibration(){//BMC_GLOBALF_GLOBAL_POT_CALIBRATION
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_GLOBAL_POTS){
    sendNotification(BMC_NOTIFY_INVALID_GLOBAL_POT, index, true);
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_GLOBAL_POT_CALIBRATION, 0,
    index
  );
  buff.appendToSysEx7Bits(BMC_MAX_GLOBAL_POTS); // 9
#if BMC_MAX_GLOBAL_POTS > 0
  buff.appendToSysEx16Bits(store.global.globalPotCalibration[index].min);
  buff.appendToSysEx16Bits(store.global.globalPotCalibration[index].max);
#endif
  sendToEditor(buff);
}
void BMCEditor::globalPotCalibration(){//BMC_GLOBALF_POT_CALIBRATION
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t index = getMessagePageNumber();
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
}

void BMCEditor::globalCustomSysEx(bool write){//BMC_GLOBALF_CUSTOM_SYSEX
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 28;
  // handle backup
  if(write && backupActive()){
    backupGlobalCustomSysEx(sysExLength);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_CUSTOM_SYSEX){
    sendNotification(BMC_NOTIFY_INVALID_CUSTOM_SYSEX, index, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_CUSTOM_SYSEX > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalCustomSysEx& item = store.global.customSysEx[index];
    item.length = incoming.get7Bits(9);
    //item.length = incoming.sysex[9] & 0x7F;
    for(uint8_t i=10,e=0,n=10+16;i<n;i++,e++){
      //item.event[e] = incoming.sysex[i] & 0x7F;
      item.event[e] = incoming.get7Bits(i);
    }
    if(!backupActive()){
      saveCustomSysEx(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_CUSTOM_SYSEX, 0,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_CUSTOM_SYSEX);
  #if BMC_MAX_CUSTOM_SYSEX > 0
  bmcStoreGlobalCustomSysEx& item = store.global.customSysEx[index];
    buff.appendToSysEx7Bits(item.length);
    for(uint8_t i=0;i<16;i++){
      buff.appendToSysEx7Bits(item.event[i]);
    }
  #endif
  sendToEditor(buff);
}
void BMCEditor::globalTriggers(bool write){//BMC_GLOBALF_TRIGGERS
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 21;
  // handle backup
  if(write && backupActive()){
    backupGlobalTriggers(sysExLength);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_TRIGGERS){
    sendNotification(BMC_NOTIFY_INVALID_TRIGGER, index, true);
    return;
  }
#if BMC_MAX_TRIGGERS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalTriggers& item = store.global.triggers[index];
    item.event = incoming.get32Bits(9);
    item.source = incoming.get32Bits(14);
    if(!backupActive()){
      // used by BMC to check if a trigger has been updated
      // if so BMC will go thru triggers and rebuild it's listener
      // this allows BMC to skip MIDI triggers if there are none
      // or only look at specific MIDI messages to speed things up
      flags.on(BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED);
      saveTrigger(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_TRIGGERS, 0,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_TRIGGERS);
  #if BMC_MAX_TRIGGERS > 0
    bmcStoreGlobalTriggers& item = store.global.triggers[index];
    buff.appendToSysEx32Bits(item.event);
    buff.appendToSysEx32Bits(item.source);
  #endif
  sendToEditor(buff);
  */
}

void BMCEditor::globalTimedEvents(bool write){//BMC_GLOBALF_TIMED_EVENTS
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 21;
  // handle backup
  if(write && backupActive()){
    backupGlobalTimedEvents(sysExLength);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_TIMED_EVENTS){
    sendNotification(BMC_NOTIFY_INVALID_TIMED_EVENT, index, true);
    return;
  }
#if BMC_MAX_TIMED_EVENTS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalTimedEvents& item = store.global.timedEvents[index];
    item.event = incoming.get32Bits(9);
    item.timeout = incoming.get32Bits(14);
    if(!backupActive()){
      // used by BMC to check if a timedEvent has been updated
      // if so BMC will go thru timedEvents and rebuild it's listener
      // this allows BMC to skip timedEvents if there are none
      // or only look at specific MIDI messages to speed things up
      flags.on(BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED);
      saveTimedEvent(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_TIMED_EVENTS, 0,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_TIMED_EVENTS);
  #if BMC_MAX_TIMED_EVENTS > 0
    bmcStoreGlobalTimedEvents& item = store.global.timedEvents[index];
    buff.appendToSysEx32Bits(item.event);
    buff.appendToSysEx32Bits(item.timeout);
  #endif
  sendToEditor(buff);
}



















void BMCEditor::globalTempoToTap(bool write){//BMC_GLOBALF_TEMPO_TO_TAP
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 16;
  // handle backup
  if(write && backupActive()){
    backupGlobalTempoToTap(sysExLength);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_TEMPO_TO_TAP){
    sendNotification(BMC_NOTIFY_INVALID_TEMPO_TO_TAP, index, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_TEMPO_TO_TAP > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalTempoToTap& item = store.global.tempoToTap[index];
    //item.event = BMC_MIDI_ARRAY_TO_32BITS(9,incoming.sysex);
    item.event = incoming.get32Bits(9);
    if(!backupActive()){
      saveTempoToTap(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_TEMPO_TO_TAP, 0,
    index
  );
  buff.appendToSysEx8Bits(BMC_MAX_TEMPO_TO_TAP);
  #if BMC_MAX_TEMPO_TO_TAP > 0
    bmcStoreGlobalTempoToTap& item = store.global.tempoToTap[index];
    buff.appendToSysEx32Bits(item.event);
  #endif
  sendToEditor(buff);
  */
}
void BMCEditor::globalSketchBytes(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = BMC_EDITOR_SYSEX_MIN_LENGTH;
  // handle backup
  if(write && backupActive()){
    backupGlobalSketchBytes(sysExLength);
    return;
  }
  sysExLength += (BMC_MAX_SKETCH_BYTES*2);
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_SKETCH_BYTES > 0
  if(write){
    // write new data and save, starts at byte 9
    //uint8_t e = 9;
    for(uint8_t i = 0, e = 9 ; i < BMC_MAX_SKETCH_BYTES ; i++, e += 2){
      BMCSketchByteData data = BMCBuildData::getSketchByteData(i);
      uint8_t sbv = incoming.get8Bits(e);
      store.global.sketchBytes[i] = constrain(sbv, data.min, data.max);
    }
    if(!backupActive()){
      saveSketchBytes();
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_SKETCH_BYTES, 0, 0
  );
  buff.appendToSysEx7Bits(BMC_MAX_SKETCH_BYTES);
  #if BMC_MAX_SKETCH_BYTES > 0
    for(uint8_t i = 0 ; i < BMC_MAX_SKETCH_BYTES ; i++){
      BMCSketchByteData data = BMCBuildData::getSketchByteData(i);
      uint8_t sbv = store.global.sketchBytes[i];
      sbv = constrain(sbv, data.min, data.max);
      buff.appendToSysEx8Bits(sbv);
    }
  #endif
  sendToEditor(buff);
}
void BMCEditor::globalSketchBytesData(){
  if(!isValidGlobalMessage()){
    return;
  }
  uint16_t index = getMessagePageNumber();
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

void BMCEditor::globalNLRelay(bool write){//BMC_GLOBALF_NL_RELAYS
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 16;
  // handle backup
  if(write && backupActive()){
    backupGlobalNLRelay(sysExLength);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_NL_RELAYS){
    sendNotification(BMC_NOTIFY_INVALID_NL_RELAY, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_NL_RELAYS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalRelay& item = store.global.relaysNL[index];
    item.event = incoming.get32Bits(9);
    #if BMC_NAME_LEN_RELAYS > 1
      incoming.getStringFromSysEx(14,item.name,BMC_NAME_LEN_RELAYS);
    #endif
    if(!backupActive()){
      saveNLRelay(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_NL_RELAYS, 0,
    index
  );
  buff.appendToSysEx7Bits(BMC_MAX_NL_RELAYS);
  #if BMC_MAX_NL_RELAYS > 0
    buff.appendToSysEx16Bits(BMCBuildData::getRelayNLPosition(index,true));
    buff.appendToSysEx16Bits(BMCBuildData::getRelayNLPosition(index,false));
    bmcStoreGlobalRelay& item = store.global.relaysNL[index];
    buff.appendToSysEx32Bits(item.event);
    #if BMC_NAME_LEN_RELAYS > 1
      buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_RELAYS);
    #endif
  #endif
  sendToEditor(buff);
  */
}
void BMCEditor::globalLRelay(bool write){//BMC_GLOBALF_L_RELAYS
  /*
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 16;
  // handle backup
  if(write && backupActive()){
    backupGlobalLRelay(sysExLength);
    return;
  }
  uint16_t index = getMessagePageNumber();
  if(index>0 && index>=BMC_MAX_L_RELAYS){
    sendNotification(BMC_NOTIFY_INVALID_L_RELAY, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_L_RELAYS > 0
  if(write){
    // write new data and save, starts at byte 9
    bmcStoreGlobalRelay& item = store.global.relaysL[index];
    item.event = incoming.get32Bits(9);
    #if BMC_NAME_LEN_RELAYS > 1
      incoming.getStringFromSysEx(14,item.name,BMC_NAME_LEN_RELAYS);
    #endif
    if(!backupActive()){
      saveLRelay(index);
      reloadData();
    }
  }
#endif
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_L_RELAYS, 0,
    index
  );
  buff.appendToSysEx7Bits(BMC_MAX_L_RELAYS);
  #if BMC_MAX_L_RELAYS > 0
    buff.appendToSysEx16Bits(BMCBuildData::getRelayLPosition(index,true));
    buff.appendToSysEx16Bits(BMCBuildData::getRelayLPosition(index,false));
    bmcStoreGlobalRelay& item = store.global.relaysL[index];
    buff.appendToSysEx32Bits(item.event);
    #if BMC_NAME_LEN_RELAYS > 1
      buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_RELAYS);
    #endif
  #endif
  sendToEditor(buff);
  */
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
void BMCEditor::globalPortPresets(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = 27;
  // handle backup
  if(write && backupActive()){
    backupGlobalPortPresets(sysExLength);
    return;
  }
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    // write new data and save, starts at byte 9
    //uint8_t e = 9;
    for(uint8_t i = 0, e = 9 ; i < 16 ; i++, e++){
      store.global.portPresets.preset[i] = incoming.get7Bits(e);
    }
    if(!backupActive()){
      saveDevicePorts();
      reloadData();
    }
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_PORTS_PRESETS, 0, 0
  );
  for(uint8_t i = 0 ; i < 16 ; i++){
    buff.appendToSysEx7Bits(store.global.portPresets.preset[i]);
  }
  sendToEditor(buff);
}
void BMCEditor::globalEditorFeedback(bool write){
  if(!isValidGlobalMessage()){
    return;
  }
  uint8_t sysExLength = BMC_EDITOR_SYSEX_MIN_LENGTH+1;
  if(write && incoming.size()>=sysExLength){
    uint8_t status = incoming.get7Bits(9);
    flags.write(BMC_EDITOR_FLAG_EDITOR_FEEDBACK,status>0);
    BMC_PRINTLN("BMC_EDITOR_FLAG_EDITOR_FEEDBACK", status);
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
