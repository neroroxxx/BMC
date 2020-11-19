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
  for(uint8_t i = 0; i < BMC_MAX_LEDS; i++){
    leds[i].begin(BMCBuildData::getLedPin(i));

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
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    globalLeds[i].begin(BMCBuildData::getGlobalLedPin(i));

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
  bmcStorePage& pageData = store.pages[page];
  for(uint8_t index = 0; index < BMC_MAX_LEDS; index++){
    leds[index].reassign(bitRead(pageData.leds[index].event, 31));
    // turn off blinking for certain events like MIDI IO
    if(!BMCTools::isLedBlinkAllowed(pageData.leds[index].event & 0xFF)){
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
  uint32_t _ledStates = ledStates;
  for(uint8_t i = 0; i < BMC_MAX_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    uint8_t state = handleLedEvent(i, store.pages[page].leds[i].event, 0);
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
    bitWrite(_ledStates, i, leds[i].update());

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(leds[i].getMuxPin(), leds[i].getMuxState());
    if(leds[i].muxTesting()){
      mux.testDigital(leds[i].getMuxPin());
    }
#endif

  }
  if(ledStates != _ledStates){
    ledStates = _ledStates;
    editor.utilitySendLedActivity(ledStates);
    if(callback.ledsActivity){
      callback.ledsActivity(ledStates);
    }
  }
}
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
/*
  Read
*/
void BMC::assignGlobalLeds(){
  for(uint8_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    globalLeds[index].reassign(bitRead(globalData.leds[index].event, 31));
    // turn off blinking for certain events
    if(!BMCTools::isLedBlinkAllowed(globalData.leds[index].event&0xFF)){
      globalLeds[index].setBlinkMode(false);
    }
#if BMC_GLOBAL_LED_DIM == true
    globalLeds[index].setPwmOffValue(settings.getPwmDimWhenOff());
#endif

  }
}
void BMC::readGlobalLeds(){
  uint16_t _globalLedStates = 0;
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    uint8_t state = handleLedEvent(i, globalData.leds[i].event, 1);
    if(state<=1){
      globalLeds[i].setState(state);
    } else if(state==2){
      globalLeds[i].pulse();
    } else if(state!=255){
      globalLeds[i].setBlinkMode(bitRead(state, 2));
      globalLeds[i].setState(bitRead(state, 3));
    }
    bitWrite(_globalLedStates,i,globalLeds[i].update());
#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    mux.writeDigital(globalLeds[i].getMuxPin(), globalLeds[i].getMuxState());
    if(globalLeds[i].muxTesting()){
      mux.testDigital(globalLeds[i].getMuxPin());
    }
#endif
  }
  if(_globalLedStates!=globalLedStates){
    globalLedStates = _globalLedStates;
    editor.utilitySendGlobalLedActivity(globalLedStates);
    if(callback.globalLedsActivity){
      callback.globalLedsActivity(globalLedStates);
    }
  }
}
#endif
