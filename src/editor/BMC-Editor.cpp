/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include "editor/BMC-Editor.h"

BMCEditor::BMCEditor(bmcStore& t_store,
                    BMCMidi& t_midi,
                    BMCSettings& t_settings,
                    BMCMessenger& t_messenger
 ):
  store(t_store),
  midi(t_midi),
  settings(t_settings),
  storage(midi.globals),
  incoming(midi.message),
  messenger(t_messenger)
{
  incoming.reset();
}
void BMCEditor::begin(){
  flags.reset();
  // see getStore() in BMC-Editor.h
  flags.on(BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP);
  BMC_PRINTLN("");
  BMC_PRINTLN("+++++++++++++++++++++++++++++++++++++++++++");
  BMC_PRINTLN("BMCEditor::begin");

  storage.begin();
  #if defined(BMC_USE_TIME)
    setSyncProvider(getTeensy3Time);
    adjustTime(BMC_TIME_ADJUST);
    #if defined(BMC_DEBUG)
      // print the time at launch if debug is enabled
      BMC_PRINT("BMC Enabled Time:");
      BMC_PRINTNS((getHour()<10?"0":""),getHour(),":");
      BMC_PRINTNS((getMinute()<10?"0":""),getMinute(),":");
      BMC_PRINTNS((getSecond()<10?"0":""),getSecond()," ");
      BMC_PRINTNS(getYear(),"-");
      BMC_PRINTNS((getMonth()<10?"0":""),getMonth(),"-");
      BMC_PRINTNS((getDay()<10?"0":""),getDay());
      BMC_PRINTLN("");
    #endif
  #endif
  // Make sure the bmcStore size is not larger than the EEPROM size
  if(sizeof(bmcStore) > storage.length()){
    BMC_ERROR(
      "The size of bmcStore has exceeded the size of EEPROM",
      "Reupload your sketch with a different config",
      storage.length()
    );
    BMC_HALT();
  }
  // CHECK THE STORE ADDRESS
  // The store address is always stored on the first store (0)
  // when BMC first launches it will always load the first store
  // get the store address from it, then it will load whatever store
  // is selected.
  BMC_PRINTLN("****************************************");
  BMC_PRINTLN("Editor Loading store at setup");

#if defined(BMC_DEBUG)
  unsigned long storeLoadTime = millis();
#endif

#if defined(BMC_SD_CARD_ENABLED)
  setStoreAddress(storage.getFileId());
#else
  setStoreAddress(settings.getStoreAddress());
  if(storeAddress!=0){
    getStore();
  }
#endif

  // get the store
  getStore();

  BMC_PRINTLN("Editor Initial store load took",(millis()-storeLoadTime),"ms");
  BMC_PRINTLN("****************************************");

  deviceId = settings.getDeviceId();

  #if BMC_MAX_TRIGGERS > 0
    flags.on(BMC_EDITOR_FLAG_EDITOR_TRIGGERS_UPDATED);
  #endif
  #if BMC_MAX_TIMED_EVENTS > 0
    flags.on(BMC_EDITOR_FLAG_EDITOR_TIMED_EVENTS_UPDATED);
  #endif

  BMC_PRINTLNNS("BMC Library Version \"",BMC_VERSION_MAJ,".",BMC_VERSION_MIN,".",BMC_VERSION_PATCH,"\"");
  BMC_PRINTLNNS("Library Version stored in EEPROM \"",BMC_GET_BYTE(1,store.version),".",BMC_GET_BYTE(0,store.version),"\"");
  BMC_PRINTLN("deviceId =", deviceId);
  BMC_PRINTLN("storeAddress =", storeAddress);
  BMC_PRINTLN("+++++++++++++++++++++++++++++++++++++++++++");
  BMC_PRINTLN("");

  flags.off(BMC_EDITOR_FLAG_EDITOR_INITIAL_SETUP);
}
void BMCEditor::update(){

}
bool BMCEditor::readyToReload(){
  return flags.toggleIfTrue(BMC_EDITOR_FLAG_READY_TO_RELOAD);
}
bool BMCEditor::dataForBMCAvailable(){
  return flags.toggleIfTrue(BMC_EDITOR_FLAG_DATA_FOR_BMC_AVAILABLE);
}
bool BMCEditor::connected(){
  return midi.globals.editorConnected();
}
bool BMCEditor::connectionHasChanged(){
  return flags.toggleIfTrue(BMC_EDITOR_FLAG_CONNECTION_HAS_CHANGED);
}
void BMCEditor::setPort(uint8_t port){
  bitWrite(this->port,port,1);
}
void BMCEditor::setPage(uint8_t page){
  if(page < BMC_MAX_PAGES){
    this->page = page;
  }
}
uint8_t BMCEditor::getPage(){
  return page;
}


