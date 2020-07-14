/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This is meant to be used with the built in DAC pin
  Teensy 3.2 Pin A14
  Teensy 3.5/3.6 A21

  Provides a simple click track linked to the MIDI CLOCK available in MIDI Clock Slave or Master
  If you are set to Slave mode the click will only play when a Clock Command is received
*/
#ifndef BMC_CLICKTRACK_H
#define BMC_CLICKTRACK_H

#ifdef BMC_USE_CLICK_TRACK

#include <Audio.h>
#include "utility/BMC-Def.h"

#define BMC_CLICK_TRACK_FLAG_MUTE 0
#define BMC_CLICK_TRACK_FLAG_CHANGED 1


class BMCClickTrack {
public:
  BMCClickTrack():
              patchCord(tick,0,mixer,0),
              patchCordMixer(mixer,output)
  {
    AudioMemory(8);
  }
  void begin(){
    // audio library init
    tick.frequency(frequency);
    tick.length(25);
    tick.pitchMod(0.55);
    level(5);
  }
  void play(){
    if(count==0){
      tick.frequency(frequency+500);
    } else if(count==1){
      tick.frequency(frequency);
    }
    if(!flags.read(BMC_CLICK_TRACK_FLAG_MUTE)){
      tick.noteOn();
    }
    if(count>=3){
      count = 0;
    } else {
      count++;
    }
  }
  void command(uint16_t t_command){
    switch(t_command){
      case BMC_CLICK_TRACK_MUTE:
        mute();
        break;
      case BMC_CLICK_TRACK_UNMUTE:
        unmute();
        break;
      case BMC_CLICK_TRACK_MUTE_TOGGLE:
        toggleMute();
        break;
      case BMC_CLICK_TRACK_FREQ_INCREASE:
        frequencyIncrease();
        break;
      case BMC_CLICK_TRACK_FREQ_DECREASE:
        frequencyDecrease();
        break;
      case BMC_CLICK_TRACK_LEVEL_INCREASE:
        levelIncrease();
        break;
      case BMC_CLICK_TRACK_LEVEL_DECREASE:
        levelDecrease();
        break;
    }
  }
  void frequencyIncrease(uint16_t min=500, uint16_t max=4000){
    BMCScroller <uint16_t> s(500, 4000);
    s.setValue(frequency, min, max);
    setFrequency(s.up(500, BMC_SCROLL_LIMITED));
  }
  void frequencyDecrease(uint16_t min=500, uint16_t max=4000){
    BMCScroller <uint16_t> s(500, 4000);
    s.setValue(frequency, min, max);
    setFrequency(s.down(500, BMC_SCROLL_LIMITED));
  }
  void levelIncrease(uint16_t min=0, uint16_t max=10){
    BMCScroller <uint8_t> s(0, 10);
    s.setValue(volume, min, max);
    setFrequency(s.up(1, BMC_SCROLL_LIMITED));
  }
  void levelDecrease(uint16_t min=0, uint16_t max=10){
    BMCScroller <uint8_t> s(0, 10);
    s.setValue(volume, min, max);
    setFrequency(s.down(1, BMC_SCROLL_LIMITED));
  }
  void toggleMute(){
    flags.on(BMC_CLICK_TRACK_FLAG_CHANGED);
    flags.toggle(BMC_CLICK_TRACK_FLAG_MUTE);
  }
  void mute(){
    if(!flags.read(BMC_CLICK_TRACK_FLAG_MUTE)){
      flags.on(BMC_CLICK_TRACK_FLAG_CHANGED);
    }
    flags.on(BMC_CLICK_TRACK_FLAG_MUTE);
  }
  void unmute(){
    if(flags.read(BMC_CLICK_TRACK_FLAG_MUTE)){
      flags.on(BMC_CLICK_TRACK_FLAG_CHANGED);
    }
    flags.off(BMC_CLICK_TRACK_FLAG_MUTE);
  }
  void setFrequency(uint16_t t_frequency){
    if(t_frequency>=500 && t_frequency<=4000 && frequency != t_frequency){
      frequency = t_frequency;
      tick.frequency(frequency);
      flags.on(BMC_CLICK_TRACK_FLAG_CHANGED);
    }
  }
  uint16_t getFrequency(){
    return frequency;
  }
  void level(uint8_t value){
    if(value>=0 && value<=10 && volume != value){
      volume = value;
      mixer.gain(0,(float) value/10.00);
      flags.on(BMC_CLICK_TRACK_FLAG_CHANGED);
    }
  }
  uint8_t getLevel(){
    return volume;
  }
  bool getMuteState(){
    return flags.read(BMC_CLICK_TRACK_FLAG_MUTE);
  }
  bool dataChanged(){
    return flags.toggleIfTrue(BMC_CLICK_TRACK_FLAG_CHANGED);
  }
private:
  AudioSynthSimpleDrum tick;
  AudioMixer4 mixer;
  AudioOutputAnalog output;
  AudioConnection patchCord;
  AudioConnection patchCordMixer;
  BMCFlags <uint8_t> flags;
  uint16_t frequency = 2000;
  uint8_t volume = 0;
  uint8_t count = 0;
};

#endif

#endif
