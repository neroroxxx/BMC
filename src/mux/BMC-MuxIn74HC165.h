/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Control up to 4 74HC165, these are 8 pin multiplexers and they must have a
  pullup resistor on each pin, 10k should work
*/
#ifndef BMC_MUX_IN_74HC165_H
#define BMC_MUX_IN_74HC165_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_IN > 0 && BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165

#ifndef BMC_MUX_IN_74HC165_CLOCK
  #error "BMC_MUX_IN_74HC165_CLOCK was NOT defined"
#elif BMC_MUX_IN_74HC165_CLOCK >= 64
  #error "BMC_MUX_IN_74HC165_CLOCK is not a valid pin"
#endif

#ifndef BMC_MUX_IN_74HC165_LOAD
  #error "BMC_MUX_IN_74HC165_LOAD was NOT defined"
#elif BMC_MUX_IN_74HC165_LOAD >= 64
  #error "BMC_MUX_IN_74HC165_LOAD is not a valid pin"
#endif

#ifndef BMC_MUX_IN_74HC165_DATA
  #error "BMC_MUX_IN_74HC165_DATA was NOT defined"
#elif BMC_MUX_IN_74HC165_DATA >= 64
  #error "BMC_MUX_IN_74HC165_DATA is not a valid pin"
#endif

// #define BMC_MUX_IN_74HC165_1MS_READ


#define BMC_MUX_IN_74HC165_DELAY 5

#if BMC_MAX_MUX_IN > 64
  #undef BMC_MAX_MUX_IN
  #define BMC_MAX_MUX_IN 64
#endif


#if BMC_MAX_MUX_IN == 1
  #define BMC_MUX_IN_CHIP_COUNT 1
#else
  #define BMC_MUX_IN_CHIP_COUNT (((BMC_MAX_MUX_IN - 1) >> 3) + 1)
#endif


class BMCMuxIn74HC165 {
private:
  uint8_t states[BMC_MUX_IN_CHIP_COUNT];

public:
  BMCMuxIn74HC165(){}
  void begin(){
    BMC_PRINTLN("BMCMuxIn74HC165::begin()");
    pinMode(BMC_MUX_IN_74HC165_CLOCK, OUTPUT);
    pinMode(BMC_MUX_IN_74HC165_LOAD, OUTPUT);
    pinMode(BMC_MUX_IN_74HC165_DATA, INPUT);
    digitalWrite(BMC_MUX_IN_74HC165_CLOCK, LOW);
    digitalWrite(BMC_MUX_IN_74HC165_LOAD, HIGH);
  }

  void update(){
    // set load pin
    digitalWrite(BMC_MUX_IN_74HC165_LOAD, LOW);
    delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
    digitalWrite(BMC_MUX_IN_74HC165_LOAD, HIGH);
    for(uint8_t mux = 0; mux < BMC_MUX_IN_CHIP_COUNT; mux++){
      for(int i = 7; i >= 0; i--){
        uint8_t bit = digitalRead(BMC_MUX_IN_74HC165_DATA);
        bitWrite(states[mux], i, bit);
        digitalWrite(BMC_MUX_IN_74HC165_CLOCK, HIGH);
        delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
        digitalWrite(BMC_MUX_IN_74HC165_CLOCK, LOW);
      }
    }
  }
  bool readPin(uint16_t t_pin){
    if(t_pin >= BMC_MAX_MUX_IN){
      return false;
    }
    return bitRead(states[t_pin>>3], t_pin & 0x07);
  }

};
#endif
#endif
