/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_GPIO_MCP_H
#define BMC_MUX_GPIO_MCP_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_GPIO > 0 && BMC_MUX_GPIO_CHIPSET == BMC_MUX_GPIO_CHIPSET_MCP

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



// #define BMC_MUX_GPIO_CHIP_COUNT 1

#if BMC_MAX_MUX_GPIO == 1
  #define BMC_MUX_GPIO_CHIP_COUNT 1
#else
  #define BMC_MUX_GPIO_CHIP_COUNT ((BMC_MAX_MUX_GPIO-1) >> 3)+1
#endif

// #if BMC_MUX_GPIO_CHIP_COUNT == 1
//   #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1}
// #elif BMC_MUX_GPIO_CHIP_COUNT == 2
//   #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2}
// #elif BMC_MUX_GPIO_CHIP_COUNT == 3
//   #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2, BMC_MUX_GPIO_ADDR_3}
// #elif BMC_MUX_GPIO_CHIP_COUNT == 4
//   #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2, BMC_MUX_GPIO_ADDR_3, BMC_MUX_GPIO_ADDR_4}
// #endif



// #if defined(BMC_MUX_GPIO_ADDR_2) && BMC_MAX_MUX_GPIO > 16
//   #undef BMC_MUX_GPIO_CHIP_COUNT
//   #define BMC_MUX_GPIO_CHIP_COUNT 2
//   #undef BMC_MUX_GPIO_CHIP_ADDR
//   #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2}

//   #if defined(BMC_MUX_GPIO_ADDR_3) && BMC_MAX_MUX_GPIO > 32
//     #undef BMC_MUX_GPIO_CHIP_COUNT
//     #define BMC_MUX_GPIO_CHIP_COUNT 3
//     #undef BMC_MUX_GPIO_CHIP_ADDR
//     #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2, BMC_MUX_GPIO_ADDR_3}

//     #if defined(BMC_MUX_GPIO_ADDR_4) && BMC_MAX_MUX_GPIO > 48
//       #undef BMC_MUX_GPIO_CHIP_COUNT
//       #define BMC_MUX_GPIO_CHIP_COUNT 4
//       #undef BMC_MUX_GPIO_CHIP_ADDR
//       #define BMC_MUX_GPIO_CHIP_ADDR {BMC_MUX_GPIO_ADDR_1, BMC_MUX_GPIO_ADDR_2, BMC_MUX_GPIO_ADDR_3, BMC_MUX_GPIO_ADDR_4}
//     #endif
//   #endif
// #endif



#define BMC_MUX_GPIO_FLAGS_UPDATE   0
#define BMC_MUX_GPIO_FLAGS_UPDATE_1 1
#define BMC_MUX_GPIO_FLAGS_UPDATE_2 2
#define BMC_MUX_GPIO_FLAGS_UPDATE_3 3


#include <Wire.h>

