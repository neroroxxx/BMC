/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

uint8_t BMC::processEvent(uint8_t group, uint8_t deviceId, 
                          uint16_t deviceIndex, uint16_t eventIndex, 
                          uint8_t value, uint8_t dat){
  // Process Events
  // Check if we should render a display's name
  if(eventIndex == 0 && group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
    if(settings.getDisplayNames()){
      #if BMC_MAX_OLED > 0
        if(deviceId == BMC_DEVICE_ID_OLED && store.layers[layer].oled[deviceIndex].name == 0){
          return false;
        }
      #endif
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(deviceId == BMC_DEVICE_ID_ILI && store.layers[layer].ili[deviceIndex].name == 0){
          return false;
        }
      #endif
      bmcStoreName t;
      editor.getDeviceNameText(deviceId, deviceIndex, t.name);
      display.renderText(deviceIndex, (deviceId == BMC_DEVICE_ID_OLED), 254, t.name, "");
    }
#endif
    return false;
  }

  if(eventIndex == 0 || eventIndex > BMC_MAX_EVENTS_LIBRARY){
    return false;
  }
  
  bmcStoreEvent& e = store.global.events[eventIndex-1];
  if(e.type == BMC_NONE){
    return false;
  }
  globals.offset = settings.getDisplayOffset()?0:1;
  uint32_t event = e.event;
  uint8_t byteA = BMC_GET_BYTE(0, event);
  uint8_t byteB = BMC_GET_BYTE(1, event);
  uint8_t byteC = BMC_GET_BYTE(2, event);
  uint8_t byteD = BMC_GET_BYTE(3, event);

  BMCEventScrollData scroll(e.settings, value, deviceId==BMC_DEVICE_GROUP_ENCODER);

#if defined(BMC_HAS_DISPLAY)
  bool isOled = (deviceId == BMC_DEVICE_ID_OLED);
  uint8_t displaySettings = 0;
  if(group == BMC_DEVICE_GROUP_DISPLAY){
#if BMC_MAX_OLED > 0
    if(deviceId == BMC_DEVICE_ID_OLED){
      displaySettings = store.layers[layer].oled[deviceIndex].settings[0];
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(deviceId == BMC_DEVICE_ID_ILI){
      displaySettings = store.layers[layer].ili[deviceIndex].settings[0];
    }
#endif
  }
#endif

  switch(e.type){
    case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
    {
      uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
      uint8_t currentPC = midi.getLocalProgram(channel);
      uint8_t min = 0;
      uint8_t max = 127;
      uint8_t outVal = byteB;
      if(byteC > 0){
        // scrolling max or toggle enabled
        if(max > min){
          min = byteB;
          max = byteC;
        }
        if(!scroll.enabled){
          outVal = currentPC != byteB ? byteB : (byteC-1);
        }
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        // if scroll is enabled or if it's an encoder use scrolling by default
        if(scroll.enabled){
          outVal = midi.scrollPC(e.ports, channel, scroll.amount, scroll.direction, scroll.endless, min, max);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, channel, outVal);
        } else {
          midi.sendProgramChange(e.ports, channel, outVal);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, channel, outVal);
        }

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendProgramChange(e.ports, channel, value);
        streamMidi(BMC_MIDI_PROGRAM_CHANGE, channel, value);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(currentPC, 0, 127, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(bitRead(displaySettings, 2)){ // selected
          display.renderProgramChangeValue(deviceIndex, isOled, e.type, channel, currentPC, false);
        } else {
          display.renderProgramChangeValue(deviceIndex, isOled, e.type, channel, byteB, false);
        }
#endif

      } else {
        return currentPC == (byteB & 0x7F);
      }
    }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
    {
      uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
      uint8_t currentCC = midi.getLocalControl(channel, byteB);
      uint8_t min = 0;
      uint8_t max = 127;
      uint8_t outVal = byteC;
      if(byteD > 0){
        // scrolling max or toggle enabled
        if(max > min){
          min = byteC;
          max = byteD;
        }
        if(!scroll.enabled){
          outVal = currentCC != byteC ? byteC : (byteD-1);
        }
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(scroll.enabled){
          outVal = midi.scrollCC(e.ports, channel, byteB, scroll.amount, scroll.direction, scroll.endless, min, max);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, channel, byteB, outVal);
        } else {
          midi.sendControlChange(e.ports, channel, byteB, outVal);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, channel, byteB, outVal);
        }

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendControlChange(e.ports, channel, byteB, value);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, channel, byteB, value);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(currentCC, 0, 127, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(bitRead(displaySettings, 2)){ // selected
          display.renderControlChangeValue(deviceIndex, isOled, e.type, channel, byteB, currentCC, false);
        } else {
          display.renderControlChangeValue(deviceIndex, isOled, e.type, channel, byteB, byteC, false);
        }
#endif

      } else {
        return currentCC == (byteC & 0x7F);
      }
    }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendNoteOn(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendNoteOn(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);

      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(byteC, 0, 127, 0, 100);

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
      display.renderNoteValue(deviceIndex, isOled, e.type, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC, false);
#endif
      }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendNoteOff(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendNoteOff(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);

      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(byteC, 0, 127, 0, 100);
        

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
      display.renderNoteValue(deviceIndex, isOled, e.type, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC, false);
#endif
      }
      break;
    case BMC_EVENT_TYPE_MIDI_PITCH_BEND:
      if(group==BMC_DEVICE_GROUP_POT){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        if(byteB==0){
          int8_t pitch = midi.getLocalPitch(channel);
          if(value<59){
            // pitch down
            uint16_t newPitch = map(value, 0, 58, -8192, -1);
            midi.sendPitchBend(e.ports, channel, newPitch);
          } else if(value>68){
            // pitch up
            uint16_t newPitch = map(value, 69, 127, 1, 8191);
            midi.sendPitchBend(e.ports, channel, newPitch);
          } else if(pitch!=0){
            // center
            midi.sendPitchBend(e.ports, channel, 0);
            midi.setLocalPitch(channel, 0);
          }
        } else if(byteB==1){
          // leave the first 10 values of the pot as a buffer for a flat pitch
          if(value>9){
            // move pitch up
            uint16_t newPitch = map(value, 10, 127, 1, 8191);
            midi.sendPitchBend(e.ports, channel, newPitch);
          } else if(midi.getLocalPitch(channel)!=0){
            midi.sendPitchBend(e.ports, channel, 0);
            midi.setLocalPitch(channel, 0);
          }
        } else {
          // leave the first 10 values of the pot as a buffer for a flat pitch
          if(value>9){
            // move pitch up
            int16_t newPitch = map(value, 10, 127, -1, -8192);
            midi.sendPitchBend(e.ports, channel, newPitch);
          } else if(midi.getLocalPitch(channel)!=0){
            midi.sendPitchBend(e.ports, channel, 0);
            midi.setLocalPitch(channel, 0);
          }
        }
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "PITCH");
#endif
      }
      break;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH_POLY:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouchPoly(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH_POLY, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(byteC, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "A.T. POLY");
#endif

      }
      return false;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouch(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(byteC, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "A.T.");
#endif
      }
      return false;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_SET:
    {
      uint8_t min = 0;
      uint8_t max = 127;
      uint8_t outVal = byteB;
      if(byteC > 0){
        // scrolling max or toggle enabled
        if(max > min){
          min = byteB;
          max = byteC;
        }
        if(!scroll.enabled){
          outVal = programBank != byteB ? byteB : byteC;
        }
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(scroll.enabled){
          midiProgramBankScroll(scroll.direction, scroll.endless, scroll.amount, byteB, byteC);
        } else {
          programBank = outVal;
        }
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(programBank, 0, 127, 0, 100);
        

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(bitRead(displaySettings, 2)){ // selected
          display.renderNumber(deviceIndex, isOled, e.type, programBank, "%03u", "PROGRAM");
        } else {
          display.renderNumber(deviceIndex, isOled, e.type, byteB, "%03u", "PROGRAM");
        }
#endif

      }
    }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        midiProgramBankTrigger(BMC_TO_MIDI_CHANNEL(byteA), e.ports);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(programBank, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "TRIGGER");
