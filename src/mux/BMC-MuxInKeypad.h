/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_IN_KEYPAD_H
#define BMC_MUX_IN_KEYPAD_H

#include "utility/BMC-Def.h"

#if defined(BMC_MAX_MUX_IN_KEYPAD) && BMC_MAX_MUX_IN_KEYPAD > 0

// BMC_MAX_MUX_IN_KEYPAD_ROW_PINS
// BMC_MAX_MUX_IN_KEYPAD_COL_PINS

// BMC_MAX_MUX_IN_KEYPAD_ROWS
// BMC_MAX_MUX_IN_KEYPAD_COLS

class BMCMuxInKeypad {
private:
  uint8_t rowPins[BMC_MAX_MUX_IN_KEYPAD_ROWS] = BMC_MAX_MUX_IN_KEYPAD_ROW_PINS;
  uint8_t colPins[BMC_MAX_MUX_IN_KEYPAD_COLS] = BMC_MAX_MUX_IN_KEYPAD_COL_PINS;
  bool states[(BMC_MAX_MUX_IN_KEYPAD>>4)];
  uint8_t parsePinNumber(uint8_t t_pin){
    t_pin -= (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG);
    return constrain(t_pin, 0, (BMC_MAX_MUX_IN_KEYPAD-1));
  }
public:
  BMCMuxInKeypad(){

  }
  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxInKeypad::begin()");
    BMC_PRINTLN("");

    for(uint8_t i = 0 ; i < BMC_MAX_MUX_IN_KEYPAD_ROWS ; i++){
      if(!BMCBuildData::isDigitalPin(rowPins[i]) || rowPins[i]>=64){
        BMC_ERROR(
          "PIN:", rowPins[i],
          "Can NOT be used with Keypad as it is NOT Digital capable"
        );
        BMC_HALT();
      }
    }
    for(uint8_t i = 0 ; i < BMC_MAX_MUX_IN_KEYPAD_COLS ; i++){
      if(!BMCBuildData::isDigitalPin(colPins[i]) || colPins[i]>=64){
        BMC_ERROR(
          "PIN:", colPins[i],
          "Can NOT be used with Keypad as it is NOT Digital capable"
        );
        BMC_HALT();
      }
    }
    for(uint8_t i = 0 ; i < BMC_MAX_MUX_IN_KEYPAD_ROWS ; i++){
      pin_mode(rowPins[i], INPUT_PULLUP);
    }
    for(uint8_t i = 0 ; i < BMC_MAX_MUX_IN_KEYPAD_COLS ; i++){
      pin_mode(rowPins[i], INPUT_PULLUP);
    }
  }
  void update(){
    for(uint8_t i = 0, pin=0; i < BMC_MAX_MUX_IN_KEYPAD_COLS; i++, pin++){
      pin_mode(colPins[i], OUTPUT);
      digitalWrite(colPins[i], LOW);
      for(int e = 0; e < BMC_MAX_MUX_IN_KEYPAD_ROWS; e++){
        bitWrite(states[pin>>4], e, digitalRead(rowPins[e])==LOW);
      }
      pin_mode(colPins[i], INPUT_PULLUP);
    }
  }
  bool getPinValue(uint8_t t_pin){
    t_pin = parsePinNumber(t_pin);
    return bitRead(states[t_pin>>4], (t_pin&0x0F));
  }
  void setPinValues(uint8_t t_pin, bool t_value){
    t_pin = parsePinNumber(t_pin);
    bitWrite(states[t_pin>>4], (t_pin&0x0F), t_value);
  }
};
#endif
#endif
