/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_CUSTOM_SYSEX_H
#define BMC_CUSTOM_SYSEX_H
#if BMC_MAX_CUSTOM_SYSEX > 0

#include "utility/BMC-Def.h"

class BMCCustomSysEx {
public:
  BMCCustomSysEx(BMCMidi& t_midi, bmcStoreGlobal& t_global):
                midi(t_midi),
                global(t_global)
  {

  }
  void send(uint8_t mode, uint8_t ports, uint8_t indexA, uint8_t indexB=255){

    switch(mode & 0x03){
      case BMC_CUSTOM_SYSEX_SEND_A:
        send(ports, indexA);
        break;
      case BMC_CUSTOM_SYSEX_SEND_B:
        send(ports, indexA);
        send(ports, indexB);
        break;
      case BMC_CUSTOM_SYSEX_SEND_MERGE:
        sendMerged(ports, indexA, indexB);
        break;
    }
  }
  void send(uint8_t port, uint8_t index){
    if(index < BMC_MAX_CUSTOM_SYSEX){
      //bmcStoreGlobalCustomSysEx& a = global.customSysEx[index];
      bmcStoreDevice <1, 16, uint8_t>& device = global.customSysEx[index];
      if(device.settings[0] != 0){
        midi.sendSysEx(port, device.events, device.settings[0]);
      }
    }
  }
  void sendMerged(uint8_t port, uint8_t indexA, uint8_t indexB){
    if(port != 0 && indexA < BMC_MAX_CUSTOM_SYSEX && indexB < BMC_MAX_CUSTOM_SYSEX){
      //bmcStoreGlobalCustomSysEx& a = global.customSysEx[indexA];
      //bmcStoreGlobalCustomSysEx& b = global.customSysEx[indexB];
      bmcStoreDevice <1, 16, uint8_t>& deviceA = global.customSysEx[indexA];
      bmcStoreDevice <1, 16, uint8_t>& deviceB = global.customSysEx[indexB];
      uint8_t length = deviceA.settings[0] + deviceB.settings[0];
      if(length==0){
        return;
      }
      uint8_t bytes[length];
      memset(bytes, 0, length);
      for(uint8_t i=0;i<deviceA.settings[0];i++){
        bytes[i] = deviceA.events[i] & 0x7F;
      }
      for(uint8_t i=deviceA.settings[0],e=0;e<deviceB.settings[0];i++,e++){
        bytes[i] = deviceB.events[e] & 0x7F;
      }
      midi.sendSysEx(port, bytes, length);
    }
  }
private:
  // reference to midi object from BMC
  BMCMidi& midi;
  bmcStoreGlobal& global;
};

#endif
#endif
