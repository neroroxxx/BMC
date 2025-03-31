/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
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
    data.setDisplayType(deviceId);
    if(settings.getDisplayNames()){
      #if BMC_MAX_OLED > 0
        if(data.isOled() && store.layers[layer].oled[deviceIndex].name == 0){
          return false;
        }
      #endif
      #if BMC_MAX_ILI9341_BLOCKS > 0
        if(data.isIli() && store.layers[layer].ili[deviceIndex].name == 0){
          return false;
        }
      #endif
      #if BMC_MAX_MINI_DISPLAY > 0
        if(data.isMiniDisplay() && store.layers[layer].miniDisplay[deviceIndex].name == 0){
          return false;
        }
      #endif
      #if BMC_MAX_LCD > 0
        if(data.isLcd() && store.layers[layer].lcd[deviceIndex].name == 0){
          return false;
        }
      #endif
      bmcStoreName t;
      editor.getDeviceNameText(deviceId, deviceIndex, t.name);
      data.crc = 255;
      data.type = 255;
      strcpy(data.str, t.name);
      data.forceOnlyString();
      display.renderBlock(data);
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

#if defined(BMC_HAS_DISPLAY)
  if(group == BMC_DEVICE_GROUP_DISPLAY){
    data.setDisplayType(deviceId);
#if BMC_MAX_OLED > 0
    if(data.isOled()){
      data.settings = store.layers[layer].oled[deviceIndex].settings[0]+0;
    }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
    if(data.isIli()){
      data.settings = store.layers[layer].ili[deviceIndex].settings[0]+0;
      #if BMC_ILI_S_COUNT > 1
        data.colors = store.layers[layer].ili[deviceIndex].settings[1]+0;
      #endif
    }
#endif
#if BMC_MAX_MINI_DISPLAY > 0
    if(data.isMiniDisplay()){
      data.settings = store.layers[layer].miniDisplay[deviceIndex].settings[0]+0;
      data.colors   = store.layers[layer].miniDisplay[deviceIndex].settings[1]+0;
    }
#endif
#if BMC_MAX_LCD > 0
    if(data.isLcd()){
      data.settings = store.layers[layer].lcd[deviceIndex].settings[0]+0;
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
        // data.value          = data.byteB;
        // data.valueSelected  = currentPC;
        if(data.useSelected()){
          data.byteB = currentPC;
        }
        sprintf(data.str, "CH%u PC%u", data.getChannel(), data.byteB);
        data.type = BMC_MIDI_PROGRAM_CHANGE;
        display.renderMidi(data);
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
        if(data.useName()){
          if(BMCTools::isValidNameIndex(e.name)){
            bmcStoreName t = store.global.names[e.name-1];
            strcpy(data.str, t.name);
          } else {
            sprintf(data.str, "CC#%u", data.byteB);
          }

          data.highlight = currentCC >= 64;
          display.renderBlock(data);

          // editor.getDeviceNameText(deviceId, deviceIndex, t.name);
          // strcpy(data.str, t.name);
          
        } else {
          sprintf(data.label, "CC#%u", data.byteB);
          if(data.useSelected()){
            data.byteC = currentCC;
          }
          sprintf(data.str, "CH%u CC%u V%u", data.getChannel(), data.byteB, data.byteC);
          data.type = BMC_MIDI_CONTROL_CHANGE;
          display.renderMidi(data);
        }
        
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
        sprintf(data.str, "CH%u N%u V%u", data.getChannel(), data.byteB, data.byteC);
        data.type = BMC_MIDI_NOTE_ON;
        display.renderMidi(data);
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
        sprintf(data.str, "CH%u N%u V%u", data.getChannel(), data.byteB, data.byteC);
        data.type = BMC_MIDI_NOTE_OFF;
        display.renderMidi(data);
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
          data.max = 100;
          display.renderSlider(data);
        } else {
          data.forceOnlyString();
          strcpy(data.str, data.label);
          display.renderBlock(data);
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
        data.forceOnlyString();
        display.renderBlock(data);
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
        data.forceOnlyString();
        display.renderBlock(data);
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
        data.forceOnlyString();
        sprintf(data.str, "%03u", data.value);
        strcpy(data.label, "PGM BNK");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "TRIGGER");
        strcpy(data.label, "PGM BNK");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "R.T. BLOCK");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "LSB PGM");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "MSB PGM");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "MSB LSB");
        display.renderBlock(data);
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB_PROGRAM:

      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        uint8_t channel = data.getChannel();
        
        midi.sendControlChange(e.ports, channel, 0, data.byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, data.byteC & 0x7F);

        if(data.scrollEnabled()){
          uint8_t currentPC = midi.getLocalProgram(channel);
          data.setMinMax(currentPC, 0, 127, 0, 127);
          midi.scrollPC(e.ports, data.getChannel(), data.scrollAmount(), data.scrollDirection(), data.scrollWrap(), data.min, data.max);
        } else {
          midi.sendProgramChange(e.ports, data.getChannel(), data.byteD & 0x7F);
        }
        // midi.sendProgramChange(e.ports, channel, data.byteD & 0x7F);
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        data.forceOnlyString();
        strcpy(data.str, "MSB LSB PGM");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "ACTIVE SENSE");
        data.highlight = midiActiveSense.active();
        display.renderBlock(data);
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
        data.value = midiClock.getBpm();
        data.forceOnlyString();
        sprintf(data.str, "%03u", data.value);
        strcpy(data.label, "BPM");
        display.renderBlock(data);
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
        data.forceOnlyString();
        strcpy(data.str, "TAP");
        display.renderBlock(data);
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
            strcpy(data.str, "BMC");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_EDITOR_CONNECTED:
            strcpy(data.str, "EDITOR");
            strcpy(data.label, "STATUS");
            data.highlight = globals.editorConnected();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_HOST_CONNECTED:
            strcpy(data.str, "HOST");
            strcpy(data.label, "STATUS");
            data.highlight = globals.hostConnected();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_BLE_CONNECTED:
            strcpy(data.str, "BLE");
            strcpy(data.label, "STATUS");
            data.highlight = globals.bleConnected();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_SENDING:
            strcpy(data.str, "A.S. SEND");
            strcpy(data.label, "STATUS");
            data.highlight = midiActiveSense.active();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_ACTIVE_SENSE_READING:
            strcpy(data.str, "A.S. READ");
            strcpy(data.label, "STATUS");
            data.highlight = midiActiveSense.reading();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT:
            strcpy(data.str, "R.T. IN");
            strcpy(data.label, "STATUS");
            data.highlight = midi.getRealTimeBlockInput();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT:
            strcpy(data.str, "R.T. OUT");
            strcpy(data.label, "STATUS");
            data.highlight = midi.getRealTimeBlockOutput();
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_LED_STATUS_STOPWATCH_ACTIVE:
          case BMC_LED_STATUS_STOPWATCH_STATE:
          case BMC_LED_STATUS_STOPWATCH_COMPLETE:
          {
            sprintf(data.str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
            strcpy(data.label, "STOPWATCH");
            data.forceOnlyString();
            display.renderBlock(data);
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
        strcpy(data.str, "MIDI IO");
        data.forceOnlyString();
        display.renderBlock(data);
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
        strcpy(data.str, "SAVE EEPROM");
        data.forceOnlyString();
        display.renderBlock(data);
        
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
            strcpy(data.str, "TOGGLE");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_SELECT:
            strcpy(data.str, "SELECT");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_BACK:
            strcpy(data.str, "BACK");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_PREV:
            strcpy(data.str, "PREV");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_NEXT:
            strcpy(data.str, "NEXT");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_SHIFT:
            strcpy(data.str, "SHIFT");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_CANCEL:
            strcpy(data.str, "CANCEL");
            data.forceOnlyString();
            display.renderBlock(data);
            return 1;
          case BMC_MENU_SAVE:
            strcpy(data.str, "SAVE");
            data.forceOnlyString();
            display.renderBlock(data);
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
          display.setSelChar(deviceIndex, data.isOled(), valueTyper.getSelChar());
        }
        strcpy(data.label, "TYPER");
        data.forceOnlyString();
        display.renderBlock(data);

        
        
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
          strcpy(data.str, "BLE");
          strcpy(data.label, "STATUS");
          data.highlight = globals.bleConnected();
          data.forceOnlyString();
          display.renderBlock(data);
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
        strcpy(data.label, "STOPWATCH");
        data.forceOnlyString();
        display.renderBlock(data);
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
        data.highlight = lfo[data.byteA].isEnabled();
        data.forceOnlyString();
        display.renderBlock(data);
        
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

        strcpy(data.label, sbData.name);
        data.forceOnlyString();
        display.renderBlock(data);
#endif
      }