// EEPROM offset
uint8_t BMCEditor::getCrcAndVersionSize(){
  return sizeof(store.crc) + sizeof(store.version);
}
uint32_t BMCEditor::getStoreOffset(){
  return (storeAddress * sizeof(store));
}
uint32_t BMCEditor::getGlobalOffset(){
  return (storeAddress * sizeof(store)) + getCrcAndVersionSize();
}
uint32_t BMCEditor::getSettingsOffset(){
  return sizeof(store.global.settings);
}





uint32_t BMCEditor::getEventsOffset(){
  uint32_t value = getSettingsOffset();
  return value + sizeof(store.global.events);
}
uint32_t BMCEditor::getEventsOffset(uint16_t index){
  uint32_t value = getSettingsOffset();
  return value + (sizeof(bmcStoreEvent)*index);
}

uint32_t BMCEditor::getNamesOffset(){
  uint32_t value = getEventsOffset();
  return value + sizeof(store.global.names);
}
uint32_t BMCEditor::getNamesOffset(uint16_t index){
  uint32_t value = getEventsOffset();
  return value + (sizeof(bmcStoreName)*index);
}


uint32_t BMCEditor::getSketchBytesOffset(){
  uint32_t value = getNamesOffset();
  #if BMC_MAX_SKETCH_BYTES > 0
    value += sizeof(store.global.sketchBytes);
  #endif
  return value;
}

uint32_t BMCEditor::getStringLibraryOffset(){
  uint32_t value = getSketchBytesOffset();
#if BMC_MAX_STRING_LIBRARY > 0
  value += sizeof(store.global.stringLibrary);
#endif
  return value;
}
uint32_t BMCEditor::getStringLibraryOffset(uint8_t index){
  uint32_t value = getSketchBytesOffset();
#if BMC_MAX_STRING_LIBRARY > 0
  value += (sizeof(bmcStoreGlobalStringLibrary)*index);
#endif
  return value;
}

uint32_t BMCEditor::getLibraryOffset(){
  uint32_t value = getStringLibraryOffset();
#if BMC_MAX_LIBRARY > 0
  value += sizeof(store.global.library);
#endif
  return value;
}
uint32_t BMCEditor::getLibraryOffset(bmcLibrary_t index){
  uint32_t value = getStringLibraryOffset();
#if BMC_MAX_LIBRARY > 0
  value += (sizeof(bmcStoreGlobalLibrary)*index);
#endif
  return value;
}
uint32_t BMCEditor::getPresetOffset(){
  uint32_t value = getLibraryOffset();
#if BMC_MAX_PRESETS > 0
  value += sizeof(bmcPreset_t);
  value += sizeof(store.global.presets);
#endif
  return value;
}
uint32_t BMCEditor::getPresetOffset(bmcPreset_t index){
  uint32_t value = getLibraryOffset();
#if BMC_MAX_PRESETS > 0
  value += sizeof(bmcPreset_t);
  value += (sizeof(bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS>)*index);
#endif
  return value;
}

