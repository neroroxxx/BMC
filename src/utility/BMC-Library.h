/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Send out messsages stored in store.global.library
  store.global.library is an array, each item contains an event and name (optional)
  event is a 32-bit unsigned integer (uint32_t)
  name is a char array, the length is defined by BMC_NAME_LEN_LIBRARY
  BMC_NAME_LEN_LIBRARY must be the desired length + 1 for a end of string
  the last item in the char array must be 0 ALWAYS
  A Library event is split into 4 bytes (hence why it's a 32-bit unsigned int):
   bits 0-7: MIDI Message Status (with channel)
              Program Change (0xC0)
              Control Change (0xB0)
              Etc.
   bits 1-15: MIDI Message Data1
              Program #
              Control #
              Note #
              Etc.
   bits 16-23: MIDI Message Data2
              Control Value (for control Change)
              Note Velocity (for note on/off)
              etc.
              If this value is 128 or higher it will be used as a TOGGLE
              for control changes, this will toggle the last value for a
              control change from 0 to 127 and vice-versa
   bits 14-31: MIDI Message Output Port, can be one or more ports

*/
#ifndef BMC_LIBRARY_H
#define BMC_LIBRARY_H
#if BMC_MAX_LIBRARY > 0

#include "utility/BMC-Def.h"
#if BMC_MAX_CUSTOM_SYSEX > 0
  #include "utility/BMC-CustomSysEx.h"
#endif

#define BMC_LIBRARY_FLAG_CHANGE_AVAILABLE 0
#define BMC_LIBRARY_FLAG_SET_LAYER 1
#define BMC_LIBRARY_FLAG_SET_BPM  2
#define BMC_LIBRARY_FLAG_SET_PIXEL_PROGRAM  3

class BMCLibrary {
public:

  BMCLibrary(
    BMCMidi& t_midi,
    bmcStoreGlobal& t_global,
    BMCCallbacks& cb
#if BMC_MAX_CUSTOM_SYSEX > 0
    ,BMCCustomSysEx& t_sysex
#endif
#if defined(BMC_USE_BEATBUDDY)
    ,BMCBeatBuddy& t_beatBuddy
#endif
  ):
    midi(t_midi),
    global(t_global),
    callback(cb)
#if BMC_MAX_CUSTOM_SYSEX > 0
    ,customSysEx(t_sysex)
#endif
#ifdef BMC_USE_BEATBUDDY
    ,beatBuddy(t_beatBuddy)
#endif
  {

  }
  /*
  #if defined(BMC_USE_BEATBUDDY)
    ,beatBuddy
  #endif
  */
  void send(bmcLibrary_t index){
    uint32_t event = global.library[index].event;
    uint8_t status = (event & 0xFF);
    if(index < BMC_MAX_LIBRARY){
      if(status>127 && status<0xF0){
        midi.send(event);
      } else if(status>=0xF0 && status<=0xF2){
        #if BMC_MAX_CUSTOM_SYSEX > 0
          uint8_t ports = BMC_GET_BYTE(3, event);
          sendCustomSysEx(index, status, ports);
        #endif
      } else if(status==BMC_LIBRARY_EVENT_TYPE_LAYER){// layer

        layer = BMC_GET_BYTE(1, event);
        flags.on(BMC_LIBRARY_FLAG_SET_LAYER);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_CLOCK){// clock

        bpm = mergeDataBytes(event);
        flags.on(BMC_LIBRARY_FLAG_SET_BPM);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_PIXEL_PROGRAM){// bmp

        pixelProgram = BMC_GET_BYTE(1, event);
        flags.on(BMC_LIBRARY_FLAG_SET_PIXEL_PROGRAM);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_BEATBUDDY_SET_BPM){// clock
#if defined(BMC_USE_BEATBUDDY)
        beatBuddy.tempo(mergeDataBytes(event));
#endif
      } else if(status==BMC_LIBRARY_EVENT_TYPE_BEATBUDDY_CMD){// clock
#if defined(BMC_USE_BEATBUDDY)
        beatBuddy.sendCommand(BMC_GET_BYTE(1, event), BMC_GET_BYTE(2, event));
#endif
      } else if(status==BMC_EVENT_TYPE_CUSTOM){
        uint8_t value = mergeDataBytes(event) & 0xFF;
        if(callback.libraryCustom){
          callback.libraryCustom(value);
        }
      }
    }
  }
  void sendWithDifferentPorts(bmcLibrary_t index, uint8_t ports){
    uint32_t event = global.library[index].event;
    uint8_t status = (event & 0xFF);
    if(index < BMC_MAX_LIBRARY){
      if(status>127 && status<0xF0){
        midi.send((event & 0xFFFFFF) | ports<<24);
      } else if(status>=0xF0 && status<=0xF2){
        #if BMC_MAX_CUSTOM_SYSEX > 0
        sendCustomSysEx(index, status, ports);
        #endif
      } else if(status==BMC_LIBRARY_EVENT_TYPE_LAYER){// layer

        layer = BMC_GET_BYTE(1, event);
        flags.on(BMC_LIBRARY_FLAG_SET_LAYER);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_CLOCK){// bmp

        bpm = mergeDataBytes(event);
        flags.on(BMC_LIBRARY_FLAG_SET_BPM);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_PIXEL_PROGRAM){// bmp

        pixelProgram = BMC_GET_BYTE(1, event);
        flags.on(BMC_LIBRARY_FLAG_SET_PIXEL_PROGRAM);
        flags.on(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);

      } else if(status==BMC_LIBRARY_EVENT_TYPE_BEATBUDDY_SET_BPM){// clock
#if defined(BMC_USE_BEATBUDDY)
        beatBuddy.tempo(mergeDataBytes(event));
#endif
      } else if(status==BMC_LIBRARY_EVENT_TYPE_BEATBUDDY_CMD){// clock
#if defined(BMC_USE_BEATBUDDY)
        beatBuddy.sendCommand(BMC_GET_BYTE(1, event), BMC_GET_BYTE(2, event));
#endif
      } else if(status==BMC_EVENT_TYPE_CUSTOM){
        uint8_t value = mergeDataBytes(event) & 0xFF;
        if(callback.libraryCustom){
          callback.libraryCustom(value);
        }
      }
    }
  }
  void send(bmcLibrary_t index, bmcLibrary_t index2){
    send(index);
    send(index2);
  }
  void send(bmcLibrary_t index, bmcLibrary_t index2, bmcLibrary_t index3){
    send(index);
    send(index2);
    send(index3);
  }
  bool changeAvailable(){
    return flags.toggleIfTrue(BMC_LIBRARY_FLAG_CHANGE_AVAILABLE);
  }
  bool layerChanged(){
    return flags.toggleIfTrue(BMC_LIBRARY_FLAG_SET_LAYER);
  }
  uint8_t getLayerChange(){
    return layer;
  }
  bool bpmChanged(){
    return flags.toggleIfTrue(BMC_LIBRARY_FLAG_SET_BPM);
  }
  uint16_t getBpmChange(){
    return bpm;
  }
  bool pixelProgramChanged(){
    return flags.toggleIfTrue(BMC_LIBRARY_FLAG_SET_PIXEL_PROGRAM);
  }
  uint8_t getPixelProgramChange(){
    return pixelProgram;
  }

  // these are here to make it easier to access a library message from the outside
  uint32_t getEvent(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    return global.library[n].event;
  }
  // get the status of an event (program,control, etc.)
  uint8_t getStatus(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    uint8_t status = BMC_GET_BYTE(0, global.library[n].event);
    if(status<0xF0){
      // these messages have a channel, so strip it from the status
      return status & 0xF0;
    }
    return status;
  }
  // we always return the channel from 1 to 16 rather than from 0 to 15
  // to match the MIDI Library
  uint8_t getChannel(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    return (BMC_GET_BYTE(0, global.library[n].event) & 0x0F) + 1;
  }
  // since these can only be 7 bits we mask it
  uint8_t getData1(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    return BMC_GET_BYTE(1, global.library[n].event) & 0x7F;
  }
  // these can only be 7 bits, however a value of 128 or higher can be used
  // to toggle a control change
  uint8_t getData2(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    return BMC_GET_BYTE(2, global.library[n].event);
  }
  uint8_t getPort(bmcLibrary_t n){
    if(n>=BMC_MAX_LIBRARY){
      return 0;
    }
    return BMC_GET_BYTE(3, global.library[n].event);
  }
#if BMC_NAME_LEN_LIBRARY > 1
  void getName(bmcLibrary_t n, char* t_string){
    strcpy(t_string, global.library[n].name);
  }
#endif
  void createEvent(uint8_t port, uint8_t status, uint8_t channel, uint8_t data1, uint8_t data2){

  }
private:
  // reference to midi object from BMC
  BMCMidi& midi;
  bmcStoreGlobal& global;
  BMCCallbacks& callback;
  BMCFlags <uint8_t> flags;
  uint8_t layer = 0;
  uint8_t pixelProgram = 0;
  uint16_t bpm = 0;

  uint16_t mergeDataBytes(uint32_t t_event){
    uint16_t b = (t_event>>8) & 0xFFFF;
    return (BMC_GET_BYTE(0, b) & 0x7F) | ((BMC_GET_BYTE(1, b) & 0x7F)<<7);
  }

  #if BMC_MAX_CUSTOM_SYSEX > 0
    BMCCustomSysEx& customSysEx;
    void sendCustomSysEx(bmcLibrary_t index, uint8_t status, uint8_t ports){
      uint8_t mode = BMC_CUSTOM_SYSEX_SEND_A;
      if(status==0xF1){
        mode = BMC_CUSTOM_SYSEX_SEND_B;
      } else if(status==0xF2){
        mode = BMC_CUSTOM_SYSEX_SEND_MERGE;
      }
      customSysEx.send(mode, ports, getData1(index), getData2(index));
    }
  #endif
  #if defined(BMC_USE_BEATBUDDY)
    BMCBeatBuddy& beatBuddy;

  #endif
};

#endif
#endif
