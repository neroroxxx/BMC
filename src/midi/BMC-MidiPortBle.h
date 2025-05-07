/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MIDI_BLE_H
#define BMC_MIDI_BLE_H

#include "utility/BMC-Def.h"

#ifdef BMC_MIDI_BLE_ENABLED

#include "HardwareSerial.h"
#include "midi/BMC-SerialMIDI.h"
// ***********************************
// ***********************************
// ***********************************
// *       SERIAL READING CLASS
// ***********************************
// ***********************************
// ***********************************
class BMCMidiPortBle {
public:
  BMCMidiPortBle(BMCCallbacks& cb, BMCGlobals& t_globals):
    callback(cb),
    globals(t_globals),
    Port(BMC_MIDI_SERIAL_IO_BLE)
  {

  }

  void begin(){
    BMC_PRINTLN(" - BMCMidiPortBle::begin");
    Port.begin();
  }

  void flush(){
    Port.flush();
  }

  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    bool value = Port.read(message, ignoreRealTime);
    if(value){
      tConn = millis();
      connected = true;
    }
    if(!value && connected && ((unsigned long) millis()-tConn > 6000)){
      connected = false;
    }
    globals.setBleConnected(connected);
    return value;
  }

  void turnThruOn(uint8_t port=0){
    Port.turnThruOn();
  }
  
  void turnThruOff(uint8_t port=0){
    Port.turnThruOff();
  }

  void disconnectBLE(){
    // SerialBle.disconnectBLE();
  }

  BMCCallbacks& callback;
  BMCGlobals& globals;
  BMCSerialMIDI <BMC_MIDI_PORT_BLE_BIT, HardwareSerial, 1, false> Port;
  unsigned long tConn = 0;
  bool connected = 0;
};

#endif
#endif
