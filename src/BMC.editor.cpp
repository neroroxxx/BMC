/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
void BMC::editorRead(){
  // read the incoming midi messages to see
  // if it's a message for the editor
  if(editor.read()){
    // editor message was received
    if(editor.readyToReload()){
      // reassign all objects to new data
      assignStoreData();
    } else if(editor.dataForBMCAvailable()){
      controlReceived();
    }
  }
  // check if editor is now disconnceted
  if(editor.connectionHasChanged()){
    if(!globals.editorConnected()){
      // put here anything that should be done if the editor was disconnected
      #if BMC_MAX_POTS > 0
        // if pot calibration is ongoing after disconnected, cancel it
        if(potCalibration.active()){
          potCalibrationToggle();
        }
      #endif
      #if BMC_MAX_GLOBAL_POTS > 0
        // if pot calibration is ongoing after disconnected, cancel it
        if(potCalibration.active()){
          globalPotCalibrationToggle();
        }
      #endif
    }
    if(callback.editorConnection){
      callback.editorConnection(globals.editorConnected());
    }
  }
}
void BMC::assignStoreData(){
  // The editor has updated data in EEPROM so we need to update all Hardware and Settings
  BMC_PRINTLN("editor.readyToReload()");
  setPage(editor.getPage(), true);

  #if BMC_MAX_GLOBAL_BUTTONS > 0
    globalButtonStates = ~globalButtonStates;
    // BMC.hardware.buttons
    assignGlobalButtons();
  #endif

  #if BMC_MAX_GLOBAL_POTS > 0
    // BMC.hardware.pots
    assignGlobalPots();
  #endif

  #if BMC_MAX_GLOBAL_ENCODERS > 0
    // BMC.hardware.encoders
    assignGlobalEncoders();
  #endif

  #if BMC_MAX_GLOBAL_LEDS > 0
    globalLedStates = ~globalLedStates;
    // BMC.hardware.leds
    assignGlobalLeds();
  #endif

  #if BMC_MAX_NL_RELAYS > 0
    // BMC.relays.leds
    assignRelaysNL();
  #endif

  #if BMC_MAX_L_RELAYS > 0
    // BMC.relays.leds
    assignRelaysL();
  #endif

  if(callback.storeUpdated){
    callback.storeUpdated();
  }
}
void BMC::assignSettings(){
  // Set the global settings
  midiClock.setMaster(settings.getMasterClock());
  midiActiveSense.setOutputPorts(settings.getListenerPorts());
  midi.setListenerEnable(settings.getIncomingListenerEnabled());
  midi.setListenerChannel(settings.getListenerChannel());
  midi.setListenerPorts(settings.getListenerPorts());
  midi.setClockListenerPort(settings.getClockInputPortBit());
  editor.setChainingPort(settings.getChainingPort());

  valueTyper.setOffset(settings.getTyperOffSet());

  midi.setRouting(BMC_USB, settings.getUsbRouting());
#ifdef BMC_MIDI_SERIAL_A_ENABLED
  midi.setRouting(BMC_SERIAL_A, settings.getSerialARouting());
#endif
#ifdef BMC_MIDI_SERIAL_B_ENABLED
  midi.setRouting(BMC_SERIAL_B, settings.getSerialBRouting());
#endif
#ifdef BMC_MIDI_SERIAL_C_ENABLED
  midi.setRouting(BMC_SERIAL_C, settings.getSerialCRouting());
#endif
#ifdef BMC_MIDI_SERIAL_D_ENABLED
  midi.setRouting(BMC_SERIAL_D, settings.getSerialDRouting());
#endif

#ifdef BMC_USB_HOST_ENABLED
  midi.setRouting(BMC_HOST, settings.getHostRouting());
#endif

#ifdef BMC_USB_BLE_ENABLED
  midi.setRouting(BMC_BLE, settings.getBleRouting());
#endif

#ifdef BMC_USE_BEATBUDDY
  beatBuddy.enableSync(settings.getBeatBuddySync());
  beatBuddy.setChannel(settings.getBeatBuddyChannel()+1);
  beatBuddy.setPortBit(settings.getBeatBuddyPort());
#endif

#ifdef BMC_USE_HELIX
  helix.setDeviceId(settings.getHelixId());
  helix.setChannel(settings.getHelixChannel()+1);
  helix.setPortBit(settings.getHelixPort());
#endif

#if BMC_MAX_AUX_JACKS > 0
  for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
    // update with data from settings
    bool useAsExpression = settings.getAuxJackMode(i);
    auxJacks.setMode(i, useAsExpression);
    if(!useAsExpression){
      // get analog pin and enable btn Index
      // set enable btn index to analog pin
      uint8_t potPin = auxJacks.getPotPin(i);
      uint8_t btnEnIndex = auxJacks.getBtnEnIndex(i);
      buttons[btnEnIndex].changePin(potPin);
    }
  }
