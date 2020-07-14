/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Wrapper to control/read from Kemper Profilers, not tested but based on documentation

  This class is not Tested, if you own a Kemper profiler please help development
  visit RoxXxtar.com/contact and message me.
  Currently i'm trying to get my  hands on a Kemper for testing once I do I will
  implement the whole thing ;-)

  1: 0xF0
  2: 0x00
  3: 0x20
  4: 0x33
  5: 0x02
  6: 0x7F
  7: message id
  n: payload
  n+payload: 0xF7

*/
#ifndef BMC_KEMPER_H
#define BMC_KEMPER_H
#include "utility/BMC-Def.h"
#if defined(BMC_USE_KEMPER)

#if !defined(BMC_KEMPER_DEVICE_ID)
  #define BMC_KEMPER_DEVICE_ID 0x7F
#endif

#define BMC_KEMPER_FN_CODE_PARAM_CHANGE 0x01
#define BMC_KEMPER_FN_CODE_MULTI_PARAM_CHANGE 0x02
#define BMC_KEMPER_FN_CODE_STRING_PARAM 0x03
#define BMC_KEMPER_FN_CODE_BLOB 0x04
#define BMC_KEMPER_FN_CODE_EXT_PARAM_CHANGE 0x06
#define BMC_KEMPER_FN_CODE_EXT_STRING_CHANGE 0x07
#define BMC_KEMPER_FN_CODE_REQUEST_SINGLE_PARAM 0x41
#define BMC_KEMPER_FN_CODE_REQUEST_MULTI_PARAM 0x42
#define BMC_KEMPER_FN_CODE_REQUEST_STRING_PARAM 0x43
#define BMC_KEMPER_FN_CODE_REQUEST_EXT_STRING_PARAM 0x47
#define BMC_KEMPER_FN_CODE_REQUEST_PARAM_RENDERED_STRING 0x7C

class BMCKemper {
public:
  BMCKemper(BMCMidi& t_midi):midi(t_midi){

  }
  void update(){

  }
  void setChannel(uint8_t t_channel){
    channel = (t_channel & 0x0F) + 1;
  }
  void setPort(uint8_t t_port){
    // remove the port preset, ble and usb bits
    port = t_port & 0xC1;
  }
  void incoming(BMCMidiMessage& message){
    if(!isKemperSysExMessage()){
      parseIncomingSysEx(message);
    } else if(!isKemperMidiMessage()){
      parseIncomingMidi(message);
    }
  }

  // change a parameter value to kemper
  void sendSetParameter(uint8_t page, uint8_t param, uint8_t value){
    sendSetParameter(param|(page<<8), value);
  }
  void sendSetParameter(uint16_t param, uint16_t value){
    BMCMidiMessage message;
    prepSysEx(message, BMC_KEMPER_FN_CODE_PARAM_CHANGE);
    message.appendToSysEx14BitsLSBFirst(param);
    message.appendToSysEx14BitsLSBFirst(value);
    sendSysEx(message);
  }
  // take value as a percentage from 0 to 100, non-float
  void sendSetParameterPercentage(uint8_t page, uint8_t param, uint8_t value){
    sendSetParameterPercentage(param|(page<<8), value);
  }
  void sendSetParameterPercentage(uint16_t param, uint8_t value){
    value = constrain(value, 0, 100);
    sendSetParameter(param, map(value, 0, 100, 0, 0xFFFFFFFF));
  }

  // Request a single parameter
  void requestParameter(uint8_t page, uint8_t param){
    requestParameter(param|(page<<8));
  }
  // Request a single parameter
  void requestParameter(uint16_t param){
    BMCMidiMessage message;
    prepSysEx(message, BMC_KEMPER_FN_CODE_REQUEST_SINGLE_PARAM);
    message.appendToSysEx14BitsLSBFirst(param);
    sendSysEx(message);
  }


