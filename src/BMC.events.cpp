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
            uint8_t val = midi.scrollPC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), scroll.direction, scroll.endless,0,127);
            streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), val);
          } else {
            midi.sendProgramChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB);
            streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB);
          }
        } else if(group==BMC_DEVICE_GROUP_ENCODER){
          uint8_t val = midi.scrollPC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), scroll.direction, scroll.endless,0,127);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), val);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendProgramChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), value);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), value);
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
          uint8_t pc = midi.getLocalProgram(channel);
          return pc == (byteB & 0x7F);
        }
      }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group==BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            uint8_t val = midi.scrollCC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, scroll.direction, scroll.endless,0,127);
            streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
          } else {
            midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
            streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          }
        } else if(group==BMC_DEVICE_GROUP_ENCODER){
          uint8_t val = midi.scrollCC(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, scroll.direction, scroll.endless,0,127);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, val);
        } else if(group==BMC_DEVICE_GROUP_POT){
          midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, value);
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
          uint8_t cc = midi.getLocalControl(channel, byteB);
          return cc == (byteC & 0x7F);
        }
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
      if(group==BMC_DEVICE_GROUP_BUTTON){
        uint8_t currentValue = midi.getLocalControl(BMC_TO_MIDI_CHANNEL(byteA), byteB);
        currentValue = currentValue > 0 ? 0 : 127;
        midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, currentValue);
        streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, currentValue);
      }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_SCROLL:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_PROGRAM_BANKING_TRIGGER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_PROGRAM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_BANK_MSB_LSB:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
#if BMC_MAX_ILI9341_BLOCKS > 0
    case BMC_EVENT_TYPE_SYSTEM_MENU:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          display.menuCommand(byteA);
          if(callback.menuCommand){
            callback.menuCommand(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          uint8_t menCmd = 0;
          if(byteA == BMC_MENU_UP || byteA == BMC_MENU_DOWN){
            menCmd = scroll.direction ? BMC_MENU_UP : BMC_MENU_DOWN;
          } else if(byteA == BMC_MENU_INC || byteA == BMC_MENU_DEC){
            menCmd = scroll.direction ? BMC_MENU_INC : BMC_MENU_DEC;
          }
          display.menuCommand(menCmd);
          if(callback.menuCommand){
            callback.menuCommand(menCmd);
          }
        }
      }
      break;
#endif
    case BMC_EVENT_TYPE_SYSTEM_TYPER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
          // display the stopwatch
        }
      }
      break;
    // SKETCH BYTES
    case BMC_EVENT_TYPE_SKETCH_BYTE:
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
          streamToSketch(BMC_DEVICE_ID_SKETCH_BYTES, tmp, data.name);
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
          streamToSketch(BMC_DEVICE_ID_SKETCH_BYTES, tmp, data.name);
          setSketchByte(byteA, tmp);
          if(callback.storeUpdated){
            callback.storeUpdated();
          }
        }
      } else {
        return false;
      }
      break;

    // PAGES
    case BMC_EVENT_TYPE_PAGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            scrollPage(scroll.direction, scroll.endless, scroll.amount);
          } else {
            setPage(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          scrollPage(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (event & 0x3FFF) == page;
        } else {
#if defined(BMC_HAS_DISPLAY)
          #if BMC_MAX_PAGES < 10
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+1), "%01u");
          #elif BMC_MAX_PAGES < 100
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+1), "%02u");
          #else
            display.renderNumber(deviceIndex, isOled, e.type, (uint16_t)((event & 0x3FFF)+1), "%03u");
          #endif

          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PAGE_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        return false;
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (event & 0x3FFF) == page;
        } else {
#if defined(BMC_HAS_DISPLAY)
          uint16_t pageN = (event & 0x3FFF);
          if(pageN < BMC_MAX_PAGES){
            bmcStoreName t = globals.getDeviceName(store.pages[pageN].name);
            display.renderText(deviceIndex, isOled, e.type, t.name);
          }
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PAGE_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          #if BMC_MAX_PAGES < 10
            display.renderNumber(deviceIndex, isOled, e.type, page+1, "%01u");
          #elif BMC_MAX_PAGES < 100
            display.renderNumber(deviceIndex, isOled, e.type, page+1, "%02u");
          #else
            display.renderNumber(deviceIndex, isOled, e.type, page+1, "%02u");
          #endif
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PAGE_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          if(page < BMC_MAX_PAGES){
            bmcStoreName t = globals.getDeviceName(store.pages[page].name);
            display.renderText(deviceIndex, isOled, e.type, t.name);
          }
          return false;
#endif
        }
      }
      break;














    // PRESETS
#if BMC_MAX_PRESETS > 0
    case BMC_EVENT_TYPE_PRESET:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(group == BMC_DEVICE_GROUP_BUTTON){
          if(scroll.enabled){
            presets.scrollPreset(scroll.direction, scroll.endless, scroll.amount);
          } else {
            presets.setPreset(byteA);
          }
        } else if(group == BMC_DEVICE_GROUP_ENCODER){
          presets.scrollPreset(scroll.direction, scroll.endless, scroll.amount);
        }
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return byteA == presets.get();
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+1, "%02u");
#endif
        }
      }
      break;

    case BMC_EVENT_TYPE_PRESET_SELECTED:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, presets.get()+1, "%02u");
#endif
      }
      break;
    case BMC_EVENT_TYPE_PRESET_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name);

#endif
      }
      break;
    case BMC_EVENT_TYPE_PRESET_SELECTED_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = presets.getName();
        display.renderText(deviceIndex, isOled, e.type, t.name);
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
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return byteA == presets.getBank();
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+1, "%02u");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_BANK_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, presets.getBank()+1, "%02u");
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
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.get());
        } else {
#if defined(BMC_HAS_DISPLAY)
          display.renderNumber(deviceIndex, isOled, e.type, byteA+1, "%02u");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        display.renderNumber(deviceIndex, isOled, e.type, setLists.get()+1, "%02u");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSetName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name);
