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

#define BMC_EDITOR_FLAG_CONNECTED 0
#define BMC_EDITOR_FLAG_CONNECTION_HAS_CHANGED 1
#define BMC_EDITOR_FLAG_READY_TO_RELOAD 2
#define BMC_EDITOR_FLAG_DATA_FOR_BMC_AVAILABLE 3
#define BMC_EDITOR_FLAG_CONNECTING_TO_EDITOR 4
#define BMC_EDITOR_FLAG_EDITOR_FEEDBACK 5
#define BMC_EDITOR_FLAG_EDITOR_DISCONNECTED 6
#define BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED 7
#define BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED 8
#define BMC_EDITOR_FLAG_EDITOR_EEPROM_CLEARED 9
#define BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP 10

#define BMC_EDITOR_FLAG_BACKUP_ACTIVE 11
#define BMC_EDITOR_FLAG_BACKUP_STARTED 12
#define BMC_EDITOR_FLAG_BACKUP_COMPLETE 13
#define BMC_EDITOR_FLAG_BACKUP_CANCELED 14


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

#if BMC_MAX_POTS > 0
  void setPotCalibration(uint8_t index, uint16_t min, uint16_t max){
    if(index<BMC_MAX_POTS){
      store.global.potCalibration[index].min = min;
      store.global.potCalibration[index].max = max;
      saveGlobalAndReloadData();
    }
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  void setGlobalPotCalibration(uint8_t index, uint16_t min, uint16_t max){
    if(index<BMC_MAX_GLOBAL_POTS){
      store.global.globalPotCalibration[index].min = min;
      store.global.globalPotCalibration[index].max = max;
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
  BMCFlags <uint16_t> flags;
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
    switch(t_type){
      case BMC_ITEM_ID_BUTTON:          return BMC_MAX_BUTTONS;
      case BMC_ITEM_ID_LED:             return BMC_MAX_LEDS;
      case BMC_ITEM_ID_PWM_LED:         return BMC_MAX_PWM_LEDS;
      case BMC_ITEM_ID_PIXEL:           return BMC_MAX_PIXELS;
      case BMC_ITEM_ID_RGB_PIXEL:       return BMC_MAX_RGB_PIXELS;
      case BMC_ITEM_ID_POT:             return BMC_MAX_POTS;
      case BMC_ITEM_ID_ENCODER:         return BMC_MAX_ENCODERS;
      case BMC_ITEM_ID_GLOBAL_BUTTON:   return BMC_MAX_GLOBAL_BUTTONS;
      case BMC_ITEM_ID_GLOBAL_ENCODER:  return BMC_MAX_GLOBAL_ENCODERS;
      case BMC_ITEM_ID_GLOBAL_POT:      return BMC_MAX_GLOBAL_POTS;
      case BMC_ITEM_ID_GLOBAL_LED:      return BMC_MAX_GLOBAL_LEDS;
      case BMC_ITEM_ID_LIBRARY:         return BMC_MAX_LIBRARY;
      case BMC_ITEM_ID_STRING_LIBRARY:  return BMC_MAX_STRING_LIBRARY;
      case BMC_ITEM_ID_PRESET:          return BMC_MAX_PRESETS;
      case BMC_ITEM_ID_CUSTOM_SYSEX:    return BMC_MAX_CUSTOM_SYSEX;
      case BMC_ITEM_ID_TRIGGER:         return BMC_MAX_TRIGGERS;
      case BMC_ITEM_ID_TIMED_EVENT:     return BMC_MAX_TIMED_EVENTS;
      case BMC_ITEM_ID_TEMPO_TO_TAP:    return BMC_MAX_TEMPO_TO_TAP;
      case BMC_ITEM_ID_SKETCH_BYTES:    return BMC_MAX_SKETCH_BYTES;
      case BMC_ITEM_ID_NL_RELAY:        return BMC_MAX_NL_RELAYS;
      case BMC_ITEM_ID_L_RELAY:         return BMC_MAX_L_RELAYS;
      case BMC_ITEM_ID_SETLIST:         return BMC_MAX_SETLISTS;
      case BMC_ITEM_ID_SETLIST_SONG:    return BMC_MAX_SETLISTS_SONGS;
      case BMC_ITEM_ID_SETLIST_SONG_LIBRARY:    return BMC_MAX_SETLISTS_SONGS_LIBRARY;
      case BMC_ITEM_ID_OLED:            return BMC_MAX_OLED;
      case BMC_ITEM_ID_ILI:            return BMC_MAX_ILI9341_BLOCKS;
    }
    return 0;
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
  uint32_t getSketchBytesOffset();
  uint32_t getStringLibraryOffset();
  uint32_t getStringLibraryOffset(uint8_t index);
  uint32_t getLibraryOffset();
  uint32_t getLibraryOffset(bmcLibrary_t index);
  uint32_t getPresetOffset();
  uint32_t getPresetOffset(bmcPreset_t index);
  uint32_t getSetListOffset();
  uint32_t getSetListOffset(uint8_t index);
  uint32_t getSetListSongOffset();
  uint32_t getSetListSongOffset(uint8_t index);
  uint32_t getGlobalLedOffset();
  uint32_t getGlobalLedOffset(uint8_t index);

  uint32_t getGlobalButtonOffset();
  uint32_t getGlobalButtonOffset(uint8_t index);
  uint32_t getGlobalEncoderOffset();
  uint32_t getGlobalEncoderOffset(uint8_t index);
  uint32_t getGlobalPotOffset();
  uint32_t getGlobalPotOffset(uint8_t index);
  uint32_t getGlobalPotCalibrationOffset();
  uint32_t getGlobalPotCalibrationOffset(uint8_t index);

  uint32_t getPotCalibrationOffset();
  uint32_t getPotCalibrationOffset(uint8_t index);
  uint32_t getCustomSysExOffset();
  uint32_t getCustomSysExOffset(uint8_t index);
  uint32_t getTriggerOffset();
  uint32_t getTriggerOffset(uint8_t index);
  uint32_t getTempoToTapOffset();
  uint32_t getTempoToTapOffset(uint8_t index);
  uint32_t getNLRelayOffset();
  uint32_t getNLRelayOffset(uint8_t index);
  uint32_t getLRelayOffset();
  uint32_t getLRelayOffset(uint8_t index);
  uint32_t getPortPresetsOffset();
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

#if BMC_MAX_SKETCH_BYTES > 0
  // save Sketch Bytes to EEPROM
  void saveSketchBytes(){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getSettingsOffset();
      storage.set(address, store.global.sketchBytes);
    #endif
  }
#endif

#if BMC_MAX_STRING_LIBRARY > 0
  // save a single "string library" item to EEPROM
  void saveStringLibrary(uint8_t index){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getStringLibraryOffset(index);
      storage.set(address, store.global.stringLibrary[index]);
    #endif
  }
#endif

#if BMC_MAX_LIBRARY > 0
  // save a single "library" item to EEPROM
  void saveLibrary(bmcLibrary_t index){
    if(index>=BMC_MAX_LIBRARY){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getLibraryOffset(index);
      storage.set(address, store.global.library[index]);
    #endif
  }
#endif

#if BMC_MAX_LIBRARY > 0 && BMC_MAX_PRESETS > 0
  // save the "startup" preset item to EEPROM
  void saveStartup(){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getLibraryOffset();
      storage.set(address, store.global.startup);
    #endif
  }
  // save a single "preset" to EEPROM
  void savePreset(bmcPreset_t index){
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

#if BMC_MAX_GLOBAL_LEDS > 0
  // save a single "global led" to EEPROM
  void saveGlobalLed(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_LEDS){
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
  // save a single global pot calibrarion to EEPROM
  void saveGlobalPotCalibration(uint8_t index){
    if(index>=BMC_MAX_GLOBAL_POTS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getGlobalPotCalibrationOffset(index);
      storage.set(address, store.global.globalPotCalibration[index]);
    #endif
  }

#endif

#if BMC_MAX_POTS > 0
  // save a single "pot" to EEPROM
  void savePotCalibration(uint8_t index){
    if(index>=BMC_MAX_POTS){
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

#if BMC_MAX_NL_RELAYS > 0
  // save a single "Tempo To Tap" to EEPROM
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
  // save a single "Tempo To Tap" to EEPROM
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
  // save a single "Tempo To Tap" to EEPROM
  void saveDevicePorts(){
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPortPresetsOffset();
      storage.set(address, store.global.portPresets);
    #endif
  }
#if BMC_MAX_PIXEL_PROGRAMS > 0
  void savePixelProgram(uint8_t index){
    if(index >= BMC_MAX_PIXEL_PROGRAMS){
      return;
    }
    #if defined(BMC_SD_CARD_ENABLED)
      storage.set(storeAddress, store);
    #else
      uint16_t address = getGlobalOffset();
      address += getPixelProgramsOffset(index);
      storage.set(address, store.global.pixelPrograms);
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
      storage.set(address,store.pages[page]);
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
        store.global.sketchBytes[i] = data.getInitialValue();
      }
#endif
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
                        bool hasError=false);
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
    //return BMC_MIDI_ARRAY_TO_8BITS(6,incoming.sysex);
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
  void globalStringLibrary(bool write);
  void globalLibrary(bool write);
  void globalPreset(bool write);
  void globalStartup(bool write);
  void globalStoreAddress(bool write);
  void globalLeds(bool write);
  void globalPixelProgram(bool write);

  void globalButton(bool write);
  void globalEncoder(bool write);
  void globalPot(bool write);
  void globalGlobalPotCalibration();

  void globalPotCalibration();
  void globalCustomSysEx(bool write);
  void globalTriggers(bool write);
  void globalTimedEvents(bool write);
  void globalTempoToTap(bool write);
  void globalSketchBytes(bool write);
  void globalSketchBytesData();
  void globalNLRelay(bool write);
  void globalLRelay(bool write);
  void globalSetTime(bool write);
  void globalPortPresets(bool write);
  void globalGetFasState();
  void globalEditorFeedback(bool write);
  void globalEditorMetrics();
  void globalEditorMessenger(bool write);
  void globalEditorPerformMode(bool write);
  void globalSetList(bool write);
  void globalSetListSong(bool write);
  void globalSetListSongPartShiftPosition(bool write);

// BMC-Editor.midi.page.h
private:
  void pageProcessMessage();
  void pageMessage(bool write);
  void pageNameMessage(bool write);
  void pageButtonMessage(bool write);
  void pageLedMessage(bool write);
  void pagePwmLedMessage(bool write);
  void pagePixelMessage(bool write);
  void pageRgbPixelMessage(bool write);
  void pagePotMessage(bool write);
  void pageEncoderMessage(bool write);
  void pageOledDisplay(bool write);
  void pageIliDisplay(bool write);
  void pageHardwareCopySwapMessage(bool write);
  void pageButtonEventShiftPositionMessage(bool write);
  void globalButtonEventShiftPositionMessage(bool write);

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
#if BMC_MAX_BUTTONS > 32
  void utilitySendButtonActivity(uint32_t states=0,
                                 uint32_t states2=0,
                                 bool onlyIfConnected=true);
#else
  void utilitySendButtonActivity(uint32_t states=0,
                               bool onlyIfConnected=true);
#endif

  void utilitySendLedActivity(uint32_t data,
                              bool onlyIfConnected=true);
  //
  void utilitySendAuxJackActivity(uint8_t data,
                              bool onlyIfConnected=true);
  //
  void utilitySendFasState(uint8_t data,
                              bool onlyIfConnected=true);
  //
  void utilitySendNLRelayActivity(uint16_t data,
                              bool onlyIfConnected=true);
  void utilitySendLRelayActivity(uint16_t data,
                              bool onlyIfConnected=true);

  void utilitySendPwmLedActivity(uint32_t data,
                              bool onlyIfConnected=true);

  void utilitySendPotActivity(uint8_t index, uint8_t value=0,
                              bool onlyIfConnected=true);

  void utilitySendPotsActivity(uint8_t *values, uint8_t length,
                               bool onlyIfConnected=true);

  void utilitySendEncoderActivity(uint8_t index, bool increased,
                                  bool onlyIfConnected=true);

  void utilitySendGlobalLedActivity(uint16_t data,
                                    bool onlyIfConnected=true);
  void utilitySendPixelActivity(uint32_t data,
                                    bool onlyIfConnected=true);
  void utilitySendRgbPixelActivity(uint32_t red, uint32_t green, uint32_t blue,
                                    bool onlyIfConnected=true);
  void utilitySendPreset(bmcPreset_t presetNumber,
                        bool onlyIfConnected=true);

  void utilitySendClickTrackData(uint16_t freq, uint8_t level,
                                 uint8_t state, bool onlyIfConnected=true);

  void utilitySendPotCalibrationStatus(bool status, bool canceled=false,
                                       bool onlyIfConnected=true);

  void utilitySendSketchBytes(bool onlyIfConnected);


  void utilitySendGlobalButtonActivity(uint32_t states=0,
                                 bool onlyIfConnected=true);

  void utilitySendGlobalPotActivity(uint8_t index, uint8_t value=0,
                              bool onlyIfConnected=true);

  void utilitySendGlobalPotsActivity(uint8_t *values, uint8_t length,
                               bool onlyIfConnected=true);

  void utilitySendGlobalEncoderActivity(uint8_t index, bool increased,
                                  bool onlyIfConnected=true);

  void utilitySendGlobalPotCalibrationStatus(bool status, bool canceled=false,
                                  bool onlyIfConnected=true);
private:

  // GLOBAL
  void backupGlobalSettings(uint16_t t_minLength);
  void backupGlobalStringLibrary(uint16_t t_minLength);
  void backupGlobalLibrary(uint16_t t_minLength);
  void backupGlobalPreset(uint16_t t_minLength);
  void backupGlobalSetList(uint16_t t_minLength);
  void backupGlobalSetListSong(uint16_t t_minLength);
  void backupGlobalStartup(uint16_t t_minLength);
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
