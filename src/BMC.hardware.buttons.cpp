/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if defined(BMC_HAS_BUTTONS)
// setup buttons by assigning button pins, we only do this once at startup
void BMC::setupButtons(){
#if BMC_MAX_BUTTONS > 0
  for(uint16_t i = 0; i < BMC_MAX_BUTTONS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_BUTTON, i);
    buttons[i].begin(ui.pins[0]);
  }
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_BUTTON, i);
    globalButtons[i].begin(ui.pins[0]);
  }
#endif
}

void BMC::assignButtons(){
#if BMC_MAX_BUTTONS > 0
  for(uint16_t i = 0; i < BMC_MAX_BUTTONS; i++){
    assignButton(buttons[i], store.layers[layer].buttons[i]);
  }
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    assignButton(globalButtons[i], store.global.buttons[i]);
  }
#endif
}

void BMC::assignButton(BMCButton& button, bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>& data){
  // first check fi the button has an event with a State Change Trigger
  bool hasStateChangeTrigger = flags.read(BMC_FLAGS_FIRST_LOOP);
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    if((data.settings[e] & 0x0F) == BMC_BUTTON_PRESS_TYPE_STATE_CHANGE){
      hasStateChangeTrigger = true;
      break;
    }
  }
  button.reassign(hasStateChangeTrigger);
  button.setThreshold(settings.getButtonHoldThreshold());
  // read button only any of it's events have a Trigger set
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    if((data.settings[e] & 0x0F) != BMC_NONE){
      button.setMode(data.settings[e]);
      button.setFlags(data.settings[0]);
    }
  }
}
// assign button hold threshold and flags.
// this happens everytime a layer changes since it can be different for each layer
// also we activate buttons, if a button doesn't have an event attached then
// we don't bother parsing the event data, UNLESS all buttons are active thru settings

// read the buttons
void BMC::readButtons(){
#if BMC_MAX_BUTTONS > 0
  for(uint16_t i = 0; i < BMC_MAX_BUTTONS; i++){
    bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>& device = store.layers[layer].buttons[i];
    // GET THE PIN STATE FROM MUX
    #if defined(BMC_MUX_INPUTS_AVAILABLE)
      buttons[i].setMuxValue(mux.readDigital(buttons[i].getMuxPin()));
    #endif

    uint8_t buttonTrigger = buttons[i].read();
    // this feature is only available when more than 1 button are compiled
    #if BMC_MAX_BUTTONS == 1
      // if only one button is compiled don't use this feature
      bool dual = false;
    #else
      bool dual = dualPress.read(i, buttonTrigger, buttons[i].isClosed());
    #endif
    if(buttonTrigger != BMC_NONE && !dual){
      handleButton(device, BMC_DEVICE_ID_BUTTON, i, buttonTrigger);
      #if defined(BMC_DEBUG)
        printButtonTrigger(BMC_DEVICE_ID_BUTTON, i, buttonTrigger);
      #endif
    }
    globals.buttonStates.setBit(i, buttons[i].isClosed());
  }
  if(globals.buttonStates.hasChanged()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_BUTTON);
  }
  #if BMC_MAX_BUTTONS > 1
    // used for dual buttons to run the timeout
    dualPress.update();
  #endif
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS>& device = store.global.buttons[i];
    // GET THE PIN STATE FROM MUX
    #if defined(BMC_MUX_INPUTS_AVAILABLE)
      globalButtons[i].setMuxValue(mux.readDigital(globalButtons[i].getMuxPin()));
    #endif

    uint8_t buttonTrigger = globalButtons[i].read();

    #if BMC_MAX_GLOBAL_BUTTONS == 1
      // if only one button is compiled don't use this feature
      bool dual = false;
    #else
      bool dual = dualPressGlobal.read(i, buttonTrigger, globalButtons[i].isClosed());
    #endif

    if(buttonTrigger != BMC_NONE && !dual){
      handleButton(device, BMC_DEVICE_ID_GLOBAL_BUTTON, i, buttonTrigger);
      #if defined(BMC_DEBUG)
        printButtonTrigger(BMC_DEVICE_ID_GLOBAL_BUTTON, i, buttonTrigger);
      #endif
    }
    globals.globalButtonStates.setBit(i, globalButtons[i].isClosed());
  }
  if(globals.globalButtonStates.hasChanged()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_BUTTON);
  }

  #if BMC_MAX_GLOBAL_BUTTONS > 1
    // used for dual buttons to run the timeout
    dualPressGlobal.update();
  #endif
#endif
}

template <uint8_t sLen, uint8_t eLen>
void BMC::handleButton(bmcStoreDevice<sLen, eLen>& device, uint8_t deviceType, uint16_t index, uint8_t t_trigger){
  #if defined(BMC_USE_ON_BOARD_EDITOR)
  if(obe.checkDeviceAssignment(deviceType, index, t_trigger)){
    return;
  }
  #endif
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    bmcStoreEvent data = globals.getDeviceEventType(device.events[e]);
    uint8_t type = data.type;
    uint8_t trigger = (device.settings[e] & 0x0F) == t_trigger ? t_trigger : BMC_NONE;

    if(trigger != BMC_NONE){
      if(type != BMC_NONE){
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                  deviceType,
                  index,
                  device.events[e],
                  0,
                  trigger
                );
      }
      if(callback.buttonActivity){
        #if BMC_MAX_BUTTONS > 0
        if(deviceType== BMC_DEVICE_ID_BUTTON){
          callback.buttonActivity(index, e, trigger);
        }
        #endif

        #if BMC_MAX_GLOBAL_BUTTONS > 0
        if(deviceType== BMC_DEVICE_ID_GLOBAL_BUTTON){
          callback.globalButtonActivity(index, e, trigger);
        }
        #endif
      }
    }
    /*
    if(type==BMC_EVENT_TYPE_CUSTOM && callback.buttonsCustomActivity){
      callback.buttonsCustomActivity(index, e, data.ports);
    } else if(callback.buttonActivity){
      callback.buttonActivity(index, e, trigger);
    }
    */
  }
}

#endif

