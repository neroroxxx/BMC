/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
// SETUP
void BMC::setupPots(){
#if BMC_MAX_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_POT, i);
    pots[i].begin(ui.pins[0]);
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_POT, i);
    globalPots[i].begin(ui.pins[0]);
  }
#endif
}

void BMC::assignPots(){
#if BMC_MAX_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    bmcStoreDevice <1, 3>& device = store.layers[layer].pots[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    bmcEvent_t toeEngage = device.events[1];
    bmcEvent_t toeDisengage = device.events[2];
    pots[i].reassign();
    pots[i].setCalibration(
      store.global.potCalibration[i].events[0],
      store.global.potCalibration[i].events[1]
    );
    //pot.setTaper(bitRead(BMC_GET_BYTE(3, event), 7));
    pots[i].assignToeSwitch(toeEngage, toeDisengage, device.settings[0]);
  }
#endif
#if BMC_MAX_GLOBAL_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    bmcStoreDevice <1, 3>& device = store.global.pots[i];
    bmcEvent_t toeEngage = device.events[1];
    bmcEvent_t toeDisengage = device.events[2];
    globalPots[i].reassign();
    globalPots[i].setCalibration(
      store.global.potCalibration[BMC_MAX_POTS+i].events[0],
      store.global.potCalibration[BMC_MAX_POTS+i].events[1]
    );
    //pot.setTaper(bitRead(BMC_GET_BYTE(3, event), 7));
    globalPots[i].assignToeSwitch(toeEngage, toeDisengage, device.settings[0]);
  }
#endif
}

void BMC::readPots(){
#if BMC_MAX_POTS > 0
  // handle Calibration
  if(potCalibration.active()){
    if(potCalibration.getDeviceType()==BMC_DEVICE_ID_POT){
      uint16_t n = potCalibration.getIndex();
#if BMC_MAX_MUX_IN_ANALOG > 0
      pots[n].setMuxValue(mux.readAnalog(pots[n].getMuxPin()));
#endif
      uint16_t value = pots[n].getAnalogValue();
      potCalibration.setValue(value);
      return;
    }
  }
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    bmcStoreDevice <1, 3>& device = store.layers[layer].pots[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
#if BMC_MAX_MUX_IN_ANALOG > 0
    pots[i].setMuxValue(mux.readAnalog(pots[i].getMuxPin()));
#endif

    if(pots[i].toeSwitchActive()){
      potParseToeSwitch(pots[i]);
    }
    bool sendData = false;
    if(pots[i].update()){
      sendData = true;
      uint8_t value = pots[i].getValue();
      processEvent(BMC_DEVICE_GROUP_POT,
                    BMC_DEVICE_ID_POT,
                    i,
                    device.events[0],
                    value
                  );
      #if defined(BMC_DEBUG)
        if(globals.getPotsDebug()){
          BMC_PRINTLN("Pot", i, value);
        }
      #endif
      // HANDLE CALLBACKS
      /*
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.potCustomActivity){
        callback.potCustomActivity(i, value);
      } else if(callback.potActivity){
        callback.potActivity(i, value);
      }
      */
    }
    if(globals.editorConnected() && (sendData || editor.isTriggerStates())){
      editor.utilitySendPotActivity(BMC_DEVICE_ID_POT, i, pots[i].getPosition());
    }
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  if(potCalibration.active()){
    if(potCalibration.getDeviceType()==BMC_DEVICE_ID_GLOBAL_POT){
      uint16_t n = potCalibration.getIndex();
  #if BMC_MAX_MUX_IN_ANALOG > 0
      globalPots[n].setMuxValue(mux.readAnalog(globalPots[n].getMuxPin()));
  #endif
      uint16_t value = globalPots[n].getAnalogValue();
      potCalibration.setValue(value);
      return;
    }
  }
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
  #if BMC_MAX_MUX_IN_ANALOG > 0
    globalPots[i].setMuxValue(mux.readAnalog(globalPots[i].getMuxPin()));
  #endif
    bmcStoreDevice <1, 3>& device = store.global.pots[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    if(globalPots[i].toeSwitchActive()){
      potParseToeSwitch(globalPots[i]);
      /*
      if(callback.globalPotsToeSwitchState && BMC_GET_BYTE(0, globalPots[i].toeSwitchGetEvent())>0){
        callback.globalPotsToeSwitchState(i, globalPots[i].toeSwitchGetState());
      }
      */
    }
    bool sendData = false;
    if(globalPots[i].update()){
      sendData = true;
      uint8_t value = globalPots[i].getValue();
      processEvent(BMC_DEVICE_GROUP_POT,
                    BMC_DEVICE_ID_GLOBAL_POT,
                    i,
                    device.events[0],
                    value
                  );
      #if defined(BMC_DEBUG)
        if(globals.getPotsDebug()){
          BMC_PRINTLN("Globals Pot", i, value);
        }
      #endif
      // HANDLE CALLBACKS
      /*
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.globalPotCustomActivity){
        callback.globalPotCustomActivity(i, value);
      } else if(callback.globalPotActivity){
        callback.globalPotActivity(i, value);
      }
      */
    }
    if(globals.editorConnected() && (sendData || editor.isTriggerStates())){
      editor.utilitySendPotActivity(BMC_DEVICE_ID_GLOBAL_POT, i, globalPots[i].getPosition());
    }
  }
#endif
}

void BMC::potParseToeSwitch(BMCPot& pot){
  if(!pot.toeSwitchAvailable()){
    return;
  }
  processEvent(BMC_DEVICE_GROUP_BUTTON,
                BMC_DEVICE_ID_BUTTON,
                0,
                pot.toeSwitchGetEvent()
              );
}

#endif