#endif
      break;

    // LAYERS
    case BMC_EVENT_TYPE_LAYER:
      {
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
            // set display settings
            strcpy(data.label, "LAYER");
            // bmcStoreName name;
            // bmcStoreName selName;

            
            data.value          = data.byteA;
            data.valueSelected  = layer;
            data.highlight      = (data.valueSelected == data.byteA);
            data.allowMeter     = true;
            data.prependValue   = settings.getAppendPresetNumberToPresetName();
            // assign Name and Selected Name
            getLayerName(data.value, data.str);
            getLayerName(data.valueSelected, data.strSelected);
            // digits
            #if BMC_MAX_LAYERS >= 100
            data.digits = 3;
            strcpy(data.format, "L %03u");
            #elif BMC_MAX_LAYERS >= 10
            data.digits = 2;
            strcpy(data.format, "L %02u");
            #else
            data.digits = 1;
            strcpy(data.format, "L %01u");
            #endif
            
            // strcpy(data.str, name.name);
            // strcpy(data.strSelected, selName.name);

            display.renderBlock(data);
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
            // set display settings
            strcpy(data.label, "PRESET");
            // bmcStoreName name;
            // bmcStoreName selName;

            
            data.value          = data.byteA;
            data.valueSelected  = presets.get();
            data.highlight      = (data.valueSelected == data.byteA);
            data.allowMeter     = true;
            if(data.useMeter()){
              if(data.byteC == 1){
                data.value      = presets.getIndex();
              } else {
                data.value      = presets.get();
              }
              data.valueSelected = data.value;
              data.byteD = presets.getBank();
            }
            // not needed here as the name will append it automatically
            // data.prependValue   = settings.getAppendPresetNumberToPresetName();
            // assign Name and Selected Name
            presets.getName(data.value, data.str);
            presets.getName(data.valueSelected, data.strSelected);
            // digits
            #if BMC_MAX_PRESETS_PER_BANK >= 10
            data.digits = 2;
            strcpy(data.format, "P %02u");
            #else
            data.digits = 1;
            strcpy(data.format, "P %01u");
            #endif
            
            // strcpy(data.str, name.name);
            // strcpy(data.strSelected, selName.name);

            display.renderBlock(data);
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
          // set display settings
          strcpy(data.label, "BANK");
          // bmcStoreName name;
          // bmcStoreName selName;

          
          data.value          = data.byteA;
          data.valueSelected  = presets.getBank();
          data.highlight      = (data.valueSelected == data.byteA);
          data.allowMeter     = true;
          // data.prependValue   = settings.getAppendPresetNumberToPresetName();
          // assign Name and Selected Name
          presets.getBankStr(data.value, data.str);
          presets.getBankStr(data.valueSelected, data.strSelected);
          // digits
          #if BMC_MAX_PRESET_BANKS >= 10
          data.digits = 2;
          strcpy(data.format, "Bk %02u");
          #else
          data.digits = 1;
          strcpy(data.format, "Bk %01u");
          #endif
          
          // strcpy(data.str, name.name);
          // strcpy(data.strSelected, selName.name);
          
          display.renderBlock(data);
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

            // set display settings
            strcpy(data.label, "SET");
            // bmcStoreName name;
            // bmcStoreName selName;

            data.value          = data.byteA;
            data.valueSelected  = setLists.get();
            data.highlight      = (data.valueSelected == data.byteA);
            data.allowMeter     = true;
            data.prependValue   = settings.getAppendPresetNumberToPresetName();
            // assign Name and Selected Name
            setLists.getSetName(data.value, data.str);
            setLists.getSetName(data.valueSelected, data.strSelected);
            // digits
            #if BMC_MAX_SETLISTS >= 10
            data.digits = 2;
            strcpy(data.format, "St %02u");
            #else
            data.digits = 1;
            strcpy(data.format, "St %01u");
            #endif
            
            // strcpy(data.str, name.name);
            // strcpy(data.strSelected, selName.name);
            
            display.renderBlock(data);
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
            // set display settings
            strcpy(data.label, "SONG");

            data.value          = data.byteA;
            data.valueSelected  = setLists.getSong();
            data.highlight      = (data.valueSelected == data.byteA);
            data.allowMeter     = true;
            data.prependValue   = settings.getAppendPresetNumberToPresetName();
            // assign Name and Selected Name
            setLists.getSongName(data.value, data.str);
            setLists.getSongName(data.valueSelected, data.strSelected);
            // digits
            #if BMC_MAX_SETLISTS_SONGS >= 10
            data.digits = 2;
            strcpy(data.format, "Sg %02u");
            #else
            data.digits = 1;
            strcpy(data.format, "Sg %01u");
            #endif
            display.renderBlock(data);
            
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
            // set display settings
            strcpy(data.label, "PART");
            // bmcStoreName name;
            // bmcStoreName selName;

            data.value          = data.byteA;
            data.valueSelected  = setLists.getPart();
            data.highlight      = (data.valueSelected == data.byteA);
            data.allowMeter     = true;
            data.prependValue   = settings.getAppendPresetNumberToPresetName();
            // assign Name and Selected Name
            setLists.getPartName(data.value, data.str);
            setLists.getPartName(data.valueSelected, data.strSelected);
            // digits
            #if BMC_MAX_SETLISTS_SONG_PARTS >= 10
            data.digits = 2;
            strcpy(data.format, "Pt %02u");
            #else
            data.digits = 1;
            strcpy(data.format, "Pt %01u");
            #endif
            
            // strcpy(data.str, name.name);
            // strcpy(data.strSelected, selName.name);
            
            display.renderBlock(data);
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
        } else if(data.byteB == 2){
          return auxJacks[data.byteA].getPotValue() > 0 ? true : false;
        }
        
      } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        if(data.byteB == 0){
          return auxJacks[data.byteA].isConnected() ? 100 : 0;
        } else if(data.byteB == 1){
          return auxJacks[data.byteA].isPotMode() ? 100 : 0;
        } else if(data.byteB == 2){
          return !auxJacks[data.byteA].isPotMode() ? 100 : 0;
        } else if(data.byteB == 3){
          // return !auxJacks[data.byteA].isPotMode() ? 100 : 0;
          return map(auxJacks[data.byteA].getPotValue(), 0, 127, 0, 100);
        }

      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)

        // set display settings
        // strcpy(data.label, "");
        sprintf(data.label, "AUX JACK %u", data.byteA+data.offset);
        data.value          = auxJacks[data.byteA].getPotValue() & 0x7F;
        data.valueSelected  = data.value;
        data.highlight      = auxJacks[data.byteA].isConnected();
        data.min            = 0;
        data.max            = 127;
        data.useOffset      = false;
        data.forceOnlyString();
        if(auxJacks[data.byteA].isPotMode()){
          strcpy(data.str, "EXP");
        } else {
          strcpy(data.str, "CTRL");
        }
        display.renderSlider(data);
