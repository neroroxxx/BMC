/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#if !defined(BMC_MIDI_SERIAL_H)
#define BMC_MIDI_SERIAL_H

#include "utility/BMC-Def.h"

#if defined(BMC_HAS_SERIAL_MIDI)

#include "HardwareSerial.h"

// * If compiling for ESP32, define default RX/TX pins for MIDI serial ports.
#if defined(BMC_FOR_ESP32)
  #define BMC_ESP32_RX1 18  // * RX pin for Serial A
  #define BMC_ESP32_TX1 17  // * TX pin for Serial A

  #define BMC_ESP32_RX2 16  // * RX pin for Serial B
  #define BMC_ESP32_TX2 15  // * TX pin for Serial B
#endif

#include "midi/BMC-SerialMIDI.h"

// *****************************************************************************
// *               Class to Handle the 4 HardwareSerial Ports I/O              
// *****************************************************************************
class BMCMidiPortSerial {
public:
  // * Constructor accepts a reference to BMCCallbacks.
  // * It uses an initializer list to initialize the serial port members.
  BMCMidiPortSerial(BMCCallbacks& cb)
    : callback(cb)
    
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
    #if defined(BMC_FOR_ESP32)
      // * On ESP32, instantiate the HardwareSerial object for port A using UART 1.
      ,BMC_MIDI_SERIAL_IO_A(1)
    #endif
    // * Initialize serialPortA with the HardwareSerial object or macro.
    ,serialPortA(BMC_MIDI_SERIAL_IO_A)
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
    #if defined(BMC_FOR_ESP32)
      // * On ESP32, instantiate the HardwareSerial object for port B using UART 2.
      ,BMC_MIDI_SERIAL_IO_B(2)
    #endif
    // * Initialize serialPortB with the HardwareSerial object or macro.
    ,serialPortB(BMC_MIDI_SERIAL_IO_B)
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
    // * For Serial port C, assume the object is defined elsewhere (or via macro).
    ,serialPortC(BMC_MIDI_SERIAL_IO_C)
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
    // * For Serial port D, assume the object is defined elsewhere (or via macro).
    ,serialPortD(BMC_MIDI_SERIAL_IO_D)
#endif
  {
    // * Constructor body (empty)
  }

  // * Initialize the MIDI serial ports.
  void begin(){
    BMC_PRINTLN(" - BMCMidiPortSerial::begin");
    
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
      #if defined(BMC_FOR_TEENSY)
        // * For Teensy, simply call begin() (Teensy's serial ports are pre-configured).
        serialPortA.begin();
      #elif defined(BMC_FOR_ESP32)
        // * For ESP32, specify the RX and TX pins for Serial A.
        serialPortA.begin(BMC_ESP32_RX1, BMC_ESP32_TX1);
      #endif
      BMC_PRINTLN("    - SerialA begin()");
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
      #if defined(BMC_FOR_TEENSY)
        serialPortB.begin();
      #elif defined(BMC_FOR_ESP32)
        // * For ESP32, specify the RX and TX pins for Serial B.
        serialPortB.begin(BMC_ESP32_RX2, BMC_ESP32_TX2);
      #endif
      BMC_PRINTLN("    - SerialB begin()");
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
      // * For Serial C, simply call begin() (assuming default setup).
      serialPortC.begin();
      BMC_PRINTLN("    - SerialC begin()");
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
      // * For Serial D, simply call begin().
      serialPortD.begin();
      BMC_PRINTLN("    - SerialD begin()");
#endif
  }

  // * Flush the buffers of all enabled serial ports.
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

  // * Read a MIDI message from the specified port.
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
      default: return false;
    }
  }

  // * dummy function
  void send_now(){}

  // * Enable MIDI thru for the specified port.
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
      default: return;
    }
  }
  
  // * Disable MIDI thru for the specified port.
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
      default: return;
    }
  }

public:
  // * Reference to callback interface.
  BMCCallbacks& callback;
  
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
  #if defined(BMC_FOR_ESP32)
    // * On ESP32, define the HardwareSerial object for Serial A (UART 1).
    HardwareSerial BMC_MIDI_SERIAL_IO_A;
  #endif
  // * Serial A Port: Instance of the BMCSerialMIDI template class.
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_A_BIT, HardwareSerial, 1, false> serialPortA;
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
  #if defined(BMC_FOR_ESP32)
    // * On ESP32, define the HardwareSerial object for Serial B (UART 2).
    HardwareSerial BMC_MIDI_SERIAL_IO_B;
  #endif
  // * Serial B Port: Instance of the BMCSerialMIDI template class.
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_B_BIT, HardwareSerial, 2, false> serialPortB;
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
  // * Serial C Port: Instance of the BMCSerialMIDI template class.
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_C_BIT, HardwareSerial, 3, false> serialPortC;
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
  // * Serial D Port: Instance of the BMCSerialMIDI template class.
  BMCSerialMIDI <BMC_MIDI_PORT_SERIAL_D_BIT, HardwareSerial, 4, false> serialPortD;
#endif
};

#endif // * BMC_HAS_SERIAL_MIDI
#endif // * BMC_MIDI_SERIAL_H