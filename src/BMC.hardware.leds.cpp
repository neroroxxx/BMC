/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_TOTAL_LEDS > 0
// SETUP
void BMC::handleSetupLeds(BMCLed& t_led, uint16_t t_pin){
  t_led.begin(t_pin);
  #if BMC_LAYER_LED_DIM == true
    t_led.setPwmOffValue(settings.getPwmDimWhenOff());
  #endif

  #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
    t_led.test(true);
  #endif

  #if defined(BMC_MUX_OUTPUTS_AVAILABLE)
    if(t_led.muxTesting()){
      mux.testDigital(t_led.getMuxPin());
    }
  #endif
}
void BMC::setupLeds(){
  ledBlinkerTimer.start(BMC_LED_BLINK_TIMEOUT);
#if BMC_MAX_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_LED, i);
    handleSetupLeds(leds[i], ui.pins[0]);
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_LED, i);
    handleSetupLeds(globalLeds[i], ui.pins[0]);
  }
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_BI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_BI_LED, i);
    for(uint16_t e = (i*2), u=0; u < 2; e++, u++){
      handleSetupLeds(biLeds[e], ui.pins[u]);
    }
  }
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_BI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_BI_LED, i);
    for(uint16_t e = (i*2), u=0; u < 2; e++, u++){
      handleSetupLeds(globalBiLeds[e], ui.pins[u]);
    }
  }
#endif

#if BMC_MAX_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_TRI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_TRI_LED, i);
    for(uint16_t e = (i*3), u=0; u < 3; e++, u++){
      handleSetupLeds(triLeds[e], ui.pins[u]);
    }
  }
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_TRI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_TRI_LED, i);
    for(uint16_t e = (i*3), u=0; u < 3; e++, u++){
      handleSetupLeds(globalTriLeds[e], ui.pins[u]);
    }
  }
#endif
}
template <uint8_t sLen, uint8_t eLen, typename tname=bmcEvent_t>
void BMC::handleAssignLeds(BMCLed& t_led, bmcStoreDevice<sLen, eLen, tname>& t_device, uint8_t eIndex){
  bmcStoreEvent data = globals.getDeviceEventType(t_device.events[eIndex]);
  t_led.reassign(t_device.settings[eIndex]);
  // turn off blinking for certain events like MIDI IO
  if(!BMCTools::isLedBlinkAllowed(data.type)){
    t_led.setBlinkMode(false);
  }
#if BMC_LAYER_LED_DIM == true
  t_led.setPwmOffValue(settings.getPwmDimWhenOff());
#endif
}
void BMC::assignLeds(){
#if BMC_MAX_LEDS > 0
  globals.ledStates.clear();
  for(uint16_t index = 0; index < BMC_MAX_LEDS; index++){
    handleAssignLeds<1,1>(leds[index], store.layers[layer].leds[index]);
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  globals.globalLedStates.clear();
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    handleAssignLeds<1,1>(globalLeds[index], store.global.leds[index]);
  }
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_BI_LEDS; index++){
    for(uint16_t e = (index*2), u = 0; u < 2; e++, u++){
      globals.biLedStates[u].clear();
      handleAssignLeds<2,2>(biLeds[e], store.layers[layer].biLeds[index], u);
    }
  }
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_BI_LEDS; index++){
    for(uint16_t e = (index*2), u = 0; u < 2; e++, u++){
      globals.globalBiLedStates[u].clear();
      handleAssignLeds<2,2>(globalBiLeds[e], store.global.biLeds[index], u);
    }
  }
#endif

#if BMC_MAX_TRI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_TRI_LEDS; index++){
    for(uint16_t e = (index*3), u = 0; u < 3; e++, u++){
      globals.triLedStates[u].clear();
      handleAssignLeds<3,3>(triLeds[e], store.layers[layer].triLeds[index], u);
    }

  }
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_TRI_LEDS; index++){
    for(uint16_t e = (index*3), u = 0; u < 3; e++, u++){
      globals.globalTriLedStates[u].clear();
      handleAssignLeds<3,3>(globalTriLeds[e], store.global.triLeds[index], u);
    }
  }
#endif
}

