/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

uint8_t BMC::processEvent(uint8_t group, uint8_t deviceId, 
                          uint16_t deviceIndex, uint16_t eventIndex, 
                          uint8_t value, uint8_t dat){
  // Process Events
  
  
  BMCDataContainer data;
  data.index = deviceIndex;
  data.offset = globals.offset;
  data.useOffset = true;

#if defined(BMC_HAS_DISPLAY)
  // Check if we should render a display's name
  if(eventIndex == 0 && group == BMC_DEVICE_GROUP_DISPLAY){
    data.oled = (deviceId == BMC_DEVICE_ID_OLED);
    if(settings.getDisplayNames()){
      #if BMC_MAX_OLED > 0
        if(data.oled && store.layers[layer].oled[deviceIndex].name == 0){
          return false;
        }
      #endif
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(!data.oled && store.layers[layer].ili[deviceIndex].name == 0){
          return false;
        }
      #endif
      bmcStoreName t;
      editor.getDeviceNameText(deviceId, deviceIndex, t.name);
      data.crc = 254;
      strcpy(data.str, t.name);
      display.renderText(data);
      // display.renderText(deviceIndex, data.oled, 254, t.name, "");
    }
    return false;
  }
#endif

  if(eventIndex == 0 || eventIndex > BMC_MAX_EVENTS_LIBRARY){
    return false;
  }
  
  bmcStoreEvent& e = store.global.events[eventIndex-1];
  if(e.type == BMC_NONE){
    return false;
  }
  
  uint32_t event = e.event;

  data.type = e.type;
  data.byteA = BMC_GET_BYTE(0, event);
  data.byteB = BMC_GET_BYTE(1, event);
  data.byteC = BMC_GET_BYTE(2, event);
  data.byteD = BMC_GET_BYTE(3, event);
  data.setScroll(e.settings, value, group==BMC_DEVICE_GROUP_ENCODER);

  // uint8_t data.byteA = BMC_GET_BYTE(0, event);
  // uint8_t data.byteB = BMC_GET_BYTE(1, event);
  // uint8_t data.byteC = BMC_GET_BYTE(2, event);
  // uint8_t data.byteD = BMC_GET_BYTE(3, event);

  // BMCEventScrollData scroll(e.settings, value, group==BMC_DEVICE_GROUP_ENCODER);

#if defined(BMC_HAS_DISPLAY)
  if(group == BMC_DEVICE_GROUP_DISPLAY){
    data.oled = (deviceId == BMC_DEVICE_ID_OLED);
#if BMC_MAX_OLED > 0
    if(data.oled){
      data.settings = store.layers[layer].oled[deviceIndex].settings[0]+0;
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(!data.oled){
      data.settings = store.layers[layer].ili[deviceIndex].settings[0]+0;
    }
#endif
  }
#endif

#if BMC_MAX_ENCODERS > 0
    if(deviceId == BMC_DEVICE_ID_ENCODER){
      data.setNoScroll(bitRead(store.layers[layer].encoders[deviceIndex].settings[0], 0));
    }
#endif
#if BMC_MAX_GLOBAL_ENCODERS > 0
    if(deviceId == BMC_DEVICE_ID_GLOBAL_ENCODER){
      data.setNoScroll(bitRead(store.global.encoders[deviceIndex].settings[0], 0));
    }
#endif

  switch(data.type){
    case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
    {
      uint8_t currentPC = midi.getLocalProgram(data.getChannel());
      uint8_t outVal = data.setMinMax(currentPC, 0, 127, data.byteB, data.byteC);
      
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        // if scroll is enabled or if it's an encoder use scrolling by default
        if(data.scrollEnabled()){
          outVal = midi.scrollPC(e.ports, data.getChannel(), data.scrollAmount(), data.scrollDirection(), data.scrollWrap(), data.min, data.max);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, data.getChannel(), outVal);
        } else {
          midi.sendProgramChange(e.ports, data.getChannel(), outVal);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, data.getChannel(), outVal);
        }

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendProgramChange(e.ports, data.getChannel(), value);
        streamMidi(BMC_MIDI_PROGRAM_CHANGE, data.getChannel(), value);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(currentPC, 0, 127, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        strcpy(data.label, "PC");
        if(data.useSelected()){
          data.byteB = currentPC;
        }
        display.renderProgramChangeValue(data);
#endif

      } else {
        return currentPC == (data.byteB & 0x7F);
      }
    }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
    {
      data.useOffset = false;
      uint8_t currentCC = midi.getLocalControl(data.getChannel(), data.byteB);
      uint8_t outVal = data.setMinMax(currentCC, 0, 127, data.byteC, data.byteD);


      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(data.scrollEnabled()){
          outVal = midi.scrollCC(e.ports, data.getChannel(), data.byteB, data.scrollAmount(), data.scrollDirection(), data.scrollWrap(), data.min, data.max);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, outVal);
        } else {
          midi.sendControlChange(e.ports, data.getChannel(), data.byteB, outVal);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, outVal);
        }

      } else if(group==BMC_DEVICE_GROUP_POT){
        midi.sendControlChange(e.ports, data.getChannel(), data.byteB, value);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, value);

      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(currentCC, 0, 127, 0, 100);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        sprintf(data.label, "CC#%u", data.byteB);
        if(data.useSelected()){
          data.byteC = currentCC;
        }
        display.renderControlChangeValue(data);
