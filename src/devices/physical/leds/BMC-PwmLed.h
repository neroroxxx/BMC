/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  PWM LEDs behave similarly to standard LEDs except they don't have BLINK or PULSE
  the pulse method is available for better compatibility with BMCLed but it will
  only turn the LED on

  A PWM LED can have a brightness value of 0 to 255
*/
#ifndef BMC_PWM_LED_H
#define BMC_PWM_LED_H

#include "utility/BMC-Def.h"

#define BMC_FLAG_PWM_LED_BLINK_ENABLED 0
#define BMC_FLAG_PWM_LED_BLINK_STATE 1
#define BMC_FLAG_PWM_LED_STATE 2
#define BMC_FLAG_PWM_LED_STATE_CHANGED 3
#define BMC_FLAG_PWM_LED_TEMP_BLINK 4

class BMCPwmLed {
public:
  BMCPwmLed(){
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
    // check if the pin is Analog capable
    if(!BMCBuildData::isPwmPin(t_pin)){
      BMC_ERROR(
        "PIN:", t_pin,
        "Can NOT be used with PWM Leds as it is NOT PWM Capable"
      );
      BMC_HALT();
    }
    pin = t_pin;
    pinMode(pin, OUTPUT);
    // is this line below needed for PWM?
    //pinMode(pin, OUTPUT);
    // reset all falags and turn the LED off
    reset();
#if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
    test();
#endif
  }
  void overrideState(bool t_value){
    _analogWrite(t_value?BMC_LED_PWM_MAX_VALUE:0);
  }
  void setPwmOffValue(bool t_value){
    offValue = (t_value) ? BMC_LED_PWM_DIM_VALUE : 0;
    if(offValue >= BMC_LED_PWM_MAX_VALUE){
      offValue = 0;
    }
    if(pin!=255 && !flags.read(BMC_FLAG_PWM_LED_STATE)){
      _analogWrite(offValue);
    }
  }
  // reassign the LED behaviour, used when switching layers or the editor
  // has updated EEPROM
  void reassign(){
    reset();
  }
  // test the LED by fading it's brightness from 0 to 255
  // then back to it's previous state
  void test(){
    for(uint8_t i=0;i<3;i++){
      _analogWrite(BMC_LED_PWM_MAX_VALUE);
      delay(BMC_MAX_LED_TEST_DELAY);
      _analogWrite(0);
      delay(BMC_MAX_LED_TEST_DELAY);
    }
    // set the LED to it's previous state
    _analogWrite(currentValue);
  }
  // this method will return true if the LED is has a
  // brightness value higher than 0
  bool update(){
    if(handleQuickBlinker()){
      return getState();
    }
    if(pulseTimer.complete()){
      off();
    }
    return getState();
  }
  // used to blink an led temporarily, similar to the test() method but
  // it can be used to blink an led temporarily then reset back to its
  // current state
  // blink it even if the led is inactive
  void quickBlink(uint8_t t_value){
    quickBlinkerValue = t_value==0 ? BMC_LED_PWM_MAX_VALUE : map(t_value, 0, 127, 0, BMC_LED_PWM_MAX_VALUE);
    flags.on(BMC_FLAG_PWM_LED_TEMP_BLINK);
    quickBlinkerTimer.start(0);
  }
  bool handleQuickBlinker(){
    if(flags.read(BMC_FLAG_PWM_LED_TEMP_BLINK)){
      if(quickBlinkerTimer.complete()){
        if(BMC_IS_EVEN(quickBlinkerCount)){
          _analogWrite(flags.read(BMC_FLAG_PWM_LED_STATE) ? quickBlinkerValue : 0);
        } else {
          _analogWrite(flags.read(BMC_FLAG_PWM_LED_STATE) ? 0 : quickBlinkerValue);
        }
        quickBlinkerTimer.start(100);
        quickBlinkerCount++;
        if(quickBlinkerCount >= BMC_LEDS_MAX_TEMP_BLINKER){
          quickBlinkerCount = 0;
          flags.off(BMC_FLAG_PWM_LED_TEMP_BLINK);
          quickBlinkerTimer.stop();
          // get the currentvalue that the led should be at and map it
          uint8_t b = map(currentValue,0,127,0,BMC_LED_PWM_MAX_VALUE);
          // turn the LED to it's previous state before quick blink
          _analogWrite(flags.read(BMC_FLAG_PWM_LED_STATE) ? b : offValue);
        }
      }
      return true;
    }
    return false;
  }
  // return true if the LED has a brightness value higher than 0
  bool getState(){
    return flags.read(BMC_FLAG_PWM_LED_STATE);
  }
  // set a brightness value for the LED (0 to 255)
  void setValue(uint8_t t_value){
    write( (t_value==0) ? 255 : (t_value & 0x7F));
  }
  // same as setValue but used to match the BMCLed class
  void setState(uint8_t t_value){
    setValue(t_value);
  }
  // get the brighness value of the LED
  uint8_t getValue(){
    return currentValue;
  }
  // turn the LED to max brightness
  void on(){
    write(127);
  }
  // turn the LED off
  void off(){
    // value of 255 is OFF but it will bring us to the offValue
    write(255);
  }
  // toggle the LED from on (max) / off and vice-versa
  // if the brightness value is more than 0 it will turn it off
  void toggle(){
    if(currentValue>0){
      // value of 255 is OFF but it will bring us to the offValue
      write(255);
    } else {
      write(127);
    }
  }
  // turn the LED on for a short period of time then automatically turn it off
  // BMC_LED_PULSE_TIMEOUT specifies how long to keep the LED on before
  // automatically turn it off via the update() method
  void pulse(uint8_t t_value=127){
    write(t_value);
    pulseTimer.start(BMC_LED_PULSE_TIMEOUT);
  }
  // is the value of the LED more than 0 (on)
  bool isOn(){
    return read();
  }
  // has the LED changed it's state from on/off and vice-versa
  bool stateChanged(){
    return flags.toggleIfTrue(BMC_FLAG_PWM_LED_STATE_CHANGED);
  }
private:
  BMCFlags <uint8_t> flags;
  // LED pin
  uint8_t pin = 255;
  // off value used to dim leds when settings are set for it
  uint8_t offValue = 0;
  // the value set by the write() method
  uint8_t currentValue = 0;
  // temporary blinker
  BMCTimer quickBlinkerTimer;
  uint8_t quickBlinkerCount = 0;
  uint8_t quickBlinkerValue = 127;
  // timer to automatically turn the LED off after pulse() was called
  BMCTimer pulseTimer;
  // reset flags and turn LED off
  void reset(){
    flags.reset();
    currentValue = 0;
    _analogWrite(offValue);
  }
  void _analogWrite(uint16_t t_value){
    #if defined(BMC_REVERSE_LED_POLARITY)
      analogWrite(pin, map(t_value, 0, BMC_LED_PWM_MAX_VALUE, BMC_LED_PWM_MAX_VALUE, 0));
    #else
      analogWrite(pin, t_value);
    #endif
  }
  // is the value of the LED more than 0 (on)
  bool read(){
    return currentValue>0;
  }
  // write a new value to the LED
  void write(uint8_t t_value){
    // if the write value is 255 it means we are turning the LED off
    // using the off() or toggle() method, in this case we wanna handle
    // things differently so we can make use of the DIM off value
    bool useOffValue = false;
    if(t_value==255){
      useOffValue = true;
      t_value = 0;
    }
    // if the new value is different than the current value we proceed
    if(currentValue != t_value){
      // we only trigger the state change if value is changing from 0 or to 0
      if((currentValue==0 && t_value > 0) || (t_value==0 && currentValue > 0)){
        flags.on(BMC_FLAG_PWM_LED_STATE_CHANGED);
      }
      //
      _analogWrite(useOffValue ? offValue : map(t_value, 0, 127, 0, BMC_LED_PWM_MAX_VALUE));

      // store the new value for the LED and write it
      currentValue = t_value;
      // if the new value is higher than 0 the LED is on
      flags.write(BMC_FLAG_PWM_LED_STATE, currentValue>0);
    }
  }
};
#endif
