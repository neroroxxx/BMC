/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>


uint8_t BMC::processEvent(uint8_t deviceType, uint8_t deviceId, uint8_t deviceIndex, uint8_t ioType, uint16_t eventIndex){
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
  switch(e.type){
    case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(deviceType==BMC_DEVICE_TYPE_BUTTON){
          //midi.send(ports, event);// standard midi event
          midi.sendProgramChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB);
          streamMidi(BMC_MIDI_PROGRAM_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB);
          break;
        } else {

        }
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
          uint8_t pc = midi.getLocalProgram(channel);
          return pc == (byteB & 0x7F);
        }
      }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        if(deviceType==BMC_DEVICE_TYPE_BUTTON){
          //midi.send(ports, event);// standard midi event
          midi.sendControlChange(e.ports, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          streamMidi(BMC_MIDI_CONTROL_CHANGE, BMC_TO_MIDI_CHANNEL(byteA), byteB, byteC);
          break;
        } else {

        }
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          uint8_t channel = BMC_TO_MIDI_CHANNEL(byteA);
          uint8_t cc = midi.getLocalControl(channel, byteB);
          return cc == (byteC & 0x7F);
        }
      }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_ON:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_MIDI_NOTE_OFF:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_MIDI_AFTER_TOUCH:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_MIDI_CONTROL_TOGGLE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
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
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
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
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return midiActiveSense.active();
        }
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType == BMC_DEVICE_TYPE_LED){
          return BMC_IGNORE_LED_EVENT;
        }
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType == BMC_DEVICE_TYPE_LED){
          return BMC_IGNORE_LED_EVENT;
        }
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_STATUS:
      if(deviceType == BMC_DEVICE_TYPE_LED){
        return handleStatusLedEvent(byteA);
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
    if(deviceType == BMC_DEVICE_TYPE_LED){
      return globals.hasMidiActivity(byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
    }
      break;
    case BMC_EVENT_TYPE_SYSTEM_SAVE_EEPROM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_MENU:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_TYPER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_BLE_DISCONNECT:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return globals.bleConnected();
        }
      }
      break;
    case BMC_EVENT_TYPE_SYSTEM_STOPWATCH:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (stopwatch.getState() == 1);
        } else {
          // display the stopwatch
        }
      }
      break;
    // SKETCH BYTES
    case BMC_EVENT_TYPE_SKETCH_BYTE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        return false;
      }
      break;

    // PAGES
    case BMC_EVENT_TYPE_PAGE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (event & 0x3FFF) == page;
        } else {
#if defined(BMC_HAS_DISPLAY)
          char str[4] = "";
          #if BMC_MAX_PAGES < 10
            sprintf(str, "%01u", (uint16_t)((event & 0x3FFF)+1));
          #elif BMC_MAX_PAGES < 100
            sprintf(str, "%02u", (uint16_t)((event & 0x3FFF)+1));
          #else
            sprintf(str, "%03u", (uint16_t)((event & 0x3FFF)+1));
          #endif
          //(uint8_t deviceType, uint8_t deviceId, uint8_t deviceIndex, uint8_t ioType, uint16_t event)
          display.renderText(deviceIndex, deviceId==BMC_ITEM_ID_OLED, e.type, str);
          return false;
#endif
        }

      }
      break;
    case BMC_EVENT_TYPE_PAGE_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        return false;
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (event & 0x3FFF) == page;
        } else {
#if defined(BMC_HAS_DISPLAY)
          uint16_t pageN = (event & 0x3FFF);
          if(pageN < BMC_MAX_PAGES){
            bool isOled = deviceId==BMC_ITEM_ID_OLED;
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
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          char str[4] = "";
          #if BMC_MAX_PAGES < 10
            sprintf(str, "%01u", (page+1));
          #elif BMC_MAX_PAGES < 100
            sprintf(str, "%02u", (page+1));
          #else
            sprintf(str, "%03u", (page+1));
          #endif
          display.renderText(deviceIndex, deviceId==BMC_ITEM_ID_OLED, e.type, str);
          return false;
#endif
        }
      }
      break;
    case BMC_EVENT_TYPE_PAGE_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {
#if defined(BMC_HAS_DISPLAY)
          if(page < BMC_MAX_PAGES){
            bool isOled = deviceId==BMC_ITEM_ID_OLED;
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
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return BMC_EVENT_TO_PRESET_NUM(event>>8) == presets.get();
        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_IN_BANK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return presets.isPresetInBank(byteA);
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_IN_BANK_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_IN_BANK_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PRESET_IN_BANK_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_BANK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return byteA == presets.getBank();
        }
      }
      break;
    case BMC_EVENT_TYPE_BANK_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
