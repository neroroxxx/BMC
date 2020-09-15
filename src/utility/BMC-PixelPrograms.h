/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#ifndef BMC_PIXEL_PROGRAMS_H
#define BMC_PIXEL_PROGRAMS_H
#include "utility/BMC-Def.h"
#if BMC_MAX_PIXELS > 0 && BMC_MAX_PIXEL_PROGRAMS > 0

#define BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT 0

class BMCPixelPrograms {
private:
  BMCFlags <uint8_t> flags;
  uint8_t program = 0;
  uint8_t currentItem = 0;
  uint8_t eigthNotes = 0;
  bmcStoreGlobal& global;
public:
  BMCPixelPrograms(bmcStoreGlobal& t_global):global(t_global){

  }
  void reassign(){

  }
  void update(bool isEigthNote){
    if(isEigthNote){
      eigthNotes++;
      if(eigthNotes>8){
        eigthNotes = 1;
      }
    }
    uint8_t duration = ((global.pixelPrograms[program].events[currentItem]>>4)&0x0F)+1;

    if(eigthNotes == duration){
      currentItem++;
      if(currentItem >= global.pixelPrograms[program].length){
        currentItem = 0;
      }
      eigthNotes = 0;
    }
  }
  void setBlackout(bool state){
    if(state != flags.read(BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT)){
      flags.write(BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT, state);
      currentItem = 0;
      eigthNotes = 0;
    }
  }
  void toggleBlackout(){
    setBlackout(!flags.read(BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT));
  }
  uint8_t getColor(){
    if(flags.read(BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT)){
      return 0;
    }
    return global.pixelPrograms[program].events[currentItem] & 0x0F;
  }
  uint8_t getProgram(){
    return program;
  }
  void setProgram(uint8_t t_value){
    if(t_value<BMC_MAX_PIXEL_PROGRAMS){
      program = t_value;
      currentItem = 0;
    }
  }
  void scrollUp(bool endless, uint8_t min, uint8_t max){
    scroll(true, endless, min, max);
  }
  void scrollDown(bool endless, uint8_t min, uint8_t max){
    scroll(false, endless, min, max);
  }
  void scroll(bool up, bool endless, uint8_t min, uint8_t max){
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PIXEL_PROGRAMS-1);
    setProgram(scroller.scroll(1, up, endless, program, min, max));
  }
};

#endif
#endif
