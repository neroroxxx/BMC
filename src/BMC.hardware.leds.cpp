/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_TOTAL_LEDS > 0
// SETUP
void BMC::setupLeds(){
  ledBlinkerTimer.start(BMC_LED_BLINK_TIMEOUT);
#if BMC_MAX_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_LED, i);
    leds[i].begin(ui.pins[0]);

    #if BMC_PAGE_LED_DIM == true
    leds[i].setPwmOffValue(settings.getPwmDimWhenOff());
    #endif

    #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
      leds[i].test(true);
    #endif

    #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      if(leds[i].muxTesting()){
        mux.testDigital(leds[i].getMuxPin());
      }
    #endif
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_LED, i);
    globalLeds[i].begin(ui.pins[0]);
    //globalLeds[i].begin(BMCBuildData::getGlobalLedPin(i));

    #if BMC_GLOBAL_LED_DIM == true
    globalLeds[i].setPwmOffValue(settings.getPwmDimWhenOff());
    #endif

    #if !defined(BMC_NO_GLOBAL_LED_TEST_AT_LAUNCH)
      globalLeds[i].test(true);
    #endif

    #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      if(globalLeds[i].muxTesting()){
        mux.testDigital(globalLeds[i].getMuxPin());
      }
    #endif
  }
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_BI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_BI_LED, i);
    for(uint16_t e = (i*2), u=0; e < 2; e++, u++){
      biLeds[e].begin(ui.pins[u]);
      #if BMC_PAGE_LED_DIM == true
        biLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        biLeds[e].test(true);
      #endif
      #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
        if(biLeds[e].muxTesting()){
          mux.testDigital(biLeds[e].getMuxPin());
        }
      #endif
    }
  }
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_BI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_BI_LED, i);
    for(uint16_t e = (i*2), u=0; e < 2; e++, u++){
      globalBiLeds[e].begin(ui.pins[u]);
      #if BMC_GLOBAL_LED_DIM == true
        globalBiLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
      #if !defined(BMC_NO_GLOBAL_LED_TEST_AT_LAUNCH)
        globalBiLeds[e].test(true);
      #endif
      #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
        if(globalBiLeds[e].muxTesting()){
          mux.testDigital(globalBiLeds[e].getMuxPin());
        }
      #endif
    }
  }
#endif

#if BMC_MAX_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_TRI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_TRI_LED, i);
    for(uint16_t e = (i*3), u=0; e < 3; e++, u++){
      triLeds[e].begin(ui.pins[u]);
      #if BMC_PAGE_LED_DIM == true
        triLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        triLeds[e].test(true);
      #endif
      #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
        if(triLeds[e].muxTesting()){
          mux.testDigital(triLeds[e].getMuxPin());
        }
      #endif
    }
  }
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_TRI_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_TRI_LED, i);
    for(uint16_t e = (i*3), u=0; e < 3; e++, u++){
      globalTriLeds[e].begin(ui.pins[u]);
      #if BMC_GLOBAL_LED_DIM == true
        globalTriLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
      #if !defined(BMC_NO_GLOBAL_LED_TEST_AT_LAUNCH)
        globalTriLeds[e].test(true);
      #endif
      #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
        if(globalTriLeds[e].muxTesting()){
          mux.testDigital(globalTriLeds[e].getMuxPin());
        }
      #endif
    }
  }
#endif
}

void BMC::assignLeds(){
#if BMC_MAX_LEDS > 0
  globals.ledStates.clear();
  for(uint16_t index = 0; index < BMC_MAX_LEDS; index++){
    bmcStoreDevice <1, 1>& device = store.pages[page].leds[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);

    leds[index].reassign(device.settings[0]);
    // turn off blinking for certain events like MIDI IO
    if(!BMCTools::isLedBlinkAllowed(data.type)){
      leds[index].setBlinkMode(false);
    }
#if BMC_PAGE_LED_DIM == true
    leds[index].setPwmOffValue(settings.getPwmDimWhenOff());
#endif
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  globals.globalLedStates.clear();
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    bmcStoreDevice <1, 1>& device = store.global.leds[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);

    globalLeds[index].reassign(device.settings[0]);
    // turn off blinking for certain events like MIDI IO
    if(!BMCTools::isLedBlinkAllowed(data.type)){
      globalLeds[index].setBlinkMode(false);
    }
#if BMC_GLOBAL_LED_DIM == true
    globalLeds[index].setPwmOffValue(settings.getPwmDimWhenOff());
#endif
  }
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_BI_LEDS; index++){
    bmcStoreDevice <2, 2>& device = store.pages[page].biLeds[index];
    // for(uint16_t e = (index*2), u = 0; e < BMC_MAX_BI_LEDS; e++, u++){
    for(uint16_t e = (index*2), u = 0; u < 2; e++, u++){
      globals.biLedStates[u].clear();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[u]);
      biLeds[e].reassign(device.settings[u]);
      // turn off blinking for certain events like MIDI IO
      if(!BMCTools::isLedBlinkAllowed(data.type)){
        biLeds[e].setBlinkMode(false);
      }
      #if BMC_PAGE_LED_DIM == true
        biLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
    }

  }
