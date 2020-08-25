/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MIDI_BLE_H
#define BMC_MIDI_BLE_H

#include "utility/BMC-Def.h"

#ifdef BMC_MIDI_BLE_ENABLED
#include "midi/BMC-SerialBle.h"
#include <MIDI.h>

struct midiSerialBleSettings : public midi::DefaultSettings {
  static const unsigned SysExMaxSize = BMC_MIDI_SYSEX_SIZE;
};

class BMCMidiPortBle {
public:

  BMCSerialBle SerialBle;
  midi::SerialMIDI<BMCSerialBle> serialPort;
  midi::MidiInterface<midi::SerialMIDI<BMCSerialBle>, midiSerialBleSettings> Port;

  BMCMidiPortBle(BMCCallbacks& cb, BMCGlobals& t_globals):
    SerialBle(t_globals),
    serialPort(SerialBle),
    Port(serialPort),
    callback(cb),
    globals(t_globals){
  }
  void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
    BMC_PRINTLN("    BMCMidiPortBle::begin");
    Port.begin(channel);
    Port.turnThruOff();
  }
  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    SerialBle.update();
    if(SerialBle.stateChanged()){
      if(callback.bleConnection){
        callback.bleConnection(globals.bleConnected());
      }
    }
    if(Port.read()){
      message.reset(BMC_MIDI_PORT_BLE_BIT);
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
        message.setData1(0);
        message.setData2(0);
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
  // Utilities
  void disconnectBLE(){
    SerialBle.disconnectBLE();
  }
private:
  BMCCallbacks& callback;
  BMCGlobals& globals;
};

#endif
#endif
