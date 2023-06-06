/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_AUX_JACK_POT_H
#define BMC_AUX_JACK_POT_H
#include "utility/BMC-Def.h"

#define BMC_FLAG_AUX_JACK_POT_REASSIGNED 0
#define BMC_FLAG_AUX_JACK_POT_MUX 1
#define BMC_FLAG_AUX_JACK_POT_LOG 2
#define BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_AVAILABLE 3
#define BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE 4
#define BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE_CHANGED 5

class BMCAuxJackPot {
public:
  BMCAuxJackPot(){
    // initialize with the pin number as 255
    // if the pin is 255 it means the begin method has not been called
    pin = 255;
    flags.reset();
    reset();
  }
  // begin, if the pin value is 255 only, and t_pin is not 255
  // the BMC-Pins.h object will return 255 if the pot doesn't have a pin defined
  // this method will only work the first time it's called
  void begin(uint8_t t_pin){
    if(pin!=255){
      return;
    }
    if(t_pin==255){
      BMC_ERROR(
        "PIN:", t_pin,
        "is invalid, make sure you check that the pin was defined in your config"
      );
      BMC_HALT();
    }
    reset();
    pin = t_pin;
    // check if the pin is Analog capable
    if(!BMCBuildData::isAnalogPin(pin) || pin >= 64){
      BMC_ERROR(
        "PIN:", t_pin,
        "Can NOT be used with Pots as it is NOT Analog Capable or is a MUX pin"
      );
      BMC_HALT();
    }
    pinMode(pin, INPUT_PULLUP);
  }
  // set the calibration of the POT
  void setCalibration(uint16_t t_min, uint16_t t_max){
    uint16_t limit = 1023;
    t_min = (t_min >= limit) ? 0 : t_min;
    t_max = (t_max > limit) ? 1023 : t_max;
    if(t_min>=t_max){
      t_min = 0;
      t_max = limit;
    }
    calMin = t_min;
    calMax = t_max;
  }
  // reassign the POT behaviour, used when switching layers or the editor
  // has updated EEPROM
  void reassign(){
    reset();
    flags.on(BMC_FLAG_AUX_JACK_POT_REASSIGNED);
  }
  void assignToeSwitch(bool allow, uint8_t t_settings){
    if(allow){
      toeSwitchSettings = t_settings;
      flags.on(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_AVAILABLE);
    } else {
      toeSwitchSettings = 0;
      flags.off(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_AVAILABLE);
    }
  }
  bool toeSwitchActive(){
    if(!toeSwitchAvailable()){
      return false;
    }
    return flags.toggleIfTrue(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE_CHANGED);
  }
  bool toeSwitchAvailable(){
    return flags.read(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_AVAILABLE);
  }
  bool toeSwitchGetState(){
    return flags.read(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE);
  }
  uint8_t toeSwitchGetOffValue(){
    // use 3 bits for off value (0-2)
    return ((toeSwitchSettings & 0x07)+1)*5;
  }
  uint16_t toeSwitchGetOffSpeed(){
    // use 3 bits for off speed (3-5)
    uint8_t value = ((toeSwitchSettings>>3) & 0x07);
    return ((value+1)*100)+200;
  }
  uint8_t toeSwitchGetMode(){
    // use 2 bits for Mode (6-7)
    return (toeSwitchSettings>>6) & 0x03;
  }
  void handleToeSwitch(uint8_t lastValue){
    // toe switch timing
    if(toeSwitchAvailable()){
      switch(toeSwitchGetMode()){
        case 0:
          handleToeSwitchModeAutoEngage(lastValue);
          break;
        case 1:
          handleToeSwitchModeToeSwitch(lastValue);
          break;
      }
    }
  }
  uint8_t toeSwitchGetEvent(){
    if(toeSwitchGetState()){
      return 1;
    }
    return 2;
  }
  // default mode is AUTO-ENGAGE
  // Engage message is sent as soon as the pot is rotated past the off value
  // then once it goes back to the off value or less a timer will start that
  // once that timer is complete the off value is sent.
  // these messages are sent only once upon switch states.
  void handleToeSwitchModeAutoEngage(uint8_t lastValue){
    uint8_t offValue = toeSwitchGetOffValue();
    uint16_t offSpeed = toeSwitchGetOffSpeed();
    if(!toeSwitchGetState()){
      // engage
      if(value >= offValue){
        flags.on(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE);
        flags.on(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE_CHANGED);
        toeSwitch.stop();
      }
    } else {
      // disengage
      if(value<=offValue && value!=lastValue){
        toeSwitch.start(offSpeed);
      } else if(value>offValue){
        toeSwitch.stop();
      }
      if(toeSwitch.complete()){
        flags.off(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE);
        flags.on(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE_CHANGED);
      }
    }
  }
  // Toe Switch Mode
  // Toe switch is engaged/disengaged when the specified value is reached
  void handleToeSwitchModeToeSwitch(uint8_t lastValue){
    uint8_t trigger = (127-toeSwitchGetOffValue());
    if(value >= trigger){
      if(lastValue < trigger){
        toeSwitch.start(toeSwitchGetOffSpeed());
      }
    } else {
      toeSwitch.stop();
    }
    if(toeSwitch.complete()){
      flags.toggle(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE);
      flags.on(BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE_CHANGED);
    }
  }

