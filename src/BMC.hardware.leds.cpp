/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_LEDS > 0 || BMC_MAX_GLOBAL_LEDS > 0
// SETUP
void BMC::setupLeds(){
#if BMC_MAX_LEDS > 0
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_LED, i);
    leds[i].begin(ui.pin);

    #if BMC_PAGE_LED_DIM == true
    leds[i].setPwmOffValue(settings.getPwmDimWhenOff());
    #endif

    #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
      leds[i].test();
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
    globalLeds[i].begin(ui.pin);
    //globalLeds[i].begin(BMCBuildData::getGlobalLedPin(i));

    #if BMC_GLOBAL_LED_DIM == true
    globalLeds[i].setPwmOffValue(settings.getPwmDimWhenOff());
    #endif

    #if !defined(BMC_NO_GLOBAL_LED_TEST_AT_LAUNCH)
      globalLeds[i].test();
    #endif

    #if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
      if(globalLeds[i].muxTesting()){
        mux.testDigital(globalLeds[i].getMuxPin());
      }
    #endif
  }
  assignGlobalLeds();
#endif
}
#endif

#if BMC_MAX_LEDS > 0
void BMC::assignLeds(){
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
}
/*
  Read
*/
void BMC::readLeds(){
  for(uint16_t i = 0; i < BMC_MAX_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    //uint8_t state = handleLedEvent(i, store.pages[page].leds[i].event, 0);
    //uint8_t state = 0;
    bmcStoreDevice <1, 1>& device = store.pages[page].leds[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
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
    globals.ledStates.setBit(i, leds[i].update());

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(leds[i].getMuxPin(), leds[i].getMuxState());
    if(leds[i].muxTesting()){
      mux.testDigital(leds[i].getMuxPin());
    }
#endif

  }
  if(globals.ledStates.hasChanged()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_LED);
  }
}
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
/*
  Read
*/
void BMC::assignGlobalLeds(){
  for(uint16_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    bmcStoreDevice <1, 1>& device = store.global.leds[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);

    globalLeds[index].reassign(device.settings[0]);
    // turn off blinking for certain events like MIDI IO
    if(!BMCTools::isLedBlinkAllowed(data.type)){
      globalLeds[index].setBlinkMode(false);
    }

    /*
    globalLeds[index].reassign(bitRead(globalData.leds[index].event, 31));
    // turn off blinking for certain events
    if(!BMCTools::isLedBlinkAllowed(globalData.leds[index].event&0xFF)){
      globalLeds[index].setBlinkMode(false);
    }
    */
#if BMC_GLOBAL_LED_DIM == true
    globalLeds[index].setPwmOffValue(settings.getPwmDimWhenOff());
#endif

  }
}
void BMC::readGlobalLeds(){
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    //uint8_t state = handleLedEvent(i, globalData.leds[i].event, 1);
    bmcStoreDevice <1, 1>& device = store.global.leds[i];
    //bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
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
    globals.globalLedStates.setBit(i, globalLeds[i].update());

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(globalLeds[i].getMuxPin(), globalLeds[i].getMuxState());
    if(globalLeds[i].muxTesting()){
      mux.testDigital(globalLeds[i].getMuxPin());
    }
#endif
  }

  if(globals.globalLedStates.hasChanged()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_LED);
  }
}
#endif
