#ifndef BMC_STATE_MACHINE_H
#define BMC_STATE_MACHINE_H

#include "utility/BMC-Def.h"
#include "utility/BMC-Flags.h"
#include "utility/BMC-Timer.h"

#ifndef BMC_CONTINOUS_LOWER_BY
  #define BMC_CONTINOUS_LOWER_BY 10
#endif

#ifndef BMC_CONTINOUS_LOWEST_VALUE
  #define BMC_CONTINOUS_LOWEST_VALUE 100
#endif

// Flag bit positions used in BMCFlags
#define BMC_STATE_MACHINE_FLAG_CLOSED         0 // current input signal (debounced)
#define BMC_STATE_MACHINE_FLAG_LAST_STATE     1 // previous signal state
#define BMC_STATE_MACHINE_FLAG_DBL_ENABLED    2 // double press feature enabled
#define BMC_STATE_MACHINE_FLAG_2ND_ENABLED    3 // second press (toggle) feature enabled
#define BMC_STATE_MACHINE_FLAG_TOGGLE_PRESS   4 // toggle state for 2nd press tracking
#define BMC_STATE_MACHINE_FLAG_DBL_PENDING    5 // waiting for second press
#define BMC_STATE_MACHINE_FLAG_HOLD_ACTIVE    6 // hold has been triggered
#define BMC_STATE_MACHINE_FLAG_CONTINUOUS     7 // continuous mode has started

class BMCStateMachine {
public:
  BMCStateMachine(){}

  // Initialize with optional hold time (default 500ms)
  void begin(uint16_t hold = 500){
    holdTime = hold;
    reset();
  }

  // Update state based on current signal (true = active/pressed)
  // Returns true if a trigger is ready to be read
  bool update(bool t_signalReading){
    // ----------------------------------------------
    // Lockout state: ignore everything until release
    // ----------------------------------------------
    if(isLockoutEnabled()){
      if(!t_signalReading){
        // Button released, exit lockout mode
        locked = false;
      }
      return false;
    }

    if(!isClosed() && useDoublePress() && isDoublePressPending() && doublePressTimer.complete()){
      if(lastPressType == BMC_TRIG_PRESS || lastPressType == BMC_TRIG_ALT_PRESS){
        setReleaseType();
        return true;
      }
    }

    // Save current and previous state
    bool prev = isClosed();
    flags.write(BMC_STATE_MACHINE_FLAG_LAST_STATE, prev);
    flags.write(BMC_STATE_MACHINE_FLAG_CLOSED, t_signalReading);

    // ----------------------------------------------
    // Queue STATE CHANGE if state flipped
    // ----------------------------------------------
    if(prev != t_signalReading){
      stateChangeReturnValue = BMC_TRIG_STATE_CHANGE;
    }

    // ---------------------------------------------------
    // Detect rising edge: Button just pressed (LOW state)
    // ---------------------------------------------------
    if(!prev && isClosed()){
      // Start hold detection timer
      holdTimer.start(holdTime);
      contTimer.stop();             // Stop any active continuous timer
      contInterval = continuousTime; // Reset continuous interval

      // --------------------------------------------
      // Determine PRESS type (standard or alternate)
      // --------------------------------------------
      pressReturnValue = BMC_TRIG_PRESS;
      if(useSecondPress()){
        if(flags.toggleIfFalse(BMC_STATE_MACHINE_FLAG_TOGGLE_PRESS)){
          pressReturnValue = BMC_TRIG_PRESS;
        } else {
          pressReturnValue = BMC_TRIG_ALT_PRESS;
        }
      }

      // ---------------------------------------------
      // Double press check (second tap within window)
      // ---------------------------------------------
      if(useDoublePress()){
        if(doublePressTimer.active() && !doublePressTimer.complete()){
          // Detected a valid double press
          pressReturnValue = BMC_TRIG_DOUBLE_PRESS;
          flags.off(BMC_STATE_MACHINE_FLAG_DBL_PENDING);
          doublePressTimer.stop();
        } else {
          // Start waiting for second tap
          flags.on(BMC_STATE_MACHINE_FLAG_DBL_PENDING);
          doublePressTimer.start(doublePressTime);
        }
      }

      // Store the current press type
      lastPressType = pressReturnValue;
    }

    // ------------------------------------------------------
    // Detect falling edge: Button just released (HIGH state)
    // ------------------------------------------------------
    
    if(prev && !isClosed()){
      pressReturnValue = BMC_TRIG_RELEASE;
    
      if(useDoublePress() && isDoublePressPending()){

        if(doublePressTimer.complete()){
          // double press has timedout
          flags.off(BMC_STATE_MACHINE_FLAG_DBL_PENDING);

        } else {
          // Still waiting for second press, do not emit final release
          return true;
        }
      }

      // Now decide release type based on what was actually triggered last
      setReleaseType();

      holdTimer.stop();
      contTimer.stop();
      flags.off(BMC_STATE_MACHINE_FLAG_HOLD_ACTIVE);
      flags.off(BMC_STATE_MACHINE_FLAG_CONTINUOUS);
    }



    // -------------------------------------------
    // Button is still held down (signal is LOW)
    // -------------------------------------------
    if(isClosed()){
      // HOLD trigger — fires once after holdTime
      if(!isHoldActive() && holdTimer.complete()){
        pressReturnValue = BMC_TRIG_HOLD;
        flags.on(BMC_STATE_MACHINE_FLAG_HOLD_ACTIVE);
        contTimer.start(holdTime * 2); // First CONTINUOUS after 2x hold time
        lastPressType = pressReturnValue;
      }

      // CONTINUOUS trigger — fires repeatedly after hold
      else if(isHoldActive() && contTimer.complete()){
        pressReturnValue = BMC_TRIG_CONTINUOUS;
        contTimer.start(contInterval);
        lastPressType = pressReturnValue;

        // Reduce the interval between CONTINUOUS triggers
        if(contInterval > BMC_CONTINOUS_LOWEST_VALUE){
          // Reduce the value
          contInterval -= BMC_CONTINOUS_LOWER_BY;
          if(contInterval < BMC_CONTINOUS_LOWEST_VALUE){
            // We reached the minimum, constrain to lowest
            contInterval = BMC_CONTINOUS_LOWEST_VALUE;
          }
        }
      }
    }

    // True if we have a trigger queued up
    return (
      stateChangeReturnValue != BMC_TRIG_IDLE ||
      pressReturnValue != BMC_TRIG_IDLE ||
      releaseReturnValue != BMC_TRIG_IDLE
    );
  }

