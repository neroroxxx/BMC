/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  This class handles all the communication to and from the Editor App.
  It also has acces to the Storage class which reads/writes EEPROM.

*/
#ifndef __BMC_EDITOR__
#define __BMC_EDITOR__

#include "utility/BMC-Def.h"
#include "editor/BMC-EditorMidiDef.h"
#include "storage/BMC-Storage.h"
#include "midi/BMC-Midi.h"

#if defined(BMC_USE_TIME)
#include <TimeLib.h>
#endif

// keep the connection between bmc and the editor alive for this time (ms),
// remove definition to disable it
#define BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT 5000

#define BMC_EDITOR_FLAG_CONNECTED                      0
#define BMC_EDITOR_FLAG_CONNECTION_HAS_CHANGED      	 1
#define BMC_EDITOR_FLAG_READY_TO_RELOAD             	 2
#define BMC_EDITOR_FLAG_DATA_FOR_BMC_AVAILABLE      	 3
#define BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR        	 4
#define BMC_EDITOR_FLAG_EDITOR_FEEDBACK             	 5
#define BMC_EDITOR_FLAG_EDITOR_DISCONNECTED         	 6
#define BMC_EDITOR_FLAG_EDITOR_LFO_UPDATED          	 7
#define BMC_EDITOR_FLAG_EDITOR_TEMPO_TO_TAP_UPDATED 	 8
#define BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED     	 9
#define BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED 	 10
#define BMC_EDITOR_FLAG_EEPROM_ERASED       	         11
#define BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP        	 12
#define BMC_EDITOR_FLAG_BACKUP_ACTIVE               	 13
#define BMC_EDITOR_FLAG_BACKUP_STARTED              	 14
#define BMC_EDITOR_FLAG_BACKUP_COMPLETE             	 15
#define BMC_EDITOR_FLAG_BACKUP_CANCELED             	 16
#define BMC_EDITOR_FLAG_BACKUP_STATE_CHANGE            17
#define BMC_EDITOR_FLAG_SEND_STATES                 	 18


class BMCEditor {
public:
  /*
    BMC-Editor.cpp
  */
  BMCEditor(bmcStore& t_store, BMCMidi& t_midi, BMCSettings& t_settings, BMCMessenger& t_messenger);

  void begin();
  void update();
  bool readyToReload();
  bool dataForBMCAvailable();
  void saveEEPROM(){
    saveStore();
  }
  void reloadPreviouslySavedStore(){
    getStore();
  }
  void triggerStates(){
    flags.on(BMC_EDITOR_FLAG_SEND_STATES);
  }
  bool isTriggerStates(){
    return flags.read(BMC_EDITOR_FLAG_SEND_STATES);
  }
  void messengerSend(uint16_t status, signed long value, char* str, uint8_t len){
    if(!midi.globals.editorConnected() || connectionOngoing()){
      return;
    }
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_EDITOR_MESSENGER, 0, 0
    );
    // send a 1 as the first data byte to notify the app that this a
    // a new message for the app
    buff.appendToSysEx7Bits(1);
    buff.appendToSysEx16Bits(status);
    buff.appendToSysEx32Bits(value);
    buff.appendToSysEx7Bits(len);
    buff.appendCharArrayToSysEx(str, len);
    sendToEditor(buff);
  }
  void messengerSend(uint16_t status, signed long value, const char* str){
    if(!midi.globals.editorConnected() || connectionOngoing()){
      return;
    }
    String str2 = str;
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_EDITOR_MESSENGER, 0, 0
    );
    // send a 1 as the first data byte to notify the app that this a
    // a new message for the app
    buff.appendToSysEx7Bits(1);
    buff.appendToSysEx16Bits(status);
    buff.appendToSysEx32Bits(value);
    buff.appendToSysEx7Bits(str2.length()>32 ? 32 : str2.length());
    buff.appendCharArrayToSysEx(str2);
    sendToEditor(buff);
  }
  // USB can not be used as a Chaining Port
  void setChainingPort(uint8_t value){
    value &= 0x07;
    chaingingPort = 0;
    if(value==0){
      return;
    }
    bitWrite(chaingingPort, value, 1);
  }
  BMCMidiControl getDataForBMC(){
    return dataForBMC;
  }
  bool readingBackup(){
    return midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
  }
  uint8_t getCtrlWrite(){
    return dataForBMC.isWrite();
  }
  uint8_t getCtrlGroup(){
    return dataForBMC.getGroup();
  }
  uint8_t getCtrlParameter(){
    return dataForBMC.getParameter();
  }
  uint32_t getCtrlValue(){
    return dataForBMC.getValue();
  }

  #if defined(BMC_DEBUG)
    void printStorageInfo(){
      storage.printInfo();
    }
  #endif

  bool connected();
  bool connectionHasChanged();
  void connectEditor();
  void keepConnectionAlive();
  void disconnectEditor();
  void forceDisconnectEditor();
  void setPort(uint8_t port);
  void setLayer(uint8_t layer);
  uint8_t getLayer();
  uint16_t getEepromSize(){
    return storage.length();
  }

  void getGlobalData(bmcStoreGlobal& p){
    p = store.global;
  }
  void getLayerData(bmcStoreLayer& p){
    p = store.layers[layer];
  }
  void getLayerData(uint8_t index, bmcStoreLayer& p){
    p = store.layers[index];
  }
  void saveSketchBytesToEEPROM(){
    #if BMC_MAX_SKETCH_BYTES > 0
      saveSketchBytes();
    #endif
  }
  bool lfoUpdated(){
    #if BMC_MAX_LFO > 0
      return flags.toggleIfTrue(BMC_EDITOR_FLAG_EDITOR_LFO_UPDATED);
    #else
      return false;
    #endif
  }
  bool tempoToTapUpdated(){
    #if BMC_MAX_TEMPO_TO_TAP > 0
      return flags.toggleIfTrue(BMC_EDITOR_FLAG_EDITOR_TEMPO_TO_TAP_UPDATED);
    #else
      return false;
    #endif
  }
  bool triggersUpdated(){
    #if BMC_MAX_TRIGGERS > 0
      return flags.toggleIfTrue(BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED);
    #else
      return false;
    #endif
  }
  bool timedEventsUpdated(){
    #if BMC_MAX_TIMED_EVENTS > 0
      return flags.toggleIfTrue(BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED);
    #else
      return false;
    #endif
  }
  bool eepromErased(){
    return flags.toggleIfTrue(BMC_EDITOR_FLAG_EEPROM_ERASED);
  }
  bool wasStoreCleared(){
    return eepromErased();
  }
  #if defined(BMC_USE_TIME)
    static time_t getTeensy3Time(){
      return Teensy3Clock.get();
    }
    void setRTCTime(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t mo, uint16_t y){
      setTime(h,m,s,d,mo,y);
      Teensy3Clock.set(now());
    }
  #endif
  uint8_t getHour(){
    #if defined(BMC_USE_TIME)
      return hour();
    #endif
    return 0;
  }
  uint8_t getMinute(){
    #if defined(BMC_USE_TIME)
      return minute();
    #endif
    return 0;
  }
  uint8_t getSecond(){
    #if defined(BMC_USE_TIME)
      return second();
    #endif
    return 0;
  }
  uint8_t getDay(){
    #if defined(BMC_USE_TIME)
      return day();
    #endif
    return 0;
  }
  uint8_t getMonth(){
    #if defined(BMC_USE_TIME)
      return month();
    #endif
    return 0;
  }
  uint16_t getYear(){
    #if defined(BMC_USE_TIME)
      return year();
    #endif
    return 0;
  }

