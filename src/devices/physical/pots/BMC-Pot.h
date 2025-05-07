/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

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
#include "devices/physical/pots/BMC-StateMachine.h"
#include "devices/physical/pots/BMC-ToeSwitch.h"

#define BMC_FLAG_POT_REASSIGNED 0
#define BMC_FLAG_POT_MUX 1

class BMCPot {
public:
  BMCPot():stateMachine(), toeSwitch(stateMachine){
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
    stateMachine.begin();
    toeSwitch.begin();

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
    BMC_PRINTLN("BMCPot Pin", pin);

    pinMode(pin, INPUT_PULLUP);
    analogReadResolution(10);
  }

  // set the calibration of the POT
  void setCalibration(uint16_t t_min, uint16_t t_max){
    stateMachine.setCalibrationRange(t_min, t_max);
  }

  // set the range of the POT, this is used to lower the resolution
  // in some cases you may want so send a MIDI CC ranging from say 0 to 10
  // if that's the case then this function would see the Potentiometer
  // to go from 0 at full counter-clockwise to 10 at full clockwise etc.
  void setRange(uint8_t t_min, uint8_t t_max){
    stateMachine.setOutputRange(t_min, t_max);
  }

  void setTaperLog(bool t_log){
    stateMachine.setTaper(t_log);
  }

  // reassign the POT behaviour, used when switching layers or the editor
  // has updated EEPROM
  void reassign(){
    reset();
    flags.on(BMC_FLAG_POT_REASSIGNED);
  }

  // *********************************************
  // ************** Toe Switch API ***************
  // *********************************************
  void assignToeSwitch(bmcEvent_t t_engage, bmcEvent_t t_disengage, uint8_t t_settings){
    toeSwitch.assign(t_engage, t_disengage, t_settings);
  }

  bool toeSwitchActive(){
    return toeSwitch.isActive();
  }

  bmcEvent_t toeSwitchGetEvent(){
    return toeSwitch.getEvent();
  }
  // *********************************************
  // *********************************************

  bool update(){
    // this is used when a layer has changed or the editor
    // has updated the EEPROM, the pot will then act as if it was turned
    // this is done to make sure that if the pot has a different event assigned
    // that event is trigger as soon as a layer has been changed or if the pot
    // was updated
    if(flags.toggleIfTrue(BMC_FLAG_POT_REASSIGNED)){
      return true;
    }
    
    bool ret = stateMachine.update(readPin());

    toeSwitch.update();

    return ret;
  }


  // get the current reading of the pot mapped to the range min/max
  uint8_t getValue(){
    return stateMachine.read();
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
    return stateMachine.readPosition();
  }
  uint16_t getRawValue(){
    return readPin();
  }

  // get the calibration min
  uint16_t getCalibrationMin(){
    return stateMachine.getCalibrationMin();
  }

  // get the calibration max
  uint16_t getCalibrationMax(){
    return stateMachine.getCalibrationMax();
  }

  // get the range min
  uint8_t getRangeMin(){
    return stateMachine.getRangeMin();
  }

  // get the range max
  uint8_t getRangeMax(){
    return stateMachine.getRangeMax();
  }


private:
  BMCFlags <uint8_t> flags;

  BMCPotStateMachine stateMachine;
  BMCPotToeSwitch toeSwitch;

  // pot pin number, must be analog input
  uint8_t pin = 255;

#if BMC_MAX_MUX_IN_ANALOG > 0
  uint16_t muxValue = 0;
#endif

  void reset(){
    stateMachine.recalculate(readPin());
    toeSwitch.reset();
    flags.reset(1<<BMC_FLAG_POT_MUX);
  }

  uint16_t readPin(){
#if BMC_MAX_MUX_IN_ANALOG > 0
    if(flags.read(BMC_FLAG_POT_MUX)){
      return muxValue;
    }
#endif
    return analogRead(pin);
  }
};
#endif