#endif
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSetName();
        display.renderText(deviceIndex, isOled, e.type, t.name);
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
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.get());
        } else {
#if defined(BMC_HAS_DISPLAY)
          /*
          char str[4] = "";
          sprintf(str, "%02u", byteA+1);
          display.renderText(deviceIndex, isOled, e.type, str);
          */
          display.renderNumber(deviceIndex, isOled, e.type, byteA+1, "%02u");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_SONG_SELECTED:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        /*
        char str[4] = "";
        sprintf(str, "%02u", setLists.getSong()+1);
        display.renderText(deviceIndex, isOled, e.type, str);
        */
        display.renderNumber(deviceIndex, isOled, e.type, setLists.getSong()+1, "%02u");
#endif
      }
      break;
    case BMC_EVENT_TYPE_SONG_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSongName(byteA);
        display.renderText(deviceIndex, isOled, e.type, t.name);
#endif
      }
      break;
    case BMC_EVENT_TYPE_SONG_SELECTED_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getSongName();
        display.renderText(deviceIndex, isOled, e.type, t.name);
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
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return (byteA == setLists.get());
        } else {
#if defined(BMC_HAS_DISPLAY)
          /*
          char str[4] = "";
          sprintf(str, "%02u", byteA+1);
          display.renderText(deviceIndex, isOled, e.type, str);
          */
          display.renderNumber(deviceIndex, isOled, e.type, byteA+1, "%02u");
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        /*
        char str[4] = "";
        sprintf(str, "%02u", setLists.getPart()+1);
        display.renderText(deviceIndex, isOled, e.type, str);
        */
        display.renderNumber(deviceIndex, isOled, e.type, setLists.getPart()+1, "%02u");
#endif
      }
      break;
    case BMC_EVENT_TYPE_PART_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getPartName();
        display.renderText(deviceIndex, isOled, e.type, t.name);
#endif
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED_NAME:
      if(group == BMC_DEVICE_GROUP_DISPLAY){
#if defined(BMC_HAS_DISPLAY)
        bmcStoreName t = setLists.getPartName();
        display.renderText(deviceIndex, isOled, e.type, t.name);
#endif
      }
      break;
    // PIXELS
    case BMC_EVENT_TYPE_PIXEL_PROGRAM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(group != BMC_DEVICE_GROUP_DISPLAY){
          return false;
        } else {

        }
      }
      break;
#endif
    // EXTERNAL SYNC


#ifdef BMC_USE_DAW_LC
    case BMC_EVENT_TYPE_DAW_BUTTON:
      // handled by BMC::handleButton
      return false;
      break;
    case BMC_EVENT_TYPE_DAW_LED:
      if(ioType==BMC_EVENT_IO_TYPE_OUTPUT && group != BMC_DEVICE_GROUP_LED){
        return sync.daw.getLedState(byteA, byteB);
      }
      break;
    case BMC_EVENT_TYPE_DAW_ENCODER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT && group == BMC_DEVICE_GROUP_ENCODER){
        return sync.daw.getLedState(byteA, byteB);
      }
      break;
    case BMC_EVENT_TYPE_DAW_DISPLAY:
      {
#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_DAW_LC)
        if(byteA==0){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_DEVICE_ID_ILI){
              display.updateDawMeters();
            }
          #endif
        } else if(byteA == 1){
          bmcStoreName t = sync.daw.getLcdTrackName(byteB);
          display.renderText(deviceIndex, isOled, e.type, t.name);

        } else if(byteA == 2){
          bmcStoreName t = sync.daw.getLcdTrackValue(byteB);
          display.renderText(deviceIndex, isOled, e.type, t.name);
        }
#endif
      }
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        switch(byteA){
          case 0:  return sync.fas.connected();
          case 1:  return sync.fas.isTunerActive();
          case 2:  return sync.fas.tempoReceived()?BMC_PULSE_LED_EVENT:BMC_IGNORE_LED_EVENT;
          case 3:  return sync.fas.looperPlaying();
          case 4:  return sync.fas.looperRecording();
          case 5:  return sync.fas.looperDubbing();
          case 6:  return sync.fas.looperRecordingOrDubbing();
          case 7:  return sync.fas.looperReversed();
          case 8:  return sync.fas.looperHalf();
          case 9:  return sync.fas.looperStoppedWithTrack();
          case 10: return sync.fas.tunerInTune();
          case 11: return sync.fas.tunerFlat();
          case 12: return sync.fas.tunerFlatter();
          case 13: return sync.fas.tunerFlattest();
          case 14: return sync.fas.tunerSharp();
          case 15: return sync.fas.tunerSharper();
          case 16: return sync.fas.tunerSharpest();
        }
      }
      break;
    case BMC_EVENT_TYPE_FAS_PRESET:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        return sync.fas.getPresetNumber()==(event & 0xFFFF);
      }
      break;
    case BMC_EVENT_TYPE_FAS_SCENE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        return sync.fas.getSceneNumber()==byteA;
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        bool state = false;
        if(sync.fas.connected()){
          if(byteA==0){ // on if bypassed
            state = sync.fas.isBlockBypassed(byteB);
          } else if(byteA==1){ // on if engage
            state = sync.fas.isBlockEngaged(byteB);
          } else if(byteA==2){ // on if X
            state = sync.fas.isBlockX(byteB);
          } else if(byteA==3){ // on if Y
            state = sync.fas.isBlockY(byteB);
          }
        }
        return state;
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK_PARAM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(group != BMC_DEVICE_GROUP_DISPLAY){
        //
      }
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
