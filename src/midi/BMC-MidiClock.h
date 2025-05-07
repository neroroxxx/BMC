/*
  See https://www.roxxxtar.com/bmc for more details
  Copyright (c) 2015 - 2025 Roxxxtar.com
  See BMC Documentation for License

  Handles the Master and Slave Clock
  It uses the BpmCalculator for tap tempo and to calculate PPQ Clock ticks
*/

#ifndef BMC_MIDI_CLOCK_H
#define BMC_MIDI_CLOCK_H

#include "utility/BMC-Def.h"
#include "midi/BMC-Midi.h"
#include "midi/BMC-MidiClockTimer.h"

#ifdef BMC_USE_CLICK_TRACK
  #include "utility/BMC-ClickTrack.h"
#endif

#define BMC_MIDI_CLOCK_FLAG_MASTER 0
#define BMC_MIDI_CLOCK_FLAG_BEAT 1
#define BMC_MIDI_CLOCK_FLAG_BPM_CHANGED 2
#define BMC_MIDI_CLOCK_FLAG_ACTIVE 3
#define BMC_MIDI_CLOCK_FLAG_EIGTH 4

#define BMC_CLOCK_BPM_AVG 4
#define BMC_MICROS_SECOND 0x3938700

class BMCMidiClock {
public:
  BMCMidiClock(BMCMidi& t_midi):midi(t_midi), globals(t_midi.globals), bpm(t_midi.globals.bpm){
    
  }
  void begin(){
    BMC_PRINTLN(" - BMCMidiClock::begin");
    flags.reset();
    bpmCalc.begin();
    masterClockTimer.begin();
    #ifdef BMC_USE_CLICK_TRACK
      clickTrack.begin();
    #endif
  }
  void update(){
    masterClockTimer.update();
  }

  void setInputPorts(uint8_t t_value){

  }
  void setOutputPorts(uint8_t t_value){

  }

  bool read(bool incoming = false, bool isStartOrContinue = false){
    // update the bpm calculator first
    bpmCalc.update();
    // if we are slave and a start or continue has been received
    // we reset the number of ticks to 0, this is so leds set to clock sync
    // can be in better sync with the master that's sending the clock
    if(!isMaster() && isStartOrContinue){
      ticks = 0;
      // this will reset the number of PPQNs in the BPM Calculator
      bpmCalc.startReceived();
    }

    // If BMC is set to Master Clock
    if(isMaster()){
      return handleMaster();
    } 
    
    if(incoming && midi.isIncomingClockPort()){
      timeout.start(2000);
      
      flags.on(BMC_MIDI_CLOCK_FLAG_ACTIVE);

      if(timeout.complete()){
        flags.off(BMC_MIDI_CLOCK_FLAG_ACTIVE);
      }
      // the ticks variable is only used by the master clock
      ticks = 0;

      #if defined(BMC_DEBUG)
        if(globals.getMidiClockDebug()){
          BMC_PRINT(".");
        }
      #endif

      // the bmp calculator that a PPQN was received
      // if it retunrs tru then 24 ticks have been received
      if(bpmCalc.tickReceived()){
        // check if  the new bpm is the same as the current bpm
        if(bpm != bpmCalc.getBpm()){
          // if the bpm has changed we set up a timer to wait 100ms
          // callbacks are triggered, this is so if the tempo is being changed
          // in real time we don't send a bunch of callbacks and for clock drift
          // this is also used for TempoToTap
          // this time delay doesn't affect the speed of the led as it blinks
          bpmSetTimer.start(100);
        }
        // set the new bpm
        bpm = bpmCalc.getBpm();
        #ifdef BMC_USE_CLICK_TRACK
          // if we're using the click track play the sound
          clickTrack.play();
        #endif
        // set a flat that a beat has accured (24 PPQN)
        flags.on(BMC_MIDI_CLOCK_FLAG_BEAT);

        #if defined(BMC_DEBUG)
          if(globals.getMidiClockDebug()){
            BMC_PRINTLN(" Beat");
          }
        #endif

        // check if the timer is active and has reached the 1000ms
        // also check if the BPM has changed, we'll store the previous bpm
        // in tmpBpm
        if(bpmSetTimer.complete() && tmpBpm != bpm){
          tmpBpm = bpm;
          // 100ms have passed since the last time the tempo changed
          // now callbacks can be triggered
          BMC_PRINTLN("NEW BPM", bpm, "Received");
          flags.on(BMC_MIDI_CLOCK_FLAG_BPM_CHANGED);
        }
        // return true as 24 PPQN have been received
        return true;
      }
    }
    return false;
  }

  bool handleMaster(){
    if(!isMaster()) return false;

    flags.on(BMC_MIDI_CLOCK_FLAG_ACTIVE);
    // check if the timer is active and complete, in which case we assign
    // a new BPM, this timer is started when a new BPM is set via the API
    
    if(bpmSetTimer.complete()){
      assignBpm(tmpBpm);
    }

    // check if the number of microseconds (based on the master bpm) has passed
    if(masterClockTimer.ready()){

      // send the Clock Message to the assigned port(s) 24 per quarter note
      midi.sendRealTime(midi.getClockPort(), BMC_MIDI_RT_CLOCK);

      #if defined(BMC_DEBUG)
        if(globals.getMidiClockDebug()){
          BMC_PRINT(".");
        }
      #endif
      
      // increase the number of ticks
      ticks++;
      flags.write(BMC_MIDI_CLOCK_FLAG_EIGTH, (ticks==12));
      // if we have reached 24 ticks then we have reached a BEAT
      if(ticks >= 24){
        flags.on(BMC_MIDI_CLOCK_FLAG_EIGTH);
        // reset the ticks to start over
        ticks = 0;

        #ifdef BMC_USE_CLICK_TRACK
          // play the click track sound if compiled
          clickTrack.play();
        #endif

        // announce that a new beat has occureed
        flags.on(BMC_MIDI_CLOCK_FLAG_BEAT);

        #if defined(BMC_DEBUG)
          if(globals.getMidiClockDebug()){
            BMC_PRINTLN(" Beat");
          }
        #endif
        return true;
      }
    }
    return false;
  }

