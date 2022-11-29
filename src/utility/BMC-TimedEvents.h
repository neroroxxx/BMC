/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2021 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_TIMED_EVENTS_H
#define BMC_TIMED_EVENTS_H

#if BMC_MAX_TIMED_EVENTS > 0

#include "utility/BMC-Def.h"

#define BMC_TIMED_EVENTS_FLAG_AVAILABLE 0

#define BMC_TIMED_EVENTS_TIMER_FLAG_MODE 0
#define BMC_TIMED_EVENTS_TIMER_FLAG_TRIGGERED 1


class BMCTimedEvents {
public:
  BMCTimedEvents(BMCGlobals& t_globals, bmcStoreGlobal& t_global):globals(t_globals),global(t_global){

  }
  void buildListeners(){
    flags.off(BMC_TIMED_EVENTS_FLAG_AVAILABLE);
    totalReadyTimedEvents = 0;
    for(uint8_t i=0;i<BMC_MAX_TIMED_EVENTS;i++){
      bmcStoreDevice <2, 1>& device = global.timedEvents[i];
      if(device.events[0]>0){
        flags.on(BMC_TIMED_EVENTS_FLAG_AVAILABLE);
        totalReadyTimedEvents = i+1;
        // set the mode, single or loop
        uint8_t mode = (device.settings[1]>>2) & 0x03;
        setMode(i, mode);
      } else {
        // if there's no event we stop the timer
        timers[i].stop();
      }
    }
    BMC_PRINTLN("BMCTimedEvents::buildListeners() ",totalReadyTimedEvents);
  }
  void trigger(uint8_t n){
    // trigger the start of a timer
    if(n >= BMC_MAX_TIMED_EVENTS){
      return;
    }
    bmcStoreDevice <2, 1>& device = global.timedEvents[n];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    // first check if the timed event has any event data
    if(data.type == BMC_NONE){
      return;
    }
    uint16_t timeoutMs = (device.settings[0] + 1) * 10;
    // 0=restart, 1=stop, 2=ignore
    uint8_t retrigger = device.settings[1] & 0x03;
    // 0=single, 1=loop
    uint8_t mode = (device.settings[1]>>2) & 0x03;
    // check if timer is active
    if(timers[n].active()){
      // timer is active, check how to re-trigger it.
      if(isLooped(n)){
        timers[n].stop();
        setTriggered(n, false);
        BMC_PRINTLN("timed event LOOP",n,"re-triggered STOPPING");
        return;
      }
      if(retrigger==BMC_TIMED_EVENT_RESTART){
        timers[n].start(timeoutMs);
        BMC_PRINTLN("timed event SINGLE",n,"re-triggered RESTART");
      } else if(retrigger==BMC_TIMED_EVENT_STOP){
        timers[n].stop();
        setTriggered(n, false);
        BMC_PRINTLN("timed event SINGLE",n,"re-triggered STOP");
      } else {
        // ignore
        BMC_PRINTLN("timed event SINGLE",n,"re-triggered IGNORE");
      }
      return;
    }
    // timer is inactive, start it
    timers[n].start(timeoutMs);
    setMode(n, mode);
    setTriggered(n, true);
    BMC_PRINTLN("timed event",(isLooped(n)?"LOOP":"SINGLE"),n,"triggered",timeoutMs);
  }
  bool isReady(uint8_t n){
    bool resp = false;
    if(available() > 0 && n < BMC_MAX_TIMED_EVENTS){
      resp = timers[n].complete();
      if(resp && isLooped(n)){
        timers[n].start(getTimeout(n));
      }
      if(resp){
        BMC_PRINTLN("timed event",n,"is complete",isLooped(n)?"LOOP":"");
      }
    }
    return resp;
  }
  void setMode(uint8_t n,  uint8_t mode){
    if(n < BMC_MAX_TIMED_EVENTS){
      timerFlags[n].write(BMC_TIMED_EVENTS_TIMER_FLAG_MODE, mode==1);
    }
  }
  void setTriggered(uint8_t n, bool state){
    if(n < BMC_MAX_TIMED_EVENTS){
      timerFlags[n].write(BMC_TIMED_EVENTS_TIMER_FLAG_TRIGGERED, state);
    }
  }
  bool isLooped(uint8_t n){
    if(n < BMC_MAX_TIMED_EVENTS){
      return timerFlags[n].read(BMC_TIMED_EVENTS_TIMER_FLAG_MODE);
    }
    return false;
  }
  bmcEvent_t getEvent(uint8_t n){
    return global.timedEvents[n].events[0];
  }
  uint16_t getTimeout(uint8_t n){
    return (global.timedEvents[n].settings[0]+1)*10;
  }
  uint8_t getReTrigger(uint8_t n){
    return global.timedEvents[n].settings[1] & 0x03;
  }
  uint8_t getMode(uint8_t n){
    return (global.timedEvents[n].settings[1]>>2) & 0x03;
  }
  uint8_t available(){
    return totalReadyTimedEvents;
  }

private:
  // reference to midi object from BMC
  BMCGlobals& globals;
  bmcStoreGlobal& global;
  BMCFlags <uint8_t> flags;
  uint8_t totalReadyTimedEvents = 0;
  BMCTimerLong timers[BMC_MAX_TIMED_EVENTS];
  BMCFlags <uint8_t> timerFlags[BMC_MAX_TIMED_EVENTS];

};

#endif
#endif
