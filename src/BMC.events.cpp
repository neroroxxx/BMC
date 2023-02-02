/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>


uint8_t BMC::processEvent(uint8_t group, uint8_t deviceId, uint8_t deviceIndex,
                          uint8_t ioType, uint16_t eventIndex, uint8_t value){
  if(eventIndex == 0 || eventIndex > BMC_MAX_EVENTS_LIBRARY){
    return false;
  }
  bmcStoreEvent& e = store.global.events[eventIndex-1];
  if(e.type==BMC_NONE){
    return false;
  }
  globals.offset = settings.getDisplayOffset()?0:1;
  uint32_t event = e.event;
  uint8_t byteA = BMC_GET_BYTE(0, event);
  uint8_t byteB = BMC_GET_BYTE(1, event);
  uint8_t byteC = BMC_GET_BYTE(2, event);
  uint8_t byteD = BMC_GET_BYTE(3, event);
  BMCEventScrollData scroll(e.settings, value);
#if defined(BMC_HAS_DISPLAY)
  bool isOled = deviceId == BMC_DEVICE_ID_OLED;
#endif
  switch(e.type){
    case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            uint8_t val = midi.scrollPC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), scroll.amount, scroll.direction, scroll.endless,0,127);
            streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), val);
          } else {
            midi.sendProgramChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB);
            streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB);
          }
        } else if(group==BMC_DEVICE_GROUP_ENCODER){
          uint8_t val = midi.scrollPC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), scroll.amount, scroll.direction, scroll.endless,0,127);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), val);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendProgramChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), value);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), value);
        }
      } else {
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        uint8_t pc = midi.getLocalProgram(channel);
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(pc, 0, 127, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return pc == (byteB & 0x7F);
        }
        return false;
      }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            uint8_t val = midi.scrollCC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, scroll.amount, scroll.direction, scroll.endless,0,127);
            streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
          } else {
            midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
            streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          }
        } else if(group==BMC_DEVICE_GROUP_ENCODER){
          uint8_t val = midi.scrollCC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, scroll.amount, scroll.direction, scroll.endless,0,127);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        }
      } else {
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        uint8_t cc = midi.getLocalControl(channel, byteB);
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(cc, 0, 127, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return cc == (byteC & 0x7F);
        }
        return false;
      }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          midi.sendNoteOn(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendNoteOn(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        }
      }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          midi.sendNoteOff(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendNoteOff(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        }
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
      }
      break;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH_POLY:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouchPoly(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH_POLY, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
      }
      return false;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midi.sendAfterTouch(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
        streamMidi(BMC_MIDI_AFTER_TOUCH, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
      }
      return false;
    case BMC_EVENT_TYPE_MIDI_CONTROL_TOGGLE:
      {
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        uint8_t currentValue = midi.getLocalControl(channel, byteB);
        if(byteC==byteD){
          byteC = 0;
          byteD = 127;
        }
        if(group==BMC_DEVICE_GROUP_BUTTON){
          currentValue = (currentValue == byteC) ? byteD : byteC;
          midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, currentValue);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, currentValue);
        } else if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(currentValue, 0, 127, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          uint8_t c = byteC;
          if(byteD > byteC){
            c = byteD;
          }
          return currentValue == (c & 0x7F);
        }
      }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_SCROLL:
      if(group==BMC_DEVICE_GROUP_BUTTON || group==BMC_DEVICE_GROUP_ENCODER){
        midiProgramBankScroll(scroll.direction, scroll.endless, scroll.amount, byteB, byteC);
      }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiProgramBankTrigger(BMC_TO_MIDI_CHANNEL(byteA), e.ports);
      }
      break;
    case BMC_EVENT_TYPE_MIDI_REAL_TIME_BLOCK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
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
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          if(byteA==0){
            return !midi.getRealTimeBlockInput();
          }
          return !midi.getRealTimeBlockOutput();
        }
      }
      break;
    case BMC_EVENT_TYPE_BANK_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteC & 0x7F);
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 32, byteB & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteC & 0x7F);
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, byteC & 0x7F);
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB_PROGRAM:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
        midi.sendControlChange(e.ports, channel, 0, byteB & 0x7F);
        midi.sendControlChange(e.ports, channel, 32, byteC & 0x7F);
        midi.sendProgramChange(e.ports, channel, byteD & 0x7F);
      }
      break;
    // SYSTEM
    case BMC_EVENT_TYPE_SYSTEM_ACTIVE_SENSE:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiActiveSense.command(byteA);
      } else {
        return midiActiveSense.active();
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiClock.setBpm(BMC_GET_BYTE_2(0, event));
      } else if(group==BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        char str[4] = "";
        sprintf(str, "%u", midiClock.getBpm());
        display.renderText(deviceIndex, isOled, e.type, str, "BPM");
#endif
      } else {
        return BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        midiClock.tap();
      } else {
        return BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_STATUS:
      if(group == BMC_DEVICE_GROUP_LED){
        return handleStatusLedEvent(byteA);
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
      if(group == BMC_DEVICE_GROUP_LED){
        return globals.hasMidiActivity(byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_SAVE_EEPROM:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        editor.saveEEPROM();
        if(callback.storeUpdated){
          callback.storeUpdated();
        }
      }
      break;
#if defined(BMC_USE_ON_BOARD_EDITOR)
    case BMC_EVENT_TYPE_SYSTEM_MENU:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          obe.menuCommand(byteA);
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          uint8_t menCmd = scroll.direction ? BMC_MENU_NEXT : BMC_MENU_PREV;
          obe.menuCommand(menCmd, true);
        }
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_TYPER:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        uint8_t cmd = valueTyper.cmd(byteA, byteB);
        if(cmd > 10){// cmd 10 is Clear
          if(cmd==12){// layer
            setLayer(valueTyper.getRawOutput());
          } else if(cmd==13){// preset
#if BMC_MAX_PRESETS > 0
            presets.set(valueTyper.getRawOutput());
#endif
          } else if(cmd==14){// fas preset
#if defined(BMC_USE_FAS)
            sync.fas.setPreset(valueTyper.getRawOutput());
#endif
          } else if(cmd==15){// fas scene
#if defined(BMC_USE_FAS)
            sync.fas.setSceneNumber(valueTyper.getRawOutput(), false);
#endif
          } else if(cmd==16){// fas scene revert
#if defined(BMC_USE_FAS)
            sync.fas.setSceneNumber(valueTyper.getRawOutput(), true);
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
            midi.sendProgramChange(e.ports, typerChannel, pc);
            streamMidiProgram(typerChannel, pc);
          } else if(cmd==19){
            // control 0 value
            uint8_t val = valueTyper.getRawOutput();
            midi.sendControlChange(e.ports, typerChannel, 0, val);
            streamMidiControl(typerChannel, 0, val);
          } else if(cmd==20){
            // control toggle
            uint8_t cc = valueTyper.getRawOutput();
            uint8_t val = midi.toggleCC(e.ports, typerChannel, cc);
            midi.sendControlChange(e.ports, typerChannel, cc, val);
            streamMidiControl(typerChannel, cc, val);
          }
        }
      }
      break;
#ifdef BMC_MIDI_BLE_ENABLED
    case BMC_EVENT_TYPE_SYSTEM_BLE_DISCONNECT:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        midi.disconnectBLE();
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return globals.bleConnected();
        }
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_STOPWATCH:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          stopwatchCmd(byteA, byteB, byteC, byteD);
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (stopwatch.getState() == 1);
        } else {
#if defined(BMC_HAS_DISPLAY)
          char str[6] = "";
          sprintf(str, "%02u:%02u", stopwatch.hours, stopwatch.minutes);
          display.renderText(deviceIndex, isOled, e.type, str, "STOPWATCH");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_LFO:
      if(group == BMC_DEVICE_GROUP_BUTTON && byteA < BMC_MAX_LFO){
        if(byteB==0){
          lfo[byteA].toggle();
        } else if(byteB==1){
          lfo[byteA].start();
        } else if(byteB==2){
          lfo[byteA].stop();
        }
      }
      break;
    // SKETCH BYTES
    case BMC_EVENT_TYPE_SKETCH_BYTE:
#if BMC_MAX_SKETCH_BYTES > 0
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          byteA = constrain(byteA, 0, BMC_MAX_SKETCH_BYTES);
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
        } else if(group==BMC_DEVICE_GROUP_ENCODER){
          byteA = constrain(byteA, 0, BMC_MAX_SKETCH_BYTES);
          BMCSketchByteData data = BMCBuildData::getSketchByteData(byteA);
          uint8_t tmp = getSketchByte(byteA);
          BMCScroller <uint8_t> scroller(data.min, data.max);
          tmp = scroller.scroll(data.step, scroll.direction, scroll.endless, tmp, data.min, data.max);
          streamToSketch(BMC_DEVICE_ID_SKETCH_BYTE, tmp, data.name);
          setSketchByte(byteA, tmp);
          if(callback.storeUpdated){
            callback.storeUpdated();
          }
        }
      } else {
        return false;
      }
