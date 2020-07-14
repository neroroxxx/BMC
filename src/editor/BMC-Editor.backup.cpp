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

void BMCEditor::backupGlobalStringLibrary(uint16_t t_minLength){
#if BMC_MAX_STRING_LIBRARY > 0
  uint16_t index = getMessagePageNumber();
  if(index >= BMC_MAX_STRING_LIBRARY){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength + t_minLength + 1)){
      bmcStoreGlobalStringLibrary& item = store.global.stringLibrary[index];
      // set all the name characters all to 0
      memset(item.name, 0, BMC_NAME_LEN_STRING_LIBRARY);
      // if the length we received is higher than the compiled length,
      // set it to the compiled length
      if(nameLength > BMC_NAME_LEN_STRING_LIBRARY){
        nameLength = BMC_NAME_LEN_STRING_LIBRARY;
      }
      incoming.getStringFromSysEx(9, item.name, nameLength);
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}

void BMCEditor::backupGlobalLibrary(uint16_t t_minLength){
#if BMC_MAX_LIBRARY > 0
  uint16_t index = getMessagePageNumber();
  if(index >= BMC_MAX_LIBRARY){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength + t_minLength + 1)){
      bmcStoreGlobalLibrary& item = store.global.library[index];
      //item.event = BMC_MIDI_ARRAY_TO_32BITS(9,incoming.sysex);
      item.event = incoming.get32Bits(9);
      #if BMC_NAME_LEN_LIBRARY > 1
        // set all the name characters all to 0
        memset(item.name, 0, BMC_NAME_LEN_LIBRARY);
        // if the length we received is higher than the compiled length,
        // set it to the compiled length
        if(nameLength > BMC_NAME_LEN_LIBRARY){
          nameLength = BMC_NAME_LEN_LIBRARY;
        }
        incoming.getStringFromSysEx(14, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalPreset(uint16_t t_minLength){
#if BMC_MAX_PRESETS > 0
  uint16_t index = getMessagePageNumber();
  if(index >= BMC_MAX_PRESETS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  // and the number of preset items as the byte before the name length
  if(incoming.size() >= (t_minLength+2)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    uint8_t itemsLength = incoming.sysex[incoming.size()-4];

    // check that incoming message length matches the required length
    if(incoming.size()==(nameLength+(itemsLength*2)+t_minLength+2)){

      bmcStoreGlobalPresets& item = store.global.presets[index];
      // add the number of preset items that will be used
      // make sure it's not higher than the number of preset items compiled
      item.length = incoming.sysex[9];
      if(item.length > BMC_MAX_PRESET_ITEMS){
        item.length = BMC_MAX_PRESET_ITEMS;
      }
      // set all bytes in the event array to 0
      memset(item.events, 0, BMC_MAX_PRESET_ITEMS);
      // e is the offset where we start in the sysex array
      // it will be used to keep track of where we are and for the
      // name if it's compiled
      uint8_t e = 10;
      for(uint8_t i = 0; i < itemsLength ; i++){
        // only add the item if it's within the limir compiled
        if(i < BMC_MAX_PRESET_ITEMS){
          //item.events[i] = BMC_MIDI_ARRAY_TO_8BITS(e,incoming.sysex);
          item.events[i] = incoming.get8Bits(e);
          // if the library item is higher than the compiled we set it
          // to 0 and we lower the length of items that are part of the preset
          if(item.events[i] >= BMC_MAX_LIBRARY){
            item.events[i] = 0;
            if(item.length>0){
              item.length--;
            }
          }
        }
        e+=2;
      }
      #if BMC_NAME_LEN_PRESETS > 1
        // if the name length is higher than the compiled we set it to the max
        if(nameLength > BMC_NAME_LEN_PRESETS){
          nameLength = BMC_NAME_LEN_PRESETS;
        }
        incoming.getStringFromSysEx(e,item.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalStartup(uint16_t t_minLength){
#if BMC_MAX_PRESETS > 0
  // this message doesn't require any additional bytes
  // from the standard read/write messages
  if(incoming.size() >= t_minLength){
    //uint8_t index = BMC_MIDI_ARRAY_TO_8BITS(9,incoming.sysex);
    uint8_t index = incoming.get8Bits(9);
    if(index >= BMC_MAX_PRESETS){
      index = 0;
    }
    store.global.startup = index;
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalSetList(uint16_t t_minLength){
#if BMC_MAX_SETLISTS > 0
  uint16_t index = getMessagePageNumber();
  if(index >= BMC_MAX_SETLISTS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  // and the number of preset items as the byte before the name length
  if(incoming.size() >= (t_minLength+2)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    uint8_t itemsLength = incoming.sysex[incoming.size()-4];

    // check that incoming message length matches the required length
    if(incoming.size()==(nameLength+(itemsLength*2)+t_minLength+2)){

      bmcStoreGlobalSetList& item = store.global.setLists[index];
      // add the number of preset items that will be used
      // make sure it's not higher than the number of preset items compiled
      item.length = incoming.sysex[9];
      if(item.length > BMC_MAX_SETLISTS_SONGS){
        item.length = BMC_MAX_SETLISTS_SONGS;
      }
      // set all bytes in the event array to 0
      memset(item.songs, 0, BMC_MAX_SETLISTS_SONGS);
      // e is the offset where we start in the sysex array
      // it will be used to keep track of where we are and for the
      // name if it's compiled
      uint8_t e = 10;
      for(uint8_t i = 0; i < itemsLength ; i++){
        // only add the item if it's within the limir compiled
        if(i < BMC_MAX_SETLISTS_SONGS){
          //item.songs[i] = BMC_MIDI_ARRAY_TO_8BITS(e,incoming.sysex);
          item.songs[i] = incoming.get8Bits(e);
          // if the library item is higher than the compiled we set it
          // to 0 and we lower the length of items that are part of the preset
          if(item.songs[i] >= BMC_MAX_PRESETS){
            item.songs[i] = 0;
            if(item.length>0){
              item.length--;
            }
          }
        }
        e+=2;
      }
      #if BMC_NAME_LEN_SETLISTS > 1
        // if the name length is higher than the compiled we set it to the max
        if(nameLength > BMC_NAME_LEN_SETLISTS){
          nameLength = BMC_NAME_LEN_SETLISTS;
        }
        incoming.getStringFromSysEx(e,item.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalCustomSysEx(uint16_t t_minLength){
#if BMC_MAX_CUSTOM_SYSEX > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_CUSTOM_SYSEX){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // does NOT require additional bytes from write message
  // custom sysex can have a max number of 16 bytes
  if(incoming.size() == t_minLength){
    bmcStoreGlobalCustomSysEx& item = store.global.customSysEx[index];
    //item.length = incoming.sysex[9] & 0x7F;
    item.length = incoming.get7Bits(9);
    for(uint8_t i=10,e=0,n=10+16;i<n;i++,e++){
      //item.event[e] = incoming.sysex[i] & 0x7F;
      item.event[e] = incoming.get7Bits(i);
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalTempoToTap(uint16_t t_minLength){
#if BMC_MAX_TEMPO_TO_TAP > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_TEMPO_TO_TAP){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // does NOT require additional bytes from write message
  if(incoming.size() == t_minLength){
    store.global.tempoToTap[index].event = incoming.get32Bits(9);
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalSketchBytes(uint16_t t_minLength){
#if BMC_MAX_SKETCH_BYTES > 0
  // backup must include length of sketch bytes as the byte before the CRC
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t length = incoming.sysex[incoming.size()-3];
    // if the backup contains more than the number of bytes compiled
    // we use the number of bytes compiled for the length
    if(length>BMC_MAX_SKETCH_BYTES){
      length = BMC_MAX_SKETCH_BYTES;
    }
    for(uint8_t i = 0, e = 9 ; i < length ; i++, e += 2){
      // this is kinda redundant since we're limiting the length
      // to be the same as BMC_MAX_SKETCH_BYTES but JUST IN CASE...
      if(i >= BMC_MAX_SKETCH_BYTES){
        break;
      }
      store.global.sketchBytes[i] = incoming.get8Bits(e);
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalPortPresets(uint16_t t_minLength){
  // no additional bytes
  if(incoming.size() == t_minLength){
    for(uint8_t i = 0, e = 9 ; i < 16 ; i++, e++){
      store.global.portPresets.preset[i] = incoming.get7Bits(e);
    }
  }
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalTriggers(uint16_t t_minLength){
#if BMC_MAX_TRIGGERS > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_TRIGGERS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // does NOT require additional bytes from write message
  if(incoming.size() == t_minLength){
    bmcStoreGlobalTriggers& item = store.global.triggers[index];
    item.event = incoming.get32Bits(9);
    item.source = incoming.get32Bits(14);
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalLed(uint16_t t_minLength){
#if BMC_MAX_GLOBAL_LEDS > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_GLOBAL_LEDS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  // even if it's 0
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength+t_minLength+1)){
      bmcStoreLed& item = store.global.leds[index];
      //item.event = BMC_MIDI_ARRAY_TO_32BITS(9,incoming.sysex);
      item.event = incoming.get32Bits(9);
      #if BMC_NAME_LEN_LEDS > 1
        // set all the name characters all to 0
        memset(item.name, 0, BMC_NAME_LEN_LEDS);
        // if the length we received is higher than the compiled length,
        // set it to the compiled length
        if(nameLength > BMC_NAME_LEN_LEDS){
          nameLength = BMC_NAME_LEN_LEDS;
        }
        incoming.getStringFromSysEx(14, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}

void BMCEditor::backupGlobalNLRelay(uint16_t t_minLength){
#if BMC_MAX_NL_RELAYS > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_NL_RELAYS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  // even if it's 0
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength+t_minLength+1)){
      bmcStoreGlobalRelay& item = store.global.relaysNL[index];
      item.event = incoming.get32Bits(9);
      #if BMC_NAME_LEN_RELAYS > 1
        // set all the name characters all to 0
        memset(item.name, 0, BMC_NAME_LEN_RELAYS);
        // if the length we received is higher than the compiled length,
        // set it to the compiled length
        if(nameLength > BMC_NAME_LEN_RELAYS){
          nameLength = BMC_NAME_LEN_RELAYS;
        }
        incoming.getStringFromSysEx(14, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalLRelay(uint16_t t_minLength){
#if BMC_MAX_L_RELAYS > 0
  uint8_t index = getMessagePageNumber();
  if(index >= BMC_MAX_L_RELAYS){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  // backup must include length of the name as the byte before the CRC
  // even if it's 0
  if(incoming.size() >= (t_minLength+1)){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength+t_minLength+1)){
      bmcStoreGlobalRelay& item = store.global.relaysL[index];
      item.event = incoming.get32Bits(9);
      #if BMC_NAME_LEN_RELAYS > 1
        // set all the name characters all to 0
        memset(item.name, 0, BMC_NAME_LEN_RELAYS);
        // if the length we received is higher than the compiled length,
        // set it to the compiled length
        if(nameLength > BMC_NAME_LEN_RELAYS){
          nameLength = BMC_NAME_LEN_RELAYS;
        }
        incoming.getStringFromSysEx(14, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}

void BMCEditor::backupPageName(uint16_t t_minLength){
#if BMC_NAME_LEN_PAGES > 1
  uint16_t index = getMessagePageNumber();
  if(index >= BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, 0);
    return;
  }
  if(incoming.size() >= t_minLength){
    // get the name length byte
    uint8_t nameLength = incoming.sysex[9];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size() == (nameLength + t_minLength)){
      // set all the name characters all to 0
      memset(store.pages[index].name, 0, BMC_NAME_LEN_PAGES);
      // if the length we received is higher than the compiled length,
      // set it to the compiled length
      if(nameLength > BMC_NAME_LEN_PAGES){
        nameLength = BMC_NAME_LEN_PAGES;
      }
      incoming.getStringFromSysEx(10, store.pages[index].name, nameLength);
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
// PAGE DATA
void BMCEditor::backupPageButton(uint16_t t_minLength){
#if BMC_MAX_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t page = getMessagePageNumber();
      uint8_t buttonIndex = incoming.get7Bits(9);
      uint8_t eventIndex = incoming.get7Bits(10);
      //uint8_t buttonIndex = incoming.sysex[9];
      //uint8_t eventIndex = incoming.sysex[10];
      bmcStoreButton& button = store.pages[page].buttons[buttonIndex];
      bmcStoreButtonEvent& event = button.events[eventIndex];
      event.mode = incoming.get8Bits(11);//+2
      event.ports = incoming.get8Bits(13);//+2
      event.event = incoming.get32Bits(15);//+5
      #if BMC_NAME_LEN_BUTTONS > 1
        if(nameLength > BMC_NAME_LEN_BUTTONS){
          nameLength = BMC_NAME_LEN_BUTTONS;
        }
        memset(button.name,0,BMC_NAME_LEN_BUTTONS);
        incoming.getStringFromSysEx(20,button.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPageLed(uint16_t t_minLength){
#if BMC_MAX_LEDS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t page = getMessagePageNumber() & 0xFF;
      uint8_t index = incoming.sysex[9];
      bmcStoreLed &item = store.pages[page].leds[index];
      //item.event = BMC_MIDI_ARRAY_TO_32BITS(10,incoming.sysex);
      item.event = incoming.get32Bits(10);
      #if BMC_NAME_LEN_LEDS > 1
        if(nameLength > BMC_NAME_LEN_LEDS){
          nameLength = BMC_NAME_LEN_LEDS;
        }
        incoming.getStringFromSysEx(15,item.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPagePwmLed(uint16_t t_minLength){
#if BMC_MAX_PWM_LEDS > 0

  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t page = getMessagePageNumber() & 0xFF;
      uint8_t index = incoming.sysex[9];
      bmcStoreLed &item = store.pages[page].pwmLeds[index];
      //item.event = BMC_MIDI_ARRAY_TO_32BITS(10, incoming.sysex);
      item.event = incoming.get32Bits(10);
      #if BMC_NAME_LEN_LEDS > 1
        if(nameLength > BMC_NAME_LEN_LEDS){
          nameLength = BMC_NAME_LEN_LEDS;
        }
        incoming.getStringFromSysEx(15, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPagePixel(uint16_t t_minLength){
  #if BMC_MAX_PIXELS > 0
    // the name length must be appended to the sysex before the CRC
    if(incoming.size() >= (t_minLength+1)){
      uint8_t nameLength = incoming.sysex[incoming.size()-3];
      // check the length of the message, it must match this length
      // for it to be used
      if(incoming.size()==(nameLength+t_minLength+1)){
        uint8_t page = getMessagePageNumber() & 0xFF;
        uint8_t index = incoming.sysex[9];
        bmcStoreLed &item = store.pages[page].pixels[index];
        //item.event = BMC_MIDI_ARRAY_TO_32BITS(10,incoming.sysex);
        item.event = incoming.get32Bits(10);
        #if BMC_NAME_LEN_LEDS > 1
          if(nameLength > BMC_NAME_LEN_LEDS){
            nameLength = BMC_NAME_LEN_LEDS;
          }
          incoming.getStringFromSysEx(15,item.name,nameLength);
        #endif
      }
    }
  #endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPageRgbPixel(uint16_t t_minLength){
  #if BMC_MAX_RGB_PIXELS > 0
    // the name length must be appended to the sysex before the CRC
    if(incoming.size() >= (t_minLength+1)){
      uint8_t nameLength = incoming.sysex[incoming.size()-3];
      // check the length of the message, it must match this length
      // for it to be used
      if(incoming.size()==(nameLength+t_minLength+1)){
        uint8_t page = getMessagePageNumber() & 0xFF;
        uint8_t index = incoming.sysex[9];
        bmcStoreRgbLed &item = store.pages[page].rgbPixels[index];
        //item.event = BMC_MIDI_ARRAY_TO_32BITS(10,incoming.sysex);
        item.red = incoming.get32Bits(10);
        item.green = incoming.get32Bits(15);
        item.blue = incoming.get32Bits(20);
        #if BMC_NAME_LEN_LEDS > 1
          if(nameLength > BMC_NAME_LEN_LEDS){
            nameLength = BMC_NAME_LEN_LEDS;
          }
          incoming.getStringFromSysEx(25,item.name,nameLength);
        #endif
      }
    }
  #endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPageEncoder(uint16_t t_minLength){
#if BMC_MAX_ENCODERS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t page = getMessagePageNumber() & 0xFF;
      uint8_t index = incoming.sysex[9];
      bmcStoreEncoder& item = store.pages[page].encoders[index];
      item.mode = incoming.get8Bits(10);//+2
      item.ports = incoming.get8Bits(12);//+2
      item.event = incoming.get32Bits(14);//+2
      #if BMC_NAME_LEN_ENCODERS > 1
        if(nameLength > BMC_NAME_LEN_ENCODERS){
          nameLength = BMC_NAME_LEN_ENCODERS;
        }
        incoming.getStringFromSysEx(19,item.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupPagePot(uint16_t t_minLength){
#if BMC_MAX_POTS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t page = getMessagePageNumber() & 0xFF;
      uint8_t index = incoming.sysex[9];
      bmcStorePot& item = store.pages[page].pots[index];
      //item.ports = BMC_MIDI_ARRAY_TO_8BITS(10,incoming.sysex);
      //item.event = BMC_MIDI_ARRAY_TO_32BITS(12,incoming.sysex);
      item.ports = incoming.get8Bits(10);
      item.event = incoming.get32Bits(12);
      #if BMC_NAME_LEN_POTS > 1
        if(nameLength > BMC_NAME_LEN_POTS){
          nameLength = BMC_NAME_LEN_POTS;
        }
        incoming.getStringFromSysEx(17, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalButton(uint16_t t_minLength){
#if BMC_MAX_GLOBAL_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t buttonIndex = incoming.get7Bits(9);
      uint8_t eventIndex = incoming.get7Bits(10);
      //uint8_t buttonIndex = incoming.sysex[9];
      //uint8_t eventIndex = incoming.sysex[10];
      bmcStoreButton& button = store.global.buttons[buttonIndex];
      bmcStoreButtonEvent& event = button.events[eventIndex];
      event.mode = incoming.get8Bits(11);//+2
      event.ports = incoming.get8Bits(13);//+2
      event.event = incoming.get32Bits(15);//+5
      #if BMC_NAME_LEN_BUTTONS > 1
        if(nameLength > BMC_NAME_LEN_BUTTONS){
          nameLength = BMC_NAME_LEN_BUTTONS;
        }
        memset(button.name,0,BMC_NAME_LEN_BUTTONS);
        incoming.getStringFromSysEx(20,button.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}

void BMCEditor::backupGlobalEncoder(uint16_t t_minLength){
#if BMC_MAX_GLOBAL_ENCODERS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t index = incoming.sysex[9];
      bmcStoreEncoder& item = store.global.encoders[index];
      item.mode = incoming.get8Bits(10);//+2
      item.ports = incoming.get8Bits(12);//+2
      item.event = incoming.get32Bits(14);//+2
      #if BMC_NAME_LEN_ENCODERS > 1
        if(nameLength > BMC_NAME_LEN_ENCODERS){
          nameLength = BMC_NAME_LEN_ENCODERS;
        }
        incoming.getStringFromSysEx(19,item.name,nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
void BMCEditor::backupGlobalPot(uint16_t t_minLength){
#if BMC_MAX_GLOBAL_POTS > 0
  // the name length must be appended to the sysex before the CRC
  if(incoming.size() >= (t_minLength+1)){
    uint8_t nameLength = incoming.sysex[incoming.size()-3];
    // check the length of the message, it must match this length
    // for it to be used
    if(incoming.size()==(nameLength+t_minLength+1)){
      uint8_t index = incoming.sysex[9];
      bmcStorePot& item = store.global.pots[index];
      item.ports = incoming.get8Bits(10);
      item.event = incoming.get32Bits(12);
      #if BMC_NAME_LEN_POTS > 1
        if(nameLength > BMC_NAME_LEN_POTS){
          nameLength = BMC_NAME_LEN_POTS;
        }
        incoming.getStringFromSysEx(17, item.name, nameLength);
      #endif
    }
  }
#endif
  sendNotification(BMC_NOTIFY_BACKUP_DATA_ACCEPTED, t_minLength);
}
