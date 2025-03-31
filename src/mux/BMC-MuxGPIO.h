/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Work in progress
*/
#ifndef BMC_MUX_GPIO_H
#define BMC_MUX_GPIO_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_GPIO > 0

#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP
  #include "mux/BMC-MuxGpioMcp.h"
#endif

// #if BMC_MAX_MUX_GPIO > 48
//   #define BMC_MUX_GPIO_COUNT 4
// #elif BMC_MAX_MUX_GPIO > 32
//   #define BMC_MUX_GPIO_COUNT 3
// #elif BMC_MAX_MUX_GPIO > 16
//   #define BMC_MUX_GPIO_COUNT 2
// #else
//   #define BMC_MUX_GPIO_COUNT 1
// #endif

#if BMC_MAX_MUX_GPIO == 1
  #define BMC_MUX_GPIO_COUNT 1
#else
  #define BMC_MUX_GPIO_COUNT (((BMC_MAX_MUX_GPIO - 1) >> 4) + 1)
#endif

class BMCMuxGpio {
private:

#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_OTHER
  uint16_t states[BMC_MUX_GPIO_COUNT];
#elif BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP
  BMCMuxGpioMCP mux;
#endif

  uint8_t parsePinNumber(uint8_t t_pin){
    if(t_pin>=64){
      t_pin -= 64;
    }
    return constrain(t_pin, 0, (BMC_MAX_MUX_GPIO-1));
  }
public:
  BMCMuxGpio(){

  }
  void begin(){
    BMC_PRINTLN("");
    BMC_PRINTLN("BMCMuxGpio::begin()");

#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_OTHER
    BMC_PRINTLN("");
    BMC_PRINTLN("BMC MUX OUT set to use a chip other than the MCP23017.");
    BMC_PRINTLN("");
    for(uint8_t i=0;i<BMC_MUX_GPIO_COUNT;i++){
      states[i] = 0;
    }
#else
    mux.begin();
    delay(10);
    mux.update();
#endif
    BMC_PRINTLN("");
  }

  void update(){
#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP
    mux.update();
#endif
  }
  void test(uint8_t t_pin){
    if(t_pin < BMC_MAX_MUX_GPIO){
      mux.test(t_pin);
    }
  }
  void setupPin(uint8_t t_pin, uint8_t t_mode){
    if(t_pin < BMC_MAX_MUX_GPIO){
      mux.setupPin(t_pin, t_mode);
    }
  }
  bool readPin(uint8_t t_pin){
    if(t_pin < BMC_MAX_MUX_GPIO){
#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_OTHER
      // uint8_t mux = (uint8_t) (t_pin/16);
      // uint8_t pin = t_pin-(mux*16);
      // return bitRead(states[mux], pin);
      bitRead(states[t_pin>>4], t_pin & 0x0F);
#elif BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP
      return mux.readPin(t_pin);
#endif
    }
    return false;
  }
  void writePin(uint8_t t_pin, bool t_value){
    if(t_pin < BMC_MAX_MUX_GPIO){
#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_OTHER
      // uint8_t mux = (uint8_t) (t_pin/16);
      // uint8_t pin = t_pin-(mux*16);
      // bitWrite(states[mux], pin, t_value);
      bitWrite(states[(t_pin>>4) & 0x0F], t_pin & 0x0F, t_value);
#elif BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP
      mux.writePin(t_pin, t_value);
#endif
    }
  }
  bool getPinValue(uint8_t t_pin){
    return readPin(t_pin);
  }
  void setPinValue(uint8_t t_pin, bool t_value){
    writePin(t_pin, t_value);
  }



};
#endif
#endif
