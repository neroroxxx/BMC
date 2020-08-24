/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_IN_MCP2301X_H
#define BMC_MUX_IN_MCP2301X_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_IN > 0 && BMC_MUX_IN_CHIPSET == BMC_MUX_IN_CHIPSET_MCP2301X

// pin mode
#define BMC_MCP2301X_IO_MODE 0x00
// Interrupts
#define BMC_MCP2301X_INT_ENABLE 0x04
#define BMC_MCP2301X_DEFAULT_VALUE 0x06
#define BMC_MCP2301X_INT_CONFIG 0x08
#define BMC_MCP2301X_IO_CONFIG 0x0A
// pullups
#define BMC_MCP2301X_PULLUP 0x0C
// read
#define BMC_MCP2301X_IO 0x12

#include <Wire.h>

class BMCMuxInMCP2301x {
public:
  BMCMuxInMCP2301x(){}
  void begin(){
    BMC_PRINTLN("Mux In Using MCP23017/MCP23018");
    Wire.begin();
    Wire.setClock(BMC_I2C_FREQ);
    setupPins(BMC_MUX_IN_ADDR_1);

    #if defined(BMC_MUX_IN_ADDR_2) && BMC_MAX_MUX_IN > 16
      setupPins(BMC_MUX_IN_ADDR_2);

      #if defined(BMC_MUX_IN_ADDR_3) && BMC_MAX_MUX_IN > 32
        setupPins(BMC_MUX_IN_ADDR_3);

        #if defined(BMC_MUX_IN_ADDR_4) && BMC_MAX_MUX_IN > 48
          setupPins(BMC_MUX_IN_ADDR_4);
        #endif
      #endif
    #endif
  }
  void setupPins(uint8_t addr){
    // set all pins of first MCP2301X as inputs
    writeData(addr, BMC_MCP2301X_IO_MODE, 0xFF);
    writeData(addr, BMC_MCP2301X_IO_MODE+1, 0xFF);

    // set all pins of first MCP2301X to use built-in pullup
    // if you have external pullup resistors then set 0xFF to 0 on both
    writeData(addr, BMC_MCP2301X_PULLUP, 0xFF);
    writeData(addr, BMC_MCP2301X_PULLUP+1, 0xFF);
  }

  void update(){
    readAllPins();
  }


  uint32_t read1To32(){
    return states;
  }
#if BMC_MAX_MUX_IN > 32
  uint32_t read33To64(){
    return states2;
  }
#endif

private:
  uint32_t states = 0;
#if BMC_MAX_MUX_IN > 32
  uint32_t states2 = 0;
#endif
  void readAllPins(){
    states = readPins(BMC_MUX_IN_ADDR_1);

    #if defined(BMC_MUX_IN_ADDR_2) && BMC_MAX_MUX_IN > 16
      states = (readPins(BMC_MUX_IN_ADDR_2)<<16) | states;
    #endif

    #if defined(BMC_MUX_IN_ADDR_3) && BMC_MAX_MUX_IN > 32
      states2 = readPins(BMC_MUX_IN_ADDR_3);

      #if defined(BMC_MUX_IN_ADDR_4) && BMC_MAX_MUX_IN > 48
        states2 = (readPins(BMC_MUX_IN_ADDR_4)<<16) | states2;
      #endif
    #endif
  }
  void writeData(uint8_t t_chipAddr, uint8_t t_reg, uint8_t t_value){
    Wire.beginTransmission(t_chipAddr);
    Wire.write((uint8_t) t_reg);
    Wire.write((uint8_t) t_value);
  	Wire.endTransmission();
  }
  uint8_t readData(uint8_t t_chipAddr, uint8_t t_reg){
    Wire.beginTransmission(t_chipAddr);
    Wire.write((uint8_t) t_reg);
    Wire.endTransmission();

    Wire.requestFrom((int) t_chipAddr, (int) 1);
    return Wire.read();
  }
  uint16_t readPins(uint8_t t_chipAddr){
    Wire.beginTransmission(t_chipAddr);
    Wire.write((uint8_t) BMC_MCP2301X_IO);
  	Wire.endTransmission();
    // request 2 bytes
    // always read both ports A and B
    Wire.requestFrom((int) t_chipAddr, (int) 2);
    uint8_t a = Wire.read();
    uint8_t b = Wire.read();
    return (uint16_t) ((b << 8) | a);
  }

};
#endif
#endif
