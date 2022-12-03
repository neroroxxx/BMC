/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_AUX_JACKS > 0
// SETUP
void BMC::setupAuxJacks(){
  for(uint8_t i = 0; i < BMC_MAX_AUX_JACKS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_AUX_JACK, i);
    auxJacks[i].begin(ui.pins[0], ui.pins[1], ui.pins[2]);
  }
  assignAuxJacks();
}
void BMC::assignAuxJacks(){
  for(uint8_t i = 0; i < BMC_MAX_AUX_JACKS; i++){
    bmcStoreDevice <2, 3>& device = store.global.auxJacks[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    auxJacks[i].reassign();
    auxJacks[i].setMode(device.settings[0]);
    auxJacks[i].assignToeSwitch(device.events[1], device.events[2], device.settings[1]);
    uint16_t e = BMC_MAX_POTS+BMC_MAX_GLOBAL_POTS+i;
    auxJacks[i].setCalibration(
      globalData.potCalibration[e].events[0],
      globalData.potCalibration[e].events[1]
    );
  }
}
// READ
void BMC::readAuxJacks(){
  if(potCalibration.active()){
    if(potCalibration.getDeviceType()==BMC_DEVICE_ID_AUX_JACK){
      uint16_t n = potCalibration.getIndex();
      if(auxJacks[n].isPotMode()){
        uint16_t value = auxJacks[n].getAnalogValue();
        potCalibration.setValue(value);
        return;
      }
    }
  }
  for(uint8_t i = 0; i < BMC_MAX_AUX_JACKS; i++){
    bmcStoreDevice <2, 3>& device = store.global.auxJacks[i];
    auxJacks[i].update();
    globals.auxJackStates.setBit(i, auxJacks[i].isConnected());
    uint8_t cmd = auxJacks[i].read();
    if(cmd==0){
      continue;
    }
    if(cmd == 1){ //pot
      uint8_t value = auxJacks[i].getPotValue();
      processEvent(BMC_DEVICE_GROUP_POT, BMC_DEVICE_ID_POT, i, BMC_EVENT_IO_TYPE_INPUT, device.events[0], value);
    } else {
      if(cmd == 2){
        processEvent(BMC_DEVICE_GROUP_BUTTON, BMC_DEVICE_ID_BUTTON, i, BMC_EVENT_IO_TYPE_INPUT, device.events[1]);
      } else if(cmd == 3){
        processEvent(BMC_DEVICE_GROUP_BUTTON, BMC_DEVICE_ID_BUTTON, i, BMC_EVENT_IO_TYPE_INPUT, device.events[2]);
      }
    }
    /*

    */
  }
  if(globals.auxJackStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_AUX_JACK);
  }
}
// CALIBRATION
/*
uint16_t BMC::getPotAnalogValue(uint8_t n){
  return auxJacks[n].getAnalogValue();
}
*/
#endif