#endif
      break;

    // LAYERS
    case BMC_EVENT_TYPE_LAYER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            scrollLayer(scroll.direction, scroll.endless, scroll.amount);
          } else {
            setLayer(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          scrollLayer(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (event & 0x3FFF) == layer;
        } else {
#if defined(BMC_HAS_DISPLAY)
          #if BMC_MAX_LAYERS < 10
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+globals.offset), "%01u", "LAYER");
          #elif BMC_MAX_LAYERS < 100
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+globals.offset), "%02u", "LAYER");
          #else
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+globals.offset), "%03u", "LAYER");
          #endif
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_LAYER_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        return false;
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (event & 0x3FFF) == layer;
        } else {
#if defined(BMC_HAS_DISPLAY)
          uint16_t pageN = (event & 0x3FFF);
          if(pageN < BMC_MAX_LAYERS){
            bmcStoreName t = globals.getDeviceName(store.layers[pageN].name);
            display.renderText(deviceIndex, isOled, e.type, t.name, "LAYER");
          }
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_LAYER_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          #if BMC_MAX_LAYERS < 10
            display.renderNumber(deviceIndex, isOled, e.type, layer+globals.offset, "%01u", "LAYER");
          #elif BMC_MAX_LAYERS < 100
            display.renderNumber(deviceIndex, isOled, e.type, layer+globals.offset, "%02u", "LAYER");
          #else
            display.renderNumber(deviceIndex, isOled, e.type, layer+globals.offset, "%02u", "LAYER");
          #endif
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_LAYER_SELECTED_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(layer, 0, BMC_MAX_LAYERS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        if(layer < BMC_MAX_LAYERS){
          bmcStoreName t = globals.getDeviceName(store.layers[layer].name);
          display.renderText(deviceIndex, isOled, e.type, t.name, "LAYER");
        }
        return false;
#endif
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
      } else if(group == BMC_DEVICE_GROUP_LED){
        return byteA == presets.get();
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getPresetStr(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name, "PRESET");
#endif
      }
      break;

    case BMC_EVENT_TYPE_PRESET_SELECTED:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(presets.get(), 0, BMC_MAX_PRESETS_PER_BANK-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getPresetStr();
        display.renderText(deviceIndex, isOled, e.type, t.name, "PRESET");
#endif
      }
      break;
    case BMC_EVENT_TYPE_PRESET_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(presets.get(), 0, BMC_MAX_PRESETS_PER_BANK-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name, "PRESET");

#endif
      }
      break;
    case BMC_EVENT_TYPE_PRESET_SELECTED_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(presets.get(), 0, BMC_MAX_PRESETS_PER_BANK-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getName();
        display.renderText(deviceIndex, isOled, e.type, t.name, "PRESET");
#endif
      }
      break;
    case BMC_EVENT_TYPE_BANK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            presets.scrollBank(scroll.direction, scroll.endless, scroll.amount);
          } else {
            presets.setBank(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          presets.scrollBank(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(presets.getBank(), 0, BMC_MAX_PRESET_BANKS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return byteA == presets.getBank();
        } else {
#if defined(BMC_HAS_DISPLAY)
          bmcStoreName t = presets.getBankStr();
          display.renderText(deviceIndex, isOled, e.type, t.name, "BANK");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_BANK_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(presets.getBank(), 0, BMC_MAX_PRESET_BANKS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          bmcStoreName t = presets.getBankStr(byteA);
          display.renderText(deviceIndex, isOled, e.type, t.name, "BANK");
#endif
        }
      }
      break;
#endif

#if BMC_MAX_SETLISTS > 0
    // SETLISTS
    case BMC_EVENT_TYPE_SETLIST:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            setLists.scrollSet(scroll.direction, scroll.endless, scroll.amount);
          } else {
            setLists.set(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          setLists.scrollSet(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.get());
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+globals.offset, "%02u", "SET");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, setLists.get()+globals.offset, "%02u", "SET");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSetName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name, "SET");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.get(), 0, BMC_MAX_SETLISTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSetName();
        display.renderText(deviceIndex, isOled, e.type, t.name, "SET");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SONG:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            setLists.scrollSong(scroll.direction, scroll.endless, scroll.amount);
          } else {
            setLists.setSong(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          setLists.scrollSong(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.getSong());
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+globals.offset, "%02u", "SONG");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_SONG_SELECTED:
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, setLists.getSong()+globals.offset, "%02u", "SONG");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SONG_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSongName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name, "SONG");
#endif
      }
      break;


    case BMC_EVENT_TYPE_SONG_SELECTED_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getSong(), 0, BMC_MAX_SETLISTS_SONGS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSongName();
        display.renderText(deviceIndex, isOled, e.type, t.name, "SONG");
