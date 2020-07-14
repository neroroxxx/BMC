/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This class handles Non-Latching relays.
  With Non-Latching relays the pin must remain HIGH or LOW
*/
#ifndef BMC_RELAYNL_H
#define BMC_RELAYNL_H

#include "utility/BMC-Def.h"

#define BMC_FLAG_NL_RELAY_STATE 0
#define BMC_FLAG_NL_RELAY_STATE_CHANGED 1
#define BMC_FLAG_NL_RELAY_MOMENTARY_MODE 2
#define BMC_FLAG_NL_RELAY_REVERSE 3

class BMCRelayNL {
public:
  BMCRelayNL(){
    // turn the relay of it's off position when BMC first starts
    reset();
  }
  // begin, if the pin value is 255 only, and t_pin is not 255
  // the BMC-Pins.h object will return 255 if the pot doesn't have a pin defined
  // this method will only work the first time it's called
  void begin(uint8_t t_pin=255, bool momentary = false, bool reverse = false){
    if(pin!=255 || t_pin==255){
      return;
    }
    pin = t_pin;
    pinMode(pin, OUTPUT);
    setMomentary(momentary);
    setReverse(reverse);
    reassign();
  }
  // the update method does nothing for non-latching relay but we keep it
  // so it matching the latching relay class
  bool update(){
    if(timerMomentary.complete()){
      off();
    }
    return getState();
  }
  void reassign(){
    if(isOn()){
      digitalWrite(pin, isReverse() ? LOW : HIGH);
    } else {
      digitalWrite(pin, isReverse() ? HIGH : LOW);
    }
  }
  bool isMomentary(){
    return flags.read(BMC_FLAG_NL_RELAY_MOMENTARY_MODE);
  }
  bool isReverse(){
    return flags.read(BMC_FLAG_NL_RELAY_REVERSE);
  }
  void setMomentary(bool momentary){
    flags.write(BMC_FLAG_NL_RELAY_MOMENTARY_MODE, momentary);
  }
  void setReverse(bool reverse){
    flags.write(BMC_FLAG_NL_RELAY_REVERSE, reverse);
  }
  // when a relay is set to MOMENTARY it will only TOGGLE
  // the relay will be set to it's CLOSED state then back to OPEN after 50ms
  void command(uint8_t cmd){
    if(isMomentary()){
      toggle();
      return;
    }
    switch(cmd){
      case BMC_RELAY_NO:
        off();
        break;
      case BMC_RELAY_NC:
        on();
        break;
      case BMC_RELAY_TOGGLE:
        toggle();
        break;
    }
  }
  // return the current state of the RELAY, true (on), false (off)
  // the state of the RELAY is stored to a flag, this is done so we don't have
  // always do a digitalRead() since blinking and pulsing don't read the actual
  // state of the RELAY but weather it was turned on/off via the write() method
  bool getState(){
    return flags.read(BMC_FLAG_NL_RELAY_STATE);
  }
  // turn the RELAY on or off via t_state (true/false)
  void setState(bool t_state){
    if(t_state!=getState()){
      write(t_state);
    }
  }
  // turn the RELAY to the SET
  void on(){
    write(true);
  }
  // turn the RELAY to RESET
  void off(){
    write(false);
  }
  // we add have some overloaded functions here
  void set(){on();}
  void close(){on();}
  void unset(){off();}
  void open(){off();}
  // toggle the state of the RELAY on/off
  void toggle(){
    write(!getState());
  }
  // check if the RELAY is on
  bool isOn(){
    return read();
  }
  // returns true if the RELAY has changed it's state between on/off
  // this method returns true only once after the state has changed
  bool stateChanged(){
    return flags.toggleIfTrue(BMC_FLAG_NL_RELAY_STATE_CHANGED);
  }

private:
  uint8_t pin = 255;
  BMCFlags <uint8_t> flags;
  BMCTimer timerMomentary;
  // reset flags and turn the RELAY to it's off position
  void reset(){
    flags.reset();
    // turn the RELAY off
    digitalWrite(pin,LOW);
  }
  // read the digital value of the RELAY
  bool read(){
    return flags.read(BMC_FLAG_NL_RELAY_STATE);
  }
  // turn the RELAY on/off, when a BMC RELAY is turned on or off we don't just
  // want to set the digitalWrite value but also set a couple of flags to
  // track the state.
  // We set the new state of the RELAY to a flag and if we only do a digitalWrite
  // if the new value is different than the current one
  // we also set a STATE CHANGED flag in case we need to be notified when and
  // RELAY has changed states
  // t_value = true (RELAY on position), false (RELAY off position)
  void write(bool t_value){
    #if !defined(BMC_FAST_MODE)
    // ignore if RELAY was not enabled
    if(pin==255){
      return;
    }
    #endif
    // if new value is different than the current state we set it
    if(t_value == getState()){
      return;
    }
    // turn the RELAY to it's on or off position
    // could be replaced with digitalWrite(pin,t_value?HIGH:LOW);
    digitalWrite(pin, isReverse() ? !t_value : t_value);

    // set the RELAY STATE flag value to the same as the value passed
    flags.write(BMC_FLAG_NL_RELAY_STATE, t_value);
    // we set the STATE CHANGED flag on
    flags.on(BMC_FLAG_NL_RELAY_STATE_CHANGED);

    if(isMomentary()){
      timerMomentary.start(BMC_RELAYS_MOMENTARY_HOLD);
    }
  }
};
#endif
