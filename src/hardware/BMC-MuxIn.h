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

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_MCP2301X
  #include "hardware/BMC-MuxInMCP2301x.h"
#elif BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  #include "hardware/BMC-MuxIn74HC165.h"
#endif

#ifndef BMC_MUX_IN_DELAY_MICROS
  #define BMC_MUX_IN_DELAY_MICROS 500
#endif

class BMCMuxIn {
private:
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
  uint32_t states = 0;
  #if BMC_MAX_MUX_IN > 32
    uint32_t states2 = 0;
  #endif
#elif BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_MCP2301X
  BMCMuxInMCP2301x mux;
#elif BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  BMCMuxIn74HC165 mux;
#endif

#if BMC_MUX_IN_CHIPSET != BMC_MUX_IN_CHIPSET_OTHER
  elapsedMicros timer;
#endif

  uint8_t parsePinNumber(uint8_t t_pin){
    if(t_pin>=64){
      t_pin -= 64;
    }
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
      states = 0xFFFFFFFF;
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
        return bitRead(states2, (t_pin-32));
      }
  #endif
    return bitRead(states, t_pin);
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
    states = t_states;
#endif
  }
  // for custom chip only
  void setPinValues33To64(uint32_t t_states){
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER && BMC_MAX_MUX_IN > 32
    states2 = t_states;
#endif
  }

  void setPinValues(uint8_t t_pin, bool t_value){
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
    t_pin = parsePinNumber(t_pin);
    if(t_pin<BMC_MAX_MUX_IN){

#if BMC_MAX_MUX_IN > 32
      if(t_pin>=32){
        return bitRead(states2, (t_pin-32));
      }
#endif

      bitWrite(states, t_pin, t_value);
    }
#endif
  }
};
#endif
#endif