#endif
      }
      break;
#endif

#if defined(BMC_HAS_DISPLAY)
    case BMC_EVENT_TYPE_DEVICE_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){

        // set display settings
        strcpy(data.label, "NAME");
        data.forceOnlyString();

        bmcStoreName t;
        editor.getDeviceNameText(data.byteA, BMC_GET_BYTE_2(1, event), t.name);
        strcpy(data.str, t.name);
        display.renderBlock(data);
      }
      break;
    case BMC_EVENT_TYPE_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
        
        // set display settings
        strcpy(data.label, "NAME");
        data.forceOnlyString();
        if((event & 0xFFFF) < BMC_MAX_NAMES_LIBRARY){
          strcpy(data.str, store.global.names[(event & 0xFFFF)].name);
        }
        display.renderBlock(data);
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
              display.renderDaw8Meters(data);
            }
          #endif
        } else if(data.byteA == 1){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.renderDaw8Channel(data);
            }
          #endif
        } else if(data.byteA == 2){
          // display.updateDawChannelInfo(data.byteB);
          display.renderDawChannel(data);
        } else if(data.byteA == 3){
          
          // set display settings
          strcpy(data.label, "DAW");
          data.forceOnlyString();
          sync.daw.getTwoDigitDisplay(data.str);
          display.renderBlock(data);
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
            sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_TRANS_PART_1+s, data.byteB);
            return 0;
          }
        }
        BMC_PRINTLN("event values", data.byteA, data.byteB);
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
          sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_TRANS_PART_1+s, data.byteB);
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
          // set display settings
            bmcStoreName name;
            bmcStoreName selName;

            data.value          = data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1;
            data.valueSelected  = sync.beatBuddy.getSongPart();
            data.highlight      = sync.beatBuddy.isSongPart(data.value);
            data.allowMeter     = true;
            // digits
            data.digits = 3;
            strcpy(data.format, "PT %03u");
            
            sprintf(data.str, "Part %03u", data.value);
            sprintf(data.strSelected, "Part %03u", data.valueSelected);
            data.forceOnlyString();


          // if(data.useSelected()){ // selected
          //   uint8_t s = sync.beatBuddy.getSongPart();
          //   sprintf(data.str,"PT %u", s+data.offset);
          //   data.highlight = true;
          // } else {
          //   sprintf(data.str,"PT %u",(data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1)+data.offset);
          //   data.highlight = sync.beatBuddy.isSongPart(data.byteA-BMC_BEATBUDDY_CMD_TRANS_PART_1);
          // }
        } else {
          data.forceOnlyString();
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
        strcpy(data.label, "BEATBUDDY");
        display.renderBlock(data);
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
        // set display settings
        data.forceOnlyString();
        strcpy(data.str, "BB BPM");
        strcpy(data.label, "BEATBUDDY");
        
        display.renderBlock(data);
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
      switch(data.byteA){
        case BMC_FAS_CMD_LOOPER_PLAY:
        case BMC_FAS_CMD_LOOPER_REC:
        case BMC_FAS_CMD_LOOPER_DUB:
        case BMC_FAS_CMD_LOOPER_REV:
        case BMC_FAS_CMD_LOOPER_HALF:
        case BMC_FAS_CMD_LOOPER_UNDO:
        case BMC_FAS_CMD_LOOPER_ONCE:
        case BMC_FAS_CMD_LOOPER_RDP:
        case BMC_FAS_CMD_LOOPER_RPD:
        case BMC_FAS_CMD_LOOPER_STOP:
        case BMC_FAS_CMD_LOOPER_CLEAR:
          sync.fas.enableLooperFetch(true);
          break;
      }
      if(group == BMC_DEVICE_GROUP_LED){
        switch(data.byteA){
          case BMC_FAS_CMD_CONNECTION:          return sync.fas.connected();
          case BMC_FAS_CMD_TUNER_ON:            return sync.fas.tuner.isOn();
          case BMC_FAS_CMD_TUNER_OFF:           return !sync.fas.tuner.isOn();
          case BMC_FAS_CMD_TUNER_TOGGLE:        return sync.fas.tuner.isOn();
          case BMC_FAS_CMD_TUNER_IN_TUNE:       return sync.fas.tuner.inTune();
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:   return sync.fas.tuner.outOfTune();
          case BMC_FAS_CMD_TUNER_FLAT:          return sync.fas.tuner.isFlat();
          case BMC_FAS_CMD_TUNER_FLATTER:       return sync.fas.tuner.isFlatter();
          case BMC_FAS_CMD_TUNER_FLATTEST:      return sync.fas.tuner.isFlattest();
          case BMC_FAS_CMD_TUNER_SHARP:         return sync.fas.tuner.isSharp();
          case BMC_FAS_CMD_TUNER_SHARPER:       return sync.fas.tuner.isSharper();
          case BMC_FAS_CMD_TUNER_SHARPEST:      return sync.fas.tuner.isSharpest();
          case BMC_FAS_CMD_LOOPER_PLAY:         return sync.fas.looperPlaying();
          case BMC_FAS_CMD_LOOPER_REC:          return sync.fas.looperRecording();
          case BMC_FAS_CMD_LOOPER_DUB:          return sync.fas.looperDubbing();
          case BMC_FAS_CMD_LOOPER_REV:          return sync.fas.looperReversed();
          case BMC_FAS_CMD_LOOPER_HALF:         return sync.fas.looperHalf();
          case BMC_FAS_CMD_LOOPER_UNDO:         return 0; // looper undo
          case BMC_FAS_CMD_LOOPER_RDP:          return sync.fas.looperPlaying() || sync.fas.looperRecording();
          case BMC_FAS_CMD_LOOPER_RPD:          return sync.fas.looperPlaying() || sync.fas.looperRecording();
          case BMC_FAS_CMD_LOOPER_STOP:         return sync.fas.looperStopped();
          case BMC_FAS_CMD_LOOPER_CLEAR:        return sync.fas.looperTrackRecorded();
          case BMC_FAS_CMD_TAP:                 return sync.fas.tempoBeat(); // only works on FAS3
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
            if(bitRead(value, 7)){
              sync.fas.tunerOn();
            } else {
              sync.fas.tunerOff();
            }
            break;
        }
      } else if(group == BMC_DEVICE_GROUP_BUTTON){
        switch(data.byteA){
          case BMC_FAS_CMD_CONNECTION:
            sync.fas.toggleConnection();
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
          case BMC_FAS_CMD_LOOPER_RDP:    sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_REC_DUB_PLAY); break;
          case BMC_FAS_CMD_LOOPER_RPD:    sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_REC_PLAY_DUB); break;
          case BMC_FAS_CMD_LOOPER_STOP:   sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_STOP); break;
          case BMC_FAS_CMD_LOOPER_CLEAR:  sync.fas.looperControl(BMC_FAS_LOOPER_CONTROL_CLEAR); break;
          case BMC_FAS_CMD_TAP:  sync.fas.tapTempo(); break;
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        
        switch(data.byteA){
          case BMC_FAS_CMD_CONNECTION:
            display.renderFasStatus(data);
            break;
          case BMC_FAS_CMD_TUNER_ON:
          case BMC_FAS_CMD_TUNER_OFF:
          case BMC_FAS_CMD_TUNER_TOGGLE:
            display.renderFasTuner(data);
            break;
          case BMC_FAS_CMD_TUNER_IN_TUNE:
            strcpy(data.str, "In Tune"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.inTune();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:
            strcpy(data.str, "Out of Tune"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.outOfTune();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_FLAT:
            strcpy(data.str, "Flat"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isFlat();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_FLATTER:
            strcpy(data.str, "Flatter"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isFlatter();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_FLATTEST:
            strcpy(data.str, "Flattest"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isFlattest();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_SHARP:
            strcpy(data.str, "Sharp"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isSharp();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_SHARPER:
            strcpy(data.str, "Sharper"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isSharper();
            data.forceOnlyString();
            display.renderBlock(data);
            break;
          case BMC_FAS_CMD_TUNER_SHARPEST:
            strcpy(data.str, "Sharpest"); strcpy(data.label, "TUNER");
            data.highlight = sync.fas.tuner.isSharpest();
            data.forceOnlyString();
            display.renderBlock(data);
            break;






          // case BMC_FAS_CMD_TUNER_OUT_OF_TUNE:   return sync.fas.tuner.();
          // case BMC_FAS_CMD_TUNER_FLAT:          return sync.fas.tuner.();
          // case BMC_FAS_CMD_TUNER_FLATTER:       return sync.fas.tuner.isFlatter();
          // case BMC_FAS_CMD_TUNER_FLATTEST:      return sync.fas.tuner.isFlattest();
          // case BMC_FAS_CMD_TUNER_SHARP:         return sync.fas.tuner.();
          // case BMC_FAS_CMD_TUNER_SHARPER:       return sync.fas.tuner.isSharper();




          case BMC_FAS_CMD_LOOPER_PLAY:
            strcpy(data.str, "PLAY"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperPlaying();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_REC:
            strcpy(data.str, "REC"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperRecording();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_DUB:
            strcpy(data.str, "DUB"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperDubbing();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_REV:
            strcpy(data.str, "REVERSE"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperReversed();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_HALF:
            strcpy(data.str, "HALF"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperHalf();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_UNDO:
            strcpy(data.str, "UNDO"); strcpy(data.label, "LOOPER");
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_ONCE:
            strcpy(data.str, "ONCE"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperHalf();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_RDP:
            strcpy(data.str, "R/D/P"); strcpy(data.label, "LOOPER");
            display.renderFasLooper(data);
            break;
          case BMC_FAS_CMD_LOOPER_RPD:
            strcpy(data.str, "R/P/D"); strcpy(data.label, "LOOPER");
            display.renderFasLooper(data);
            break;
          case BMC_FAS_CMD_LOOPER_STOP:
            strcpy(data.str, "STOP"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperTrackRecorded();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_LOOPER_CLEAR:
            strcpy(data.str, "CLEAR"); strcpy(data.label, "LOOPER");
            data.highlight = sync.fas.looperTrackRecorded();
            display.renderFasLooperIcon(data);
            break;
          case BMC_FAS_CMD_TAP:
            data.forceOnlyString();
            strcpy(data.str, "TAP");
            display.renderBlock(data);
            break;
        }
#endif
      }
      break;
    case BMC_EVENT_TYPE_FAS_SCENE:
      {
        data.min = 0;
        data.max = 7;
        uint8_t p1 = BMC_GET_BYTE(0, event) & 0x07;
        uint8_t p2 = BMC_GET_BYTE(1, event) & 0x07;
        uint8_t outVal = p1;
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
            outVal = sync.fas.getSceneNumber() != p1 ? p1: (p2 - 1);
          }
        }
        if(group==BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          if(data.scrollEnabled()){
            sync.fas.sceneScroll(data.scrollDirection(), data.scrollWrap(), data.min, data.max);
          } else {
            sync.fas.setSceneNumber(outVal);
          }

        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
  #if defined(BMC_HAS_DISPLAY)

          // set display settings
          strcpy(data.label, "SCENE");

          data.value          = (data.byteA & 0x07);
          data.valueSelected  = sync.fas.getSceneNumber();
          data.highlight      = data.valueSelected == data.value;
          // data.allowMeter     = true;
          data.prependValue   = settings.getAppendPresetNumberToPresetName();
          // assign Name and Selected Name
          #if defined(BMC_USE_FAS3)
          sync.fas.getSceneName(data.value, data.str);
          sync.fas.getSceneName(data.strSelected);
          #endif
          // digits
          data.digits = 1;
          strcpy(data.format, "S %01u");
          
          display.renderBlock(data);

  #endif
        } else {
          return sync.fas.getSceneNumber() == p1;
          // return true;
        }
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
          // set display settings
          strcpy(data.label, "PRESET");

          data.value          = p1;
          data.valueSelected  = sync.fas.getPresetNumber();
          data.highlight      = data.valueSelected == p1;
          // data.allowMeter     = true;
          data.prependValue   = settings.getAppendPresetNumberToPresetName();
          // assign Name and Selected Name
          sprintf(data.str, "P %04u", data.value);
          sync.fas.getPresetName(data.strSelected);
          // digits
          data.digits = 4;
          strcpy(data.format, "P %04u");
          display.renderBlock(data);
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
#if !defined(BMC_USE_FAS3)
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
#else
          // fas 3 code
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
          case 4:
          case 5:
          case 6:
            sync.fas.setBlockChannel(data.byteB, data.byteA-3);
            break;
          case 7:
            sync.fas.toggleBlockChannel(data.byteB, 0, 1);
            break;
          case 8:
            sync.fas.toggleBlockChannel(data.byteB, 2, 3);
            break;
#endif
        }
        return 1;
      } else if(group == BMC_DEVICE_GROUP_LED){
        switch(data.byteA){
#if !defined(BMC_USE_FAS3)
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
#else
          // fas 3 code
          case 0:
            return sync.fas.isBlockBypassed(data.byteB); // block bypass state
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(data.byteB); // block bypass state
          case 3:
          case 4:
          case 5:
          case 6:
            return (data.byteA-3) == sync.fas.getBlockChannel(data.byteB);
          case 7:
            return sync.fas.getBlockChannel(data.byteB) == 1;
          case 8:
            return sync.fas.getBlockChannel(data.byteB) == 3;
#endif
        }
      } else if(group == BMC_DEVICE_GROUP_MAGIC_ENCODER){
        switch(data.byteA){
#if !defined(BMC_USE_FAS3)
          case 0:
            return sync.fas.isBlockBypassed(data.byteB) ? 100 : 0;
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(data.byteB) ? 100 : 0;
          case 3:
            return sync.fas.isBlockX(data.byteB) ? 100 : 0;
          case 4:
          case 5:
            return sync.fas.isBlockY(data.byteB) ? 100 : 0;
#else
          // fas 3 code
          case 0:
            return sync.fas.isBlockBypassed(data.byteB) ? 100 : 0;
          case 1:
          case 2:
            return sync.fas.isBlockEngaged(data.byteB) ? 100 : 0;
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
            return (sync.fas.getBlockChannel(data.byteB)+1) * 25;
#endif
        }
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        // set display settings
        strcpy(data.label, "BLOCK");
        data.highlight      = sync.fas.isBlockEngaged(data.byteB);
        data.forceOnlyString();
        data.value          = sync.fas.getBlockBits(data.byteB);
        sync.fas.getBlockName(data.byteB, data.str, false);
        display.renderFasFxBlock(data);
#endif
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

        // set display settings
        strcpy(data.label, "HELIX");
        
        switch(data.byteA){
          case BMC_HELIX_CMD_TAP:
            strcpy(data.str, "HX TAP");
            break;
          case BMC_HELIX_CMD_TUNER:
            strcpy(data.str, "HX TUNNER");
            break;
          case BMC_HELIX_CMD_SNAPSHOT:
            
            if(data.useSelected()){
              sprintf(data.str, "SN %u", sync.helix.getSnapshot()+data.offset);
            } else {
              data.highlight = sync.helix.isSnapshot(data.byteB);
              sprintf(data.str, "SN %u", data.byteB+data.offset);
            }
            break;
          case BMC_HELIX_CMD_SNAPSHOT_TOGGLE:
            data.highlight = sync.helix.isSnapshot(data.byteB);
            sprintf(data.str, "SN %u %u", data.byteB+data.offset, data.byteC+data.offset);
            break;
        }
        data.forceOnlyString();
        display.renderBlock(data);
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
