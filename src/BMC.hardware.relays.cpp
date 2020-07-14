/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

// NON-LATCHING RELAYS
#if BMC_MAX_NL_RELAYS > 0
void BMC::setupRelaysNL(){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    uint8_t m = BMC_GET_BYTE(3,globalData.relaysNL[i].event>>1);
    bool momentary = bitRead(m,5);
    bool reversed = bitRead(m,6);
    relaysNL[i].begin(BMCBuildData::getRelayNLPin(i),
                      momentary, reversed);
    // bit 0 of event is initial state
    relaysNL[i].command(globalData.relaysNL[i].event & 0x01);
  }
  assignRelaysNL();
}
void BMC::assignRelaysNL(){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    uint8_t m = BMC_GET_BYTE(3, globalData.relaysNL[i].event>>1);
    relaysNL[i].setMomentary(bitRead(m,5));
    relaysNL[i].setReverse(bitRead(m,6));
    relaysNLTmp[i].type = 255;
    relaysNLTmp[i].data1 = 255;
    uint32_t e = globalData.relaysNL[i].event>>1;
    switch(e & 0xF0){
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_CONTROL_CHANGE:
        relaysNLTmp[i].type = BMC_GET_BYTE(0, e);
        relaysNLTmp[i].data1 = BMC_GET_BYTE(1, e);
        break;
    }
    relaysNL[i].reassign();
  }
}
void BMC::readRelaysNL(){
  uint32_t _relaysNLStates = 0;
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    bitWrite(_relaysNLStates,i,relaysNL[i].update());
    handleRelaysNL(i);
  }
  if(_relaysNLStates!=relayNLStates){
    relayNLStates = _relaysNLStates;
    editor.utilitySendNLRelayActivity(relayNLStates);
  }
}
// triggered on incoming midi messages
void BMC::checkRelaysNLMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2){
  for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
    uint8_t match = relaysNLTmp[i].match2(type, channel, data1);
    // if match = 0 the message doesn't match
    // if match = 1 the message match including data1
    // if match = 2 the message match, it's a program change BUT data1 doesn't match
    // if data1 doesn't match but it's a program then we use that to RESET the relay
    if(match==0){
      continue;
    }
    uint8_t cmd = BMC_GET_BYTE(3, globalData.relaysNL[i].event>>1) & 0x03;
    if((type & 0xF0)==BMC_MIDI_PROGRAM_CHANGE){
      if(cmd==BMC_RELAY_RESET || cmd==BMC_RELAY_SET){
        // if match = 2 the type and channel matched but NOT data1 (program #)
        // in this case we set the relay to the opposite state
        relaysNL[i].command( match==2 ? !cmd : cmd);

      } else if(cmd==BMC_RELAY_TOGGLE){
        // if it's a TOGGLE we only toggle when the actual program change was received
        if(match==1){
          relaysNL[i].toggle();
        }
      }
    } else {
      if(cmd==BMC_RELAY_RESET || cmd==BMC_RELAY_SET){
        relaysNL[i].command((data2>63) ? cmd : !cmd);
      } else if(cmd==BMC_RELAY_TOGGLE){
        if(data2==127){
          relaysNL[i].toggle();
        }
      }
    }
  }
}
void BMC::handleRelaysNL(uint8_t index){
  #if !defined(BMC_FAST_MODE)
  if(index >= BMC_MAX_NL_RELAYS){
    return;
  }
  #endif
  handleRelay(index, false, globalData.relaysNL[index].event);
}
#endif