#endif

      } else {
        return currentCC == (data.byteC & 0x7F);
      }
    }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      {
        data.useOffset = false;
        if(group==BMC_DEVICE_GROUP_BUTTON){
          midi.sendNoteOn(e.ports, data.getChannel(), data.byteB, data.byteC);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, data.byteC);

        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendNoteOn(e.ports, data.getChannel(), data.byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, value);

        } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(data.byteC, 0, 127, 0, 100);

        } else if(group==BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
        // display.renderNoteValue(deviceIndex, data.oled, data.type, data.getChannel(), data.byteB, data.byteC, false);
        display.renderNoteValue(data);
  #endif
        }
      }
      
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
      {
        data.useOffset = false;
        if(group==BMC_DEVICE_GROUP_BUTTON){
          midi.sendNoteOff(e.ports, data.getChannel(), data.byteB, data.byteC);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, data.byteC);

        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendNoteOff(e.ports, data.getChannel(), data.byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, data.getChannel(), data.byteB, value);

        } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(data.byteC, 0, 127, 0, 100);
          

        } else if(group==BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
        // display.renderNoteValue(deviceIndex, data.oled, data.type, data.getChannel(), data.byteB, data.byteC, false);
        display.renderNoteValue(data);
  #endif
        }
      }
      
      break;
      
    case BMC_EVENT_TYPE_MIDI_PITCH_BEND:
      if(group==BMC_DEVICE_GROUP_POT){
        uint8_t channel = data.getChannel();
        if(data.byteB==0){
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
        } else if(data.byteB==1){
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
        data.useOffset = false;
        strcpy(data.label, "PITCH");
        if(data.useMeter()){
          uint8_t pitch = midi.getLocalPitch(data.getChannel());
          uint8_t newPitch = map(pitch, 0, 127, 0, 100);
          data.value = newPitch;
          data.min = 0;
          data.min = 100;
          // display.renderSlider(deviceIndex, data.oled, data.type, newPitch, 0, 100, data.label);
          display.renderSlider(data);
        } else {
          // display.renderText(deviceIndex, data.oled, data.type, data.label);
          strcpy(data.str, data.label);
          display.renderText(data);
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH_POLY:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouchPoly(e.ports, data.getChannel(), data.byteB, data.byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH_POLY, data.getChannel(), data.byteB, data.byteC);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(data.byteC, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        data.useOffset = false;
        strcpy(data.str, "A.T. POLY");
        display.renderText(data);
        // display.renderText(deviceIndex, data.oled, data.type, "A.T. POLY");
#endif

      }
      return false;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouch(e.ports, data.getChannel(), data.byteB, data.byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH, data.getChannel(), data.byteB, data.byteC);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(data.byteC, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        data.useOffset = false;
        strcpy(data.str, "A.T.");
        display.renderText(data);
        // display.renderText(deviceIndex, data.oled, data.type, "A.T.");
#endif
      }
      return false;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_SET:
    {
      data.min = 0;
      data.max = 127;
      uint8_t outVal = data.byteB;
      if(data.byteC > 0){
        // scrolling max or toggle enabled
        if(data.max > data.min){
          data.min = data.byteB;
          data.max = data.byteC;
        }
        if(!data.scrollEnabled()){
          outVal = (programBank != data.byteB) ? data.byteB : data.byteC;
        }
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(data.scrollEnabled()){
          midiProgramBankScroll(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.byteB, data.byteC);
        } else {
          programBank = outVal;
        }
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(programBank, 0, 127, 0, 100);
        

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        data.value = (data.useSelected()) ? programBank : data.byteB;
        strcpy(data.label, "PROGRAM");
        display.renderNumber(data);
        // if(data.useSelected()){ // selected
        //   display.renderNumber(deviceIndex, data.oled, data.type, programBank, "%03u", "PROGRAM");
        // } else {
        //   display.renderNumber(deviceIndex, data.oled, data.type, data.byteB, "%03u", "PROGRAM");
        // }
#endif

      }
    }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        midiProgramBankTrigger(data.getChannel(), e.ports);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(programBank, 0, 127, 0, 100);
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "TRIGGER");
        strcpy(data.str, "TRIGGER");
        display.renderText(data);
#endif

      }
      break;
    case BMC_EVENT_TYPE_MIDI_REAL_TIME_BLOCK:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        if(data.byteA==0){
          if(data.byteB >= 2){
            midi.toggleRealTimeBlockInput();
          } else {
            midi.setRealTimeBlockInput(data.byteB==1);
          }
        } else {
          if(data.byteB>=2){
            midi.toggleRealTimeBlockOutput();
          } else {
            midi.setRealTimeBlockOutput(data.byteB==1);
          }
        }
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        if(data.byteA==0){
          return midi.getRealTimeBlockInput() ? 100 : 0;
          
        }
        return midi.getRealTimeBlockOutput() ? 100 : 0;
        
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "R.T. BLOCK");
        strcpy(data.str, "R.T. BLOCK");
        display.renderText(data);
#endif
      } else {
        if(data.byteA==0){
          return midi.getRealTimeBlockInput();
        }
        return midi.getRealTimeBlockOutput();
      }
      break;
    case BMC_EVENT_TYPE_BANK_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = data.getChannel();
        midi.sendControlChange(e.ports, channel, 0, data.byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, data.byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "LSB PGM");
        strcpy(data.str, "LSB PGM");
        display.renderText(data);
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = data.getChannel();
        midi.sendControlChange(e.ports, channel, 32, data.byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, data.byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "MSB PGM");
        strcpy(data.str, "MSB PGM");
        display.renderText(data);
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = data.getChannel();
        midi.sendControlChange(e.ports, channel, 0, data.byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, data.byteC & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "MSB LSB");
        strcpy(data.str, "MSB LSB");
        display.renderText(data);
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = data.getChannel();
        midi.sendControlChange(e.ports, channel, 0, data.byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, data.byteC & 0x7F);
        midi.sendProgramChange(e.ports, channel, data.byteD & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "MSB LSB PGM");
        strcpy(data.str, "MSB LSB PGM");
        display.renderText(data);
#endif
      }
      break;
    // SYSTEM
    case BMC_EVENT_TYPE_SYSTEM_ACTIVE_SENSE:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiActiveSense.command(data.byteA);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return midiActiveSense.active() ? 100 : 0;

      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "ACTIVE SENSE", "", midiActiveSense.active());
        strcpy(data.str, "ACTIVE SENSE");
        data.highlight = midiActiveSense.active();
        display.renderText(data);
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
        // display.renderNumber(deviceIndex, data.oled, data.type, midiClock.getBpm(), "%u", "BPM");
        data.value = midiClock.getBpm();
        strcpy(data.label, "BPM");
        display.renderNumber(data);
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
        // display.renderText(deviceIndex, data.oled, data.type, "TAP");
        strcpy(data.str, "TAP");
        display.renderText(data);