class BMCMuxGpioMCP {
public:
  BMCMuxGpioMCP(){}
  void begin(){
    BMC_PRINTLN("Mux GPIO using MCP23017/MCP23018");
    Wire.begin();
    Wire.setClock(BMC_I2C_FREQ);
    initializePins();
  }
  void initializePins(){
    // check which pins are inputs and outputs
#if BMC_MAX_BUTTONS > 0
    for(uint8_t i=0;i<BMC_MAX_BUTTONS;i++){
      uint8_t pin = BMCBuildData::getButtonPin(i);
      if(BMCBuildData::isMuxGpioPin(pin)){
        setupPin(pin, INPUT);
      }
    }
#endif
#if BMC_MAX_GLOBAL_BUTTONS > 0
    for(uint8_t i=0;i<BMC_MAX_GLOBAL_BUTTONS;i++){
      uint8_t pin = BMCBuildData::getGlobalButtonPin(i);
      if(BMCBuildData::isMuxGpioPin(pin)){
        setupPin(pin, INPUT);
      }
    }
#endif
#if BMC_MAX_ENCODERS > 0
    for(uint8_t i=0;i<BMC_MAX_ENCODERS;i++){
      uint8_t pinA = BMCBuildData::getEncoderPinA(i);
      uint8_t pinB = BMCBuildData::getEncoderPinB(i);
      if(BMCBuildData::isMuxGpioPin(pinA)){
        setupPin(pinA, INPUT);
      }
      if(BMCBuildData::isMuxGpioPin(pinB)){
        setupPin(pinB, INPUT);
      }
    }
#endif
#if BMC_MAX_GLOBAL_ENCODERS > 0
    for(uint8_t i=0;i<BMC_MAX_GLOBAL_ENCODERS;i++){
      uint8_t pinA = BMCBuildData::getGlobalEncoderPinA(i);
      uint8_t pinB = BMCBuildData::getGlobalEncoderPinB(i);
      if(BMCBuildData::isMuxGpioPin(pinA)){
        setupPin(pinA, INPUT);
      }
      if(BMCBuildData::isMuxGpioPin(pinB)){
        setupPin(pinB, INPUT);
      }
    }
#endif
#if BMC_MAX_LEDS > 0
    for(uint8_t i=0;i<BMC_MAX_LEDS;i++){
      uint8_t pin = BMCBuildData::getLedPin(i);
      if(BMCBuildData::isMuxGpioPin(pin)){
        setupPin(pin, OUTPUT);
      }
    }
#endif
#if BMC_MAX_GLOBAL_LEDS > 0
    for(uint8_t i=0;i<BMC_MAX_GLOBAL_LEDS;i++){
      uint8_t pin = BMCBuildData::getGlobalLedPin(i);
      if(BMCBuildData::isMuxGpioPin(pin)){
        setupPin(pin, OUTPUT);
      }
    }
#endif
    for(uint8_t i=0;i<BMC_MUX_GPIO_CHIP_COUNT;i++){
      // bit set to 1 is input, 0 is output
      controlSetDirection(i);
      // if bit is 0 internal pullup is off, 1 internal pullup is on
      controlSetPullup(i);
      // value for the pin
      controlSetValue(i);
    }
    delay(5);
    readAllPins();
    delay(5);
  }
  void setupPin(uint8_t t_pin, uint8_t t_mode){
    if(t_pin>=64+BMC_MAX_MUX_GPIO){
      return;
    }
    t_pin -= 64;
    // uint8_t mux = (uint8_t) (t_pin/16);
    // uint8_t pin = t_pin-(mux*16);
    uint8_t mux = (t_pin >> 4);
    uint8_t pin = t_pin & 0x0F;
    if(t_mode==OUTPUT){
      bitWrite(pinDirection[mux], pin, 0);
      bitWrite(states[mux], pin, 0);
    } else {
      // is input, BMC will always set inputs as input pullup
      bitWrite(pinDirection[mux], pin, 1);
      bitWrite(states[mux], pin, 1);
    }
  }

