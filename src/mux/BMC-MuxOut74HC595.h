/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Control up to 4 74HC595, these are 8 pin multiplexers and they must have a
  pullup resistor on each pin, 10k should work
*/
#ifndef BMC_MUX_OUT_74HC595_H
#define BMC_MUX_OUT_74HC595_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_OUT > 0 && BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_74HC595

#ifndef BMC_MUX_OUT_74HC595_CLOCK
  #error "BMC_MUX_OUT_74HC595_CLOCK was NOT defined"
#elif BMC_MUX_OUT_74HC595_CLOCK >= 64
  #error "BMC_MUX_OUT_74HC595_CLOCK is not a valid pin"
#endif

#ifndef BMC_MUX_OUT_74HC595_LATCH
  #error "BMC_MUX_OUT_74HC595_LATCH was NOT defined"
#elif BMC_MUX_OUT_74HC595_LATCH >= 64
  #error "BMC_MUX_OUT_74HC595_LATCH is not a valid pin"
#endif

#ifndef BMC_MUX_OUT_74HC595_DATA
  #error "BMC_MUX_OUT_74HC595_DATA was NOT defined"
#elif BMC_MUX_OUT_74HC595_DATA >= 64
  #error "BMC_MUX_OUT_74HC595_DATA is not a valid pin"
#endif

#define BMC_MUX_OUT_74HC595_DELAY 0

#define BMC_MUX_OUT_74HC595_FLAG_CHANGED 0

#if BMC_MAX_MUX_OUT > 32
  #define BMC_74HC595_MUX_ARR_LEN 2
#else
  #define BMC_74HC595_MUX_ARR_LEN 1
#endif

#define BMC_74HC595_MUX_COUNT (ceil(BMC_MAX_MUX_OUT/8))

class BMCMuxOut74HC595 {
private:
  BMCFlags <uint8_t> flags;
  uint8_t states[BMC_74HC595_MUX_ARR_LEN];

  void _updateMuxReverse(){
    for(int mux = BMC_74HC595_MUX_COUNT-1; mux >= 0; mux--){
      for(uint8_t mask=0x80; mask; mask >>= 1){
        _writeToMux(mux, mask);
      }
    }
  }
  void _updateMux(){
    for(int mux = 0; mux < BMC_74HC595_MUX_COUNT; mux++){
      for(uint8_t mask=0x80; mask; mask >>= 1){
        _writeToMux(mux, mask);
      }
    }
  }
  void _writeToMux(uint8_t mux, uint8_t mask){
    digitalWrite(BMC_MUX_OUT_74HC595_DATA, (states[mux] & mask));
    digitalWrite(BMC_MUX_OUT_74HC595_CLOCK, HIGH);
  #if BMC_MUX_OUT_74HC595_DELAY > 0
    delayMicroseconds(BMC_MUX_OUT_74HC595_DELAY);
  #endif
    digitalWrite(BMC_MUX_OUT_74HC595_CLOCK, LOW);
    digitalWrite(BMC_MUX_OUT_74HC595_DATA, LOW);
  }

public:
  BMCMuxOut74HC595(){}
  void begin(){
    BMC_PRINTLN("BMCMuxOut74HC595::begin()");
    pinMode(BMC_MUX_OUT_74HC595_CLOCK, OUTPUT);
    pinMode(BMC_MUX_OUT_74HC595_LATCH, OUTPUT);
    pinMode(BMC_MUX_OUT_74HC595_DATA, OUTPUT);

#ifdef BMC_MUX_OUT_74HC595_PWM
    #if BMC_MUX_OUT_74HC595_PWM < 64
      if(!BMCBuildData::isPwmPin(BMC_MUX_OUT_74HC595_PWM)){
        BMC_ERROR(
          "PIN:", BMC_MUX_OUT_74HC595_PWM,
          "Can NOT be used with to for 74HC595 PWM as it's not PWM capable."
        );
        BMC_HALT();
      }
      pinMode(BMC_MUX_OUT_74HC595_PWM, OUTPUT);
      uint8_t maxBrightness = map(BMC_LED_PWM_MAX_VALUE, 0, 255, 255, 0);
      analogWrite(BMC_MUX_OUT_74HC595_PWM, maxBrightness);
    #endif
#endif

    digitalWrite(BMC_MUX_OUT_74HC595_CLOCK, LOW);
    digitalWrite(BMC_MUX_OUT_74HC595_LATCH, HIGH);

    flags.on(BMC_MUX_OUT_74HC595_FLAG_CHANGED);
  }
  void update(){
    if(flags.toggleIfTrue(BMC_MUX_OUT_74HC595_FLAG_CHANGED)){
      // set load pin
      digitalWrite(BMC_MUX_OUT_74HC595_LATCH, LOW);
      digitalWrite(BMC_MUX_OUT_74HC595_DATA, LOW);
      if(BMC_74HC595_MUX_COUNT>1){
        _updateMuxReverse();
      } else {
        _updateMux();
      }
      digitalWrite(BMC_MUX_OUT_74HC595_LATCH, HIGH);
    }
  }
  void test(uint8_t t_pin){
    // hold the current state
    bool currentState = getPinState(t_pin);

    for(uint8_t i=0;i<3;i++){
      // now tell the update function that a change has happened
      //flags.on(BMC_MUX_OUT_74HC595_FLAG_CHANGED);
      writePin(t_pin, !currentState);
      update();
      delay(BMC_MAX_LED_TEST_DELAY);

      //flags.on(BMC_MUX_OUT_74HC595_FLAG_CHANGED);
      writePin(t_pin, currentState);
      update();
      delay(BMC_MAX_LED_TEST_DELAY);
    }
  }
  // expects a zero-index value
  void writePin(uint8_t t_pin, bool on){
    uint8_t muxIndex = (uint8_t)floor(t_pin/8.0);
    if(muxIndex>0){
      t_pin -= (muxIndex*8);
    }
    if(bitRead(states[muxIndex], t_pin) != on){
      flags.on(BMC_MUX_OUT_74HC595_FLAG_CHANGED);
    }
    bitWrite(states[muxIndex], t_pin, on);
  }
  // expects a zero-index value
  bool getPinState(uint8_t t_pin){
    uint8_t muxIndex = (uint8_t)floor(t_pin/8.0);
    if(muxIndex>0){
      t_pin -= (muxIndex*8);
    }
    return bitRead(states[muxIndex], t_pin);
  }


};
#endif
#endif
