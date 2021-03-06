/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include "editor/BMC-Editor.h"

void BMCEditor::utilityCommand(){
  dataForBMC.reset();
  if(dataForBMC.set(isWriteMessage(), incoming)){
    flags.on(BMC_EDITOR_FLAG_DATA_FOR_BMC_AVAILABLE);
  }
}
// on all the following functions onlyIfConnected is used by
// BMC when buttons are being read or leds have changed states.
// all those functions will notify the editor but with onlyIfConnected set to "true"
// This is so that these are skipped when the editor is not connected, however
// if another BMC build is connected to this BMC build they can request data
// from each other thru other means, those requests would have onlyIfConnected set to "false"
// Additionally BMC can enable/disabled editor real time feedback which turns leds on/off
// lights up buttons when pressed etc on the editor app.
// this option is not store in EEPROM instead is stored in the editor app local settings
// and the editor app will send it as needed. This is so that the PERFORMANCE mode
// don't get these messages making the MIDI traffic less.
#if BMC_MAX_BUTTONS > 32
void BMCEditor::utilitySendButtonActivity(uint32_t states,
                                          uint32_t states2,
                                          bool onlyIfConnected){
#else
void BMCEditor::utilitySendButtonActivity(uint32_t states,
                                          bool onlyIfConnected){
#endif
#if BMC_MAX_BUTTONS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
  BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_BUTTON
    );
    buff.appendToSysEx32Bits(states);
#if BMC_MAX_BUTTONS > 32
    buff.appendToSysEx32Bits(states2);
#endif
    // don't show midi activity
    sendToEditor(buff,true,false);
  }
#endif
}
void BMCEditor::utilitySendGlobalButtonActivity(uint32_t states, bool onlyIfConnected){
#if BMC_MAX_GLOBAL_BUTTONS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
  BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_GLOBAL_BUTTON
    );
    buff.appendToSysEx32Bits(states);
    // don't show midi activity
    sendToEditor(buff,true,false);
  }
#endif
}

void BMCEditor::utilitySendLedActivity(uint32_t data, bool onlyIfConnected){
#if BMC_MAX_LEDS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_LED
    );
    buff.appendToSysEx32Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendAuxJackActivity(uint8_t data, bool onlyIfConnected){
#if BMC_MAX_AUX_JACKS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_AUX_JACK
    );
    buff.appendToSysEx7Bits(data);
    sendToEditor(buff, true, false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendFasState(uint8_t data, bool onlyIfConnected){
#if defined(BMC_USE_FAS)
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_FAS_STATE
    );
    buff.appendToSysEx7Bits(data);
    sendToEditor(buff, true, false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendNLRelayActivity(uint16_t data, bool onlyIfConnected){
#if BMC_MAX_NL_RELAYS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_NL_RELAY
    );
    buff.appendToSysEx16Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendLRelayActivity(uint16_t data, bool onlyIfConnected){
#if BMC_MAX_L_RELAYS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_L_RELAY
    );
    buff.appendToSysEx16Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}

void BMCEditor::utilitySendPixelActivity(uint32_t data,
                                             bool onlyIfConnected){
#if BMC_MAX_PIXELS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_PIXEL
    );
    buff.appendToSysEx32Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendRgbPixelActivity(uint32_t red, uint32_t green, uint32_t blue,
                                             bool onlyIfConnected){
#if BMC_MAX_RGB_PIXELS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_RGB_PIXEL
    );
    buff.appendToSysEx32Bits(red);
    buff.appendToSysEx32Bits(green);
    buff.appendToSysEx32Bits(blue);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}

void BMCEditor::utilitySendGlobalLedActivity(uint16_t data,
                                             bool onlyIfConnected){
#if BMC_MAX_GLOBAL_LEDS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_GLOBAL_LED
    );
    buff.appendToSysEx16Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendPwmLedActivity(uint32_t data, bool onlyIfConnected){
#if BMC_MAX_PWM_LEDS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_PWM_LED
    );
    buff.appendToSysEx32Bits(data);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendPotActivity(uint8_t index, uint8_t value,
                                       bool onlyIfConnected){
#if BMC_MAX_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing() && index < BMC_MAX_POTS){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_POT);
    buff.appendToSysEx7Bits(index);
    buff.appendToSysEx7Bits(value);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendPotsActivity(uint8_t *values, uint8_t length,
                                        bool onlyIfConnected){
#if BMC_MAX_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_POTS
    );
    buff.appendToSysEx7Bits(length);
    for(uint8_t i = 0; i < length; i++){
      buff.appendToSysEx7Bits(values[i]);
    }
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}