  void update(){
    if((flags.read()&0x0F)>0){
      // a mux has been updated so write the values only to the mux that was updated
      for(uint8_t i=0;i<BMC_MUX_GPIO_CHIP_COUNT;i++){
        if(flags.toggleIfTrue(BMC_MUX_GPIO_FLAGS_UPDATE+i)){
          controlSetValue(i);
        }
      }
    }
    readAllPins();
  }
  bool readPin(uint8_t t_pin){
    if(t_pin<BMC_MAX_MUX_GPIO){
      // uint8_t mux = (uint8_t) (t_pin/16);
      // uint8_t pin = t_pin-(mux*16);
      // // we can read inputs and outputs
      // return bitRead(states[mux], pin);
      
      // we can read inputs and outputs
      return bitRead(states[t_pin>>4], t_pin & 0x0F);
    }
    return false;
  }
  void writePin(uint8_t t_pin, bool state){
    if(t_pin>=BMC_MAX_MUX_GPIO){
      return;
    }
    // uint8_t mux = (uint8_t) (t_pin/16);
    // uint8_t pin = t_pin-(mux*16);
    uint8_t mux = (t_pin >> 4);
    uint8_t pin = t_pin & 0x0F;
    // check if pin is an output pin, we don't write to input pins.
    if(bitRead(pinDirection[mux], pin) == 0){
      // prepare to update a mux pin on the next update
      if(bitRead(states[mux], pin) != state){
        bitWrite(states[mux], pin, state);
        flags.on(BMC_MUX_GPIO_FLAGS_UPDATE+mux);
      }
    }
  }
  void test(uint8_t t_pin){
    if(t_pin>=BMC_MAX_MUX_GPIO){
      return;
    }
    bool currentState = getPinState(t_pin);

    for(uint8_t i=0;i<3;i++){
      // now tell the update function that a change has happened
      writePin(t_pin, !currentState);
      update();
      delay(BMC_MAX_LED_TEST_DELAY);

      writePin(t_pin, currentState);
      update();
      delay(BMC_MAX_LED_TEST_DELAY);
    }
  }
  bool getPinState(uint8_t t_pin){
    if(t_pin>=BMC_MAX_MUX_GPIO){
      return false;
    }
    // uint8_t mux = (uint8_t) (t_pin/16);
    // uint8_t pin = t_pin-(mux*16);
    // return bitRead(states[mux], pin);
    return bitRead(states[t_pin>>4], t_pin & 0x0F);
  }

private:
  BMCFlags <uint8_t> flags;

  // const uint8_t addrList[BMC_MUX_GPIO_CHIP_COUNT] = BMC_MUX_GPIO_CHIP_ADDR;
    const uint8_t addrList[BMC_MUX_GPIO_CHIP_COUNT] = {
      BMC_MUX_GPIO_ADDR_1
  #if BMC_MUX_GPIO_CHIP_COUNT == 2
      ,BMC_MUX_GPIO_ADDR_2
  #endif
  #if BMC_MUX_GPIO_CHIP_COUNT == 3
      ,BMC_MUX_GPIO_ADDR_3
  #endif
  #if BMC_MUX_GPIO_CHIP_COUNT == 4
      ,BMC_MUX_GPIO_ADDR_4
  #endif
    };


  uint16_t states[BMC_MUX_GPIO_CHIP_COUNT];
  uint16_t pinDirection[BMC_MUX_GPIO_CHIP_COUNT];

  void readAllPins(){
    for(uint8_t i=0;i<BMC_MUX_GPIO_CHIP_COUNT;i++){
      states[i] = readPins(addrList[i]);
    }
    /*
    states[0] = readPins(BMC_MUX_GPIO_ADDR_1);

    #if defined(BMC_MUX_GPIO_ADDR_2) && BMC_MAX_MUX_GPIO > 16
      states[1] = readPins(BMC_MUX_GPIO_ADDR_2);
    #endif

    #if defined(BMC_MUX_GPIO_ADDR_3) && BMC_MAX_MUX_GPIO > 32
      states[2] = readPins(BMC_MUX_GPIO_ADDR_3);

      #if defined(BMC_MUX_GPIO_ADDR_4) && BMC_MAX_MUX_GPIO > 48
        states[3] = readPins(BMC_MUX_GPIO_ADDR_4);
      #endif
    #endif
    */
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



  void controlSetDirection(uint8_t n){
    writeData(addrList[n], BMC_MCP2301X_IO_MODE, pinDirection[n] & 0xFF); // is input or ouput, 0 = output
    writeData(addrList[n], BMC_MCP2301X_IO_MODE+1, (pinDirection[n]>>8) & 0xFF);
  }
  void controlSetPullup(uint8_t n){
    writeData(addrList[n], BMC_MCP2301X_PULLUP, pinDirection[n] & 0xFF);
    writeData(addrList[n], BMC_MCP2301X_PULLUP+1, (pinDirection[n]>>8) & 0xFF);
  }
  void controlSetValue(uint8_t n){
    writeData(addrList[n], BMC_MCP2301X_IO, states[n] & 0xFF); // writes a state to the pin
    writeData(addrList[n], BMC_MCP2301X_IO+1, (states[n]>>8) & 0xFF);
  }

};
#endif
#endif
