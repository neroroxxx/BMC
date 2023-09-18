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
// ***********************************
// ***********************************
// ***********************************
// *       SERIAL READING CLASS
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
