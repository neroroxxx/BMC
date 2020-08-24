/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_TYPER_H
#define BMC_TYPER_H

#include <Arduino.h>
#include "utility/BMC-Callbacks.h"

#define BMC_TYPER_MODE 1
#if !defined(BMC_TYPER_MODE)
  #define BMC_TYPER_MODE 0
#endif

class BMCTyper {
private:
  BMCFlags <uint8_t> flags;
  uint8_t vtCount = 0;
  uint16_t vtValue = 0;
  uint16_t output = 0;
  BMCCallbacks& callback;
  void buildOutput(){
#if BMC_TYPER_MODE == 0
    output = (((vtValue>>0)&0x0F)*100) + (((vtValue>>4)&0x0F)*10) + ((vtValue>>1)&0x0F);
#else
    output = (((vtValue>>8)&0x0F)*100) + (((vtValue>>4)&0x0F)*10) + ((vtValue>>0)&0x0F);
#endif
  }
public:
  BMCTyper(BMCCallbacks& cb):callback(cb){}
  uint16_t getOutput(){
    return output;
  }
  uint8_t cmd(uint8_t value, uint8_t autoTrigger=0){
    if(value >= 10){
      // 10 is clear
      // 11 is custom callback
      // 12 is page
      // 13 is preset
      // 14 is fas preset
      // 15 is fas scene
      vtValue = 0;
      vtCount = 0;
      if(value==10){
        output = 0;
      }

      if(value==11){
        if(callback.typerCustomCommand){
          callback.typerCustomCommand(output);
          return value;
        }
      }
      if(callback.typerCommand){
        callback.typerCommand(output);
      }
      // trigger display callback
      return value;
    }
    if(vtCount >= 3){
      vtCount = 0;
      vtValue = 0;
    }

#if BMC_TYPER_MODE == 0
    vtValue |= (value << (vtCount*4));
#else
    // shift the value to the left
    vtValue = (vtValue << 4) | (value & 0x0F);
#endif

    buildOutput();
    vtCount++;

    if(vtCount>=3 && autoTrigger>0){
      return cmd(autoTrigger+10, 0);
    }
    // trigger display callback
    if(callback.typerCommand){
      callback.typerCommand(output);
    }
    return 0;
  }
};
#endif