#endif

      }
      break;
    case BMC_EVENT_TYPE_MIDI_REAL_TIME_BLOCK:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        if(byteA==0){
          if(byteB >= 2){
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
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        if(byteA==0){
          return midi.getRealTimeBlockInput() ? 100 : 0;
          
        }
        return midi.getRealTimeBlockOutput() ? 100 : 0;
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "R.T. BLOCK");
#endif
      } else {
        if(byteA==0){
          return midi.getRealTimeBlockInput();
        }
        return midi.getRealTimeBlockOutput();
      }
      break;
    case BMC_EVENT_TYPE_BANK_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "LSB PGM");
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 32, byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "MSB PGM");
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "MSB LSB");
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, byteC & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteD & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "MSB LSB PGM");
#endif
      }
      break;
    // SYSTEM
    case BMC_EVENT_TYPE_SYSTEM_ACTIVE_SENSE:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiActiveSense.command(byteA);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return midiActiveSense.active() ? 100 : 0;

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "ACTIVE SENSE", "",midiActiveSense.active());
#endif
      } else {
        return midiActiveSense.active();
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiClock.setBpm(BMC_GET_BYTE_2(0, event));
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(midiClock.getBpm(), 30, 300, 0, 100);

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, midiClock.getBpm(), "%u", "BPM");
#endif
      } else {
        return BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiClock.tap();
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "TAP");
#endif
      } else {
        return BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_STATUS:
      if(group == BMC_DEVICE_GROUP_LED){
        switch(byteA){
          case BMC_LED_STATUS_ALWAYS_ON:
            return true;
          case BMC_LED_STATUS_BMC:
            return flags.read(BMC_FLAGS_STATUS_LED);
          case BMC_LED_STATUS_EDITOR_CONNECTED:
            return globals.editorConnected();
          case BMC_LED_STATUS_HOST_CONNECTED:
            return globals.hostConnected();
          case BMC_LED_STATUS_BLE_CONNECTED:
            return globals.bleConnected();
          case BMC_LED_STATUS_ACTIVE_SENSE_SENDING:
            return midiActiveSense.active();
          case BMC_LED_STATUS_ACTIVE_SENSE_READING:
            return midiActiveSense.reading();
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT:
            return !midi.getRealTimeBlockInput();
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT:
            return !midi.getRealTimeBlockOutput();
          case BMC_LED_STATUS_STOPWATCH_ACTIVE:
            return (stopwatch.getState() == 1);
          case BMC_LED_STATUS_STOPWATCH_STATE:
            return (stopwatch.getState() > 0);
          case BMC_LED_STATUS_STOPWATCH_COMPLETE:
            return (stopwatch.getState() == 2);
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        switch(byteA){
          case BMC_LED_STATUS_ALWAYS_ON:
          case BMC_LED_STATUS_BMC:
            display.renderText(deviceIndex, isOled, e.type, "BMC");
            return 1;
          case BMC_LED_STATUS_EDITOR_CONNECTED:
            display.renderText(deviceIndex, isOled, e.type, "EDITOR","STATUS",globals.editorConnected());
            return 1;
          case BMC_LED_STATUS_HOST_CONNECTED:
            display.renderText(deviceIndex, isOled, e.type, "HOST","STATUS",globals.hostConnected());
            return 1;
          case BMC_LED_STATUS_BLE_CONNECTED:
            display.renderText(deviceIndex, isOled, e.type, "BLE","STATUS",globals.bleConnected());
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_SENDING:
            display.renderText(deviceIndex, isOled, e.type, "A.S. SEND","STATUS", midiActiveSense.active());
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_READING:
            display.renderText(deviceIndex, isOled, e.type, "A.S. READ","STATUS", midiActiveSense.reading());
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT:
            display.renderText(deviceIndex, isOled, e.type, "R.T. IN","STATUS", midi.getRealTimeBlockInput());
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT:
            display.renderText(deviceIndex, isOled, e.type, "R.T. OUT","STATUS", midi.getRealTimeBlockOutput());
            return 1;
          case BMC_LED_STATUS_STOPWATCH_ACTIVE:
          case BMC_LED_STATUS_STOPWATCH_STATE:
          case BMC_LED_STATUS_STOPWATCH_COMPLETE:
          {
            char str[13] = "";
            sprintf(str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
            display.renderText(deviceIndex, isOled, e.type, str, "STOPWATCH");
          }
            return 1;
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
      if(group == BMC_DEVICE_GROUP_LED){
        return globals.hasMidiActivity(byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "MIDI IO");
#endif

      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_SAVE_EEPROM:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        editor.saveEEPROM();
        if(callback.storeUpdated){
          callback.storeUpdated();
        }
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "SAVE EEPROM");
#endif

      }
      break;
#if defined(BMC_USE_ON_BOARD_EDITOR)
    case BMC_EVENT_TYPE_SYSTEM_MENU:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        obe.menuCommand(byteA);
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        uint8_t menCmd = scroll.direction ? BMC_MENU_NEXT : BMC_MENU_PREV;
        obe.menuCommand(menCmd, true);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        switch(byteA){
          case BMC_MENU_TOGGLE:
            display.renderText(deviceIndex, isOled, e.type, "TOGGLE");
            return 1;
          case BMC_MENU_SELECT:
            display.renderText(deviceIndex, isOled, e.type, "SELECT");
            return 1;
          case BMC_MENU_BACK:
            display.renderText(deviceIndex, isOled, e.type, "BACK");
            return 1;
          case BMC_MENU_PREV:
            display.renderText(deviceIndex, isOled, e.type, "PREV");
            return 1;
          case BMC_MENU_NEXT:
            display.renderText(deviceIndex, isOled, e.type, "NEXT");
            return 1;
          case BMC_MENU_SHIFT:
            display.renderText(deviceIndex, isOled, e.type, "SHIFT");
            return 1;
          case BMC_MENU_CANCEL:
            display.renderText(deviceIndex, isOled, e.type, "CANCEL");
            return 1;
          case BMC_MENU_SAVE:
            display.renderText(deviceIndex, isOled, e.type, "SAVE");
            return 1;
        }
#endif
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_TYPER:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        uint8_t cmd = valueTyper.cmd(byteA, byteB);
        if(cmd > 10){// cmd 10 is Clear
          // HANDLED BY TYPER CLASS
          // 10 is clear
          // 11 is cursor left
          // 12 is cursor right
          // 13 is decrease
          // 14 is increase
          // 15 is custom callback

          // HANDLED HERE
          // 16 is layer
          // 17 is preset
          // 18 is fas preset
          // 19 is fas scene
          // 20 is fas scene revert

          switch(cmd){
            case 16:
              setLayer(valueTyper.getRawOutput());
              break;
#if BMC_MAX_PRESETS > 0
            case 17:
              presets.setByIndex(valueTyper.getRawOutput());
              break;
#endif
#if defined(BMC_USE_FAS)
            case 18:
              sync.fas.setPreset(valueTyper.getRawOutput());
              break;
            case 19:
              sync.fas.setSceneNumber(valueTyper.getRawOutput(), false);
              break;
            case 20:
              sync.fas.setSceneNumber(valueTyper.getRawOutput(), true);
              break;
#endif
            case 21:
              {
                // program
                uint8_t pc = valueTyper.getOutput();
                if(pc <= 127){
                  uint8_t channel = settings.getTyperChannel();
                  channel = BMC_TO_MIDI_CHANNEL(channel);
                  midi.sendProgramChange(e.ports, channel, pc);
                  streamMidiProgram(channel, pc);
                }
              }
              break;
            case 22:
              {
                // control toggle
                uint8_t cc = valueTyper.getOutput();
                if(cc <= 127){
                  uint8_t channel = settings.getTyperChannel();
                  channel = BMC_TO_MIDI_CHANNEL(channel);
                  uint8_t val = midi.toggleCC(e.ports, channel, cc);
                  midi.sendControlChange(e.ports, channel, cc, val);
                  streamMidiControl(channel, cc, val);
                }
              }
              break;
          }
        }
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[16] = "";
        uint8_t cmd = byteA;
        if(bitRead(displaySettings, 3)){ // Name
          if(cmd < 10){
            sprintf(str, "%u", cmd);
          } else {
            switch(cmd){
              case 10: strcpy(str, "CLEAR"); break;
              case 11: strcpy(str, "<"); break;
              case 12: strcpy(str, ">"); break;
              case 13: strcpy(str, "DEC"); break;
              case 14: strcpy(str, "INC"); break;
              case 15: strcpy(str, "CUSTOM"); break;
              case 16: strcpy(str, "LAYER"); break;
  #if BMC_MAX_PRESETS > 0
              case 17: strcpy(str, "PRESET"); break;
  #endif
  #if defined(BMC_USE_FAS)
              case 18: strcpy(str, "FAS PRESET"); break;

              case 19:
              case 20: strcpy(str, "FAS SCENE"); break;
  #endif
              case 21: strcpy(str, "PROGRAM"); break;
              case 22: strcpy(str, "CONTROL"); break;
            }
          }
        } else {
          sprintf(str, "%03u", valueTyper.getOutput());
          display.setSelChar(deviceIndex, isOled, valueTyper.getSelChar());
        }
        display.renderText(deviceIndex, isOled, e.type, str, "TYPER");
        
#endif
      }
      break;
#ifdef BMC_MIDI_BLE_ENABLED
    case BMC_EVENT_TYPE_SYSTEM_BLE_DISCONNECT:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        midi.disconnectBLE();
      } else {
        if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
          display.renderText(deviceIndex, isOled, e.type, "BLE","STATUS",globals.bleConnected());
#endif
        } else {
          return globals.bleConnected();
        }
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_STOPWATCH:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        stopwatchCmd(byteA, byteB, byteC, byteD);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return (stopwatch.getState() == 1) ? 100 : 0;

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[13] = "";
        sprintf(str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
        display.renderText(deviceIndex, isOled, e.type, str, "STOPWATCH");
#endif
      } else {
        return (stopwatch.getState() == 1);

      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_LFO:
      if(byteA >= BMC_MAX_LFO){
        return 0;
      }
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(byteB==0){
          lfo[byteA].toggle();
        } else if(byteB==1){
          lfo[byteA].start();
        } else if(byteB==2){
          lfo[byteA].stop();
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[10] = "";
        sprintf(str, "LFO %u", byteA+globals.offset);
        display.renderText(deviceIndex, isOled, e.type, str, "", lfo[byteA].isEnabled());
#endif
      } else {
        return lfo[byteA].isEnabled();
      }
      break;
    // SKETCH BYTES
    case BMC_EVENT_TYPE_SKETCH_BYTE:
#if BMC_MAX_SKETCH_BYTES > 0
      if(byteA >= BMC_MAX_SKETCH_BYTES){
        return 0;
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
        uint8_t tmp = getSketchByte(byteA);
        if(scroll.enabled){
          BMCScroller <uint8_t> scroller(data.min, data.max);
          tmp = scroller.scroll(data.step, scroll.direction, scroll.endless, tmp, data.min, data.max);
        } else {
          tmp = constrain(byteB, data.min, data.max);
        }
        streamToSketch(BMC_DEVICE_ID_SKETCH_BYTE, tmp, data.name);
        setSketchByte(byteA, tmp);
        if(callback.storeUpdated){
          callback.storeUpdated();
        }
      // } else if(group==BMC_DEVICE_GROUP_ENCODER){
      //   BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
      //   uint8_t tmp = getSketchByte(byteA);
      //   BMCScroller <uint8_t> scroller(data.min, data.max);
      //   tmp = scroller.scroll(data.step, scroll.direction, scroll.endless, tmp, data.min, data.max);
      //   streamToSketch(BMC_DEVICE_ID_SKETCH_BYTE, tmp, data.name);
      //   setSketchByte(byteA, tmp);
      //   if(callback.storeUpdated){
      //     callback.storeUpdated();
      //   }
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[26] = "";
        BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
        BMCTools::getSketchByteFormat(str, byteA, getSketchByte(byteA));
        // getSketchByteFormat(char* str, uint8_t n, uint8_t value)
        display.renderText(deviceIndex, isOled, e.type, str, data.name);
#endif
      }
#endif
      break;

    // LAYERS
    case BMC_EVENT_TYPE_LAYER:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          scrollLayer(scroll.direction, scroll.endless, scroll.amount);
        } else {
          setLayer(byteA);
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        scrollLayer(scroll.direction, scroll.endless, scroll.amount);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
        
#if defined(BMC_HAS_DISPLAY)
        uint16_t selLayer = (event & 0x3FFF);
        bool highlight = layer==(event & 0x3FFF);
        if(bitRead(displaySettings, 2)){ // selected
          selLayer = layer;
          highlight = false;
        }
        if(selLayer < BMC_MAX_LAYERS){
          if(bitRead(displaySettings, 3)){ // name
            bmcStoreName t = globals.getDeviceName(store.layers[selLayer].events[0].name);
            if(BMC_STR_MATCH(t.name, "")){
              sprintf(t.name, "L %u", selLayer+globals.offset);
            }
            display.renderText(deviceIndex, isOled, e.type, t.name, "LAYER");
          } else {
            display.renderNumber(deviceIndex, isOled, e.type, selLayer+globals.offset, "%u", "LAYER", highlight);
          }
        }
#endif        
      } else {
        return (event & 0x3FFF) == layer;
      }
      break;
    // PRESETS
#if BMC_MAX_PRESETS > 0
    case BMC_EVENT_TYPE_PRESET:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          presets.scrollPreset(scroll.direction, scroll.endless, scroll.amount);
        } else {
          presets.setPreset(byteA);
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        presets.scrollPreset(scroll.direction, scroll.endless, scroll.amount);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(presets.get(), 0, BMC_MAX_PRESETS_PER_BANK-1, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){

#if defined(BMC_HAS_DISPLAY)
        if(byteA < BMC_MAX_PRESETS){
          bmcStoreName t;
          if(bitRead(displaySettings, 3)){ // name
            t = (bitRead(displaySettings, 2)) ? presets.getName() : presets.getName(byteA);
          } else {
            t = (bitRead(displaySettings, 2)) ? presets.getPresetStr() : presets.getPresetStr(byteA);
          }
          display.renderText(deviceIndex, isOled, e.type, t.name, "PRESET");
        }
#endif
      } else {
        return byteA == presets.get();
      }
      break;
    case BMC_EVENT_TYPE_BANK:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          presets.scrollBank(scroll.direction, scroll.endless, scroll.amount);
        } else {
          presets.setBank(byteA);
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        presets.scrollBank(scroll.direction, scroll.endless, scroll.amount);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(presets.getBank(), 0, BMC_MAX_PRESET_BANKS-1, 0, 100);
        
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = (bitRead(displaySettings, 2)) ? presets.getBankStr() : presets.getBankStr(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name, "BANK");
#endif
      } else {
        return byteA == presets.getBank();

      }
      break;
#endif

#if BMC_MAX_SETLISTS > 0
    // SETLISTS
    case BMC_EVENT_TYPE_SETLIST:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          setLists.scrollSet(scroll.direction, scroll.endless, scroll.amount);
        } else {
          setLists.set(byteA);
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        setLists.scrollSet(scroll.direction, scroll.endless, scroll.amount);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
        
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(byteA < BMC_MAX_SETLISTS){
          bmcStoreName t;
          if(bitRead(displaySettings, 3)){ // display name
            t = (bitRead(displaySettings, 2)) ? setLists.getSetName() : setLists.getSetName(byteA);
          } else { // display number
            t = (bitRead(displaySettings, 2)) ? setLists.getSetStr() : setLists.getSetStr(byteA);
          }
          display.renderText(deviceIndex, isOled, e.type, t.name, "SET");
        }
#endif
      } else {
        return (byteA == setLists.get());
      }
      break;
    case BMC_EVENT_TYPE_SONG:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          setLists.scrollSong(scroll.direction, scroll.endless, scroll.amount);
        } else {
          setLists.setSong(byteA);
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        setLists.scrollSong(scroll.direction, scroll.endless, scroll.amount);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
        
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(byteA < BMC_MAX_SETLISTS_SONGS){
          bmcStoreName t;
          if(bitRead(displaySettings, 3)){ // display name
            t = (bitRead(displaySettings, 2)) ? setLists.getSongName() : setLists.getSongName(byteA);
          } else { // display number
            t = (bitRead(displaySettings, 2)) ? setLists.getSongStr() : setLists.getSongStr(byteA);
          }
          display.renderText(deviceIndex, isOled, e.type, t.name, "SONG");
        }
#endif
      } else {
        return (byteA == setLists.getSong());

      }
      break;
    case BMC_EVENT_TYPE_PART:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          setLists.scrollPart(scroll.direction, scroll.endless, scroll.amount);
        } else {
          setLists.setPart(byteA);
        }
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        setLists.scrollPart(scroll.direction, scroll.endless, scroll.amount);
        
      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(byteA < BMC_MAX_SETLISTS_SONG_PARTS){
          bmcStoreName t;
          if(bitRead(displaySettings, 3)){ // display name
            t = (bitRead(displaySettings, 2)) ? setLists.getPartName() : setLists.getPartName(byteA);
          } else { // display number
            t = (bitRead(displaySettings, 2)) ? setLists.getPartStr() : setLists.getPartStr(byteA);
          }
          display.renderText(deviceIndex, isOled, e.type, t.name, "PART");
        }
