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

// #define BMC_MAX_MUX_IN_KEYPAD_STATES (((BMC_MAX_MUX_IN_KEYPAD>>3)&0x1F)+1)
#define BMC_MAX_MUX_IN_KEYPAD_STATES (((BMC_MAX_MUX_IN_KEYPAD>>3)-1)+1)

class BMCMuxInKeypad {
private:
  uint8_t rowPins[BMC_MAX_MUX_IN_KEYPAD_ROWS] = BMC_MAX_MUX_IN_KEYPAD_ROW_PINS;
  uint8_t colPins[BMC_MAX_MUX_IN_KEYPAD_COLS] = BMC_MAX_MUX_IN_KEYPAD_COL_PINS;
  uint8_t states[BMC_MAX_MUX_IN_KEYPAD_STATES];
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
      pinMode(rowPins[i], INPUT_PULLUP);
    }
    for(uint8_t i = 0 ; i < BMC_MAX_MUX_IN_KEYPAD_COLS ; i++){
      pinMode(colPins[i], INPUT_PULLUP);
    }
  }
  void update(){
    uint8_t pin = 0;
    for(uint8_t i = 0; i < BMC_MAX_MUX_IN_KEYPAD_COLS; i++){
      pinMode(colPins[i], OUTPUT);
      digitalWrite(colPins[i], LOW);
      for(int e = 0; e < BMC_MAX_MUX_IN_KEYPAD_ROWS; e++){
        pin = i + (e*BMC_MAX_MUX_IN_KEYPAD_COLS);
        bitWrite(states[pin>>3], pin & 0x07, digitalRead(rowPins[e]));
      }      
      pinMode(colPins[i], INPUT_PULLUP);
    }
  }
  bool readPin(uint8_t t_pin){
    t_pin = parsePinNumber(t_pin);
    if(t_pin >= BMC_MAX_MUX_IN_KEYPAD){
      return false;
    }
    return bitRead(states[t_pin>>3], t_pin & 0x07);
  }
  bool getPinValue(uint8_t t_pin){
    return readPin(t_pin);
  }
};
#endif
#endif
