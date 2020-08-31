/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
// setup buttons by assigning button pins, we only do this once at startup
void BMC::setupButtons(){
#ifdef BMC_BUTTON_DELAY_ENABLED
  BMC_PRINTLN("BMC_BUTTON_DELAY_ENABLED");
#endif

#if BMC_MAX_BUTTONS > 0
  for(uint8_t i = 0; i < BMC_MAX_BUTTONS; i++){
    buttons[i].begin(BMCBuildData::getButtonPin(i));
  }
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    globalButtons[i].begin(BMCBuildData::getGlobalButtonPin(i));
  }
  assignGlobalButtons();
#endif
}

void BMC::assignButton(BMCButton& button, bmcStoreButton& data){
  // first check fi the button has an event with a State Change Trigger
  bool hasStateChangeTrigger = flags.read(BMC_FLAGS_FIRST_LOOP);
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    if((data.events[e].mode & 0x0F) == BMC_BUTTON_PRESS_TYPE_STATE_CHANGE){
      hasStateChangeTrigger = true;
      break;
    }
  }
  button.reassign(hasStateChangeTrigger);
  button.setThreshold(settings.getButtonHoldThreshold());
  // read button only any of it's events have a Trigger set
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    if((data.events[e].mode & 0x0F) != BMC_NONE){
      button.setMode(data.events[e].mode);
      button.setFlags(data.events[0].mode);
    }
  }
}
#endif


#if BMC_MAX_BUTTONS > 0
// assign button hold threshold and flags.
// this happens everytime a page changes since it can be different for each page
// also we activate buttons, if a button doesn't have an event attached then
// we don't bother parsing the event data, UNLESS all buttons are active thru settings
void BMC::assignButtons(){
  for(uint8_t i = 0; i < BMC_MAX_BUTTONS; i++){
    assignButton(buttons[i], store.pages[page].buttons[i]);
  }
}
// read the buttons
void BMC::readButtons(){
#if defined(BMC_BUTTON_DELAY_ENABLED)
    // check if any triggers are active
    uint8_t d = buttonsDelay.update();
    if(d!=255){
      handleButtonEvent(buttonsDelay.getType(d), buttonsDelay.getEvent(d));
      BMC_PRINTLN("Button delay event handled");
    }
#endif
  uint32_t _buttonStates = buttonStates;
#if BMC_MAX_BUTTONS > 32
  uint32_t _buttonStates2 = buttonStates2;
#endif
  for(uint8_t i = 0; i < BMC_MAX_BUTTONS; i++){

    #if BMC_MAX_AUX_JACKS > 0
      if(!auxJacks.readButton(i)){
        continue;
      }
    #endif

    // GET THE PIN STATE FROM MUX
    #if BMC_MAX_MUX_IN > 0
      buttons[i].setMuxValue(mux.readDigital(buttons[i].getMuxPin()));
    #endif

    uint8_t buttonTrigger = buttons[i].read();

// this feature is only available when more than 1 button are compiled

  #if BMC_MAX_BUTTONS == 1
    // if only one button is compiled don't use this feature
    bool dual = false;
  #elif BMC_MAX_BUTTONS > 32
    bool dual = dualPress.read(i, buttonTrigger, buttons[i].isClosed(), buttonStates, buttonStates2);
  #else
    bool dual = dualPress.read(i, buttonTrigger, buttons[i].isClosed(), buttonStates);
  #endif

    if(buttonTrigger != BMC_NONE && !dual){
      handleButton(i, buttonTrigger);
      #if defined(BMC_DEBUG)
        printButtonTrigger(i, buttonTrigger, false);
      #endif
    }
#if BMC_MAX_BUTTONS > 32
    // add dual press for more than 32 buttons
    if(i>=32){
      bitWrite(_buttonStates2, i-32, buttons[i].isClosed());
    } else {
      bitWrite(_buttonStates, i, buttons[i].isClosed());
    }
#else
    bitWrite(_buttonStates, i, buttons[i].isClosed());
#endif
  }
#if BMC_MAX_BUTTONS > 32
  if(buttonStates != _buttonStates || buttonStates2 != _buttonStates2){
    buttonStates = _buttonStates;
    buttonStates2 = _buttonStates2;
    editor.utilitySendButtonActivity((uint32_t) buttonStates, (uint32_t) buttonStates2);
  }
#else
  if(buttonStates != _buttonStates){
    buttonStates = _buttonStates;
    editor.utilitySendButtonActivity((uint32_t) buttonStates);
  }
#endif

#if BMC_MAX_BUTTONS > 1
  // used for dual buttons to run the timeout
  dualPress.update();
#endif
}
void BMC::handleButton(uint8_t index, uint8_t t_trigger){
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    bmcStoreButtonEvent &data = store.pages[page].buttons[index].events[e];
    uint8_t type = BMC_GET_BYTE(0,data.event);
    uint8_t trigger = (data.mode & 0x0F)==t_trigger ? t_trigger : BMC_NONE;
    if(trigger == BMC_NONE || type == BMC_NONE){
      continue;
    }
#if defined(BMC_BUTTON_DELAY_ENABLED)
    if(type==BMC_BUTTON_EVENT_TYPE_DELAY && e < (BMC_MAX_BUTTON_EVENTS-1)){
      // do not use the delay if the event with the delay
      // is the last event of the button
      // always set the delay threshold first
      buttonsDelay.setThreshold(BMC_GET_BYTE(1,data.event));
      buttonsDelay.queueDelay(index, e, trigger, data);
    } else if(buttonsDelay.setDelayedEvent(index, e, trigger, data)){
      continue;
    }
#endif
    handleButtonEvent(type, data);
    if(type==BMC_EVENT_TYPE_CUSTOM && callback.buttonsCustomActivity){
      callback.buttonsCustomActivity(index, e,
                            BMC_GET_BYTE(1,data.event),
                            BMC_GET_BYTE(2,data.event),
                            BMC_GET_BYTE(3,data.event),
                            data.ports);
    } else if(callback.buttonActivity){
      callback.buttonActivity(index, e, trigger, store.pages[page].buttons[index], data);
    }
  }
  #if defined(BMC_BUTTON_DELAY_ENABLED)
    // clear the queue in case there was no event for the delay
    buttonsDelay.clearQueued();
  #endif
}
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
// assign button hold threshold and flags.
// this happens everytime a page changes since it can be different for each page
// also we activate buttons, if a button doesn't have an event attached then
// we don't bother parsing the event data, UNLESS all buttons are active thru settings
void BMC::assignGlobalButtons(){
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    assignButton(globalButtons[i], globalData.buttons[i]);
  }
}