  // Request a string parameter
  void requestStringParameter(uint8_t page, uint8_t param){
    requestStringParameter(param|(page<<8));
  }
  // Request a string parameter
  void requestStringParameter(uint16_t param){
    BMCMidiMessage message;
    prepSysEx(message, BMC_KEMPER_FN_CODE_REQUEST_STRING_PARAM);
    message.appendToSysEx14BitsLSBFirst(param);
    sendSysEx(message);
  }
private:
  BMCMidi& midi;
  uint8_t channel = 0;
  uint8_t port = 0;
  uint16_t rig = 0;
  void parseIncomingSysEx(BMCMidiMessage& message){
    if(message.size()<7){
      return;
    }
    uint8_t code = message.get7Bits(6);
    switch(code){
      // respond to param change request
      case BMC_KEMPER_FN_CODE_PARAM_CHANGE:
        receivedParameterValue(message);
        break;
      case BMC_KEMPER_FN_CODE_STRING_PARAM:
        receivedStringParameterValue(message);
        break;
    }
  }
  void parseIncomingMidi(BMCMidiMessage& message){

  }
  void receivedParameterValue(BMCMidiMessage& message){
    uint16_t param = message.get14BitsLSBFirst(7);
    uint16_t value = message.get14BitsLSBFirst(9);
    if(midi.callback.kemperParamReceived){
      midi.callback.kemperParamReceived(param, value);
    }
  }
  void receivedStringParameterValue(BMCMidiMessage& message){
    uint16_t param = message.get14BitsLSBFirst(7);
    uint8_t len = message.size()-8;
    char str[len+1];
    message.getStringFromSysEx(9, str, len);
    if(midi.callback.kemperStringReceived){
      midi.callback.kemperStringReceived(param, str, len);
    }
  }
  void sendSysEx(BMCMidiMessage& message){
    midi.sendSysEx(
      port, // syn port(s)
      message.getSysEx(), // the sysex array
      message.size(), // the sysex array length
      false, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      true // should it trigger MIDI Out activity
    );
  }
  // send NRPN with page and parameter id separated
  void sendNRPN(uint8_t page, uint8_t param, uint32_t value){
    sendNRPN(param|(page<<8), value);
  }
  // send NRPN with page and parameter id encoded into 14-bits
  void sendNRPN(uint16_t param, uint32_t value){
    midi.sendControlChange(port, channel, 99, ((param >> 8) & 0x7F));
    midi.sendControlChange(port, channel, 98, (param & 0x7F));
    midi.sendControlChange(port, channel, 6, ((value >> 8) & 0x7F));
    midi.sendControlChange(port, channel, 38, (value & 0x7F));
  }
  void prepSysEx(BMCMidiMessage& message, uint8_t messageId){
    message.setStatus(BMC_MIDI_SYSTEM_EXCLUSIVE);
    message.appendToSysEx7Bits(0x00);
    message.appendToSysEx7Bits(0x20);
    message.appendToSysEx7Bits(0x33);
    message.appendToSysEx7Bits(2); // Product Type 0x02 = Kemper Profiler
    message.appendToSysEx7Bits(BMC_KEMPER_DEVICE_ID); // Device ID 0x7F = OMNI (See Manual)
    message.appendToSysEx7Bits(messageId);
  }

  bool isKemperSysExMessage(BMCMidiMessage& message, uint8_t minLength=5){
    return (message.isSysEx() &&
      message.size()>=minLength &&
      message.sysex[1]==0x00 &&
      message.sysex[2]==0x20 &&
      message.sysex[3]==0x33
    );
  }
  bool isKemperMidiMessage(BMCMidiMessage& message, uint8_t minLength=5){
    return (message.isControlChange() ||
            message.isProgramChange()) &&
            midi.getChannel()==channel;
  }
  void tunerNote(uint8_t note, char* str){
		switch(note){
			case 0: strcpy(str, "C "); break;
			case 1: strcpy(str, "C#"); break;
			case 2: strcpy(str, "D "); break;
			case 3: strcpy(str, "Eb"); break;
			case 4: strcpy(str, "E "); break;
			case 5: strcpy(str, "F "); break;
			case 6: strcpy(str, "F#"); break;
			case 7: strcpy(str, "G "); break;
			case 8: strcpy(str, "G#"); break;
      case 9: strcpy(str, "A "); break;
			case 10: strcpy(str, "Bb"); break;
			case 11: strcpy(str, "B "); break;
		}
	}

};

#endif
#endif
