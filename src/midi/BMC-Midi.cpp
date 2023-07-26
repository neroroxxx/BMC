/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#include "midi/BMC-Midi.h"

void BMCMidi::send(BMCMidiMessage m, uint8_t cable){
  send(m.getSource(),m,cable);
}
void BMCMidi::send(uint8_t port, BMCMidiMessage m, uint8_t cable){
  if(m.getStatus()==BMC_NONE){
    return;
  }
  if(!m.isSystemExclusive()){
    send(
      port,
      m.getStatus(),
      m.getData1(),
      m.getData2(),
      m.getChannel(),
      cable
    );
  } else {
    sendSysEx(
      port,
      m.getSysEx(),
      m.size(),
      (m.sysex[0]==0xF0),
      cable
    );
  }
}
void BMCMidi::send(uint8_t ports, uint32_t event){
  send((event & 0x00FFFFFF) | (ports << 24));
}
void BMCMidi::send(uint32_t event){
  BMCMidiEvent e;
  e.setEvent(event);
  send(e);
}
void BMCMidi::send(BMCMidiEvent event, uint8_t cable){
  if(event.hasEvent()){
    send(
      event.getPort(),
      event.getStatus(),
      event.getData1(),
      event.getData2(),
      event.getChannel()+1,
      cable);
  }
}
void BMCMidi::send(uint8_t port, uint8_t type,
                  uint8_t data1, uint8_t data2,
                  uint8_t channel, uint8_t cable){
  // check if it's a realtime
  switch(type){
    case BMC_MIDI_RT_CLOCK:
    case BMC_MIDI_RT_START:
    case BMC_MIDI_RT_CONTINUE:
    case BMC_MIDI_RT_STOP:
    case BMC_MIDI_RT_ACTIVE_SENSE:
    case BMC_MIDI_RT_SYSTEM_RESET:
      sendRealTime(port,type,cable);
      return;
    case BMC_MIDI_SONG_SELECT:
      sendSongSelect(port, data1, cable);
      return;
    case BMC_MIDI_SONG_POSITION:
      sendSongPosition(port, (data1 & 0x7F) | ((data2 & 0x7F)<<7), cable);
      return;
    case 0xF0:
    case 0xF4:
    case 0xF5:
    case 0xF9:
    case 0xFD:
      return;
  }
  type &= 0xF0;
  if(data2 > 127){
    data2 = getLocalControl(channel,data1)>0 ? 0 : 127;
  }
  if(isMidiUsbPort(port)){
    usbMIDI.send(type, data1, data2, channel, cable);
  }

#ifdef BMC_MIDI_SERIAL_A_ENABLED
  if(isMidiSerialAPort(port)){
    midiSerial.serialPortA.send(
      type,
      data1,
      data2,
      channel
    );
  }
#endif

#ifdef BMC_MIDI_SERIAL_B_ENABLED
  if(isMidiSerialBPort(port)){
    midiSerial.serialPortB.send(
      type,
      data1,
      data2,
      channel
    );
  }
#endif
#ifdef BMC_MIDI_SERIAL_C_ENABLED
  if(isMidiSerialCPort(port)){
    midiSerial.serialPortC.send(
      type,
      data1,
      data2,
      channel
    );
  }
#endif
#ifdef BMC_MIDI_SERIAL_D_ENABLED
  if(isMidiSerialDPort(port)){
    midiSerial.serialPortD.send(
      type,
      data1,
      data2,
      channel
    );
  }
#endif

  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.send(type, data1, data2, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.send((midi::MidiType) type, data1, data2, channel);
    }
  #endif
  if(type == BMC_MIDI_PROGRAM_CHANGE){
    setLocalProgram(channel,data1);
  } else if(type == BMC_MIDI_CONTROL_CHANGE){
    setLocalControl(channel,data1,data2);
  }
  globals.setMidiOutActivity();

  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    if(!isSkipped(type)){
      BMC_PRINTLN(
        millis(),
        BMCTools::printPortsNames(getPortPreset(port)),
        "Outgoing",BMCTools::getMidiStatusName(type),
        "channel:",channel,
        "data1:",data1,
        "data2:",data2
      );
    }
  }
  #endif
}
void BMCMidi::sendRealTime(uint8_t port, uint8_t type, uint8_t cable){
  if(flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_OUTPUT)){
    return;
  }
  if(isMidiUsbPort(port)){
    usbMIDI.sendRealTime(type, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendRealTime(type);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendRealTime(type);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendRealTime(type);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendRealTime(type);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendRealTime(type,cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(
      isMidiBlePort(port) &&
      globals.bleConnected() &&
      type!=BMC_MIDI_RT_CLOCK &&
      type!=BMC_MIDI_RT_ACTIVE_SENSE
    ){
      midiBle.Port.sendRealTime((midi::MidiType) type);
    }
  #endif
  // don't light up the midi out led(s) for these
  if(!isSkipped(type)){
    globals.setMidiOutActivity();
  }
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    if(isSkipped(type) && !globals.getMidiOutClockDebug()){
      return;
    }
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing",BMCTools::getMidiStatusName(type)
    );
  }
  #endif
}
void BMCMidi::sendSysEx(uint8_t port, uint8_t *data,
                        uint16_t size, bool hasTerm,
                        uint8_t cable, bool midiOutActivityAllowed){
  if(size==0){
    return;
  }
  if(isMidiUsbPort(port)){
    usbMIDI.sendSysEx(size, data, hasTerm, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      #if BMC_DELAY_SYSEX_ON_SERIAL > 0
        delay(BMC_DELAY_SYSEX_ON_SERIAL);
      #endif
      midiSerial.serialPortA.sendSysEx(size, data, hasTerm);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      #if BMC_DELAY_SYSEX_ON_SERIAL > 0
        delay(BMC_DELAY_SYSEX_ON_SERIAL);
      #endif
      midiSerial.serialPortB.sendSysEx(size, data, hasTerm);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      #if BMC_DELAY_SYSEX_ON_SERIAL > 0
        delay(BMC_DELAY_SYSEX_ON_SERIAL);
      #endif
      midiSerial.serialPortC.sendSysEx(size, data, hasTerm);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      #if BMC_DELAY_SYSEX_ON_SERIAL > 0
        delay(BMC_DELAY_SYSEX_ON_SERIAL);
      #endif
      midiSerial.serialPortD.sendSysEx(size, data, hasTerm);
    }
  #endif

  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendSysEx(size, data, hasTerm, cable);
    }
  #endif

  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendSysEx(size, data, hasTerm);
    }
  #endif

  if(midiOutActivityAllowed){
    globals.setMidiOutActivity();
  }

  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing SysEx"
    );
    BMC_PRINT_ARRAY(true,data,size);
  }
  #endif
}
void BMCMidi::sendProgramChange(uint8_t port, uint8_t channel,
                                uint8_t program, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendProgramChange(program, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendProgramChange(program, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendProgramChange(program, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendProgramChange(program, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendProgramChange(program, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendProgramChange(program, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendProgramChange(program, channel);
    }
  #endif
  setLocalProgram(channel,program);
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Program Change",
      "channel:",channel,
      "program:",program
    );
  }
  #endif
}
void BMCMidi::sendControlChange(uint8_t port, uint8_t channel,
                                uint8_t control, uint8_t value,
                                uint8_t cable, bool localLog){
  if(value>127){
    if(getLocalControl(channel,control)>0){
      value = 0;
    } else {
      value = 127;
    }
  }
  if(isMidiUsbPort(port)){
    usbMIDI.sendControlChange(control, value, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendControlChange(control, value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendControlChange(control, value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendControlChange(control, value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendControlChange(control, value, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendControlChange(control, value , channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendControlChange(control, value, channel);
    }
  #endif
  if(localLog){
    setLocalControl(channel,control,value);
  }

  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Control Change",
      "channel:",channel,
      "control:",control,
      "value:",value
    );
  }
  //
  #endif
}
void BMCMidi::sendControlChangeNoLocalLog(uint8_t port, uint8_t channel,
                                uint8_t control, uint8_t value,
                                uint8_t cable){
  sendControlChange(port,channel,control,value,cable,false);
}
void BMCMidi::sendNoteOn(uint8_t port, uint8_t channel,
                        uint8_t note, uint8_t velocity,
                        uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendNoteOn(note, velocity, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendNoteOn(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendNoteOn(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendNoteOn(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendNoteOn(note, velocity, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendNoteOn(note, velocity, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendNoteOn(note, velocity, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Note On",
      "channel:",channel,
      "note:",note,
      "velocity:",velocity
    );
  }
  #endif
}
void BMCMidi::sendNoteOff(uint8_t port, uint8_t channel,
                          uint8_t note, uint8_t velocity,
                          uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendNoteOff(note, velocity, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendNoteOff(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendNoteOff(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendNoteOff(note, velocity, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendNoteOff(note, velocity, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendNoteOff(note, velocity, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendNoteOff(note, velocity, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Note Off",
      "channel:",channel,
      "note:",note,
      "velocity:",velocity
    );
  }
  #endif
}
void BMCMidi::sendPitchBend(uint8_t port, uint8_t channel,
                            int16_t value, uint8_t cable){
  // value range for pitch bend -8192 to 8191, 0 is center
  if(isMidiUsbPort(port)){
    usbMIDI.sendPitchBend(value, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendPitchBend(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendPitchBend(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendPitchBend(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendPitchBend(value, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendPitchBend(value, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendPitchBend(value, channel);
    }
  #endif
  globals.setMidiOutActivity();
  if(value==0){
    setLocalPitch(channel, 0);
  } else if(value>0){
    setLocalPitch(channel, map(value, 1, 8191, 1, 127));
  } else {
    setLocalPitch(channel, map(value, -8192, -1, -127, -1));
  }
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Pitch Bend",
      "channel:",channel,
      "value:",value
    );
  }
  #endif
}

void BMCMidi::sendAfterTouch(uint8_t port, uint8_t channel,
                              uint8_t pressure, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendAfterTouch(pressure, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendAfterTouch(pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendAfterTouch(pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendAfterTouch(pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendAfterTouch(pressure, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendAfterTouch(pressure, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendAfterTouch(pressure, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing After Touch",
      "channel:",channel,
      "pressure:",pressure
    );
  }
  #endif
}
void BMCMidi::sendAfterTouchPoly(uint8_t port, uint8_t channel,
                                  uint8_t note, uint8_t pressure,
                                  uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendAfterTouchPoly(note, pressure, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendAfterTouch(note, pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendAfterTouch(note, pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendAfterTouch(note, pressure, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendAfterTouch(note, pressure, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendAfterTouchPoly(note, pressure, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendAfterTouch(note, pressure, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing After Touch Poly",
      "channel:",channel,
      "note:",note,
      "pressure:",pressure
    );
  }
  #endif
}






void BMCMidi::sendTimeCodeQuarterFrame(uint8_t port, uint8_t type,
                                        uint8_t value, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendTimeCodeQuarterFrame(type, value, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendTimeCodeQuarterFrame(type, value);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendTimeCodeQuarterFrame(type, value);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendTimeCodeQuarterFrame(type, value);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendTimeCodeQuarterFrame(type, value);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendTimeCodeQuarterFrame(type, value, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendTimeCodeQuarterFrame(type, value);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Time Code Quarter Frame"
      "type:",type,
      "value:",value
    );
  }
  #endif
}
void BMCMidi::sendSongPosition(uint8_t port, uint16_t beats,
                              uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendSongPosition(beats, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendSongPosition(beats);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendSongPosition(beats);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendSongPosition(beats);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendSongPosition(beats);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendSongPosition(beats, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendSongPosition(beats);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Song Position",
      "beats:",beats
    );
  }
  #endif
}
void BMCMidi::sendSongSelect(uint8_t port, uint8_t song, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendSongSelect(song, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendSongSelect(song);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendSongSelect(song);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendSongSelect(song);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendSongSelect(song);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendSongSelect(song, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendSongSelect(song);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Song Selection",
      "song:",song
    );
  }
  #endif
}
void BMCMidi::sendTuneRequest(uint8_t port, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendTuneRequest(cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendTuneRequest();
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendTuneRequest();
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendTuneRequest();
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendTuneRequest();
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendTuneRequest(cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendTuneRequest();
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Tune Request"
    );
  }
  #endif
}
// RPN
void BMCMidi::beginRpn(uint8_t port, uint8_t channel,
                        uint16_t number, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.beginRpn(number, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.beginRpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.beginRpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.beginRpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.beginRpn(number, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.beginRpn(number, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.beginRpn(number, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing Begin Rpn",
      "channel:",channel,
      "number:",number
    );
  }
  #endif
}
void BMCMidi::sendRpnValue(uint8_t port, uint8_t channel,
                            uint16_t value, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendRpnValue(value, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendRpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendRpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendRpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendRpnValue(value, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendRpnValue(value, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendRpnValue(value, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Rpn Value",
      "channel:",channel,
      "value:",value
    );
  }
  #endif
}
void BMCMidi::sendRpnIncrement(uint8_t port, uint8_t channel,
                                uint8_t amount, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendRpnIncrement(amount, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendRpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendRpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendRpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendRpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendRpnIncrement(amount, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendRpnIncrement(amount, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Rpn Increment",
      "channel:",channel,
      "amount:",amount
    );
  }
  #endif
}
void BMCMidi::sendRpnDecrement(uint8_t port, uint8_t channel,
                                uint8_t amount, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendRpnDecrement(amount, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendRpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendRpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendRpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendRpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendRpnDecrement(amount, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendRpnDecrement(amount, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Rpn Decrement",
      "channel:",channel,
      "amount:",amount
    );
  }
  #endif
}
void BMCMidi::endRpn(uint8_t port, uint8_t channel, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.endRpn(channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.endRpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.endRpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.endRpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.endRpn(channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.endRpn(channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.endRpn(channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing end Rpn",
      "channel:",channel
    );
  }
  #endif
}
// NRPN
void BMCMidi::beginNrpn(uint8_t port, uint8_t channel,
                        uint16_t number, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.beginNrpn(number, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.beginNrpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.beginNrpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.beginNrpn(number, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.beginNrpn(number, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.beginNrpn(number, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.beginNrpn(number, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing begin Nrpn",
      "channel:",channel,
      "number:",number
    );
  }
  #endif
}
void BMCMidi::sendNrpnValue(uint8_t port, uint8_t channel,
                            uint16_t value, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendNrpnValue(value, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendNrpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendNrpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendNrpnValue(value, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendNrpnValue(value, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendNrpnValue(value, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendNrpnValue(value, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Nrpn Value",
      "channel:",channel,
      "value:",value
    );
  }
  #endif
}
void BMCMidi::sendNrpnIncrement(uint8_t port, uint8_t channel,
                                uint8_t amount, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendNrpnIncrement(amount, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendNrpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendNrpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendNrpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendNrpnIncrement(amount, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendNrpnIncrement(amount, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendNrpnIncrement(amount, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Nrpn Increment",
      "channel:",channel,
      "amount:",amount
    );
  }
  #endif
}
void BMCMidi::sendNrpnDecrement(uint8_t port, uint8_t channel,
                                uint8_t amount, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.sendNrpnDecrement(amount, channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.sendNrpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.sendNrpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.sendNrpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.sendNrpnDecrement(amount, channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.sendNrpnDecrement(amount, channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.sendNrpnDecrement(amount, channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing send Nrpn Decrement",
      "channel:",channel,
      "amount:",amount
    );
  }
  #endif
}
void BMCMidi::endNrpn(uint8_t port, uint8_t channel, uint8_t cable){
  if(isMidiUsbPort(port)){
    usbMIDI.endNrpn(channel, cable);
  }
  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    if(isMidiSerialAPort(port)){
      midiSerial.serialPortA.endNrpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_B_ENABLED
    if(isMidiSerialBPort(port)){
      midiSerial.serialPortB.endNrpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_C_ENABLED
    if(isMidiSerialCPort(port)){
      midiSerial.serialPortC.endNrpn(channel);
    }
  #endif
  #ifdef BMC_MIDI_SERIAL_D_ENABLED
    if(isMidiSerialDPort(port)){
      midiSerial.serialPortD.endNrpn(channel);
    }
  #endif
  #ifdef BMC_USB_HOST_ENABLED
    if(isMidiHostPort(port) && globals.hostConnected()){
      midiHost.Port.endNrpn(channel, cable);
    }
  #endif
  #ifdef BMC_MIDI_BLE_ENABLED
    if(isMidiBlePort(port) && globals.bleConnected()){
      midiBle.Port.endNrpn(channel);
    }
  #endif
  globals.setMidiOutActivity();
  #ifdef BMC_DEBUG
  if(globals.getMidiOutDebug()){
    BMC_PRINTLN(
      millis(),
      BMCTools::printPortsNames(getPortPreset(port)),
      "Outgoing end Nrpn",
      "channel:",channel
    );
  }
  #endif
}
// TOGGLE
uint8_t BMCMidi::toggleCC(uint8_t ports, uint8_t channel, uint8_t control){
  sendControlChange(ports, channel, control, 255);
  return getLocalControl(channel,control);
}

// SCROLLING
// channel MUST be 1 to 16 not 0 to 15
uint8_t BMCMidi::scrollCC(uint8_t ports, uint8_t channel,
                        uint8_t control, uint8_t t_flags,
                        uint8_t min, uint8_t max){
  return scrollCC(ports,channel,control, 1,bitRead(t_flags,0),bitRead(t_flags,1),min,max);
}
// channel MUST be 1 to 16 not 0 to 15
uint8_t BMCMidi::scrollCC(uint8_t ports, uint8_t channel,
                        uint8_t control, uint8_t amount, 
                        bool direction, bool endless, 
                        uint8_t min, uint8_t max){
  if(channel == 0){
    return 0;
  }
  BMCScroller <uint8_t> s(0, 127);
  uint8_t ccValue = getLocalControl(channel, control);
  ccValue = s.scroll(1, direction, endless, ccValue, min, max);
  sendControlChange(ports,channel,control,ccValue);
  return ccValue;
}
// channel MUST be 1 to 16 not 0 to 15
uint8_t BMCMidi::scrollPC(uint8_t ports, uint8_t channel,
                        uint8_t t_flags, uint8_t min, uint8_t max){
  return scrollPC(ports,channel,1,bitRead(t_flags,0),bitRead(t_flags,1),min, max);
}
// channel MUST be 1 to 16 not 0 to 15
uint8_t BMCMidi::scrollPC(uint8_t ports, uint8_t channel, uint8_t amount,
                        bool direction, bool endless,
                        uint8_t min, uint8_t max){
  if(channel == 0){
    return 0;
  }
  BMCScroller <uint8_t> s(0, 127);
  uint8_t program = getLocalProgram(channel);
  program = s.scroll(1, direction, endless, program, min, max);
  sendProgramChange(ports, channel, program);
  return program;
}
