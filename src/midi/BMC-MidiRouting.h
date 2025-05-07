/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Handles Midi Routing
*/

#ifndef __BMC_MIDI_ROUTING_H__
#define __BMC_MIDI_ROUTING_H__

#include "utility/BMC-Def.h"

class BMCMidiRouting {
public:
  BMCMidiRouting(){
  }
  void begin(){
    BMC_PRINTLN("BMCMidiRouting::begin");
  }
  void assign(uint8_t t_port, uint16_t t_data){
    switch(t_port){
      case BMC_USB: routing.usb.setData(t_data); break;

#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case BMC_SERIAL_A: routing.serialA.setData(t_data); break;
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case BMC_SERIAL_B: routing.serialB.setData(t_data); break;
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case BMC_SERIAL_C: routing.serialC.setData(t_data); break;
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case BMC_SERIAL_D: routing.serialD.setData(t_data); break;
#endif

#ifdef BMC_USB_HOST_ENABLED
      case BMC_HOST: routing.host.setData(t_data); break;
#endif

#ifdef BMC_MIDI_BLE_ENABLED
      case BMC_BLE: routing.ble.setData(t_data); break;
#endif
    }
  }

  uint8_t incoming(BMCMidiMessage m){
    if(m.getStatus()==BMC_NONE){
      return BMC_NONE;
    }
    BMCRoutingItem item;
    switch(m.getSource()){
      case BMC_USB: item = routing.usb; break;

#ifdef BMC_MIDI_SERIAL_A_ENABLED
      case BMC_SERIAL_A: item = routing.serialA; break;
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
      case BMC_SERIAL_B: item = routing.serialB; break;
#endif

#ifdef BMC_MIDI_SERIAL_C_ENABLED
      case BMC_SERIAL_C: item = routing.serialC; break;
#endif

#ifdef BMC_MIDI_SERIAL_D_ENABLED
      case BMC_SERIAL_D: item = routing.serialD; break;
#endif

#ifdef BMC_USB_HOST_ENABLED
      case BMC_HOST: item = routing.host; break;
#endif

#ifdef BMC_MIDI_BLE_ENABLED
      case BMC_BLE: item = routing.ble; break;
#endif
      default:
        return BMC_NONE;
    }

    if(item.hasDestination()){
      if(processFilter(m, item)){
        return item.destinations;
      }
    }
    return BMC_NONE;
  }

private:
  BMCRoutingData routing;
  bool processFilter(BMCMidiMessage m, BMCRoutingItem item){
    // filter bits
    // 0 - voice messages (cc, pc, note etc.)
    // 1 - system exclusive
    // 2 - system common
    // 3 - real time
    if(m.isVoiceStatus() && bitRead(item.filters, 0)){
      // allow voice messages if channel is OMNI (0) or matches
      return (item.channel==0 || item.channel==m.getChannel());
    } else if(m.isSystemExclusiveStatus() && bitRead(item.filters, 1)){
      return true; // allow system exclusive
    } else if(m.isSystemCommonStatus() && bitRead(item.filters, 2)){
      return true; // allow system common
    } else if(m.isSystemRealTimeStatus() && bitRead(item.filters, 3)){
      return true; // allow Real Time
    }
    return false;
  }
};
#endif
