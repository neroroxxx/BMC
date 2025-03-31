/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2015 - 2025 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  ================================
  Reading Potentiometer Values
  ================================

  - Potentiometers (pots) must be connected to analog-capable pins.
  - Output values are limited to 0-127 for MIDI compatibility.

  ---------------------
  Calibration
  ---------------------
  By default, analogRead() returns values from 0 to 1023. However, some pots 
  may never reach the full range due to hardware tolerances. To address this, 
  calibration can be set manually or automatically initialized by BMC using 
  its Editor and API. This ensures the pot operates within its actual working range.

  ---------------------
  Range Min/Max
  ---------------------
  Pots can be assigned a custom range (min/max) to reduce resolution.
  For example, setting a range from 1 to 3 divides the pot’s movement 
  into three sections, where each section corresponds to a specific output value.

  ---------------------
  How Range Mapping Works
  ---------------------
  The range is mapped using the map() function, meaning values are distributed 
  evenly across the pot’s physical movement. For example, if a pot is set to a 
  range of 1 to 3, the output values will be triggered based on position thresholds:

      Pot Position   Expected Output   Actual Output (Mapped)
      ------------------------------------------------------
      0             | 1               | 1 (0 to 42)
      64            | 2               | 2 (43 to 86)
      127           | 3               | 3 (87 to 127)

  Since mapping divides the full range into equal sections, the output values 
  are triggered based on position thresholds rather than specific fixed values.
*/

#ifndef BMC_POT_H
#define BMC_POT_H
#include "utility/BMC-Def.h"

#define BMC_FLAG_POT_REASSIGNED 0
#define BMC_FLAG_POT_MUX 1
#define BMC_FLAG_POT_LOG 2
#define BMC_FLAG_POT_TOE_SWITCH_AVAILABLE 3
#define BMC_FLAG_POT_TOE_SWITCH_STATE 4
#define BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED 5

