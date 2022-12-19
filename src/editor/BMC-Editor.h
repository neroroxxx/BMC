/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

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
#define BMC_EDITOR_FLAG_EDITOR_EEPROM_CLEARED       	 11
#define BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP        	 12
#define BMC_EDITOR_FLAG_BACKUP_ACTIVE               	 13
#define BMC_EDITOR_FLAG_BACKUP_STARTED              	 14
#define BMC_EDITOR_FLAG_BACKUP_COMPLETE             	 15
#define BMC_EDITOR_FLAG_BACKUP_CANCELED             	 16
#define BMC_EDITOR_FLAG_SEND_STATES                 	 17


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
  bmcStoreName getDeviceName(uint16_t n){
    bmcStoreName name;
    strcpy(name.name, "");
    if(n==0 || n > BMC_MAX_NAMES_LIBRARY){
      return name;
    }
    strcpy(name.name, store.global.names[n-1].name);
    return name;
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
  bool connected();
  bool connectionHasChanged();
  void connectEditor();
  void disconnectEditor();
  void forceDisconnectEditor();
  void setPort(uint8_t port);
  void setPage(uint8_t page);
  uint8_t getPage();
  uint16_t getEepromSize(){
    return storage.length();
  }

  void getGlobalData(bmcStoreGlobal& p){
    p = store.global;
  }
  void getPageData(bmcStorePage& p){
    p = store.pages[page];
  }
  void getPageData(uint8_t index, bmcStorePage& p){
    p = store.pages[index];
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
    return flags.toggleIfTrue(BMC_EDITOR_FLAG_EDITOR_EEPROM_CLEARED);
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
  // the current page we are working with
  uint8_t page = 0;
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
      flags.off(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.off(BMC_EDITOR_FLAG_BACKUP_CANCELED);
    }
  }
  void backupComplete(){
    // if the backup is running then stop it
    // and save the current store to EEPROM
    if(midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      BMC_INFO("Backup Complete");
      flags.off(BMC_EDITOR_FLAG_BACKUP_STARTED);
      flags.on(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.off(BMC_EDITOR_FLAG_BACKUP_CANCELED);
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
      saveStore();
      reloadData();
    }
  }
  void backupCancel(){
    if(midi.globals.editorConnected() && flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
      BMC_WARNING("Backup Canceled");
      flags.off(BMC_EDITOR_FLAG_BACKUP_STARTED);
      flags.off(BMC_EDITOR_FLAG_BACKUP_COMPLETE);
      flags.on(BMC_EDITOR_FLAG_BACKUP_CANCELED);
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
    /*
    switch(t_type){
      case BMC_DEVICE_ID_PAGE:                  return BMC_MAX_PAGES;
      case BMC_DEVICE_ID_BUTTON:                return BMC_MAX_BUTTONS;
      case BMC_DEVICE_ID_LED:                   return BMC_MAX_LEDS;
      case BMC_DEVICE_ID_PIXEL:                 return BMC_MAX_PIXELS;
      case BMC_DEVICE_ID_RGB_PIXEL:             return BMC_MAX_RGB_PIXELS;
      case BMC_DEVICE_ID_POT:                   return BMC_MAX_POTS;
      case BMC_DEVICE_ID_ENCODER:               return BMC_MAX_ENCODERS;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:         return BMC_MAX_GLOBAL_BUTTONS;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:        return BMC_MAX_GLOBAL_ENCODERS;
      case BMC_DEVICE_ID_GLOBAL_POT:            return BMC_MAX_GLOBAL_POTS;
      case BMC_DEVICE_ID_GLOBAL_LED:            return BMC_MAX_GLOBAL_LEDS;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:          return BMC_MAX_GLOBAL_PIXELS;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:      return BMC_MAX_GLOBAL_RGB_PIXELS;
      case BMC_DEVICE_ID_NL_RELAY:              return BMC_MAX_NL_RELAYS;
      case BMC_DEVICE_ID_L_RELAY:               return BMC_MAX_L_RELAYS;
      case BMC_DEVICE_ID_OLED:                  return BMC_MAX_OLED;
      case BMC_DEVICE_ID_ILI:                   return BMC_MAX_ILI9341_BLOCKS;
      case BMC_DEVICE_ID_PRESET:                return BMC_MAX_PRESETS;
      case BMC_DEVICE_ID_CUSTOM_SYSEX:          return BMC_MAX_CUSTOM_SYSEX;
      case BMC_DEVICE_ID_TRIGGER:               return BMC_MAX_TRIGGERS;
      case BMC_DEVICE_ID_TIMED_EVENT:           return BMC_MAX_TIMED_EVENTS;
      case BMC_DEVICE_ID_TEMPO_TO_TAP:          return BMC_MAX_TEMPO_TO_TAP;
      case BMC_DEVICE_ID_SKETCH_BYTE:           return BMC_MAX_SKETCH_BYTES;
      case BMC_DEVICE_ID_SETLIST:               return BMC_MAX_SETLISTS;
      case BMC_DEVICE_ID_SETLIST_SONG:          return BMC_MAX_SETLISTS_SONGS;
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:  return BMC_MAX_SETLISTS_SONGS_LIBRARY;
      case BMC_DEVICE_ID_PORT_PRESET:           return 16;
      case BMC_DEVICE_ID_PIXEL_PROGRAM:         return BMC_MAX_PIXEL_PROGRAMS;
      case BMC_DEVICE_ID_BI_LED:                return BMC_MAX_BI_LEDS;
      case BMC_DEVICE_ID_TRI_LED:               return BMC_MAX_TRI_LEDS;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:         return BMC_MAX_GLOBAL_BI_LEDS;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:        return BMC_MAX_GLOBAL_TRI_LEDS;
      case BMC_DEVICE_ID_AUX_JACK:              return BMC_MAX_AUX_JACKS;
      case BMC_DEVICE_ID_LFO:                   return BMC_MAX_LFO;
      case BMC_DEVICE_ID_SHORTCUTS:             return 1;
      case BMC_DEVICE_ID_PIXEL_STRIP:           return (BMC_MAX_PIXEL_STRIP>0)?1:0;
      case BMC_DEVICE_ID_POT_CALIBRATION:       return BMC_TOTAL_POTS_AUX_JACKS;
      case BMC_DEVICE_ID_MAGIC_ENCODER:         return BMC_MAX_MAGIC_ENCODERS;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:  return BMC_MAX_GLOBAL_MAGIC_ENCODERS;
    }
    */
    return 0;
  }
  String getDeviceName2(uint8_t t_type){
    switch(t_type){
      case BMC_DEVICE_ID_PAGE:                  return "Page Name";
      case BMC_DEVICE_ID_BUTTON:                return "Button";
      case BMC_DEVICE_ID_LED:                   return "Led";
      case BMC_DEVICE_ID_PIXEL:                 return "Pixel";
      case BMC_DEVICE_ID_RGB_PIXEL:             return "RGB Pixle";
      case BMC_DEVICE_ID_POT:                   return "Pot";
      case BMC_DEVICE_ID_ENCODER:               return "Encoder";
      case BMC_DEVICE_ID_GLOBAL_BUTTON:         return "Global Button";
      case BMC_DEVICE_ID_GLOBAL_ENCODER:        return "Global Encoder";
      case BMC_DEVICE_ID_GLOBAL_POT:            return "Global Pot";
      case BMC_DEVICE_ID_GLOBAL_LED:            return "Global Led";
      case BMC_DEVICE_ID_GLOBAL_PIXEL:          return "Global Pixel";
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:      return "Global RGB Pixel";
      case BMC_DEVICE_ID_NL_RELAY:              return "NL Relay";
      case BMC_DEVICE_ID_L_RELAY:               return "L Relay";
      case BMC_DEVICE_ID_OLED:                  return "OLED";
      case BMC_DEVICE_ID_ILI:                   return "ILI9341 Block";
      case BMC_DEVICE_ID_PRESET:                return "Preset";
      case BMC_DEVICE_ID_CUSTOM_SYSEX:          return "Custom SysEx";
      case BMC_DEVICE_ID_TRIGGER:               return "Trigger";
      case BMC_DEVICE_ID_TIMED_EVENT:           return "Timed Event";
      case BMC_DEVICE_ID_TEMPO_TO_TAP:          return "Tempo To Tap";
      case BMC_DEVICE_ID_SKETCH_BYTE:           return "Sketch Byte";
      case BMC_DEVICE_ID_SETLIST:               return "SetList";
      case BMC_DEVICE_ID_SETLIST_SONG:          return "Song";
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:  return "Song Library";
      case BMC_DEVICE_ID_PORT_PRESET:           return "Port Preset";
      case BMC_DEVICE_ID_PIXEL_PROGRAM:         return "Pixel Program";
      case BMC_DEVICE_ID_BI_LED:                return "Bi Led";
      case BMC_DEVICE_ID_TRI_LED:               return "Tri Led";
      case BMC_DEVICE_ID_GLOBAL_BI_LED:         return "Global Bi Led";
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:        return "Global Tri Led";
      case BMC_DEVICE_ID_AUX_JACK:              return "Aux Jack";
      case BMC_DEVICE_ID_LFO:                   return "LFO";
      case BMC_DEVICE_ID_SHORTCUTS:             return "Shortcuts";
      case BMC_DEVICE_ID_PIXEL_STRIP:           return "Pixel Strip";
    }
    return "";
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
  uint32_t getShortcutsOffset(uint8_t index);

  uint32_t getLfoOffset();
  uint32_t getLfoOffset(uint8_t index);

  uint32_t getSketchBytesOffset();
  uint32_t getSketchBytesOffset(uint8_t index);

  uint32_t getPresetOffset();
  uint32_t getPresetOffset(uint16_t index);

  uint32_t getSetListOffset();
  uint32_t getSetListOffset(uint8_t index);
  uint32_t getSetListSongOffset();
  uint32_t getSetListSongOffset(uint8_t index);


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
  uint32_t getCustomSysExOffset(uint8_t index);
  uint32_t getTriggerOffset();
  uint32_t getTriggerOffset(uint8_t index);
  uint32_t getTempoToTapOffset();
  uint32_t getTempoToTapOffset(uint8_t index);
  uint32_t getPortPresetsOffset();
  uint32_t getPortPresetsOffset(uint16_t index);
  uint32_t getPixelProgramsOffset();
  uint32_t getPixelProgramsOffset(uint8_t index);
  uint32_t getTimedEventOffset();
  uint32_t getTimedEventOffset(uint8_t n);

  // Clear the entire EEPROM
  void clearEEPROM(){
    storage.clear();
  }
  // save the entire "store" struct to EEPROM
  void saveStore(){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getStoreOffset();
      storage.set(address, store);
    #endif
  }
  // save "store.global" only to EEPROM
  void saveGlobal(){
    #if defined(BMC_SD_CARD_ENABLED)
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
    if(value>0){
      if(strlen(store.global.names[value-1].name) > 0){
        strcpy(str, store.global.names[value-1].name);
        return;
      }
    }
    strcpy(str, "...");
  }
  void getDeviceNameText(uint8_t deviceType, uint16_t index, char* str){
    switch(deviceType){
      case BMC_DEVICE_ID_PAGE:
        getDeviceNameFromIndex(store.pages[index].name, str);
        break;
      case BMC_DEVICE_ID_EVENT:
        getDeviceNameFromIndex(store.global.events[index].name, str);
        break;
      case BMC_DEVICE_ID_NAME:
        getDeviceNameFromIndex(index+1, str);
        break;
      case BMC_DEVICE_ID_BUTTON:
        #if BMC_MAX_BUTTONS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].buttons[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
        #if BMC_MAX_GLOBAL_BUTTONS > 0
          getDeviceNameFromIndex(store.global.buttons[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_LED:
        #if BMC_MAX_LEDS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].leds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_LED:
        #if BMC_MAX_GLOBAL_LEDS > 0
          getDeviceNameFromIndex(store.global.leds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_BI_LED:
        #if BMC_MAX_BI_LEDS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].biLeds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
          getDeviceNameFromIndex(store.global.biLeds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_TRI_LED:
        #if BMC_MAX_TRI_LEDS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].triLeds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
          getDeviceNameFromIndex(store.global.triLeds[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_ENCODER:
        #if BMC_MAX_ENCODERS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].encoders[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
        #if BMC_MAX_GLOBAL_ENCODERS > 0
          getDeviceNameFromIndex(store.global.encoders[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_POT:
        #if BMC_MAX_POTS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].pots[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_POT:
        #if BMC_MAX_GLOBAL_POTS > 0
          getDeviceNameFromIndex(store.global.pots[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_POT_CALIBRATION:
        #if BMC_TOTAL_POTS_AUX_JACKS > 0
          getDeviceNameFromIndex(store.global.potCalibration[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_MAGIC_ENCODER:
        #if BMC_MAX_MAGIC_ENCODERS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].magicEncoders[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
        #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
          getDeviceNameFromIndex(store.global.magicEncoders[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL:
        #if BMC_MAX_PIXELS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].pixels[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
        #if BMC_MAX_GLOBAL_PIXELS > 0
          getDeviceNameFromIndex(store.global.pixels[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_RGB_PIXEL:
        #if BMC_MAX_RGB_PIXELS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].rgbPixels[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
          getDeviceNameFromIndex(store.global.rgbPixels[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_PIXEL_STRIP:
        #if BMC_MAX_PIXEL_STRIP > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].pixelStrip[0].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_NL_RELAY:
        #if BMC_MAX_NL_RELAYS > 0
          getDeviceNameFromIndex(store.global.relaysNL[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_L_RELAY:
        #if BMC_MAX_L_RELAYS > 0
          getDeviceNameFromIndex(store.global.relaysL[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_AUX_JACK:
        #if BMC_MAX_AUX_JACKS > 0
          getDeviceNameFromIndex(store.global.auxJacks[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_OLED:
        #if BMC_MAX_OLED > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].oled[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_ILI:
        #if BMC_MAX_ILI9341_BLOCKS > 0
          getDeviceNameFromIndex(store.pages[midi.globals.page].ili[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_LFO:
        #if BMC_MAX_LFO > 0
          getDeviceNameFromIndex(store.global.lfo[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_PRESET:
        #if BMC_MAX_PRESETS > 0
          getDeviceNameFromIndex(store.global.presets[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_CUSTOM_SYSEX:
        #if BMC_MAX_CUSTOM_SYSEX > 0
          getDeviceNameFromIndex(store.global.customSysEx[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_TRIGGER:
        #if BMC_MAX_TRIGGERS > 0
          getDeviceNameFromIndex(store.global.triggers[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_TEMPO_TO_TAP:
        #if BMC_MAX_TEMPO_TO_TAP > 0
          getDeviceNameFromIndex(store.global.tempoToTap[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_PORT_PRESET:
        getDeviceNameFromIndex(store.global.portPresets[index].name, str);
        break;
      case BMC_DEVICE_ID_SHORTCUTS:
        getDeviceNameFromIndex(store.global.shortcuts[index].name, str);
        break;
      case BMC_DEVICE_ID_PIXEL_PROGRAM:
        #if BMC_MAX_PIXEL_PROGRAMS > 0
          getDeviceNameFromIndex(store.global.pixelPrograms[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_SKETCH_BYTE:
        #if BMC_MAX_SKETCH_BYTES > 0
          // getDeviceNameFromIndex(store.global.sketchBytes[0], buff, 0, deviceType);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST:
        #if BMC_MAX_SETLISTS > 0
          getDeviceNameFromIndex(store.global.setLists[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_SETLIST_SONG:

        break;
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:
        #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
          getDeviceNameFromIndex(store.global.songLibrary[index].name, str);
        #endif
        break;
      case BMC_DEVICE_ID_TIMED_EVENT:
        #if BMC_MAX_TIMED_EVENTS > 0
          getDeviceNameFromIndex(store.global.timedEvents[index].name, str);
        #endif
        break;
    }
  }
  const BMCDeviceData devicesData[40] = {
    {BMC_DEVICE_ID_PAGE, "BMC_DEVICE_ID_PAGE", "Page Name", -1, BMC_MAX_PAGES, false, 0, 0},
    {BMC_DEVICE_ID_EVENT, "BMC_DEVICE_ID_EVENT", "Event", -1, BMC_MAX_EVENTS_LIBRARY, true, 0, 0},
    {BMC_DEVICE_ID_NAME, "BMC_DEVICE_ID_NAME", "Name", -1, BMC_MAX_NAMES_LIBRARY, true, 0, 0},
    #if BMC_MAX_BUTTONS > 0
    {BMC_DEVICE_ID_BUTTON, "BMC_DEVICE_ID_BUTTON", "Button", 1, BMC_MAX_BUTTONS, false, BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS},
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
    {BMC_DEVICE_ID_GLOBAL_BUTTON, "BMC_DEVICE_ID_GLOBAL_BUTTON", "Global Button", 1, BMC_MAX_GLOBAL_BUTTONS, true, BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS},
    #endif

    #if BMC_MAX_LEDS > 0
    {BMC_DEVICE_ID_LED, "BMC_DEVICE_ID_LED", "Led", 2, BMC_MAX_LEDS, false, 1, 1},
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_LED, "BMC_DEVICE_ID_GLOBAL_LED", "Global Led", 2, BMC_MAX_GLOBAL_LEDS, true, 1, 1},
    #endif

    #if BMC_MAX_BI_LEDS > 0
    {BMC_DEVICE_ID_BI_LED, "BMC_DEVICE_ID_BI_LED", "Bi-Color Led", 2, BMC_MAX_BI_LEDS, false, 0, 2},
    #endif

    #if BMC_MAX_GLOBAL_BI_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_BI_LED, "BMC_DEVICE_ID_GLOBAL_BI_LED", "Global Bi Led", 2, BMC_MAX_GLOBAL_BI_LEDS, true, 0, 2},
    #endif

    #if BMC_MAX_TRI_LEDS > 0
    {BMC_DEVICE_ID_TRI_LED, "BMC_DEVICE_ID_TRI_LED", "Tri-Color Led", 2, BMC_MAX_TRI_LEDS, false, 0, 3},
    #endif

    #if BMC_MAX_GLOBAL_TRI_LEDS > 0
    {BMC_DEVICE_ID_GLOBAL_TRI_LED, "BMC_DEVICE_ID_GLOBAL_TRI_LED", "Global Tri Led", 2, BMC_MAX_GLOBAL_TRI_LEDS, true, 0, 3},
    #endif

    #if BMC_MAX_ENCODERS > 0
    {BMC_DEVICE_ID_ENCODER, "BMC_DEVICE_ID_ENCODER", "Encoder", 3, BMC_MAX_ENCODERS, false, 0, 1},
    #endif

    #if BMC_MAX_GLOBAL_ENCODERS > 0
    {BMC_DEVICE_ID_GLOBAL_ENCODER, "BMC_DEVICE_ID_GLOBAL_ENCODER", "Global Encoder", 3, BMC_MAX_GLOBAL_ENCODERS, true, 0, 1},
    #endif

    #if BMC_MAX_POTS > 0
    {BMC_DEVICE_ID_POT, "BMC_DEVICE_ID_POT", "Pot", 4, BMC_MAX_POTS, false, 1, 3},
    #endif

    #if BMC_MAX_GLOBAL_POTS > 0
    {BMC_DEVICE_ID_GLOBAL_POT, "BMC_DEVICE_ID_GLOBAL_POT", "Global Pot", 4, BMC_MAX_GLOBAL_POTS, true, 1, 3},
    #endif

    #if BMC_TOTAL_POTS_AUX_JACKS > 0
    {BMC_DEVICE_ID_POT_CALIBRATION, "BMC_DEVICE_ID_POT_CALIBRATION", "Analog Calibration", -1, BMC_TOTAL_POTS_AUX_JACKS, true, 0, 2},
    #endif

    #if BMC_MAX_PIXELS > 0
    {BMC_DEVICE_ID_PIXEL, "BMC_DEVICE_ID_PIXEL", "Pixel", 2, BMC_MAX_PIXELS, false, 1, 1},
    #endif

    #if BMC_MAX_GLOBAL_PIXELS > 0
    {BMC_DEVICE_ID_GLOBAL_PIXEL, "BMC_DEVICE_ID_GLOBAL_PIXEL", "Global Pixel", 2, BMC_MAX_GLOBAL_PIXELS, true, 1, 1},
    #endif

    #if BMC_MAX_RGB_PIXELS > 0
    {BMC_DEVICE_ID_RGB_PIXEL, "BMC_DEVICE_ID_RGB_PIXEL", "RGB Pixel", 2, BMC_MAX_RGB_PIXELS, false, 0, 3},
    #endif

    #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    {BMC_DEVICE_ID_GLOBAL_RGB_PIXEL, "BMC_DEVICE_ID_GLOBAL_RGB_PIXEL", "Global RGB Pixel", 2, BMC_MAX_GLOBAL_RGB_PIXELS, true, 0, 3},
    #endif

    #if BMC_MAX_PIXEL_STRIP > 0
    {BMC_DEVICE_ID_PIXEL_STRIP, "BMC_DEVICE_ID_PIXEL_STRIP", "Pixel Strip", 2, BMC_MAX_PIXEL_STRIP>0?1:0, false, 1, 1},
    #endif

    #if BMC_MAX_NL_RELAYS > 0
    {BMC_DEVICE_ID_NL_RELAY, "BMC_DEVICE_ID_NL_RELAY", "Non-Latching Relay", 6, BMC_MAX_NL_RELAYS, true, 1, 1},
    #endif

    #if BMC_MAX_L_RELAYS > 0
    {BMC_DEVICE_ID_L_RELAY, "BMC_DEVICE_ID_L_RELAY", "Latching Relay", 6, BMC_MAX_L_RELAYS, true, 1, 1},
    #endif

    #if BMC_MAX_AUX_JACKS > 0
    {BMC_DEVICE_ID_AUX_JACK, "BMC_DEVICE_ID_AUX_JACK", "Aux Jack", 7, BMC_MAX_AUX_JACKS, true, 2, 3},
    #endif

    #if BMC_MAX_LFO > 0
    {BMC_DEVICE_ID_LFO, "BMC_DEVICE_ID_LFO", "LFO", -1, BMC_MAX_LFO, true, 3, 5},
    #endif

    #if BMC_MAX_OLED > 0
    {BMC_DEVICE_ID_OLED, "BMC_DEVICE_ID_OLED", "OLED Display", 8, BMC_MAX_OLED, false, 0, 1},
    #endif

    #if BMC_MAX_ILI9341_BLOCKS > 0
    {BMC_DEVICE_ID_ILI, "BMC_DEVICE_ID_ILI", "ILI9341 Block", 8, BMC_MAX_ILI9341_BLOCKS, false, 0, 1},
    #endif

    #if BMC_MAX_MAGIC_ENCODERS > 0
    {BMC_DEVICE_ID_MAGIC_ENCODER, "BMC_DEVICE_ID_MAGIC_ENCODER", "Magic Encoder", 5, BMC_MAX_MAGIC_ENCODERS, false, 3, 3},
    #endif

    #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
    {BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER, "BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER", "Gbl Magic Encoder", 5, BMC_MAX_GLOBAL_MAGIC_ENCODERS, true, 3, 3},
    #endif

    #if BMC_MAX_PRESETS > 0
    {BMC_DEVICE_ID_PRESET, "BMC_DEVICE_ID_PRESET", "Preset", -1, BMC_MAX_PRESETS, true, 1, 0},
    #endif

    #if BMC_MAX_SETLISTS > 0
    {BMC_DEVICE_ID_SETLIST, "BMC_DEVICE_ID_SETLIST", "SetList", -1, BMC_MAX_SETLISTS, true, 1, 0},
    #endif

    #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
    {BMC_DEVICE_ID_SETLIST_SONG_LIBRARY, "BMC_DEVICE_ID_SETLIST_SONG_LIBRARY", "Song", -1, BMC_MAX_SETLISTS_SONGS_LIBRARY, true, 1, 0},
    #endif

    #if BMC_MAX_TRIGGERS > 0
    {BMC_DEVICE_ID_TRIGGER, "BMC_DEVICE_ID_TRIGGER", "Trigger", -1, BMC_MAX_TRIGGERS, true, 1, 2},
    #endif

    #if BMC_MAX_TEMPO_TO_TAP > 0
    {BMC_DEVICE_ID_TEMPO_TO_TAP, "BMC_DEVICE_ID_TEMPO_TO_TAP", "Tempo to Tap", -1, BMC_MAX_TEMPO_TO_TAP, true, 0, 1},
    #endif

    #if BMC_MAX_CUSTOM_SYSEX > 0
    {BMC_DEVICE_ID_CUSTOM_SYSEX, "BMC_DEVICE_ID_CUSTOM_SYSEX", "Custom SysEx", -1, BMC_MAX_CUSTOM_SYSEX, true, 1, 16},
    #endif

    #if BMC_MAX_PIXEL_PROGRAMS > 0
    {BMC_DEVICE_ID_PIXEL_PROGRAM, "BMC_DEVICE_ID_PIXEL_PROGRAM", "Pixel Program", -1, BMC_MAX_PIXEL_PROGRAMS, true, 1, 8},
    #endif

    #if BMC_MAX_TIMED_EVENTS > 0
    {BMC_DEVICE_ID_TIMED_EVENT, "BMC_DEVICE_ID_TIMED_EVENT", "Timed Event", -1, BMC_MAX_TIMED_EVENTS, true, 2, 1},
    #endif

    #if BMC_MAX_SKETCH_BYTES > 0
    {BMC_DEVICE_ID_SKETCH_BYTE, "BMC_DEVICE_ID_SKETCH_BYTE", "Sketch Bytes", -1, BMC_MAX_SKETCH_BYTES>0?1:0, true, 0, 0},
    #endif

    {BMC_DEVICE_ID_PORT_PRESET, "BMC_DEVICE_ID_PORT_PRESET", "Port Preset", -1, 16, true, 0, 1},
    {BMC_DEVICE_ID_SHORTCUTS, "BMC_DEVICE_ID_SHORTCUTS", "Shortcuts", -1, 1, true, 0, 6},
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getNamesOffset(index);
      storage.set(address, store.global.names[index]);
    #endif
  }
  void saveDevicePorts(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPortPresetsOffset(index);
      storage.set(address, store.global.portPresets[index]);
    #endif
  }
  void saveShortCuts(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getShortcutsOffset(index);
      storage.set(address, store.global.shortcuts[index]);
    #endif
  }
#if BMC_MAX_LFO > 0
  void saveLFO(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
      #if defined(BMC_SD_CARD_ENABLED)
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
      #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    if(index>=BMC_MAX_AUX_JACKS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
    BMC_PRINTLN("savePixelProgram", n);
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPixelProgramsOffset(n);
      BMC_PRINTLN("savePixelProgram",address);
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
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getTimedEventOffset(n);
      storage.set(address, store.global.timedEvents[n]);
    #endif
  }
#endif
  // save a single page to EEPROM
  void savePage(uint8_t page){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress,store);
    #else
      uint16_t address = getGlobalOffset();
      address += sizeof(store.global) + (sizeof(store.pages[0]) * page);
      BMC_PRINTLN("page address:", address);
      storage.set(address, store.pages[page]);
    #endif
  }
private:
  // save all pages to EEPROM
  void savePage(){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress,store);
    #else
      uint16_t address = getGlobalOffset();
      address += sizeof(store.global);
      storage.set(address,store.pages);
    #endif
  }
  // save a single page and notify to reassign
  void savePagesAndReloadData(uint8_t page){
    savePage(page);
    reloadData();
  }
  // save all pages and notify to reassign
  void savePagesAndReloadData(){
    savePage();
    reloadData();
  }
  // change the store address in EEPROM
  void setStoreAddress(uint8_t value){
    #if defined(BMC_SD_CARD_ENABLED)
      if(value>=BMC_FS_MAX_STORES){
        value = BMC_FS_MAX_STORES-1;
      }
    #endif
    if(value<maxStoreAddresses() && value < 32){
      storeAddress = value;
    }
  }
  // Get the maximum number of stores based on the store size and the eeprom size
  uint8_t maxStoreAddresses(){
#if defined(BMC_SD_CARD_ENABLED)
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
    #if defined(BMC_SD_CARD_ENABLED)
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
      BMC_PRINTLN("EEPROM Store",address,"CRC did NOT match");
      BMC_PRINTLN("store.crc:",store.crc,", BMC_CRC:",BMC_CRC);
      BMC_PRINTLN("EEPROM Store",address,"is being Erased.");
      BMC_WARN_FOOT;
      // clear the current store in RAM by setting all bytes to 0
      memset(&store,0,sizeof(bmcStore));
      // add the CRC
      store.crc = (BMC_CRC); // update the CRC
      store.version = (BMC_VERSION); // update the library version
      // save the new store with updated CRC and version
#if BMC_MAX_SKETCH_BYTES > 0
      for(uint8_t i=0;i<BMC_MAX_SKETCH_BYTES;i++){
        BMCSketchByteData data = BMCBuildData::getSketchByteData(i);
        //store.global.sketchBytes[i] = constrain(data.initialValue, data.min, data.max);
        store.global.sketchBytes[0].events[i] = data.getInitialValue();
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
      saveStore();
      storage.get(address, store);
      flags.on(BMC_EDITOR_FLAG_EDITOR_EEPROM_CLEARED);
    } else {
      // update the device id on this store to match the one we already have
      // this is only done when a you change the store id so we skip doing this
      // when BMC first launches and gets the store.
      if(!flags.read(BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP)){
        if(settings.getDeviceId()!=deviceId){
          BMC_PRINTLN("Changing Device ID from",settings.getDeviceId(),"to",deviceId);
          settings.setDeviceId(deviceId);
          saveSettings();
        }
      }
    }
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
    #if defined(BMC_SD_CARD_ENABLED)
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
  bool isWriteToAllPages(){
    return midiFlags.isPage() && midiFlags.isAllPages();
  }
  bool isDeviceWriteToAllPages(){
    return !midiFlags.isPage() && midiFlags.isAllPages();
  }
  bool isPageMessage(){
    return midiFlags.isPage();
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
  uint16_t getMessagePageNumber(){
    return incoming.get14Bits(6);
  }
  uint8_t getMessageRequestId(){
    return incoming.sysex[8];
  }
  uint8_t getMessageFlags(){
    return incoming.sysex[5];
  }
  bool isValidPageMessage(bool checkSysExSize=true){
    return (isValidMessage(checkSysExSize) && isPageMessage());
  }
  bool isValidGlobalMessage(bool checkSysExSize=true){
    return (isValidMessage(checkSysExSize) && !isPageMessage());
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

  void incomingMessageEvent(bool write);
  void incomingMessageName(bool write);
  void incomingMessageDevice(bool write);

  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  void incomingMessageDeviceWrite(bmcStoreDevice<sLen, eLen, tname>& item, uint16_t index, int16_t page=-1);

  template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
  void deviceResponseData(bmcStoreDevice<sLen, eLen, tname>& item, BMCMidiMessage& buff, uint16_t index, uint8_t deviceType);

// BMC-Editor.midi.page.h
private:

  void pageProcessMessage();
  void pageMessage(bool write);
  void pageNameMessage(bool write);

public:
  void pageSendChangeMessage(bool onlyIfConnected=true);
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

  void utilitySendAnalogInputCalibrationStatus(bool status, bool canceled=false,
                                       bool onlyIfConnected=true);
  void utilitySendAnalogInputCalibrationActivity(uint8_t deviceId, uint16_t index,
                                        uint16_t min, uint16_t max,
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
  // PAGE
  void backupPageName(uint16_t t_minLength);
  void backupPageButton(uint16_t t_minLength);
  void backupPageLed(uint16_t t_minLength);
  void backupPagePwmLed(uint16_t t_minLength);
  void backupPagePixel(uint16_t t_minLength);
  void backupPageRgbPixel(uint16_t t_minLength);
  void backupPageEncoder(uint16_t t_minLength);
  void backupPagePot(uint16_t t_minLength);
  void backupPageOled(uint16_t t_minLength);
  void backupPageIli(uint16_t t_minLength);

};
#endif
