/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_BUTTON_H
#define BMC_BUTTON_H

#include "utility/BMC-Def.h"

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

// @assignedFlags:
// these are flags that are only reset when reassigning the button
#define BMC_BTN_FLAG_MUX_IN 0
#define BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED 1
#define BMC_BTN_FLAG_CONTINUOUS_ENABLED 2
#define BMC_BTN_FLAG_ALTERNATE_PRESS_ENABLED 3
#define BMC_BTN_FLAG_IS_ALT 4

// @buttonFlags:
#define BMC_BTN_FLAG_MUX_STATE 0
#define BMC_BTN_FLAG_STATE_HAS_CHANGED 1
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
#define BMC_BTN_FLAG_ACTIVITY 0
#define BMC_BTN_FLAG_STATE 1
#define BMC_BTN_FLAG_REASSIGNED 2
#define BMC_BTN_FLAG_PRESSED 3
#define BMC_BTN_FLAG_RELEASED 4
#define BMC_BTN_FLAG_HOLD_COMPLETE 5
#define BMC_BTN_FLAG_CONTINUOUS 6
#define BMC_BTN_FLAG_DOUBLE_PRESSED 7
#define BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT 8
#define BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT_RELEASE 9
#define BMC_BTN_FLAG_DOUBLE_PRESS_COMPLETE 10
#define BMC_BTN_FLAG_IGNORE_RELEASE 11
#define BMC_BTN_FLAG_IN_HOLD_POSITION 12
#define BMC_BTN_FLAG_PRESS_TRIGGERED 13
#define BMC_BTN_FLAG_RELEASED_TRIGGERED 14
#define BMC_BTN_FLAG_DEBOUNCING 15

// release types used to determine what type of release event should be triggered
#define BMC_BTN_REL_TYPE_PRESS 1
#define BMC_BTN_REL_TYPE_HOLD 2
#define BMC_BTN_REL_TYPE_DOUBLE_PRESS 3
#define BMC_BTN_REL_TYPE_CONTINUOUS 4
#define BMC_BTN_REL_TYPE_ALT 5

