/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_PWM_LEDS > 0
// SETUP
void BMC::setupPwmLeds(){
  for(uint8_t i = 0; i < BMC_MAX_PWM_LEDS; i++){
    pwmLeds[i].begin(BMCBuildData::getPwmLedPin(i));
  }
}
void BMC::assignPwmLeds(){
  for(uint8_t index = 0; index < BMC_MAX_PWM_LEDS; index++){
    pwmLeds[index].reassign();
    pwmLeds[index].setPwmOffValue(settings.getPwmDimWhenOff());
  }
}
// Read
void BMC::readPwmLeds(){
  uint16_t _pwmLedStates = 0;
  bmcStorePage& pageData = store.pages[page];
  for(uint8_t i = 0; i < BMC_MAX_PWM_LEDS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    uint8_t state = handleLedEvent(i, pageData.pwmLeds[i].event, 2);
    // last 4 bits of the event are the brightness of the led, these are
    // stored in 4 bits so the value stored will range from 0 to 15
    // we have to map this value to from 0 to 15 to 1 127
    uint8_t brightness = (BMC_GET_BYTE(3, pageData.pwmLeds[i].event)>>4) & 0x0F;
    // since the brightness value should never be 0 (otherwise we're turning the led off)
    // we'll add 1 to that value and map it from there.
    brightness = map(brightness, 0, 15, 1, 127);

    if(state==0){
      // if handleLedEvent returns 0 we turn led off
      pwmLeds[i].setState(state);
    } else if(state==1){
      // if handleLedEvent returns 1 we turn led to led brightness
      pwmLeds[i].setState(brightness);
    } else if(state==2){
      // pulse led
      pwmLeds[i].pulse();
    } else if(state==3){
      // used to match return type 3 on standard leds which would blink
      pwmLeds[i].setState(brightness);
    } else if(state!=255){
      // set a specific brightness
      pwmLeds[i].setState(state-4);
    }
    bitWrite(_pwmLedStates, i, pwmLeds[i].update());
  }
  if(_pwmLedStates!=pwmLedStates){
    pwmLedStates = _pwmLedStates;
    editor.utilitySendPwmLedActivity(pwmLedStates);
  }
}
#endif
