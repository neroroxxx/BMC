/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MIDI_SERIAL4_H
#define BMC_MIDI_SERIAL4_H

#include "utility/BMC-Def.h"
#include <MIDI.h>

#if defined(BMC_MIDI_SERIAL_D_ENABLED)

struct midiSerialDSettings : public midi::DefaultSettings {
   static const unsigned SysExMaxSize = BMC_MIDI_SYSEX_SIZE;
};

class BMCMidiPortSerialD {
public:
  midi::MidiInterface<HardwareSerial,midiSerialDSettings> Port;
  BMCMidiPortSerialD():Port(BMC_MIDI_SERIAL_IO_D){}
  void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
    BMC_PRINTLN("    SerialD BMCMidiPortSerialD::begin");
    Port.begin(channel);
    Port.turnThruOff();
  }
  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    if(Port.read()){
      message.reset(BMC_MIDI_PORT_SERIAL_D_BIT);
      message.setStatus((uint8_t) Port.getType());
      if(message.isSystemRealTimeStatus()){
        if(ignoreRealTime){
          message.reset();
          return false;
        }
        return true;
      }
      message.setData1(Port.getData1());
      message.setData2(Port.getData2());
      if(message.isSystemExclusive()){
        if(Port.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
          message.addSysEx(Port.getSysExArray(),Port.getSysExArrayLength());
        } else {
          message.setStatus(BMC_NONE);
        }
      } else if(message.isChannelStatus()){
        message.setChannel((uint8_t) Port.getChannel());
      }
      return true;
    }
    return false;
  }
};

#endif
#endif
