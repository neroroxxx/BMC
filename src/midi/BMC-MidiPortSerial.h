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
#include "HardwareSerial.h"
#include "midi/BMC-SerialMIDI.h"

// #include <MIDI.h>

// struct midiSerialSettings : public midi::DefaultSettings {
//    static const unsigned SysExMaxSize = BMC_MIDI_SYSEX_SIZE;
// };

// // ***********************************
// // ***********************************
// // ***********************************
// // Each MIDI Port has it's own class
// // ***********************************
// // ***********************************
// // ***********************************
// #if defined(BMC_MIDI_SERIAL_A_ENABLED)
// template <uint8_t SerBit>
// class BMCMidiPortSerialAWrapper {
// public:
//   midi::SerialMIDI<HardwareSerial> serialPort;
//   midi::MidiInterface<midi::SerialMIDI<HardwareSerial>, midiSerialSettings> Port;
//   BMCMidiPortSerialAWrapper():serialPort(BMC_MIDI_SERIAL_IO_A),Port(serialPort){}

//   void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
//     Port.begin(channel);
//     Port.turnThruOff();
//   }
//   void flush(){
//     BMC_MIDI_SERIAL_IO_A.flush();
//   }
//   bool read(BMCMidiMessage& message, bool ignoreRealTime){
//     if(Port.read()){
//       message.reset(SerBit);
//       message.setStatus((uint8_t) Port.getType());
//       if(message.isSystemRealTimeStatus()){
//         if(ignoreRealTime){
//           message.reset();
//           return false;
//         }
//         return true;
//       }
//       message.setData1(Port.getData1());
//       message.setData2(Port.getData2());
//       if(message.isSystemExclusive()){
//         message.setData1(0);
//         message.setData2(0);
        
//         if(Port.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
//           message.addSysEx(Port.getSysExArray(), Port.getSysExArrayLength());
//           // BMC_PRINTLN(message.sysex[0], message.sysex[1], message.sysex[2], message.sysex[3], message.sysex[4]);
//         } else {
//           message.setStatus(BMC_NONE);
//         }
//       } else if(message.isChannelStatus()){
//         message.setChannel((uint8_t) Port.getChannel());
//       }
//       return true;
//     }
//     return false;
//   }
// };
// #endif

// #if defined(BMC_MIDI_SERIAL_B_ENABLED)
// template <uint8_t SerBit>
// class BMCMidiPortSerialBWrapper {
// public:
//   midi::SerialMIDI<HardwareSerial> serialPort;
//   midi::MidiInterface<midi::SerialMIDI<HardwareSerial>, midiSerialSettings> Port;
//   BMCMidiPortSerialBWrapper():serialPort(BMC_MIDI_SERIAL_IO_B), Port(serialPort){}
//   void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
//     Port.begin(channel);
//     Port.turnThruOff();
//   }
//   void flush(){
//     BMC_MIDI_SERIAL_IO_B.flush();
//   }
//   bool read(BMCMidiMessage& message, bool ignoreRealTime){
//     if(Port.read()){
//       message.reset(SerBit);
//       message.setStatus((uint8_t) Port.getType());
//       if(message.isSystemRealTimeStatus()){
//         if(ignoreRealTime){
//           message.reset();
//           return false;
//         }
//         return true;
//       }
//       message.setData1(Port.getData1());
//       message.setData2(Port.getData2());
//       if(message.isSystemExclusive()){
//         message.setData1(0);
//         message.setData2(0);
//         if(Port.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
//           message.addSysEx(Port.getSysExArray(), Port.getSysExArrayLength());
//           if(message.sysex[0] == 0xF7){
//             message.reset();
//             return false;
//           }
//         } else {
//           message.setStatus(BMC_NONE);
//         }
//       } else if(message.isChannelStatus()){
//         message.setChannel((uint8_t) Port.getChannel());
//       }
//       return true;
//     }
//     return false;
//   }
// };
// #endif