// LATCHING RELAYS
#if BMC_MAX_L_RELAYS > 0
void BMC::setupRelaysL(){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    uint8_t m = BMC_GET_BYTE(3,globalData.relaysL[i].event>>1);
    bool momentary = bitRead(m, 5);
    bool reversed = bitRead(m, 6);
    relaysL[i].begin(BMCBuildData::getRelayLPinA(i),
                      BMCBuildData::getRelayLPinB(i),
                      momentary, reversed);
     // bit 0 of event is initial state
    relaysL[i].command(globalData.relaysL[i].event & 0x01);
  }
  assignRelaysL();
}
void BMC::assignRelaysL(){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    uint8_t m = BMC_GET_BYTE(3,globalData.relaysL[i].event>>1);
    relaysL[i].setMomentary(bitRead(m,5));
    relaysL[i].setReverse(bitRead(m,6));

    relaysLTmp[i].type = 255;
    relaysLTmp[i].data1 = 255;
    uint32_t e = globalData.relaysL[i].event>>1;
    switch(e & 0xF0){
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_CONTROL_CHANGE:
        relaysLTmp[i].type = BMC_GET_BYTE(0, e);
        relaysLTmp[i].data1 = BMC_GET_BYTE(1, e);
        break;
    }
    relaysL[i].reassign();
  }
}
void BMC::readRelaysL(){
  uint32_t _relaysLStates = 0;
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    bitWrite(_relaysLStates,i,relaysL[i].update());
    handleRelaysL(i);
  }
  if(_relaysLStates!=relayLStates){
    relayLStates = _relaysLStates;
    editor.utilitySendLRelayActivity(relayLStates);
  }
}
// triggered on incoming midi messages
void BMC::checkRelaysLMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2){
  for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
    uint8_t match = relaysLTmp[i].match2(type, channel, data1);
    // if match = 0 the message doesn't match
    // if match = 1 the message match including data1
    // if match = 2 the message match, it's a program change BUT data1 doesn't match
    // if data1 doesn't match but it's a program then we use that to RESET the relay
    if(match==0){
      continue;
    }
    uint8_t cmd = BMC_GET_BYTE(3, globalData.relaysL[i].event>>1) & 0x03;
    if((type & 0xF0)==BMC_MIDI_PROGRAM_CHANGE){
      if(cmd==BMC_RELAY_RESET || cmd==BMC_RELAY_SET){
        // if match = 2 the type and channel matched but NOT data1 (program #)
        // in this case we set the relay to the opposite state
        relaysL[i].command( match==2 ? !cmd : cmd);

      } else if(cmd==BMC_RELAY_TOGGLE){
        // if it's a TOGGLE we only toggle when the actual program change was received
        if(match==1){
          relaysL[i].toggle();
        }
      }
    } else {
      if(cmd==BMC_RELAY_RESET || cmd==BMC_RELAY_SET){
        relaysL[i].command( (data2>63) ? cmd : !cmd );
      } else if(cmd==BMC_RELAY_TOGGLE){
        if(data2==127){
          relaysL[i].toggle();
        }
      }
    }
  }
}
void BMC::handleRelaysL(uint8_t index){
  #if !defined(BMC_FAST_MODE)
  if(index >= BMC_MAX_L_RELAYS){
    return;
  }
  #endif
  handleRelay(index, true, globalData.relaysL[index].event);
}
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  void BMC::handleRelay(uint8_t index, bool latching, uint32_t event){
    event = event >> 1;
    uint8_t eventType = BMC_GET_BYTE(0, event);
    if(BMC_GET_BYTE(0,event)!=BMC_NONE){
      switch(parseMidiEventType(eventType)){
#if BMC_MAX_PRESETS > 0
        case BMC_RELAY_EVENT_TYPE_PRESET:
          if(presets.peekChanged()){
            uint8_t newState = BMC_GET_BYTE(3, event) & 0x03;
            if(BMC_GET_BYTE(1, event) == presets.get()){
              setRelay(index, latching, newState);
            } else if(newState!=BMC_RELAY_TOGGLE){
              setRelay(index, latching, !newState);
            }
          }
          break;
#endif
        case BMC_RELAY_EVENT_TYPE_PAGE:
          if(pageChangedPeek()){
            uint8_t newState = BMC_GET_BYTE(3, event) & 0x03;
            if(BMC_GET_BYTE(1, event) == page){
              setRelay(index, latching, newState);
            } else if(newState!=BMC_RELAY_TOGGLE){
              setRelay(index, latching, !newState);
            }
          }
          break;
        case BMC_MIDI_PROGRAM_CHANGE:
        case BMC_MIDI_CONTROL_CHANGE:
          break;
        case BMC_RELAY_EVENT_TYPE_USER_1:
        case BMC_RELAY_EVENT_TYPE_USER_2:
        case BMC_RELAY_EVENT_TYPE_USER_3:
        case BMC_RELAY_EVENT_TYPE_USER_4:
        case BMC_RELAY_EVENT_TYPE_USER_5:
        case BMC_RELAY_EVENT_TYPE_USER_6:
        case BMC_RELAY_EVENT_TYPE_USER_7:
        case BMC_RELAY_EVENT_TYPE_USER_8:
          if(callback.userEventRelays){
            uint8_t cmd = callback.userEventRelays(parseUserEventType(eventType), event);
            setRelay(index, latching, cmd);
          }
          break;
      }
    }
  }
  void BMC::checkRelaysMidiInput(uint8_t type, uint8_t channel, uint8_t data1, uint8_t data2){
    if(type>=0xF0 || (type!=BMC_MIDI_PROGRAM_CHANGE && type!=BMC_MIDI_CONTROL_CHANGE)){
      return;
    }
    #if BMC_MAX_NL_RELAYS > 0
      checkRelaysNLMidiInput(type, channel, data1, data2);
    #endif
    #if BMC_MAX_L_RELAYS > 0
      checkRelaysLMidiInput(type, channel, data1, data2);
    #endif
  }
  void BMC::checkRelaysMidiInput(BMCMidiMessage m){
    checkRelaysMidiInput(m.getStatus(),m.getChannel()-1,m.getData1(),m.getData2());
  }
  void BMC::setRelay(uint8_t index, bool latching, uint8_t cmd){
    if(!latching){
      #if BMC_MAX_NL_RELAYS > 0
        if(index>=BMC_MAX_NL_RELAYS){
          return;
        }
        relaysNL[index].command(cmd);
      #endif
    } else {
      #if BMC_MAX_L_RELAYS > 0
        if(index>=BMC_MAX_L_RELAYS){
          return;
        }
        relaysL[index].command(cmd);
      #endif
    }
  }
  bool BMC::getRelayState(uint8_t index, bool latching){
    if(!latching){
      #if BMC_MAX_NL_RELAYS > 0
        if(index < BMC_MAX_NL_RELAYS){
          return relaysNL[index].getState();
        }
      #endif
    } else {
      #if BMC_MAX_L_RELAYS > 0
        if(index < BMC_MAX_L_RELAYS){
          return relaysL[index].getState();
        }
      #endif
    }
    return false;
  }

#endif
