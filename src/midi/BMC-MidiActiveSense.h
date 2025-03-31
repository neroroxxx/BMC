/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A MIDI Active sense class, it handles sending an Active Sense message (0xFE)
  Every 300 ms (as the MIDI Spec specifies) to the specified MIDI Port(s)
  It also keeps track of incoming Active Sense Messages on all ports.
*/

#ifndef __BMC_MIDI_ACTIVE_SENSE_H__
#define __BMC_MIDI_ACTIVE_SENSE_H__

#include "utility/BMC-Def.h"
#include "midi/BMC-Midi.h"

class BMCMidiActiveSense {
public:
  BMCMidiActiveSense(BMCMidi& t_midi):midi(t_midi){
    inTimer.stop();
    outTimer.stop();
  }
  void begin(){
    BMC_PRINTLN("    BMCMidiActiveSense::begin");
  }
  void update(){
    if(outTimer.complete() && ports.get()!=BMC_NONE){
      midi.sendRealTime(ports.get(), BMC_MIDI_RT_ACTIVE_SENSE);
      outTimer.start(300);
    }
    if(inTimer.complete()){
      inTimer.stop();
    }
  }
  // in active sense
  void received(uint8_t t_status){
    if(t_status==BMC_MIDI_RT_ACTIVE_SENSE){
      // add an extra 200ms for the next incoming message in case of jitter
      inTimer.start(500);
    }
  }
  bool reading(){
    return inTimer.active();
  }
  void command(uint8_t t_command, uint8_t t_ports=BMC_NONE){
    switch(t_command & 0x03){
      case BMC_ACTIVE_SENSE_STOP:
        stop();
        break;
      case BMC_ACTIVE_SENSE_START:
        start();
        break;
      case BMC_ACTIVE_SENSE_TOGGLE:
        toggle();
        break;
    }
  }
  // out active sense
  void toggle(){
    if(!outTimer.active()){
      start();
    } else {
      stop();
    }
  }
  void start(){
    if(ports.get()!=BMC_NONE && !outTimer.active()){
      BMC_PRINTLN("BMCMidiActiveSense Start");
      outTimer.start(300);
    }
  }
  void stop(){
    BMC_PRINTLN("BMCMidiActiveSense Stop");
    outTimer.stop();
  }
  void setOutputPorts(uint8_t t_ports){
    ports.set(t_ports);
  }
  bool active(){
    return outTimer.active();
  }
private:
  BMCMidi& midi;
  BMCTimer outTimer;
  BMCTimer inTimer;
  BMCMidiPort ports;

};
#endif
