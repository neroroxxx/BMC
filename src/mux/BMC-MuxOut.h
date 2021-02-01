/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_OUT_H
#define BMC_MUX_OUT_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_OUT > 0

#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_74HC595
  #include "mux/BMC-MuxOut74HC595.h"
#endif

#ifndef BMC_MUX_OUT_DELAY_MICROS
  #define BMC_MUX_OUT_DELAY_MICROS 500
#endif

class BMCMuxOut {
private:

#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
  #if BMC_MAX_MUX_OUT > 32
    uint32_t states[2];
  #else
    uint32_t states[1];
  #endif
#elif BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_74HC595
  BMCMuxOut74HC595 mux;
#endif

  uint8_t parsePinNumber(uint8_t t_pin){
    t_pin -= (BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN);
    return constrain(t_pin, 0, (BMC_MAX_MUX_OUT-1));
  }
public:
  BMCMuxOut(){

  }
  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxOut::begin()");

#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
      BMC_PRINTLN("");
      BMC_PRINTLN("BMC MUX OUT set to use a chip other than the 74HC595.");
      BMC_PRINTLN("");
      states[0] = 0xFFFFFFFF;
      #if BMC_MAX_MUX_OUT > 32
        states[1] = 0xFFFFFFFF;
      #endif
#else
      mux.begin();
      delay(50);
      mux.update();
#endif
    BMC_PRINTLN("");
  }

  void update(){
#if BMC_MUX_OUT_CHIPSET != BMC_MUX_OUT_CHIPSET_OTHER
    mux.update();
#endif
  }
  void test(uint8_t t_pin){
    t_pin = parsePinNumber(t_pin);
#if BMC_MUX_OUT_CHIPSET != BMC_MUX_OUT_CHIPSET_OTHER
    mux.test(t_pin);
#endif
  }

  void setPinValue(uint8_t t_pin, bool on){
    t_pin = parsePinNumber(t_pin);
#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
    uint8_t mux = (uint8_t) (t_pin/32);
    uint8_t pin = t_pin-(mux*32);
    bitWrite(states[mux], pin, on);
#elif BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_74HC595
    mux.writePin(t_pin, on);
#endif
  }
  // for custom chips only
  void setPinValues1To32(uint32_t t_states){
#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
    states[0] = t_states;
#endif
  }
  // for custom chips only
  void setPinValues33To64(uint32_t t_states){
#if BMC_MAX_MUX_OUT > 32
  #if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
    states[1] = t_states;
  #endif
#endif
  }

  bool getPinValue(uint8_t t_pin){
    t_pin = parsePinNumber(t_pin);
#if BMC_MUX_OUT_CHIPSET == BMC_MUX_OUT_CHIPSET_OTHER
  #if BMC_MAX_MUX_OUT > 32
      if(t_pin>=32){
        return bitRead(states[1], (t_pin-32));
      }
  #endif
    return bitRead(states[0], t_pin);
#else

    return mux.getPinState(t_pin);
#endif
  }



};
#endif
#endif
