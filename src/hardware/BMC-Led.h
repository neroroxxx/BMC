/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  BMC Leds have 2 modes:

  SOLID: LED will either be on or off when calling on(), off(), toggle()
         the LED may also PULSE which turns the LED on and then turns it off
         after the number of milliseconds specified by BMC_LED_PULSE_TIMEOUT
         has passed after pulse() has been called.
         The pulse() method only works if the LED is set to SOLID

  BLINK: LED will turn on/off based on the number of milliseconds specified
         by BMC_LED_BLINK_TIMEOUT.
         If an LED is set to Blink the Pulse() method will be ignored

         NOTE: boths BMC_LED_PULSE_TIMEOUT & BMC_LED_BLINK_TIMEOUT can be
               overitten by the config file, these are defined in
               utility/BMC-Def.h

*/
#ifndef BMC_LED_H
#define BMC_LED_H

#include "utility/BMC-Def.h"

#define BMC_FLAG_LED_STATE 0
#define BMC_FLAG_LED_BLINK_ENABLED 1
#define BMC_FLAG_LED_BLINKER_STATE 2
#define BMC_FLAG_LED_STATE_CHANGED 3
#define BMC_FLAG_LED_TEMP_BLINK 4
#define BMC_FLAG_LED_IS_PWM 5
#define BMC_FLAG_LED_USE_OFF_VALUE 6
// flag 7 available
#define BMC_FLAG_LED_MUX 8
#define BMC_FLAG_LED_MUX_VALUE 9
#define BMC_FLAG_LED_MUX_TESTING 10

class BMCLed {
public:
  BMCLed(){
    // initialize with the pin number as 255
    // if the pin is 255 it means the begin method has not been called
    pin = 255;
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
/*
#if BMC_MAX_MUX_GPIO > 0
// all mux pins start with pin number 64, that includes MUX_IN MUX_IN_ANALOG
// BMC will group them in this order MUX_IN then MUX_IN_ANALOG
// so if you have 10 MUX_IN pins then pins 64 to 73 are MUX_IN pins
// then MUX_IN_ANALOG pins start at pin 74 and so on
// so we want to make sure this pot was set to a MUX_IN_ANALOG
if(t_pin>=64){
  if(BMCBuildData::isMuxOutPin(t_pin)){
    flags.on(BMC_FLAG_LED_MUX);
    pin = t_pin;
    reset();
    blinker.start(BMC_LED_BLINK_TIMEOUT);
    return;
  } else {
    BMC_ERROR(
      "Mux Pin:", t_pin,
      "Can NOT be used with Leds as it is NOT a Mux Out Pin"
    );
    BMC_HALT();
  }
}
#endif
*/
#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    // all mux pins start with pin number 64, that includes MUX_IN MUX_IN_ANALOG
    // BMC will group them in this order MUX_IN then MUX_IN_ANALOG
    // so if you have 10 MUX_IN pins then pins 64 to 73 are MUX_IN pins
    // then MUX_IN_ANALOG pins start at pin 74 and so on
    // so we want to make sure this pot was set to a MUX_IN_ANALOG
    if(t_pin>=64){
      if(BMCBuildData::isMuxOutPin(t_pin)){
        flags.on(BMC_FLAG_LED_MUX);
        pin = t_pin;
        reset();
        blinker.start(BMC_LED_BLINK_TIMEOUT);
        return;
      } else {
        BMC_ERROR(
          "Mux Pin:", t_pin,
          "Can NOT be used with Leds as it is NOT a Mux Out Pin"
        );
        BMC_HALT();
      }
    }
#endif

    if(!BMCBuildData::isDigitalPin(t_pin) && !BMCBuildData::isPwmPin(t_pin)){
      BMC_ERROR(
        "PIN:", t_pin,
        "Can NOT be used with LEDS as it is NOT Digital or PWM capable"
      );
      BMC_HALT();
    }
    pin = t_pin;

    pinMode(pin, OUTPUT);

    flags.write(BMC_FLAG_LED_IS_PWM, BMCBuildData::isPwmPin(pin));

#if defined(BMC_DEBUG)
    if(flags.read(BMC_FLAG_LED_IS_PWM)){
      BMC_PRINTLN("LED on pin", pin, "is PWM Capable");
    }
#endif

    reset();

    blinker.start(BMC_LED_BLINK_TIMEOUT);
  }
  uint8_t getPin(){
    return pin;
  }

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
  uint8_t getMuxPin(){
#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    if(flags.read(BMC_FLAG_LED_MUX)){
      return pin-64;
    }
#endif
    return pin;
  }
  bool getMuxState(){
    return flags.read(BMC_FLAG_LED_MUX_VALUE);
  }
  bool muxTesting(){
    return flags.toggleIfTrue(BMC_FLAG_LED_MUX_TESTING);
  }