class BMCButton {
public:
  BMCButton(){
    // initialize with the pin number as 255
    // if the pin is 255 it means the begin method has not been called
    pin = 255;
    // reset everything
    assignedFlags.reset();
    buttonFlags.reset();
    reset();
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

    assignedFlags.reset();
    buttonFlags.reset();
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
      assignedFlags.write(BMC_BTN_FLAG_MUX_IN, true);
      setInitialState();
      // all good
      return;
    } else {
      assignedFlags.write(BMC_BTN_FLAG_MUX_IN, false);
    }
#endif
    if(!BMCBuildData::isDigitalPin(pin)){
      BMC_ERROR(
        "PIN:", pin,
        "Can NOT be used with buttons as it is NOT Digital capable"
      );
      BMC_HALT();
    }
    pinMode(pin, BMC_BUTTON_PIN_MODE);
    setInitialState();
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
        enableAltPress();
        break;
    }
  }
  // button flag bits
  void setFlags(uint8_t data=0){
    if(bitRead(data,BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD)){
      ignoreReleaseAfterHold();
    }
    if(bitRead(data,BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS)){
      ignoreHoldOnContinuous();
    }
    if(bitRead(data,BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS)){
      ignoreReleaseOnDoublePress();
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
    assignedFlags.on(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED);
    doublePressTimer.stop();
  }
  void enableContinuous(){
    assignedFlags.on(BMC_BTN_FLAG_CONTINUOUS_ENABLED);
  }
  void ignoreReleaseAfterHold(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD);
  }
  void ignoreHoldOnContinuous(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS);
  }
  void ignoreReleaseOnDoublePress(){
    buttonFlags.on(BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS);
  }
  void enableAltPress(){
    assignedFlags.on(BMC_BTN_FLAG_ALTERNATE_PRESS_ENABLED);
  }
  // threshold must be a value from 0 to 15
  // we increase it by 2 then it's multiplied by 250 when applied to the timer
  // the only reason i chose not to multiply the value here is so that it only
  // requires a byte rather than than 2 bytes, less RAM per button
  void setThreshold(uint8_t t_value){
    t_value += 2;
    threshold = constrain(t_value, 2, 17);
  }
  void reassign(bool hasStateChangeTrigger=false){
    // only keep the exp button flag in whatever state it was
    assignedFlags.reset(1 << BMC_BTN_FLAG_MUX_IN);
    // don't reset the current mux value
    buttonFlags.reset(1 << BMC_BTN_FLAG_MUX_STATE);
    reset(true);

    // when layers change BMC expects all buttons to be in their OPEN position
    // before reading them again, this is because if a button was used to change
    // layers on it's press, hold, or continuous, then when the layer changes
    // if the button has a new event assigned to that same trigger, that event
    // will automatically be triggered, this will also cause layers to change
    // more than once in some cases, so it you want to scroll layers you will
    // not go to the next layer but 2 or 3 layers up.
    // to solve this there's the REASSIGNED flag, this tells the button to
    // ignore EVERYTHING thing until the button has been released.
    // ------------------------
    // for Latching buttons there's a STATE CHANGE trigger type, since latching
    // buttons will change their state only when they are pressed, we can not
    // use the same technique of locking out the button on reassign
    //
    if(!hasStateChangeTrigger){
      // if this button doesn't have an event with a State Change Trigger
      // then we treat it as a non-latching button
      if(readState()){
        flags.on(BMC_BTN_FLAG_REASSIGNED);
      }
    }
  }
  uint8_t read(){
    // check if the state of the button has changed
    // @releaseType this variable notifies what type of release event should be
    // triggered upon the button's release
    if(update()){
      // if a press was detected trigger it, additionally if the double press
      // has timed out (you didn't press it at the right time) then we treat
      // it as a press so any other events as triggered
      if(pressed() || doublePressedTimeoutPress()){
        buttonFlags.on(BMC_BTN_FLAG_STATE_HAS_CHANGED);
        if(assignedFlags.read(BMC_BTN_FLAG_ALTERNATE_PRESS_ENABLED)){
          if(assignedFlags.toggleIfTrue(BMC_BTN_FLAG_IS_ALT)){
            releaseType = BMC_BTN_REL_TYPE_ALT;
            return BMC_BUTTON_PRESS_TYPE_ALT_PRESS;
          }
          assignedFlags.on(BMC_BTN_FLAG_IS_ALT);
        }
        releaseType = BMC_BTN_REL_TYPE_PRESS;
        return BMC_BUTTON_PRESS_TYPE_PRESS;
      }

      if(holdComplete()){
        releaseType = BMC_BTN_REL_TYPE_HOLD;
        return BMC_BUTTON_PRESS_TYPE_HOLD;
      }
      if(released() || doublePressedTimeoutRelease()){
        return getReleaseType();
      }
      if(doublePressed()){
        releaseType = BMC_BTN_REL_TYPE_DOUBLE_PRESS;
        return BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS;
      }
      if(continuous()){
        releaseType = BMC_BTN_REL_TYPE_CONTINUOUS;
        return BMC_BUTTON_PRESS_TYPE_CONTINUOUS;
      }
    }
    if(releaseType != 0 && !isClosed()){
      releaseType = 0;
      buttonFlags.on(BMC_BTN_FLAG_STATE_HAS_CHANGED);
      return BMC_BUTTON_PRESS_TYPE_RELEASE;
    }
    if(buttonFlags.toggleIfTrue(BMC_BTN_FLAG_STATE_HAS_CHANGED)){
      return BMC_BUTTON_PRESS_TYPE_STATE_CHANGE;
    }
    return 0;
  }
  uint8_t getReleaseType(){
    switch(releaseType){
      case BMC_BTN_REL_TYPE_PRESS:
        return BMC_BUTTON_PRESS_TYPE_RELEASE_PRESS;
      case BMC_BTN_REL_TYPE_HOLD:
        return BMC_BUTTON_PRESS_TYPE_RELEASE_HOLD;
      case BMC_BTN_REL_TYPE_DOUBLE_PRESS:
        return BMC_BUTTON_PRESS_TYPE_RELEASE_DOUBLE_PRESS;
      case BMC_BTN_REL_TYPE_CONTINUOUS:
        return BMC_BUTTON_PRESS_TYPE_RELEASE_CONTINUOUS;
      case BMC_BTN_REL_TYPE_ALT:
        return BMC_BUTTON_PRESS_TYPE_RELEASE_ALT;
    }
    releaseType = 0;
    return BMC_BUTTON_PRESS_TYPE_RELEASE;
  }
  bool update(){
    // check if the button has gone from OPEN to CLOSED or vice-versa
    if(debouncer()){
      flags.on(BMC_BTN_FLAG_ACTIVITY);
      if(flags.read(BMC_BTN_FLAG_STATE)){
        flags.on(BMC_BTN_FLAG_PRESSED);
        flags.off(BMC_BTN_FLAG_RELEASED);
      } else {
        flags.off(BMC_BTN_FLAG_PRESSED);
        flags.on(BMC_BTN_FLAG_RELEASED);
      }
    }
    if(assignedFlags.read(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED)){
      if(doublePressTimer.complete()){
        //send the pressed command as double press has timed out.
        flags.off(BMC_BTN_FLAG_DOUBLE_PRESSED);
        flags.on(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT);
        flags.off(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT_RELEASE);
      }
    }
    if(holdTimer.complete()){
      flags.on(BMC_BTN_FLAG_HOLD_COMPLETE);
    }
    if(continuousTimer.complete()){
      continuousTimer.start(BMC_BTN_CONTINUOUS_INTERVAL);
      flags.on(BMC_BTN_FLAG_ACTIVITY);
      flags.on(BMC_BTN_FLAG_CONTINUOUS);
    }
    return true;
  }
  // check if the button has gone from being OPEN to being CLOSED (pressed)
  bool pressed(){
    if(flags.read(BMC_BTN_FLAG_REASSIGNED)){
      return false;
    }
    if(activityDetected() && flags.read(BMC_BTN_FLAG_PRESSED)){
      flags.off(BMC_BTN_FLAG_PRESSED);
      holdTimer.start(threshold*250);
      if(assignedFlags.read(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED) && doublePressTimer.active()){
        doublePressTimer.stop();
        flags.on(BMC_BTN_FLAG_ACTIVITY);
        flags.on(BMC_BTN_FLAG_DOUBLE_PRESSED);
        flags.on(BMC_BTN_FLAG_DOUBLE_PRESS_COMPLETE);
        flags.off(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT);
      }
      // if double press is enabled we always ignore the press event
      return !assignedFlags.read(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED);
    }
    return false;
  }
  // check if the button has been held down
  bool holdComplete(){
    if(flags.read(BMC_BTN_FLAG_REASSIGNED)){
      return false;
    }
    if(activityDetected() && flags.read(BMC_BTN_FLAG_HOLD_COMPLETE)){
      flags.off(BMC_BTN_FLAG_HOLD_COMPLETE);
      flags.on(BMC_BTN_FLAG_IN_HOLD_POSITION);
      holdTimer.stop();
      if(buttonFlags.read(BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD)){
        flags.on(BMC_BTN_FLAG_IGNORE_RELEASE);
      }
      if(assignedFlags.read(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED)){
        doublePressTimer.stop();
      }
      // being continuous evens after this time has been complete
      // the contious evens will begin after double the time threshold has passed
      // if the hold time is 500ms, the continuous events will begin after 1000ms
      // if the hold time is 750ms, the continuous events will begin after 1500ms
      continuousTimer.start(threshold*500);
      return !buttonFlags.read(BMC_BTN_FLAG_IGNORE_HOLD_ON_CONTINUOUS);
    }
    return false;
  }
  bool released(){
    if(activityDetected() && flags.read(BMC_BTN_FLAG_RELEASED)){
      if(flags.read(BMC_BTN_FLAG_REASSIGNED)){
        reset(true);
        releaseType = 0;
        return false;
      }
      if(ignoreRelease()){
        reset();
        releaseType = 0;
        return false;
      }
      if(doublePressHandler()){
        continuousTimer.stop();
        return false;
      }
      if(isIgnoreReleaseAfterHold()){
        reset(true);
        releaseType = 0;
        return false;
      }
      reset();
      return true;
    }
    return false;
  }
  bool doublePressed(){
    if(flags.read(BMC_BTN_FLAG_REASSIGNED)){
      return false;
    }
    if(activityDetected() && flags.read(BMC_BTN_FLAG_DOUBLE_PRESSED)){
      doublePressTimer.stop();
      flags.off(BMC_BTN_FLAG_DOUBLE_PRESSED);
      return true;
    }
    return false;
  }
  bool continuous(){
    if(flags.read(BMC_BTN_FLAG_REASSIGNED)){
      return false;
    }
    if(activityDetected() && flags.read(BMC_BTN_FLAG_CONTINUOUS)){
      continuousTimer.start(250-continuousCount);
      continuousCount += 10;
      if(continuousCount >= 100){
        continuousCount = 100;
      }
      flags.off(BMC_BTN_FLAG_CONTINUOUS);
      return true;
    }
    return false;
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
  bool isClosed(){
    return flags.read(BMC_BTN_FLAG_STATE);
  }
#if defined(BMC_MUX_INPUTS_AVAILABLE)
  void setMuxValue(bool t_state){
    buttonFlags.write(BMC_BTN_FLAG_MUX_STATE, t_state);
  }
  bool isMux(){
    return assignedFlags.read(BMC_BTN_FLAG_MUX_IN);
  }
  uint8_t getMuxPin(){
    return isMux() ? pin-64 : 0;
  }
#endif

  void changePin(uint8_t t_pin){
    if(pin!=255
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    && !isMux()
#endif
    ){
      pin = t_pin;
    }

  }
  uint8_t getPin(){
    return pin;
  }

private:
  void reset(bool hard=false){
    holdTimer.stop();
    continuousTimer.stop();
    continuousCount = 0;
    // reset all flags except for the debouncing flag and the current state
    flags.reset((1<<BMC_BTN_FLAG_DEBOUNCING)|(1<<BMC_BTN_FLAG_STATE));
    if(hard){
      doublePressTimer.stop();
    }
  }
  bool activityDetected(){
    return flags.read(BMC_BTN_FLAG_ACTIVITY);
  }
  // either do the digitalRead or if it's an Expansion Button return the state
  // that was set for the pin.
  // during testing putting this function in FASTRUN gave me about 0.5% more LPS
  FASTRUN bool _digitalRead(){
#if defined(BMC_MUX_INPUTS_AVAILABLE)
    if(assignedFlags.read(BMC_BTN_FLAG_MUX_IN)){
      return buttonFlags.read(BMC_BTN_FLAG_MUX_STATE);
    }
#endif
    return digitalRead(pin);
  }

  // here's where we "debounce" the button, there are many ways to debounce switches
  // there are 2 available, the default will only read buttons every time the
  // debounce time has passed (set by BMC_BUTTON_DEBOUNCE_TIME)
  // the alternate method will read for a button state change all the time
  // once a state change has been detected it will wait the time set by BMC_BUTTON_DEBOUNCE_TIME
  // once that time has passed it will start checking for state changes again
  // both methods will immediately respond to a state change so both are responsive
  // but they also have pros/cons
  // ------------------
  // Default: slightly less responsive to a new change because it only reads
  // button state changes between bebounce timeouts, however it has less overhead
  // because the digitalRead is only done between timeouts and digitalRead can
  // takes some time, this method will let BMC run more LPS making specially
  // if you have a lot of buttons
  // ------------------
  // Alt : the most responsive of the 2 because it's constantly doing a
  // digitalRead, once it detects a state change on the pin it starts waiting
  // for BMC_BUTTON_DEBOUNCE_TIME to pass, once it passes then it can start
  // reading the pin again. the only downside it slows down BMC overall because
  // of the constant digitalRead, digitalRead only take a few micro seconds
  // and since you are running it on a Teensy that won't hurt performance at all
  // unless you have other peripherals connected that need to update faster.

  bool debouncer(){
#ifdef BMC_BUTTON_DEBOUNCE_MAX_RESPONSE
    if(flags.read(BMC_BTN_FLAG_DEBOUNCING)){
      if((millis() - debounceTime) >= BMC_BUTTON_DEBOUNCE_TIME){
        flags.off(BMC_BTN_FLAG_DEBOUNCING);
        debounceTime = 0;
      }
    } else if(flags.read(BMC_BTN_FLAG_STATE) != readState()){
      flags.toggle(BMC_BTN_FLAG_STATE);
      flags.on(BMC_BTN_FLAG_DEBOUNCING);
      debounceTime = millis();
      return true;
    }
#else
    if((millis() - debounceTime) >= BMC_BUTTON_DEBOUNCE_TIME){
      debounceTime = millis();
      if(flags.read(BMC_BTN_FLAG_STATE) != readState()){
        flags.toggle(BMC_BTN_FLAG_STATE);
        return true;
      }
    }
#endif
    return false;
  }
  bool ignoreRelease(){
    return flags.toggleIfTrue(BMC_BTN_FLAG_IGNORE_RELEASE);
  }
  bool isIgnoreReleaseAfterHold(){
    return (buttonFlags.read(BMC_BTN_FLAG_IGNORE_RELEASE_AFTER_HOLD) && flags.read(BMC_BTN_FLAG_IN_HOLD_POSITION));
  }
  bool doublePressHandler(){
    if(assignedFlags.read(BMC_BTN_FLAG_DOUBLE_PRESS_ENABLED)){
      if(flags.read(BMC_BTN_FLAG_DOUBLE_PRESS_COMPLETE)){
        reset(true);
        return true;
      }
      // reset the released and activity flags
      flags.off(BMC_BTN_FLAG_ACTIVITY);
      flags.off(BMC_BTN_FLAG_RELEASED);
      holdTimer.stop();
      if(doublePressTimer.active()){
        doublePressTimer.stop();
        flags.on(BMC_BTN_FLAG_ACTIVITY);
        flags.on(BMC_BTN_FLAG_DOUBLE_PRESSED);
      } else {
        doublePressTimer.start(BMC_BUTTON_DOUBLE_PRESS_THRESHOLD);
        flags.off(BMC_BTN_FLAG_DOUBLE_PRESSED);
      }
      return true;
    }
    return false;
  }
  bool doublePressedTimeoutPress(){
    if(flags.read(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT)){
      if(!flags.read(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT_RELEASE)){
        flags.on(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT_RELEASE);
        return true;
      }
    }
    return false;
  }
  bool doublePressedTimeoutRelease(){
    if(flags.read(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT)){
      if(flags.read(BMC_BTN_FLAG_DOUBLE_PRESS_TIMEOUT_RELEASE)){
        reset(true);
        if(buttonFlags.read(BMC_BTN_FLAG_IGNORE_RELEASE_ON_DOUBLE_PRESS)){
          return false;
        }
        return true;
      }
    }
    return false;
  }

private:
  uint8_t pin = 255;
  uint8_t threshold = 0;
  uint8_t releaseType = 0;
  uint8_t continuousCount = 0;
  unsigned long debounceTime = 0;
  BMCFlags <uint8_t> assignedFlags;
  BMCFlags <uint8_t> buttonFlags;
  BMCFlags <uint16_t> flags;
  BMCTimer holdTimer;
  BMCTimer doublePressTimer;
  BMCTimer continuousTimer;
  void setInitialState(){
    delay(1);
    buttonFlags.write(BMC_BTN_FLAG_MUX_STATE, HIGH);
    // set the initial state of the button
    flags.write(BMC_BTN_FLAG_STATE, readState());
  }
};
#endif
