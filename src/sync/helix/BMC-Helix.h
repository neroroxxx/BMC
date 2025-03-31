/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_HELIX_H
#define BMC_HELIX_H

#include "utility/BMC-Def.h"

#ifdef BMC_USE_HELIX

class BMCHelix {
public:
  BMCHelix(BMCMidi& t_midi) : midi(t_midi){
    //
  }
  void update(){
    uint8_t cc = midi.getLocalControl(channel,BMC_HELIX_CC_SNAPSHOT);
    if(channel!=0 && cc!=snapshot){
      if(cc<getMaxSnapshots()){
        snapshot = cc;
      }
    }
    //snapshot
  }
  void incoming(BMCMidiMessage m){
    // used to read incoming messages
    if(m.matchSource(port)){
      if(m.isControlChange() && m.matchChannel(channel)){
        if(m.isData1(BMC_HELIX_CC_SNAPSHOT)){
          snapshot = m.getData2();
        }
      }
    }
  }
  void setDeviceId(uint8_t value){
    switch(value & 0x0F){
      case BMC_HELIX_ID:
      case BMC_HELIX_FX_ID:
      case BMC_HELIX_STOMP_ID:
        id = value;
        break;
    }
  }
  void setChannel(uint8_t value){
    channel = value;
  }
  void setPort(uint8_t value){
    port = value;
  }
  void setPortBit(uint8_t value){
    uint8_t x = 0;
    port = bitWrite(x,value,1);
  }
  uint8_t getSnapshot(){
    return snapshot;
  }
  bool isSnapshot(uint8_t t_value){
    return snapshot==t_value;
  }
  void command(uint8_t t_id, uint8_t t_valueA, uint8_t t_valueB){
    switch(t_id){
      case BMC_HELIX_CMD_TAP:
        tap();
        break;
      case BMC_HELIX_CMD_TUNER:
        tuner();
        break;
      case BMC_HELIX_CMD_SNAPSHOT:
        setSnapshot(t_valueA);
        break;
      case BMC_HELIX_CMD_SNAPSHOT_TOGGLE:
        toggleSnapshot(t_valueA, t_valueB);
        break;
      case BMC_HELIX_CMD_SNAPSHOT_INC:
        snapshotScroll(true);
        break;
      case BMC_HELIX_CMD_SNAPSHOT_DEC:
        snapshotScroll(false);
        break;
    }
  }
  void snapshotScroll(bool up){
    //getMaxSnapshots()
    //snapshot
    BMCScroller <uint8_t> scroller(snapshot, 0, getMaxSnapshots()-1);
    setSnapshot(scroller.scroll(1, up, true));
  }
  void snapshotScroll(bool direction, uint8_t min, uint8_t max){
    //getMaxSnapshots()
    //snapshot
    if(max < min || min == max){
      return;
    }
    uint8_t _max = getMaxSnapshots()-1;
    min = constrain(min, 0, _max);
    max = constrain(max, 0, _max);
    BMCScroller <uint8_t> scroller(snapshot, min, max);
    setSnapshot(scroller.scroll(1, direction, true));
  }
  void tap(){
    midi.sendControlChange(port, channel, BMC_HELIX_CC_TAP, 127);
  }
  void tuner(){
    midi.sendControlChange(port, channel, BMC_HELIX_CC_TUNER, 127);
  }
  void setSnapshot(uint8_t t_value){
    if(isDevice(BMC_HELIX_STOMP_ID)){
      if(t_value==8 || t_value==9 || validateSnapshot(t_value)){
        midi.sendControlChange(port, channel, BMC_HELIX_CC_SNAPSHOT, t_value);
        if(t_value==8){
          // next snapshot
          if((snapshot+1)>=getMaxSnapshots()){
            snapshot = 0;
          }
        } else if(t_value==9){
          // prev snapshot
          if(snapshot==0){
            snapshot = getMaxSnapshots()-1;
          }
        } else {
          snapshot = t_value;
        }

      }
    } else {
      if(validateSnapshot(t_value)){
        midi.sendControlChange(port, channel, BMC_HELIX_CC_SNAPSHOT, t_value);
        snapshot = t_value;
      }
    }
  }
  void toggleSnapshot(uint8_t a, uint8_t b){
    if(validateSnapshot(a) && validateSnapshot(b)){
      setSnapshot((snapshot==a)?b:a);
    }
  }
  uint8_t getMaxSnapshots(){
    switch(id){
      case BMC_HELIX_ID:
        return 8;
      case BMC_HELIX_FX_ID:
        return 4;
      case BMC_HELIX_STOMP_ID:
        return 3;
    }
    return 0;
  }

private:
  BMCMidi& midi;
  uint8_t id = 0;
  uint8_t channel = 0;
  uint8_t port = 0;
  uint8_t snapshot = 0;
  uint8_t maxSnapshots = 3;

  bool isDevice(uint8_t t_value){
    return id == t_value;
  }
  bool validateSnapshot(uint8_t t_value){
    return t_value < getMaxSnapshots();
  }
};

#endif

#endif
