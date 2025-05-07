/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  The BMC Encoder class only keeps track of weather an Encoder has been rotated
  clockwise (up) or counter-clockwise (down) then BMC handles what to do
  in either case, this way the BMC class can keep track of the value (and type)
  that the encoder is changing.
*/
#ifndef BMC_ENCODER_H
#define BMC_ENCODER_H

#include "utility/BMC-Def.h"
#include "devices/physical/encoders/BMC-StateMachine.h"


// BMC expects encoders to be active LOW by default pinMode is set to INPUT
// to match the common encoder boards sold on amazon which already have pullup resistors,
// but you can also use the built-in pullup resistor on teensy if you want to
// wire your encoder directly to pins, if you want to use INPUT_PULLUP instead
// and use the built-in pullup resistor then your sketch must have
// BMC_ENCODER_INPUT_PULLUP defined, this can be done with the config file tool under Advanced.
#define BMC_ENCODER_ACTIVE LOW

#define BMC_ENCODER_FLAG_REASSIGNED 0
#define BMC_ENCODER_FLAG_ACTIVITY 1
#define BMC_ENCODER_FLAG_INCREASED 2
#define BMC_ENCODER_FLAG_TRIGGER_DOWN 3
#define BMC_ENCODER_FLAG_TRIGGER_UP 4

#define BMC_ENCODER_MUX_FLAG_A_VALUE 0
#define BMC_ENCODER_MUX_FLAG_B_VALUE 1
#define BMC_ENCODER_MUX_FLAG_A_IS_MUX 2
#define BMC_ENCODER_MUX_FLAG_B_IS_MUX 3
#define BMC_ENCODER_MUX_FLAG_IS_MUX 7

#if !defined(BMC_ENCODER_DENOISE_TIME)
  #define BMC_ENCODER_DENOISE_TIME 200
#endif

class BMCEncoder {
public:
  BMCEncoder(){
    // initialize with the pin numbers as 255
    // if either is pin is 255 it means the begin method has not been called
    pinA = 255;
    pinB = 255;
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    states.on(BMC_ENCODER_MUX_FLAG_A_VALUE);
    states.on(BMC_ENCODER_MUX_FLAG_B_VALUE);
    states.off(BMC_ENCODER_MUX_FLAG_A_IS_MUX);
    states.off(BMC_ENCODER_MUX_FLAG_B_IS_MUX);
    states.off(BMC_ENCODER_MUX_FLAG_IS_MUX);
#endif
    reset();
  }
  void begin(uint8_t t_pinA, uint8_t t_pinB){
    if(pinA != 255 && pinB != 255){
      return;
    }
    if((t_pinA == 255 || t_pinB == 255) || t_pinA == t_pinB){
      BMC_ERROR(
        "PINS:", t_pinA, "and" ,t_pinB,
        "are invalid, make sure you check that the pins were defined in your config"
      );
      BMC_HALT();
    }
    reset();
    pinA = t_pinA;
    pinB = t_pinB;

    stateMachine.begin();


#if defined(BMC_MUX_INPUTS_AVAILABLE)
    checkMuxPin(pinA, BMC_ENCODER_MUX_FLAG_A_IS_MUX);
    checkMuxPin(pinB, BMC_ENCODER_MUX_FLAG_A_IS_MUX);
#else
    setupPin(pinA);
    setupPin(pinB);
#endif
    BMC_PRINTLN("BMCEncoder Pin A:", pinA, "/ Pin B:", pinB);
  }

  void reassign(uint8_t t_settings){
    flags.reset();
    flags.on(BMC_ENCODER_FLAG_REASSIGNED);
    setMode(bitRead(t_settings, 1));
    setFastTurnThreshold((t_settings >> 2) & 0x03);
  }