#endif
  void overrideState(bool t_value){
    writeToPin(t_value);
  }
  void setPwmOffValue(bool value){
    // if the DIM value is more or equal to the max value we skip this part
    if(!isPwmCapable() || (BMC_LED_PWM_DIM_VALUE >= BMC_LED_PWM_MAX_VALUE)){
      flags.off(BMC_FLAG_LED_USE_OFF_VALUE);
      return;
    }
    flags.write(BMC_FLAG_LED_USE_OFF_VALUE, value);
    if(!flags.read(BMC_FLAG_LED_STATE)){
      writeToPin(false);
    }
  }
  // test LED led by blinking it, here we use delay since this is only used
  // at startup or if the editor is triggering a test of the LED
  // the LED will return to it's state before the test began
  void test(){
#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    if(flags.read(BMC_FLAG_LED_MUX)){
      flags.on(BMC_FLAG_LED_MUX_TESTING);
      return;
    }
#endif
    bool state = flags.read(BMC_FLAG_LED_STATE);
    for(uint8_t i=0;i<3;i++){
      writeToPin(!state);
      delay(BMC_MAX_LED_TEST_DELAY);
      writeToPin(state);
      delay(BMC_MAX_LED_TEST_DELAY);
    }
  }
  // used to blink an led temporarily, similar to the test() method but
  // it can be used to blink an led temporarily then reset back to its
  // current state
  void quickBlink(){
    flags.on(BMC_FLAG_LED_TEMP_BLINK);
    quickBlinkerTimer.start(0);
  }
  bool handleQuickBlinker(){
    if(flags.read(BMC_FLAG_LED_TEMP_BLINK)){
      if(quickBlinkerTimer.complete()){
        if(BMC_IS_EVEN(quickBlinkerCount)){
          writeToPin(flags.read(BMC_FLAG_LED_STATE));
        } else {
          writeToPin(!flags.read(BMC_FLAG_LED_STATE));
        }
        quickBlinkerTimer.start(100);
        quickBlinkerCount++;
        if(quickBlinkerCount>=BMC_LEDS_MAX_TEMP_BLINKER){
          quickBlinkerCount = 0;
          flags.off(BMC_FLAG_LED_TEMP_BLINK);
          quickBlinkerTimer.stop();
          writeToPin(flags.read(BMC_FLAG_LED_STATE));
        }
      }
      return true;
    }
    return false;
  }
  // set weather the LED will blink when on
  void setBlinkMode(bool t_mode){
    flags.write(BMC_FLAG_LED_BLINK_ENABLED, t_mode);
  }
  // reassign the LED behaviour, used when switching pages or the editor
  // has updated EEPROM
  void reassign(uint8_t t_blinkMode=false){
    reset();
    setBlinkMode(t_blinkMode);
  }
  // used to update the blink timer to turn the LED on/off
  // and the pulse timer which turns the LED off after the set threshold time
  // this method returns the current state of the led,
  // true if the LED is on (or blinking), false when the LED is off
  bool update(){
    // handle quick blink even if LED is not active
    if(handleQuickBlinker()){
      return getState();
    }
    // check if the LED is in BLINK mode
    if(flags.read(BMC_FLAG_LED_BLINK_ENABLED)){
      // when the LED is blinking the state will always be ON
      if(flags.read(BMC_FLAG_LED_STATE)){
        // if it's on we check if the blinker time has reached it's interval
        // and we then set the LED to the oposite state it's currently in
        if(blinker.complete()){
          writeToPin(flags.toggle(BMC_FLAG_LED_BLINKER_STATE));
        }
      } else {
        // if the state is OFF we just turn the LED off
        off();
      }
    } else {
      // if the LED is NOT in BLINK mode we check if the PULSE timer has been
      // activated and if so we turn the LED off once the timer has reached
      // it's interval
      if(pulseTimer.complete()){
        off();
      }
    }
    // return the current state of the LED, true (on), false (off)
    return getState();
  }
  // return the current state of the LED, true (on), false (off)
  // the state of the LED is stored to a flag, this is done so we don't have
  // always do a digitalRead() since blinking and pulsing don't read the actual
  // state of the LED but weather it was turned on/off via the write() method
  bool getState(){
    return flags.read(BMC_FLAG_LED_STATE);
  }
  // turn the LED on or off via t_state
  void setState(bool t_state){
    write(t_state);
  }
  // turn the LED on
  void on(){
    write(true);
  }
  // turnt he LED off
  void off(){
    write(false);
  }
  // toggle the state of the LED on/off
  void toggle(){
    write(!getState());
  }
  // turn the LED on for a short period of time then automatically turn it off
  // BMC_LED_PULSE_TIMEOUT specifies how long to keep the LED on before
  // automatically turn it off via the update() method
  void pulse(){
    // if the LED is in BLINK mode ignore pulsing
    if(!flags.read(BMC_FLAG_LED_BLINK_ENABLED)){
      // turn the LED on and start the pulse timer
      on();
      pulseTimer.start(BMC_LED_PULSE_TIMEOUT);
    }
  }
  // check if LED is in BLINK mode, this doesn't refer to if the LED is
  // currently blinking but only if the BLINK mode was set
  bool isBlinkEnabled(){
    return flags.read(BMC_FLAG_LED_BLINK_ENABLED);
  }
  // check if the LED is on
  bool isOn(){
    return flags.read(BMC_FLAG_LED_STATE);
  }
  // returns true if the LED has gone from on to off and vice-versa
  // this method returns true only once after the state has changed
  bool stateChanged(){
    return flags.toggleIfTrue(BMC_FLAG_LED_STATE_CHANGED);
  }
