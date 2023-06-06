/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_TEMPO_TO_TAP_H
#define BMC_TEMPO_TO_TAP_H

#if BMC_MAX_TEMPO_TO_TAP > 0

#include "utility/BMC-Def.h"

#define BMC_FLAG_TEMPO_TO_TAP_AVAILABLE 0
#define BMC_FLAG_TEMPO_TO_TAP_SEND_NOW 1

class BMCTempoToTap {
public:
  // constructor, pass the midi and store.global data objects from BMC.h
  BMCTempoToTap(BMCMidi& t_midi):
                midi(t_midi),
                globals(midi.globals),
                global(globals.store.global)
  {
    reset();
  }
  void buildListeners(){
    activeList.zeroOut();
    flags.reset();
    for(uint8_t i = 0 ; i < BMC_MAX_TEMPO_TO_TAP ; i++){
      bmcStoreDevice <1, 1>& device = global.tempoToTap[i];
      if(isValidEvent(device.events[0])){
        flags.on(BMC_FLAG_TEMPO_TO_TAP_AVAILABLE);
        activeList.setBit(i, true);
        totalActiveCount = (i + 1);
      }
    }
  }
  bool isAllowed(){
    return flags.read(BMC_FLAG_TEMPO_TO_TAP_AVAILABLE) && flags.toggleIfTrue(BMC_FLAG_TEMPO_TO_TAP_SEND_NOW);
  }
  bool isReady(uint8_t n){
    if((n >= BMC_MAX_TEMPO_TO_TAP)){
      return false;
    }
    return activeList.getBit(n);
  }
  uint8_t available(){
    return totalActiveCount;
  }
  // check if the next tap should be sent
  // this must run within every loop so the timer can send each tap
  void update(){
    if(timer.complete()){
      if(count>=3){
        // all done
        reset();
        return;
      }
      sendTaps();
      count++;
    }
  }
  // start sending the taps based on the specified Tempo
  void updateBpm(uint16_t tempo){
    if(lastBpm == tempo){
      return;
    }
    if(BMCBpmCalculator::isValidBpm(tempo)){
      if(bpm == tempo){
        if(timer.active()){
          return;
        }
      } else {
        timer.stop();
        reset();
      }
      bpm = tempo;
      sendTaps();
    }
  }
private:
  // reference to midi object from BMC.h
  BMCMidi& midi;

  BMCGlobals& globals;
  // reference to store.global from BMC.h
  bmcStoreGlobal& global;
  // timer used to send each midi message
  BMCTimer timer;
  BMCFlags <uint8_t> flags;
  BMCBitStates <BMC_MAX_TEMPO_TO_TAP> activeList;
  // number of taps that have been sent
  uint8_t count = 0;
  uint8_t totalActiveCount = 0;
  // the bpm for the taps interval
  uint16_t bpm = 0;
  // the last bpm sent out
  uint16_t lastBpm = 0;
  // set the current number of taps that were sent to 0
  void reset(){
    count = 0;
    flags.off(BMC_FLAG_TEMPO_TO_TAP_SEND_NOW);
  }
  // send the MIDI Message out for each trigger
  void sendTaps(){
    lastBpm = bpm;
    if(!flags.read(BMC_FLAG_TEMPO_TO_TAP_AVAILABLE)){
      flags.off(BMC_FLAG_TEMPO_TO_TAP_SEND_NOW);
      return;
    }
    flags.on(BMC_FLAG_TEMPO_TO_TAP_SEND_NOW);
    /*
    for(uint8_t i=0;i<BMC_MAX_TEMPO_TO_TAP;i++){
      bmcStoreDevice <1, 1>& device = global.tempoToTap[i];
      if(isValidEvent(device.events[0])){
        //midi.send(global.tempoToTap[i].event);
        //BMC_PRINTLN("Sending Tap bpm:", bpm, "event:", global.tempoToTap[i].event);
      }
    }
    */
    timer.start(BMCBpmCalculator::bpmToMillis(bpm));
  }
  bool isValidEvent(bmcEvent_t event){
    if(event == BMC_NONE){
      return false;
    }
    // bmcStoreEvent data = globals.getDeviceEventType(event);
    bmcStoreEvent data = BMCTools::getDeviceEventType(midi.globals.store, event);
    
    if(data.ports == BMC_NONE){
      return false;
    }
    switch(data.type){
      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
        return true;
    }
    return false;
  }
};

#endif
#endif
