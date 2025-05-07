/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#ifndef BMC_BUTTON_H
#define BMC_BUTTON_H

#include "utility/BMC-Def.h"
#include "devices/physical/buttons/BMC-Debounce.h"
#include "devices/physical/buttons/BMC-StateMachine.h"

// this should be defined as part of your config file if you want that method,
// i just keep it here for testing.
//#define BMC_BUTTON_DEBOUNCE_MAX_RESPONSE

// BMC expects all buttons to be active LOW, either BMC will set the pinMode to
// INPUT_PULLUP by default or you can define on your config file BMC_BUTTON_NO_PULLUP
// for BMC to set the pinMode of each button to INPUT in which case you have to
// add a pullup resistor
#define BMC_BUTTON_CLOSED LOW
#define BMC_BUTTON_OPEN HIGH

// this can be overloaded on the config file
// it's how often the continous events should be sent in ms
// so if it's 250 each continuous event will be sent every 250ms until
// the button is released
#if !defined(BMC_BTN_CONTINUOUS_INTERVAL)
  #define BMC_BTN_CONTINUOUS_INTERVAL 250
#endif
// limit the continous interval to 250ms minimum
#if BMC_BTN_CONTINUOUS_INTERVAL < 250
  #undef BMC_BTN_CONTINUOUS_INTERVAL
  #define BMC_BTN_CONTINUOUS_INTERVAL 250
#endif

// @configFlags:
// these are flags that are only reset when reassigning the button
#define BMC_BTN_FLAG_MUX_IN 0

// @buttonFlags:
#define BMC_BTN_FLAG_MUX_STATE 0
// these are the flags that are part of the "mode" of the button
// since the button uses the first 4 bits of the mode variable for
// the press type, we use the other 4 for press flags.
// that's why here they start at bit 4, since bits 0,1,2,3 are the press type
// these could be mapped to start at 0
// but let's keep them at 4 so they match the mode bit
#define BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD 4
#define BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS 5
#define BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS 6

// @flags
#define BMC_BTN_FLAG_STATE 0
#define BMC_BTN_FLAG_PRESS_TRIGGERED 1
#define BMC_BTN_FLAG_RELEASED_TRIGGERED 2

class BMCButton {
public:
  BMCButton(){
    // initialize with the pin number as 255
    // if the pin is 255 it means the begin method has not been called
    pin = 255;
  }
// if Mux In is compiled
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

    configFlags.reset();
    buttonFlags.reset();
    
    reset();

    pin = t_pin;

#if defined(BMC_MUX_INPUTS_AVAILABLE)
// if the pin number is 64 or higher it's a mux pin
    if(pin>=64){
      if(!BMCBuildData::isMuxInputPin(pin)){
        BMC_ERROR(
          "Mux Pin:", pin,
          "Can NOT be used with buttons as it is NOT a valid Mux In Pin"
        );
        BMC_HALT();
      }
      configFlags.write(BMC_BTN_FLAG_MUX_IN, true);
      setInitialState();
      // all good
      return;
    } else {
      configFlags.write(BMC_BTN_FLAG_MUX_IN, false);
    }
#endif
    if(!BMCBuildData::isDigitalPin(pin)){
      BMC_ERROR(
        "PIN:", pin,
        "Can NOT be used with buttons as it is NOT Digital capable"
      );
      BMC_HALT();
    }
    
    BMC_PRINTLN("BMCButton Pin", pin);

