/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Read Potentiometer values
  Pots must be connected to Analog Capable pins
  The output value of Pots is limited to 0 to 127 specifically for MIDI use

  Calibration data can be set for the pot, normally analogRead() will get a
  value from 0 to 1023, however some pots will never hit 1023 or 0
  for this reason you can set the calibration value, BMC can initialize
  potentiometer calibration and automatically do this with the Editor and
  it's API.

  Pots can also use a Range min/max, this will lower the resolution further
  for example a pot could be set to have a range min of 1 and a max of 3
  in this case the pots range is divided into 3 sections, as soon as each
  section is reached the pot will trigger the value for that section.
  NOTE: setting the range values uses the map() function to convert the range
  So in other words the pot will not have preset values, for example if the pot
  has the range above of 1 to 3 you may expect the pot to send a value of 1
  when the actual pot value is 0, a value of 2 when actual pot value is 64 and
  a value of 3 when the actual pot value is 127, however this is not the case,
  the value 1 would be triggered when the actual value of the pot is within
  0 and 42, value 2 is sent when the pot value is between 43 and 86 etc.
*/
#ifndef BMC_POT_H
#define BMC_POT_H
#include "utility/BMC-Def.h"

#define BMC_FLAG_POT_REASSIGNED 0
#define BMC_FLAG_POT_MUX 1
#define BMC_FLAG_POT_TOE_SWITCH_AVAILABLE 2
#define BMC_FLAG_POT_TOE_SWITCH_STATE 3
#define BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED 4