#endif
      }
      break;


    case BMC_EVENT_TYPE_PART:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            setLists.scrollPart(scroll.direction, scroll.endless, scroll.amount);
          } else {
            setLists.setPart(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          setLists.scrollPart(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);
        } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.getPart());
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+globals.offset, "%02u", "PART");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, setLists.getPart()+globals.offset, "%02u", "PART");
#endif
      }
      break;
    case BMC_EVENT_TYPE_PART_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
          return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getPartName();
        display.renderText(deviceIndex, isOled, e.type, t.name, "PART");
#endif
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED_NAME:
      if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
        return map(setLists.getPart(), 0, BMC_MAX_SETLISTS_SONG_PARTS-1, 0, 100);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getPartName();
        display.renderText(deviceIndex, isOled, e.type, t.name, "PART");
#endif
      }
      break;
#endif

#if BMC_MAX_PIXEL_PROGRAMS > 0
    // PIXELS
    case BMC_EVENT_TYPE_PIXEL_PROGRAM:
      if(group == BMC_DEVICE_GROUP_BUTTON){
        if(scroll.enabled){
          pixelPrograms.scroll(scroll.direction, scroll.endless);
          BMC_PRINTLN("scroll Pixel Program");
        } else {
          pixelPrograms.setProgram(byteA);
          BMC_PRINTLN("Set Pixel Program", byteA);
        }
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        pixelPrograms.scroll(scroll.direction, scroll.endless);
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
      if(group == BMC_DEVICE_GROUP_LED && byteA < BMC_MAX_AUX_JACKS){
        if(byteB == 0){
          return auxJacks[byteA].isConnected();
        } else if(byteB == 1){
          return auxJacks[byteA].isPotMode();
        } else if(byteB == 2){
          return !auxJacks[byteA].isPotMode();
        }
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
          // bmcStoreName t = sync.daw.getLcdTrackName(byteB);
          // display.renderText(deviceIndex, isOled, e.type, t.name);
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return handleBeatBuddyLedEvent(byteA, byteB);
        }
      }
      break;
    case BMC_EVENT_TYPE_BEATBUDDY_BPM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return 0;
      }
      break;
    case BMC_EVENT_TYPE_BEATBUDDY_FOLDER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return 0;
      }
      break;
