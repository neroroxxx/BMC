/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Handle reading analog multiplexer, currently only CH74HC4067 is supported
  Value passed must be 10-bits
*/
#ifndef BMC_MUX_IN_ANALOG_H
#define BMC_MUX_IN_ANALOG_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_IN_ANALOG > 0

#if (BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067 || BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051)
  #include "hardware/BMC-MuxInAnalog74HC40XX.h"
#endif

class BMCMuxInAnalog {
private:
#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_OTHER
  uint16_t values[BMC_MAX_MUX_IN_ANALOG];
#elif (BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067 || BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051)
  BMCMuxInAnalog74HC40XX mux;
#endif
  uint8_t parsePinNumber(uint8_t t_pin){
    if(t_pin>=64){
      t_pin -= (64+BMC_MAX_MUX_IN);
    }
    return constrain(t_pin, 0, (BMC_MAX_MUX_IN_ANALOG-1));
  }
public:
  BMCMuxInAnalog(){

  }
  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxInAnalog::begin()");

#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_OTHER
      BMC_PRINTLN("");
      BMC_PRINTLN("BMC MUX IN set to use a chip other than the 74HC4067 or 74HC4051.");
      BMC_PRINTLN("You must read the chip with your sketch and use bmc.setMuxInAnalogValue(pin, value) to set the values of the pins used.");
      BMC_PRINTLN("BMC will handle smoothing the analog values, make sure these are 10-bits.");
      BMC_PRINTLN("");
      memset(values, 0, BMC_MAX_MUX_IN_ANALOG);
#else
      mux.begin();
      delay(10);
      mux.update();
#endif
    BMC_PRINTLN("");
  }

  void update(){
    #if BMC_MUX_IN_ANALOG_CHIPSET != BMC_MUX_IN_ANALOG_CHIPSET_OTHER
      mux.update();
    #endif
  }

  uint16_t getPinValue(uint8_t n){
    n = parsePinNumber(n);
    if(n < BMC_MAX_MUX_IN_ANALOG){
#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_OTHER
    return values[n];
#else
    return mux.read(n);
#endif
    }
    return 0;
  }

#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_OTHER
  void setPinValue(uint8_t n, uint16_t t_value){
    n = parsePinNumber(n);
    if(n < BMC_MAX_MUX_IN_ANALOG){
      values[n] = t_value;
    }
  }
#endif

};
#endif
#endif
