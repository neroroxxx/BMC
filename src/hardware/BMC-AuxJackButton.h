/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_AUX_JACK_BTN_H
#define BMC_AUX_JACK_BTN_H
#include "utility/BMC-Def.h"

#define BMC_FLAG_AUX_JACK_BUTTON_REASSIGNED 0
#define BMC_FLAG_AUX_JACK_BUTTON_STATE 1
#define BMC_FLAG_AUX_JACK_BUTTON_LOG 2
#define BMC_FLAG_AUX_JACK_BUTTON_TOE_SWITCH_AVAILABLE 3
#define BMC_FLAG_AUX_JACK_BUTTON_TOE_SWITCH_STATE 4
#define BMC_FLAG_AUX_JACK_BUTTON_TOE_SWITCH_STATE_CHANGED 5

class BMCAuxJackButton {
public:
  BMCAuxJackButton(){
    // initialize with the pin number as 255
    // if the pin is 255 it means the begin method has not been called
    pin = 255;
    flags.reset();
    debounceTime = millis();
  }
  // begin, if the pin value is 255 only, and t_pin is not 255
  // this method will only work the first time it's called
  void begin(uint8_t t_pin){
    if(pin!=255){
      return;
    }
    if(t_pin==255){
      BMC_ERROR(
        "PIN:", t_pin,
        "is invalid, make sure you check that the pin was defined in your config"
      );
      BMC_HALT();
    }
    pin = t_pin;
    // check if the pin is Digital capable
    if(!BMCBuildData::isDigitalPin(pin) || pin >= 64){
      BMC_ERROR(
        "PIN:", t_pin,
        "Can NOT be used with Pots as it is NOT Digital Capable or is a MUX pin"
      );
      BMC_HALT();
    }
    pinMode(pin, BMC_BUTTON_PIN_MODE);
    debounceTime = millis();
  }
  // reassign the POT behaviour, used when switching pages or the editor
  // has updated EEPROM
  void reassign(){
    flags.reset();
    debounceTime = millis();
  }

  bool update(){
    if((millis() - debounceTime) >= BMC_BUTTON_DEBOUNCE_TIME){
      debounceTime = millis();
      if(flags.read(BMC_FLAG_AUX_JACK_BUTTON_STATE) != digitalRead(pin)){
        flags.toggle(BMC_FLAG_AUX_JACK_BUTTON_STATE);
        return flags.read(BMC_FLAG_AUX_JACK_BUTTON_STATE);
      }
    }
    return false;
  }
private:
  BMCFlags <uint8_t> flags;
  // pot pin number, must be analog input
  uint8_t pin = 255;
  unsigned long debounceTime = 0;

};
#endif
