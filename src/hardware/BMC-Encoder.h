/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  most of this code comes from
  http://www.mathertel.de/Arduino
  by Matthias Hertel

  The BMC Encoder class only keeps track of weather an Encoder has been rotated
  clockwise (up) or counter-clockwise (down) then BMC handles what to do
  in either case, this way the BMC class can keep track of the value (and type)
  that the encoder is changing.


*/
#ifndef BMC_ENCODER_H
#define BMC_ENCODER_H

#include "utility/BMC-Def.h"

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

class BMCEncoder {
public:
  BMCEncoder(){
    // initialize with the pin numbers as 255
    // if either is pin is 255 it means the begin method has not been called
    pinA = 255;
    pinB = 255;
#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
    states.on(BMC_ENCODER_MUX_FLAG_A_VALUE);
    states.on(BMC_ENCODER_MUX_FLAG_B_VALUE);
    states.off(BMC_ENCODER_MUX_FLAG_A_IS_MUX);
    states.off(BMC_ENCODER_MUX_FLAG_B_IS_MUX);
    states.off(BMC_ENCODER_MUX_FLAG_IS_MUX);
#endif
    reset();
  }
  void begin(uint8_t t_pinA, uint8_t t_pinB){
    if(pinA!=255 && pinB!=255){
      return;
    }
    if((t_pinA==255 || t_pinB==255) || t_pinA == t_pinB){
      BMC_ERROR(
        "PINS:", t_pinA, "and" ,t_pinB,
        "are invalid, make sure you check that the pins were defined in your config"
      );
      BMC_HALT();
    }
    reset();
    pinA = t_pinA;
    pinB = t_pinB;


#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
    if(pinA>=64){
      if(!BMCBuildData::isMuxInPin(pinA)){
        BMC_ERROR(
          "Mux Pin:", pinA,
          "Can NOT be used with Encoders as it is NOT a valid Mux In"
        );
        BMC_HALT();
      }
      states.on(BMC_ENCODER_MUX_FLAG_A_IS_MUX);
      states.on(BMC_ENCODER_MUX_FLAG_IS_MUX);
    } else {
      setupPin(pinA);
    }
    if(pinB>=64){
      if(!BMCBuildData::isMuxInPin(pinB)){
        BMC_ERROR(
          "Mux Pin:", pinB,
          "Can NOT be used with Encoders as it is NOT a valid Mux In"
        );
        BMC_HALT();
      }
      states.on(BMC_ENCODER_MUX_FLAG_B_IS_MUX);
      states.on(BMC_ENCODER_MUX_FLAG_IS_MUX);
    } else {
      setupPin(pinB);
    }
#else
    setupPin(pinA);
    setupPin(pinB);
#endif


  }
  void reassign(){
    flags.reset();
    flags.on(BMC_ENCODER_FLAG_REASSIGNED);
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
  // read the ENCODER, return true if it was rotated in either direction
  bool update(){
    // read the ENCODER
    tick();

    // check if the encoder was triggered externally
    checkTrigger();

    // BMCEncoder will always keep the encoder at 0
    // with values ranging from -1, 0, 1
    // if it reads 1 it has been increase,
    // if it reads -1 it has been decreased
    if(output != 0){
      //BMC_PRINTLN(output, readB(), readA());
      flags.on(BMC_ENCODER_FLAG_ACTIVITY);
      flags.write(BMC_ENCODER_FLAG_INCREASED,(output>0));
      return true;
    }
    flags.off(BMC_ENCODER_FLAG_INCREASED);
    flags.off(BMC_ENCODER_FLAG_ACTIVITY);
    return false;
  }
  bool increased(){
    return flags.read(BMC_ENCODER_FLAG_INCREASED);
  }

#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
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
#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
  BMCFlags <uint8_t> states;
#endif

int8_t lastState;
int8_t newState;
int8_t output;

const int8_t lookupTable[16] = {
   0,-1,  1,  0,
   1, 0,  0, -1,
  -1, 0,  0,  1,
   0, 1, -1,  0
};
void tick(){
  output = 0;
  uint8_t now = (readA() << 1) | readB();
  if(lastState != now){
    newState += lookupTable[now | (lastState<<2)];
    if(now == 3){
      output = (newState >> 2) + (lastState>>1);
      newState = 0;
    }
    lastState = now;
  }
}
  bool readA(){
#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
    if(pinA >= 64){
      return states.read(BMC_ENCODER_MUX_FLAG_A_VALUE);
    }
#endif
    return (digitalRead(pinA)==BMC_ENCODER_ACTIVE);
  }
  bool readB(){
#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
    if(pinB >= 64){
      return states.read(BMC_ENCODER_MUX_FLAG_B_VALUE);
    }
#endif
    return (digitalRead(pinB)==BMC_ENCODER_ACTIVE);
  }
  int8_t getPosition(){
    return output;
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
    lastState = 3;
    //newState = 0;
    output = 0;
  }
};
#endif
