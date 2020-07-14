/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
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

#define BMC_MUX_IN_74HC165_1MS_READ


#define BMC_MUX_IN_74HC165_DELAY 5


class BMCMuxIn74HC165 {
private:
  uint32_t states = 0;
#if BMC_MAX_MUX_IN > 32
  uint32_t states2 = 0;
#endif

public:
  BMCMuxIn74HC165(){}
  void begin(){
    BMC_PRINTLN("BMCMuxIn74HC165::begin()");
    pinMode(BMC_MUX_IN_74HC165_CLOCK, OUTPUT);
    pinMode(BMC_MUX_IN_74HC165_LOAD, OUTPUT);
    pinMode(BMC_MUX_IN_74HC165_DATA, INPUT);
    digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, LOW);
    digitalWriteFast(BMC_MUX_IN_74HC165_LOAD, HIGH);
  }
  void update(){
    // set load pin
    digitalWriteFast(BMC_MUX_IN_74HC165_LOAD, LOW);
    delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
    digitalWriteFast(BMC_MUX_IN_74HC165_LOAD, HIGH);
    // total number of 74HC165 chips, each chip has 8 inputs and we have to
    // read all even if you aren't using all pins.
    uint8_t total = (ceil(BMC_MAX_MUX_IN/8.0) * 8);
    for(uint8_t mux = 0, n=total/8; mux < n; mux++){
      for(int i = 7, bitN = ((mux + 1) * 8); i >= 0; i--, bitN--){
        uint8_t bit = digitalReadFast(BMC_MUX_IN_74HC165_DATA);

        #if BMC_MAX_MUX_IN > 32
          if(bitN>=32){
            // states2 starting with bit 0 so remove 33 from the value
            bitWrite(states2, bitN-33, bit);
          } else {
            bitWrite(states, bitN-1, bit);
          }
        #else
          bitWrite(states, bitN-1, bit);
        #endif

        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, HIGH);
        delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, LOW);
      }
    }
  }
  uint32_t read1To32(){
    return states;
  }
#if BMC_MAX_MUX_IN > 32
  uint32_t read33To64(){
    return states2;
  }
#endif


#if BMC_MAX_MUX_IN > 32

  uint32_t read(uint8_t n=0){
    return (n > 0) ? states2 : states;
  }

#else

  uint32_t read(){
    return states;
  }

#endif
};
#endif
#endif