    pinMode(pin, BMC_BUTTON_PIN_MODE);
    setInitialState();
  }

  void reassign(bool hasStateChangeTrigger=false){
    // only keep the exp button flag in whatever state it was
    configFlags.reset(1 << BMC_BTN_FLAG_MUX_IN);

    // don't reset the current mux value
    buttonFlags.reset(1 << BMC_BTN_FLAG_MUX_STATE);

    reset(true);
  }

  bool update(){
    if(debouncer.update(readState())){
      flags.write(BMC_BTN_FLAG_STATE, debouncer.getState());
    }
    return stateMachine.update(flags.read(BMC_BTN_FLAG_STATE));
  }

  uint8_t read(){
    update();
    return stateMachine.read();
  }

  bool isClosed(){
    return flags.read(BMC_BTN_FLAG_STATE);
  }

  void setModeAndFlags(uint8_t t_modeAndFlags=0){
    setMode(t_modeAndFlags);
    setFlags(t_modeAndFlags);
  }

  void setMode(uint8_t value=0){
    switch((value & 0x0F)){
      case BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS:
        enableDoublePress();
        break;
      case BMC_BUTTON_PRESS_TYPE_ALT_PRESS:
        enableSecondPress();
        break;
    }
  }

  void triggerPress(){
    flags.on(BMC_BTN_FLAG_PRESS_TRIGGERED);
  }

  void triggerRelease(){
    if(flags.read(BMC_BTN_FLAG_PRESS_TRIGGERED)){
      flags.on(BMC_BTN_FLAG_RELEASED_TRIGGERED);
    }
  }

  void triggerToggle(){
    if(!flags.read(BMC_BTN_FLAG_PRESS_TRIGGERED)){
      flags.on(BMC_BTN_FLAG_PRESS_TRIGGERED);
    } else {
      flags.on(BMC_BTN_FLAG_RELEASED_TRIGGERED);
    }
  }

  void enableDoublePress(){
    stateMachine.enableDoublePress(true);
  }

  void enableSecondPress(){
    stateMachine.enableSecondPress(true);
  }

  // * sets the mode the buttons will debounce
  void setDebounceMode(uint8_t t_value){
    t_value = constrain(t_value, 0, 3);
    debouncer.setMode(t_value);
  }

  // * sets how long to hold button down before HOLD is fired
  // * threshold must be a value from 0 to 15
  // * minimum is 500ms
  void setHoldTime(uint8_t t_value){
    t_value = constrain(t_value, 0, 15);
    stateMachine.setHoldTime(500 + (t_value * 250));
  }

  // * sets the window of time between double presses, minimum is 300
  void setDoublePressWindow(uint8_t t_value){
    t_value = constrain(t_value, 0, 7);
    stateMachine.setDoublePressWindow(300 + (t_value * 50));
  }

  // * sets the interval time the continuous trigger is fired up, minimum is 300
  void setContinuousTime(uint8_t t_value){
    t_value = constrain(t_value, 0, 7);
    stateMachine.setContinuousTime(300 + (t_value * 50));
  }

  // * button flag bits
  // * DEPRECATED
  void setFlags(uint8_t data=0){
    if(bitRead(data, BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD)){
      ignoreReleaseAfterHold();
    }
    if(bitRead(data, BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS)){
      ignoreHoldOnContinuous();
    }
    if(bitRead(data, BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS)){
      ignoreReleaseOnDoublePress();
    }
  }

  // * DEPRECATED
  void ignoreReleaseAfterHold(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD);
  }

  // * DEPRECATED
  void ignoreHoldOnContinuous(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS);
  }

  // * DEPRECATED
  void ignoreReleaseOnDoublePress(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS);
  }

  bool readState(){
    if(flags.read(BMC_BTN_FLAG_PRESS_TRIGGERED)){
      if(flags.toggleIfTrue(BMC_BTN_FLAG_RELEASED_TRIGGERED)){
        flags.off(BMC_BTN_FLAG_PRESS_TRIGGERED);
        return false;
      }
      return true;
    }
    return (_digitalRead()==BMC_BUTTON_CLOSED);
  }
#if defined(BMC_MUX_INPUTS_AVAILABLE)
  void setMuxValue(bool t_state){
    buttonFlags.write(BMC_BTN_FLAG_MUX_STATE, t_state);
  }
  bool isMux(){
    return configFlags.read(BMC_BTN_FLAG_MUX_IN);
  }
  uint8_t getMuxPin(){
    return isMux() ? pin-64 : 0;
  }
#endif

  uint8_t getPin(){
    return pin;
  }

private:
  void reset(bool hard = false){
    // holdTimer.stop();
    // continuousTimer.stop();

    // reset all flags except for the debouncing flag and the current state
    flags.reset((1<<BMC_BTN_FLAG_STATE));

    stateMachine.lockout(true);

    // if(hard){
    //   doublePressTimer.stop();
    // }
  }

  // either do the digitalRead or if it's an Expansion Button return the state
  // that was set for the pin.
  // during testing putting this function in FASTRUN gave me about 0.5% more LPS
  FASTRUN bool _digitalRead(){
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    if(configFlags.read(BMC_BTN_FLAG_MUX_IN)){
      return buttonFlags.read(BMC_BTN_FLAG_MUX_STATE);
    }
#endif
    return digitalRead(pin);
  }

private:

  uint8_t pin = 255;

  BMCFlags <uint8_t> configFlags;
  BMCFlags <uint8_t> buttonFlags;
  BMCFlags <uint8_t> flags;

  // BMCTimer holdTimer;
  // BMCTimer doublePressTimer;
  // BMCTimer continuousTimer;
  BMCStateMachine stateMachine;
  BMCDebounce debouncer;

  void setInitialState(){
    delay(1);
    buttonFlags.write(BMC_BTN_FLAG_MUX_STATE, HIGH);
    // set the initial state of the button
    flags.write(BMC_BTN_FLAG_STATE, readState());

    debouncer.setMode(BMC_DEBOUNCE_MODE_SMART);
  }
};
#endif