  // --------------------------------------------------
  // Returns one pending trigger per call, clears after
  // Order: STATE CHANGE → PRESS → RELEASE
  // --------------------------------------------------
  uint8_t read(){
    if(stateChangeReturnValue != BMC_TRIG_IDLE){
      uint8_t out = stateChangeReturnValue;
      stateChangeReturnValue = BMC_TRIG_IDLE;
      return out;
    }
    if(pressReturnValue != BMC_TRIG_IDLE){
      uint8_t out = pressReturnValue;
      pressReturnValue = BMC_TRIG_IDLE;
      return out;
    }
    if(releaseReturnValue != BMC_TRIG_IDLE){
      uint8_t out = releaseReturnValue;
      releaseReturnValue = BMC_TRIG_IDLE;
      return out;
    }
    return BMC_TRIG_IDLE;
  }

  // ----------------------------------
  // Configuration and feature toggles
  // ----------------------------------
  void enableDoublePress(bool v){ flags.write(BMC_STATE_MACHINE_FLAG_DBL_ENABLED, v); }
  void enableSecondPress(bool v){ flags.write(BMC_STATE_MACHINE_FLAG_2ND_ENABLED, v); }
  void setHoldTime(uint16_t t){ holdTime = t; }
  void setDoublePressWindow(uint16_t t){ doublePressTime = t; }
  void setContinuousTime(uint16_t t){ continuousTime = t; }

  // Enables or disables lockout mode (used during reassignment)
  void lockout(bool v){
    locked = v;
    reset();
  }

  // Returns true if lockout is currently enabled
  bool isLockoutEnabled(){ return locked; }

private:
  // Internal flag and timer infrastructure
  BMCFlags<uint8_t> flags;
  BMCTimer holdTimer, contTimer, doublePressTimer;

  // Internal state tracking
  uint8_t lastPressType = BMC_TRIG_IDLE;
  uint8_t pressReturnValue = BMC_TRIG_IDLE;
  uint8_t releaseReturnValue = BMC_TRIG_IDLE;
  uint8_t stateChangeReturnValue = BMC_TRIG_IDLE;

  // Timing config
  uint16_t holdTime = 500;
  uint16_t continuousTime = 250;
  uint16_t contInterval = 250;
  uint16_t doublePressTime = 250;
  bool locked = false;

  // Reset the state machine to its initial state
  void reset(){
    flags.reset();
    holdTimer.stop();
    contTimer.stop();
    doublePressTimer.stop();
    pressReturnValue = BMC_TRIG_IDLE;
    releaseReturnValue = BMC_TRIG_IDLE;
    stateChangeReturnValue = BMC_TRIG_IDLE;
    lastPressType = BMC_TRIG_IDLE;
    continuousTime = 250;
    contInterval = 250;
  }
  void setReleaseType(){
    switch(lastPressType){
      case BMC_TRIG_PRESS:           releaseReturnValue = BMC_TRIG_RELEASE_PRESS;         break;
      case BMC_TRIG_ALT_PRESS:       releaseReturnValue = BMC_TRIG_RELEASE_ALT;           break;
      case BMC_TRIG_HOLD:            releaseReturnValue = BMC_TRIG_RELEASE_HOLD;          break;
      case BMC_TRIG_CONTINUOUS:      releaseReturnValue = BMC_TRIG_RELEASE_CONTINUOUS;    break;
      case BMC_TRIG_DOUBLE_PRESS:    releaseReturnValue = BMC_TRIG_RELEASE_DOUBLE_PRESS;  break;
      default:                       releaseReturnValue = BMC_TRIG_RELEASE_PRESS;         break;
    }
  }
  

  // -----------------------
  // Internal helper methods
  // -----------------------
  bool isHoldActive(){ return flags.read(BMC_STATE_MACHINE_FLAG_HOLD_ACTIVE); }
  bool useDoublePress(){ return flags.read(BMC_STATE_MACHINE_FLAG_DBL_ENABLED); }
  bool useSecondPress(){ return flags.read(BMC_STATE_MACHINE_FLAG_2ND_ENABLED); }
  bool isDoublePressPending(){ return flags.read(BMC_STATE_MACHINE_FLAG_DBL_PENDING); }
  bool isClosed(){ return flags.read(BMC_STATE_MACHINE_FLAG_CLOSED); }
  bool wasClosed(){ return flags.read(BMC_STATE_MACHINE_FLAG_LAST_STATE); }
};

#endif