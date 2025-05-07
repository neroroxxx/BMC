/*
  See https://www.roxxxtar.com/bmc for more details
  Copyright (c) 2015 - 2025 Roxxxtar.com
  Licensed under the MIT license.
  Read and send MIDI over Hardware Serial
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SERIAL_MIDI_H
#define BMC_SERIAL_MIDI_H

#include "utility/BMC-Def.h"

#if defined(BMC_HAS_SERIAL_MIDI) || defined(BMC_MIDI_BLE_ENABLED) || defined(BMC_FOR_ESP32)



#include "HardwareSerial.h"


template <uint8_t SerBit, class S, uint8_t objIndex, bool isBLE=false>
class BMCSerialMIDI {
public:
  S& Port;
  uint8_t expecting = 0;
  uint8_t status = 0;
  uint8_t channel = 0;
  uint8_t data1 = 0;
  uint8_t data2 = 0;
  uint8_t sysex[BMC_MIDI_SYSEX_SIZE];
  uint16_t sysexLen = 0;
  uint16_t rpnVal = 0xFFFF;
  uint16_t nrpnVal = 0xFFFF;
  // unsigned long tConn = 0;
  // bool connected = 0;
  bool waitForSysExClose = false;
  bool thruOn = false;

  BMCSerialMIDI(S& _port) : Port(_port)
  {}
  // BMCSerialMIDI(){}

  void begin(){
    Port.begin(31250);
  }
  void begin(uint8_t rxPin, uint8_t txPin){
    Port.begin(31250, SERIAL_8N1, rxPin, txPin);
  }
  void flush(){
    Port.flush();
  }
  void turnThruOn(){
    thruOn = true;
  }
  void turnThruOff(){
    thruOn = false;
  }
  bool read(BMCMidiMessage& message, bool ignoreRealTime){
    if(_read()){

      message.reset(SerBit);
      message.setStatus(status);
      if(message.isSystemRealTimeStatus()){
        if(ignoreRealTime){
          message.reset();
          return false;
        }
        return true;
      }
      message.setData1(data1);
      message.setData2(data2);
      if(message.isSystemExclusive()){
        message.setData1(0);
        message.setData2(0);
        if(sysexLen <= BMC_MIDI_SYSEX_SIZE){
          message.addSysEx(sysex, sysexLen);
        } else {
          message.setStatus(BMC_NONE);
        }
      } else if(message.isChannelStatus()){
        message.setChannel(channel);
      }
      return true;
    }
    // if(connected && ((unsigned long) millis()-tConn > 6000)){
    //   connected = false;
    // }
    return false;
  }
  bool _read(){
    while(Port.available() > 0){
      uint8_t c = Port.read();
      
      if(!isBLE && thruOn){
        Port.write(c);
      }
      if(c > 0x7F){
        uint8_t statusCheck = c;

        if(c < 0xF0){
          // channel status
          statusCheck = c & 0xF0;
        }
        // handle status
        switch(statusCheck){

          // 3 bytes
          case BMC_MIDI_NOTE_OFF:
          case BMC_MIDI_NOTE_ON:
          case BMC_MIDI_AFTER_TOUCH_POLY:
          case BMC_MIDI_CONTROL_CHANGE:
          case BMC_MIDI_PITCH_BEND:
            // expect 3 bytes total including status
            status = c & 0xF0;
            channel = (c & 0x0F) + 1;
            expecting = 2;
            waitForSysExClose = false;
            break;
          
          // 3 bytes
          case BMC_MIDI_SONG_POSITION:
            // expect 3 bytes total including status, no channel!
            status = c;
            channel = 0;
            expecting = 2;
            waitForSysExClose = false;
            break;

          // 2 byte
          case BMC_MIDI_AFTER_TOUCH:
          case BMC_MIDI_PROGRAM_CHANGE:
            // expect 2 bytes total including status
            status = c & 0xF0;
            channel = (c & 0x0F) + 1;
            expecting = 1;
            waitForSysExClose = false;
            break;

          // 2 bytes
          case BMC_MIDI_SONG_SELECT:
          case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
            // expect 2 bytes total including status, no channel!
            status = c;
            channel = 0;
            expecting = 1;
            waitForSysExClose = false;
            break;

          // 1 byte
          case BMC_MIDI_TUNE_REQUEST:
          case BMC_MIDI_RT_CLOCK:
          case BMC_MIDI_RT_START:
          case BMC_MIDI_RT_CONTINUE:
          case BMC_MIDI_RT_STOP:
          case BMC_MIDI_RT_ACTIVE_SENSE:
          case BMC_MIDI_RT_SYSTEM_RESET:
            status = c;
            channel = 0;
            expecting = 0;
            waitForSysExClose = false;
            return true;

          case BMC_MIDI_SYSTEM_EXCLUSIVE: 
            status = c;
            channel = 0;
            sysexLen = 0;
            sysex[sysexLen++] = 0xF0;
            // variable data
            break;

          case 0xF7:  // sysex closer
            if(status == BMC_MIDI_SYSTEM_EXCLUSIVE){
              if(waitForSysExClose){
                waitForSysExClose = false;
              } else {
                sysex[sysexLen++] = 0xF7;
              }
            }
            return true;
        }
      } else {

        // handle data
        if(waitForSysExClose){
          continue;
        }
        if(status == BMC_MIDI_SYSTEM_EXCLUSIVE){
          if(sysexLen < BMC_MIDI_SYSEX_SIZE){
            sysex[sysexLen++] = c;
          } else {
            // message too long to process, ignore it
            sysexLen = 0;
            waitForSysExClose = true;
          }
          
        } else if(expecting > 0){
          if(expecting == 2){
            data1 = c;
          } else if(expecting == 1){
            data2 = c;
          }
          expecting--;
          if(expecting == 0){
            // done
            return true;
          }
        }
      }
    }
    return false;
  }
  void writeData(uint8_t status){
    if constexpr (isBLE) {
      Port.sendMidiData(status);
    } else {
      Port.write(status);
    }
  }
  void writeData(uint8_t status, uint8_t d1){
    if constexpr (isBLE) {
      Port.sendMidiData(status, d1 & 0x7F);
    } else {
      Port.write(status);
      Port.write(d1 & 0x7F);
    }
    
  }
  void writeData(uint8_t status, uint8_t d1, uint8_t d2){
    if constexpr (isBLE) {
      Port.sendMidiData(status, d1 & 0x7F, d2 & 0x7F);
    } else {
      Port.write(status);
      Port.write(d1 & 0x7F);
      Port.write(d2 & 0x7F);
    }
  }
  void send(uint8_t type, uint8_t d1, uint8_t d2, uint8_t channel, uint8_t cable=0){
    if(type <= BMC_MIDI_PITCH_BEND){
      if(channel < 1){
        return;
      }
    }
    switch(type){
      // 3 bytes
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_PITCH_BEND:
      case BMC_MIDI_SONG_POSITION:
        writeData(type | (channel-1), d1, d2);
        break;
      // 2 byte
      case BMC_MIDI_AFTER_TOUCH:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
        writeData(type | (channel-1), d1);
        break;
      // 1 byte
      case BMC_MIDI_TUNE_REQUEST:
      case BMC_MIDI_RT_CLOCK:
      case BMC_MIDI_RT_START:
      case BMC_MIDI_RT_CONTINUE:
      case BMC_MIDI_RT_STOP:
      case BMC_MIDI_RT_ACTIVE_SENSE:
      case BMC_MIDI_RT_SYSTEM_RESET:
        writeData(type);
        break;
    }
  }
  void sendSysEx(uint16_t len, const uint8_t* arr, bool bounds = false, uint8_t cable=0){
    // writeData(BMC_MIDI_CONTROL_CHANGE | (channel-1), cc, val);
    if constexpr (isBLE) {
      #if defined(BMC_FOR_ESP32)
      Port.sendSysEx(arr, len, bounds);
      #endif
    } else {
      if(!bounds){
        Port.write(0xF0);
      }
      for(int i=0;i<len;i++){
        Port.write(arr[i]);
      }
      if(!bounds){
        Port.write(0xF7);
      }
    }
    
  }
  void sendNoteOn(uint8_t note, uint8_t vel, uint8_t channel, uint8_t cable=0){
    writeData(BMC_MIDI_NOTE_ON | (channel-1), note, vel);
  }
  void sendNoteOff(uint8_t note, uint8_t vel, uint8_t channel, uint8_t cable=0){
    writeData(BMC_MIDI_NOTE_OFF | (channel-1), note, vel);
  }
  void sendProgramChange(uint8_t pc, uint8_t channel, uint8_t cable=0){
    writeData(BMC_MIDI_PROGRAM_CHANGE | (channel-1), pc);
  }
  void sendControlChange(uint8_t cc, uint8_t val, uint8_t channel, uint8_t cable=0){
    writeData(BMC_MIDI_CONTROL_CHANGE | (channel-1), cc, val);
  }
  void sendPitchBend(int pitch, uint8_t channel, uint8_t cable=0){
    int bend = int(pitch - int(-8192));
    writeData(BMC_MIDI_PITCH_BEND | (channel-1), (bend & 0x7f), (bend >> 7) & 0x7f);
  }
  void sendAfterTouch(uint8_t pressure, uint8_t channel){
    writeData(BMC_MIDI_AFTER_TOUCH | (channel-1), pressure);
  }
  void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel){
    writeData(BMC_MIDI_AFTER_TOUCH_POLY | (channel-1), note, pressure);
  }
  void sendAfterTouchPoly(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable=0){
    writeData(BMC_MIDI_AFTER_TOUCH_POLY | (channel-1), note, pressure);
  }
  void sendTimeCodeQuarterFrame(uint8_t type, uint8_t val, uint8_t cable=0){
    writeData(BMC_MIDI_TIME_CODE_QUARTER_FRAME, ((type&0x07)<<4) | (val&0x0F));
  }
  // void sendTimeCodeQuarterFrame(uint8_t d1, uint8_t cable=0){
  //   writeData(BMC_MIDI_TIME_CODE_QUARTER_FRAME, d1);
  // }

  void sendSongPosition(uint16_t beats, uint8_t cable=0){
    writeData(BMC_MIDI_SONG_POSITION, (beats&0x7F), ((beats>>7)&0x7F));
  }
  void sendSongSelect(uint8_t inSongNumber, uint8_t cable=0){
    writeData(BMC_MIDI_SONG_SELECT, inSongNumber);
  }
  void sendTuneRequest(uint8_t cable=0){
    writeData(BMC_MIDI_TUNE_REQUEST);
  }
  // void sendCommon(uint8_t type, unsigned = 0);
  void sendClock()         { writeData(BMC_MIDI_RT_CLOCK); };
  void sendStart()         { writeData(BMC_MIDI_RT_START); };
  void sendStop()          { writeData(BMC_MIDI_RT_STOP);  };
  void sendTick()          { writeData(BMC_MIDI_RT_CLOCK);  };
  void sendContinue()      { writeData(BMC_MIDI_RT_CONTINUE);  };
  void sendActiveSensing() { writeData(BMC_MIDI_RT_ACTIVE_SENSE);  };
  void sendSystemReset()   { writeData(BMC_MIDI_RT_SYSTEM_RESET);  };
  void sendRealTime(uint8_t type, uint8_t cable=0){
    writeData(type);
  }

  void beginRpn(uint16_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(100, (val&0x7F), channel);
    sendControlChange(101, ((val>>7)&0x7F), channel);
    rpnVal = val;
  }
  void sendRpnValue(uint16_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(6, (val&0x7F), channel);
    sendControlChange(38, ((val>>7)&0x7F), channel);
  }
  void sendRpnValue(uint8_t msb, uint8_t lsb, uint8_t channel, uint8_t cable=0){
    sendControlChange(6, msb, channel);
    sendControlChange(38, lsb, channel);
  }
  void sendRpnIncrement(uint8_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(96, val, channel);
  }
  void sendRpnDecrement(uint8_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(97, val, channel);
  }
  void endRpn(uint8_t channel, uint8_t cable=0){
    sendControlChange(100, 0x7f, channel);
    sendControlChange(101, 0x7f, channel);
    rpnVal = 0xffff;
  }
  void beginNrpn(uint16_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(99, (val&0x7F), channel);
    sendControlChange(98, ((val>>7)&0x7F), channel);
    nrpnVal = val;
  }
  void sendNrpnValue(uint16_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(6, (val&0x7F), channel);
    sendControlChange(38, ((val>>7)&0x7F), channel);
  }
  void sendNrpnValue(uint8_t msb, uint8_t lsb, uint8_t channel, uint8_t cable=0){
    sendControlChange(6, msb, channel);
    sendControlChange(38, lsb, channel);
  }
  void sendNrpnIncrement(uint8_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(96, val, channel);
  }
  void sendNrpnDecrement(uint8_t val, uint8_t channel, uint8_t cable=0){
    sendControlChange(97, val, channel);
  }
  void endNrpn(uint8_t channel, uint8_t cable=0){
    sendControlChange(99, 0x7f, channel);
    sendControlChange(98, 0x7f, channel);
    nrpnVal = 0xffff;
  }
  void send_now(){
    
  }
};
#endif
#endif
