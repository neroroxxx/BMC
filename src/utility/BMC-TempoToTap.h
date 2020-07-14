/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_TEMPO_TO_TAP_H
#define BMC_TEMPO_TO_TAP_H

#if BMC_MAX_TEMPO_TO_TAP > 0

#include "utility/BMC-Def.h"

class BMCTempoToTap {
public:
  // constructor, pass the midi and store.global data objects from BMC.h
  BMCTempoToTap(BMCMidi& t_midi,bmcStoreGlobal& t_global):
                midi(t_midi),
                global(t_global)
  {
    reset();
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
  void send(uint16_t tempo){
    if(lastBpm==tempo){
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
  // reference to store.global from BMC.h
  bmcStoreGlobal& global;
  // timer used to send each midi message
  BMCTimer timer;
  // number of taps that have been sent
  uint8_t count = 0;
  // the bpm for the taps interval
  uint16_t bpm = 0;
  // the last bpm sent out
  uint16_t lastBpm = 0;
  // set the current number of taps that were sent to 0
  void reset(){
    count = 0;
  }
  // send the MIDI Message out for each trigger
  void sendTaps(){
    lastBpm = bpm;
    for(uint8_t i=0;i<BMC_MAX_TEMPO_TO_TAP;i++){
      if(isValid(global.tempoToTap[i].event)){
      //if(BMC_GET_BYTE(0,global.tempoToTap[i].event)>0 && BMC_GET_BYTE(3,global.tempoToTap[i].event)>0){
        midi.send(global.tempoToTap[i].event);
        BMC_PRINTLN("Sending Tap bpm:", bpm, "event:", global.tempoToTap[i].event);
      }
    }
    timer.start(BMCBpmCalculator::bpmToMillis(bpm));
  }
  bool isValid(uint32_t event){
    return hasEvent(event) && hasPorts(event);
  }
  bool hasEvent(uint32_t event){
    return BMC_GET_BYTE(0,event)>0;
  }
  bool hasPorts(uint32_t event){
    return BMC_GET_BYTE(3,event)>0;
  }
};

#endif
#endif