// #if defined(BMC_MIDI_SERIAL_C_ENABLED)
// template <uint8_t SerBit>
// class BMCMidiPortSerialCWrapper {
// public:
//   midi::SerialMIDI<HardwareSerial> serialPort;
//   midi::MidiInterface<midi::SerialMIDI<HardwareSerial>, midiSerialSettings> Port;
//   BMCMidiPortSerialCWrapper():serialPort(BMC_MIDI_SERIAL_IO_C), Port(serialPort){}
//   void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
//     Port.begin(channel);
//     Port.turnThruOff();
//   }
//   void flush(){
//     BMC_MIDI_SERIAL_IO_C.flush();
//   }
//   bool read(BMCMidiMessage& message, bool ignoreRealTime){
//     if(Port.read()){
//       message.reset(SerBit);
//       message.setStatus((uint8_t) Port.getType());
//       if(message.isSystemRealTimeStatus()){
//         if(ignoreRealTime){
//           message.reset();
//           return false;
//         }
//         return true;
//       }
//       message.setData1(Port.getData1());
//       message.setData2(Port.getData2());
//       if(message.isSystemExclusive()){
//         message.setData1(0);
//         message.setData2(0);
//         if(Port.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
//           message.addSysEx(Port.getSysExArray(), Port.getSysExArrayLength());
//           if(message.sysex[0] == 0xF7){
//             message.reset();
//             return false;
//           }
//         } else {
//           message.setStatus(BMC_NONE);
//         }
//       } else if(message.isChannelStatus()){
//         message.setChannel((uint8_t) Port.getChannel());
//       }
//       return true;
//     }
//     return false;
//   }
// };
// #endif

// #if defined(BMC_MIDI_SERIAL_D_ENABLED)
// template <uint8_t SerBit>
// class BMCMidiPortSerialDWrapper {
// public:
//   midi::SerialMIDI<HardwareSerial> serialPort;
//   midi::MidiInterface<midi::SerialMIDI<HardwareSerial>, midiSerialSettings> Port;
//   BMCMidiPortSerialDWrapper():serialPort(BMC_MIDI_SERIAL_IO_D), Port(serialPort){}
//   void begin(uint8_t channel=MIDI_CHANNEL_OMNI){
//     Port.begin(channel);
//     Port.turnThruOff();
//   }
//   void flush(){
//     BMC_MIDI_SERIAL_IO_D.flush();
//   }
//   bool read(BMCMidiMessage& message, bool ignoreRealTime){
//     if(Port.read()){
//       message.reset(SerBit);
//       message.setStatus((uint8_t) Port.getType());
//       if(message.isSystemRealTimeStatus()){
//         if(ignoreRealTime){
//           message.reset();
//           return false;
//         }
//         return true;
//       }
//       message.setData1(Port.getData1());
//       message.setData2(Port.getData2());
//       if(message.isSystemExclusive()){
//         message.setData1(0);
//         message.setData2(0);
//         if(Port.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
//           message.addSysEx(Port.getSysExArray(), Port.getSysExArrayLength());
//           if(message.sysex[0] == 0xF7){
//             message.reset();
//             return false;
//           }
//         } else {
//           message.setStatus(BMC_NONE);
//         }
//       } else if(message.isChannelStatus()){
//         message.setChannel((uint8_t) Port.getChannel());
//       }
//       return true;
//     }
//     return false;
//   }
// };
// #endif

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
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
    ,serialPortA(BMC_MIDI_SERIAL_IO_A)
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
    ,serialPortB(BMC_MIDI_SERIAL_IO_B)
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
    ,serialPortC(BMC_MIDI_SERIAL_IO_C)
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
    ,serialPortD(BMC_MIDI_SERIAL_IO_D)
#endif

  {

  }

  void begin(){
    BMC_PRINTLN("    BMCMidiPortSerial::begin");
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
      serialPortA.begin();
      BMC_PRINTLN("    SerialA begin()");
#endif
#if defined(BMC_MIDI_SERIAL_B_ENABLED)
      serialPortB.begin();
      BMC_PRINTLN("    SerialB begin()");
#endif
#if defined(BMC_MIDI_SERIAL_C_ENABLED)
      serialPortC.begin();
      BMC_PRINTLN("    SerialC begin()");
#endif
#if defined(BMC_MIDI_SERIAL_D_ENABLED)
      serialPortD.begin();
      BMC_PRINTLN("    SerialD begin()");
#endif
  }

  void flush(){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      serialPortA.flush();
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      serialPortB.flush();
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      serialPortC.flush();
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      serialPortD.flush();
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
      case 0: return serialPortA.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1: return serialPortB.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2: return serialPortC.turnThruOn();
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3: return serialPortD.turnThruOn();
#endif
    }
  }
  
  void turnThruOff(uint8_t port=0){
    switch(port){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case 0: return serialPortA.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1: return serialPortB.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2: return serialPortC.turnThruOff();
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3: return serialPortD.turnThruOff();
#endif
    }
  }

public:
  BMCCallbacks& callback;
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
  // Serial A Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_A_BIT, HardwareSerial> serialPortA;
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
  // Serial B Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_B_BIT, HardwareSerial> serialPortB;
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
  // Serial C Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_C_BIT, HardwareSerial> serialPortC;
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
  // Serial D Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_D_BIT, HardwareSerial> serialPortD;
#endif
};

#endif
#endif
