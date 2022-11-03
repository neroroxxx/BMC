/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
// SETUP
void BMC::setupPots(){
#if BMC_MAX_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_POT, i);
    pots[i].begin(ui.pins[0]);
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_POT, i);
    globalPots[i].begin(ui.pins[0]);
  }
  assignGlobalPots();
#endif
}
void BMC::assignPot(BMCPot& pot, bmcStoreEvent& data, bmcStoreGlobalPotCalibration& calibration){
  pot.reassign();
  pot.setCalibration(
    calibration.min,
    calibration.max
  );
  uint32_t event = data.event;
  pot.setTaper(bitRead(BMC_GET_BYTE(3, event), 7));
  switch(event & 0xF0){
    case BMC_MIDI_CONTROL_CHANGE:
    case BMC_MIDI_PROGRAM_CHANGE:
    case BMC_MIDI_NOTE_ON:
    case BMC_MIDI_NOTE_OFF:
      pot.setRange(
        BMC_GET_BYTE(2, event) & 0x7F,
        BMC_GET_BYTE(3, event) & 0x7F
      );
      break;
  }
  #if defined(BMC_USE_POT_TOE_SWITCH)
    pot.assignToeSwitch(storeData.toeSwitch, data.toeSwitchFlags);
  #endif
}
#endif

#if BMC_MAX_POTS > 0
void BMC::assignPots(){
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    bmcStoreDevice <1, 2>& device = store.pages[page].pots[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent toeData = globals.getDeviceEventType(device.events[1]);
    assignPot(pots[i], data, globalData.potCalibration[i]);
  }
}
// READ
void BMC::readPots(){
  if(potCalibration.active()){
    potCalibration.setValue(getPotAnalogValue(potCalibration.getIndex()));
    return;
  }
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
#if BMC_MAX_AUX_JACKS > 0
    if(!auxJacks.readPot(i)){
      continue;
    }
#endif

    bmcStoreDevice <1, 2>& device = store.pages[page].pots[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent toeData = globals.getDeviceEventType(device.events[1]);

#if BMC_MAX_MUX_IN_ANALOG > 0
    pots[i].setMuxValue(mux.readAnalog(pots[i].getMuxPin()));
#endif

#if defined(BMC_USE_POT_TOE_SWITCH)
    if(pots[i].toeSwitchActive()){
      potParseToeSwitch(pots[i].toeSwitchGetEvent(), pots[i].toeSwitchGetState(), data.ports);
      if(callback.potsToeSwitchState && BMC_GET_BYTE(0, pots[i].toeSwitchGetEvent())>0){
        callback.potsToeSwitchState(i, pots[i].toeSwitchGetState());
      }
    }
#endif
    bool sendData = false;
    if(pots[i].update()){
      sendData = true;
      uint8_t value = pots[i].getValue();
#if defined(BMC_DEBUG)
      if(globals.getPotsDebug()){
        BMC_PRINTLN("Page Pot #",i," > value:",value,"raw:",getPotAnalogValue(i));
      }
#endif
      //handlePot(store.pages[page].pots[i], value);
      processEvent(BMC_DEVICE_GROUP_POT, BMC_DEVICE_ID_POT, i, BMC_EVENT_IO_TYPE_INPUT, device.events[0], value);

      // HANDLE CALLBACKS

      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.potCustomActivity){
        callback.potCustomActivity(i, value);
      } else if(callback.potActivity){
        callback.potActivity(i, value);
      }
    }
    if(globals.editorConnected() && (sendData || editor.isTriggerStates())){
      editor.utilitySendPotActivity(i, pots[i].getPosition());
    }

  }
}
void BMC::potParseToeSwitch(uint16_t event, bool on, uint8_t ports){
  uint8_t type = BMC_GET_BYTE(0, event);
  switch(parseMidiEventType(type)){
#if BMC_MAX_LIBRARY > 0
    case BMC_POT_TOE_SWITCH_EVENT_TYPE_LIBRARY:
      library.send(BMC_GET_BYTE(1, event));
      break;
#endif
    case BMC_MIDI_CONTROL_CHANGE:
    case BMC_MIDI_NOTE_ON:
    case BMC_MIDI_NOTE_OFF:
      midi.send(ports, (uint32_t)((event & 0xFFFF) | ((on?127:0) << 16)));
      streamMidi((type & 0xF0), BMC_TO_MIDI_CHANNEL(type), BMC_GET_BYTE(1, event), (on?127:0));
      break;
    case BMC_MIDI_PROGRAM_CHANGE:
      midi.sendProgramChange(ports, BMC_TO_MIDI_CHANNEL(type), BMC_GET_BYTE(1, event));
      streamMidi((type & 0xF0), BMC_TO_MIDI_CHANNEL(type), BMC_GET_BYTE(1, event));
      break;
  }
}
// CALIBRATION
void BMC::potCalibrationToggle(uint8_t n){
  if(!potCalibration.active() && n < BMC_MAX_POTS){
    potCalibration.toggle(n);
  } else {
    potCalibration.cancel();
  }
}
uint16_t BMC::getPotAnalogValue(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
  pots[n].setMuxValue(mux.readAnalog(pots[n].getMuxPin()));
#endif
  return pots[n].getAnalogValue();
}
#endif


