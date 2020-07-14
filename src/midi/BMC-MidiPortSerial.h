/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MIDI_SERIAL_H
#define BMC_MIDI_SERIAL_H

#include "utility/BMC-Def.h"
#include <MIDI.h>

#include "midi/BMC-MidiPortSerialA.h"
#if defined(BMC_MIDI_SERIAL_B_ENABLED)
  #include "midi/BMC-MidiPortSerialB.h"
#endif
#if defined(BMC_MIDI_SERIAL_C_ENABLED)
  #include "midi/BMC-MidiPortSerialC.h"
#endif
#if defined(BMC_MIDI_SERIAL_D_ENABLED)
  #include "midi/BMC-MidiPortSerialD.h"
#endif

class BMCMidiPortSerial {
public:
  BMCMidiPortSerial(BMCCallbacks& cb):
    callback(cb)
  {

  }
  void begin(){
    BMC_PRINTLN("    BMCMidiPortSerial::begin");
    serialPortA.begin(MIDI_CHANNEL_OMNI);
    #if defined(BMC_MIDI_SERIAL_B_ENABLED)
      serialPortB.begin(MIDI_CHANNEL_OMNI);
    #endif
    #if defined(BMC_MIDI_SERIAL_C_ENABLED)
      serialPortC.begin(MIDI_CHANNEL_OMNI);
    #endif
    #if defined(BMC_MIDI_SERIAL_D_ENABLED)
      serialPortD.begin(MIDI_CHANNEL_OMNI);
    #endif
  }
  bool read(uint8_t port, BMCMidiMessage& message, bool ignoreRealTime){
    switch(port){
      case 0:
        return serialPortA.read(message, ignoreRealTime);

    #ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1:
        return serialPortB.read(message, ignoreRealTime);
    #endif

    #ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2:
        return serialPortC.read(message, ignoreRealTime);
    #endif

    #ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3:
        return serialPortD.read(message, ignoreRealTime);
    #endif
    }
    return false;
  }
  void turnThruOn(uint8_t port=0){
    switch(port){
      case 0:
        return serialPortA.Port.turnThruOn();
    #ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1:
        return serialPortB.Port.turnThruOn();
    #endif

    #ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2:
        return serialPortC.Port.turnThruOn();
    #endif

    #ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3:
        return serialPortD.Port.turnThruOn();
    #endif
    }
  }
  void turnThruOff(uint8_t port=0){
    switch(port){
      case 0:
        return serialPortA.Port.turnThruOff();
    #ifdef BMC_MIDI_SERIAL_B_ENABLED
      case 1:
        return serialPortB.Port.turnThruOff();
    #endif

    #ifdef BMC_MIDI_SERIAL_C_ENABLED
      case 2:
        return serialPortC.Port.turnThruOff();
    #endif

    #ifdef BMC_MIDI_SERIAL_D_ENABLED
      case 3:
        return serialPortD.Port.turnThruOff();
    #endif
    }
  }

public:
  BMCCallbacks& callback;
  BMCMidiPortSerialA serialPortA;
  #if defined(BMC_MIDI_SERIAL_B_ENABLED)
    BMCMidiPortSerialB serialPortB;
  #endif
  #if defined(BMC_MIDI_SERIAL_C_ENABLED)
    BMCMidiPortSerialC serialPortC;
  #endif
  #if defined(BMC_MIDI_SERIAL_D_ENABLED)
    BMCMidiPortSerialD serialPortD;
  #endif
};

#endif
