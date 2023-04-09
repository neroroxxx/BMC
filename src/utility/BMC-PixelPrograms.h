/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#ifndef BMC_PIXEL_PROGRAMS_H
#define BMC_PIXEL_PROGRAMS_H
#include "utility/BMC-Def.h"
#if BMC_TOTAL_PIXELS > 0 && BMC_MAX_PIXEL_PROGRAMS > 0

#define BMC_PIXEL_PROGRAMS_FLAG_ACTIVE 0
#define BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT 1

class BMCPixelPrograms {
private:
  BMCMidi& midi;
  BMCFlags <uint8_t> flags;
  uint8_t program = 0;
  uint8_t currentItem = 0;
  uint8_t eigthNotes = 0;
public:
  BMCPixelPrograms(BMCMidi& t_midi):midi(t_midi){

  }
  void reassign(){

  }
  void update(bool t_eigth, bool t_active){
    if(t_eigth){
      eigthNotes++;
      if(eigthNotes>16){
        eigthNotes = 1;
      }
    }
    uint8_t duration = ((midi.globals.store.global.pixelPrograms[program].events[currentItem]>>4)&0x0F)+1;
    flags.write(BMC_PIXEL_PROGRAMS_FLAG_ACTIVE, t_active);
    if(eigthNotes == duration){
      currentItem++;
      if(currentItem >= midi.globals.store.global.pixelPrograms[program].settings[0]){
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
    if(isBlackout() || !isActive()){
      return 0;
    }
    return (midi.globals.store.global.pixelPrograms[program].events[currentItem] & 0x0F);
  }
  uint8_t getProgram(){
    return program;
  }
  void setProgram(uint8_t t_value){
    if(t_value < BMC_MAX_PIXEL_PROGRAMS){
      program = t_value;
      currentItem = 0;
      eigthNotes = 0;
    }
  }
  bool isBlackout(){
    return flags.read(BMC_PIXEL_PROGRAMS_FLAG_BLACKOUT);
  }
  bool isActive(){
    return flags.read(BMC_PIXEL_PROGRAMS_FLAG_ACTIVE);
  }
  void scroll(bool up, bool endless){
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PIXEL_PROGRAMS-1);
    setProgram(scroller.scroll(1, up, endless, program, 0, BMC_MAX_PIXEL_PROGRAMS-1));
  }
};

#endif
#endif
