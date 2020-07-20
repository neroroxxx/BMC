/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MIDI_SERIAL_H
#define BMC_MIDI_SERIAL_H

#include "utility/BMC-Def.h"

#ifdef BMC_HAS_SERIAL_MIDI

#include <MIDI.h>

// ***********************************
// ***********************************
// ***********************************
//      WRAPPER FOR SERIAL PORTS
// ***********************************
// ***********************************
// ***********************************
struct midiSerialSettings : public midi::DefaultSettings {
   static const unsigned SysExMaxSize = BMC_MIDI_SYSEX_SIZE;
};
template <HardwareSerial& _MidiSerialPort, uint8_t SerBit>
class BMCMidiPortSerialWrapper {
public:
  midi::MidiInterface<HardwareSerial, midiSerialSettings> Port;
  BMCMidiPortSerialWrapper():Port(_MidiSerialPort){}
  void begin(uint8_t channel=MIDI_CHANNEL_OMNI){

    Port.begin(channel);
    Port.turnThruOff();
  }
  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    if(Port.read()){
      message.reset(SerBit);
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

// ***********************************
// ***********************************
// ***********************************
//         SERIAL READING CLASS
// ***********************************
// ***********************************
// ***********************************
class BMCMidiPortSerial {
public:
  BMCMidiPortSerial(BMCCallbacks& cb):
    callback(cb)
  {

  }
  void begin(){
    BMC_PRINTLN("    BMCMidiPortSerial::begin");
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
    serialPortA.begin(MIDI_CHANNEL_OMNI);
    BMC_PRINTLN("    SerialA begin()");
#endif
#if defined(BMC_MIDI_SERIAL_B_ENABLED)
      serialPortB.begin(MIDI_CHANNEL_OMNI);
      BMC_PRINTLN("    SerialB begin()");
#endif
#if defined(BMC_MIDI_SERIAL_C_ENABLED)
      serialPortC.begin(MIDI_CHANNEL_OMNI);
      BMC_PRINTLN("    SerialC begin()");
#endif
#if defined(BMC_MIDI_SERIAL_D_ENABLED)
      serialPortD.begin(MIDI_CHANNEL_OMNI);
      BMC_PRINTLN("    SerialD begin()");
#endif
  }
  bool read(uint8_t port, BMCMidiMessage& message, bool ignoreRealTime){
    switch(port){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case 0: return serialPortA.read(message, ignoreRealTime);
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1: return serialPortB.read(message, ignoreRealTime);
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2: return serialPortC.read(message, ignoreRealTime);
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3: return serialPortD.read(message, ignoreRealTime);
#endif
    }
    return false;
  }
  void turnThruOn(uint8_t port=0){
    switch(port){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case 0: return serialPortA.Port.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1: return serialPortB.Port.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2: return serialPortC.Port.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3: return serialPortD.Port.turnThruOn();
#endif
    }
  }
  void turnThruOff(uint8_t port=0){
    switch(port){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case 0: return serialPortA.Port.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1: return serialPortB.Port.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2: return serialPortC.Port.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3: return serialPortD.Port.turnThruOff();
#endif
    }
  }

public:
  BMCCallbacks& callback;
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
  // Serial A Port
  BMCMidiPortSerialWrapper <BMC_MIDI_SERIAL_IO_A, BMC_MIDI_PORT_SERIAL_A_BIT> serialPortA;
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
  // Serial B Port
  BMCMidiPortSerialWrapper <BMC_MIDI_SERIAL_IO_B, BMC_MIDI_PORT_SERIAL_B_BIT> serialPortB;
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
  // Serial C Port
  BMCMidiPortSerialWrapper <BMC_MIDI_SERIAL_IO_C, BMC_MIDI_PORT_SERIAL_C_BIT> serialPortC;
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
  // Serial D Port
  BMCMidiPortSerialWrapper <BMC_MIDI_SERIAL_IO_D, BMC_MIDI_PORT_SERIAL_D_BIT> serialPortD;
#endif
};

#endif
#endif