void BMCEditor::utilitySendGlobalPotActivity(uint8_t index, uint8_t value,
                                       bool onlyIfConnected){
#if BMC_MAX_GLOBAL_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing() && index < BMC_MAX_GLOBAL_POTS){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_GLOBAL_POT);
    buff.appendToSysEx7Bits(index);
    buff.appendToSysEx7Bits(value);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendGlobalPotsActivity(uint8_t *values, uint8_t length,
                                        bool onlyIfConnected){
#if BMC_MAX_GLOBAL_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing()){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_GLOBAL_POTS
    );
    buff.appendToSysEx7Bits(length);
    for(uint8_t i = 0; i < length; i++){
      buff.appendToSysEx7Bits(values[i]);
    }
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendEncoderActivity(uint8_t index, bool increased,
                                           bool onlyIfConnected){
#if BMC_MAX_ENCODERS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing() && index < BMC_MAX_ENCODERS){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_ENCODER
    );
    buff.appendToSysEx7Bits(index);
    buff.appendToSysEx7Bits(increased);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}

void BMCEditor::utilitySendGlobalEncoderActivity(uint8_t index, bool increased,
                                           bool onlyIfConnected){
#if BMC_MAX_GLOBAL_ENCODERS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  if(!connectionOngoing() && index < BMC_MAX_GLOBAL_ENCODERS){
    BMCEditorMidiFlags flag;
    flag.setWrite(true);
    BMCMidiMessage buff;
    buff.prepareEditorMessage(
      port, deviceId,
      BMC_GLOBALF_UTILITY, flag,
      BMC_UTILF_GLOBAL_ENCODER
    );
    buff.appendToSysEx7Bits(index);
    buff.appendToSysEx7Bits(increased);
    sendToEditor(buff,true,false); // don't show midi activity
  }
#endif
}
void BMCEditor::utilitySendPreset(bmcPreset_t presetNumber,
                                  bool onlyIfConnected){
#if BMC_MAX_PRESETS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  if(presetNumber >= BMC_MAX_PRESETS){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  BMCEditorMidiFlags flag;
  flag.setWrite(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_UTILITY, flag,
    BMC_UTILF_PRESET
  );
  buff.appendToSysEx8Bits(presetNumber);

  #if BMC_NAME_LEN_PRESETS > 1
    bmcStoreGlobalPresets& item = store.global.presets[presetNumber];
    buff.appendToSysEx7Bits(BMC_NAME_LEN_PRESETS);
    buff.appendCharArrayToSysEx(item.name, BMC_NAME_LEN_PRESETS);
  #endif
  sendToEditor(buff,true,false); // don't show midi activity
#endif
}

void BMCEditor::utilitySendClickTrackData(uint16_t freq, uint8_t level,
                                          uint8_t state, bool onlyIfConnected){
#ifdef BMC_USE_CLICK_TRACK
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  BMCEditorMidiFlags flag;
  flag.setWrite(true);
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_UTILITY, flag,
    BMC_UTILF_CLICK_TRACK
  );
  buff.appendToSysEx16Bits(freq);
  buff.appendToSysEx7Bits(level);
  buff.appendToSysEx7Bits(state);
  sendToEditor(buff,true,false); // don't show midi activity
#endif
}
void BMCEditor::utilitySendPotCalibrationStatus(bool status, bool canceled,
                                                bool onlyIfConnected){
#if BMC_MAX_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_UTILITY, 0,
    BMC_UTILF_POT_CALIBRATION_STATUS
  );
  buff.appendToSysEx7Bits(status?1:0);
  buff.appendToSysEx7Bits(canceled?1:0);
  // don't show midi activity
  sendToEditor(buff,true,false);
#endif
}
void BMCEditor::utilitySendGlobalPotCalibrationStatus(bool status, bool canceled,
                                                bool onlyIfConnected){
#if BMC_MAX_GLOBAL_POTS > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_UTILITY, 0,
    BMC_UTILF_GLOBAL_POT_CALIBRATION_STATUS
  );
  buff.appendToSysEx7Bits(status?1:0);
  buff.appendToSysEx7Bits(canceled?1:0);
  // don't show midi activity
  sendToEditor(buff,true,false);
#endif
}
// send a message to the editor with the sketchbytes
// used when sketch bytes are updated by the Sketch API
void BMCEditor::utilitySendSketchBytes(bool onlyIfConnected){
#if BMC_MAX_SKETCH_BYTES > 0
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  // if editor feedback is disabled...
  if(onlyIfConnected && !flags.read(BMC_EDITOR_FLAG_EDITOR_FEEDBACK)){
    return;
  }
  BMCMidiMessage buff;
  buff.prepareEditorMessage(
    port, deviceId,
    BMC_GLOBALF_UTILITY, 0,
    BMC_UTILF_SKETCH_BYTES
  );
  buff.appendToSysEx7Bits(BMC_MAX_SKETCH_BYTES);
  for(uint8_t i = 0 ; i < BMC_MAX_SKETCH_BYTES ; i++){
    buff.appendToSysEx8Bits(store.global.sketchBytes[i]);
  }
  // don't show midi activity
  sendToEditor(buff,true,false);
#endif
}
