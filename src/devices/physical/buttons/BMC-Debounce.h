/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DEBOUNCE_H
#define BMC_DEBOUNCE_H

#include "utility/BMC-Def.h"

#define BMC_DEBOUNCE_CLOSED LOW
#define BMC_DEBOUNCE_OPEN HIGH

// Bit flags used internally
#define BMC_DEBOUNCE_FLAG_ACTIVE          0
#define BMC_DEBOUNCE_FLAG_STATE           1
#define BMC_DEBOUNCE_FLAG_CURRENT_READING 2
#define BMC_DEBOUNCE_FLAG_STATE_CHANGE    3

class BMCDebounce {
private:
  uint8_t mode = BMC_DEBOUNCE_MODE_DEFAULT;
  uint8_t history = 0;
  uint8_t historyCount = 0;
  uint16_t interval = 50;
  unsigned long lastMillis = 0;
  BMCFlags <uint16_t> flags;

public:
  BMCDebounce(){}

  // Update the debounce logic with new input state
  bool update(bool t_signaleReading){
    flags.write(BMC_DEBOUNCE_FLAG_CURRENT_READING, t_signaleReading);
    return debouncer();
  }

  void setInterval(uint16_t t_interval){
    interval = t_interval;
  }

  void setMode(uint16_t t_mode){
    mode = t_mode;
  }

  bool getState(){
    return flags.read(BMC_DEBOUNCE_FLAG_STATE);
  }

  // Main debounce engine
  bool debouncer(){
    bool currentReading = flags.read(BMC_DEBOUNCE_FLAG_CURRENT_READING);
    uint32_t currentMillis = millis();

    if(mode == BMC_DEBOUNCE_MODE_DEFAULT){
      // Basic debounce: check every `interval` ms
      if((currentMillis - lastMillis) >= interval){
        lastMillis = currentMillis;
        if(flags.read(BMC_DEBOUNCE_FLAG_STATE) != currentReading){
          flags.write(BMC_DEBOUNCE_FLAG_STATE, currentReading);
          flags.on(BMC_DEBOUNCE_FLAG_ACTIVE);
          return true;
        }
      }

    } else if(mode == BMC_DEBOUNCE_MODE_RESPONSIVE){
      // Fast reaction, but block new changes for `interval` after a trigger
      if(flags.read(BMC_DEBOUNCE_FLAG_ACTIVE)){
        if((currentMillis - lastMillis) >= interval){
          flags.off(BMC_DEBOUNCE_FLAG_ACTIVE);
          lastMillis = 0;
        }
      } else if(flags.read(BMC_DEBOUNCE_FLAG_STATE) != currentReading){
        flags.write(BMC_DEBOUNCE_FLAG_STATE, currentReading);
        flags.on(BMC_DEBOUNCE_FLAG_ACTIVE);
        lastMillis = currentMillis;
        return true;
      }

    } else if(mode == BMC_DEBOUNCE_MODE_FILTER){
      // Strict: only accept change if we get 8 stable readings
      history = (history << 1) | currentReading;

      if(++historyCount >= 8){
        historyCount = 0;
        if(history == 0xFF || history == 0x00){
          flags.write(BMC_DEBOUNCE_FLAG_STATE, currentReading);
          flags.on(BMC_DEBOUNCE_FLAG_ACTIVE);
          return true;
        }
      }

    } else if(mode == BMC_DEBOUNCE_MODE_SMART){
      // Hybrid: accept change only after 3 matching bits, then enter cooldown
      if(flags.read(BMC_DEBOUNCE_FLAG_ACTIVE)){
        // In cooldown: block new changes until interval expires
        if((currentMillis - lastMillis) >= interval){
          flags.off(BMC_DEBOUNCE_FLAG_ACTIVE);
          lastMillis = 0;
        }
      } else {
        history = (history << 1) | currentReading;

        // Require 3 consistent readings for change (e.g., 0b111 or 0b000)
        if((history & 0x07) == 0x07 || (history & 0x07) == 0x00){
          if(flags.read(BMC_DEBOUNCE_FLAG_STATE) != currentReading){
            flags.write(BMC_DEBOUNCE_FLAG_STATE, currentReading);
            flags.on(BMC_DEBOUNCE_FLAG_ACTIVE);
            lastMillis = currentMillis;
            return true;
          }
        }
      }
    }

    return false;
  }

  // Clear internal state and history buffer
  void reset(){
    history = 0;
    historyCount = 0;
  }
};

#endif