void BMC::readLeds(){
  // blinState is passed to all leds, it turns true every 100ms
  // leds can blink at 100, 200, 300, 400, 500 ms rates, instead
  // of each led object having it's own timer, they all just have
  // 1 byte that holds a count of how many of these blinkStates
  // have happened and that is used to determine if the led should turn on/off
  blinkState = ledBlinkerTimer.complete();

#if BMC_MAX_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].leds[i];
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                  BMC_DEVICE_ID_LED,
                                  i,
                                  device.events[0]
                                );
    handleLed<BMC_MAX_LEDS>(leds[i], globals.ledStates, i, state);
  }
  if(globals.ledStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_LED);
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    bmcStoreDevice <1, 1>& device = store.global.leds[i];
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                  BMC_DEVICE_ID_GLOBAL_LED,
                                  i,
                                  device.events[0]
                                );
    handleLed<BMC_MAX_GLOBAL_LEDS>(globalLeds[i], globals.globalLedStates, i, state);
  }
  if(globals.globalLedStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_LED);
  }
  
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_BI_LEDS; i++){
    bmcStoreDevice <2, 2>& device = store.layers[layer].biLeds[i];
    for(uint16_t e = (i*2), u = 0; u < 2; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_BI_LED,
                                    i,
                                    device.events[u],
                                    0,
                                    u
                                  );
      handleLed<BMC_MAX_BI_LEDS>(biLeds[e], globals.biLedStates[u], i, state);
    }
  }
  {
    bool l1 = globals.biLedStates[0].hasChanged();
    bool l2 = globals.biLedStates[1].hasChanged();
    if(l1 || l2 || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_BI_LED);
    }
  }
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_BI_LEDS; i++){
    bmcStoreDevice <2, 2>& device = store.global.biLeds[i];
    for(uint16_t e = (i*2), u = 0; u < 2; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_GLOBAL_BI_LED,
                                    i,
                                    device.events[u],
                                    0,
                                    u
                                  );
      handleLed<BMC_MAX_GLOBAL_BI_LEDS>(globalBiLeds[e], globals.globalBiLedStates[u], i, state);
    }
  }
  {
    bool l1 = globals.globalBiLedStates[0].hasChanged();
    bool l2 = globals.globalBiLedStates[1].hasChanged();
    if(l1 || l2 || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_BI_LED);
    }
  }
#endif

#if BMC_MAX_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_TRI_LEDS; i++){
    bmcStoreDevice <3, 3>& device = store.layers[layer].triLeds[i];
    for(uint16_t e = (i*3), u = 0; u < 3; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_TRI_LED,
                                    i,
                                    device.events[u],
                                    0,
                                    u
                                  );
      handleLed<BMC_MAX_TRI_LEDS>(triLeds[e], globals.triLedStates[u], i, state);
    }
  }
  {
    bool l1 = globals.triLedStates[0].hasChanged();
    bool l2 = globals.triLedStates[1].hasChanged();
    bool l3 = globals.triLedStates[2].hasChanged();
    if(l1 || l2 || l3 || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_TRI_LED);
    }
  }

#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_TRI_LEDS; i++){
    bmcStoreDevice <3, 3>& device = store.global.triLeds[i];
    for(uint16_t e = (i*3), u = 0; u < 3; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_GLOBAL_TRI_LED,
                                    i,
                                    device.events[u],
                                    0,
                                    u
                                  );
      handleLed<BMC_MAX_GLOBAL_TRI_LEDS>(globalTriLeds[e], globals.globalTriLedStates[u], i, state);
    }
  }
  {
    bool l1 = globals.globalTriLedStates[0].hasChanged();
    bool l2 = globals.globalTriLedStates[1].hasChanged();
    bool l3 = globals.globalTriLedStates[2].hasChanged();
    if(l1 || l2 || l3 || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_TRI_LED);
    }
  }

#endif
}
template <uint16_t y>
void BMC::handleLed(BMCLed& t_led, BMCBitStates<y>& t_bitStates, uint8_t t_index, uint8_t t_state){
  if(t_state<=1){
    t_led.setState(t_state);
  } else if(t_state==2){
    t_led.pulse();
  } else if(t_state==3){
    t_led.setBlinkMode(true);
    t_led.setState(true);
  } else if(t_state!=255){
    t_led.setBlinkMode(bitRead(t_state, 2));
    t_led.setState(bitRead(t_state, 3));
  }
  t_bitStates.setBit(t_index, t_led.update(blinkState));

  #if defined(BMC_MUX_OUTPUTS_AVAILABLE)
  
  if(t_led.isMuxPin()){
    uint8_t muxPin = t_led.getMuxPin();
    bool muxState = t_led.getMuxState();
    mux.writeDigital(muxPin, muxState);
    if(t_led.muxTesting()){
      mux.testDigital(muxPin);
    }
  }

  #endif
}


#endif