#if BMC_MAX_GLOBAL_POTS > 0
// ASSIGN
void BMC::assignGlobalPots(){
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    bmcStoreDevice <1, 2>& device = store.global.pots[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent toeData = globals.getDeviceEventType(device.events[1]);
    assignPot(globalPots[i], data, globalData.globalPotCalibration[i]);
  }
}
// READ
void BMC::readGlobalPots(){
  if(potCalibration.active()){
    potCalibration.setValue(getGlobalPotAnalogValue(potCalibration.getIndex()));


#if defined(BMC_DEBUG)
  if(globals.getPotsDebug()){
    BMC_PRINTLN("potCalibration.getIndex() >> ",getGlobalPotAnalogValue(potCalibration.getIndex()));
  }
#endif

    return;
  }


  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
#if BMC_MAX_MUX_IN_ANALOG > 0
    globalPots[i].setMuxValue(mux.readAnalog(globalPots[i].getMuxPin()));
#endif

    bmcStoreDevice <1, 2>& device = store.global.pots[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent toeData = globals.getDeviceEventType(device.events[1]);

#if defined(BMC_USE_POT_TOE_SWITCH)
    if(globalPots[i].toeSwitchActive()){
      potParseToeSwitch(globalPots[i].toeSwitchGetEvent(), globalPots[i].toeSwitchGetState(), globalData.pots[i].ports);
      if(callback.globalPotsToeSwitchState && BMC_GET_BYTE(0, globalPots[i].toeSwitchGetEvent())>0){
        callback.globalPotsToeSwitchState(i, globalPots[i].toeSwitchGetState());
      }
    }
#endif
    bool sendData = false;
    if(globalPots[i].update()){
      sendData = true;
      uint8_t value = globalPots[i].getValue();
#if defined(BMC_DEBUG)
      if(globals.getPotsDebug()){
        BMC_PRINTLN("Global Pot #",i," > value:",value,"raw:",getGlobalPotAnalogValue(i));
      }
#endif
      processEvent(BMC_DEVICE_GROUP_POT, BMC_DEVICE_ID_GLOBAL_POT, i, BMC_EVENT_IO_TYPE_INPUT, device.events[0], value);
      // HANDLE CALLBACKS

      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.globalPotCustomActivity){
        callback.globalPotCustomActivity(i, value);
      } else if(callback.globalPotActivity){
        callback.globalPotActivity(i, value);
      }

    }
    if(globals.editorConnected() && (sendData || editor.isTriggerStates())){
      editor.utilitySendGlobalPotActivity(i, globalPots[i].getPosition());
    }
  }
}
// CALIBRATION
void BMC::globalPotCalibrationToggle(uint8_t n){
  if(!potCalibration.active() && n < BMC_MAX_GLOBAL_POTS){
    potCalibration.toggle(n);
  } else {
    potCalibration.cancel();
  }
}
uint16_t BMC::getGlobalPotAnalogValue(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
  globalPots[n].setMuxValue(mux.readAnalog(globalPots[n].getMuxPin()));
#endif
  return globalPots[n].getAnalogValue();
}
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
void BMC::handlePot(bmcStorePot& data, uint8_t value){
  uint8_t type = BMC_GET_BYTE(0, data.event);
  if(type == BMC_NONE){
    return;
  }
  uint8_t byteA = BMC_GET_BYTE(1, data.event);
  switch(parseMidiEventType(type)){
    case BMC_MIDI_CONTROL_CHANGE:
    case BMC_MIDI_NOTE_ON:
    case BMC_MIDI_NOTE_OFF:
      midi.send(data.ports, ((data.event & 0xFFFF) | value << 16));
      streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA, value);

//#if defined(BMC_DEBUG)
//      if(globals.getPotsDebug()){
//        BMC_PRINTLN("Pot Sending CC#",byteA,"ch:",BMC_TO_MIDI_CHANNEL(type),"value:", value);
//      }
//#endif

      break;
    case BMC_MIDI_PROGRAM_CHANGE:
      midi.sendProgramChange(data.ports, BMC_TO_MIDI_CHANNEL(type), value);
      streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), value);
      break;
    case BMC_POT_EVENT_TYPE_CLOCK:
      {
        uint16_t min = (data.event >> 8) & 0x1FF;
        uint16_t max = (data.event >> 17) & 0x1FF;
        midiClock.setBpm(map(value, 0, 127, min, max));
      }
      break;
    case BMC_POT_EVENT_TYPE_PITCH:
      {
        uint8_t channel = (byteA&0x0F)+1;
        int8_t pitch = midi.getLocalPitch(channel);
        if(value<59){
          // pitch down
          uint16_t newPitch = map(value, 0, 58, -8192, -1);
          midi.sendPitchBend(data.ports, channel, newPitch);
        } else if(value>68){
          // pitch up
          uint16_t newPitch = map(value, 69, 127, 1, 8191);
          midi.sendPitchBend(data.ports, channel, newPitch);
        } else if(pitch!=0){
          // center
          midi.sendPitchBend(data.ports, channel, 0);
          midi.setLocalPitch(channel, 0);
        }
      }
      break;
    case BMC_POT_EVENT_TYPE_PITCH_UP:
      {
        uint8_t channel = (byteA&0x0F)+1;
        // leave the first 10 values of the pot as a buffer for a flat pitch
        if(value>9){
          // move pitch up
          uint16_t newPitch = map(value, 10, 127, 1, 8191);
          midi.sendPitchBend(data.ports, channel, newPitch);
        } else if(midi.getLocalPitch(channel)!=0){
          midi.sendPitchBend(data.ports, channel, 0);
          midi.setLocalPitch(channel, 0);
        }
      }
      break;
    case BMC_POT_EVENT_TYPE_PITCH_DOWN:
      {
        uint8_t channel = (byteA&0x0F)+1;
        // leave the first 10 values of the pot as a buffer for a flat pitch
        if(value>9){
          // move pitch up
          int16_t newPitch = map(value, 10, 127, -1, -8192);
          midi.sendPitchBend(data.ports, channel, newPitch);
        } else if(midi.getLocalPitch(channel)!=0){
          midi.sendPitchBend(data.ports, channel, 0);
          midi.setLocalPitch(channel, 0);
        }
      }
      break;

