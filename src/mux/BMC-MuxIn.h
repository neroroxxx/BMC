/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
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

#define BMC_MAX_MUX_IN_ARR ((BMC_MAX_MUX_IN-1) >> 3)+1

class BMCMuxIn {
private:

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
  // hold states for custom sketch code
  uint8_t states[BMC_MAX_MUX_IN_ARR];
#endif

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  // BMCMuxIn74HC165 holds the state of all pins
  BMCMuxIn74HC165 mux;
#endif

#if BMC_MUX_IN_CHIPSET != BMC_MUX_IN_CHIPSET_OTHER
  BMCElapsedMicros timer;
#endif

  uint8_t parsePinNumber(uint8_t t_pin){
    t_pin -= (BMC_MAX_MUX_GPIO);
    return constrain(t_pin, 0, (BMC_MAX_MUX_IN-1));
  }
public:
  BMCMuxIn(){}

  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxIn::begin()");

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
      BMC_PRINTLN("");
      BMC_PRINTLN("BMC MUX IN set to use a chip other than the MCP23017, MCP23018 or 74HC165.");
      BMC_PRINTLN("You must read the chip with your sketch and use bmc.setMuxInValues() to set the states of the pins used.");
      BMC_PRINTLN("");
      for(uint8_t i=0;i<BMC_MAX_MUX_IN_ARR;i++){
        states[i] = 0xFF;
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
  return bitRead(states[t_pin>>3], t_pin & 0x07);
#endif

#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_74HC165
  return mux.readPin(t_pin);
#endif
  }

  void setPinValues(uint8_t t_pin, bool t_value){
    t_pin = parsePinNumber(t_pin);
#if BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_OTHER
    bitWrite(states[t_pin>>3], t_pin & 0x07, t_value);
#endif
  }
};
#endif
#endif
