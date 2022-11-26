/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_TIMED_EVENTS > 0
  void BMC::readTimedEvent(){
    if(timedEvents.available()==0){
      return;
    }
    for(uint8_t index = 0, n=timedEvents.available(); index < n; index++){
      if(timedEvents.isReady(index)){
        processTimedEvent(index);
      }
    }
  }
  void BMC::processTimedEvent(uint8_t n){
    // ready to trigger
    if(n>=BMC_MAX_TIMED_EVENTS){
      return;
    }
    uint32_t event = store.global.timedEvents[n].event;
    switch(BMC_GET_BYTE(0, event)){
      case BMC_NONE:
        return;
      case BMC_TIMED_EVENT_TYPE_RELAY_NL_CONTROL:
#if BMC_MAX_NL_RELAYS>0
        if(BMC_GET_BYTE(1, event) < BMC_MAX_NL_RELAYS){
          relaysNL[BMC_GET_BYTE(1, event)].command(BMC_GET_BYTE(2, event));
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_RELAY_L_CONTROL:
#if BMC_MAX_L_RELAYS>0
        if(BMC_GET_BYTE(1, event) < BMC_MAX_L_RELAYS){
          relaysL[BMC_GET_BYTE(1, event)].command(BMC_GET_BYTE(2, event));
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_BUTTON_EVENT:
#if BMC_MAX_BUTTONS > 0
        {
          /*
          uint8_t btnN = BMC_GET_BYTE(1, event);
          uint8_t btnEventN = BMC_GET_BYTE(2, event);
          bmcStoreButtonEvent &data = store.pages[page].buttons[btnN].events[btnEventN];
          uint8_t type = BMC_GET_BYTE(0,data.event);
          if(type!=BMC_NONE){
            handleButtonEvent(type, data);
          }
          */
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_GLOBAL_BUTTON_EVENT:
#if BMC_MAX_GLOBAL_BUTTONS > 0
        {
          /*
          uint8_t btnN = BMC_GET_BYTE(1, event);
          uint8_t btnEventN = BMC_GET_BYTE(2, event);
          bmcStoreButtonEvent &data = globalData.buttons[btnN].events[btnEventN];
          uint8_t type = BMC_GET_BYTE(0,data.event);
          if(type!=BMC_NONE){
            handleButtonEvent(type, data);
          }
          */
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_ENCODER:
#if BMC_MAX_ENCODERS > 0
        {
          /*
          uint8_t enc   = BMC_GET_BYTE(1, event);
          uint8_t inc   = BMC_GET_BYTE(2, event);
          uint8_t type  = BMC_GET_BYTE(0, store.pages[page].encoders[enc].event);
          if(type!=BMC_NONE){
            handleEncoder(store.pages[page].encoders[enc], inc);
          }
          */
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_GLOBAL_ENCODER:
#if BMC_MAX_GLOBAL_ENCODERS > 0
        {
          /*
          uint8_t enc   = BMC_GET_BYTE(1, event);
          uint8_t inc   = BMC_GET_BYTE(2, event);
          uint8_t type  = BMC_GET_BYTE(0, globalData.encoders[enc].event);
          if(type!=BMC_NONE){
            handleEncoder(globalData.encoders[enc], inc);
          }
          */
        }
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_PAGE:
#if BMC_MAX_GLOBAL_ENCODERS > 1
        setPage(BMC_GET_BYTE(1, event));
#endif
        break;
      case BMC_TIMED_EVENT_TYPE_MASTER_CLOCK:
        midiClock.setBpm((event >> 8) & 0x1FF);
        break;
      case BMC_TIMED_EVENT_TYPE_CUSTOM:
        callback.timedEventCustom(n,
                              BMC_GET_BYTE(1,event),
                              BMC_GET_BYTE(2,event),
                              BMC_GET_BYTE(3,event));
        break;
    }
  }
#endif