#endif
#if BMC_MAX_SETLISTS > 0
    // SETLISTS
    case BMC_EVENT_TYPE_SETLIST:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (byteA == setLists.get());
        }
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_SETLIST_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_SONG:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (byteA == setLists.getSong());
        }
      }
      break;
    case BMC_EVENT_TYPE_SONG_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_SONG_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_SONG_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PART:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return (byteA == setLists.getPart());
        }
      }
      break;
    case BMC_EVENT_TYPE_PART_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    case BMC_EVENT_TYPE_PART_SELECTED_NAME:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
          return false;
        } else {

        }
      }
      break;
    // PIXELS
    case BMC_EVENT_TYPE_PIXEL_PROGRAM:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else {
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
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
      if(ioType==BMC_EVENT_IO_TYPE_OUTPUT && deviceType != BMC_DEVICE_TYPE_LED){
        return sync.daw.getLedState(byteA, byteB);
      }
      break;
    case BMC_EVENT_TYPE_DAW_ENCODER:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT && deviceType == BMC_DEVICE_TYPE_ENCODER){
        return sync.daw.getLedState(byteA, byteB);
      }
      break;
    case BMC_EVENT_TYPE_DAW_DISPLAY:
      {
#if defined(BMC_HAS_DISPLAY) && defined(BMC_USE_DAW_LC)
        if(byteA==0){
          #if BMC_MAX_ILI9341_BLOCKS > 0
            if(deviceId==BMC_ITEM_ID_ILI){
              display.updateDawMeters();
            }
          #endif
        } else if(byteA == 1){
          bool isOled = deviceId==BMC_ITEM_ID_OLED;
          bmcStoreName t = sync.daw.getLcdTrackName(byteB);
          display.renderText(deviceIndex, isOled, e.type, t.name);

        } else if(byteA == 2){
          bool isOled = deviceId==BMC_ITEM_ID_OLED;
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
        if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
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
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
        switch(byteA){
          case 0: return sync.fas.connected();
          case 1: return sync.fas.isTunerActive();
          case 2: return sync.fas.tempoReceived()?BMC_PULSE_LED_EVENT:BMC_IGNORE_LED_EVENT;
          case 3: return sync.fas.looperPlaying();
          case 4: return sync.fas.looperRecording();
          case 5: return sync.fas.looperDubbing();
          case 6: return sync.fas.looperRecordingOrDubbing();
          case 7: return sync.fas.looperReversed();
          case 8: return sync.fas.looperHalf();
          case 9: return sync.fas.looperStoppedWithTrack();
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
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
        return sync.fas.getPresetNumber()==(event & 0xFFFF);
      }
      break;
    case BMC_EVENT_TYPE_FAS_SCENE:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
        return sync.fas.getSceneNumber()==byteA;
      }
      break;
    case BMC_EVENT_TYPE_FAS_BLOCK:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
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
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
        //
      }
      break;
#endif
#ifdef BMC_USE_HELIX
    case BMC_EVENT_TYPE_HELIX:
      if(ioType==BMC_EVENT_IO_TYPE_INPUT){
        //
      } else if(deviceType != BMC_DEVICE_TYPE_DISPLAY){
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
