/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
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
  if(editor.wasStoreCleared()){
    #if defined(BMC_HAS_DISPLAY) && BMC_MAX_ILI9341_BLOCKS > 0
      display.renderStoreClearedBanner();
    #endif
  }
}
void BMC::assignStoreData(){
  // The editor has updated data in EEPROM so we need to update all Hardware and Settings
  BMC_PRINTLN("editor.readyToReload()");
  setLayer(editor.getLayer(), true);

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

  valueTyper.setOffset(settings.getDisplayOffset());

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

  #if BMC_MAX_LFO > 0
    if(editor.lfoUpdated()){
      for(uint8_t i=0;i<BMC_MAX_LFO;i++){
        uint8_t mode = bitRead(store.global.lfo[i].settings[0], 7);
        uint8_t cycle = store.global.lfo[i].settings[0] & 0x7F;
        uint8_t waveform = store.global.lfo[i].settings[1];
        uint8_t bpmRate = store.global.lfo[i].settings[2];
        uint8_t min = store.global.lfo[i].events[3]+0;
        uint8_t max = store.global.lfo[i].events[4]+0;
        if(min == max){
          min = 0;
          max = 127;
        } else if(max < min){
          uint8_t _min = min;
          min = max;
          max = _min;
        }
        lfo[i].setMode(mode);
        lfo[i].setSendCycle(cycle);
        lfo[i].setBpm(midiClock.getBpm());  
        lfo[i].setWaveForm(waveform);
        lfo[i].setBpmRate(bpmRate);
        lfo[i].setRange(min, max);
      }
    }
  #endif
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
    case BMC_CTRL_LAYERS_GET:
      editor.layerSendChangeMessage(false);
      break;
    case BMC_CTRL_LAYERS_SET:
      if(editor.getCtrlWrite() && editor.getCtrlValue()<BMC_MAX_LAYERS){
        setLayer(editor.getCtrlValue() & 0xFF);
      }
      editor.layerSendChangeMessage(false);
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
      if(editor.getCtrlValue() < BMC_MAX_BUTTONS){
        buttons[editor.getCtrlValue()].triggerRelease();
      }
      break;
#endif
    case BMC_CTRL_LED_TEST:
#if BMC_TOTAL_LEDS > 0
    {
      uint8_t deviceId = (editor.getCtrlValue()>>16) & 0xFF;
      uint16_t deviceIndex = editor.getCtrlValue() & 0xFF;
      BMC_PRINTLN("deviceId", deviceId, "deviceIndex", deviceIndex);
      if(deviceId == BMC_DEVICE_ID_LED){
        #if BMC_MAX_LEDS > 0
        if(deviceIndex < BMC_MAX_LEDS){
          BMC_PRINTLN("Test led");
          leds[deviceIndex].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_GLOBAL_LED){
        #if BMC_MAX_GLOBAL_LEDS > 0
        if(deviceIndex < BMC_MAX_GLOBAL_LEDS){
          globalLeds[deviceIndex].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_BI_LED){
        #if BMC_MAX_BI_LEDS > 0
        if(deviceIndex < BMC_MAX_BI_LEDS){
          biLeds[(deviceIndex*2)].test();
          biLeds[(deviceIndex*2)+1].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_GLOBAL_BI_LED){
        #if BMC_MAX_GLOBAL_BI_LEDS > 0
        if(deviceIndex < BMC_MAX_GLOBAL_BI_LEDS){
          globalBiLeds[(deviceIndex*2)].test();
          globalBiLeds[(deviceIndex*2)+1].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_TRI_LED){
        #if BMC_MAX_TRI_LEDS > 0
        if(deviceIndex < BMC_MAX_TRI_LEDS){
          triLeds[(deviceIndex*3)].test();
          triLeds[(deviceIndex*3)+1].test();
          triLeds[(deviceIndex*3)+2].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_GLOBAL_TRI_LED){
        #if BMC_MAX_GLOBAL_TRI_LEDS > 0
        if(deviceIndex < BMC_MAX_GLOBAL_TRI_LEDS){
          globalTriLeds[(deviceIndex*3)].test();
          globalTriLeds[(deviceIndex*3)+1].test();
          globalTriLeds[(deviceIndex*3)+2].test();
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_PIXEL){
        #if BMC_MAX_PIXELS > 0
        if(deviceIndex < BMC_MAX_PIXELS){
          pixels.test(deviceId, deviceIndex);
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_GLOBAL_PIXEL){
        #if BMC_MAX_GLOBAL_PIXELS > 0
        if(deviceIndex < BMC_MAX_GLOBAL_PIXELS){
          pixels.test(deviceId, deviceIndex);
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_RGB_PIXEL){
        #if BMC_MAX_RGB_PIXELS > 0
        if(deviceIndex < BMC_MAX_RGB_PIXELS){
          pixels.test(deviceId, deviceIndex);
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_GLOBAL_RGB_PIXEL){
        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
        if(deviceIndex < BMC_MAX_GLOBAL_RGB_PIXELS){
          pixels.test(deviceId, deviceIndex);
        }
        #endif
      } else if(deviceId == BMC_DEVICE_ID_PIXEL_STRIP){
        #if BMC_MAX_PIXEL_STRIP > 0
          pixels.test(deviceId, 0);
        #endif
      }
    }
#endif
      break;

#if BMC_MAX_NL_RELAYS > 0
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

#if defined(BMC_USE_FAS)
    case BMC_CTRL_FAS_STATE:
      editor.utilitySendFasState(sync.fas.getConnectedDeviceId());
      break;
#endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
    case BMC_CTRL_POT_CALIBRATION:
      {
        uint32_t e = editor.getCtrlValue();
        uint8_t deviceType = (e >> 16) & 0xFF;
        uint16_t index = e & 0xFFFF;
        BMC_PRINTLN("BMCCtrl::hardware::PotCalibration", deviceType, index);
        bool canceled = false;
        if(potCalibration.active()){
          if(potCalibration.getMin() < potCalibration.getMax()){
            editor.setPotCalibration(
              potCalibration.getDeviceType(),
              potCalibration.getIndex(),
              potCalibration.getMin(),
              potCalibration.getMax()
            );
          } else {
            canceled = true;
          }
        }
        analogInputCalibrationToggle(deviceType, index);
        editor.utilitySendAnalogInputCalibrationStatus(potCalibration.active(), canceled);
      }
      break;

    case BMC_CTRL_POT_CALIBRATION_CANCEL:
      if(potCalibration.active()){
        analogInputCalibrationToggle();
      }
      BMC_PRINTLN("Pot Calibration Cancelled");
      editor.utilitySendAnalogInputCalibrationStatus(potCalibration.active(),true);
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
      if(editor.getCtrlWrite()){
        uint16_t p = (uint16_t) editor.getCtrlValue();
        uint8_t bank = (p >> 8) & 0xFF;
        uint8_t preset = p & 0xFF;
        presets.set(bank, preset);
        // since this is a request that can be sent not just by the editor app
        // we need to send a notification of this change right away
        // so we send it out (second parameter false means it should be sent
        // even if we're not connected to the editor app)
        // we also call presets.presetChanged() to clear that flag
        if(!globals.editorConnected()){
          editor.utilitySendPreset(presets.getBank(), presets.get(), false);
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