#endif
      } else {
        return (byteA == setLists.getPart());
      }
      break;
#endif

#if BMC_MAX_PIXEL_PROGRAMS > 0
    // PIXELS
    case BMC_EVENT_TYPE_PIXEL_PROGRAM:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        if(scroll.enabled){
          pixelPrograms.scroll(scroll.direction, scroll.endless);
        } else {
          pixelPrograms.setProgram(byteA);
        }

      } else if(deviceId==BMC_DEVICE_ID_PIXEL || deviceId==BMC_DEVICE_ID_GLOBAL_PIXEL){
        // nothing happens here
        // event is handled withint BMC.hardware.pixels.cpp
      }
      break;
    case BMC_EVENT_TYPE_PIXEL_PROGRAM_BLACKOUT:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        pixelPrograms.toggleBlackout();
      } 
      break;
#endif
    // HARDWARE
#if BMC_MAX_AUX_JACKS > 0
    case BMC_EVENT_TYPE_AUX_JACK:
      if(byteA >= BMC_MAX_AUX_JACKS){
        return 0;
      }
      if(group == BMC_DEVICE_GROUP_LED){
        if(byteB == 0){
          return auxJacks[byteA].isConnected();
        } else if(byteB == 1){
          return auxJacks[byteA].isPotMode();
        } else if(byteB == 2){
          return !auxJacks[byteA].isPotMode();
        }
        
      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        if(byteB == 0){
          return auxJacks[byteA].isConnected() ? 100 : 0;
        } else if(byteB == 1){
          return auxJacks[byteA].isPotMode() ? 100 : 0;
        } else if(byteB == 2){
          return !auxJacks[byteA].isPotMode() ? 100 : 0;
        }

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[13] = "";
        if(auxJacks[byteA].isPotMode()){
          sprintf(str, "Exp %u", byteA+globals.offset);
        } else {
          sprintf(str, "Ctrl %u", byteA+globals.offset);
        }
        display.renderText(deviceIndex, isOled, e.type, str, "AUX JACK", auxJacks[byteA].isConnected());
#endif
      }
      break;