  bool update(){
    // last value read
    uint8_t lastValue = value;
    // read the value of the pot mapped to range min/max
    // this reading also includes the pot's calibration
    value = readPot();
    // this is used when a layer has changed or the editor
    // has updated the EEPROM, the pot will then act as if it was turned
    // this is done to make sure that if the pot has a different event assigned
    // that event is trigger as soon as a layer has been changed or if the pot
    // was updated
    if(flags.toggleIfTrue(BMC_FLAG_AUX_JACK_POT_REASSIGNED)){
      return true;
    }
    handleToeSwitch(lastValue);
    return (lastValue != value);
  }
  // get the current reading of the pot mapped to the range min/max
  uint8_t getValue(){
    return value;
  }
  // get the actual analog reading of the pot without any mapping it to 127 max
  // used for Pot Calibration and debugging
  uint16_t getAnalogValue(){
    return analogRead(pin);
  }
  uint8_t getPin(){
    return pin;
  }
  // get the position of the pot, used by the editor
  // this may also be used to get the value without mapping the range
  // this value will always return a range of 0/127
  // the readPot() method will always store the value mapped down to the
  // specified range, here we map it back to 0-127
  uint8_t getPosition(){
    return value;
  }
  // get the calibration min
  uint16_t getCalibrationMin(){
    return calMin;
  }
  // get the calibration max
  uint16_t getCalibrationMax(){
    return calMax;
  }
private:
  BMCFlags <uint8_t> flags;
  // pot pin number, must be analog input
  uint8_t pin = 255;
  // the current value used by BMC
  uint8_t value = 0;

  uint8_t rawValue = 0;
  uint8_t stableSteps = 0;
  // the calibration minimum and maximum
  uint16_t calMin = 0;
  uint16_t calMax = 1023;


  BMCTimer toeSwitch;
  uint8_t toeSwitchSettings = 0;


  // this is the best way i've found to keep steady readings from a pot
  // specially since we're lowering the resolution down to 7-bits
  // this code came from:
  // https://gist.github.com/CodeZombie/2b7f986fd5aab8c7a25ebdaf33a53118
  // it was modified to work with BMC's calibration values
  uint8_t readPot(){
    uint8_t lastRawValue = rawValue;
    rawValue = readPin();

    if(rawValue != lastRawValue){
      stableSteps = 0;
    }
    value = floor((value + (rawValue*stableSteps)) / (stableSteps+1));
    if(abs(rawValue - value) > 10) {
      value = (value + rawValue)/2;
    }
    stableSteps++;
    if(stableSteps >= 255){
      stableSteps = 0;
    }
    return value;
  }
  void reset(){
    value = readPot();
    // always leave the mux flag in whatever state it was
    flags.reset(1<<BMC_FLAG_AUX_JACK_POT_MUX | 1<<BMC_FLAG_AUX_JACK_POT_TOE_SWITCH_STATE);
  }
  uint8_t readPin(){
    return map(analogRead(pin), calMin, calMax, 0, 128);
  }
};
#endif