#endif
      } else {
        return BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_STATUS:
      if(group == BMC_DEVICE_GROUP_LED){
        switch(data.byteA){
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
        switch(data.byteA){
          case BMC_LED_STATUS_ALWAYS_ON:
          case BMC_LED_STATUS_BMC:
            // display.renderText(deviceIndex, data.oled, data.type, "BMC");
            strcpy(data.str, "BMC");
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_EDITOR_CONNECTED:
            // display.renderText(deviceIndex, data.oled, data.type, "EDITOR","STATUS",globals.editorConnected());
            strcpy(data.str, "EDITOR");
            strcpy(data.label, "STATUS");
            data.highlight = globals.editorConnected();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_HOST_CONNECTED:
            // display.renderText(deviceIndex, data.oled, data.type, "HOST","STATUS",globals.hostConnected());
            strcpy(data.str, "HOST");
            strcpy(data.label, "STATUS");
            data.highlight = globals.hostConnected();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_BLE_CONNECTED:
            // display.renderText(deviceIndex, data.oled, data.type, "BLE","STATUS",globals.bleConnected());
            strcpy(data.str, "BLE");
            strcpy(data.label, "STATUS");
            data.highlight = globals.bleConnected();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_SENDING:
            // display.renderText(deviceIndex, data.oled, data.type, "A.S. SEND","STATUS", midiActiveSense.active());
            strcpy(data.str, "A.S. SEND");
            strcpy(data.label, "STATUS");
            data.highlight = midiActiveSense.active();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_READING:
            // display.renderText(deviceIndex, data.oled, data.type, "A.S. READ","STATUS", midiActiveSense.reading());
            strcpy(data.str, "A.S. READ");
            strcpy(data.label, "STATUS");
            data.highlight = midiActiveSense.reading();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT:
            // display.renderText(deviceIndex, data.oled, data.type, "R.T. IN","STATUS", midi.getRealTimeBlockInput());
            strcpy(data.str, "R.T. IN");
            strcpy(data.label, "STATUS");
            data.highlight = midi.getRealTimeBlockInput();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT:
            // display.renderText(deviceIndex, data.oled, data.type, "R.T. OUT","STATUS", midi.getRealTimeBlockOutput());
            strcpy(data.str, "R.T. OUT");
            strcpy(data.label, "STATUS");
            data.highlight = midi.getRealTimeBlockOutput();
            display.renderText(data);
            return 1;
          case BMC_LED_STATUS_STOPWATCH_ACTIVE:
          case BMC_LED_STATUS_STOPWATCH_STATE:
          case BMC_LED_STATUS_STOPWATCH_COMPLETE:
          {
            sprintf(data.str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
            strcpy(data.label, "STOPWATCH");
            display.renderText(data);
            // char str[13] = "";
            // sprintf(str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
            // display.renderText(deviceIndex, data.oled, data.type, str, "STOPWATCH");
          }
            return 1;
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
      if(group == BMC_DEVICE_GROUP_LED){
        return globals.hasMidiActivity(data.byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "MIDI IO");
        strcpy(data.str, "MIDI IO");
        display.renderText(data);
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
        // display.renderText(deviceIndex, data.oled, data.type, "SAVE EEPROM");
        strcpy(data.str, "SAVE EEPROM");
        display.renderText(data);
        
#endif

      }
      break;
#if defined(BMC_USE_ON_BOARD_EDITOR)
    case BMC_EVENT_TYPE_SYSTEM_MENU:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        obe.menuCommand(data.byteA);
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        uint8_t menCmd = data.scrollDirection() ? BMC_MENU_NEXT : BMC_MENU_PREV;
        obe.menuCommand(menCmd, true);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        switch(data.byteA){
          case BMC_MENU_TOGGLE:
            // display.renderText(deviceIndex, data.oled, data.type, "TOGGLE");
            strcpy(data.str, "TOGGLE");
            display.renderText(data);
            return 1;
          case BMC_MENU_SELECT:
            // display.renderText(deviceIndex, data.oled, data.type, "SELECT");
            strcpy(data.str, "SELECT");
            display.renderText(data);
            return 1;
          case BMC_MENU_BACK:
            // display.renderText(deviceIndex, data.oled, data.type, "BACK");
            strcpy(data.str, "BACK");
            display.renderText(data);
            return 1;
          case BMC_MENU_PREV:
            // display.renderText(deviceIndex, data.oled, data.type, "PREV");
            strcpy(data.str, "PREV");
            display.renderText(data);
            return 1;
          case BMC_MENU_NEXT:
            // display.renderText(deviceIndex, data.oled, data.type, "NEXT");
            strcpy(data.str, "NEXT");
            display.renderText(data);
            return 1;
          case BMC_MENU_SHIFT:
            // display.renderText(deviceIndex, data.oled, data.type, "SHIFT");
            strcpy(data.str, "SHIFT");
            display.renderText(data);
            return 1;
          case BMC_MENU_CANCEL:
            // display.renderText(deviceIndex, data.oled, data.type, "CANCEL");
            strcpy(data.str, "CANCEL");
            display.renderText(data);
            return 1;
          case BMC_MENU_SAVE:
            // display.renderText(deviceIndex, data.oled, data.type, "SAVE");
            strcpy(data.str, "SAVE");
            display.renderText(data);
            return 1;
        }
#endif
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_TYPER:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        uint8_t cmd = valueTyper.cmd(data.byteA, data.byteB);
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
        // char str[16] = "";
        uint8_t cmd = data.byteA;
        if(data.useName()){ // Name
          if(cmd < 10){
            sprintf(data.str, "%u", cmd);
          } else {
            switch(cmd){
              case 10: strcpy(data.str, "CLEAR"); break;
              case 11: strcpy(data.str, "<"); break;
              case 12: strcpy(data.str, ">"); break;
              case 13: strcpy(data.str, "DEC"); break;
              case 14: strcpy(data.str, "INC"); break;
              case 15: strcpy(data.str, "CUSTOM"); break;
              case 16: strcpy(data.str, "LAYER"); break;
  #if BMC_MAX_PRESETS > 0
              case 17: strcpy(data.str, "PRESET"); break;
  #endif
  #if defined(BMC_USE_FAS)
              case 18: strcpy(data.str, "FAS PRESET"); break;

              case 19:
              case 20: strcpy(data.str, "FAS SCENE"); break;
  #endif
              case 21: strcpy(data.str, "PROGRAM"); break;
              case 22: strcpy(data.str, "CONTROL"); break;
            }
          }
        } else {
          sprintf(data.str, "%03u", valueTyper.getOutput());
          display.setSelChar(deviceIndex, data.oled, valueTyper.getSelChar());
        }
        // display.renderText(deviceIndex, data.oled, data.type, str, "TYPER");

        // strcpy(data.str, "SAVE");
        strcpy(data.label, "TYPER");
        display.renderText(data);
        
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
          // display.renderText(deviceIndex, data.oled, data.type, "BLE","STATUS",globals.bleConnected());
          strcpy(data.str, "BLE");
          strcpy(data.label, "STATUS");
          data.highlight = globals.bleConnected();
          display.renderText(data);
#endif
        } else {
          return globals.bleConnected();
        }
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_STOPWATCH:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        stopwatchCmd(data.byteA, data.byteB, data.byteC, data.byteD);
        
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return (stopwatch.getState() == 1) ? 100 : 0;

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[13] = "";
        sprintf(data.str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
        // display.renderText(deviceIndex, data.oled, data.type, str, "STOPWATCH");
        // strcpy(data.str, "BLE");
        strcpy(data.label, "STOPWATCH");
        display.renderText(data);
#endif
      } else {
        return (stopwatch.getState() == 1);

      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_LFO:
      if(data.byteA >= BMC_MAX_LFO){
        return 0;
      }
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(data.byteB==0){
          lfo[data.byteA].toggle();
        } else if(data.byteB==1){
          lfo[data.byteA].start();
        } else if(data.byteB==2){
          lfo[data.byteA].stop();
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[10] = "";
        sprintf(data.str, "LFO %u", data.byteA+data.offset);
        // display.renderText(deviceIndex, data.oled, data.type, str, "", lfo[data.byteA].isEnabled());
        data.highlight = lfo[data.byteA].isEnabled();
        display.renderText(data);
        
#endif
      } else {
        return lfo[data.byteA].isEnabled();
      }
      break;
    // SKETCH BYTES
    case BMC_EVENT_TYPE_SKETCH_BYTE:
#if BMC_MAX_SKETCH_BYTES > 0
      if(data.byteA >= BMC_MAX_SKETCH_BYTES){
        return 0;
      }
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        BMCSketchByteData sbData = BMCBuildData::getSketchByteData(data.byteA);
        uint8_t tmp = getSketchByte(data.byteA);
        if(data.scrollEnabled()){
          BMCScroller <uint8_t> scroller(sbData.min, sbData.max);
          tmp = scroller.scroll(sbData.step, data.scrollDirection(), data.scrollWrap(), tmp, sbData.min, sbData.max);
        } else {
          tmp = constrain(data.byteB, sbData.min, sbData.max);
        }
        streamToSketch(BMC_DEVICE_ID_SKETCH_BYTE, tmp, sbData.name);
        setSketchByte(data.byteA, tmp);
        if(callback.storeUpdated){
          callback.storeUpdated();
        }
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[26] = "";
        BMCSketchByteData sbData = BMCBuildData::getSketchByteData(data.byteA);
        BMCTools::getSketchByteFormat(data.str, data.byteA, getSketchByte(data.byteA));
        // getSketchByteFormat(char* str, uint8_t n, uint8_t value)
        // display.renderText(deviceIndex, data.oled, data.type, str, sbData.name);

        strcpy(data.label, sbData.name);
        display.renderText(data);
#endif
      }
#endif
      break;

    // LAYERS
    case BMC_EVENT_TYPE_LAYER:
      {
        // data.min = 0;
        // data.max = BMC_MAX_LAYERS-1;
        // uint8_t outVal = data.byteA;
        // if(data.byteB > 0){
        //   // scrolling max or toggle enabled
        //   if((data.byteB-1) > data.byteA){
        //     data.min = data.byteA;
        //     data.max = data.byteB-1;
        //   } else if((data.byteB-1) != data.byteA){
        //     data.max = data.byteA;
        //     data.min = data.byteB-1;
        //   }

        //   if(!data.scrollEnabled()){
        //     outVal = layer != data.byteA ? data.byteA : (data.byteB-1);
        //   }
        // }
        uint8_t outVal = data.setMinMax(layer, 0, BMC_MAX_LAYERS-1, data.byteA, data.byteB);
        if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            scrollLayer(data.scrollDirection(), data.scrollWrap(), data.min, data.max, data.scrollAmount());
          } else {
            setLayer(outVal);
          }
        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);

        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
          
  #if defined(BMC_HAS_DISPLAY)
          if(data.byteA < BMC_MAX_LAYERS && data.byteB <= BMC_MAX_LAYERS){
            data.highlight = (layer == data.byteA);
            if(!data.useSelected()){ // selected
              data.highlight = false;
            }
            strcpy(data.label, "LAYER");
            if(data.useMeter()){
              data.value = layer;
              display.renderSlider(data);
              // display.renderSlider(deviceIndex, data.oled, data.type, layer, data.min, data.max, data.label);
            } else {
              bmcStoreName t;
              if(data.useName()){ // name
                t = (data.useSelected()) ? getLayerName() : getLayerName(data.byteA);
              } else {
                t = (data.useSelected()) ? getLayerStr() : getLayerStr(data.byteA);
              }
              // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label, highlight);
              strcpy(data.str, t.name);
              display.renderText(data);

            }
          }
  #endif        
        } else {
          return (event & 0x3FFF) == layer;
        }
      }
      break;
    // PRESETS
#if BMC_MAX_PRESETS > 0
    case BMC_EVENT_TYPE_PRESET:
      {
        data.min = 0;
        data.max = BMC_MAX_PRESETS_PER_BANK-1;
        uint8_t outVal = data.byteA;
        if(data.byteB > 0){
          // scrolling max or toggle enabled
          if((data.byteB-1) > data.byteA){
            data.min = data.byteA;
            data.max = data.byteB-1;
          } else if((data.byteB-1) != data.byteA){
            data.max = data.byteA;
            data.min = data.byteB-1;
          }

          if(!data.scrollEnabled()){
            outVal = presets.get() != data.byteA ? data.byteA : (data.byteB-1);
          }
        }
        if(data.byteC == 1){
          data.min = 0;
          data.max = BMC_MAX_PRESETS-1;
        }
        // don't run this event if it's being triggered by a preset
        if(flags.read(BMC_FLAGS_BLOCK_PRESETS)){
          return false;
        }
        if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            if(data.byteC == 1){
              presets.scrollPresetList(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), 0, 0);
            } else {
              presets.scrollPreset(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
            }
          } else {
            presets.setPreset(outVal);
          }

        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(presets.get(), data.min, data.max, 0, 100);

        } else if(group == BMC_DEVICE_GROUP_DISPLAY){

  #if defined(BMC_HAS_DISPLAY)
          if(data.byteA < BMC_MAX_PRESETS_PER_BANK){
            strcpy(data.label, "PRESET");
            if(data.useMeter()){
              // display.renderSlider(deviceIndex, data.oled, data.type, presets.get(), data.min, data.max, data.label);

              // BMCTools::getPresetLabelNoName(presets.getBank(), presets.get(), data.str);
              if(data.byteC == 1){
                data.value = presets.getIndex();
              } else {
                data.value = presets.get();
              }
              
              data.byteD = presets.getBank();
              display.renderSlider(data);
            } else {
              bmcStoreName t;
              if(data.useName()){ // name
                t = (data.useSelected()) ? presets.getName() : presets.getName(data.byteA);
              } else {
                t = (data.useSelected()) ? presets.getPresetStr() : presets.getPresetStr(data.byteA);
              }
              // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label);
              strcpy(data.str, t.name);
              display.renderText(data);
            }
          }
  #endif
        } else {
          return data.byteA == presets.get();
        }
      }
      break;
    case BMC_EVENT_TYPE_BANK:
      {
        data.min = 0;
        data.max = BMC_MAX_PRESET_BANKS-1;
        uint8_t outVal = data.byteA;
        if(data.byteB > 0){
          // scrolling max or toggle enabled
          if((data.byteB-1) > data.byteA){
            data.min = data.byteA;
            data.max = data.byteB-1;
          } else if((data.byteB-1) != data.byteA){
            data.max = data.byteA;
            data.min = data.byteB-1;
          }

          if(!data.scrollEnabled()){
            outVal = presets.getBank() != data.byteA ? data.byteA : (data.byteB-1);
          }
        }
        // don't run this event if it's being triggered by a preset
        if(flags.read(BMC_FLAGS_BLOCK_PRESETS)){
          return false;
        }
        if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            presets.scrollBank(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
          } else {
            presets.setBank(outVal);
          }

        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(presets.getBank(), 0, BMC_MAX_PRESET_BANKS-1, 0, 100);
          
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
          
          strcpy(data.label, "BANK");
          if(data.useMeter()){
            data.value = presets.getBank();
            display.renderSlider(data);
            // display.renderSlider(deviceIndex, data.oled, data.type, presets.getBank(), data.min, data.max, data.label);
          } else {
            bmcStoreName t = (data.useSelected()) ? presets.getBankStr() : presets.getBankStr(data.byteA);
            // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label);
            strcpy(data.str, t.name);
            display.renderText(data);
          }
  #endif
        } else {
          return data.byteA == presets.getBank();
        }
      }
      break;
