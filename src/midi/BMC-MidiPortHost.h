/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_MIDI_HOST_H
#define BMC_MIDI_HOST_H

#include "utility/BMC-Def.h"

#ifdef BMC_USB_HOST_ENABLED

#include <USBHost_t36.h>

class BMCMidiPortHost {
public:
  #if BMC_USE_USB_MIDI_BIG_BUFFER
    MIDIDevice_BigBuffer Port;
  #else
    MIDIDevice Port;
  #endif
  BMCMidiPortHost(BMCCallbacks& cb, BMCGlobals& t_globals):
    Port(UsbHost),
    callback(cb),
    globals(t_globals){

  }
  void begin(){
    BMC_PRINTLN(" - BMCMidiPortHost::begin");
    UsbHost.begin();
    delay(200);
  }
  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    UsbHost.Task();
    if((Port) != globals.hostConnected()){
      globals.setHostConnected((Port==true));
      if(callback.hostConnection){
        callback.hostConnection(globals.hostConnected());
      }
    }
    if(Port && Port.read()){
      message.reset(BMC_MIDI_PORT_HOST_BIT);
      message.setStatus(Port.getType());
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
        message.setChannel(Port.getChannel());
      }
      return true;
    }
    return false;
  }
private:
  BMCCallbacks& callback;
  BMCGlobals& globals;
  USBHost UsbHost;
};

#endif
#endif
