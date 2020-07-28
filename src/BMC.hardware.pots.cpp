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
    pots[i].begin(BMCBuildData::getPotPin(i));
  }
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    globalPots[i].begin(BMCBuildData::getGlobalPotPin(i));
  }
  assignGlobalPots();
#endif
}
void BMC::assignPot(BMCPot& pot, bmcStorePot& storeData, bmcStoreGlobalPotCalibration& calibration){
  pot.reassign();
  pot.setCalibration(
    calibration.min,
    calibration.max
  );
  uint32_t event = storeData.event;
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
    pot.assignToeSwitch(storeData.toeSwitch, storeData.toeSwitchFlags);
  #endif
}
#endif

#if BMC_MAX_POTS > 0
void BMC::assignPots(){
  for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
    assignPot(pots[i], store.pages[page].pots[i], globalData.potCalibration[i]);
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

#if BMC_MAX_MUX_IN_ANALOG > 0
    pots[i].setMuxValue(muxInAnalog.getPinValue(pots[i].getMuxPin()));
#endif

#if defined(BMC_USE_POT_TOE_SWITCH)
    if(pots[i].toeSwitchActive()){
      potParseToeSwitch(pots[i].toeSwitchGetEvent(), pots[i].toeSwitchGetState(), store.pages[page].pots[i].ports);
    }
#endif
    if(pots[i].update()){

      uint8_t value = pots[i].getValue();
      handlePot(store.pages[page].pots[i], value);
      // HANDLE CALLBACKS
      uint32_t event = store.pages[page].pots[i].event;
      if(BMC_GET_BYTE(0, event)==BMC_EVENT_TYPE_CUSTOM && callback.potCustomActivity){
        callback.potCustomActivity(i,
                          BMC_GET_BYTE(1, event),
                          BMC_GET_BYTE(2, event),
                          BMC_GET_BYTE(3, event),
                          value);
      } else if(callback.potActivity){
        callback.potActivity(i, value, store.pages[page].pots[i]);
      }
      if(globals.editorConnected()){
        editor.utilitySendPotActivity(i, pots[i].getPosition());
      }
    }
  }
}
void BMC::potParseToeSwitch(uint16_t event, bool on, uint8_t ports){
  BMC_PRINTLN("potParseToeSwitch", on, ports);
  uint8_t type = BMC_GET_BYTE(0, event);
  switch(parseMidiEventType(type)){
    case BMC_POT_TOE_SWITCH_EVENT_TYPE_LIBRARY:
      library.send(BMC_GET_BYTE(1, event));
      break;
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
  pots[n].setMuxValue(muxInAnalog.getPinValue(pots[n].getMuxPin()));
#endif
  return pots[n].getAnalogValue();
}
#endif


#if BMC_MAX_GLOBAL_POTS > 0
// ASSIGN
void BMC::assignGlobalPots(){
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
    assignPot(globalPots[i], globalData.pots[i], globalData.globalPotCalibration[i]);
  }
}
// READ
void BMC::readGlobalPots(){
  if(potCalibration.active()){
    potCalibration.setValue(getGlobalPotAnalogValue(potCalibration.getIndex()));
    return;
  }
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
#if BMC_MAX_MUX_IN_ANALOG > 0
    globalPots[i].setMuxValue(muxInAnalog.getPinValue(globalPots[i].getMuxPin()));
#endif

#if defined(BMC_USE_POT_TOE_SWITCH)
    if(globalPots[i].toeSwitchActive()){
      potParseToeSwitch(globalPots[i].toeSwitchGetEvent(), globalPots[i].toeSwitchGetState(), globalData.pots[i].ports);
    }
#endif

    if(globalPots[i].update()){
      uint8_t value = globalPots[i].getValue();
      handlePot(globalData.pots[i], value);
      // HANDLE CALLBACKS
      uint32_t event = globalData.pots[i].event;
      if(BMC_GET_BYTE(0, event)==BMC_EVENT_TYPE_CUSTOM && callback.globalPotCustomActivity){
        callback.globalPotCustomActivity(i,
                          BMC_GET_BYTE(1, event),
                          BMC_GET_BYTE(2, event),
                          BMC_GET_BYTE(3, event),
                          value);
      } else if(callback.globalPotActivity){
        callback.globalPotActivity(i, value, globalData.pots[i]);
      }
      if(globals.editorConnected()){
        editor.utilitySendGlobalPotActivity(i, globalPots[i].getPosition());
      }
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
  globalPots[n].setMuxValue(muxInAnalog.getPinValue(globalPots[n].getMuxPin()));
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

#ifdef BMC_USE_BEATBUDDY
    case BMC_POT_EVENT_TYPE_BEATBUDDY_CMD:
      if(byteA == BMC_BEATBUDDY_CMD_MIX_VOL){
        beatBuddy.mixVol(map(value, 0, 127, 0, 100));
      } else if(byteA == BMC_BEATBUDDY_CMD_HP_VOL){
        beatBuddy.hpVol(map(value, 0, 127, 0, 100));
      } else if(byteA == BMC_BEATBUDDY_CMD_BPM_INC || BMC_BEATBUDDY_CMD_BPM_DEC){
        beatBuddy.tempoExpression(value);
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
