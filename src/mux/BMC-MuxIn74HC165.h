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

#if BMC_MAX_MUX_IN > 64
  #undef BMC_MAX_MUX_IN
  #define BMC_MAX_MUX_IN 64
#endif

#if BMC_MAX_MUX_IN >= 1 && BMC_MAX_MUX_IN <= 8
  #define BMC_MUX_IN_CHIP_COUNT 1
  #define BMC_MUX_IN_CHIP_STATES 4
#elif BMC_MAX_MUX_IN >= 9 && BMC_MAX_MUX_IN <= 16
  #define BMC_MUX_IN_CHIP_COUNT 2
  #define BMC_MUX_IN_CHIP_STATES 4
#elif BMC_MAX_MUX_IN >= 17 && BMC_MAX_MUX_IN <= 24
  #define BMC_MUX_IN_CHIP_COUNT 3
  #define BMC_MUX_IN_CHIP_STATES 4
#elif BMC_MAX_MUX_IN >= 25 && BMC_MAX_MUX_IN <= 32
  #define BMC_MUX_IN_CHIP_COUNT 4
  #define BMC_MUX_IN_CHIP_STATES 4
#elif BMC_MAX_MUX_IN >= 33 && BMC_MAX_MUX_IN <= 40
  #define BMC_MUX_IN_CHIP_COUNT 5
  #define BMC_MUX_IN_CHIP_STATES 8
#elif BMC_MAX_MUX_IN >= 41 && BMC_MAX_MUX_IN <= 48
  #define BMC_MUX_IN_CHIP_COUNT 6
  #define BMC_MUX_IN_CHIP_STATES 8
#elif BMC_MAX_MUX_IN >= 49 && BMC_MAX_MUX_IN <= 56
  #define BMC_MUX_IN_CHIP_COUNT 7
  #define BMC_MUX_IN_CHIP_STATES 8
#elif BMC_MAX_MUX_IN >= 57 && BMC_MAX_MUX_IN <= 64
  #define BMC_MUX_IN_CHIP_COUNT 8
  #define BMC_MUX_IN_CHIP_STATES 8
#endif

class BMCMuxIn74HC165 {
private:
  uint8_t states[BMC_MUX_IN_CHIP_STATES];

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

    for(uint8_t mux = 0; mux < BMC_MUX_IN_CHIP_COUNT; mux++){
      for(int i = 7; i >= 0; i--){
        uint8_t bit = digitalReadFast(BMC_MUX_IN_74HC165_DATA);
        bitWrite(states[mux], i, bit);

        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, HIGH);
        delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, LOW);
      }
    }
  }

  void update2(){
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
            bitWrite(states[1], bitN-33, bit);
          } else {
            bitWrite(states[0], bitN-1, bit);
          }
        #else
          bitWrite(states[0], bitN-1, bit);
        #endif

        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, HIGH);
        delayMicroseconds(BMC_MUX_IN_74HC165_DELAY);
        digitalWriteFast(BMC_MUX_IN_74HC165_CLOCK, LOW);
      }
    }
  }

  uint32_t read1To32(){
    return (states[3]<<24)|(states[2]<<16)|(states[1]<<8)|states[0];
  }

#if BMC_MAX_MUX_IN > 32
  uint32_t read33To64(){
    return (states[7]<<24)|(states[6]<<16)|(states[5]<<8)|states[4];
  }
#endif

#if BMC_MAX_MUX_IN > 32
  uint32_t read(uint8_t n=0){
    if(n==0){
      return read1To32();
    }
    return read33To64();
  }
#else
  uint32_t read(){
    return read1To32();
  }
#endif
};
#endif
#endif