#endif

#if defined(BMC_HAS_DISPLAY)
    case BMC_EVENT_TYPE_DEVICE_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
        bmcStoreName t;
        editor.getDeviceNameText(byteA, BMC_GET_BYTE_2(1, event), t.name);
        display.renderText(deviceIndex, isOled, e.type, t.name, "NAME");
      }
      break;
#endif
    // EXTERNAL SYNC
#ifdef BMC_USE_DAW_LC
    case BMC_EVENT_TYPE_DAW_COMMAND:
      // handled by BMC::handleButton
      if(group == BMC_DEVICE_GROUP_BUTTON){

        sync.daw.sendButtonCommand(byteA, byteB, false);

      } else if(group == BMC_DEVICE_GROUP_LED){
        
        return sync.daw.getLedState(byteA, byteB);

      } else if(group == BMC_DEVICE_GROUP_ENCODER){

        sync.daw.sendEncoderScrolling(byteA, byteB, scroll.direction, scroll.amount);

      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){

        if(byteA == BMC_DAW_CMD_VPOT_SELECT || (byteA >= BMC_DAW_CMD_VPOT_LED_1 && byteA <= BMC_DAW_CMD_VPOT_LED_CENTER)){
          return sync.daw.getVPotValuePercentage(byteB);
        } else if(byteA >= BMC_DAW_CMD_METER_LED_PEAK && byteA <= BMC_DAW_CMD_METER_LED_12){
          return sync.daw.getMeterValuePercentage(byteB);
        } else if(byteA >= BMC_DAW_CMD_FADER_TOUCH){
          return sync.daw.getFaderValuePercentage(byteB);
        } else {
          return sync.daw.getLedState(byteA, byteB)>0 ? 100 : 0;
        }
      }
      break;
    case BMC_EVENT_TYPE_DAW_DISPLAY:
#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_DAW_LC)
      if(group == BMC_DEVICE_GROUP_DISPLAY){
        if(byteA==0){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.updateDawMeters();
            }
          #endif
        } else if(byteA == 1){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.updateDawChannels();
            }
          #endif
        } else if(byteA == 2){
          display.updateDawChannelInfo(byteB);
        } else if(byteA == 3){
          char str[3] = "";
          sync.daw.getTwoDigitDisplay(str);
          display.renderText(deviceIndex, isOled, e.type, str);
        }
      }
#endif
      break;
#endif

#ifdef BMC_USE_BEATBUDDY
    case BMC_EVENT_TYPE_BEATBUDDY:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          if(byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
            uint8_t s = sync.beatBuddy.getSongPart();
            if(scroll.direction){
              if(s >= 124){
                s = 0;
              } else {
                s++;
              }
            } else {
              if(s == 0){
                s = 124;
              } else {
                s--;
              }
            }
            sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_TRANS_PART_1+s);
            return 0;
          }
        }
        sync.beatBuddy.sendCommand(byteA, byteB);
        
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        if(byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          uint8_t s = sync.beatBuddy.getSongPart();
          if(scroll.direction){
            if(s >= 124){
              s = 0;
            } else {
              s++;
            }
          } else {
            if(s == 0){
              s = 124;
            } else {
              s--;
            }
          }
          sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_TRANS_PART_1+s);
          return 0;
        }
        switch(byteA){
          case BMC_BEATBUDDY_CMD_BPM_DEC:
          case BMC_BEATBUDDY_CMD_BPM_INC:
            sync.beatBuddy.tempoControl(scroll.amount, scroll.direction);
            break;
          case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN:
          case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:
            sync.beatBuddy.sendCommand((scroll.direction)?BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN);
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_LED){
        if(byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          return sync.beatBuddy.isSongPart(byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1);
        }
        switch(byteA){
          case BMC_BEATBUDDY_CMD_START:
          case BMC_BEATBUDDY_CMD_STOP:
            return sync.beatBuddy.isPlaying();
            break;
          case BMC_BEATBUDDY_CMD_NORMAL_TIME:
            return !sync.beatBuddy.isHalfTime() && !sync.beatBuddy.isDoubleTime();
            break;
          case BMC_BEATBUDDY_CMD_HALF_TIME:
          case BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE:
            return sync.beatBuddy.isHalfTime();
            break;
          case BMC_BEATBUDDY_CMD_DOUBLE_TIME:
          case BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE:
            return sync.beatBuddy.isDoubleTime();
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_POT){
        switch(byteA){
          case BMC_BEATBUDDY_CMD_BPM_DEC:
          case BMC_BEATBUDDY_CMD_BPM_INC:
            sync.beatBuddy.tempoExpression(value);
            break;
          case BMC_BEATBUDDY_CMD_MIX_VOL:
            sync.beatBuddy.mixVol(map(value, 0, 127, 0, 100));
            break;
          case BMC_BEATBUDDY_CMD_HP_VOL:
            sync.beatBuddy.hpVol(map(value, 0, 127, 0, 100));
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[24] = "";
        bool highlight = false;
        if(byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          if(bitRead(displaySettings, 2)){ // selected
            uint8_t s = sync.beatBuddy.getSongPart();
            sprintf(str,"PT %u", s+globals.offset);
            highlight = true;
          } else {
            sprintf(str,"PT %u",(byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1)+globals.offset);
            highlight = sync.beatBuddy.isSongPart(byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1);
          }
        } else {
          switch(byteA){
            case BMC_BEATBUDDY_CMD_START:
              strcpy(str, "Start");
              highlight = sync.beatBuddy.isPlaying();
              break;
            case BMC_BEATBUDDY_CMD_STOP:
              strcpy(str, "Stop");
              highlight = !sync.beatBuddy.isPlaying();
              break;
            case BMC_BEATBUDDY_CMD_BPM_DEC:
              strcpy(str, "BPM Dec");
              break;
            case BMC_BEATBUDDY_CMD_BPM_INC:
              strcpy(str, "BPM Inc");
              break;
            case BMC_BEATBUDDY_CMD_PAUSE:
              strcpy(str, "Pause");
              break;
            case BMC_BEATBUDDY_CMD_UNPAUSE:
              strcpy(str, "Unpause");
              break;
            case BMC_BEATBUDDY_CMD_PAUSE_TOGGLE:
              strcpy(str, "Pause Toggle");
              break;
            case BMC_BEATBUDDY_CMD_DRUM_FILL:
              strcpy(str, "Drum Fill");
              break;
            case BMC_BEATBUDDY_CMD_TAP:
              strcpy(str, "Tap");
              break;
            case BMC_BEATBUDDY_CMD_OUTRO:
              strcpy(str, "Outtro");
              break;
            case BMC_BEATBUDDY_CMD_MIX_VOL:
              strcpy(str, "Mix Vol");
              break;
            case BMC_BEATBUDDY_CMD_HP_VOL:
              strcpy(str, "HP Vol");
              break;
            case BMC_BEATBUDDY_CMD_ACCENT_HIT:
              strcpy(str, "Accent Hit");
              break;
            case BMC_BEATBUDDY_CMD_DRUMSET_SELECT:
              strcpy(str, "Drumset Sel");
              break;
            case BMC_BEATBUDDY_CMD_NORMAL_TIME:
              strcpy(str, "Normal Time");
              highlight = !sync.beatBuddy.isHalfTime() && !sync.beatBuddy.isDoubleTime();
              break;
            case BMC_BEATBUDDY_CMD_HALF_TIME:
              highlight = sync.beatBuddy.isHalfTime();
              strcpy(str, "Half Time");
              break;
            case BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE:
              highlight = sync.beatBuddy.isHalfTime();
              strcpy(str, "Half Time Tggle");
              break;
            case BMC_BEATBUDDY_CMD_DOUBLE_TIME:
              highlight = sync.beatBuddy.isDoubleTime();
              strcpy(str, "Double Time");
              break;
            case BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE:
              highlight = sync.beatBuddy.isDoubleTime();
              strcpy(str, "Dble Time Tggle");
              break;
            case BMC_BEATBUDDY_CMD_FOLDER_ENTER:
              strcpy(str, "Folder Enter");
              break;
            case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN:
              strcpy(str, "Song Scroll Down");
              break;
            case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:
              strcpy(str, "Song Scroll Up");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_END:
              strcpy(str, "Trans End");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_PREV:
              strcpy(str, "Trans Prev");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_NEXT:
              strcpy(str, "Trans Next");
              break;
          }
        }
        display.renderText(deviceIndex, isOled, e.type, str, "BEATBUDDY", highlight); 
#endif
      }
      break;
    case BMC_EVENT_TYPE_BEATBUDDY_BPM:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        if(scroll.enabled){
          sync.beatBuddy.tempoControl(scroll.amount, scroll.direction);
        } else {
          sync.beatBuddy.tempo(event & 0x1FF);
        }

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderText(deviceIndex, isOled, e.type, "BB BPM", "BEATBUDDY"); 
#endif
      }
      break;
    // case BMC_EVENT_TYPE_BEATBUDDY_FOLDER:
    //   if(group == BMC_DEVICE_GROUP_BUTTON){
    //     sync.beatBuddy.songSelect(event & 0x3FFF, byteB);
    //   }
    //   break;
#endif
#ifdef BMC_USE_FAS
    case BMC_EVENT_TYPE_FAS:
      if(group == BMC_DEVICE_GROUP_LED){
        switch(byteA){
          case BMC_FAS_CMD_CONNECTION:          return sync.fas.connected();
          case BMC_FAS_CMD_TUNER_ON:            return sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_OFF:           return !sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_TOGGLE:        return sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_IN_TUNE:       return sync.fas.tunerInTune();
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:   return sync.fas.tunerOutOfTune();
          case BMC_FAS_CMD_TUNER_FLAT:          return sync.fas.tunerFlat();
          case BMC_FAS_CMD_TUNER_FLATTER:       return sync.fas.tunerFlatter();
          case BMC_FAS_CMD_TUNER_FLATTEST:      return sync.fas.tunerFlattest();
          case BMC_FAS_CMD_TUNER_SHARP:         return sync.fas.tunerSharp();
          case BMC_FAS_CMD_TUNER_SHARPER:       return sync.fas.tunerSharper();
          case BMC_FAS_CMD_TUNER_SHARPEST:      return sync.fas.tunerSharpest();
          case BMC_FAS_CMD_LOOPER_PLAY:         return sync.fas.looperPlaying();
          case BMC_FAS_CMD_LOOPER_REC:          return sync.fas.looperRecording();
          case BMC_FAS_CMD_LOOPER_DUB:          return sync.fas.looperDubbing();
          case BMC_FAS_CMD_LOOPER_REV:          return sync.fas.looperReversed();
          case BMC_FAS_CMD_LOOPER_HALF:         return sync.fas.looperHalf();
          case BMC_FAS_CMD_LOOPER_UNDO:         return 0; // looper undo
          case BMC_FAS_CMD_TAP:                 return 0; // tap tempo
        }
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        switch(byteA){
          case BMC_FAS_CMD_CONNECTION:break;
          case BMC_FAS_CMD_TUNER_ON:
            sync.fas.tunerOn();
            break;
          case BMC_FAS_CMD_TUNER_OFF:
            sync.fas.tunerOff();
            break;
          case BMC_FAS_CMD_TUNER_TOGGLE:
          case BMC_FAS_CMD_TUNER_IN_TUNE:
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            sync.fas.toggleTuner();
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_BUTTON){
        switch(byteA){
          case BMC_FAS_CMD_CONNECTION:
            if(sync.fas.connected()){
              sync.fas.disconnect();
            } else {
              sync.fas.connect();
            }
            break;
          case BMC_FAS_CMD_TUNER_ON:
            sync.fas.tunerOn();
            break;
          case BMC_FAS_CMD_TUNER_OFF:
            sync.fas.tunerOff();
            break;
          case BMC_FAS_CMD_TUNER_TOGGLE:
          case BMC_FAS_CMD_TUNER_IN_TUNE:
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            sync.fas.toggleTuner();
            break;
          case BMC_FAS_CMD_LOOPER_PLAY:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_PLAY); break;
          case BMC_FAS_CMD_LOOPER_REC:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_RECORD); break;
          case BMC_FAS_CMD_LOOPER_DUB:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_OVERDUB); break;
          case BMC_FAS_CMD_LOOPER_REV:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_REVERSE); break;
          case BMC_FAS_CMD_LOOPER_HALF:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_HALF); break;
          case BMC_FAS_CMD_LOOPER_UNDO:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_UNDO); break;
          case BMC_FAS_CMD_TAP:  sync.fas.tapTempo(); break;
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        switch(byteA){
          case BMC_FAS_CMD_CONNECTION:
            display.renderText(deviceIndex, isOled, e.type, "FAS", "", sync.fas.connected());
            break;
          case BMC_FAS_CMD_TUNER_ON:
          case BMC_FAS_CMD_TUNER_OFF:
          case BMC_FAS_CMD_TUNER_TOGGLE:
          case BMC_FAS_CMD_TUNER_IN_TUNE:
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            display.updateFasTuner();
            break;
          case BMC_FAS_CMD_LOOPER_PLAY:
            display.renderText(deviceIndex, isOled, e.type, "PLAY","LOOPER",sync.fas.looperPlaying());
            break;
          case BMC_FAS_CMD_LOOPER_REC:
            display.renderText(deviceIndex, isOled, e.type, "REC","LOOPER",sync.fas.looperRecording());
            break;
          case BMC_FAS_CMD_LOOPER_DUB:
            display.renderText(deviceIndex, isOled, e.type, "DUB","LOOPER",sync.fas.looperDubbing());
            break;
          case BMC_FAS_CMD_LOOPER_REV:
            display.renderText(deviceIndex, isOled, e.type, "REVERSE","LOOPER",sync.fas.looperReversed());
            break;
          case BMC_FAS_CMD_LOOPER_HALF:
            display.renderText(deviceIndex, isOled, e.type, "HALF","LOOPER",sync.fas.looperHalf());
            break;
          case BMC_FAS_CMD_LOOPER_UNDO:
            display.renderText(deviceIndex, isOled, e.type, "UNDO","LOOPER");
            break;
          case BMC_FAS_CMD_TAP:
            display.renderText(deviceIndex, isOled, e.type, "TAP");
            break;
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_FAS_SCENE:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        if(byteB > 0){
          if(sync.fas.getSceneNumber() != byteA){
            sync.fas.setSceneNumber(byteA, bitRead(event, 16));
          } else {
            sync.fas.setSceneNumber(byteB-1, bitRead(event, 16));
          }
        } else {
          sync.fas.setSceneNumber(byteA, bitRead(event, 16));
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        sync.fas.sceneScroll(scroll.direction, scroll.endless, bitRead(event, 16), 0, 7);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[12] = "";
        bool highlight = sync.fas.getSceneNumber() == byteA;
        // display the selected scene number
        if(bitRead(displaySettings, 2)){ // selected
          highlight = true;
          sprintf(str, "S %u", (sync.fas.getSceneNumber()+globals.offset));
        } else {
          
          sprintf(str, "S %u", (byteA+globals.offset));
        }
        display.renderText(deviceIndex, isOled, e.type, str, "SCENE", highlight);
#endif
      } else {
        return sync.fas.getSceneNumber() == byteA;
      }

      break;
    case BMC_EVENT_TYPE_FAS_PRESET:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        sync.fas.setPreset(event & 0x3FF);
        
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        sync.fas.presetScroll(scroll.direction, scroll.endless, 0, sync.fas.getMaxPresets());

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[32] = "";
        uint16_t p1 = BMC_GET_BYTE_2(0, event) & 0x3FF;
        uint16_t p2 = BMC_GET_BYTE_2(2, event) & 0x3FF;
        bool highlight = sync.fas.getPresetNumber() == p1;
        if(p2 > 0){
          // if p2 is more than 0 we are in toggle mode
          highlight = false;
          uint16_t current = sync.fas.getPresetNumber();
          sprintf(str, "P %u", ((current != p1) ? p1 : (p2-1))+globals.offset);
        } else {
          if(bitRead(displaySettings, 2)){ // selected
            highlight = true;
            if(bitRead(displaySettings, 3)){ // name
              sync.fas.getPresetName(str);
            } else {
              sprintf(str, "P %u", sync.fas.getPresetNumber() + globals.offset);
            }
          } else {
            sprintf(str, "P %u", (uint16_t)(p1 + globals.offset));
          }
        }
        display.renderText(deviceIndex, isOled, e.type, str, "PRESET", highlight);
#endif
      } else {
        return sync.fas.getPresetNumber()==(event & 0x3FF);
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(!sync.fas.connected()){
          return 0;
        }
        switch(byteA){
          case 0:
            sync.fas.setBlockBypass(byteB); // bypass block
            break;
          case 1:
            sync.fas.setBlockEngage(byteB); // engage block
            break;
          case 2:
            sync.fas.toggleBlockState(byteB); // toggle bypass block
            break;
          case 3:
            sync.fas.setBlockX(byteB); // set block to X
            break;
          case 4:
            sync.fas.setBlockY(byteB); // set block to Y
            break;
          case 5:
            sync.fas.toggleBlockXY(byteB); // toggle XY block
            break;
        }
        return 1;
      } else if(group == BMC_DEVICE_GROUP_LED){
        switch(byteA){
          case 0:
            return sync.fas.isBlockBypassed(byteB); // block bypass state
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(byteB); // block bypass state
          case 3:
            return sync.fas.isBlockX(byteB); // block x/y state
          case 4:
          case 5:
            return sync.fas.isBlockY(byteB); // block x/y state 
        }
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        switch(byteA){
          case 0:
            return sync.fas.isBlockBypassed(byteB) ? 100 : 0; // block bypass state
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(byteB) ? 100 : 0; // block bypass state
          case 3:
            return sync.fas.isBlockX(byteB) ? 100 : 0; // block x/y state
          case 4:
          case 5:
            return sync.fas.isBlockY(byteB) ? 100 : 0; // block x/y state 
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
        if(!sync.fas.connected()){
          return 0;
        }
        bool blockState = sync.fas.isBlockEngaged(byteB);
        char blockName[5] = "";
        char blockXY[5] = "";
        char str[10] = "";
        
        sync.fas.getBlockName(byteB, blockName);
        sprintf(blockXY, "%s", sync.fas.isBlockX(byteB)?"x":"y");
        sprintf(str, "%s %s", blockName, blockXY);
        display.renderText(deviceIndex, isOled, e.type, str, "BLOCK", blockState);
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK_PARAM:
      break;
#endif
#ifdef BMC_USE_HELIX
    case BMC_EVENT_TYPE_HELIX:
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(scroll.enabled){
          if(byteC > 0){
            sync.helix.snapshotScroll(scroll.direction, byteB, byteC);
          } else {
            sync.helix.snapshotScroll(scroll.direction);
          }
        } else {
          if(byteC > 0){
            sync.helix.command(BMC_HELIX_CMD_SNAPSHOT_TOGGLE, byteB, byteC);
          } else {
            sync.helix.command(byteA, byteB, byteC);
          }
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[12] = "";
        if(bitRead(displaySettings, 3)){ // display name
          switch(byteA){
            case BMC_HELIX_CMD_TAP:
              strcpy(str, "HX TAP");
              break;
            case BMC_HELIX_CMD_TUNER:
              strcpy(str, "HX TUNNER");
              break;
            case BMC_HELIX_CMD_SNAPSHOT:
              sprintf(str, "SN %u", byteB+globals.offset);
              break;
            case BMC_HELIX_CMD_SNAPSHOT_TOGGLE:
              sprintf(str, "SN %u %u", byteB+globals.offset, byteC+globals.offset);
              break;
          }
        } else { // display number
          if(bitRead(displaySettings, 2)){// selected
            sprintf(str, "SN %u", sync.helix.getSnapshot()+globals.offset);
          } else {
            sprintf(str, "SN %u", byteB+globals.offset);
          }
        }
        display.renderText(deviceIndex, isOled, e.type, str, "HELIX", sync.helix.isSnapshot(byteB));
#endif
      } else {
        return sync.helix.isSnapshot(byteB);
      }

      
      break;
#endif
#if BMC_MAX_CUSTOM_SYSEX > 0
    case BMC_EVENT_TYPE_CUSTOM_SYSEX:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        // byteA = send mode, 0, 1 or 2
        // byteB = index of the 1st custom sysex item to send
        // byteC = index of the 2nd custom sysex item to send
        customSysEx.send((byteA & 0x03), e.ports, byteB, byteC);
      }
      break;
#endif
    case BMC_EVENT_TYPE_CUSTOM:
      if(callback.customActivity){
        // this function only works for hardware except relays and displays
        if(group == BMC_DEVICE_GROUP_BUTTON){
          // dat1 has the press type
          // dat2 is unused
          callback.customActivity(deviceId, deviceIndex, byteA, dat, 0);
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          // dat1 has the direction
          // dat2 has the number of ticks
          callback.customActivity(deviceId, deviceIndex, byteA, bitRead(value, 7), value & 0x7F);
        } else if(group == BMC_DEVICE_GROUP_POT){
          // dat1 has the pot value
          callback.customActivity(deviceId, deviceIndex, byteA, value, 0);
        } else if(group == BMC_DEVICE_GROUP_LED){
          // for rgb pixles dat1 is the color index, 0=r, 1=g, 2=b
          // same applies to bi and tri leds, where dat is the index of the color
          // for leds and pixels this function must return true or false, where
          // true will turn (and keep) the led on and false will turn it off
          return callback.customActivity(deviceId, deviceIndex, byteA, dat, 0);
        }
      }
      break;
  }
  return BMC_OFF_LED_EVENT;
}
void BMC::handleClockLeds(){

#if BMC_MAX_LEDS > 0
  for(uint8_t index = 0; index < BMC_MAX_LEDS; index++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].leds[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(data.type)){
      // last 4 bits are always the color
      leds[index].pulse();
    }

    //bmcStoreLed& item = store.layers[layer].leds[index];
    //if(BMCTools::isMidiClockLedEvent(item.event)){
      //leds[index].pulse();
    //}
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint8_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    bmcStoreDevice <1, 1>& device = store.global.leds[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(data.type)){
      // last 4 bits are always the color
      globalLeds[index].pulse();
    }
  }
#endif


#if BMC_MAX_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_PIXELS; index++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixels[index];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(data.type)){
      // last 4 bits are always the color
      pixels.pulse(index, device.settings[0]);
    }
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_RGB_PIXELS; index++){

    bmcStoreDevice <1, 3>& device = store.layers[layer].rgbPixels[index];
    for(uint8_t e = 0; e < 3; e++){
      bmcStoreEvent data = globals.getDeviceEventType(device.events[e]);
      // first bit is always the "blink" state
      if(BMCTools::isMidiClockLedEvent(data.type)){
        // last 4 bits are always the color
        pixels.pulseRgb(index, e);
      }
    }
  }
#endif

}