#endif
#ifdef BMC_USE_FAS
    case BMC_EVENT_TYPE_FAS:
    
      if(group == BMC_DEVICE_GROUP_LED){
        switch(byteA){
          case BMC_FAS_CMD_CONNECTION:   return sync.fas.connected();
          case BMC_FAS_CMD_TUNER_ON:   return sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_OFF:   return !sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_TOGGLE:   return sync.fas.isTunerActive();
          case BMC_FAS_CMD_TUNER_IN_TUNE:   return sync.fas.tunerInTune();
          case BMC_FAS_CMD_TUNER_FLAT:   return sync.fas.tunerFlat();
          case BMC_FAS_CMD_TUNER_FLATTER:   return sync.fas.tunerFlatter();
          case BMC_FAS_CMD_TUNER_FLATTEST:   return sync.fas.tunerFlattest();
          case BMC_FAS_CMD_TUNER_SHARP:   return sync.fas.tunerSharp();
          case BMC_FAS_CMD_TUNER_SHARPER:   return sync.fas.tunerSharper();
          case BMC_FAS_CMD_TUNER_SHARPEST:   return sync.fas.tunerSharpest();
          // scenes without revert
          case BMC_FAS_CMD_SCENE_1: case BMC_FAS_CMD_SCENE_2:
          case BMC_FAS_CMD_SCENE_3: case BMC_FAS_CMD_SCENE_4:
          case BMC_FAS_CMD_SCENE_5: case BMC_FAS_CMD_SCENE_6:
          case BMC_FAS_CMD_SCENE_7: case BMC_FAS_CMD_SCENE_8:
            return sync.fas.getSceneNumber()==(byteA-BMC_FAS_CMD_SCENE_1);
          // scenes with revert
          case BMC_FAS_CMD_SCENE_REVERT_1: case BMC_FAS_CMD_SCENE_REVERT_2:
          case BMC_FAS_CMD_SCENE_REVERT_3: case BMC_FAS_CMD_SCENE_REVERT_4:
          case BMC_FAS_CMD_SCENE_REVERT_5: case BMC_FAS_CMD_SCENE_REVERT_6:
          case BMC_FAS_CMD_SCENE_REVERT_7: case BMC_FAS_CMD_SCENE_REVERT_8:
            return sync.fas.getSceneNumber()==(byteA-BMC_FAS_CMD_SCENE_REVERT_1);
          case BMC_FAS_CMD_SCENE_CURRENT:
            return 0;
          case BMC_FAS_CMD_LOOPER_PLAY:  return sync.fas.looperPlaying();
          case BMC_FAS_CMD_LOOPER_REC:  return sync.fas.looperRecording();
          case BMC_FAS_CMD_LOOPER_DUB:  return sync.fas.looperDubbing();
          case BMC_FAS_CMD_LOOPER_REV:  return sync.fas.looperReversed();
          case BMC_FAS_CMD_LOOPER_HALF:  return sync.fas.looperHalf();
          case BMC_FAS_CMD_LOOPER_UNDO:  return 0; // looper undo
          case BMC_FAS_CMD_TAP:  return 0; // tap tempo
        }
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        // sync.fas.presetScroll(scroll.direction, scroll.endless, 0, sync.fas.getMaxPresets());
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
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            sync.fas.toggleTuner();
            break;
          // scenes without revert
          case BMC_FAS_CMD_SCENE_1: case BMC_FAS_CMD_SCENE_2:
          case BMC_FAS_CMD_SCENE_3: case BMC_FAS_CMD_SCENE_4:
          case BMC_FAS_CMD_SCENE_5: case BMC_FAS_CMD_SCENE_6:
          case BMC_FAS_CMD_SCENE_7: case BMC_FAS_CMD_SCENE_8:
            sync.fas.sceneScroll(scroll.direction, scroll.endless, false, 0, 7);
            break;
          // scenes with revert
          case BMC_FAS_CMD_SCENE_REVERT_1: case BMC_FAS_CMD_SCENE_REVERT_2:
          case BMC_FAS_CMD_SCENE_REVERT_3: case BMC_FAS_CMD_SCENE_REVERT_4:
          case BMC_FAS_CMD_SCENE_REVERT_5: case BMC_FAS_CMD_SCENE_REVERT_6:
          case BMC_FAS_CMD_SCENE_REVERT_7: case BMC_FAS_CMD_SCENE_REVERT_8:
            sync.fas.sceneScroll(scroll.direction, scroll.endless, true, 0, 7);
            break;
          case BMC_FAS_CMD_SCENE_CURRENT:
            break;
          case BMC_FAS_CMD_LOOPER_PLAY:break;
          case BMC_FAS_CMD_LOOPER_REC:break;
          case BMC_FAS_CMD_LOOPER_DUB:break;
          case BMC_FAS_CMD_LOOPER_REV:break;
          case BMC_FAS_CMD_LOOPER_HALF:break;
          case BMC_FAS_CMD_LOOPER_UNDO:break;
          case BMC_FAS_CMD_TAP:break;
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
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            sync.fas.toggleTuner();
            break;
          // scenes without revert
          case BMC_FAS_CMD_SCENE_1: case BMC_FAS_CMD_SCENE_2:
          case BMC_FAS_CMD_SCENE_3: case BMC_FAS_CMD_SCENE_4:
          case BMC_FAS_CMD_SCENE_5: case BMC_FAS_CMD_SCENE_6:
          case BMC_FAS_CMD_SCENE_7: case BMC_FAS_CMD_SCENE_8:
            sync.fas.setSceneNumber(byteA-BMC_FAS_CMD_SCENE_1, false);
            break;
          // scenes with revert
          case BMC_FAS_CMD_SCENE_REVERT_1: case BMC_FAS_CMD_SCENE_REVERT_2:
          case BMC_FAS_CMD_SCENE_REVERT_3: case BMC_FAS_CMD_SCENE_REVERT_4:
          case BMC_FAS_CMD_SCENE_REVERT_5: case BMC_FAS_CMD_SCENE_REVERT_6:
          case BMC_FAS_CMD_SCENE_REVERT_7: case BMC_FAS_CMD_SCENE_REVERT_8:
            sync.fas.setSceneNumber(byteA-BMC_FAS_CMD_SCENE_REVERT_1, true);
            break;
          case BMC_FAS_CMD_SCENE_CURRENT:
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
          case BMC_FAS_CMD_TUNER_FLAT:
          case BMC_FAS_CMD_TUNER_FLATTER:
          case BMC_FAS_CMD_TUNER_FLATTEST:
          case BMC_FAS_CMD_TUNER_SHARP:
          case BMC_FAS_CMD_TUNER_SHARPER:
          case BMC_FAS_CMD_TUNER_SHARPEST:
            display.updateFasTuner();
            break;
          // scenes without revert
          case BMC_FAS_CMD_SCENE_1: case BMC_FAS_CMD_SCENE_2:
          case BMC_FAS_CMD_SCENE_3: case BMC_FAS_CMD_SCENE_4:
          case BMC_FAS_CMD_SCENE_5: case BMC_FAS_CMD_SCENE_6:
          case BMC_FAS_CMD_SCENE_7: case BMC_FAS_CMD_SCENE_8:
            {
              char str[8] = "";
              bool sel = sync.fas.getSceneNumber() == (byteA-BMC_FAS_CMD_SCENE_REVERT_1);
              sprintf(str, "S %u", (byteA-BMC_FAS_CMD_SCENE_1)+globals.offset);
              display.renderText(deviceIndex, isOled, e.type, str, "SCENE", sel);
            }
            break;
          // scenes with revert
          case BMC_FAS_CMD_SCENE_REVERT_1: case BMC_FAS_CMD_SCENE_REVERT_2:
          case BMC_FAS_CMD_SCENE_REVERT_3: case BMC_FAS_CMD_SCENE_REVERT_4:
          case BMC_FAS_CMD_SCENE_REVERT_5: case BMC_FAS_CMD_SCENE_REVERT_6:
          case BMC_FAS_CMD_SCENE_REVERT_7: case BMC_FAS_CMD_SCENE_REVERT_8:
            {
              char str[8] = "";
              bool sel = sync.fas.getSceneNumber() == (byteA-BMC_FAS_CMD_SCENE_REVERT_1);
              sprintf(str, "S %u", (byteA-BMC_FAS_CMD_SCENE_REVERT_1)+globals.offset);
              display.renderText(deviceIndex, isOled, e.type, str, "SCENE", sel);
            }
            break;
          case BMC_FAS_CMD_SCENE_CURRENT:
            {
              char str[8] = "";
              sprintf(str, "S %u", sync.fas.getSceneNumber()+globals.offset);
              display.renderText(deviceIndex, isOled, e.type, str);
            }
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
            sync.fas.setSceneNumber(byteB, bitRead(event, 16));
          }
        } else {
          sync.fas.setSceneNumber(byteA, bitRead(event, 16));
        }
      } else if(group == BMC_DEVICE_GROUP_LED){
        return sync.fas.getSceneNumber() == byteA;
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        sync.fas.sceneScroll(scroll.direction, scroll.endless, bitRead(event, 16), 0, 7);
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
        char str[8] = "";
        bool highlight = false;
        // display the selected scene number
        if(bitRead(event, 17)){
          sprintf(str, "S %u", (sync.fas.getSceneNumber()+globals.offset));
        } else {
          highlight = sync.fas.getSceneNumber() == byteA;
          sprintf(str, "S %u", (byteA+globals.offset));
        }
        display.renderText(deviceIndex, isOled, e.type, str, "SCENE", highlight);
      }
      break;
    case BMC_EVENT_TYPE_FAS_PRESET:
      if(group==BMC_DEVICE_GROUP_BUTTON){
        sync.fas.setPreset(event & 0x3FF);
      } else if(group == BMC_DEVICE_GROUP_LED){
        return sync.fas.getPresetNumber()==(event & 0x3FF);
      } else if(group == BMC_DEVICE_GROUP_ENCODER){
        sync.fas.presetScroll(scroll.direction, scroll.endless, 0, sync.fas.getMaxPresets());
      } else if(group == BMC_DEVICE_GROUP_DISPLAY){
        char str[32] = "";
        bool highlight = false;
        if(bitRead(event, 16)){
          sync.fas.getPresetName(str);
        } else {
          highlight = sync.fas.getPresetNumber() == (event & 0x3FF);
          sprintf(str, "P %u", (uint16_t)((event & 0x3FF) + globals.offset));
        }
        display.renderText(deviceIndex, isOled, e.type, str, "PRESET", highlight);
      }
      break;
    case BMC_EVENT_TYPE_FAS_PRESET_TOGGLE:
      {
        uint16_t current = sync.fas.getPresetNumber();
        uint16_t a = event & 0x3FF;
        uint16_t b = (event>>16) & 0x3FF;
        if(group==BMC_DEVICE_GROUP_BUTTON || group == BMC_DEVICE_GROUP_ENCODER){
          sync.fas.setPreset((current != a) ? a : b);
        } else if(group == BMC_DEVICE_GROUP_DISPLAY){
          char str[11] = "";
          sprintf(str, "P %u", ((current != a) ? a : b)+globals.offset);
          display.renderText(deviceIndex, isOled, e.type, str, "PRESET");
        }
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
      // if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        
      // } else {
      //   if(group==BMC_DEVICE_GROUP_MAGIC_ENCODER){
      //     return map(sync.fas.getSyncedParameterValue(byteA, byteB), 0, 65535, 0, 100);
      //   } else if(group != BMC_DEVICE_GROUP_DISPLAY){
          
      //   }
      // }
      break;
#endif
#ifdef BMC_USE_HELIX
    case BMC_EVENT_TYPE_HELIX:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        return sync.helix.isSnapshot(byteA);
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
  }
  return BMC_OFF_LED_EVENT;
}
uint8_t BMC::handleStatusLedEvent(uint8_t status){
  switch(status){
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
  return false;
}
