/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>


#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
void BMC::setupRelays(){
  #if BMC_MAX_NL_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_NL_RELAY, i);
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    bool initialState = bitRead(device.settings[0], 0);
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);

    relaysNL[i].begin(ui.pins[0], momentary, reversed);
    relaysNL[i].command(initialState);
  }
  #endif
  #if BMC_MAX_L_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_L_RELAY, i);
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    bool initialState = bitRead(device.settings[0], 0);
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);
    relaysL[i].begin(ui.pins[0], ui.pins[1], momentary, reversed);
    // bit 0 of event is initial state
    relaysL[i].command(initialState);
  }
  #endif
  assignRelays();
}
void BMC::assignRelays(){
  #if BMC_MAX_NL_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);

    relaysNL[i].setMomentary(momentary);
    relaysNL[i].setReverse(reversed);

    relaysNL[i].reassign();
  }
  #endif
  #if BMC_MAX_L_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);
    relaysL[i].setMomentary(momentary);
    relaysL[i].setReverse(reversed);
    relaysL[i].reassign();
  }
  #endif
}
void BMC::readRelays(){
  #if BMC_MAX_NL_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    if(device.events[0] != 0){
      uint8_t cmd = processEvent(BMC_DEVICE_GROUP_RELAY, BMC_DEVICE_ID_NL_RELAY,
                                 i, BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
      relaysNL[i].command(cmd);
    }
    globals.relayNLStates.setBit(i, relaysNL[i].update());
  }
  if(globals.relayNLStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_NL_RELAY);
  }
  #endif
  #if BMC_MAX_L_RELAYS > 0
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    if(device.events[0] != 0){
      uint8_t cmd = processEvent(BMC_DEVICE_GROUP_RELAY, BMC_DEVICE_ID_L_RELAY,
                                 i, BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
      relaysL[i].command(cmd);
    }
    globals.relayLStates.setBit(i, relaysL[i].update());
  }
  if(globals.relayLStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_L_RELAY);
  }
  #endif
}
void BMC::setRelay(uint8_t index, bool latching, uint8_t cmd){
  if(!latching){
    #if BMC_MAX_NL_RELAYS > 0
      if(index>=BMC_MAX_NL_RELAYS){
        return;
      }
      relaysNL[index].command(cmd);
    #endif
  } else {
    #if BMC_MAX_L_RELAYS > 0
      if(index>=BMC_MAX_L_RELAYS){
        return;
      }
      relaysL[index].command(cmd);
    #endif
  }
}
bool BMC::getRelayState(uint8_t index, bool latching){
  if(!latching){
    #if BMC_MAX_NL_RELAYS > 0
      if(index < BMC_MAX_NL_RELAYS){
        return relaysNL[index].getState();
      }
    #endif
  } else {
    #if BMC_MAX_L_RELAYS > 0
      if(index < BMC_MAX_L_RELAYS){
        return relaysL[index].getState();
      }
    #endif
  }
  return false;
}
#endif



// NON-LATCHING RELAYS
#if BMC_MAX_NL_RELAYS > 0
/*
void BMC::setupRelaysNL(){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_NL_RELAY, i);
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    bool initialState = bitRead(device.settings[0], 0);
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);

    relaysNL[i].begin(ui.pins[0], momentary, reversed);
    relaysNL[i].command(initialState);
  }
  assignRelaysNL();
}

void BMC::assignRelaysNL(){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);

    relaysNL[i].setMomentary(momentary);
    relaysNL[i].setReverse(reversed);

    relaysNL[i].reassign();
  }
}

void BMC::readRelaysNL(){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysNL[i];
    if(device.events[0] != 0){
      uint8_t cmd = processEvent(BMC_DEVICE_GROUP_RELAY, BMC_DEVICE_ID_NL_RELAY,
                                 i, BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
      relaysNL[i].command(cmd);
    }
    globals.relayNLStates.setBit(i, relaysNL[i].update());
  }
  if(globals.relayNLStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_NL_RELAY);
  }
}
*/
#endif


// LATCHING RELAYS
#if BMC_MAX_L_RELAYS > 0
/*
void BMC::setupRelaysL(){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_L_RELAY, i);
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    bool initialState = bitRead(device.settings[0], 0);
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);
    relaysL[i].begin(ui.pins[0], ui.pins[1], momentary, reversed);
    // bit 0 of event is initial state
    relaysL[i].command(initialState);
  }
  assignRelaysL();
}

void BMC::assignRelaysL(){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    bool momentary = bitRead(device.settings[0], 1);
    bool reversed = bitRead(device.settings[0], 2);
    relaysL[i].setMomentary(momentary);
    relaysL[i].setReverse(reversed);
    relaysL[i].reassign();
  }
}
void BMC::readRelaysL(){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    bmcStoreDevice <1, 1>& device = store.global.relaysL[i];
    if(device.events[0] != 0){
      uint8_t cmd = processEvent(BMC_DEVICE_GROUP_RELAY, BMC_DEVICE_ID_L_RELAY,
                                 i, BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
      relaysL[i].command(cmd);
    }
    globals.relayLStates.setBit(i, relaysL[i].update());
  }
  if(globals.relayLStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_L_RELAY);
  }
}
*/
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  

#endif