#endif

#if BMC_MAX_SETLISTS > 0
    
    case BMC_EVENT_TYPE_SETLIST:
      {
        data.min = 0;
        data.max = BMC_MAX_SETLISTS-1;
        uint8_t outVal = data.byteA;
        if(data.byteB > 0){
          // scrolling max or toggle enabled
          if((data.byteB-1) > data.byteA){
            data.min = data.byteA;
            data.max = data.byteB-1;
          } else if((data.byteB-1) != data.byteA){
            data.max = data.byteA;
            data.min = data.byteB-1;
          }

          if(!data.scrollEnabled()){
            outVal = setLists.get() != data.byteA ? data.byteA : (data.byteB-1);
          }
        }
        if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            setLists.scrollSet(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
          } else {
            setLists.set(outVal);
          }

        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
          
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
          if(data.byteA < BMC_MAX_SETLISTS){
            strcpy(data.label, "SET");
            if(data.useMeter()){
              data.value = setLists.get();
              display.renderSlider(data);
              // display.renderSlider(deviceIndex, data.oled, data.type, setLists.get(), data.min, data.max, data.label);
            } else {
              bmcStoreName t;
              if(data.useName()){ // display name
                t = (data.useSelected()) ? setLists.getSetName() : setLists.getSetName(data.byteA);
              } else { // display number
                t = (data.useSelected()) ? setLists.getSetStr() : setLists.getSetStr(data.byteA);
              }
              // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label);
              strcpy(data.str, t.name);
              display.renderText(data);
            }
          }
  #endif
        } else {
          return (data.byteA == setLists.get());
        }
      }
      break;


    case BMC_EVENT_TYPE_SONG:
      {
        data.min = 0;
        data.max = BMC_MAX_SETLISTS_SONGS-1;
        uint8_t outVal = data.byteA;
        if(data.byteB > 0){
          // scrolling max or toggle enabled
          if((data.byteB-1) > data.byteA){
            data.min = data.byteA;
            data.max = data.byteB-1;
          } else if((data.byteB-1) != data.byteA){
            data.max = data.byteA;
            data.min = data.byteB-1;
          }

          if(!data.scrollEnabled()){
            outVal = setLists.getSong() != data.byteA ? data.byteA : (data.byteB-1);
          }
        }
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(data.scrollEnabled()){
            setLists.scrollSong(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
          } else {
            setLists.setSong(outVal);
          }

        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          setLists.scrollSong(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);

        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
          
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
          if(data.byteA < BMC_MAX_SETLISTS_SONGS){
            strcpy(data.label, "SONG");
            if(data.useMeter()){
              data.value = setLists.getSong();
              display.renderSlider(data);
              // display.renderSlider(deviceIndex, data.oled, data.type, setLists.getSong(), data.min, data.max, data.label);
            } else {
              bmcStoreName t;
              if(data.useName()){ // display name
                t = (data.useSelected()) ? setLists.getSongName() : setLists.getSongName(data.byteA);
              } else { // display number
                t = (data.useSelected()) ? setLists.getSongStr() : setLists.getSongStr(data.byteA);
              }
              // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label);
              strcpy(data.str, t.name);
              display.renderText(data);
            }
            
          }
  #endif
        } else {
          return (data.byteA == setLists.getSong());

        }
      }
      break;


    case BMC_EVENT_TYPE_PART:
      {
        data.min = 0;
        data.max = BMC_MAX_SETLISTS_SONG_PARTS-1;
        uint8_t outVal = data.byteA;
        if(data.byteB > 0){
          // scrolling max or toggle enabled
          if((data.byteB-1) > data.byteA){
            data.min = data.byteA;
            data.max = data.byteB-1;
          } else if((data.byteB-1) != data.byteA){
            data.max = data.byteA;
            data.min = data.byteB-1;
          }

          if(!data.scrollEnabled()){
            outVal = setLists.getPart() != data.byteA ? data.byteA : (data.byteB-1);
          }
        }
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(data.scrollEnabled()){
            setLists.scrollPart(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
          } else {
            setLists.setPart(outVal);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          setLists.scrollPart(data.scrollDirection(), data.scrollWrap(), data.scrollAmount(), data.min, data.max);
          
        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);

        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
          if(data.byteA < BMC_MAX_SETLISTS_SONG_PARTS){
            strcpy(data.label, "PART");
            if(data.useMeter()){
              data.value = setLists.getPart();
              display.renderSlider(data);
              // display.renderSlider(deviceIndex, data.oled, data.type, setLists.getPart(), data.min, data.max, data.label);
            } else {
              bmcStoreName t;
              if(data.useName()){ // display name
                t = (data.useSelected()) ? setLists.getPartName() : setLists.getPartName(data.byteA);
              } else { // display number
                t = (data.useSelected()) ? setLists.getPartStr() : setLists.getPartStr(data.byteA);
              }
              // display.renderText(deviceIndex, data.oled, data.type, t.name, data.label);
              strcpy(data.str, t.name);
              display.renderText(data);
            }
          }
  #endif
        } else {
          return (data.byteA == setLists.getPart());
        }
      }
      break;
