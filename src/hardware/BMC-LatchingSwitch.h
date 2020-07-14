/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  THIS FEATURE IS CURRENTLY NOT IMPLEMENTED

  Latching switches present many issues
    - They could be Footswitches or Toggles (which requires different UIs the for editor)
    - They may be in OPEN or CLOSED state at launch
    - If they are toggles they may represent a value in one direction or the other
    - Should they trigger their OPEN/CLOSED event at launch based on their state at launch?


*/
#ifndef BMC_LATCHING_SWITCH_H
#define BMC_LATCHING_SWITCH_H

#include "utility/BMC-Def.h"

// for input pullup when the button is pressed the state is LOW
// and when the button is depressed the state is HIGH
#define BMC_LATCH_SWITCH_CLOSED LOW

// @flags
#define BMC_LAT_SW_FLAG_REASSIGNED 0
#define BMC_LAT_SW_FLAG_DEFAULT 1
#define BMC_LAT_SW_FLAG_STATE 2
#define BMC_LAT_SW_FLAG_MUX_IN 3


class BMCLatchingSwitch {
public:
  BMCLatchingSwitch(){
    // reset everything
    reset();
  }
// if Expansion Buttons are compiled the begin method includes a parameter
// to tell it if this is an expansion button, this is because this same
// object is used for both regular and expansion buttons
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

#if BMC_MAX_MUX_IN > 0
// if the pin number is 64 or higher it's a mux pin but also check that's it's not an analog mux pin
    if(pin>=64){
      if(!BMCBuildData::isMuxInPin(pin)){
        BMC_ERROR(
          "Mux Pin:", pin,
          "Can NOT be used with latching switches as it is NOT a valid Mux In"
        );
        BMC_HALT();
      }
      flags.write(BMC_LAT_SW_FLAG_MUX_IN, true);
      // all good
      return;
    } else {
      flags.write(BMC_LAT_SW_FLAG_MUX_IN, false);
    }
#endif
    if(!BMCBuildData::isDigitalPin(pin)){
      BMC_ERROR(
        "PIN:", pin,
        "Can NOT be used with latching switches as it is NOT Digital capable"
      );
      BMC_HALT();
    }
    pinMode(pin, BMC_BUTTON_PIN_MODE);
    // reassign will set the current state of the button as the initial state
    reassign();
  }
  void reassign(){
    reset();
    flags.write(BMC_LAT_SW_FLAG_STATE, readState());
  }
  uint8_t read(){
    // check if the button has gone from OPEN to CLOSED or vice-versa
    if(stateChanged()){
      if(flags.read(BMC_LAT_SW_FLAG_STATE)){
        return BMC_BUTTON_PRESS_TYPE_PRESS;
      }
      return BMC_BUTTON_PRESS_TYPE_RELEASE;
    }
    return 0;
  }
  bool readState(){
#if BMC_MAX_MUX_IN > 0
    if(flags.read(BMC_LAT_SW_FLAG_MUX_IN)){
      return muxState;
    }
#endif
    return (digitalRead(pin)==BMC_LATCH_SWITCH_CLOSED);
  }
#if BMC_MAX_MUX_IN > 0
  void setMuxValue(bool t_state){
    muxState = t_state;
  }
  bool isMux(){
    return flags.read(BMC_LAT_SW_FLAG_MUX_IN);
  }
  uint8_t getMuxPin(){
    return isMux() ? pin-64 : 0;
  }
#endif

private:
  uint8_t pin = 255;
  unsigned long debounceTime = 0;
  BMCFlags <uint8_t> flags;
  #if BMC_MAX_MUX_IN > 0
    // start it with the OPEN state
    bool muxState = BMC_LATCH_SWITCH_CLOSED;
  #endif

  void reset(){
    debounceTime = 0;
    flags.reset(1 << BMC_LAT_SW_FLAG_MUX_IN);
  }
  bool stateChanged(){
    if(millis() - debounceTime >= BMC_BUTTON_DEBOUNCE_TIME){
      debounceTime = millis();
      if(flags.read(BMC_LAT_SW_FLAG_STATE) != readState()){
        flags.toggle(BMC_LAT_SW_FLAG_STATE);
        return true;
      }
    }
    return false;
  }
};
#endif