  // read the ENCODER, return true if it was rotated in either direction
  bool update(){
    if(stateMachine.update(readA(), readB())){
      output = stateMachine.read();
      flags.on(BMC_ENCODER_FLAG_ACTIVITY);
      flags.write(BMC_ENCODER_FLAG_INCREASED, (output > 0));
      return true;
    }
    output = 0;
    flags.off(BMC_ENCODER_FLAG_ACTIVITY);
    return false;
  }

  bool increased(){
    return flags.read(BMC_ENCODER_FLAG_INCREASED);
  }

  uint8_t getTicks(){
    return stateMachine.getTicks();
  }

  // * API
  // detent of no detent
  void setMode(uint8_t m){
    stateMachine.setMode(m & 0x01);
  }
  // 0 to 3, each multiplied by 1000
  void setFastTurnThreshold(uint8_t value){
    value = constrain(value, 0, 3);
    stateMachine.setFastTurnThreshold(value * 1000);
  }

  void checkTrigger(){
    if(flags.toggleIfTrue(BMC_ENCODER_FLAG_TRIGGER_DOWN)){
      output = 1;
    } else if(flags.toggleIfTrue(BMC_ENCODER_FLAG_TRIGGER_UP)){
      output = -1;
    }
  }

  void triggerDown(){
    flags.on(BMC_ENCODER_FLAG_TRIGGER_DOWN);
  }

  void triggerUp(){
    flags.on(BMC_ENCODER_FLAG_TRIGGER_UP);
  }

#if defined(BMC_MUX_INPUTS_AVAILABLE)
  uint8_t getMuxPin(uint8_t _pin){
    if(_pin==0){
      return (pinA>=64) ? pinA-64 : 0;
    }
    return (pinB>=64) ? pinB-64 : 0;
  }

  void setMuxValue(uint8_t _pin, bool value){
    if(isMux(_pin)){
      states.write(_pin, value);
    }
  }

  bool isMux(uint8_t _pin){
    return states.read(BMC_ENCODER_MUX_FLAG_A_IS_MUX + (_pin&0x01));
  }

  bool hasMux(){
    return states.read(BMC_ENCODER_MUX_FLAG_IS_MUX);
  }
#endif


private:
  BMCFlags <uint8_t> flags;
  uint8_t pinA = 255;
  uint8_t pinB = 255;
  int8_t output;
  BMCEncoderStateMachine stateMachine;

#if defined(BMC_MUX_INPUTS_AVAILABLE)
  BMCFlags <uint8_t> states;
  
  void checkMuxPin(uint8_t t_pin, uint8_t t_bit){
    if(t_pin >= 64){
      if(!BMCBuildData::isMuxInputPin(t_pin)){
        BMC_ERROR(
          "Mux Pin:", t_pin,
          "Can NOT be used with Encoders as it is NOT a valid Mux In"
        );
        BMC_HALT();
      }
      states.on(t_bit);
      states.on(BMC_ENCODER_MUX_FLAG_IS_MUX);
    } else {
      setupPin(t_pin);
    }
  }
#endif

  bool readA(){
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    if(pinA >= 64){
      return states.read(BMC_ENCODER_MUX_FLAG_A_VALUE);
    }
#endif
    return (digitalRead(pinA) == BMC_ENCODER_ACTIVE);
  }

  bool readB(){
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    if(pinB >= 64){
      return states.read(BMC_ENCODER_MUX_FLAG_B_VALUE);
    }
#endif
    return (digitalRead(pinB) == BMC_ENCODER_ACTIVE);
  }

  void setupPin(uint8_t _pin){
    // check if the pins are Digital capable
    if(!BMCBuildData::isDigitalPin(_pin)){
      BMC_ERROR(
        "PIN:", _pin,
        "Can NOT be used with Encoders as it is NOT Digital capable"
      );
      BMC_HALT();
    }
    pinMode(_pin, BMC_ENCODER_PIN_MODE);
  }
  void reset(){
    flags.reset();
    output = 0;
  }
};
#endif