#endif

#if BMC_MAX_PIXEL_PROGRAMS > 0
    // PIXELS
    case BMC_EVENT_TYPE_PIXEL_PROGRAM:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        if(data.scrollEnabled()){
          pixelPrograms.scroll(data.scrollDirection(), data.scrollWrap());
        } else {
          pixelPrograms.setProgram(data.byteA);
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
      if(data.byteA >= BMC_MAX_AUX_JACKS){
        return 0;
      }
      if(group == BMC_DEVICE_GROUP_LED){
        if(data.byteB == 0){
          return auxJacks[data.byteA].isConnected();
        } else if(data.byteB == 1){
          return auxJacks[data.byteA].isPotMode();
        } else if(data.byteB == 2){
          return !auxJacks[data.byteA].isPotMode();
        }
        
      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        if(data.byteB == 0){
          return auxJacks[data.byteA].isConnected() ? 100 : 0;
        } else if(data.byteB == 1){
          return auxJacks[data.byteA].isPotMode() ? 100 : 0;
        } else if(data.byteB == 2){
          return !auxJacks[data.byteA].isPotMode() ? 100 : 0;
        }

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[13] = "";
        if(auxJacks[data.byteA].isPotMode()){
          sprintf(data.str, "Exp %u", data.byteA+data.offset);
        } else {
          sprintf(data.str, "Ctrl %u", data.byteA+data.offset);
        }
        // display.renderText(deviceIndex, data.oled, data.type, str, "AUX JACK", auxJacks[data.byteA].isConnected());
        strcpy(data.label, "AUX JACK");
        data.highlight = auxJacks[data.byteA].isConnected();
        display.renderText(data);
#endif
      }
      break;
#endif

#if defined(BMC_HAS_DISPLAY)
    case BMC_EVENT_TYPE_DEVICE_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
        bmcStoreName t;
        editor.getDeviceNameText(data.byteA, BMC_GET_BYTE_2(1, event), t.name);
        // display.renderText(deviceIndex, data.oled, data.type, t.name, "NAME");
        strcpy(data.str, t.name);
        strcpy(data.label, "NAME");
        display.renderText(data);
      }
      break;
