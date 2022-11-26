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
  BMCTriggers(BMCMidi& t_midi, BMCGlobals& t_globals, bmcStoreGlobal& t_global):
    midi(t_midi),
    incoming(midi.message),
    globals(t_globals),
    global(t_global)
  {

  }
  void buildListeners(){
    flags.off(BMC_TRIGGERS_FLAG_AVAILABLE);
    totalReadableTriggers = 0;
    activeList.zeroOut();
    for(uint8_t i = 0 ; i < BMC_MAX_TRIGGERS ; i++){
      bmcStoreDevice <1, 2>& device = global.triggers[i];
      if(active(device.events[0]) && device.events[1] != 0){
        flags.on(BMC_TRIGGERS_FLAG_AVAILABLE);
        activeList.setBit(i, true);
        totalReadableTriggers = (i+1);
      }
    }
    BMC_PRINTLN("BMCTriggers::buildListeners() ",totalReadableTriggers);
  }
  uint8_t available(){
    return totalReadableTriggers;
  }
  bool isValidTrigger(uint8_t index){
    if(incoming.getStatus()==BMC_NONE || index>=totalReadableTriggers || !activeList.getBit(index)){
      return false;
    }
    //bmcStoreGlobalTriggers& trigger = global.triggers[index];
    bmcStoreDevice <1, 2>& device = global.triggers[index];
    return active(device.events[0]) && match(device.events[0], device.settings[0]);
  }
  uint32_t getEvent(uint8_t index){
    return 0;
  }
  uint32_t getSource(uint8_t index){
    return 0;
  }
  bool isAllowed(){
    if(totalReadableTriggers > 0 && incoming.isVoiceStatus()){
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
  BMCGlobals& globals;
  bmcStoreGlobal& global;
  BMCFlags <uint8_t> flags;
  BMCBitStates <BMC_MAX_TRIGGERS> activeList;
  uint8_t totalReadableTriggers = 0;

  bool active(bmcEvent_t type){
    bmcStoreEvent data = globals.getDeviceEventType(type);
    switch(data.type){
      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
        return true;
    }
    return false;
  }
  bool match(bmcEvent_t trigger, uint8_t settings){
    bmcStoreEvent data = globals.getDeviceEventType(trigger);
    if(incoming.getStatus()==BMC_NONE){
      return false;
    }
    uint8_t channel = BMC_GET_BYTE(0, data.event) & 0x0F;
    uint8_t data1 = BMC_GET_BYTE(1, data.event) & 0x7F;
    uint8_t data2 = BMC_GET_BYTE(2, data.event) & 0x7F;
    uint8_t data2Operator = (settings) & 0x03;
    uint8_t ignorePort = bitRead(settings, 2);
    uint32_t target = 0;
    switch(data.type){
      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
        target = (BMC_MIDI_PROGRAM_CHANGE | channel) | (data1<<8) | (data.ports<<24);
        break;
      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
        target = (BMC_MIDI_CONTROL_CHANGE | channel) | (data1<<8) | (data2<<16) | (data.ports<<24);
        break;
      case BMC_EVENT_TYPE_MIDI_NOTE_ON:
        target = (BMC_MIDI_NOTE_ON | channel) | (data1<<8) | (data2<<16) | (data.ports<<24);
        break;
      case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
        target = (BMC_MIDI_NOTE_OFF | channel) | (data1<<8) | (data2<<16) | (data.ports<<24);
        break;
    }
    if(matchEvent(incoming.getEvent(), target, ignorePort)){
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
  bool matchEvent(uint32_t source, uint32_t target, bool ignorePort){
    bool statusMatch = matchStatusAndData1(source, target);
    if(ignorePort){
      return statusMatch;
    }
    return statusMatch && matchPort(source, target);
  }
  bool matchStatusAndData1(uint32_t source, uint32_t target){
    return (source & 0x7FFF) == (target & 0x7FFF);
  }
  bool matchPort(uint32_t source, uint32_t target){
    return BMCTools::matchPort(BMC_GET_BYTE(3,source), BMC_GET_BYTE(3,target));
  }
};

#endif
#endif