uint32_t BMCEditor::getSetListOffset(){
  uint32_t value = getPresetOffset();
#if BMC_MAX_SETLISTS > 0
  value += sizeof(store.global.setLists);
#endif
  return value;
}
uint32_t BMCEditor::getSetListOffset(uint8_t index){
  uint32_t value = getPresetOffset();
#if BMC_MAX_SETLISTS > 0
  value += (sizeof(bmcStoreGlobalSetList)*index);
#endif
  return value;
}

uint32_t BMCEditor::getSetListSongOffset(){
  uint32_t value = getSetListOffset();
#if BMC_MAX_SETLISTS > 0
  value += sizeof(store.global.songLibrary);
#endif
  return value;
}
uint32_t BMCEditor::getSetListSongOffset(uint8_t index){
  uint32_t value = getSetListOffset();
#if BMC_MAX_SETLISTS > 0
  value += (sizeof(bmcStoreGlobalSetListSong)*index);
#endif
  return value;
}



uint32_t BMCEditor::getGlobalButtonOffset(){
  uint32_t value = getSetListSongOffset();
  #if BMC_MAX_GLOBAL_BUTTONS > 0
    value += sizeof(store.global.buttons);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalButtonOffset(uint8_t index){
  uint32_t value = getSetListSongOffset();
  #if BMC_MAX_GLOBAL_BUTTONS > 0
    //value += ((sizeof(bmcStoreDevice)+(BMC_MAX_BUTTON_EVENTS*4)) * index);
    value += (sizeof(bmcStoreDevice <BMC_MAX_BUTTON_EVENTS,BMC_MAX_BUTTON_EVENTS>) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalLedOffset(){
  uint32_t value = getGlobalButtonOffset();
  #if BMC_MAX_GLOBAL_LEDS > 0
    value += sizeof(store.global.leds);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalLedOffset(uint8_t index){
  uint32_t value = getGlobalButtonOffset();
  #if BMC_MAX_GLOBAL_LEDS > 0
    value += (sizeof(bmcStoreDevice<1,1>) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalEncoderOffset(){
  uint32_t value = getGlobalButtonOffset();
  #if BMC_MAX_GLOBAL_ENCODERS > 0
    value += sizeof(store.global.encoders);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalEncoderOffset(uint8_t index){
  uint32_t value = getGlobalButtonOffset();
  #if BMC_MAX_GLOBAL_ENCODERS > 0
    value += (sizeof(bmcStoreEncoder) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalPotOffset(){
  uint32_t value = getGlobalEncoderOffset();
  #if BMC_MAX_GLOBAL_POTS > 0
    value += sizeof(store.global.pots);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalPotOffset(uint8_t index){
  uint32_t value = getGlobalEncoderOffset();
  #if BMC_MAX_GLOBAL_POTS > 0
    //value += (sizeof(bmcStorePot) * index);
    value += (sizeof(bmcStoreDevice<1,2>) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalPotCalibrationOffset(){
  uint32_t value = getGlobalPotOffset();
  #if BMC_MAX_GLOBAL_POTS > 0
    value += sizeof(store.global.globalPotCalibration);
  #endif
  return value;
}
uint32_t BMCEditor::getGlobalPotCalibrationOffset(uint8_t index){
  uint32_t value = getGlobalPotOffset();
  #if BMC_MAX_GLOBAL_POTS > 0
    value += (sizeof(bmcStoreGlobalPotCalibration) * index);
  #endif
  return value;
}

uint32_t BMCEditor::getPotCalibrationOffset(){
  uint32_t value = getGlobalPotCalibrationOffset();
  #if BMC_MAX_POTS > 0
    value += sizeof(store.global.potCalibration);
  #endif
  return value;
}
uint32_t BMCEditor::getPotCalibrationOffset(uint8_t index){
  uint32_t value = getGlobalPotCalibrationOffset();
  #if BMC_MAX_POTS > 0
    value += (sizeof(bmcStoreGlobalPotCalibration) * index);
  #endif
  return value;
}




uint32_t BMCEditor::getNLRelayOffset(){
  uint32_t value = getPotCalibrationOffset();
  #if BMC_MAX_NL_RELAYS > 0
    value += sizeof(store.global.relaysNL);
  #endif
  return value;
}
uint32_t BMCEditor::getNLRelayOffset(uint8_t index){
  uint32_t value = getPotCalibrationOffset();
  #if BMC_MAX_NL_RELAYS > 0
    value += (sizeof(bmcStoreDevice <1, 1>) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getLRelayOffset(){
  uint32_t value = getNLRelayOffset();
  #if BMC_MAX_L_RELAYS > 0
    value += sizeof(store.global.relaysL);
  #endif
  return value;
}
uint32_t BMCEditor::getLRelayOffset(uint8_t index){
  uint32_t value = getNLRelayOffset();
  #if BMC_MAX_L_RELAYS > 0
    value += (sizeof(bmcStoreDevice <1, 1>) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getCustomSysExOffset(){
  uint32_t value = getLRelayOffset();
  #if BMC_MAX_CUSTOM_SYSEX > 0
    value += sizeof(store.global.customSysEx);
  #endif
  return value;
}
uint32_t BMCEditor::getCustomSysExOffset(uint8_t index){
  uint32_t value = getLRelayOffset();
  #if BMC_MAX_CUSTOM_SYSEX > 0
    value += (sizeof(bmcStoreGlobalCustomSysEx) * index);
  #endif
  return value;
}

uint32_t BMCEditor::getTriggerOffset(){
  uint32_t value = getCustomSysExOffset();
  #if BMC_MAX_TRIGGERS > 0
    value += sizeof(store.global.triggers);
  #endif
  return value;
}
uint32_t BMCEditor::getTriggerOffset(uint8_t index){
  uint32_t value = getCustomSysExOffset();
  #if BMC_MAX_TRIGGERS > 0
    value += (sizeof(bmcStoreGlobalTriggers) * index);
  #endif
  return value;
}

uint32_t BMCEditor::getTempoToTapOffset(){
  uint32_t value = getTriggerOffset();
  #if BMC_MAX_TEMPO_TO_TAP > 0
    value += sizeof(store.global.tempoToTap);
  #endif
  return value;
}
uint32_t BMCEditor::getTempoToTapOffset(uint8_t index){
  uint32_t value = getTriggerOffset();
  #if BMC_MAX_TEMPO_TO_TAP > 0
    value += (sizeof(bmcStoreGlobalTempoToTap) * index);
  #endif
  return value;
}



uint32_t BMCEditor::getPortPresetsOffset(){
  return getLRelayOffset();
}
uint32_t BMCEditor::getPixelProgramsOffset(){
  uint32_t value = getPortPresetsOffset();
  value += sizeof(store.global.portPresets);
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    value += sizeof(store.global.pixelPrograms);
  #endif
  return value;
}
uint32_t BMCEditor::getPixelProgramsOffset(uint8_t index){
  uint32_t value = getPortPresetsOffset();
  value += sizeof(store.global.portPresets);
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    value += (sizeof(bmcStorePixelPrograms) * index);
  #endif
  return value;
}
uint32_t BMCEditor::getTimedEventOffset(){
  uint32_t value = getPixelProgramsOffset();
  #if BMC_MAX_TIMED_EVENTS > 0
    value += sizeof(store.global.timedEvents);
  #endif
  return value;
}
uint32_t BMCEditor::getTimedEventOffset(uint8_t index){
  uint32_t value = getPixelProgramsOffset();
  #if BMC_MAX_TIMED_EVENTS > 0
    value += (sizeof(bmcStoreGlobalTimedEvents) * index);
  #endif
  return value;
}