#endif

  #if BMC_MAX_TRIGGERS > 0
    if(editor.triggersUpdated()){
      triggers.buildListeners();
    }
  #endif

  #if BMC_MAX_BUTTONS > 32
    buttonStates = ~buttonStates;
    buttonStates2 = ~buttonStates2;
  #elif BMC_MAX_BUTTONS > 0
    buttonStates = ~buttonStates;
  #endif

  #if BMC_MAX_LEDS > 0
    ledStates = ~ledStates;
  #endif

  #if BMC_MAX_PWM_LEDS > 0
    pwmLedStates = ~pwmLedStates;
  #endif

  #if BMC_MAX_PIXELS > 0
    pixelStates = ~pixelStates;
  #endif

  #if BMC_MAX_RGB_PIXELS > 0
    rgbPixelStatesR = ~rgbPixelStatesR;
    rgbPixelStatesG = ~rgbPixelStatesG;
    rgbPixelStatesB = ~rgbPixelStatesB;
  #endif

  #if BMC_MAX_GLOBAL_BUTTONS > 0
    globalButtonStates = ~globalButtonStates;
  #endif

  #if BMC_MAX_GLOBAL_LEDS > 0
    globalLedStates = ~globalLedStates;
  #endif

  #if BMC_MAX_NL_RELAYS > 0
    relayNLStates = ~relayNLStates;
  #endif

  #if BMC_MAX_L_RELAYS > 0
    relayLStates = ~relayLStates;
  #endif

  #if BMC_MAX_AUX_JACKS > 0
    auxJacksStates = ~auxJacksStates;
  #endif
}
void BMC::controlReceived(){
  switch(editor.getCtrlGroup()){
    case BMC_CTRL_GROUP_HARDWARE:
      ctrlHardware();
      break;

#if BMC_MAX_PRESETS > 0
    case BMC_CTRL_GROUP_PRESET:
      ctrlPreset();
      break;
#endif

#ifdef BMC_USE_CLICK_TRACK
    case BMC_CTRL_GROUP_CLICK_TRACK:
      ctrlClickTrack();
      break;
#endif
  }
}
void BMC::ctrlHardware(){
  switch(editor.getCtrlParameter()){
    case BMC_CTRL_PAGE_GET:
      editor.pageSendChangeMessage(false);
      break;
    case BMC_CTRL_PAGE_SET:
      if(editor.getCtrlWrite() && editor.getCtrlValue()<BMC_MAX_PAGES){
        setPage(editor.getCtrlValue() & 0xFF);
      }
      editor.pageSendChangeMessage(false);
      break;

#if BMC_MAX_BUTTONS > 0
    case BMC_CTRL_BUTTON_TRIGGER_TOGGLE:
      if(editor.getCtrlValue() < BMC_MAX_BUTTONS){
        buttons[editor.getCtrlValue()].triggerToggle();
      }
      break;
    case BMC_CTRL_BUTTON_TRIGGER_PRESS:
      if(editor.getCtrlValue() < BMC_MAX_BUTTONS){
        buttons[editor.getCtrlValue()].triggerPress();
      }
      break;
    case BMC_CTRL_BUTTON_TRIGGER_RELEASE:
      if(editor.getCtrlValue()  <BMC_MAX_BUTTONS){
        buttons[editor.getCtrlValue()].triggerRelease();
      }
      break;
#endif

#if BMC_MAX_LEDS > 0
    case BMC_CTRL_LED_STATES:
      ledStates = ~ledStates;
      break;
    case BMC_CTRL_LED_TEST:
      if(editor.getCtrlValue() < BMC_MAX_LEDS){
        leds[(editor.getCtrlValue() & 0xFF)].test();
      }
      break;
#endif

#if BMC_MAX_NL_RELAYS > 0
    case BMC_CTRL_NL_RELAYS_GET:
      relayNLStates = ~relayNLStates;
      break;
    case BMC_CTRL_NL_RELAYS_OPEN:
      if(editor.getCtrlValue() < BMC_MAX_NL_RELAYS){
        relaysNL[(editor.getCtrlValue() & 0xFF)].off();
      }
      break;
    case BMC_CTRL_NL_RELAYS_CLOSE:
      if(editor.getCtrlValue() < BMC_MAX_NL_RELAYS){
        relaysNL[(editor.getCtrlValue() & 0xFF)].on();
      }
      break;
    case BMC_CTRL_NL_RELAYS_TOGGLE:
      if(editor.getCtrlValue() < BMC_MAX_NL_RELAYS){
        relaysNL[(editor.getCtrlValue() & 0xFF)].toggle();
      }
      break;
#endif
#if BMC_MAX_L_RELAYS > 0
    case BMC_CTRL_L_RELAYS_GET:
      relayLStates = ~relayLStates;
      break;
    case BMC_CTRL_L_RELAYS_SET:
      if(editor.getCtrlValue() < BMC_MAX_L_RELAYS){
        relaysL[(editor.getCtrlValue() & 0xFF)].off();
      }
      break;
    case BMC_CTRL_L_RELAYS_RESET:
      if(editor.getCtrlValue() < BMC_MAX_L_RELAYS){
        relaysL[(editor.getCtrlValue() & 0xFF)].on();
      }
      break;
    case BMC_CTRL_L_RELAYS_TOGGLE:
      if(editor.getCtrlValue() < BMC_MAX_L_RELAYS){
        relaysL[(editor.getCtrlValue() & 0xFF)].toggle();
      }
      break;
#endif

#if BMC_MAX_AUX_JACKS > 0
    case BMC_CTRL_AUX_JACK_STATES:
      editor.utilitySendAuxJackActivity(auxJacksStates);
      break;
#endif

#if defined(BMC_USE_FAS)
    case BMC_CTRL_FAS_STATE:
      editor.utilitySendFasState(fas.getConnectedDeviceId());
      break;
#endif

#if BMC_MAX_PWM_LEDS > 0
    case BMC_CTRL_PWM_LED_STATES:
      pwmLedStates = ~pwmLedStates;
      break;
    case BMC_CTRL_PWM_LED_TEST:
      BMC_PRINTLN("Test Pwm Led",editor.getCtrlValue());
      if(editor.getCtrlValue() < BMC_MAX_PWM_LEDS){
        pwmLeds[(editor.getCtrlValue() & 0xFF)].test();
      }
      break;
#endif

#if BMC_MAX_PIXELS > 0
    case BMC_CTRL_PIXEL_STATES:
      pixelStates = ~pixelStates;
      break;
    case BMC_CTRL_PIXEL_TEST:
      BMC_PRINTLN("Test Pixel",editor.getCtrlValue());
      if(editor.getCtrlValue() < BMC_MAX_PIXELS){
        pixels.test((editor.getCtrlValue() & 0xFF));
      }
      break;
#endif

#if BMC_MAX_RGB_PIXELS > 0
    case BMC_CTRL_RGB_PIXEL_STATES:
      rgbPixelStatesR = ~rgbPixelStatesR;
      rgbPixelStatesG = ~rgbPixelStatesG;
      rgbPixelStatesB = ~rgbPixelStatesB;
      break;
    case BMC_CTRL_RGB_PIXEL_TEST:
      BMC_PRINTLN("Test RGB Pixel",editor.getCtrlValue());
      if(editor.getCtrlValue() < BMC_MAX_RGB_PIXELS){
        pixels.testRgb((editor.getCtrlValue() & 0xFF));
      }
      break;
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
    case BMC_CTRL_GLOBAL_LED_STATES:
      globalLedStates = ~globalLedStates;
      break;
    case BMC_CTRL_GLOBAL_LED_TEST:
      if(editor.getCtrlValue() < BMC_MAX_GLOBAL_LEDS){
        globalLeds[(editor.getCtrlValue() & 0xFF)].test();
      }
      break;
#endif

#if BMC_MAX_POTS > 0
    case BMC_CTRL_POT_STATES:
      {
        uint8_t values[BMC_MAX_POTS];
        for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
          values[i] = pots[i].getValue();
        }
        editor.utilitySendPotsActivity(values, BMC_MAX_POTS, false);
      }
      break;

    case BMC_CTRL_POT_CALIBRATION:
      {
        BMC_PRINTLN("BMCCtrl::hardware::PotCalibration",editor.getCtrlValue());
        bool canceled = false;
        if(potCalibration.active()){

          if(potCalibration.getMin() < potCalibration.getMax()){
            editor.setPotCalibration(
                potCalibration.getIndex(),
                potCalibration.getMin(),
                potCalibration.getMax()
              );
            BMC_PRINTLN("Pot Calibration Set", potCalibration.getMin(), potCalibration.getMax());
          } else {
            canceled = true;
          }
        }
        potCalibrationToggle(editor.getCtrlValue() & 0xFF);
        editor.utilitySendPotCalibrationStatus(potCalibration.active(), canceled);
      }
      break;

    case BMC_CTRL_POT_CALIBRATION_CANCEL:
      if(potCalibration.active()){
        potCalibrationToggle();
      }
      editor.utilitySendPotCalibrationStatus(potCalibration.active(),true);
      break;
#endif

#if BMC_MAX_GLOBAL_POTS > 0
    case BMC_CTRL_GLOBAL_POT_STATES:
      {
        uint8_t values[BMC_MAX_GLOBAL_POTS];
        for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
          values[i] = globalPots[i].getValue();
        }
        editor.utilitySendGlobalPotsActivity(values, BMC_MAX_GLOBAL_POTS, false);
      }
      break;

    case BMC_CTRL_GLOBAL_POT_CALIBRATION:
      {
        BMC_PRINTLN("BMCCtrl::hardware::GlobalPotCalibration",editor.getCtrlValue());
        bool canceled = false;
        if(potCalibration.active()){
          if(potCalibration.getMin() < potCalibration.getMax()){
            editor.setGlobalPotCalibration(
                potCalibration.getIndex(),
                potCalibration.getMin(),
                potCalibration.getMax()
              );
            BMC_PRINTLN("Global Pot Calibration Set", potCalibration.getMin(), potCalibration.getMax());
          } else {
            canceled = true;
          }
        }
        globalPotCalibrationToggle(editor.getCtrlValue() & 0xFF);
        editor.utilitySendGlobalPotCalibrationStatus(potCalibration.active(), canceled);
      }
      break;

    case BMC_CTRL_GLOBAL_POT_CALIBRATION_CANCEL:
      if(potCalibration.active()){
        globalPotCalibrationToggle();
      }
      editor.utilitySendGlobalPotCalibrationStatus(potCalibration.active(),true);
      break;