#endif
    // EXTERNAL SYNC
#ifdef BMC_USE_DAW_LC
    case BMC_EVENT_TYPE_DAW_COMMAND:
      // handled by BMC::handleButton
      if(group == BMC_DEVICE_GROUP_BUTTON){

        sync.daw.sendButtonCommand(data.byteA, data.byteB, false);

      } else if(group == BMC_DEVICE_GROUP_LED){
        
        return sync.daw.getLedState(data.byteA, data.byteB);

      } else if(group == BMC_DEVICE_GROUP_ENCODER){

        sync.daw.sendEncoderScrolling(data.byteA, data.byteB, data.scrollDirection(), data.scrollAmount());

      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){

        if(data.byteA == BMC_DAW_CMD_VPOT_SELECT || (data.byteA >= BMC_DAW_CMD_VPOT_LED_1 && data.byteA <= BMC_DAW_CMD_VPOT_LED_CENTER)){
          return sync.daw.getVPotValuePercentage(data.byteB);
        } else if(data.byteA >= BMC_DAW_CMD_METER_LED_PEAK && data.byteA <= BMC_DAW_CMD_METER_LED_12){
          return sync.daw.getMeterValuePercentage(data.byteB);
        } else if(data.byteA >= BMC_DAW_CMD_FADER_TOUCH){
          return sync.daw.getFaderValuePercentage(data.byteB);
        } else {
          return sync.daw.getLedState(data.byteA, data.byteB)>0 ? 100 : 0;
        }
      }
      break;
    case BMC_EVENT_TYPE_DAW_DISPLAY:
#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_DAW_LC)
      if(group == BMC_DEVICE_GROUP_DISPLAY){
        if(data.byteA==0){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.updateDawMeters();
            }
          #endif
        } else if(data.byteA == 1){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.updateDawChannels();
            }
          #endif
        } else if(data.byteA == 2){
          display.updateDawChannelInfo(data.byteB);
        } else if(data.byteA == 3){
          // char str[3] = "";
          sync.daw.getTwoDigitDisplay(data.str);
          // display.renderText(deviceIndex, data.oled, data.type, str);
          display.renderText(data);
        }
      }
#endif
      break;
#endif

