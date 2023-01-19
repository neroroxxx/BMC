/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include "editor/BMC-Editor.h"

void BMCEditor::backupGlobalSettings(uint16_t t_minLength){
  // backup message is the same as the save message
  if(incoming.size() == t_minLength){
    // the editor will always update the device id of the backup to match
    // the one currently connected but just incase we hold a copy of it
    // and set it as the device id to prevent any issues
    uint8_t tmpDeviceId = deviceId;
    bmcStoreGlobalSettings& item = store.global.settings;
    item.flags = incoming.get32Bits(9);
    uint8_t e = 14;
    for(uint8_t i = 0 ; i < 8 ; i++){
      item.data[i] = incoming.get32Bits(e);
      e += 5;
    }
    for(uint8_t i = 0; i < 7 ; i++){
      item.routing[i] = incoming.get16Bits(e);
      e += 3;
    }
    // set the device id to back to whatever it was before receiving this backup
    // this will make sure that we any messages we will receive from here on
    // are accepted, we do this even if the device id wasn't changed.
    deviceId = tmpDeviceId;
    settings.setDeviceId(deviceId);
  }
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
}
/*
void BMCEditor::backupGlobalStartup(uint16_t t_minLength){
#if BMC_MAX_PRESETS > 0
  // this message doesn't require any additional bytes
  // from the standard read/write messages
  if(incoming.size() >= t_minLength){
    //uint8_t index = BMC_MIDI_ARRAY_TO_8BITS(9,incoming.sysex);
    uint16_t index = incoming.get14Bits(9);
    if(index >= BMC_MAX_PRESETS){
      index = 0;
    }
    store.global.startup = index;
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
*/
// BMC 2.0
void BMCEditor::backupEventMessage(uint16_t t_minLength){
  uint16_t index = getMessageLayerNumber();
  if(index >= BMC_MAX_EVENTS_LIBRARY){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  if(incoming.size() == t_minLength){
    bmcStoreEvent& item = store.global.events[index];
    item.name     = incoming.get14Bits(9);
    item.settings = incoming.get8Bits(11);
    item.type     = incoming.get8Bits(13);
    item.ports    = incoming.get8Bits(15);
    item.event    = incoming.get32Bits(17);
  }
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupNameMessage(uint16_t t_minLength){
  uint16_t index = getMessageLayerNumber();
  if(index >= BMC_MAX_NAMES_LIBRARY){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  if(incoming.size() >= t_minLength){
    uint8_t nameLength = incoming.sysex[9];
    if(incoming.size() == (nameLength + t_minLength)){
      bmcStoreName& item = store.global.names[index];
      // set all the name characters all to 0
      memset(item.name, 0, BMC_MAX_NAMES_LENGTH);
      // if the length we received is higher than the compiled length,
      // set it to the compiled length
      if(nameLength > BMC_MAX_NAMES_LENGTH){
        nameLength = BMC_MAX_NAMES_LENGTH;
      }
      incoming.getStringFromSysEx(10, item.name, nameLength);
    }
  }
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}

void BMCEditor::backupGlobalLibrary(uint16_t t_minLength){

}
void BMCEditor::backupGlobalPreset(uint16_t t_minLength){

}
void BMCEditor::backupGlobalSetList(uint16_t t_minLength){
  
}
void BMCEditor::backupGlobalSetListSong(uint16_t t_minLength){
  
}
void BMCEditor::backupGlobalCustomSysEx(uint16_t t_minLength){
  
}
void BMCEditor::backupGlobalTempoToTap(uint16_t t_minLength){
  
}
void BMCEditor::backupGlobalSketchBytes(uint16_t t_minLength){
  
}
void BMCEditor::backupGlobalPortPresets(uint16_t t_minLength){
  
}
void BMCEditor::backupPixelProgram(uint16_t t_minLength){

}
void BMCEditor::backupGlobalTriggers(uint16_t t_minLength){

}
void BMCEditor::backupGlobalTimedEvents(uint16_t t_minLength){

}
void BMCEditor::backupGlobalLed(uint16_t t_minLength){

}

void BMCEditor::backupGlobalNLRelay(uint16_t t_minLength){

}
void BMCEditor::backupGlobalLRelay(uint16_t t_minLength){

}

void BMCEditor::backupLayerName(uint16_t t_minLength){

}
// LAYER DATA
void BMCEditor::backupLayerButton(uint16_t t_minLength){

}
void BMCEditor::backupLayerLed(uint16_t t_minLength){

}
void BMCEditor::backupLayerPwmLed(uint16_t t_minLength){

}
void BMCEditor::backupLayerPixel(uint16_t t_minLength){

}
void BMCEditor::backupLayerRgbPixel(uint16_t t_minLength){

}
void BMCEditor::backupLayerEncoder(uint16_t t_minLength){

}
void BMCEditor::backupLayerPot(uint16_t t_minLength){

}
void BMCEditor::backupGlobalButton(uint16_t t_minLength){

}

void BMCEditor::backupGlobalEncoder(uint16_t t_minLength){

}
void BMCEditor::backupGlobalPot(uint16_t t_minLength){

}

void BMCEditor::backupLayerOled(uint16_t t_minLength){

}
void BMCEditor::backupLayerIli(uint16_t t_minLength){

}
