/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#if !defined(BMC_MIDI_SERIAL_H)

#define BMC_MIDI_SERIAL_H

#include "utility/BMC-Def.h"


#if defined(BMC_HAS_SERIAL_MIDI)

#include "HardwareSerial.h"

#if defined(BMC_FOR_ESP32)

  #if defined(BMC_MIDI_SERIAL_A_ENABLED) && !defined(BMC_ESP32_RX1)
    #define BMC_ESP32_RX1 5
    #define BMC_ESP32_TX1 4
  #endif

  #if defined(BMC_MIDI_SERIAL_B_ENABLED) && !defined(BMC_ESP32_RX2)
    #define BMC_ESP32_RX2 17
    #define BMC_ESP32_TX2 16
  #endif

#endif


#include "midi/BMC-SerialMIDI.h"

// ***********************************
// *       SERIAL READING CLASS
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

      #if defined(BMC_FOR_TEENSY)
        serialPortA.begin();

      #elif defined(BMC_FOR_ESP32)
        serialPortA.begin(BMC_ESP32_RX1, BMC_ESP32_TX1);

      #endif

      BMC_PRINTLN(">>> SerialA begin()");

#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)

      #if defined(BMC_FOR_TEENSY)
        serialPortB.begin();

      #elif defined(BMC_FOR_ESP32)
        serialPortB.begin(BMC_ESP32_RX2, BMC_ESP32_TX2);

      #endif
      
      BMC_PRINTLN(">>> SerialB begin()");

#endif
#if defined(BMC_MIDI_SERIAL_C_ENABLED)
      serialPortC.begin();
      BMC_PRINTLN(">>> SerialC begin()");
#endif
#if defined(BMC_MIDI_SERIAL_D_ENABLED)
      serialPortD.begin();
      BMC_PRINTLN(">>> SerialD begin()");
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
  void send_now(){
    
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
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_A_BIT, HardwareSerial, 1, false> serialPortA;
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
  // Serial B Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_B_BIT, HardwareSerial, 2, false> serialPortB;
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
  // Serial C Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_C_BIT, HardwareSerial, 3, false> serialPortC;
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
  // Serial D Port
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_D_BIT, HardwareSerial, 4, false> serialPortD;
#endif
};

#endif
#endif
