/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Handles 2 buttons being pressed at the same time.
  These are to be handled in your sketch with a callback
  "onButtonDualPress(uint8_t btn1, uint8_t btn2)"
  If the callback is not setup then BMC will not read simultaneous presses

  Here's how it works, when a button is pressed BMC will wait for another button
  to be pressed, when the second button is pressed BMC will trigger the callback
  with the index of each button pressed.
  For the callback to be triggered both buttons must be pressed within a time
  determined by BMC_BUTTON_DUAL_PRESS_TIMEOUT which is default at 75 milliseconds.
  Once the second button pressed is detected the callback is triggered and none
  of the events of either button will be triggered until they have been released.
  Only the first "Press" event of the first button will be triggered immediately.
  For this matter I recommend that all buttons that will be used as Dual Press
  should not have a "Press" event instead they should have "Release" events.
  Another Dual Press will not be detected until both buttons that triggered the
  dual buttons pressed are released.

  Here's a quick example to properly use this feature

  #include <BMC.h>
  BMC_DEFAULT();
  void setup(){
    bmc.begin();
    bmc.onButtonDualPress(callback);
  }
  void callback(uint8_t btn1, uint8_t btn2){
    // this callback is triggered any time 2 buttons are pressed simultaneously
    // for this example I'll check if the first and second button where pressed
    // at the same time, remember BMC is inclusive to Button #1 will be 0, #2 is 1, etc.
    // ALSO the lowest button number will always be btn1, so if button #2 is detected
    // first and button #1 is detected second then "btn1" will carry the index of
    // button #1 and "btn2" will carry the index of button #2
    if(btn1==0 && btn2==1){
      BMC_PRINTLN("Buttons #1 and #2 were pressed simultanously");
    }
  }
  void loop(){
    bmc.update();
  }



  These Dual Button Presses are usually used for Utility, maybe to change Pages,
  save edits, maybe even to change stores.
*/
#ifndef BMC_BUTTONS_DUAL_HANDLER_H
#define BMC_BUTTONS_DUAL_HANDLER_H
#if BMC_MAX_BUTTONS > 1 && BMC_MAX_BUTTON_EVENTS > 0
#include "utility/BMC-Def.h"
#include "hardware/BMC-Button.h"

#define BMC_BUTTONS_DUAL_GLOBAL 0
#define BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE 1

class BMCButtonsDualHandler {
public:
  BMCButtonsDualHandler(BMCCallbacks& cb, bool isGlobal):callback(cb){
    reset();
    flags.reset();
    flags.write(BMC_BUTTONS_DUAL_GLOBAL, isGlobal);
  }
  // return true when 2 buttons have been pressed
  bool read(uint8_t n, uint8_t trigger, bool state, uint32_t states, uint32_t states2=0){
    // only check for dual button press if there's a callback setup
    if(callbackAvailable()){
      uint8_t btn = n;

#if BMC_MAX_BUTTONS > 32
      if(n >= 32){
        btn = n-32;
        states = states2;
      }
#endif
      if(flags.read(BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE)){
        // at this point we are waiting for the buttons to be released and any
        // events of these buttons will be ignored.
        if(n==releaseA || n==releaseB){
          // BMC_BUTTON_PRESS_TYPE_RELEASE is the "Release (Always)"  trigger
          // since this trigger is always activated when you release a button
          // we want to only accept a release of a dual button when that trigger is called
          if(state || trigger!=BMC_BUTTON_PRESS_TYPE_RELEASE){
            return true;
          }
          // the 1st button has been release
          if(releaseA==n){
            releaseA = -1;
          } else if(releaseB==n){
            // the 2nd button has been release
            releaseB = -1;
          }
          if(releaseA==-1 && releaseB==-1){
            // both buttons have been released, now everything is reset
            // nad another simultaneous button press can be detected.
            reset();
            flags.off(BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE);
          }
          return true;
        }
        return false;
      }
      // check if the button is pressed down and if the state is not the same
      // as it was the last time we checked for a dual press
      if(state && bitRead(states, btn) != state){
        // state changed and buttons is pressed
        if(last>=0 && last!=n){
          // save the index of the buttons that were pressed so we can wait for
          // them to be released
          releaseA = n;
          releaseB = last;
          // we can now wait for the release of the buttons.
          flags.on(BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE);
          // stop the timeout so we don't reset things since we are now
          // going to wait for both buttons to be released.
          timeout.stop();
          // always add the lowest index as the first argument
          // so if button 8 was detected first & button 2 was detected second
          // 2 would be the first argument, 8 would be the second argument
          // this way in the sketch you can always get the same result
          if(last > n){
            triggerCallback(n, last);
          } else {
            triggerCallback(last, n);
          }
          return true;
        } else {
          last = n;
          timeout.start(BMC_BUTTON_DUAL_PRESS_TIMEOUT);
        }
      }
    }
    return false;
  }
  void update(){
    if(callbackAvailable()){
      // reset if the timeout has passed
      if(timeout.complete()){
        reset();
        flags.off(BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE);
      }
    }
  }
  // when pages change on BMC buttons are locked out until they are all released
  // this is by design to avoid one press of a button changing pages too many times
  // because of this we have to add this call which resets the dual press handler
  // anytime there's a page change.
  void pageChanged(){
    if(callbackAvailable()){
      reset();
      timeout.stop();
      flags.off(BMC_BUTTONS_DUAL_WAITING_FOR_RELEASE);
    }
  }
private:
  int8_t last = -1;
  int8_t releaseA = -1;
  int8_t releaseB = -1;
  BMCTimer timeout;
  BMCFlags <uint8_t> flags;
  BMCCallbacks& callback;

  void reset(){
    last = -1;
    releaseA = -1;
    releaseB = -1;
  }
  bool callbackAvailable(){
    if(!flags.read(BMC_BUTTONS_DUAL_GLOBAL)){
      if(callback.buttonDualPress){
        return true;
      }
    } else {
      if(callback.globalButtonDualPress){
        return true;
      }
    }
    return false;
  }
  void triggerCallback(uint8_t btn1, uint8_t btn2){
    if(!flags.read(BMC_BUTTONS_DUAL_GLOBAL)){
      if(callback.buttonDualPress){
        callback.buttonDualPress(btn1, btn2);
      }
    } else {
      if(callback.globalButtonDualPress){
        callback.globalButtonDualPress(btn1, btn2);
      }
    }
  }
};

#endif
#endif