#endif

#if BMC_MAX_GLOBAL_BI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_BI_LEDS; index++){
    bmcStoreDevice <2, 2>& device = store.global.biLeds[index];
    // for(uint16_t e = (index*2), u = 0; e < BMC_MAX_GLOBAL_BI_LEDS; e++, u++){
    for(uint16_t e = (index*2), u = 0; u < 2; e++, u++){
      globals.globalBiLedStates[u].clear();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[u]);
      globalBiLeds[e].reassign(device.settings[u]);
      // turn off blinking for certain events like MIDI IO
      if(!BMCTools::isLedBlinkAllowed(data.type)){
        globalBiLeds[e].setBlinkMode(false);
      }
      #if BMC_GLOBAL_LED_DIM == true
        globalBiLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
    }
  }
#endif

#if BMC_MAX_TRI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_TRI_LEDS; index++){
    bmcStoreDevice <3, 3>& device = store.pages[page].triLeds[index];
    // for(uint16_t e = (index*3), u = 0; e < BMC_MAX_TRI_LEDS; e++, u++){
    for(uint16_t e = (index*3), u = 0; u < 3; e++, u++){
      globals.triLedStates[u].clear();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[u]);
      triLeds[e].reassign(device.settings[u]);
      // turn off blinking for certain events like MIDI IO
      if(!BMCTools::isLedBlinkAllowed(data.type)){
        triLeds[e].setBlinkMode(false);
      }
      #if BMC_PAGE_LED_DIM == true
        triLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
    }

  }
#endif

#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_TRI_LEDS; index++){
    bmcStoreDevice <3, 3>& device = store.global.triLeds[index];
    // for(uint16_t e = (index*3), u = 0; e < BMC_MAX_GLOBAL_TRI_LEDS; e++, u++){
    for(uint16_t e = (index*3), u = 0; u < 3; e++, u++){
      globals.globalTriLedStates[u].clear();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[u]);
      globalTriLeds[e].reassign(device.settings[u]);
      // turn off blinking for certain events like MIDI IO
      if(!BMCTools::isLedBlinkAllowed(data.type)){
        globalTriLeds[e].setBlinkMode(false);
      }
      #if BMC_GLOBAL_LED_DIM == true
        globalTriLeds[e].setPwmOffValue(settings.getPwmDimWhenOff());
      #endif
    }
  }
#endif
}















void BMC::readLeds(){
  bool blinkState = ledBlinkerTimer.complete();
#if BMC_MAX_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    bmcStoreDevice <1, 1>& device = store.pages[page].leds[i];
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_LED, i,
                                BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
    if(state<=1){
      leds[i].setState(state);
    } else if(state==2){
      leds[i].pulse();
    } else if(state==3){
      leds[i].setBlinkMode(true);
      leds[i].setState(true);
    } else if(state!=255){
      leds[i].setBlinkMode(bitRead(state, 2));
      leds[i].setState(bitRead(state, 3));
    }
    globals.ledStates.setBit(i, leds[i].update(blinkState));

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(leds[i].getMuxPin(), leds[i].getMuxState());
    if(leds[i].muxTesting()){
      mux.testDigital(leds[i].getMuxPin());
    }
#endif

  }
  if(globals.ledStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_LED);
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    bmcStoreDevice <1, 1>& device = store.global.leds[i];
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_GLOBAL_LED, i,
                                BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
    if(state<=1){
      globalLeds[i].setState(state);
    } else if(state==2){
      globalLeds[i].pulse();
    } else if(state!=255){
      globalLeds[i].setBlinkMode(bitRead(state, 2));
      globalLeds[i].setState(bitRead(state, 3));
    }
    globals.globalLedStates.setBit(i, globalLeds[i].update(blinkState));

  #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(globalLeds[i].getMuxPin(), globalLeds[i].getMuxState());
    if(globalLeds[i].muxTesting()){
      mux.testDigital(globalLeds[i].getMuxPin());
    }
  #endif
  }
  if(globals.globalLedStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_LED);
  }
