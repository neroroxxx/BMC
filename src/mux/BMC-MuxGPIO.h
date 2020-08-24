/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
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

#if BMC_MAX_MUX_GPIO > 32
  #define BMC_MUX_GPIO_COUNT 2
#else
  #define BMC_MUX_GPIO_COUNT 1
#endif

class BMCMuxGpio {
private:
#if BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_OTHER
  uint32_t states[BMC_MUX_GPIO_COUNT];
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
      states[i] = 0xFFFFFFFF;
    }
#else
    mux.begin();
    delay(50);
    mux.update();
#endif
    BMC_PRINTLN("");
  }

  void update(){

  }
  void test(uint8_t t_pin){

  }
  bool readPin(uint8_t t_pin){

  }
  void writePin(uint8_t t_pin, bool t_value){

  }
  bool getPinValue(uint8_t t_pin)}{

  }
  void setPinValue(uint8_t t_pin, bool t_value){

  }



};
#endif
#endif
