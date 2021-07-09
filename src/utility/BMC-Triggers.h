/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_TRIGGERS_H
#define BMC_TRIGGERS_H

#if BMC_MAX_TRIGGERS > 0

#include "utility/BMC-Def.h"

#define BMC_TRIGGERS_FLAG_AVAILABLE 0

class BMCTriggers {
public:
  BMCTriggers(BMCMidi& t_midi, bmcStoreGlobal& t_global):
    midi(t_midi),
    incoming(midi.message),
    global(t_global)
  {

  }
  void buildListeners(){

    flags.off(BMC_TRIGGERS_FLAG_AVAILABLE);
    totalReadableTriggers = 0;
    for(uint8_t i=0;i<BMC_MAX_TRIGGERS;i++){
      bmcStoreGlobalTriggers& trigger = global.triggers[i];
      if(active(trigger.source) != BMC_NONE){
        flags.on(BMC_TRIGGERS_FLAG_AVAILABLE);
        totalReadableTriggers = i+1;
      }
    }
    BMC_PRINTLN("BMCTriggers::buildListeners() ",totalReadableTriggers);
  }
  uint8_t available(){
    return totalReadableTriggers;
  }
  bool isValidTrigger(uint8_t index){
    if(index>=BMC_MAX_TRIGGERS){
      return false;
    }
    bmcStoreGlobalTriggers& trigger = global.triggers[index];
    return (active(trigger.source) && match(trigger.source));
  }
  uint32_t getEvent(uint8_t index){
    if(index>=BMC_MAX_TRIGGERS){
      return 0;
    }
    return global.triggers[index].event;
  }
  uint32_t getSource(uint8_t index){
    if(index>=BMC_MAX_TRIGGERS){
      return 0;
    }
    return global.triggers[index].source;
  }
  bool isAllowed(){
    if(totalReadableTriggers>0 && incoming.isVoiceStatus()){
      switch(incoming.getStatus()){
        case BMC_MIDI_NOTE_OFF:
        case BMC_MIDI_NOTE_ON:
        case BMC_MIDI_CONTROL_CHANGE:
        case BMC_MIDI_PROGRAM_CHANGE:
          return true;
      }
    }
    return false;
  }
private:
  // reference to midi object from BMC
  BMCMidi& midi;
  BMCMidiMessage& incoming;
  bmcStoreGlobal& global;
  BMCFlags <uint8_t> flags;
  uint8_t totalReadableTriggers = 0;

  bool active(uint32_t source){
    return BMC_GET_MIDI_STATUS(BMC_GET_BYTE(0,source)) != BMC_NONE;
  }
  bool match(uint32_t trigger){
    if(incoming.getStatus()==BMC_NONE){
      return false;
    }
    uint8_t data2 = (trigger>>15) & 0x7F;
    uint8_t data2Operator = (trigger>>22) & 0x03;
    if(matchEvent(incoming.getEvent(),trigger)){
      if(incoming.isProgramChange()){
        return true;
      }
      switch(data2Operator){
        case BMC_IGNORE:
          //Any (Ignore Data2 Value)
          return true;
        case BMC_EQUAL_TO:
          // Value of Data2 must be equal to the event's Data2 value
          return (incoming.getData2() == data2);
        case BMC_MORE_OR_EQUAL_TO:
          // Value of Data2 must be equal to or more than the event's Data2 value
          return (incoming.getData2() >= data2);
        case BMC_LESS_OR_EQUAL_TO:
          // Value of Data2 must be equal to or less than the event's Data2 value
          return (incoming.getData2() <= data2);
      }
    }
    return false;
  }
  bool matchEvent(uint32_t source, uint32_t target){
    return (matchStatusAndData1(source,target) && matchPort(source,target));
  }
  bool matchStatusAndData1(uint32_t source, uint32_t target){
    return ((source & 0x7FFF) == (target & 0x7FFF));
  }
  bool matchPort(uint32_t source, uint32_t target){
    return BMCTools::matchPort(BMC_GET_BYTE(3,source), BMC_GET_BYTE(3,target));
  }
};

#endif
#endif
