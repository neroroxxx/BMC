/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_BPM_CALCULATOR_H
#define BMC_BPM_CALCULATOR_H

#include "utility/BMC-Def.h"

#define BMC_BPM_AVERAGE 2
#define BMC_MICROS_ON_SECOND 0x3938700
#define BMC_MILLIS_ON_SECOND 0xEA60

#define BMC_BPM_CALC_EIGHT_NOTE 0

class BMCBpmCalculator {
public:
  BMCBpmCalculator(){
    reset();
  }
  void begin(){
    reset();
  }
  void update(){
    mms = micros();
    if(timer.complete()){
      reset();
    }
  }
  bool isEigthNote(){
    return flags.toggleIfTrue(BMC_BPM_CALC_EIGHT_NOTE);;

  }
  void setBpm(uint16_t tempo){
    if(isValidBpm(tempo)){
      bpm = tempo;
    }
  }
  uint16_t getBpm(){
    return bpm;
  }
  // used by Incoming MIDI Clock
  void startReceived(){
    ticks = 0;
  }
  void continueReceived(){
    startReceived();
  }
  bool tickReceived(){
    bool isQuarterNote = false;

    if(ticks==0){
      ticksTime = micros();
    }
    flags.write(BMC_BPM_CALC_EIGHT_NOTE, (ticks==12));
    if(ticks >= 24){
      flags.on(BMC_BPM_CALC_EIGHT_NOTE);
      // calculate bpm based on micros
      setBpm(round(60000 / ((micros()-ticksTime) / 1000.0)));

      // set a new ticks time
      ticksTime = micros();
      // set ticks to 0 since below we'll increase it anyways
      ticks = 0;
      isQuarterNote = true;
    }
    ticks++;
    return isQuarterNote;
  }
  // used by Tap Tempo
  bool tap(){
    timer.start(2000);
    if(prevBeat==0){
      prevBeat = mms;
    }
    bpmAvg[bpmAvgSize] = round(((float) BMC_MICROS_ON_SECOND / (mms - prevBeat)));
    bpmAvgSize++;
    prevBeat = mms;
    if(bpmAvgSize>=BMC_BPM_AVERAGE){
      float avgBpm = 0;
      for(uint8_t i=0;i<BMC_BPM_AVERAGE;i++){
        avgBpm += (float) bpmAvg[i];
      }
      uint16_t newBpm = (uint16_t) round((avgBpm/BMC_BPM_AVERAGE));
      reset();
      if(bpm!=newBpm && isValidBpm(newBpm)){
        setBpm(newBpm);
        return true;
      }
      return false;
    }
    return false;
  }
  // static methods
  static unsigned long bpmToMillisPPQN(uint16_t tempo){
    return bpmToMillis(tempo) / 24;
  }
  static unsigned long bpmToMicrosPPQN(uint16_t tempo){
    return bpmToMicros(tempo) / 24;
  }
  static unsigned long bpmToMillis(uint16_t tempo){
    return (BMC_MILLIS_ON_SECOND / tempo);
  }
  static unsigned long bpmToMicros(uint16_t tempo){
    return (BMC_MICROS_ON_SECOND / tempo);
  }
  static bool isValidBpm(uint16_t tempo){
    return (tempo>=30 && tempo<=300);
  }

private:
  uint16_t bpm = 0;
  BMCFlags <uint8_t> flags;
  // used for Tap Tempo
  float bpmAvg[BMC_BPM_AVERAGE];
  uint8_t bpmAvgSize = 0;
  unsigned long prevBeat = 0;
  unsigned long mms = 0;
  BMCTimer timer;

  // user for incoming MIDI Clock messages
  uint8_t ticks = 0;
  unsigned long ticksTime = 0;

  void reset(){
    ticks = 0;
    bpmAvgSize = 0;
    memset(bpmAvg,0,BMC_BPM_AVERAGE);
    timer.stop();
    flags.reset();
  }
};
#endif
