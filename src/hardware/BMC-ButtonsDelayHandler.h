/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
  
  Class handles one delay event per button
  Delays work saving the even that will be delayed then returning it once
  it's timer has ended
*/
#ifndef BMC_BUTTONS_DELAY_HANDLER_H
#define BMC_BUTTONS_DELAY_HANDLER_H
#if defined(BMC_BUTTON_DELAY_ENABLED) && BMC_MAX_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 1
#include "utility/BMC-Def.h"
#include "hardware/BMC-Button.h"

#if BMC_MAX_BUTTONS > 32
  #define BMC_BUTTONS_DELAY_HANDLER_INT_TYPE uint32_t
#elif BMC_MAX_BUTTONS > 8
  #define BMC_BUTTONS_DELAY_HANDLER_INT_TYPE uint16_t
#else
  #define BMC_BUTTONS_DELAY_HANDLER_INT_TYPE uint8_t
#endif

#define BMC_BUTTONS_DELAY_FLAG_HAS_ACTIVE_DELAY 0

class BMCButtonsDelayHandler {
public:
  BMCButtonsDelayHandler(){

  }
  uint8_t update(){
#if BMC_MAX_BUTTONS > 32
    if(btnFlags[0].read()+btnFlags[1].read()==0){
      return 255;
    }
    for(uint8_t i = 0 ; i < BMC_MAX_BUTTONS ; i++){
      if(timer[i].complete()){
        if(i>=32){
          btnFlags[1].off(i-32);
        } else {
          btnFlags[0].off(i);
        }
        return i;
      }
    }
#else
    if(btnFlags[0].read()==0){
      return 255;
    }
    for(uint8_t i = 0 ; i < BMC_MAX_BUTTONS ; i++){
      if(timer[i].complete()){
        btnFlags[0].off(i);
        return i;
      }
    }
#endif

    return 255;
  }
  bmcStoreButtonEvent getEvent(uint8_t buttonIndex){
    if(buttonIndex>=BMC_MAX_BUTTONS){
      bmcStoreButtonEvent resp;
      return resp;
    }
    clearQueued();
    return eventQueue[buttonIndex];
  }
  uint8_t getType(uint8_t buttonIndex){
    if(buttonIndex>=BMC_MAX_BUTTONS){
      return BMC_NONE;
    }
    clearQueued();
    return BMC_GET_BYTE(0,eventQueue[buttonIndex].event);
  }
  void setThreshold(uint8_t t){
    threshold = (t>=1 && t<=200) ? t : 1;
  }
  void queueDelay(uint8_t buttonIndex, uint8_t eventIndex, uint8_t pressType, bmcStoreButtonEvent event){
    // invalid button index or a delay already exists and is waiting to be sent
    if(buttonIndex>=BMC_MAX_BUTTONS || eventIndex>=BMC_MAX_BUTTON_EVENTS || timer[buttonIndex].active()){
      return;
    }
    uint8_t index = 0;
    uint8_t bIndex = buttonIndex;
#if BMC_MAX_BUTTONS > 32
    if(buttonIndex >= 32){
      index++;
      bIndex -= 32;
    }
#endif
    // now the next eventIndex will be the one we'll actually Queue
    // check if there's a queue for this button
    if(btnFlagsQueued[index].read(bIndex)){
      // there is a queue now let's match the queued event index and press type
      if(queueActive() && (buttonIndex==queuedButtonIndex && pressType==queuedPressType && eventIndex>=queuedEventIndex)){
        // both match so let's save it to the eventQueue and start the timer
        eventQueue[buttonIndex] = event;
        timer[buttonIndex].start(threshold*10);
        btnFlagsQueued[index].off(bIndex);
        btnFlags[index].on(bIndex);
        BMC_PRINTLN("SETTING DELAY, threshold:",threshold,", buttonIndex:",buttonIndex);
      }
    } else {
      // if the event that has the delay is the last event in the button
      // we ignore since there will not be anything to delay after it
      if(eventIndex>=(BMC_MAX_BUTTON_EVENTS-1)){
        return;
      }
      // there's nothing queued yet so we'll set a queue for the next event
      queuedButtonIndex = buttonIndex;
      queuedPressType = pressType;
      queuedEventIndex = eventIndex+1;
      btnFlagsQueued[index].on(bIndex);
      BMC_PRINTLN("QUEUE DELAY, queuedPressType:",queuedPressType,", queuedEventIndex:",queuedEventIndex);
    }
  }
  bool setDelayedEvent(uint8_t buttonIndex, uint8_t eventIndex,
                        uint8_t pressType, bmcStoreButtonEvent event){
    if(queueActive() && (buttonIndex==queuedButtonIndex && pressType==queuedPressType && eventIndex>=queuedEventIndex)){
      queueDelay(buttonIndex, eventIndex, pressType, event);
      return timer[buttonIndex].active();
    }
    return false;
  }
  void clearQueued(){
    queuedButtonIndex = -1;
    queuedEventIndex = -1;
    queuedPressType = -1;
  }
  bool queueActive(){
    return queuedEventIndex>=0 && queuedPressType>=0;
  }
private:
  uint8_t total = BMC_MAX_BUTTONS>32 ? 2 : 1;
  int queuedButtonIndex = -1;
  int queuedEventIndex = -1;
  int queuedPressType = -1;
  uint8_t threshold = 1;
  BMCFlags <uint8_t> flags;

  BMCFlags <BMC_BUTTONS_DELAY_HANDLER_INT_TYPE> btnFlags[BMC_MAX_BUTTONS>32?2:1];
  BMCFlags <BMC_BUTTONS_DELAY_HANDLER_INT_TYPE> btnFlagsQueued[BMC_MAX_BUTTONS>32?2:1];

  BMCTimer timer[BMC_MAX_BUTTONS];
  bmcStoreButtonEvent eventQueue[BMC_MAX_BUTTONS];
  void reset(){
    btnFlags[0].reset();
#if BMC_MAX_BUTTONS > 32
    btnFlags[1].reset();
#endif
  }
};

#endif
#endif