class BMCPot {
public:
  BMCPot(){
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

#if BMC_MAX_MUX_IN_ANALOG > 0
    // all mux pins start with pin number 64, that includes MUX_IN MUX_IN_ANALOG
    // BMC will group them in this order MUX_IN then MUX_IN_ANALOG
    // so if you have 10 MUX_IN pins then pins 64 to 73 are MUX_IN pins
    // then MUX_IN_ANALOG pins start at pin 74 and so on
    // so we want to make sure this pot was set to a MUX_IN_ANALOG
    if(t_pin>=64){
      if(BMCBuildData::isMuxInAnalogPin(pin)){
        flags.on(BMC_FLAG_POT_MUX);
        return;
      } else {
        BMC_ERROR(
          "Mux Pin:", t_pin,
          "Can NOT be used with Pots as it is NOT a Analog Mux Pin"
        );
        BMC_HALT();
      }
    }
#endif

    // check if the pin is Analog capable
    if(!BMCBuildData::isAnalogPin(pin)){
      BMC_ERROR(
        "PIN:", t_pin,
        "Can NOT be used with Pots as it is NOT Analog Capable"
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
  // set the range of the POT, this is used to lower the resolution
  // in some cases you may want so send a MIDI CC ranging from say 0 to 10
  // if that's the case then this function would see the Potentiometer
  // to go from 0 at full counter-clockwise to 10 at full clockwise etc.
  void setRange(uint8_t t_min, uint8_t t_max){
    uint8_t limit = 127;
    t_min = t_min >= limit ? 0 : t_min;
    t_max = t_max > limit ? 1023 : t_max;
    if(t_min>=t_max){
      t_min = 0;
      t_max = limit;
    }
    rangeMin = t_min;
    rangeMax = t_max;
  }
  // reassign the POT behaviour, used when switching pages or the editor
  // has updated EEPROM
  void reassign(){
    reset();
    flags.on(BMC_FLAG_POT_REASSIGNED);
  }

#if defined(BMC_USE_POT_TOE_SWITCH)
  void assignToeSwitch(uint32_t ev, uint16_t t_flags){
    toeOnEvent = validateToeSwitchEvent((ev & 0xFFFF));
    toeOffEvent = validateToeSwitchEvent(((ev>>16) & 0xFFFF));
    flags.write(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE, (toeOnEvent+toeOffEvent>0));
    toeSwitchFlags = (toeOnEvent+toeOffEvent>0)?t_flags:0;
  }
  uint16_t validateToeSwitchEvent(uint16_t t_event){
    uint8_t type = BMC_GET_BYTE(0, t_event);
    if(type == BMC_NONE){
      return 0;
    } else if(type == BMC_POT_TOE_SWITCH_EVENT_TYPE_LIBRARY){
      return (BMC_MAX_LIBRARY>0) ? t_event : 0;
    }
    return t_event;
  }
  bool toeSwitchActive(){
    return flags.toggleIfTrue(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
  }
  bool toeSwitchAvailable(){
    return flags.read(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
  }
  bool toeSwitchGetState(){
    return flags.read(BMC_FLAG_POT_TOE_SWITCH_STATE);
  }
  uint8_t toeSwitchGetOffValue(){
    // use 3 bits for off value (0-2)
    return (toeSwitchFlags & 0x07)*5;
  }
  uint16_t toeSwitchGetOffSpeed(){
    // use 3 bits for off speed (3-5)
    uint8_t value = ((toeSwitchFlags>>3) & 0x07);
    return ((value+1)*100)+200;
  }
  uint8_t toeSwitchGetMode(){
    // use 2 bits for Mode (6-7)
    return (toeSwitchFlags>>6) & 0x03;
  }
  uint16_t toeSwitchGetEvent(){
    if(toeSwitchGetState()){
      return toeOnEvent;
    }
    return toeOffEvent;
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
        flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE);
        flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
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
        flags.off(BMC_FLAG_POT_TOE_SWITCH_STATE);
        flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
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
      flags.toggle(BMC_FLAG_POT_TOE_SWITCH_STATE);
      flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
    }
  }
#endif
  bool update(){

    // last value read
    uint8_t lastValue = value;
    // read the value of the pot mapped to range min/max
    // this reading also includes the pot's calibration
    value = readPot();
    // this is used when a page has changed or the editor
    // has updated the EEPROM, the pot will then act as if it was turned
    // this is done to make sure that if the pot has a different event assigned
    // that event is trigger as soon as a page has been changed or if the pot
    // was updated
    if(flags.toggleIfTrue(BMC_FLAG_POT_REASSIGNED)){
      return true;
    }

#if defined(BMC_USE_POT_TOE_SWITCH)
    handleToeSwitch(lastValue);
#endif

    return (lastValue != value);
  }
  // get the current reading of the pot mapped to the range min/max
  uint8_t getValue(){
    return value;
  }
  // get the actual analog reading of the pot without any mapping it to 127 max
  // used for Pot Calibration and debugging
  uint16_t getAnalogValue(){
#if BMC_MAX_MUX_IN_ANALOG > 0
    if(flags.read(BMC_FLAG_POT_MUX)){
      return muxValue;
    }
#endif
    return analogRead(pin);
  }
#if BMC_MAX_MUX_IN_ANALOG > 0
    uint8_t getMuxPin(){
      return flags.read(BMC_FLAG_POT_MUX) ? pin-(64+BMC_MAX_MUX_IN) : 0;
    }
    bool isMux(){
      return flags.read(BMC_FLAG_POT_MUX);
    }
    void setMuxValue(uint16_t t_value){
      if(flags.read(BMC_FLAG_POT_MUX)){
        muxValue = t_value;
      }
    }
#endif

  uint8_t getPin(){
    return pin;
  }
  // get the position of the pot, used by the editor
  // this may also be used to get the value without mapping the range
  // this value will always return a range of 0/127
  // the readPot() method will always store the value mapped down to the
  // specified range, here we map it back to 0-127
  uint8_t getPosition(){
    return map(value, rangeMin, rangeMax, 0, 127);
  }
  // get the calibration min
  uint16_t getCalibrationMin(){
    return calMin;
  }
  // get the calibration max
  uint16_t getCalibrationMax(){
    return calMax;
  }
  // get the range min
  uint16_t getRangeMin(){
    return rangeMin;
  }
  // get the range max
  uint16_t getRangeMax(){
    return rangeMax;
  }
private:
  BMCFlags <uint8_t> flags;
  // pot pin number, must be analog input
  uint8_t pin = 255;
  // the current value used by BMC
  uint8_t value = 0;

#if BMC_MAX_MUX_IN_ANALOG > 0
  uint16_t muxValue = 0;
#endif
  //
  uint8_t rawValue = 0;
  uint8_t stableSteps = 0;

  // the range Smooth will be mapped to
  uint8_t rangeMin = 0;
  uint8_t rangeMax = 127;
  // the calibration minimum and maximum
  uint16_t calMin = 0;
  uint16_t calMax = 1023;

#if defined(BMC_USE_POT_TOE_SWITCH)
  BMCTimer toeSwitch;
  uint16_t toeOnEvent = 0;
  uint16_t toeOffEvent = 0;
  uint16_t toeSwitchFlags = 0;
#endif

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
    return map(value, 0, 127, rangeMin, rangeMax);
  }
  void reset(){
    value = readPot();
    rangeMin = 0;
    rangeMax = 127;
    // always leave the mux flag in whatever state it was
    flags.reset(1<<BMC_FLAG_POT_MUX | 1<<BMC_FLAG_POT_TOE_SWITCH_STATE);
  }
  uint8_t readPin(){
#if BMC_MAX_MUX_IN_ANALOG > 0
    if(flags.read(BMC_FLAG_POT_MUX)){
      return map(muxValue, calMin, calMax, 0, 128);
    }
#endif
    return map(analogRead(pin), calMin, calMax, 0, 128);
  }
};
#endif