#ifdef BMC_USE_BEATBUDDY
    case BMC_POT_EVENT_TYPE_BEATBUDDY_CMD:
      if(byteA == BMC_BEATBUDDY_CMD_MIX_VOL){
        sync.beatBuddy.mixVol(map(value, 0, 127, 0, 100));
      } else if(byteA == BMC_BEATBUDDY_CMD_HP_VOL){
        sync.beatBuddy.hpVol(map(value, 0, 127, 0, 100));
      } else if(byteA == BMC_BEATBUDDY_CMD_BPM_INC || BMC_BEATBUDDY_CMD_BPM_DEC){
        sync.beatBuddy.tempoExpression(value);
      }
      break;
#endif

#ifdef BMC_USE_CLICK_TRACK
    case BMC_POT_EVENT_TYPE_CLICK_TRACK_FREQ:
      {
        uint8_t byteB = BMC_GET_BYTE(2, data.event);
        uint8_t mapped = map(value, 0, 127, byteA, byteB);
        midiClock.clickTrackSetFrequency(map((mapped&0x07), 0, 7, 500, 4000));
      }
      break;
    case BMC_POT_EVENT_TYPE_CLICK_TRACK_LEVEL:
      {
        uint8_t byteB = BMC_GET_BYTE(2, data.event);
        midiClock.clickTrackSetLevel(map(value, 0, 127, byteA, byteB));
      }
      break;
#endif
    case BMC_POT_EVENT_TYPE_USER_1:
    case BMC_POT_EVENT_TYPE_USER_2:
    case BMC_POT_EVENT_TYPE_USER_3:
    case BMC_POT_EVENT_TYPE_USER_4:
    case BMC_POT_EVENT_TYPE_USER_5:
    case BMC_POT_EVENT_TYPE_USER_6:
    case BMC_POT_EVENT_TYPE_USER_7:
    case BMC_POT_EVENT_TYPE_USER_8:
      if(callback.userEventPots){
        callback.userEventPots(parseUserEventType(type), data.event, data.ports, value);
      }
      break;
  }
}
#endif