#ifdef BMC_USE_BEATBUDDY
    case BMC_EVENT_TYPE_BEATBUDDY:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(data.scrollEnabled()){
          if(data.byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && data.byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
            uint8_t s = sync.beatBuddy.getSongPart();
            if(data.scrollDirection()){
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
        sync.beatBuddy.sendCommand(data.byteA, data.byteB);
        
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        if(data.byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && data.byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          uint8_t s = sync.beatBuddy.getSongPart();
          if(data.scrollDirection()){
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
        switch(data.byteA){
          case BMC_BEATBUDDY_CMD_BPM_DEC:
          case BMC_BEATBUDDY_CMD_BPM_INC:
            sync.beatBuddy.tempoControl(data.scrollAmount(), data.scrollDirection());
            break;
          case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN:
          case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:
            sync.beatBuddy.sendCommand((data.scrollDirection())?BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN);
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_LED){
        if(data.byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && data.byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          return sync.beatBuddy.isSongPart(data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1);
        }
        switch(data.byteA){
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
        switch(data.byteA){
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
        
        if(data.byteA>=BMC_BEATBUDDY_CMD_TRANS_PART_1 && data.byteA<=BMC_BEATBUDDY_CMD_TRANS_PART_125){
          if(data.useSelected()){ // selected
            uint8_t s = sync.beatBuddy.getSongPart();
            sprintf(data.str,"PT %u", s+data.offset);
            data.highlight = true;
          } else {
            sprintf(data.str,"PT %u",(data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1)+data.offset);
            data.highlight = sync.beatBuddy.isSongPart(data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1);
          }
        } else {
          switch(data.byteA){
            case BMC_BEATBUDDY_CMD_START:
              strcpy(data.str, "Start");
              data.highlight = sync.beatBuddy.isPlaying();
              break;
            case BMC_BEATBUDDY_CMD_STOP:
              strcpy(data.str, "Stop");
              data.highlight = !sync.beatBuddy.isPlaying();
              break;
            case BMC_BEATBUDDY_CMD_BPM_DEC:
              strcpy(data.str, "BPM Dec");
              break;
            case BMC_BEATBUDDY_CMD_BPM_INC:
              strcpy(data.str, "BPM Inc");
              break;
            case BMC_BEATBUDDY_CMD_PAUSE:
              strcpy(data.str, "Pause");
              break;
            case BMC_BEATBUDDY_CMD_UNPAUSE:
              strcpy(data.str, "Unpause");
              break;
            case BMC_BEATBUDDY_CMD_PAUSE_TOGGLE:
              strcpy(data.str, "Pause Toggle");
              break;
            case BMC_BEATBUDDY_CMD_DRUM_FILL:
              strcpy(data.str, "Drum Fill");
              break;
            case BMC_BEATBUDDY_CMD_TAP:
              strcpy(data.str, "Tap");
              break;
            case BMC_BEATBUDDY_CMD_OUTRO:
              strcpy(data.str, "Outtro");
              break;
            case BMC_BEATBUDDY_CMD_MIX_VOL:
              strcpy(data.str, "Mix Vol");
              break;
            case BMC_BEATBUDDY_CMD_HP_VOL:
              strcpy(data.str, "HP Vol");
              break;
            case BMC_BEATBUDDY_CMD_ACCENT_HIT:
              strcpy(data.str, "Accent Hit");
              break;
            case BMC_BEATBUDDY_CMD_DRUMSET_SELECT:
              strcpy(data.str, "Drumset Sel");
              break;
            case BMC_BEATBUDDY_CMD_NORMAL_TIME:
              strcpy(data.str, "Normal Time");
              data.highlight = !sync.beatBuddy.isHalfTime() && !sync.beatBuddy.isDoubleTime();
              break;
            case BMC_BEATBUDDY_CMD_HALF_TIME:
              data.highlight = sync.beatBuddy.isHalfTime();
              strcpy(data.str, "Half Time");
              break;
            case BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE:
              data.highlight = sync.beatBuddy.isHalfTime();
              strcpy(data.str, "Half Time Tggle");
              break;
            case BMC_BEATBUDDY_CMD_DOUBLE_TIME:
              data.highlight = sync.beatBuddy.isDoubleTime();
              strcpy(data.str, "Double Time");
              break;
            case BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE:
              data.highlight = sync.beatBuddy.isDoubleTime();
              strcpy(data.str, "Dble Time Tggle");
              break;
            case BMC_BEATBUDDY_CMD_FOLDER_ENTER:
              strcpy(data.str, "Folder Enter");
              break;
            case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN:
              strcpy(data.str, "Song Scroll Down");
              break;
            case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:
              strcpy(data.str, "Song Scroll Up");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_END:
              strcpy(data.str, "Trans End");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_PREV:
              strcpy(data.str, "Trans Prev");
              break;
            case BMC_BEATBUDDY_CMD_TRANS_NEXT:
              strcpy(data.str, "Trans Next");
              break;
          }
        }
        // display.renderText(deviceIndex, data.oled, data.type, str, "BEATBUDDY", highlight); 
        strcpy(data.label, "BEATBUDDY");
        display.renderText(data);
#endif
      }
      break;
    case BMC_EVENT_TYPE_BEATBUDDY_BPM:
      if(group == BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
        if(data.scrollEnabled()){
          sync.beatBuddy.tempoControl(data.scrollAmount(), data.scrollDirection());
        } else {
          sync.beatBuddy.tempo(event & 0x1FF);
        }

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // display.renderText(deviceIndex, data.oled, data.type, "BB BPM", "BEATBUDDY"); 
        strcpy(data.str, "BB BPM");
        strcpy(data.label, "BEATBUDDY");
        display.renderText(data);
#endif
      }
      break;
    // case BMC_EVENT_TYPE_BEATBUDDY_FOLDER:
    //   if(group == BMC_DEVICE_GROUP_BUTTON){
    //     sync.beatBuddy.songSelect(event & 0x3FFF, data.byteB);
    //   }
    //   break;
#endif
#ifdef BMC_USE_FAS
    case BMC_EVENT_TYPE_FAS:
      if(group == BMC_DEVICE_GROUP_LED){
        switch(data.byteA){
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
        switch(data.byteA){
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
        switch(data.byteA){
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
        switch(data.byteA){
          case BMC_FAS_CMD_CONNECTION:
            // display.renderText(deviceIndex, data.oled, data.type, "FAS", "", sync.fas.connected());
            strcpy(data.str, "FAS");
            data.highlight = sync.fas.connected();
            display.renderText(data);
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
            // display.renderText(deviceIndex, data.oled, data.type, "PLAY","LOOPER",sync.fas.looperPlaying());
            strcpy(data.str, "PLAY");
            strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.connected();
            display.renderText(data);
            break;
          case BMC_FAS_CMD_LOOPER_REC:
            // display.renderText(deviceIndex, data.oled, data.type, "REC","LOOPER",sync.fas.looperRecording());
            strcpy(data.str, "PLARECY");
            strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperRecording();
            display.renderText(data);
            break;
          case BMC_FAS_CMD_LOOPER_DUB:
            // display.renderText(deviceIndex, data.oled, data.type, "DUB","LOOPER",sync.fas.looperDubbing());
            strcpy(data.str, "DUB");
            strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperDubbing();
            display.renderText(data);
            break;
          case BMC_FAS_CMD_LOOPER_REV:
            // display.renderText(deviceIndex, data.oled, data.type, "REVERSE","LOOPER",sync.fas.looperReversed());
            strcpy(data.str, "REVERSE");
            strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperReversed();
            display.renderText(data);
            break;
          case BMC_FAS_CMD_LOOPER_HALF:
            // display.renderText(deviceIndex, data.oled, data.type, "HALF","LOOPER",sync.fas.looperHalf());
            strcpy(data.str, "HALF");
            strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperHalf();
            display.renderText(data);
            break;
          case BMC_FAS_CMD_LOOPER_UNDO:
            // display.renderText(deviceIndex, data.oled, data.type, "UNDO","LOOPER");
            strcpy(data.str, "UNDO");
            strcpy(data.label, "LOOPER");
            display.renderText(data);
            break;
          case BMC_FAS_CMD_TAP:
            // display.renderText(deviceIndex, data.oled, data.type, "TAP");
            strcpy(data.str, "TAP");
            display.renderText(data);
            break;
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_FAS_SCENE:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        if(data.byteB > 0){
          if(sync.fas.getSceneNumber() != data.byteA){
            sync.fas.setSceneNumber(data.byteA, bitRead(event, 16));
          } else {
            sync.fas.setSceneNumber(data.byteB-1, bitRead(event, 16));
          }
        } else {
          sync.fas.setSceneNumber(data.byteA, bitRead(event, 16));
        }

      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        sync.fas.sceneScroll(data.scrollDirection(), data.scrollWrap(), bitRead(event, 16), 0, 7);

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[12] = "";
        data.highlight = sync.fas.getSceneNumber() == data.byteA;
        // display the selected scene number
        if(data.useSelected()){ // selected
          data.highlight = true;
          sprintf(data.str, "S %u", (sync.fas.getSceneNumber()+data.offset));
        } else {
          
          sprintf(data.str, "S %u", (data.byteA+data.offset));
        }
        // display.renderText(deviceIndex, data.oled, data.type, str, "SCENE", highlight);
        strcpy(data.label, "SCENE");
        display.renderText(data);
#endif
      } else {
        return sync.fas.getSceneNumber() == data.byteA;
      }

      break;
    case BMC_EVENT_TYPE_FAS_PRESET:
      {
        data.min = 0;
        data.max = sync.fas.getMaxPresets()-1;
        uint16_t p1 = BMC_GET_BYTE_2(0, event) & 0x3FF;
        uint16_t p2 = BMC_GET_BYTE_2(2, event) & 0x7FF;
        uint16_t outVal = p1;
        if(p2 > 0){
          // scrolling max or toggle enabled
          if((p2 - 1) > p1){
            data.min = p1;
            data.max = p2 - 1;
          } else if((p2 - 1) != p1){
            data.max = p1;
            data.min = p2 - 1;
          }
          if(!data.scrollEnabled()){
            outVal = sync.fas.getPresetNumber() != p1 ? p1: (p2 - 1);
          }
        }
        if(group==BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            sync.fas.presetScroll(data.scrollDirection(), data.scrollWrap(), data.min, data.max);
          } else {
            sync.fas.setPreset(outVal);
          }
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)
          data.highlight = sync.fas.getPresetNumber() == p1;
          if(p2 > 0){
            // if p2 is more than 0 we are in toggle mode
            data.highlight = false;
            uint16_t current = sync.fas.getPresetNumber();
            sprintf(data.str, "P %u", ((current != p1) ? p1 : (p2-1))+data.offset);
          } else {
            if(data.useSelected()){ // selected
              data.highlight = true;
              if(data.useName()){ // name
                sync.fas.getPresetName(data.str);
              } else {
                sprintf(data.str, "P %u", sync.fas.getPresetNumber() + data.offset);
              }
            } else {
              sprintf(data.str, "P %u", (uint16_t)(p1 + data.offset));
            }
          }
          // display.renderText(deviceIndex, data.oled, data.type, str, "PRESET", highlight);
          strcpy(data.label, "PRESET");
          display.renderText(data);
  #endif
        } else {
          return sync.fas.getPresetNumber() == p1;
        }
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(!sync.fas.connected()){
          return 0;
        }
        switch(data.byteA){
          case 0:
            sync.fas.setBlockBypass(data.byteB); // bypass block
            break;
          case 1:
            sync.fas.setBlockEngage(data.byteB); // engage block
            break;
          case 2:
            sync.fas.toggleBlockState(data.byteB); // toggle bypass block
            break;
          case 3:
            sync.fas.setBlockX(data.byteB); // set block to X
            break;
          case 4:
            sync.fas.setBlockY(data.byteB); // set block to Y
            break;
          case 5:
            sync.fas.toggleBlockXY(data.byteB); // toggle XY block
            break;
        }
        return 1;
      } else if(group == BMC_DEVICE_GROUP_LED){
        switch(data.byteA){
          case 0:
            return sync.fas.isBlockBypassed(data.byteB); // block bypass state
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(data.byteB); // block bypass state
          case 3:
            return sync.fas.isBlockX(data.byteB); // block x/y state
          case 4:
          case 5:
            return sync.fas.isBlockY(data.byteB); // block x/y state 
        }
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        switch(data.byteA){
          case 0:
            return sync.fas.isBlockBypassed(data.byteB) ? 100 : 0; // block bypass state
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(data.byteB) ? 100 : 0; // block bypass state
          case 3:
            return sync.fas.isBlockX(data.byteB) ? 100 : 0; // block x/y state
          case 4:
          case 5:
            return sync.fas.isBlockY(data.byteB) ? 100 : 0; // block x/y state 
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
        if(!sync.fas.connected()){
          return 0;
        }
        data.highlight = sync.fas.isBlockEngaged(data.byteB);
        char blockName[5] = "";
        char blockXY[5] = "";
        // char str[10] = "";
        
        sync.fas.getBlockName(data.byteB, blockName);
        sprintf(blockXY, "%s", sync.fas.isBlockX(data.byteB)?"x":"y");
        sprintf(data.str, "%s %s", blockName, blockXY);
        // display.renderText(deviceIndex, data.oled, data.type, str, "BLOCK", blockState);
        strcpy(data.label, "BLOCK");
        display.renderText(data);
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK_PARAM:
      break;
#endif
#ifdef BMC_USE_HELIX
    case BMC_EVENT_TYPE_HELIX:
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        if(data.scrollEnabled()){
          if(data.byteC > 0){
            sync.helix.snapshotScroll(data.scrollDirection(), data.byteB, data.byteC);
          } else {
            sync.helix.snapshotScroll(data.scrollDirection());
          }
        } else {
          if(data.byteC > 0){
            sync.helix.command(BMC_HELIX_CMD_SNAPSHOT_TOGGLE, data.byteB, data.byteC);
          } else {
            sync.helix.command(data.byteA, data.byteB, data.byteC);
          }
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // char str[12] = "";
        if(data.useName()){ // display name
          switch(data.byteA){
            case BMC_HELIX_CMD_TAP:
              strcpy(data.str, "HX TAP");
              break;
            case BMC_HELIX_CMD_TUNER:
              strcpy(data.str, "HX TUNNER");
              break;
            case BMC_HELIX_CMD_SNAPSHOT:
              sprintf(data.str, "SN %u", data.byteB+data.offset);
              break;
            case BMC_HELIX_CMD_SNAPSHOT_TOGGLE:
              sprintf(data.str, "SN %u %u", data.byteB+data.offset, data.byteC+data.offset);
              break;
          }
        } else { // display number
          if(data.useSelected()){// selected
            sprintf(data.str, "SN %u", sync.helix.getSnapshot()+data.offset);
          } else {
            sprintf(data.str, "SN %u", data.byteB+data.offset);
          }
        }
        // display.renderText(deviceIndex, data.oled, data.type, str, "HELIX", sync.helix.isSnapshot(data.byteB));
        strcpy(data.label, "HELIX");
        data.highlight = sync.helix.isSnapshot(data.byteB);
        display.renderText(data);
#endif
      } else {
        return sync.helix.isSnapshot(data.byteB);
      }

      
      break;
#endif
#if BMC_MAX_CUSTOM_SYSEX > 0
    case BMC_EVENT_TYPE_CUSTOM_SYSEX:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        // data.byteA = send mode, 0, 1 or 2
        // data.byteB = index of the 1st custom sysex item to send
        // data.byteC = index of the 2nd custom sysex item to send
        customSysEx.send((data.byteA & 0x03), e.ports, data.byteB, data.byteC);
      }
      break;
#endif
    case BMC_EVENT_TYPE_CUSTOM:
      if(callback.customActivity){
        // this function only works for hardware except relays and displays
        if(group == BMC_DEVICE_GROUP_BUTTON){
          // dat1 has the press type
          // dat2 is unused
          callback.customActivity(deviceId, deviceIndex, data.byteA, dat, 0);
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          // dat1 has the direction
          // dat2 has the number of ticks
          callback.customActivity(deviceId, deviceIndex, data.byteA, bitRead(value, 7), value & 0x7F);
        } else if(group == BMC_DEVICE_GROUP_POT){
          // dat1 has the pot value
          callback.customActivity(deviceId, deviceIndex, data.byteA, value, 0);
        } else if(group == BMC_DEVICE_GROUP_LED){
          // for rgb pixles dat1 is the color index, 0=r, 1=g, 2=b
          // same applies to bi and tri leds, where dat is the index of the color
          // for leds and pixels this function must return true or false, where
          // true will turn (and keep) the led on and false will turn it off
          return callback.customActivity(deviceId, deviceIndex, data.byteA, dat, 0);
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
    bmcStoreEvent cData = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(cData.type)){
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
    bmcStoreEvent cData = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(cData.type)){
      // last 4 bits are always the color
      globalLeds[index].pulse();
    }
  }
#endif


#if BMC_MAX_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_PIXELS; index++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixels[index];
    bmcStoreEvent cData = globals.getDeviceEventType(device.events[0]);
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(cData.type)){
      // last 4 bits are always the color
      pixels.pulse(index, device.settings[0]);
    }
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_RGB_PIXELS; index++){

    bmcStoreDevice <1, 3>& device = store.layers[layer].rgbPixels[index];
    for(uint8_t e = 0; e < 3; e++){
      bmcStoreEvent cData = globals.getDeviceEventType(device.events[e]);
      // first bit is always the "blink" state
      if(BMCTools::isMidiClockLedEvent(cData.type)){
        // last 4 bits are always the color
        pixels.pulseRgb(index, e);
      }
    }
  }
#endif

}
