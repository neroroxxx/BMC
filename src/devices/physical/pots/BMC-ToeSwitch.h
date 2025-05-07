/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_POT_TOE_SWITCH_H
#define BMC_POT_TOE_SWITCH_H

#include "utility/BMC-Def.h"
#include "devices/physical/pots/BMC-StateMachine.h"

#define BMC_FLAG_POT_TOE_SWITCH_AVAILABLE       0
#define BMC_FLAG_POT_TOE_SWITCH_STATE           1
#define BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED   2


class BMCPotToeSwitch {
public:
  BMCPotToeSwitch(BMCPotStateMachine & t_stateMachine):stateMachine(t_stateMachine){
    reset();
  }
  
  void begin(){
    
  }

  void update(){
    // toe switch timing
    if(isAvailable()){
      switch(getMode()){
        case 0:
          handleModeAutoEngage();
          break;
        case 1:
          handleModeToeSwitch();
          break;
      }
    }
  }

  void assign(bmcEvent_t t_engage, bmcEvent_t t_disengage, uint8_t t_settings){
    if(t_engage > 0 && t_disengage > 0){
      toeOnEvent = t_engage;
      toeOffEvent = t_disengage;
      settings = t_settings;
      flags.on(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
    } else {
      toeOnEvent = 0;
      toeOffEvent = 0;
      settings = 0;
      flags.off(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
    }
  }

  bool isActive(){
    if(!isAvailable()){
      return false;
    }
    return flags.toggleIfTrue(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
  }

  bool isAvailable(){
    return flags.read(BMC_FLAG_POT_TOE_SWITCH_AVAILABLE);
  }

  bool getState(){
    return flags.read(BMC_FLAG_POT_TOE_SWITCH_STATE);
  }

  uint8_t getOffValue(){
    // use 3 bits for off value (0-2)
    return ((settings & 0x07) + 1) * 5;
  }

  uint16_t getOffSpeed(){
    // use 3 bits for off speed (3-5)
    uint8_t offSpeedValue = ((settings >> 3) & 0x07);
    return ((offSpeedValue + 1) * 100) + 200;
  }

  uint8_t getMode(){
    // use 2 bits for Mode (6-7)
    return (settings>>6) & 0x03;
  }

  bmcEvent_t getEvent(){
    if(getState()){
      return toeOnEvent;
    }
    return toeOffEvent;
  }
  
  // default mode is AUTO-ENGAGE

  // * Auto Engage Mode
  // * The Toe Switch Engage Event is sent as soon as the potentiometer moves past the Engage Value.
  // * When the potentiometer returns to the Engage Value position (or lower), a timer starts based on the configured Engage Speed.
  // * Once the timer completes, the Toe Switch Disengage Event is sent.
  // * Each event is triggered only once per switch state change.
  void handleModeAutoEngage(){
    uint8_t value = stateMachine.read();
    uint8_t lastValue = stateMachine.getLastValue();
    
    uint8_t offValue = getOffValue();
    uint16_t offSpeed = getOffSpeed();
    if(!getState()){
      // engage
      if(value >= offValue){
        flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE);
        flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
        timer.stop();
      }
    } else {
      // disengage
      if(value<=offValue && value!=lastValue){
        timer.start(offSpeed);
      } else if(value>offValue){
        timer.stop();
      }
      if(timer.complete()){
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
  void handleModeToeSwitch(){
    uint8_t value = stateMachine.read();
    uint8_t lastValue = stateMachine.getLastValue();

    uint8_t trigger = (127 - getOffValue());
    if(value >= trigger){
      if(lastValue < trigger){
        timer.start(getOffSpeed());
      }
    } else {
      timer.stop();
    }
    if(timer.complete()){
      flags.toggle(BMC_FLAG_POT_TOE_SWITCH_STATE);
      flags.on(BMC_FLAG_POT_TOE_SWITCH_STATE_CHANGED);
    }
  }
  void reset(){
    flags.reset(1 << BMC_FLAG_POT_TOE_SWITCH_STATE);
  }

private:
  BMCFlags <uint8_t> flags;

  BMCPotStateMachine & stateMachine;

  BMCTimer timer;
  bmcEvent_t toeOnEvent = 0;
  bmcEvent_t toeOffEvent = 0;
  uint8_t settings = 0;

  

};
#endif