private:
  uint8_t pin = 255;
#if BMC_MAX_MUX_OUT == 0 && BMC_MAX_MUX_GPIO == 0
  BMCFlags <uint8_t> flags;
#else
  BMCFlags <uint16_t> flags;
#endif
  // endeless timer used for blinking the LED
  BMCEndlessTimer blinker;
  // temporary blinker
  BMCTimer quickBlinkerTimer;
  uint8_t quickBlinkerCount = 0;
  // timer to automatically turn the LED off after pulse() was called
  BMCTimer pulseTimer;
  bool isPwmCapable(){
    return flags.read(BMC_FLAG_LED_IS_PWM);
  }
  // reset flags and turn the LED off
  void reset(){
    // the flags.reset() will also set the LED STATE flag to off
    bool isPWM = flags.read(BMC_FLAG_LED_IS_PWM);
    bool userPwmOffValue = flags.read(BMC_FLAG_LED_USE_OFF_VALUE);
    bool blinkerState = flags.read(BMC_FLAG_LED_BLINKER_STATE);

    #if BMC_MAX_MUX_OUT == 0 && BMC_MAX_MUX_GPIO == 0
      flags.reset();
    #else
      flags.reset((1 << BMC_FLAG_LED_MUX));
    #endif

    flags.write(BMC_FLAG_LED_IS_PWM, isPWM);
    flags.write(BMC_FLAG_LED_USE_OFF_VALUE, userPwmOffValue);
    flags.write(BMC_FLAG_LED_BLINKER_STATE, blinkerState);

    // temp blinker reset
    quickBlinkerCount = 0;
    // turn the LED off
    writeToPin(false);
  }
  void writeToPin(bool t_value){
#if defined(BMC_REVERSE_LED_POLARITY)
    t_value = !t_value;
#endif

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
    if(flags.read(BMC_FLAG_LED_MUX)){
      flags.write(BMC_FLAG_LED_MUX_VALUE, t_value);
      return;
    }
#endif
    if(isPwmCapable()){
      if(flags.read(BMC_FLAG_LED_USE_OFF_VALUE)){
        analogWrite(pin, (t_value ? BMC_LED_PWM_MAX_VALUE : BMC_LED_PWM_DIM_VALUE));
      } else {
        analogWrite(pin, (t_value ? BMC_LED_PWM_MAX_VALUE : 0));
      }
    } else {
      digitalWrite(pin, t_value);
    }
  }
  // turn the LED on/off, when a BMC LED is turned on or off we don't just
  // want to set the digitalWrite value but also set a couple of flags to
  // track the state used by pulse and blinking
  // We set the new state of the LED to a flag and if we only do a digitalWrite
  // if the new value if different than the current one
  // we also set a STATE CHANGED flag if case we need to be notified when and
  // LED has changed states
  // t_value = true (LED on), false (LED off)
  // if BMC_REVERSE_LED_POLARITY is defined:
  // t_value = true (LED off), false (LED on)
  void write(bool t_value){
    // if new value is different than the current state of the LED we set it
    if(t_value != flags.read(BMC_FLAG_LED_STATE)){
      // turn the LED on or off
      writeToPin(t_value);
      // set the LED STATE flag value to the same as the LED value
      flags.write(BMC_FLAG_LED_STATE, t_value);
      // we set the STATE CHANGED flag on
      flags.on(BMC_FLAG_LED_STATE_CHANGED);
    }
  }
};
#endif