  bool isEigthNote(){
    if(isMaster()){
      //return flags.toggleIfTrue(BMC_MIDI_CLOCK_FLAG_EIGTH);
      return ticks == 12;
    }
    return bpmCalc.isEigthNote();
  }

  bool isActive(){
    return flags.read(BMC_MIDI_CLOCK_FLAG_ACTIVE);
  }

  void setMaster(bool value){
    if(isMaster() != value){

      flags.write(BMC_MIDI_CLOCK_FLAG_MASTER, value);

      masterClockTimer.setBpm(120);

      if(value){
        BMC_PRINTLN("Master Clock Mode");
        masterClockTimer.start();
      } else {
        BMC_PRINTLN("Slave Clock Mode");
        masterClockTimer.stop();
      }

      ticks = 0;
      bpm = 0;
      setBpm(120);
    }
  }

  void setBpm(uint16_t tempo = 0){
    if(isMaster() && bpmCalc.isValidBpm(tempo)){
      tmpBpm = tempo;
      // Wait 100ms before assigning the new master BPM
      // This is in case the pot sends a multiple values too fast
      // that way we don't have to recalcultate things a bunch of times in a row
      bpmSetTimer.start(100);
    }
  }
  uint16_t getBpm(){
    return bpm;
  }

  bool beat(){
    return flags.toggleIfTrue(BMC_MIDI_CLOCK_FLAG_BEAT);
  }

  bool tempoChanged(){
    return flags.toggleIfTrue(BMC_MIDI_CLOCK_FLAG_BPM_CHANGED);
  }

  bool tap(){
    if(isMaster() && bpmCalc.tap()){
      setBpm(bpmCalc.getBpm());
      return true;
    }
    return false;
  }
  // Click Track
  #ifdef BMC_USE_CLICK_TRACK
    void clickTrackCommand(uint8_t t_command){
      clickTrack.command(t_command);
    }
    void clickTrackPlay(){
      clickTrack.play();
    }
    bool clickTrackDataChanged(){
      return clickTrack.dataChanged();
    }
    // frequency
    void clickTrackSetFrequency(uint16_t freq=2000){
      clickTrack.setFrequency(freq);
    }
    uint16_t clickTrackGetFrequency(){
      return clickTrack.getFrequency();
    }
    void clickTrackFrequencyIncrease(uint16_t min=500, uint16_t max=4000){
      clickTrack.frequencyIncrease(min, max);
    }
    void clickTrackFrequencyDecrease(uint16_t min=500, uint16_t max=4000){
      clickTrack.frequencyDecrease(min, max);
    }
    void clickTrackFreqInc(uint16_t min=500, uint16_t max=4000){
      clickTrackFrequencyIncrease(min, max);
    }
    void clickTrackFreqDec(uint16_t min=500, uint16_t max=4000){
      clickTrackFrequencyDecrease(min, max);
    }
    // mute
    void clickTrackMute(){
      clickTrack.mute();
    }
    void clickTrackUnmute(){
      clickTrack.unmute();
    }
    void clickTrackToggleMute(){
      clickTrack.toggleMute();
    }
    bool clickTrackGetMuteState(){
      return clickTrack.getMuteState();
    }
    // level
    void clickTrackSetLevel(uint8_t value=10){
      clickTrack.level(value);
    }
    uint8_t clickTrackGetLevel(){
      return clickTrack.getLevel();
    }
    void clickTrackLevelIncrease(uint16_t min=0, uint16_t max=10){
      clickTrack.levelIncrease(min, max);
    }
    void clickTrackLevelDecrease(uint16_t min=0, uint16_t max=10){
      clickTrack.levelDecrease(min, max);
    }
    void clickTrackLevelInc(uint16_t min=0, uint16_t max=10){
      clickTrackLevelIncrease(min, max);
    }
    void clickTrackLevelDec(uint16_t min=0, uint16_t max=10){
      clickTrackLevelDecrease(min, max);
    }
  #endif

  bool isMaster(){
    return flags.read(BMC_MIDI_CLOCK_FLAG_MASTER);
  }



private:
  BMCMidi& midi;
  BMCGlobals& globals;
  uint8_t ticks = 0;
  uint16_t & bpm;
  uint16_t tmpBpm = 0;
  // unsigned long interval = 0;
  #ifdef BMC_USE_CLICK_TRACK
    BMCClickTrack clickTrack;
  #endif
  BMCFlags <uint8_t> flags;
  BMCBpmCalculator bpmCalc;
  BMCTimer bpmSetTimer;
  BMCTimer timeout;
  BMCMidiClockTimer masterClockTimer;

  void assignBpm(uint16_t tempo){
    if(isMaster() && BMCBpmCalculator::isValidBpm(tempo)){
      if(bpm != tempo){
        flags.on(BMC_MIDI_CLOCK_FLAG_BPM_CHANGED);
      }
      BMC_PRINTLN("BMCMidiClock::assignBpm", tempo, "was", bpm);
      bpm = tempo;

      masterClockTimer.setBpm(bpm);
    }
  }
};
#endif