/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This class handles Non-Latching relays with Dual Coils not the types
  that reversed polarity.

  Pin A must be connected to the SET coil
  Pin B must be connected to the RESET coil

  on()/set() powers the coil in Pin A (pin B is set to LOW first)
  off()/unset() powers the coil in Pin B (pin A is set to LOW first)

  The pin for each coil is pulled HIGH temporarily, this time is specified
  by BMC_L_RELAY_HOLD_TIME, this can be overloaded in your config file
  just define BMC_L_RELAY_HOLD_TIME with the number of milliseconds you want
  the Pin to pulse HIGH for, the default time is 15 milliseconds
*/
#ifndef BMC_RELAYL_H
#define BMC_RELAYL_H

#include "utility/BMC-Def.h"

#define BMC_FLAG_L_RELAY_STATE 0
#define BMC_FLAG_L_RELAY_STATE_CHANGED 1
#define BMC_FLAG_L_RELAY_MOMENTARY_MODE 2
#define BMC_FLAG_L_RELAY_REVERSE 3

class BMCRelayL {
public:
  BMCRelayL(){
    // turn the relay of it's off position when BMC first starts
    reset();
  }
  // begin, if the pin value is 255 only, and t_pin is not 255
  // the BMC-Pins.h object will return 255 if the pot doesn't have a pin defined
  // this method will only work the first time it's called
  void begin(uint8_t t_pinSet=255, uint8_t t_pinUnset=255, bool momentary = false, bool reverse = false){
    if(pinSet!=255 || pinUnset!=255){
      return;
    }
    if(t_pinSet==255 || t_pinUnset==255 || t_pinSet==t_pinUnset){
      BMC_ERROR(
        "PINS:", t_pinSet, "and" ,t_pinUnset,
        "are invalid, make sure you check that the pins were defined in your config"
      );
      BMC_HALT();
    }
    pinSet = t_pinSet;
    pinUnset = t_pinUnset;
    pinMode(pinSet, OUTPUT);
    pinMode(pinUnset, OUTPUT);
    setMomentary(momentary);
    setReverse(reverse);
    reassign();
  }
  // the update method does nothing for non-latching relay but we keep it
  // so it matching the latching relay class
  bool update(){
    if(timer.complete()){
      if(!isReverse()){
        digitalWrite(pinSet, LOW);
        digitalWrite(pinUnset, LOW);
      } else {
        digitalWrite(pinSet, HIGH);
        digitalWrite(pinUnset, HIGH);
      }
    }
    if(timerMomentary.complete()){
      off();
    }
    return getState();
  }
  void reassign(){
    if(!isReverse()){
      digitalWrite(pinSet, LOW);
      digitalWrite(pinUnset, LOW);
    } else {
      digitalWrite(pinSet, HIGH);
      digitalWrite(pinUnset, HIGH);
    }
  }
  bool isMomentary(){
    return flags.read(BMC_FLAG_L_RELAY_MOMENTARY_MODE);
  }
  bool isReverse(){
    return flags.read(BMC_FLAG_L_RELAY_REVERSE);
  }
  void setMomentary(bool momentary){
    flags.write(BMC_FLAG_L_RELAY_MOMENTARY_MODE, momentary);
  }
  void setReverse(bool reverse){
    flags.write(BMC_FLAG_L_RELAY_REVERSE, reverse);
  }
  // when a relay is set to MOMENTARY it will only TOGGLE
  // the relay will be set to it's STE state then back to RESET after 50ms
  void command(uint8_t cmd, bool forced=false){
    if(isMomentary()){
      toggle(forced);
      return;
    }

    switch(cmd){
      case BMC_RELAY_NO:
        // BMC_PRINTLN("BMC_RELAY_RESET...");
        off(forced);
        break;
      case BMC_RELAY_NC:
        // BMC_PRINTLN("BMC_RELAY_SET");
        on(forced);
        break;
      case BMC_RELAY_TOGGLE:
        // BMC_PRINTLN("BMC_RELAY_TOGGLE");
        toggle(forced);
        break;
    }
  }
  // return the current state of the RELAY, true (set), false (unset)
  // the state of the RELAY is stored to a flag, this is done so we don't have
  // always do a digitalRead() since blinking and pulsing don't read the actual
  // state of the RELAY but weather it was turned on/off via the write() method
  bool getState(){
    return flags.read(BMC_FLAG_L_RELAY_STATE);
  }
  // turn the RELAY on or off via t_state (true/false)
  void setState(bool t_state){
    if(t_state!=getState()){
      write(t_state);
    }
  }
  // turn the RELAY to the SET
  void on(bool forced=false){
    write(true, forced);
  }
  // turnt he RELAY RESET
  void off(bool forced=false){
    write(false, forced);
  }
  // we add have some overloaded functions here
  void set(bool forced=false){on(forced);}
  void close(bool forced=false){on(forced);}
  void unset(bool forced=false){off(forced);}
  void open(bool forced=false){off(forced);}

  // toggle the state of the RELAY on/off
  void toggle(bool forced=false){
    write(!getState(), forced);
  }
  // check if the RELAY is on
  bool isOn(){
    return read();
  }
  // returns true if the RELAY has changed it's state between on/off
  // this method returns true only once after the state has changed
  bool stateChanged(){
    return flags.toggleIfTrue(BMC_FLAG_L_RELAY_STATE_CHANGED);
  }

private:
  // set pin
  uint8_t pinSet = 255;
  // unset pin
  uint8_t pinUnset = 255;
  BMCTimer timer;
  BMCTimer timerMomentary;
  BMCFlags <uint8_t> flags;

  // reset flags and turn the RELAY to it's unset position
  void reset(){
    flags.reset();
    // turn the both pins to LOW
    digitalWrite(pinSet,LOW);
    digitalWrite(pinUnset,LOW);
  }
  // read the digital value of the RELAY
  bool read(){
    return flags.read(BMC_FLAG_L_RELAY_STATE);
  }
  // turn the RELAY on/off, when a BMC RELAY is turned on or off we don't just
  // want to set the digitalWrite value but also set a couple of flags to
  // track the state.
  // We set the new state of the RELAY to a flag and if we only do a digitalWrite
  // if the new value is different than the current one
  // we also set a STATE CHANGED flag in case we need to be notified when and
  // RELAY has changed states
  // t_value = true (RELAY on position), false (RELAY off position)
  void write(bool t_value, bool forced=false){
    // if new value is different than the current state we set it
    if((t_value == getState()) && !forced){
      return;
    }
    // we're still energizing the coil so don't do anything
    if(timer.active()){
      return;
    }
    // turn the RELAY between SET and RESET positions
    // pinSet is the SET position
    // pinUnset is the RESET position
    if(!isReverse()){
      digitalWrite(pinSet, t_value);
      digitalWrite(pinUnset, !t_value);
    } else {
      digitalWrite(pinSet, !t_value);
      digitalWrite(pinUnset, t_value);
    }
    // start the timer to set the SET/RESET pin LOW
    timer.start(BMC_L_RELAY_HOLD_TIME);
    // set the RELAY STATE flag value to the same as the value passed
    flags.write(BMC_FLAG_L_RELAY_STATE,t_value);
    // we set the STATE CHANGED flag on
    flags.on(BMC_FLAG_L_RELAY_STATE_CHANGED);

    if(isMomentary()){
      timerMomentary.start(BMC_RELAYS_MOMENTARY_HOLD);
    }
  }
};
#endif
