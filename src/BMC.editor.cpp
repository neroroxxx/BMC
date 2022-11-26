/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
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
      #if BMC_TOTAL_POTS_AUX_JACKS > 0
        // if pot calibration is ongoing after disconnected, cancel it
        if(potCalibration.active()){
          analogInputCalibrationToggle();
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
  sync.beatBuddy.enableSync(settings.getBeatBuddySync());
  sync.beatBuddy.setChannel(settings.getBeatBuddyChannel()+1);
  sync.beatBuddy.setPortBit(settings.getBeatBuddyPort());
#endif

#ifdef BMC_USE_HELIX
  sync.helix.setDeviceId(settings.getHelixId());
  sync.helix.setChannel(settings.getHelixChannel()+1);
  sync.helix.setPortBit(settings.getHelixPort());
#endif

/*
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
*/
  #if BMC_MAX_TEMPO_TO_TAP > 0
    if(editor.tempoToTapUpdated()){
      tempoToTap.buildListeners();
    }
  #endif
  #if BMC_MAX_TRIGGERS > 0
    if(editor.triggersUpdated()){
      triggers.buildListeners();
    }
  #endif

  #if BMC_MAX_TIMED_EVENTS > 0
    if(editor.timedEventsUpdated()){
      timedEvents.buildListeners();
    }
  #endif
  #if BMC_MAX_BUTTONS > 0
    globals.buttonStates.clear();
  #endif

  #if BMC_MAX_GLOBAL_BUTTONS > 0
    globals.globalButtonStates.clear();
  #endif

  #if BMC_MAX_LEDS > 0
    globals.ledStates.clear();
  #endif

  #if BMC_MAX_GLOBAL_LEDS > 0
    globals.globalLedStates.clear();
  #endif

  #if BMC_MAX_BI_LEDS > 0
    globals.biLedStates[0].clear();
    globals.biLedStates[1].clear();
  #endif

  #if BMC_MAX_GLOBAL_BI_LEDS > 0
    globals.globalBiLedStates[0].clear();
    globals.globalBiLedStates[1].clear();
  #endif

  #if BMC_MAX_TRI_LEDS > 0
    globals.triLedStates[0].clear();
    globals.triLedStates[1].clear();
    globals.triLedStates[2].clear();
  #endif

  #if BMC_MAX_GLOBAL_TRI_LEDS > 0
    globals.globalTriLedStates[0].clear();
    globals.globalTriLedStates[1].clear();
    globals.globalTriLedStates[2].clear();
  #endif

  #if BMC_MAX_PIXELS > 0
    globals.pixelStates.clear();
  #endif

  #if BMC_MAX_RGB_PIXELS > 0
    globals.rgbPixelStates[0].clear();
    globals.rgbPixelStates[1].clear();
    globals.rgbPixelStates[2].clear();
  #endif

  #if BMC_MAX_NL_RELAYS > 0
    globals.relayNLStates.clear();
  #endif

  #if BMC_MAX_L_RELAYS > 0
    globals.relayLStates.clear();
  #endif

  #if BMC_MAX_AUX_JACKS > 0
    globals.auxJackStates.clear();
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

    case BMC_CTRL_GET_STATES:
      editor.triggerStates();
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
      //globals.ledStates.clear();
      break;
    case BMC_CTRL_LED_TEST:
      if(editor.getCtrlValue() < BMC_MAX_LEDS){
        leds[(editor.getCtrlValue() & 0xFF)].test();
      }
      break;
#endif

#if BMC_MAX_NL_RELAYS > 0
    case BMC_CTRL_NL_RELAYS_GET:
      //relayNLStates = ~relayNLStates;
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
      //relayLStates = ~relayLStates;
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
      //editor.utilitySendAuxJackActivity(auxJacksStates);
      break;
#endif

#if defined(BMC_USE_FAS)
    case BMC_CTRL_FAS_STATE:
      editor.utilitySendFasState(sync.fas.getConnectedDeviceId());
      break;
#endif

#if BMC_MAX_PWM_LEDS > 0
    case BMC_CTRL_PWM_LED_STATES:
      //pwmLedStates = ~pwmLedStates;
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
      //globals.pixelStates.clear();
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
      //globals.rgbPixelStates[0].clear();
      //globals.rgbPixelStates[1].clear();
      //globals.rgbPixelStates[2].clear();
      break;
    case BMC_CTRL_RGB_PIXEL_TEST:
      BMC_PRINTLN("Test RGB Pixel",editor.getCtrlValue());
      if(editor.getCtrlValue() < BMC_MAX_RGB_PIXELS){
        //pixels.testRgb((editor.getCtrlValue() & 0xFF));
      }
      break;
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
    case BMC_CTRL_GLOBAL_LED_STATES:
      //globals.globalLedStates.clear();
      break;
    case BMC_CTRL_GLOBAL_LED_TEST:
      //if(editor.getCtrlValue() < BMC_MAX_GLOBAL_LEDS){
        //globalLeds[(editor.getCtrlValue() & 0xFF)].test();
      //}
      break;
#endif

#if BMC_MAX_POTS > 0
    case BMC_CTRL_POT_STATES:
      {
        /*
        uint8_t values[BMC_MAX_POTS];
        for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
          values[i] = pots[i].getValue();
        }
        editor.utilitySendPotsActivity(false, values, BMC_MAX_POTS, false);
        */
      }
      break;
#endif
#if BMC_TOTAL_POTS_AUX_JACKS > 0
    case BMC_CTRL_POT_CALIBRATION:
      {
        BMC_PRINTLN("BMCCtrl::hardware::PotCalibration", editor.getCtrlValue());
        bool canceled = false;
        if(potCalibration.active()){
          if(potCalibration.getMin() < potCalibration.getMax()){
            editor.setPotCalibration(
                potCalibration.getDeviceType(),
                potCalibration.getIndex(),
                potCalibration.getMin(),
                potCalibration.getMax()
              );
            BMC_PRINTLN("Pot Calibration Set", potCalibration.getDeviceType(), potCalibration.getIndex(),  potCalibration.getMin(), potCalibration.getMax());
          } else {
            canceled = true;
          }
        }
        uint32_t e = editor.getCtrlValue();
        uint8_t deviceType = (e >> 16) & 0xFF;
        uint16_t index = e & 0xFFFF;
        analogInputCalibrationToggle(deviceType, index);
        editor.utilitySendAnalogInputCalibrationStatus(potCalibration.active(), canceled);
      }
      break;

    case BMC_CTRL_POT_CALIBRATION_CANCEL:
      if(potCalibration.active()){
        analogInputCalibrationToggle();
      }
      editor.utilitySendAnalogInputCalibrationStatus(potCalibration.active(),true);
      break;
#endif

#if BMC_MAX_GLOBAL_POTS > 0
    case BMC_CTRL_GLOBAL_POT_STATES:
      /*
      {
        uint8_t values[BMC_MAX_GLOBAL_POTS];
        for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
          values[i] = globalPots[i].getValue();
        }
        editor.utilitySendPotsActivity(true, values, BMC_MAX_GLOBAL_POTS, false);
      }
      */
      break;

    case BMC_CTRL_GLOBAL_POT_CALIBRATION:
      {
        /*
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
        */
      }
      break;

    case BMC_CTRL_GLOBAL_POT_CALIBRATION_CANCEL:
      /*
      if(potCalibration.active()){
        globalPotCalibrationToggle();
      }
      editor.utilitySendGlobalPotCalibrationStatus(potCalibration.active(),true);
      */
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
        presets.set((uint16_t) editor.getCtrlValue());
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
