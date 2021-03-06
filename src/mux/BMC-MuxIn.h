/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_IN_H
#define BMC_MUX_IN_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_IN > 0

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  #include "mux/BMC-MuxIn74HC165.h"
#endif

#ifndef BMC_MUX_IN_DELAY_MICROS
  #define BMC_MUX_IN_DELAY_MICROS 500
#endif

#if BMC_MAX_MUX_IN > 32
  #define BMC_MAX_MUX_IN_ARR 2
#else
  #define BMC_MAX_MUX_IN_ARR 1
#endif

class BMCMuxIn {
private:
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
  uint32_t states[BMC_MAX_MUX_IN_ARR];
#elif BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  BMCMuxIn74HC165 mux;
#endif

#if BMC_MUX_IN_CHIPSET != BMC_MUX_IN_CHIPSET_OTHER
  elapsedMicros timer;
#endif

  uint8_t parsePinNumber(uint8_t t_pin){
    t_pin -= (BMC_MAX_MUX_GPIO);
    return constrain(t_pin, 0, (BMC_MAX_MUX_IN-1));
  }
public:
  BMCMuxIn(){

  }
  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxIn::begin()");

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
      BMC_PRINTLN("");
      BMC_PRINTLN("BMC MUX IN set to use a chip other than the MCP23017, MCP23018 or 74HC165.");
      BMC_PRINTLN("You must read the chip with your sketch and use bmc.setMuxInValues() to set the states of the pins used.");
      BMC_PRINTLN("");
      for(uint8_t i=0;i<BMC_MAX_MUX_IN_ARR;i++){
        states[i] = 0xFFFFFFFF;
      }

#else
      mux.begin();
      delay(50);
      mux.update();
      timer = 0;
#endif
    BMC_PRINTLN("");
  }

  void update(){
#if BMC_MUX_IN_CHIPSET != BMC_MUX_IN_CHIPSET_OTHER
    if(timer >= BMC_MUX_IN_DELAY_MICROS){
      mux.update();
      timer = 0;
    }
#endif
  }

  bool getPinValue(uint8_t t_pin){
    t_pin = parsePinNumber(t_pin);

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
  #if BMC_MAX_MUX_IN > 32
      if(t_pin>=32){
        return bitRead(states[1], (t_pin-32));
      }
  #endif
    return bitRead(states[0], t_pin);
#else

  #if BMC_MAX_MUX_IN > 32
      if(t_pin>=32){
        return bitRead(mux.read33To64(), (t_pin-32));
      }
  #endif
    return bitRead(mux.read1To32(), t_pin);
#endif
  }

  uint32_t getPinValues1To32(){
    return mux.read1To32();
  }

#if BMC_MAX_MUX_IN > 32
  uint32_t getPinValues33To64(){
    return mux.read33To64();
  }
#endif
  // for custom chip only
  void setPinValues1To32(uint32_t t_states){
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
    states[0] = t_states;
#endif
  }
  // for custom chip only
  void setPinValues33To64(uint32_t t_states){
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER && BMC_MAX_MUX_IN > 32
    states[1] = t_states;
#endif
  }

  void setPinValues(uint8_t t_pin, bool t_value){
    t_pin = parsePinNumber(t_pin);
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
    uint8_t mux = (uint8_t) (t_pin/32);
    uint8_t pin = t_pin-(mux*32);
    bitWrite(states[mux], pin, t_value);
#endif
  }
};
#endif
#endif