// position where logarithmic taper starts it's steep curve
// this value should range from 10 to 100
#define BMC_POT_LOG_POSITION_CUTOFF     60
// before the position above is reached, we will cover this much range
#define BMC_POT_LOG_PERCENTAGE_CUTOFF   20
// the values above will be used for the the final values used
#define BMC_POT_LOG_POS   ((uint16_t) ((10.23*BMC_POT_LOG_POSITION_CUTOFF)+0.5))
#define BMC_POT_LOG_PERC  ((uint16_t) ((10.23*BMC_POT_LOG_PERCENTAGE_CUTOFF)+0.5))


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
    if(pin != 255){
      return;
    }
    if(t_pin == 255){
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
    if(t_pin >= 64){
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
    BMC_PRINTLN("POT PIN @", pin);
    // pinMode(pin, INPUT_DISABLE);
    pinMode(pin, INPUT_PULLUP);
  }
  // set the calibration of the POT
  void setCalibration(uint16_t t_min, uint16_t t_max){
    uint16_t limit = 1023;
    t_min = (t_min >= limit) ? 0 : t_min;
    t_max = (t_max > limit) ? limit : t_max;
    if(t_min>=t_max){
      t_min = 0;
      t_max = limit;
    }
    if(t_min > 511){
      t_min = 0;  
    }
    if(t_max < 512){
      t_max = limit;  
    }
    // prevent too short a range which may brick the teensy
    if(t_max-t_min < 500){
      t_min = 0;
      t_max = limit;
    }
    calMin = t_min;
    calMax = t_max;
    BMC_PRINTLN("calMin", calMin, "calMax", calMax);
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
  void setTaper(bool t_log){
    flags.write(BMC_FLAG_POT_LOG, t_log);
  }
  // reassign the POT behaviour, used when switching layers or the editor
  // has updated EEPROM
  void reassign(){
    reset();
    flags.on(BMC_FLAG_POT_REASSIGNED);
  }

  void assignToeSwitch(bmcEvent_t t_engage, bmcEvent_t t_disengage, uint8_t t_settings){
    if(t_engage > 0 && t_disengage > 0){
      toeOnEvent = t_engage;
      toeOffEvent = t_disengage;
      toeSwitchSettings = t_settings;
      flags.on(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
    } else {
      toeOnEvent = 0;
      toeOffEvent = 0;
      toeSwitchSettings = 0;
      flags.off(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
    }
  }

  bool toeSwitchActive(){
    if(!toeSwitchAvailable()){
      return false;
    }
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
    return ((toeSwitchSettings & 0x07) + 1) * 5;
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
  bmcEvent_t toeSwitchGetEvent(){
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

  // * Auto Engage Mode
  // * The Toe Switch Engage Event is sent as soon as the potentiometer moves past the Engage Value.
  // * When the potentiometer returns to the Engage Value position (or lower), a timer starts based on the configured Engage Speed.
  // * Once the timer completes, the Toe Switch Disengage Event is sent.
  // * Each event is triggered only once per switch state change.
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
  // * Toe Switch Mode
  // * You must move the expression pedal/potentiometer to or beyond the Engage Value to start the timer configured by Engage Speed.
  // * When the timer completes, the Toe Switch Engage Event is sent.
  // * You can freely rock the pedal/pot position, but once it returns to the Engage Value or higher, the timer configured by Engage Speed starts again.
  // * After the timer duration is met, the Toe Switch Disengage Event is sent.
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
    if(flags.toggleIfTrue(BMC_FLAG_POT_REASSIGNED)){
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
#if BMC_MAX_MUX_IN_ANALOG > 0
    if(flags.read(BMC_FLAG_POT_MUX)){
      return muxValue;
    }
#endif
    return analogRead(pin);
  }
#if BMC_MAX_MUX_IN_ANALOG > 0
    uint8_t getMuxPin(){
      return flags.read(BMC_FLAG_POT_MUX) ? pin-64 : 0;
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


  BMCTimer toeSwitch;
  bmcEvent_t toeOnEvent = 0;
  bmcEvent_t toeOffEvent = 0;
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
    value = constrain(value, 0, 127);
    return map(value, 0, 127, rangeMin, rangeMax);
  }

  // Function to read the potentiometer value, smooth it using EMA, and return a mapped MIDI value.
  // The function applies an Exponential Moving Average (EMA) for smoother, faster filtering of potentiometer noise.
  uint8_t readPot2() {
    // Store the previous raw value to detect changes
    uint8_t lastRawValue = rawValue;

    // Read the current raw value from the potentiometer (0-127 range)
    rawValue = readPin();

    // Only reset the value if there's a significant change in the raw value
    if (abs(rawValue - lastRawValue) > 3) {
      value = rawValue; // Reset the value to the raw value for better stability
    }

    // Apply Exponential Moving Average (EMA) smoothing
    const float alpha = 0.2;  // Smoothing factor (lower = more smoothing)
    value = alpha * rawValue + (1 - alpha) * value;

    // If the difference between raw and value is too large, adjust the value
    if (abs(rawValue - value) > 10) {
      value = (value + rawValue) / 2; // Adjust to prevent sudden jumps
    }

    return mapAndConstrain(value, 0, 127, rangeMin, rangeMax);

    // // Constrain the value to the MIDI range of 0-127 (though it's already in this range)
    // value = constrain(value, 0, 127);
    // // Return the value mapped to the desired MIDI range (rangeMin to rangeMax)
    // return map(value, 0, 127, rangeMin, rangeMax);
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
      // return map(parseTaper(muxValue), calMin, calMax, 0, 127);
      return parseTaper(muxValue);
    }
#endif
    // return map(parseTaper(analogRead(pin)), calMin, calMax, 0, 127);
    return parseTaper(analogRead(pin));
  }
  
  uint16_t parseTaper(uint16_t t_value){
    t_value = constrain(t_value, calMin, calMax);
    
    // if(flags.read(BMC_FLAG_POT_LOG)){
    //   if(t_value <= BMC_POT_LOG_POS){
    //     t_value = map(t_value, 0, BMC_POT_LOG_POS, 0, BMC_POT_LOG_PERC);
    //   } else {
    //     t_value = map(t_value, BMC_POT_LOG_POS+1, 1023, BMC_POT_LOG_PERC+1, 1023);
    //   }
    // }

    // return t_value;

    if(flags.read(BMC_FLAG_POT_LOG)){
      t_value = linearToAudioTaper(t_value);
    }
    return map(t_value, calMin, calMax, 0, 127);
  }

  // Function to convert a linear value (0-1023) to an audio taper value
  // using a logarithmic scale to simulate volume perception in audio systems.
  uint16_t linearToAudioTaper(uint16_t linearValue) {
    // Preventing a divide by zero error by adding 1 to the input value
    // Logarithmic transformation to create the audio taper
    if (linearValue == 0) return 0; // Handle the zero case explicitly
    if (linearValue == 1023) return 1023; // Handle the 1023 case explicitly
    return (uint16_t)((log(linearValue + 1) / log(1024.0)) * 1023);
  }

  // Function to map a value from one range to another, ensuring the value is constrained
  uint16_t mapAndConstrain(uint16_t value, uint16_t inMin, uint16_t inMax, uint16_t outMin, uint16_t outMax) {
    // Map the value from the input range to the output range
    uint16_t mappedValue = (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    // Constrain the mapped value to the output range
    return constrain(mappedValue, outMin, outMax);
  }
};
#endif