#endif

#if BMC_MAX_BI_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_BI_LEDS; i++){
    bmcStoreDevice <2, 2>& device = store.pages[page].biLeds[i];
    for(uint16_t e = (i*2), u = 0; u < 2; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_BI_LED, i,
                                  BMC_EVENT_IO_TYPE_OUTPUT, device.events[u]);
      if(state<=1){
        biLeds[e].setState(state);
      } else if(state==2){
        biLeds[e].pulse();
      } else if(state==3){
        biLeds[e].setBlinkMode(true);
        biLeds[e].setState(true);
      } else if(state!=255){
        biLeds[e].setBlinkMode(bitRead(state, 2));
        biLeds[e].setState(bitRead(state, 3));
      }
      globals.biLedStates[u].setBit(i, biLeds[e].update(blinkState));

  #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      mux.writeDigital(biLeds[e].getMuxPin(), biLeds[e].getMuxState());
      if(biLeds[e].muxTesting()){
        mux.testDigital(biLeds[e].getMuxPin());
      }
  #endif
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
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_GLOBAL_BI_LED, i,
                                  BMC_EVENT_IO_TYPE_OUTPUT, device.events[u]);
      if(state<=1){
        globalBiLeds[e].setState(state);
      } else if(state==2){
        globalBiLeds[e].pulse();
      } else if(state!=255){
        globalBiLeds[e].setBlinkMode(bitRead(state, 2));
        globalBiLeds[e].setState(bitRead(state, 3));
      }
      globals.globalBiLedStates[u].setBit(i, globalBiLeds[e].update(blinkState));

    #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      mux.writeDigital(globalBiLeds[e].getMuxPin(), globalBiLeds[e].getMuxState());
      if(globalBiLeds[e].muxTesting()){
        mux.testDigital(globalBiLeds[e].getMuxPin());
      }
    #endif
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
    bmcStoreDevice <3, 3>& device = store.pages[page].triLeds[i];
    for(uint16_t e = (i*3), u = 0; u < 3; e++, u++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_TRI_LED, i,
                                  BMC_EVENT_IO_TYPE_OUTPUT, device.events[u]);
      if(state<=1){
        triLeds[e].setState(state);
      } else if(state==2){
        triLeds[e].pulse();
      } else if(state==3){
        triLeds[e].setBlinkMode(true);
        triLeds[e].setState(true);
      } else if(state!=255){
        triLeds[e].setBlinkMode(bitRead(state, 2));
        triLeds[e].setState(bitRead(state, 3));
      }
      globals.triLedStates[u].setBit(i, triLeds[e].update(blinkState));

  #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      mux.writeDigital(triLeds[e].getMuxPin(), triLeds[e].getMuxState());
      if(triLeds[e].muxTesting()){
        mux.testDigital(triLeds[e].getMuxPin());
      }
  #endif
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
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_GLOBAL_TRI_LED, i,
                                  BMC_EVENT_IO_TYPE_OUTPUT, device.events[u]);
      if(state<=1){
        globalTriLeds[e].setState(state);
      } else if(state==2){
        globalTriLeds[e].pulse();
      } else if(state!=255){
        globalTriLeds[e].setBlinkMode(bitRead(state, 2));
        globalTriLeds[e].setState(bitRead(state, 3));
      }
      globals.globalTriLedStates[u].setBit(i, globalTriLeds[e].update(blinkState));

    #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      mux.writeDigital(globalTriLeds[e].getMuxPin(), globalTriLeds[e].getMuxState());
      if(globalTriLeds[e].muxTesting()){
        mux.testDigital(globalTriLeds[e].getMuxPin());
      }
    #endif
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
#endif