#if BMC_TOTAL_POTS_AUX_JACKS > 0
  void setPotCalibration(uint8_t deviceType, uint16_t index, uint16_t min, uint16_t max){
    if(deviceType == BMC_DEVICE_ID_GLOBAL_POT){
      index += BMC_MAX_POTS;
    } else if(deviceType == BMC_DEVICE_ID_AUX_JACK){
      index += (BMC_MAX_POTS + BMC_MAX_GLOBAL_POTS);
    }
    if(index < BMC_TOTAL_POTS_AUX_JACKS){
      store.global.potCalibration[index].events[0] = min;
      store.global.potCalibration[index].events[1] = max;
      saveGlobalAndReloadData();
    }
  }
#endif
  bool getImportStateChanged(){
    return flags.toggleIfTrue(BMC_EDITOR_FLAG_BACKUP_STATE_CHANGE);
  }
  bool importIsActive(){
    return midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
  }


private:
  // Reference to the store from BMC.h
  bmcStore& store;
  // reference to midi object from BMC.h
  BMCMidi& midi;
  // reference to store.global.settings in BMC.h
  BMCSettings& settings;
  // a class that gets pins for hardware, all precompiled based on the config
  //BMCBuildData pins;
  // reads/writes the store object to EEPROM/SD Card
  BMCStorage storage;
  // midi port we're listening to for editing.
  uint8_t port = 1;
  // id of this device, this can be changed via Settings
  uint8_t deviceId = 0;
  // the current layer we are working with
  uint8_t layer = 0;
  // the current store address
  uint8_t storeAddress = 0;
  // flags
  BMCFlags <uint32_t> flags;
  BMCMidiControl dataForBMC;
  // reference to the BMCMidiMessage in the BMCMidi class
  BMCMidiMessage &incoming;
  // reference to BMCMessenger in BMC class
  BMCMessenger& messenger;
  // the midi flags of the incoming editor message
  BMCEditorMidiFlags midiFlags;

  #if defined(BMC_EDITOR_ENABLE_CONNECTION_TIMEOUT)
    // handles keeping the connection alive after the editor has been connected.
    BMCTimer connectionAliveTimer;
    bool editorHasConnectionAliveOption = false;
  #endif

  // the port that other BMC device is connected to
  uint8_t chaingingPort = 0;
  // the port that sent the original message to be chained
  uint8_t chaingingEditorPort = 0;

  bool connectionOngoing(){
    return flags.read(BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR);
  }
  // backup
  bool backupActive(){
    return isBackupMessage() &&
          midi.globals.editorConnected() &&
          flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
  }
  void backupStart(){
    // if the backup is NOT already running then start it
    if(midi.globals.editorConnected() && !flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      BMC_INFO("Backup Started");
      flags.on(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
      flags.on(BMC_EDITOR_FLAG_BACKUP_STARTED);
      flags.on(BMC_EDITOR_FLAG_BACKUP_STATE_CHANGE);
      flags.off(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.off(BMC_EDITOR_FLAG_BACKUP_CANCELED);
    }
  }
  bool backupComplete(){
    // if the backup is running then stop it
    // and save the current store to EEPROM
    if(midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      BMC_INFO("Backup Complete");
      flags.off(BMC_EDITOR_FLAG_BACKUP_STARTED);
      flags.on(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.off(BMC_EDITOR_FLAG_BACKUP_CANCELED);
      flags.on(BMC_EDITOR_FLAG_BACKUP_STATE_CHANGE);
      #if BMC_MAX_LFO > 0
        flags.on(BMC_EDITOR_FLAG_EDITOR_LFO_UPDATED);
      #endif
      #if BMC_MAX_TEMPO_TO_TAP > 0
        flags.on(BMC_EDITOR_FLAG_EDITOR_TEMPO_TO_TAP_UPDATED);
      #endif
      #if BMC_MAX_TRIGGERS > 0
        flags.on(BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED);
      #endif
      #if BMC_MAX_TIMED_EVENTS > 0
        flags.on(BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED);
      #endif
      // saveStore();
      // reloadData();
      return true;
    }
    return false;
  }
  void backupCancel(){
    if(midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      BMC_WARNING("Backup Canceled");
      flags.off(BMC_EDITOR_FLAG_BACKUP_STARTED);
      flags.off(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.on(BMC_EDITOR_FLAG_BACKUP_CANCELED);
      flags.on(BMC_EDITOR_FLAG_BACKUP_STATE_CHANGE);
      getStore();
      reloadData();
    }
  }
  uint8_t getBackupStatus(){
    if(midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      if(flags.toggleIfTrue(BMC_EDITOR_FLAG_BACKUP_STARTED)){
        flags.on(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
        return 1;
      } else if(flags.toggleIfTrue(BMC_EDITOR_FLAG_BACKUP_COMPLETE)){
        flags.off(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
        return 2;
      } else if(flags.toggleIfTrue(BMC_EDITOR_FLAG_BACKUP_CANCELED)){
        flags.off(BMC_EDITOR_FLAG_BACKUP_ACTIVE);
        return 3;
      }
    }
    return 0;
  }
  

  uint16_t checkIfHardwareAvailable(uint8_t t_type){
    for(uint8_t i = 0 ; i < devicesDataLength ; i++){
      if(devicesData[i].id==t_type){
        return devicesData[i].length;
      }
    }
    return 0;
  }

  bmcStoreName getDeviceName(uint16_t n){
    bmcStoreName name;
    strcpy(name.name, "");
    if(n==0 || n > BMC_MAX_NAMES_LIBRARY){
      return name;
    }
    strcpy(name.name, store.global.names[n-1].name);
    return name;
  }

  void reloadData(){
    if(midi.globals.editorConnected()){
      flags.on(BMC_EDITOR_FLAG_READY_TO_RELOAD);
    }
  }

  // dealing with saving to EEPROM

  // EEPROM address offsets
  uint8_t getCrcAndVersionSize();
  uint32_t getStoreOffset();
  uint32_t getGlobalOffset();
  uint32_t getSettingsOffset();

  uint32_t getEventsOffset();
  uint32_t getEventsOffset(uint16_t index);
  uint32_t getNamesOffset();
  uint32_t getNamesOffset(uint16_t index);

  uint32_t getShortcutsOffset();
  uint32_t getShortcutsOffset(uint16_t index);

  uint32_t getLfoOffset();
  uint32_t getLfoOffset(uint16_t index);

  uint32_t getSketchBytesOffset();
  uint32_t getSketchBytesOffset(uint16_t index);

  uint32_t getPresetOffset();
  uint32_t getPresetOffset(uint16_t index);

  uint32_t getSetListOffset();
  uint32_t getSetListOffset(uint16_t index);
  uint32_t getSetListSongOffset();
  uint32_t getSetListSongOffset(uint16_t index);


  uint32_t getGlobalButtonOffset();
  uint32_t getGlobalButtonOffset(uint16_t index);

  uint32_t getGlobalLedOffset();
  uint32_t getGlobalLedOffset(uint16_t index);

  uint32_t getGlobalBiLedOffset();
  uint32_t getGlobalBiLedOffset(uint16_t index);

  uint32_t getGlobalTriLedOffset();
  uint32_t getGlobalTriLedOffset(uint16_t index);

  uint32_t getGlobalEncoderOffset();
  uint32_t getGlobalEncoderOffset(uint16_t index);

  uint32_t getGlobalPotOffset();
  uint32_t getGlobalPotOffset(uint16_t index);

  uint32_t getPotCalibrationOffset();
  uint32_t getPotCalibrationOffset(uint16_t index);

  uint32_t getGlobalPixelOffset();
  uint32_t getGlobalPixelOffset(uint16_t index);

  uint32_t getGlobalRgbPixelOffset();
  uint32_t getGlobalRgbPixelOffset(uint16_t index);

  uint32_t getGlobalMagicEncoderOffset();
  uint32_t getGlobalMagicEncoderOffset(uint16_t index);

  uint32_t getNLRelayOffset();
  uint32_t getNLRelayOffset(uint16_t index);

  uint32_t getLRelayOffset();
  uint32_t getLRelayOffset(uint16_t index);

  uint32_t getAuxJackOffset();
  uint32_t getAuxJackOffset(uint16_t index);


  uint32_t getCustomSysExOffset();
  uint32_t getCustomSysExOffset(uint16_t index);
  uint32_t getTriggerOffset();
  uint32_t getTriggerOffset(uint16_t index);
  uint32_t getTempoToTapOffset();
  uint32_t getTempoToTapOffset(uint16_t index);
  uint32_t getPortPresetsOffset();
  uint32_t getPortPresetsOffset(uint16_t index);
  uint32_t getPixelProgramsOffset();
  uint32_t getPixelProgramsOffset(uint16_t index);
  uint32_t getTimedEventOffset();
  uint32_t getTimedEventOffset(uint16_t n);

  // Clear the entire EEPROM
  void clearEEPROM(){
    storage.clear();
  }
  // save the entire "store" struct to EEPROM
  void saveStore(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getStoreOffset();
      storage.set(address, store);
    #endif
  }
  // save "store.global" only to EEPROM
  void saveGlobal(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      storage.set(address, store.global);
    #endif
  }
  // save "store.global" only to EEPROM
  // and notify BMC to reassign Hardware
  void saveGlobalAndReloadData(){
    saveGlobal();
    reloadData();
  }

public:

  void getDeviceNameFromIndex(uint16_t value, char* str){
    if(value < BMC_MAX_NAMES_LIBRARY){
      if(value > 0 && strlen(store.global.names[value-1].name) > 0){
        strcpy(str, store.global.names[value-1].name);
        return;
      }
    }
    // strcpy(str, "...");
  }
  void getDeviceNameText(uint8_t deviceType, uint16_t index, char* str){
    strcpy(str, "...");
    switch(deviceType){
      case BMC_DEVICE_ID_LAYER:
        if(index < BMC_MAX_LAYERS){
          // getDeviceNameFromIndex(store.layers[index].name, str);
          getDeviceNameFromIndex(store.layers[midi.globals.layer].events[0].name, str);
        }
        break;
      case BMC_DEVICE_ID_EVENT:
        if(index < BMC_MAX_EVENTS_LIBRARY){
          getDeviceNameFromIndex(store.global.events[index].name, str);
        }
        break;
      case BMC_DEVICE_ID_NAME:
        if(index < BMC_MAX_NAMES_LIBRARY){
          getDeviceNameFromIndex(index+1, str);
        }
        break;
      case BMC_DEVICE_ID_BUTTON:
        #if BMC_MAX_BUTTONS > 0
          if(index < BMC_MAX_BUTTONS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].buttons[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
        #if BMC_MAX_GLOBAL_BUTTONS > 0
          if(index < BMC_MAX_GLOBAL_BUTTONS){
            getDeviceNameFromIndex(store.global.buttons[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_LED:
        #if BMC_MAX_LEDS > 0
          if(index < BMC_MAX_LEDS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].leds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_LED:
        #if BMC_MAX_GLOBAL_LEDS > 0
          if(index < BMC_MAX_GLOBAL_LEDS){
            getDeviceNameFromIndex(store.global.leds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_BI_LED:
        #if BMC_MAX_BI_LEDS > 0
          if(index < BMC_MAX_BI_LEDS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].biLeds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          if(index < BMC_MAX_GLOBAL_BI_LEDS){
            getDeviceNameFromIndex(store.global.biLeds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_TRI_LED:
        #if BMC_MAX_TRI_LEDS > 0
          if(index < BMC_MAX_TRI_LEDS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].triLeds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          if(index < BMC_MAX_GLOBAL_TRI_LEDS){
            getDeviceNameFromIndex(store.global.triLeds[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_ENCODER:
        #if BMC_MAX_ENCODERS > 0
          if(index < BMC_MAX_ENCODERS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].encoders[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
        #if BMC_MAX_GLOBAL_ENCODERS > 0
          if(index < BMC_MAX_GLOBAL_ENCODERS){
            getDeviceNameFromIndex(store.global.encoders[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_POT:
        #if BMC_MAX_POTS > 0
          if(index < BMC_MAX_POTS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].pots[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_POT:
        #if BMC_MAX_GLOBAL_POTS > 0
          if(index < BMC_MAX_GLOBAL_POTS){
            getDeviceNameFromIndex(store.global.pots[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_MAGIC_ENCODER:
        #if BMC_MAX_MAGIC_ENCODERS > 0
          if(index < BMC_MAX_MAGIC_ENCODERS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].magicEncoders[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
        #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
          if(index < BMC_MAX_GLOBAL_MAGIC_ENCODERS){
            getDeviceNameFromIndex(store.global.magicEncoders[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL:
        #if BMC_MAX_PIXELS > 0
          if(index < BMC_MAX_PIXELS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].pixels[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
        #if BMC_MAX_GLOBAL_PIXELS > 0
          if(index < BMC_MAX_GLOBAL_PIXELS){
            getDeviceNameFromIndex(store.global.pixels[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_RGB_PIXEL:
        #if BMC_MAX_RGB_PIXELS > 0
          if(index < BMC_MAX_RGB_PIXELS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].rgbPixels[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
          if(index < BMC_MAX_GLOBAL_RGB_PIXELS){
            getDeviceNameFromIndex(store.global.rgbPixels[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL_STRIP:
        #if BMC_MAX_PIXEL_STRIP > 0
          if(index < BMC_MAX_PIXEL_STRIP){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].pixelStrip[0].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_NL_RELAY:
        #if BMC_MAX_NL_RELAYS > 0
          if(index < BMC_MAX_NL_RELAYS){
            getDeviceNameFromIndex(store.global.relaysNL[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_L_RELAY:
        #if BMC_MAX_L_RELAYS > 0
          if(index < BMC_MAX_L_RELAYS){
            getDeviceNameFromIndex(store.global.relaysL[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_AUX_JACK:
        #if BMC_MAX_AUX_JACKS > 0
          if(index < BMC_MAX_AUX_JACKS){
            getDeviceNameFromIndex(store.global.auxJacks[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_OLED:
        #if BMC_MAX_OLED > 0
          if(index < BMC_MAX_OLED){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].oled[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_ILI:
        #if BMC_MAX_ILI9341_BLOCKS > 0
          if(index < BMC_MAX_ILI9341_BLOCKS){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].ili[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_MINI_DISPLAY:
        #if BMC_MAX_MINI_DISPLAY > 0
          if(index < BMC_MAX_MINI_DISPLAY){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].miniDisplay[index].name, str);
          }
        #endif
        break;
      
      case BMC_DEVICE_ID_LCD:
        #if BMC_MAX_LCD > 0
          if(index < BMC_MAX_LCD){
            getDeviceNameFromIndex(store.layers[midi.globals.layer].lcd[index].name, str);
          }
        #endif
        break;

        
      case BMC_DEVICE_ID_LFO:
        #if BMC_MAX_LFO > 0
          if(index < BMC_MAX_LFO){
            getDeviceNameFromIndex(store.global.lfo[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_PRESET:
        #if BMC_MAX_PRESETS > 0
          if(index < BMC_MAX_PRESETS){
            getDeviceNameFromIndex(store.global.presets[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_CUSTOM_SYSEX:
        #if BMC_MAX_CUSTOM_SYSEX > 0
          if(index < BMC_MAX_CUSTOM_SYSEX){
            getDeviceNameFromIndex(store.global.customSysEx[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_TRIGGER:
        #if BMC_MAX_TRIGGERS > 0
          if(index < BMC_MAX_TRIGGERS){
            getDeviceNameFromIndex(store.global.triggers[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
        #if BMC_MAX_TEMPO_TO_TAP > 0
          if(index < BMC_MAX_TEMPO_TO_TAP){
            getDeviceNameFromIndex(store.global.tempoToTap[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_PORT_PRESET:
        if(index < 16){
          getDeviceNameFromIndex(store.global.portPresets[index].name, str);
        }
        break;
      case BMC_DEVICE_ID_SHORTCUTS:
        if(index < 6){
          getDeviceNameFromIndex(store.global.shortcuts[index].name, str);
        }
        break;
      case BMC_DEVICE_ID_PIXEL_PROGRAM:
        #if BMC_MAX_PIXEL_PROGRAMS > 0
          if(index < BMC_MAX_PIXEL_PROGRAMS){
            getDeviceNameFromIndex(store.global.pixelPrograms[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_SKETCH_BYTE:
        #if BMC_MAX_SKETCH_BYTES > 0
          // getDeviceNameFromIndex(store.global.sketchBytes[0], buff, 0, deviceType);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST:
        #if BMC_MAX_SETLISTS > 0
          if(index < BMC_MAX_SETLISTS){
            getDeviceNameFromIndex(store.global.setLists[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST_SONG:
        #if BMC_MAX_SETLISTS > 0
          // getDeviceNameFromIndex(store.global.setLists[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:
        #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
          if(index < BMC_MAX_SETLISTS_SONGS_LIBRARY){
            getDeviceNameFromIndex(store.global.songLibrary[index].name, str);
          }
        #endif
        break;
      case BMC_DEVICE_ID_TIMED_EVENT:
        #if BMC_MAX_TIMED_EVENTS > 0
          if(index < BMC_MAX_TIMED_EVENTS){
            getDeviceNameFromIndex(store.global.timedEvents[index].name, str);
          }
        #endif
        break;
    }
  }
#if defined(BMC_DEBUG)
  void printDevicesInfo(){
    Serial.println("");
    Serial.println("----------------------------");
    Serial.println("        DEVICES DATA        ");
    Serial.println("----------------------------");
    for(uint8_t i = 0 ; i < totalDevices ; i++){
      if(devicesData[i].id == 0){
        break;
      }
      Serial.print(devicesData[i].length);
      Serial.print(" ");
      if(devicesData[i].hardware){
        Serial.print("*");
      }
      if(devicesData[i].global && devicesData[i].hardware){
        Serial.print("Global ");
      }
      if(devicesData[i].length > 1){
        char buff[20] = "";
        strcpy(buff, devicesData[i].label);
        BMCTools::makePlural(buff);
        Serial.print(buff);
      } else {
        Serial.print(devicesData[i].label);
      }
      Serial.println("");
    }
    Serial.println("----------------------------");
    Serial.println("* is hardware");
    Serial.println("----------------------------");
  }
  #endif
  const uint8_t totalDevices = 42;
  const BMCDeviceData devicesData[42] = {
    {BMC_DEVICE_ID_LAYER, "Layer", -1, BMC_MAX_LAYERS, false, false, 0, BMC_MAX_LAYER_EVENTS},
    {BMC_DEVICE_ID_EVENT, "Event", -1, BMC_MAX_EVENTS_LIBRARY, true, false, 0, 0},
    {BMC_DEVICE_ID_NAME, "Name", -1, BMC_MAX_NAMES_LIBRARY, true, false, 0, 0},
    #if BMC_MAX_BUTTONS > 0
    {BMC_DEVICE_ID_BUTTON, "Button", 1, BMC_MAX_BUTTONS, false, true, BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS},
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
    {BMC_DEVICE_ID_GLOBAL_BUTTON, "Button", 1, BMC_MAX_GLOBAL_BUTTONS, true, true, BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS},
    #endif

    #if BMC_MAX_LEDS > 0
    {BMC_DEVICE_ID_LED, "Led", 2, BMC_MAX_LEDS, false, true, 1, 1},
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_LED, "Led", 2, BMC_MAX_GLOBAL_LEDS, true, true, 1, 1},
    #endif

    #if BMC_MAX_BI_LEDS > 0
    {BMC_DEVICE_ID_BI_LED, "Bi-Color Led", 2, BMC_MAX_BI_LEDS, false, true, 2, 2},
    #endif

    #if BMC_MAX_GLOBAL_BI_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_BI_LED, "Bi Led", 2, BMC_MAX_GLOBAL_BI_LEDS, true, true, 2, 2},
    #endif

    #if BMC_MAX_TRI_LEDS > 0
    {BMC_DEVICE_ID_TRI_LED, "Tri-Color Led", 2, BMC_MAX_TRI_LEDS, false, true, 3, 3},
    #endif

    #if BMC_MAX_GLOBAL_TRI_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_TRI_LED, "Tri Led", 2, BMC_MAX_GLOBAL_TRI_LEDS, true, true, 3, 3},
    #endif

    #if BMC_MAX_ENCODERS > 0
    {BMC_DEVICE_ID_ENCODER, "Encoder", 3, BMC_MAX_ENCODERS, false, true, 1, 1},
    #endif

    #if BMC_MAX_GLOBAL_ENCODERS > 0
    {BMC_DEVICE_ID_GLOBAL_ENCODER, "Encoder", 3, BMC_MAX_GLOBAL_ENCODERS, true, true, 1, 1},
    #endif

    #if BMC_MAX_POTS > 0
    {BMC_DEVICE_ID_POT, "Pot", 4, BMC_MAX_POTS, false, true, 1, 3},
    #endif

    #if BMC_MAX_GLOBAL_POTS > 0
    {BMC_DEVICE_ID_GLOBAL_POT, "Pot", 4, BMC_MAX_GLOBAL_POTS, true, true, 1, 3},
    #endif

    #if BMC_TOTAL_POTS_AUX_JACKS > 0
    {BMC_DEVICE_ID_POT_CALIBRATION, "Calibration", -1, BMC_TOTAL_POTS_AUX_JACKS, true, true, 0, 2},
    #endif

    #if BMC_MAX_PIXELS > 0
    {BMC_DEVICE_ID_PIXEL, "Pixel", 2, BMC_MAX_PIXELS, false, true, 1, 1},
    #endif

    #if BMC_MAX_GLOBAL_PIXELS > 0
    {BMC_DEVICE_ID_GLOBAL_PIXEL, "Pixel", 2, BMC_MAX_GLOBAL_PIXELS, true, true, 1, 1},
    #endif

    #if BMC_MAX_RGB_PIXELS > 0
    {BMC_DEVICE_ID_RGB_PIXEL, "RGB Pixel", 2, BMC_MAX_RGB_PIXELS, false, true, 0, 3},
    #endif

    #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    {BMC_DEVICE_ID_GLOBAL_RGB_PIXEL, "RGB Pixel", 2, BMC_MAX_GLOBAL_RGB_PIXELS, true, true, 0, 3},
    #endif

    #if BMC_MAX_PIXEL_STRIP > 0
    {BMC_DEVICE_ID_PIXEL_STRIP, "Pixel Strip", 2, BMC_MAX_PIXEL_STRIP>0?1:0, false, true, 1, 1},
    #endif

    #if BMC_MAX_NL_RELAYS > 0
    {BMC_DEVICE_ID_NL_RELAY, "NoLatch Relay", 6, BMC_MAX_NL_RELAYS, true, true, 1, 1},
    #endif

    #if BMC_MAX_L_RELAYS > 0
    {BMC_DEVICE_ID_L_RELAY, "Latch Relay", 6, BMC_MAX_L_RELAYS, true, true, 1, 1},
    #endif

    #if BMC_MAX_AUX_JACKS > 0
    {BMC_DEVICE_ID_AUX_JACK, "Aux Jack", 7, BMC_MAX_AUX_JACKS, true, true, 2, 3},
    #endif

    #if BMC_MAX_LFO > 0
    {BMC_DEVICE_ID_LFO, "LFO", -1, BMC_MAX_LFO, true, false, 3, 5},
    #endif

    #if BMC_MAX_OLED > 0
    {BMC_DEVICE_ID_OLED, "OLED Display", 8, BMC_MAX_OLED, false, true, 0, 1},
    #endif

    #if BMC_MAX_ILI9341_BLOCKS > 0
    {BMC_DEVICE_ID_ILI, "ILI9341 Block", 8, BMC_MAX_ILI9341_BLOCKS, false, true, 0, 1},
    #endif

    #if BMC_MAX_MINI_DISPLAY > 0
    {BMC_DEVICE_ID_MINI_DISPLAY, "Mini Display", 8, BMC_MAX_MINI_DISPLAY, false, true, 0, BMC_MAX_MINI_DISPLAY_EVENTS},
    #endif

    #if BMC_MAX_LCD > 0
    {BMC_DEVICE_ID_LCD, "LCD", 8, BMC_DEVICE_ID_LCD, false, true, 0, 1},
    #endif

    

    #if BMC_MAX_MAGIC_ENCODERS > 0
    {BMC_DEVICE_ID_MAGIC_ENCODER, "Magic Encoder", 5, BMC_MAX_MAGIC_ENCODERS, false, 3, 3},
    #endif

    #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
    {BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER, "Magic Encoder", 5, BMC_MAX_GLOBAL_MAGIC_ENCODERS, true, true, 3, 3},
    #endif

    #if BMC_MAX_PRESETS > 0
    {BMC_DEVICE_ID_PRESET, "Preset", -1, BMC_MAX_PRESETS, true, false, 1, 0},
    #endif

    #if BMC_MAX_SETLISTS > 0
    {BMC_DEVICE_ID_SETLIST, "SetList", -1, BMC_MAX_SETLISTS, true, false, 1, 0},
    #endif

    #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
    {BMC_DEVICE_ID_SETLIST_SONG_LIBRARY, "Song", -1, BMC_MAX_SETLISTS_SONGS_LIBRARY, true, false, 1, 0},
    #endif

    #if BMC_MAX_TRIGGERS > 0
    {BMC_DEVICE_ID_TRIGGER, "Trigger", -1, BMC_MAX_TRIGGERS, true, false, 1, 2},
    #endif

    #if BMC_MAX_TEMPO_TO_TAP > 0
    {BMC_DEVICE_ID_TEMPO_TO_TAP, "Tempo 2 Tap", -1, BMC_MAX_TEMPO_TO_TAP, true, false, 0, 1},
    #endif

    #if BMC_MAX_CUSTOM_SYSEX > 0
    {BMC_DEVICE_ID_CUSTOM_SYSEX, "Custom SysEx", -1, BMC_MAX_CUSTOM_SYSEX, true, false, 1, 16},
    #endif

    #if BMC_MAX_PIXEL_PROGRAMS > 0
    {BMC_DEVICE_ID_PIXEL_PROGRAM, "Pixel Program", -1, BMC_MAX_PIXEL_PROGRAMS, true, false, 1, 8},
    #endif

    #if BMC_MAX_TIMED_EVENTS > 0
    {BMC_DEVICE_ID_TIMED_EVENT, "Timed Event", -1, BMC_MAX_TIMED_EVENTS, true, false, 2, 1},
    #endif

    #if BMC_MAX_SKETCH_BYTES > 0
    {BMC_DEVICE_ID_SKETCH_BYTE, "Sketch Bytes", -1, BMC_MAX_SKETCH_BYTES>0?1:0, true, false, 0, BMC_MAX_SKETCH_BYTES},
    #endif

    {BMC_DEVICE_ID_PORT_PRESET, "Port Preset", -1, 16, true, false, 0, 1},
    {BMC_DEVICE_ID_SHORTCUTS, "Shortcuts", -1, 1, true, false, 0, 6}
  };
  uint8_t devicesDataLength = 5;

  void setDevicesData(){
    #if BMC_MAX_BUTTONS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_BI_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_BI_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_TRI_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_TRI_LEDS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_ENCODERS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_ENCODERS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_POTS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_POTS > 0
    devicesDataLength++;
    #endif

    #if BMC_TOTAL_POTS_AUX_JACKS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_PIXELS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_PIXELS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_RGB_PIXELS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_PIXEL_STRIP > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_NL_RELAYS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_L_RELAYS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_AUX_JACKS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_LFO > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_OLED > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_ILI9341_BLOCKS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_MINI_DISPLAY > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_LCD > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_MAGIC_ENCODERS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_PRESETS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_SETLISTS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_TRIGGERS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_TEMPO_TO_TAP > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_CUSTOM_SYSEX > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_PIXEL_PROGRAMS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_TIMED_EVENTS > 0
    devicesDataLength++;
    #endif

    #if BMC_MAX_SKETCH_BYTES > 0
    devicesDataLength++;
    #endif
  }


uint8_t getDevicesDataLength(){
  return devicesDataLength;
}
BMCDeviceData getDeviceData(uint8_t id){
  for(uint16_t d=0;d<getDevicesDataLength();d++){
    if(devicesData[d].id == id){
      return devicesData[d];
    }
  }
  BMCDeviceData e;
  return e;
}
BMCDeviceData getDeviceDataByIndex(uint8_t index){
  if(index < getDevicesDataLength()){
    return devicesData[index];
  }
  BMCDeviceData e;
  return e;
}


  // keep these public for access by the Api
  // save "store.global.settings" to EEPROM
  void saveSettings(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      storage.set(address, store.global.settings);
    #endif
  }

  // save a single Event item to EEPROM
  void saveEvent(uint16_t index){
    if(index>=BMC_MAX_EVENTS_LIBRARY){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getEventsOffset(index);
      storage.set(address, store.global.events[index]);
    #endif
  }
  // save a single Event item to EEPROM
  void saveName(uint16_t index){
    if(index>=BMC_MAX_NAMES_LIBRARY){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getNamesOffset(index);
      storage.set(address, store.global.names[index]);
    #endif
  }
  void saveDevicePorts(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPortPresetsOffset(index);
      storage.set(address, store.global.portPresets[index]);
    #endif
  }
  void saveShortCuts(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getShortcutsOffset(index);
      storage.set(address, store.global.shortcuts[index]);
    #endif
  }
#if BMC_MAX_LFO > 0
  void saveLFO(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getLfoOffset(index);
      storage.set(address, store.global.lfo[index]);
    #endif
  }
#endif
#if BMC_MAX_SKETCH_BYTES > 0
  // save Sketch Bytes to EEPROM
  void saveSketchBytes(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getSketchBytesOffset(0);
      storage.set(address, store.global.sketchBytes);
    #endif
  }
#endif

#if BMC_MAX_PRESETS > 0
  // save the "startup" preset item to EEPROM
  /*
  void saveStartup(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getSketchBytesOffset();
      storage.set(address, store.global.startup);
    #endif
  }
  */
  // save a single "preset" to EEPROM
  void savePreset(uint16_t index){
    if(index>=BMC_MAX_PRESETS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPresetOffset(index);
      storage.set(address, store.global.presets[index]);
    #endif
  }
  #if BMC_MAX_SETLISTS > 0
    // save a single "preset" to EEPROM
    void saveSetList(uint8_t index){
      if(index >= BMC_MAX_SETLISTS){
        return;
      }
      #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
        storage.set(storeAddress, store);
      #else
        uint16_t address = getGlobalOffset();
        address += getSetListOffset(index);
        storage.set(address, store.global.setLists[index]);
      #endif
    }
    void saveSetListSong(uint16_t index){
      if(index >= BMC_MAX_SETLISTS_SONGS_LIBRARY){
        return;
      }
      #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
        storage.set(storeAddress, store);
      #else
        uint16_t address = getGlobalOffset();
        address += getSetListSongOffset(index);
        storage.set(address, store.global.songLibrary[index]);
      #endif
    }
  #endif
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  // save a single "global button" to EEPROM
  void saveGlobalButton(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_BUTTONS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalButtonOffset(index);
      storage.set(address, store.global.buttons[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  // save a single "global led" to EEPROM
  void saveGlobalLed(uint8_t index){
    if(index >= BMC_MAX_GLOBAL_LEDS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalLedOffset(index);
      storage.set(address, store.global.leds[index]);
    #endif
  }
#endif



#if BMC_MAX_GLOBAL_BI_LEDS > 0
  // save a single "global led" to EEPROM
  void saveGlobalBiLed(uint8_t index){
    if(index >= BMC_MAX_GLOBAL_BI_LEDS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalBiLedOffset(index);
      storage.set(address, store.global.biLeds[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  // save a single "global led" to EEPROM
  void saveGlobalTriLed(uint8_t index){
    if(index >= BMC_MAX_GLOBAL_TRI_LEDS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalTriLedOffset(index);
      storage.set(address, store.global.triLeds[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  // save a single "global encoder" to EEPROM
  void saveGlobalEncoder(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_ENCODERS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalEncoderOffset(index);
      storage.set(address, store.global.encoders[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  // save a single "global pot" to EEPROM
  void saveGlobalPot(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_POTS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalPotOffset(index);
      storage.set(address, store.global.pots[index]);
    #endif
  }
#endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
  void savePotCalibration(uint16_t index){
    if(index>=BMC_TOTAL_POTS_AUX_JACKS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPotCalibrationOffset(index);
      storage.set(address, store.global.potCalibration[index]);
    #endif
  }
#endif


#if BMC_MAX_GLOBAL_PIXELS > 0
  void saveGlobalPixel(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_PIXELS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalPixelOffset(index);
      storage.set(address, store.global.pixels[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  void saveGlobalRgbPixel(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_RGB_PIXELS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalRgbPixelOffset(index);
      storage.set(address, store.global.rgbPixels[index]);
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  void saveGlobalMagicEncoder(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_MAGIC_ENCODERS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalMagicEncoderOffset(index);
      storage.set(address, store.global.magicEncoders[index]);
    #endif
  }
#endif


#if BMC_MAX_NL_RELAYS > 0
  void saveNLRelay(uint8_t index){
    if(index>=BMC_MAX_NL_RELAYS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getNLRelayOffset(index);
      storage.set(address, store.global.relaysNL[index]);
    #endif
  }
#endif

#if BMC_MAX_L_RELAYS > 0
  void saveLRelay(uint8_t index){
    if(index>=BMC_MAX_L_RELAYS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getLRelayOffset(index);
      storage.set(address, store.global.relaysL[index]);
    #endif
  }
#endif

#if BMC_MAX_AUX_JACKS > 0
  void saveAuxJack(uint8_t index){
    if(index >= BMC_MAX_AUX_JACKS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getAuxJackOffset(index);
      storage.set(address, store.global.auxJacks[index]);
    #endif
  }
#endif




#if BMC_MAX_CUSTOM_SYSEX > 0
  // save a single "Custom SysEx" to EEPROM
  void saveCustomSysEx(uint8_t index){
    if(index>=BMC_MAX_CUSTOM_SYSEX){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getCustomSysExOffset(index);
      storage.set(address, store.global.customSysEx[index]);
    #endif
  }
#endif

#if BMC_MAX_TRIGGERS > 0
  // save a single "Trigger" to EEPROM
  void saveTrigger(uint8_t index){
    if(index>=BMC_MAX_TRIGGERS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getTriggerOffset(index);
      storage.set(address, store.global.triggers[index]);
    #endif
  }
#endif

#if BMC_MAX_TEMPO_TO_TAP > 0
  // save a single "Tempo To Tap" to EEPROM
  void saveTempoToTap(uint8_t index){
    if(index>=BMC_MAX_TEMPO_TO_TAP){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getTempoToTapOffset(index);
      storage.set(address, store.global.tempoToTap[index]);
    #endif
  }
#endif
  
#if BMC_MAX_PIXEL_PROGRAMS > 0
  void savePixelProgram(uint8_t n){
    if(n >= BMC_MAX_PIXEL_PROGRAMS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPixelProgramsOffset(n);
      storage.set(address, store.global.pixelPrograms[n]);
    #endif
  }
#endif
#if BMC_MAX_TIMED_EVENTS > 0
  // save a single "Timed Event" to EEPROM
  void saveTimedEvent(uint8_t n){
    if(n>=BMC_MAX_TIMED_EVENTS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getTimedEventOffset(n);
      storage.set(address, store.global.timedEvents[n]);
    #endif
  }
#endif
  // save a single layer to EEPROM
  void saveLayer(uint8_t layer){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress,store);
    #else
      uint16_t address = getGlobalOffset();
      address += sizeof(store.global) + (sizeof(store.layers[0]) * layer);
      storage.set(address, store.layers[layer]);
    #endif
  }
private:
  // save all layers to EEPROM
  void saveLayer(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      storage.set(storeAddress,store);
    #else
      uint16_t address = getGlobalOffset();
      address += sizeof(store.global);
      storage.set(address, store.layers);
    #endif
  }
  // save a single layer and notify to reassign
  void saveLayersAndReloadData(uint8_t layer){
    saveLayer(layer);
    reloadData();
  }
  // save all layers and notify to reassign
  void saveLayersAndReloadData(){
    saveLayer();
    reloadData();
  }
  // change the store address in EEPROM
  void setStoreAddress(uint8_t value){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      if(value >= BMC_FS_MAX_STORES){
        value = BMC_FS_MAX_STORES-1;
      }
    #endif
    if(value<maxStoreAddresses() && value < 32){
      storeAddress = value;
    }
  }
  // Get the maximum number of stores based on the store size and the eeprom size
  uint8_t maxStoreAddresses(){
#if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
    return BMC_FS_MAX_STORES;
#else
    uint8_t max = (storage.length()/sizeof(bmcStore));
    if(max==0){
      return 1;
    } else if(max>32){
      return 32;
    }
    return max;
#endif
  }

  // load the selected store into RAM
  void getStore(){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      uint16_t address = storeAddress;
    #else
      uint16_t address = getStoreOffset();
    #endif
    
    storage.get(address, store);
    

    // if the CRC in the store did NOT match the computed CRC then
    // we will clear all bytes of the store and add the new CRC and version
    // to EEPROM, this is so that if you recompile BMC with a new config
    // that has altered the store struct the bytes from the previous build
    // won't be all over the place and cause things to behave unexpectecly
    if(store.crc != BMC_CRC){
      // display a message confirming that EEPROM will be cleared if DEBUG
      BMC_WARN_HEAD;
      BMC_PRINTLN("Store",address,"CRC did NOT match");
      BMC_PRINTLN("store.crc:",store.crc,", BMC_CRC:",BMC_CRC);
      BMC_PRINTLN("Store",address,"is being Erased.");
      BMC_WARN_FOOT;
      // Erase the store and set all default values
      storeErase(true);

      
      
    } else {
      BMC_PRINTLN(" - Store looks good!");
      // update the device id on this store to match the one we already have
      // this is only done when a you change the store id so we skip doing this
      // when BMC first launches and gets the store.
      if(!flags.read(BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP)){
        if(settings.getDeviceId()!=deviceId){
          BMC_PRINTLN(" - Changing Device ID from",settings.getDeviceId(),"to",deviceId);
          settings.setDeviceId(deviceId);
          saveSettings();
        }
      }
    }
  }
  // @full = erases all data including touch calibration
  // erasing the touch calibration using the editor will cause
  // the on board editor not to work until the teensy is rebooted.
  void storeErase(bool full){
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      uint16_t address = storeAddress;
    #else
      uint16_t address = getStoreOffset();
    #endif


    #ifdef BMC_HAS_TOUCH_SCREEN
      // store touch calibration as it shouldn't get wiped when erasing
      bmcStoreTouchSettings touchTmp;
      bool isTouchCalibrated = settings.getTouchScreenIsCalibrated();
      touchTmp = store.global.settings.touchCalibration;
    #endif

    store = bmcStore();

    #ifdef BMC_HAS_TOUCH_SCREEN
      // restore touch calibration
      if(!full){
        store.global.settings.touchCalibration = touchTmp;
        settings.setTouchScreenIsCalibrated(isTouchCalibrated);
      }
    #endif

    // add the CRC
    store.crc = (BMC_CRC); // update the CRC
    store.version = (BMC_VERSION); // update the library version
    
    // save the new store with updated CRC and version
#if BMC_MAX_SKETCH_BYTES > 0
    for(uint8_t i = 0 ; i < BMC_MAX_SKETCH_BYTES ; i++){
      BMCSketchByteData data = BMCBuildData::getSketchByteData(i);
      store.global.sketchBytes[0].events[i] = data.getInitialValue();
    }
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0 && BMC_ILI_S_COUNT > 1
    for(uint8_t i = 0 ; i < BMC_MAX_LAYERS ; i++){
      for(uint8_t e = 0 ; e < BMC_MAX_ILI9341_BLOCKS ; e++){
        store.layers[i].ili[e].settings[1] = 1;
      }
    }
#endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
    for(uint16_t i = 0 ; i < BMC_TOTAL_POTS_AUX_JACKS ; i++){
      store.global.potCalibration[i].events[0] = 0;
      store.global.potCalibration[i].events[1] = 0x3FF;
    }
#endif

    store.global.shortcuts[0].events[0] = BMC_DEVICE_ID_EVENT;
    store.global.shortcuts[0].events[1] = BMC_DEVICE_ID_NAME;
    store.global.shortcuts[0].events[2] = BMC_DEVICE_ID_LFO;
    store.global.shortcuts[0].events[3] = BMC_DEVICE_ID_PORT_PRESET;

    // update the device id on this new store to match the one we already have
    settings.setDeviceId(deviceId);

#if BMC_TOTAL_PIXELS > 0
    // * value must be from 0 to 3
    // * 0 = 25% of BMC_PIXELS_MAX_CURRENT
    // * 1 = 50% of BMC_PIXELS_MAX_CURRENT
    // * 2 = 75% of BMC_PIXELS_MAX_CURRENT
    // * 3 = 100% of BMC_PIXELS_MAX_CURRENT
    settings.setPixelsBrightness(3);
#endif
    
    saveStore();

    storage.get(address, store);

    BMC_PRINTLN("get store after erase", address, store.crc)
    flags.on(BMC_EDITOR_FLAG_EEPROM_ERASED);
  }

  // BMC-Editor.midi.cpp
public:
  bool read();

private:
  void disconnect(bool t_notify=true);
  void sendToEditor(BMCMidiMessage message,
                    bool appendCRC=true,
                    bool midiOutActivityAllowed=false);
  void sendNotification(uint16_t code, uint32_t payload=0,
                        bool hasError=false, bool forceResponse=false);
  void sendInvalidIndexReceivedMessage();

  bool changeStoreLocal(uint8_t t_address){
    if(t_address==storeAddress || t_address >= maxStoreAddresses()){
      return false;
    }
    #if defined(BMC_SD_CARD_ENABLED) || defined(BMC_FS_ENABLED)
      setStoreAddress(t_address);
      getStore();
      delay(5);
      // update the device id on the current store
      settings.setDeviceId(deviceId);
      saveSettings();
    #else
      if(storeAddress!=0){
        storage.get(0, store);
      }
      setStoreAddress(t_address);
      settings.setStoreAddress(storeAddress);
      // always save the device id to store 0.
      settings.setDeviceId(deviceId);
      storage.set(0, store);
      getStore();
      delay(5);
      // update the device id on the current store
      settings.setDeviceId(deviceId);
      saveSettings();
    #endif
    return true;
  }
  bool isWriteMessage(){
    return midiFlags.isWrite();
  }
  bool isWriteToAllLayers(){
    return midiFlags.isLayer() && midiFlags.isAllLayers();
  }
  bool isDeviceWriteToAllLayers(){
    return !midiFlags.isLayer() && midiFlags.isAllLayers();
  }
  bool isLayerMessage(){
    return midiFlags.isLayer();
  }
  bool isBackupMessage(){
    return midiFlags.isBackup();
  }
  bool isErrorMessage(){
    return midiFlags.isError();
  }
  bool isUtilityMessage(){
    return getMessageRequestId() == BMC_GLOBALF_UTILITY;
  }
  uint8_t getMessageDeviceId(){
    return incoming.sysex[4];
  }
  uint16_t getMessageLayerNumber(){
    return incoming.get14Bits(6);
  }
  uint8_t getMessageRequestId(){
    return incoming.sysex[8];
  }
  uint8_t getMessageFlags(){
    return incoming.sysex[5];
  }
  bool isValidLayerMessage(bool checkSysExSize=true){
    return (isValidMessage(checkSysExSize) && isLayerMessage());
  }
  bool isValidGlobalMessage(bool checkSysExSize=true){
    return (isValidMessage(checkSysExSize) && !isLayerMessage());
  }
  bool isValidMessage(bool checkSysExSize=true){
    if(checkSysExSize){
      return (
        midi.globals.editorConnected() &&
        getMessageDeviceId() == deviceId &&
        incoming.getPort() == port &&
        incoming.peekSysEx(4) == deviceId &&
        incoming.size() >= BMC_EDITOR_SYSEX_MIN_LENGTH
      );
    }
    return (
      midi.globals.editorConnected() &&
      getMessageDeviceId() == deviceId &&
      incoming.getPort() == port &&
      incoming.peekSysEx(4) == deviceId
    );
  }

// BMC-Editor.midi.global.h
private:
  void globalProcessMessage();
  void globalBuildInfoMessage();
  void globalSettingsMessage(bool write);
  void globalBackupMessage(bool write);
  void globalSendBackupStatus();
  void globalStartup(bool write);
  void globalStoreAddress(bool write);
  void globalPotCalibration();
  void globalSketchBytesData();
  void globalSetTime(bool write);
  void globalGetFasState();
  void globalEditorFeedback(bool write);
  void globalEditorMetrics();
  void globalEditorMessenger(bool write);
  void globalEditorPerformMode(bool write);
  void globalEditorErase(bool write);

  void incomingMessageEvent(bool write);
  void incomingMessageName(bool write);
  void incomingMessageDevice(bool write);
  void incomingMessageLinks();

  

  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  void incomingMessageDeviceWrite(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, int16_t layer=-1, bool allowAnyValueForEvent=false);

  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  void deviceResponseData(bmcStoreDevice<sLen, eLen, tname>& item, BMCMidiMessage& buff, uint16_t index, uint8_t deviceType);

// BMC-Editor.midi.layer.h
private:

  void layerProcessMessage();
  void layerMessage(bool write);
  void layerNameMessage(bool write);
  void layerMessageLayerCopySwap(bool write);
  

public:
  void layerSendChangeMessage(bool onlyIfConnected=true);
  bool changeStore(uint8_t t_address){
    if(!connected()){
      if(changeStoreLocal(t_address)){
        return true;
      }
    }
    BMC_PRINTLN("store change error !!!!!!!!!!!!!!!");
    return false;
  }
  uint8_t getStoreAddress(){
    return storeAddress;
  }

// BMC-Editor.midi.utility.h
private:
  void utilityCommand();

public:

  void utilitySendStateBits(uint8_t itemId, bool onlyIfConnected=true);

  void utilitySendFasState(uint8_t data,
                              bool onlyIfConnected=true);

  void utilitySendPotActivity(uint8_t deviceType, uint16_t index, uint8_t value=0,
                              bool onlyIfConnected=true);

  void utilitySendEncoderActivity(uint8_t deviceType, uint8_t index, bool increased,
                                  bool onlyIfConnected=true);

  void utilitySendMagicEncoderActivity(uint8_t deviceType, uint8_t index, 
                                  uint8_t trigger, uint8_t ticks, bool increased,
                                  uint8_t ledValue,
                                  bool onlyIfConnected=true);

                                  

  void utilitySendPreset(uint8_t t_bank, uint8_t t_preset,
                        bool onlyIfConnected=true);

  void utilitySendClickTrackData(uint16_t freq, uint8_t level,
                                 uint8_t state, bool onlyIfConnected=true);

  void utilitySendAnalogInputCalibrationStatus(bool status, bool canceled=false, bool reset=false,
                                       bool onlyIfConnected=true);
  void utilitySendAnalogInputCalibrationActivity(uint8_t deviceId, uint16_t index,
                                        uint16_t min, uint16_t max,  uint16_t value,
                                        bool onlyIfConnected=true);

  void utilitySendSketchBytes(bool onlyIfConnected);


private:

  // GLOBAL
  void backupGlobalSettings(uint16_t t_minLength);
  void backupEventMessage(uint16_t t_minLength);
  void backupNameMessage(uint16_t t_minLength);
  void backupGlobalStartup(uint16_t t_minLength);

  void backupGlobalLibrary(uint16_t t_minLength);
  void backupGlobalPreset(uint16_t t_minLength);
  void backupGlobalSetList(uint16_t t_minLength);
  void backupGlobalSetListSong(uint16_t t_minLength);
  void backupGlobalLed(uint16_t t_minLength);
  void backupGlobalCustomSysEx(uint16_t t_minLength);
  void backupGlobalTriggers(uint16_t t_minLength);
  void backupGlobalTimedEvents(uint16_t t_minLength);
  void backupGlobalTempoToTap(uint16_t t_minLength);
  void backupGlobalSketchBytes(uint16_t t_minLength);
  void backupGlobalNLRelay(uint16_t t_minLength);
  void backupGlobalLRelay(uint16_t t_minLength);
  void backupGlobalPortPresets(uint16_t t_minLength);
  void backupPixelProgram(uint16_t t_minLength);
  void backupGlobalButton(uint16_t t_minLength);
  void backupGlobalEncoder(uint16_t t_minLength);
  void backupGlobalPot(uint16_t t_minLength);
  // LAYER
  void backupLayerName(uint16_t t_minLength);
  void backupLayerButton(uint16_t t_minLength);
  void backupLayerLed(uint16_t t_minLength);
  void backupLayerPwmLed(uint16_t t_minLength);
  void backupLayerPixel(uint16_t t_minLength);
  void backupLayerRgbPixel(uint16_t t_minLength);
  void backupLayerEncoder(uint16_t t_minLength);
  void backupLayerPot(uint16_t t_minLength);
  void backupLayerOled(uint16_t t_minLength);
  void backupLayerIli(uint16_t t_minLength);

};
#endif