#endif

  }
}

#if BMC_MAX_PRESETS > 0
void BMC::ctrlPreset(){
  switch(editor.getCtrlParameter()){
    case BMC_CTRL_PRESET_GET:
      editor.utilitySendPreset(presets.get(), false);
      break;
    case BMC_CTRL_PRESET_SET:
      if(editor.getCtrlWrite() && editor.getCtrlValue() < BMC_MAX_PRESETS){
        presets.set((bmcPreset_t) editor.getCtrlValue());
        // since this is a request that can be sent not just by the editor app
        // we need to send a notification of this change right away
        // so we send it out (second parameter false means it should be sent
        // even if we're not connected to the editor app)
        // we also call presets.presetChanged() to clear that flag
        if(!globals.editorConnected()){
          editor.utilitySendPreset(presets.get(), false);
        }
      }
      break;
  }
}
#endif

#ifdef BMC_USE_CLICK_TRACK
void BMC::ctrlClickTrack(){
  BMC_PRINTLN("ctrlClickTrack()");
  switch(editor.getCtrlParameter()){
    case BMC_CTRL_CLICK_TRACK_ALL:
      if(editor.getCtrlWrite()){
        midiClock.clickTrackSetFrequency(editor.getCtrlValue() & 0xFFFF);
        midiClock.clickTrackSetLevel((editor.getCtrlValue() >> 16) & 0xFF);
        if(((editor.getCtrlValue() >> 24) & 0x01) == 1){
          midiClock.clickTrackMute();
        } else {
          midiClock.clickTrackUnmute();
        }
      }
      flags.on(BMC_FLAGS_CLICK_TRACK_RESPOND);
      break;
    case BMC_CTRL_CLICK_TRACK_FREQUENCY:
      midiClock.clickTrackSetFrequency(editor.getCtrlValue() & 0xFFFF);
      flags.on(BMC_FLAGS_CLICK_TRACK_RESPOND);
      break;
    case BMC_CTRL_CLICK_TRACK_LEVEL:
      midiClock.clickTrackSetLevel(editor.getCtrlValue() & 0x0F);
      flags.on(BMC_FLAGS_CLICK_TRACK_RESPOND);
      break;
    case BMC_CTRL_CLICK_TRACK_MUTE:
      if(editor.getCtrlValue()==1){
        midiClock.clickTrackMute();
      } else {
        midiClock.clickTrackUnmute();
      }
      flags.on(BMC_FLAGS_CLICK_TRACK_RESPOND);
      break;
  }
}
#endif