// read the buttons
void BMC::readGlobalButtons(){
#if defined(BMC_BUTTON_DELAY_ENABLED)
    // check if any triggers are active
    uint8_t d = globalButtonsDelay.update();
    if(d!=255){
      handleButtonEvent(globalButtonsDelay.getType(d), globalButtonsDelay.getEvent(d));
      BMC_PRINTLN("Global Button delay event handled");
    }
#endif
  uint32_t _globalButtonStates = globalButtonStates;
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
    // GET THE PIN STATE FROM MUX
    #if BMC_MAX_MUX_IN > 0
      globalButtons[i].setMuxValue(mux.readDigital(globalButtons[i].getMuxPin()));
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS == 1
      // if only one button is compiled don't use this feature
      bool dual = false;
    #else
      bool dual = dualPressGlobal.read(i, buttonTrigger, globalButtons[i].isClosed(), globalButtonStates);
    #endif

    uint8_t buttonTrigger = globalButtons[i].read();
    if(buttonTrigger != BMC_NONE && !dual){
      handleGlobalButton(i, buttonTrigger);
      #if defined(BMC_DEBUG)
        printButtonTrigger(i, buttonTrigger, true);
      #endif
    }
    bitWrite(_globalButtonStates, i, globalButtons[i].isClosed());
  }
  if(globalButtonStates != _globalButtonStates){
    globalButtonStates = _globalButtonStates;
    editor.utilitySendGlobalButtonActivity((uint32_t) globalButtonStates);
  }

  #if BMC_MAX_GLOBAL_BUTTONS > 1
    // used for dual buttons to run the timeout
    dualPressGlobal.update();
  #endif
}
void BMC::handleGlobalButton(uint8_t index, uint8_t t_trigger){
  for(uint8_t e = 0; e < BMC_MAX_BUTTON_EVENTS; e++){
    bmcStoreButtonEvent &data = globalData.buttons[index].events[e];
    uint8_t type = BMC_GET_BYTE(0,data.event);
    uint8_t trigger = (data.mode & 0x0F)==t_trigger ? t_trigger : BMC_NONE;
    if(trigger == BMC_NONE || type == BMC_NONE){
      continue;
    }
#if defined(BMC_BUTTON_DELAY_ENABLED)
      if(type==BMC_BUTTON_EVENT_TYPE_DELAY && e < (BMC_MAX_BUTTON_EVENTS-1)){
        // do not use the delay if they event with the delay
        // is the last event of the button
        // always set the delay threshold first
        globalButtonsDelay.setThreshold(BMC_GET_BYTE(1,data.event));
        globalButtonsDelay.queueDelay(index, e, trigger, data);
      } else if(globalButtonsDelay.setDelayedEvent(index, e, trigger, data)){
        continue;
      }
#endif
    handleButtonEvent(type, data);
    if(type==BMC_EVENT_TYPE_CUSTOM && callback.globalButtonsCustomActivity){
      callback.globalButtonsCustomActivity(index, e,
                            BMC_GET_BYTE(1,data.event),
                            BMC_GET_BYTE(2,data.event),
                            BMC_GET_BYTE(3,data.event),
                            data.ports);
    } else if(callback.globalButtonActivity){
      callback.globalButtonActivity(index, e, trigger, globalData.buttons[index], data);
    }
  }
  #if defined(BMC_BUTTON_DELAY_ENABLED)
    // clear the queue in case there was no event for the delay
    globalButtonsDelay.clearQueued();
  #endif
}
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  void BMC::handleButtonEvent(uint8_t type, bmcStoreButtonEvent data){
    #if defined(BMC_BUTTON_DELAY_ENABLED)
      // ignore this event type
      if(type==BMC_BUTTON_EVENT_TYPE_DELAY){
        return;
      }
    #endif
    uint32_t event = data.event;
    uint8_t ports = data.ports;
    uint8_t byteA = BMC_GET_BYTE(1, event);
    uint8_t byteB = BMC_GET_BYTE(2, event);
    uint8_t byteC = BMC_GET_BYTE(3, event);
    switch(parseMidiEventType(type)){
      case BMC_BUTTON_EVENT_TYPE_MASTER_CLOCK_TAP:
        midiClock.tap();
        break;
      case BMC_BUTTON_EVENT_TYPE_MASTER_CLOCK_SET:
        midiClock.setBpm((event >> 8) & 0x1FF);
        break;

      case BMC_EVENT_TYPE_CUSTOM:
        // this is a standard custom event for all hardware the value is 127
        // it's meant to be used by your sketch
        break;
      case BMC_MIDI_RT_START:
      case BMC_MIDI_RT_CONTINUE:
      case BMC_MIDI_RT_STOP:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_RT_SYSTEM_RESET:
        midi.send(ports, event);// standard midi event
        break;
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_CONTROL_CHANGE:
        midi.send(ports, event);// standard midi event
        streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA, byteB);
        break;
      case BMC_MIDI_PROGRAM_CHANGE:
        midi.send(ports, event);// standard midi event
        streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA);
        break;
      case BMC_MIDI_PITCH_BEND:
        {
          // the pitch value stored in the event must be in a range
          // from -100 to 100 which is then mapped to -8192 to 8191
          int pitch = (int) map((int8_t) byteA, -100, 100, -8192, 8191);
          midi.sendPitchBend(ports, BMC_TO_MIDI_CHANNEL(type), pitch);
        }
        break;

  #if BMC_MAX_PAGES > 1
      case BMC_BUTTON_EVENT_TYPE_PAGE:
        setPage(byteA);
        break;
      case BMC_BUTTON_EVENT_TYPE_PAGE_SCROLL:
        // byteA = flags, bit-0 direction, bit-1 endless
        // byteB = min page
        // byteC = max page
        scrollPage(byteA, byteB, byteC, 1);
        break;
  #endif
      case BMC_BUTTON_EVENT_TYPE_PROGRAM_SCROLL:
        // byteA (bits 0-3) = Channel (0 to 15)
        // byteA (bits 4-7) = flags, bit-0 direction, bit-1 endless
        // byteB = min program
        // byteC = max program
        {
          uint8_t val = midi.scrollPC(ports, BMC_TO_MIDI_CHANNEL(byteA), (byteA>>4), byteB, byteC);
          streamMidiProgram(BMC_TO_MIDI_CHANNEL(byteA), val);
        }

        break;
      case BMC_BUTTON_EVENT_TYPE_CONTROL_SCROLL:
        // byteA (bits 0-3) = Channel (0 to 15)
        // byteA (bits 4-7) = flags, bit-0 direction, bit-1 endless
        // byteB = Control Number
        {
          uint8_t val = midi.scrollCC(ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, (byteA>>4));
          streamMidiControl(BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
        }

        break;
      case BMC_BUTTON_EVENT_TYPE_CONTROL_TOGGLE:
        // Toggle a CC value between 0 and 127, if current value is more than 0
        // it will be set to 0
        // byteA = channel
        // byteB = control number
        {
          uint8_t val = midi.toggleCC(ports, BMC_TO_MIDI_CHANNEL(byteA), byteB);
          streamMidiControl(BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_CONTROL_TOGGLE_2:
        // Toggle a CC value between 2 different values other than 0
        // BMC_BUTTON_EVENT_TYPE_CONTROL_TOGGLE toggles you between 0 and 127
        // this aims to toggle between different values than those 2
        // we got 24-bits to work with after removing the type from the event
        // 4-bits for channel
        // 7-bits for CC#
        // 7-bits for min
        // 7-bits for max
        // in other words not enough bits!!! so we gotta sacrifice one bit
        // since the channel and CC# are required the bit will have to come
        // out of the min/max values, since the max should be a higher value
        // we can take the bit from the min making the min value between 0-63
        // 4-bits for channel (bits 8-11)
        // 7-bits for CC# (bits 12-18)
        // 6-bits for min (19-24)
        // 7-bits for max (25-31)
        {
          uint8_t channel = BMC_TO_MIDI_CHANNEL((event>>8));
          uint8_t cc = ((event>>12) & 0x7F);
          uint8_t min = ((event>>19) & 0x3F);
          uint8_t max = ((event>>25) & 0x7F);
          uint8_t currentValue = midi.getLocalControl(channel, cc);
          if(currentValue==min){
            // if the current value is the same as the min go to the max
            currentValue = max;
          } else {
            // otherwise go to the min
            currentValue = min;
          }
          // we use the currentValue variable to store the value will be sending
          midi.sendControlChange(ports, channel, cc,  currentValue);
          streamMidiControl(channel, cc, currentValue);
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_ACTIVE_SENSE:
        // byteA = command, 0 stop, 1 start, 2 toggle
        // see utility/BMC-Def.h for list
        // all prefixed with "BMC_ACTIVE_SENSE_"
        // ports = where the Active sense will be sent to
        // if ports are not specified the default listener ports are used
        midiActiveSense.command(byteA);
        break;

      case BMC_BUTTON_EVENT_TYPE_STOPWATCH:
        stopwatchCmd(byteA&0x07, ((byteA>>3)&0x1F), byteB, byteC);
        break;

  #ifdef BMC_MIDI_BLE_ENABLED
      case BMC_BUTTON_EVENT_TYPE_BLE_DISCONNECT:
        midi.disconnectBLE();
        break;
  #endif

  #if BMC_MAX_NL_RELAYS > 0
      case BMC_BUTTON_EVENT_TYPE_NL_RELAY_CONTROL:
        if(byteA < BMC_MAX_NL_RELAYS){
          relaysNL[byteA].command(byteB);
        }
        break;
      #if BMC_MAX_NL_RELAYS > 1
      case BMC_BUTTON_EVENT_TYPE_NL_RELAY_CONTROL_TOGGLE:
        if(byteA < BMC_MAX_NL_RELAYS && byteB < BMC_MAX_NL_RELAYS){
          if(relaysNL[byteA].getState()){
            relaysNL[byteA].command(BMC_RELAY_NO);
            relaysNL[byteB].command(BMC_RELAY_NC);
          } else {
            relaysNL[byteA].command(BMC_RELAY_NC);
            relaysNL[byteB].command(BMC_RELAY_NO);
          }
        }
      break;
      #endif
  #endif

  #if BMC_MAX_L_RELAYS > 0
      case BMC_BUTTON_EVENT_TYPE_L_RELAY_CONTROL:
        if(byteA < BMC_MAX_L_RELAYS){
          relaysL[byteA].command(byteB);
        }
        break;
      #if BMC_MAX_L_RELAYS > 1
      case BMC_BUTTON_EVENT_TYPE_L_RELAY_CONTROL_TOGGLE:
        if(byteA < BMC_MAX_L_RELAYS && byteB < BMC_MAX_L_RELAYS){
          if(relaysL[byteA].getState()){
            relaysL[byteA].command(BMC_RELAY_NO);
            relaysL[byteB].command(BMC_RELAY_NC);
          } else {
            relaysL[byteA].command(BMC_RELAY_NC);
            relaysL[byteB].command(BMC_RELAY_NO);
          }
        }
        break;
      #endif
  #endif

  #if BMC_MAX_SKETCH_BYTES > 0
      case BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_SET:
        {
          byteA = constrain(byteA, 0, BMC_MAX_SKETCH_BYTES);
          BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
          byteB = constrain(byteB, data.min, data.max);
          streamToSketch(BMC_ITEM_ID_SKETCH_BYTES, byteB, data.name);
          setSketchByte(byteA, byteB);
          if(callback.storeUpdated){
            callback.storeUpdated();
          }
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_SCROLL:
        {
          uint8_t n = (byteA >> 2) & 0x3F;
          n = constrain(n, 0, BMC_MAX_SKETCH_BYTES);

          BMCSketchByteData data = BMCBuildData::getSketchByteData(n);

          byteB = constrain(byteB, data.min, data.max);
          byteC = constrain(byteC, data.min, data.max);

          uint8_t tmp = getSketchByte(n);

          BMCScroller <uint8_t> scroller(data.min, data.max);
          tmp = scroller.scroll(data.step, bitRead(byteA,0), bitRead(byteA,1), tmp, byteB, byteC);
          streamToSketch(BMC_ITEM_ID_SKETCH_BYTES, tmp, data.name);

          setSketchByte(n, tmp);
          if(callback.storeUpdated){
            callback.storeUpdated();
          }
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_TOGGLE:
        {
          byteA = constrain(byteA, 0, BMC_MAX_SKETCH_BYTES);
          BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
          byteB = constrain(byteB, data.min, data.max);
          byteC = constrain(byteC, data.min, data.max);
          uint8_t tmp = getSketchByte(byteA);
          if(tmp!=byteB){
            setSketchByte(byteA, byteB);
            streamToSketch(BMC_ITEM_ID_SKETCH_BYTES, byteB, data.name);
          } else {
            setSketchByte(byteA, byteC);
            streamToSketch(BMC_ITEM_ID_SKETCH_BYTES, byteC, data.name);
          }
          streamToSketch(0, byteB, data.name);
          if(callback.storeUpdated){
            callback.storeUpdated();
          }
        }
        break;
  #endif

  #if BMC_MAX_LEDS > 0
    case BMC_BUTTON_EVENT_TYPE_LED_TEMP_BLINK:
      if(byteA<BMC_MAX_LEDS){
        leds[byteA].quickBlink();
      }
      break;
  #endif
  #if BMC_MAX_GLOBAL_LEDS > 0
    case BMC_BUTTON_EVENT_TYPE_GLOBAL_LED_TEMP_BLINK:
      if(byteA<BMC_MAX_GLOBAL_LEDS){
        globalLeds[byteA].quickBlink();
      }
      break;
  #endif
  #if BMC_MAX_PWM_LEDS > 0
    case BMC_BUTTON_EVENT_TYPE_PWM_LED_TEMP_BLINK:
      if(byteA<BMC_MAX_PWM_LEDS){
        pwmLeds[byteA].quickBlink(byteB);
      }
      break;
  #endif
      case BMC_BUTTON_EVENT_TYPE_SAVE_EEPROM:
        editor.saveEEPROM();
        if(callback.storeUpdated){
          callback.storeUpdated();
        }
        break;

  #ifdef BMC_USE_BEATBUDDY
      case BMC_BUTTON_EVENT_TYPE_BEATBUDDY_SET_BPM:
        beatBuddy.tempo((event >> 8) & 0x1FF);
        break;
      case BMC_BUTTON_EVENT_TYPE_BEATBUDDY_CMD:
        // byteA = beatbuddy command
        // see utility/BMC-Def.h for list
        // all prefixed with "BMC_BEATBUDDY_CMD_"
        beatBuddy.sendCommand(byteA, byteB);
        break;
      case BMC_BUTTON_EVENT_TYPE_BEATBUDDY_FOLDER_SONG:
        // event (bits 8 to 23) = folder number (0 to 16,383)
        beatBuddy.songSelect((event >> 8) & 0x3FFF, byteC);
        break;
  #endif
      case BMC_BUTTON_EVENT_TYPE_MENU:
        if(callback.menuCommand){
          callback.menuCommand(byteA);
        }
        break;

  #ifdef BMC_USE_CLICK_TRACK
      case BMC_BUTTON_EVENT_TYPE_CLICK_TRACK:
        // byteA = Command id, see utility/ClickTrack.h for possible commands
        midiClock.clickTrackCommand(byteA);
        break;
  #endif

      case BMC_BUTTON_EVENT_TYPE_BANK_MSB_PROGRAM:
        // byteA = channel
        // byteB = control 0 value
        // byteC = program number
        midi.sendControlChange(ports, BMC_TO_MIDI_CHANNEL(byteA), 0, byteB & 0x7F);
        midi.sendProgramChange(ports, BMC_TO_MIDI_CHANNEL(byteA), byteC & 0x7F);
        break;
      case BMC_BUTTON_EVENT_TYPE_BANK_LSB_PROGRAM:
        // byteA = channel
        // byteB = control 32 value
        // byteC = program number
        midi.sendControlChange(ports, BMC_TO_MIDI_CHANNEL(byteA), 32, byteB & 0x7F);
        midi.sendProgramChange(ports, BMC_TO_MIDI_CHANNEL(byteA), byteC & 0x7F);
        break;
      case BMC_BUTTON_EVENT_TYPE_BANK_MSB_LSB:
        // byteA = channel
        // byteB = control 0 value
        // byteC = control 32 value
        midi.sendControlChange(ports, BMC_TO_MIDI_CHANNEL(byteA), 0, byteB & 0x7F);
        midi.sendControlChange(ports, BMC_TO_MIDI_CHANNEL(byteA), 32, byteC & 0x7F);
        break;

  #ifdef BMC_USE_HELIX
      case BMC_BUTTON_EVENT_TYPE_HELIX_CMD:
        helix.command(byteA, byteB, byteC);
        break;
  #endif

  #ifdef BMC_USE_FAS
      case BMC_BUTTON_EVENT_TYPE_FAS_COMMAND:
        if(byteA==0){
          fas.tapTempo();
        } else if(byteA==1){
          fas.toggleTuner();
        } else if(byteA==2){
          fas.disconnect();
        } else if(byteA==3){
          fas.connect();
        } else if(byteA==4){
          if(fas.connected()){
            fas.disconnect();
          } else {
            fas.connect();
          }
        } else if(byteA>=5){// looper
          fas.looperControl(byteA-5);
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_PRESET:
        fas.setPreset(byteA | (byteB<<8));
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_PRESET_SCROLL:
        {
          bool dir = bitRead(byteA,0);
          bool endless = bitRead(byteA,1);
          uint16_t min = (event >> 10) & 0x3FF;
          uint16_t max = (event >> 20) & 0x3FF;
          fas.presetScroll(dir, endless, min, max);
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_SCENE:
        fas.setSceneNumber(byteA, byteB);
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_SCENE_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteA (flags) = bit-2 revert, no-revert (0), revert (1)
        // byteB = minimum scene for scrolling
        // byteC = maximum scene for scrolling
        fas.sceneScroll(bitRead(byteA,0), bitRead(byteA,1), bitRead(byteA,2), byteB, byteC);
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_BLOCK_STATE:
        if(byteA==0){
          // bypass block
          fas.setBlockBypass(byteB);
        } else if(byteA==1){
          // engage block
          fas.setBlockEngage(byteB);
        } else if(byteA==2){
          // toggle bypass block
          fas.toggleBlockState(byteB);
        } else if(byteA==3){
          // set block to X
          fas.setBlockX(byteB);
        } else if(byteA==4){
          // set block to Y
          fas.setBlockY(byteB);
        } else if(byteA==5){
          // toggle XY block
          fas.toggleBlockXY(byteB);
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_FAS_BLOCK_PARAM:
        {
          uint16_t value = fas.getSyncedParameterValue(byteB);
          if(byteA==0){ // parameter min
            if(value>0){
              fas.sendChangeSyncedParameter(byteB, 0);
            }
          } else if(byteA==1){ // parameter max
            if(value==0){
              fas.sendChangeSyncedParameter(byteB, 65534);
            }
          } else if(byteA==2){ // parameter toggle
            BMC_PRINTLN("value:", value);
            if(value==0){
              fas.sendChangeSyncedParameter(byteB, 65534);
            } else {
              fas.sendChangeSyncedParameter(byteB, 0);
            }
          }
        }
        break;
  #endif

      case BMC_BUTTON_EVENT_TYPE_MIDI_REAL_TIME_BLOCK:
        // ignored any incoming/Outgoing MIDI real time messages
        // byteA: 0=input, 1=output
        // byteB: 0=allowed, 1=ignored, 2>= toggle
        if(byteA==0){
          if(byteB>=2){
            midi.toggleRealTimeBlockInput();
          } else {
            midi.setRealTimeBlockInput(byteB==1);
          }
        } else {
          if(byteB>=2){
            midi.toggleRealTimeBlockOutput();
          } else {
            midi.setRealTimeBlockOutput(byteB==1);
          }
        }
        break;
      case BMC_BUTTON_EVENT_TYPE_PROGRAM_BANKING_SCROLL:
        // byteA = flags, bit-0 direction, bit-1 endless
        midiProgramBankScroll(bitRead(byteA, 0), bitRead(byteA, 1), (byteA>>2)+1, byteB, byteC);
        break;
      case BMC_BUTTON_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
        // byteA = Amount
        // byteB = Channel
        midiProgramBankTrigger(byteA, byteB, ports);
        break;
      case BMC_BUTTON_EVENT_TYPE_TYPER_CMD:
        {
          uint8_t cmd = valueTyper.cmd(byteA, byteB);
          if(cmd > 10){// cmd 10 is Clear
            if(cmd==12){// page
              setPage(valueTyper.getRawOutput());
            } else if(cmd==13){// preset
#if BMC_MAX_PRESETS > 0
              presets.set(valueTyper.getRawOutput());
#endif
            } else if(cmd==14){// fas preset
#if defined(BMC_USE_FAS)
              fas.setPreset(valueTyper.getRawOutput());
#endif
            } else if(cmd==15){// fas scene
#if defined(BMC_USE_FAS)
              fas.setSceneNumber(valueTyper.getRawOutput(), false);
#endif
            } else if(cmd==16){// fas scene revert
#if defined(BMC_USE_FAS)
              fas.setSceneNumber(valueTyper.getRawOutput(), true);
#endif
            } else if(cmd==17){// set typer channel for midi modes
              // channel
              uint8_t ch = valueTyper.getRawOutput();
              if(ch>=0 && ch<=15){
                typerChannel = ch+1;
              }
            } else if(cmd==18){
              // program
              uint8_t pc = valueTyper.getRawOutput();
              midi.sendProgramChange(ports, typerChannel, pc);
              streamMidiProgram(typerChannel, pc);
            } else if(cmd==19){
              // control 0 value
              uint8_t val = valueTyper.getRawOutput();
              midi.sendControlChange(ports, typerChannel, 0, val);
              streamMidiControl(typerChannel, 0, val);
            } else if(cmd==20){
              // control toggle
              uint8_t cc = valueTyper.getRawOutput();
              uint8_t val = midi.toggleCC(ports, typerChannel, cc);
              midi.sendControlChange(ports, typerChannel, cc, val);
              streamMidiControl(typerChannel, cc, val);
            }
          }
        }
        break;

  #if BMC_MAX_CUSTOM_SYSEX > 0
      case BMC_BUTTON_EVENT_TYPE_CUSTOM_SYSEX:
        // byteA = send mode, 0, 1 or 2
        // byteB = index of the 1st custom sysex item to send
        // byteC = index of the 2nd custom sysex item to send
        customSysEx.send((byteA & 0x03), ports, byteB, byteC);
        break;
  #endif

  #if BMC_MAX_LIBRARY > 0
      case BMC_BUTTON_EVENT_TYPE_LIBRARY:
        // byteA = index of the library item
        library.send(byteA);
        break;
      case BMC_BUTTON_EVENT_TYPE_LIBRARY2:
        // byteA = index of the 1st library item to send
        // byteB = index of the 2nd library item to send
        library.send(byteA, byteB);
        break;
      case BMC_BUTTON_EVENT_TYPE_LIBRARY3:
        // byteA = index of the 1st library item to send
        // byteB = index of the 2nd library item to send
        // byteC = index of the 3rd library item to send
        library.send(byteA, byteB, byteC);
        break;

    #if BMC_MAX_PRESETS > 0
      case BMC_BUTTON_EVENT_TYPE_PRESET:
        // byteA = index of preset to send
        // byteB = if 0 use send each library item of the preset to it's ports
        //         if 1 or more, override all ports
        presets.set(byteA, (byteB > 0), ports);
        break;
      case BMC_BUTTON_EVENT_TYPE_PRESET_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum preset for scrolling
        // byteC = maximum preset for scrolling
        presets.scroll(1, byteA, byteB, byteC);
        break;
      case BMC_BUTTON_EVENT_TYPE_PRESET_IN_BANK:
        // byteA = index of preset to send
        // byteB = if 0 use send each library item of the preset to it's ports
        //         if 1 or more, override all ports
        presets.setInBank(byteA, (byteB > 0), ports);
        break;
      case BMC_BUTTON_EVENT_TYPE_PRESET_IN_BANK_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum bank for scrolling
        // byteC = maximum bank for scrolling
        presets.scrollInBank(1, byteA, byteB, byteC);
        break;
      case BMC_BUTTON_EVENT_TYPE_PRESETS_SET_BANK:
        // byteA = index of bank to switch to
        presets.setBank(byteA);
        break;
      case BMC_BUTTON_EVENT_TYPE_PRESETS_BANK_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum preset for scrolling
        // byteC = maximum preset for scrolling
        presets.bankScroll(1, byteA, byteB, byteC);
        break;
    #endif // BMC_MAX_PRESETS > 0 && BMC_MAX_PRESET_ITEMS > 0

    #if BMC_MAX_PRESETS > 0 && BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS > 0
      case BMC_BUTTON_EVENT_TYPE_SETLIST:
        // byteA = index of setList to send
        // byteB = switch to first song of selected setlist is value is 1
        setLists.set(byteA, (byteB > 0));
        break;
      case BMC_BUTTON_EVENT_TYPE_SETLIST_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum setList for scrolling
        // byteC = maximum setList for scrolling
        setLists.scroll(1, byteA, byteB, byteC);
        break;
      case BMC_BUTTON_EVENT_TYPE_SETLIST_SONG:
        // byteA = index of setList to send
        setLists.setSong(byteA);
        break;
      case BMC_BUTTON_EVENT_TYPE_SETLIST_SONG_SCROLL:
        // scroll thru currently selected setlist songs
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum song for scrolling
        // byteC = maximum song for scrolling
        setLists.scrollSong(1, byteA, byteB, byteC);
        break;
    #endif // BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS > 0
  #endif // BMC_MAX_LIBRARY > 0
      case BMC_BUTTON_EVENT_TYPE_USER_1:
      case BMC_BUTTON_EVENT_TYPE_USER_2:
      case BMC_BUTTON_EVENT_TYPE_USER_3:
      case BMC_BUTTON_EVENT_TYPE_USER_4:
      case BMC_BUTTON_EVENT_TYPE_USER_5:
      case BMC_BUTTON_EVENT_TYPE_USER_6:
      case BMC_BUTTON_EVENT_TYPE_USER_7:
      case BMC_BUTTON_EVENT_TYPE_USER_8:
        if(callback.userEventButtons){
          callback.userEventButtons(parseUserEventType(type), event, ports, data.mode);
        }
        break;
    }
  }
#endif
