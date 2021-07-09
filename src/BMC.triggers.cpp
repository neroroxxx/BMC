/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_TRIGGERS > 0
  void BMC::readTrigger(){
    if(!triggers.isAllowed()){
      return;
    }
    for(uint8_t index = 0, n=triggers.available(); index < n; index++){
      if(triggers.isValidTrigger(index)){
        processTrigger(index);
      }
    }
  }
  void BMC::processTrigger(uint8_t index){
    #if !defined(BMC_FAST_MODE)
    if(index>=BMC_MAX_TRIGGERS){
      BMC_PRINTLN("!!! INVALID TRIGGER",index,"!!!");
      return;
    }
    #endif
    BMC_PRINTLN("*** processTrigger HAS TRIGGER ***");
    uint32_t event = triggers.getEvent(index);
    uint8_t type = BMC_GET_BYTE(0,event);
    uint8_t byteA = BMC_GET_BYTE(1,event);
    uint8_t byteB = BMC_GET_BYTE(2,event);
    uint8_t byteC = BMC_GET_BYTE(3,event);

    switch(parseMidiEventType(type)){
      case BMC_TRIGGER_EVENT_TYPE_CUSTOM:
        if(callback.triggerCustom){
          callback.triggerCustom(byteA);
        }
        break;
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_CONTROL_CHANGE:
        //byteC = ports
        midi.send(byteC, event);
        streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA, byteB);
        break;
      case BMC_MIDI_PROGRAM_CHANGE:
        //byteC = ports
        midi.send(byteC, event);
        streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA);
        break;
      case BMC_TRIGGER_EVENT_TYPE_RELAY_MESSAGE:
        // event (bits 8 to 15) = Ports
        midi.send(byteA, midi.message);
        BMC_PRINTLN("BMCTriggers BMC_TRIGGER_EVENT_TYPE_RELAY_MESSAGE");
        break;
      case BMC_TRIGGER_EVENT_TYPE_CLOCK_TAP:
        midiClock.tap();
        BMC_PRINTLN("BMCTriggers BMC_TRIGGER_EVENT_TYPE_CLOCK_TAP");
        break;
      case BMC_TRIGGER_EVENT_TYPE_ACTIVE_SENSE:
        // event (bits 08 to 15) = Command
        // event (bits 16 to 23) = Ports
        midiActiveSense.command(byteA, byteB);
        BMC_PRINTLN("BMCTriggers BMC_TRIGGER_EVENT_TYPE_ACTIVE_SENSE");
        break;
      case BMC_TRIGGER_EVENT_TYPE_PAGE:
        // event (bits 08 to 15) = Page Number
        setPage(byteA);
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_PAGE");
        break;

#if BMC_MAX_PAGES > 1
      case BMC_TRIGGER_EVENT_TYPE_PAGE_SCROLL:
        // event (bits 08 to 15) = Flags
        // event (bits 16 to 23) = Min
        // event (bits 24 to 31) = Max
        scrollPage(
          byteA,
          byteB,
          byteC,
          1
        );
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_PAGE_SCROLL");
        break;
#endif

#if BMC_MAX_BUTTONS > 0
      case BMC_TRIGGER_EVENT_TYPE_BUTTON:
        // event (bits 08 to 15) = Button Index
        // event (bits 16 to 23) = Type
        if(byteA < BMC_MAX_BUTTONS){
          if(byteB==0){// auto
            buttons[byteA].triggerToggle();
          } else if(byteB==BMC_BUTTON_PRESS_TYPE_PRESS){
            buttons[byteA].triggerPress();
          } else if(byteB==BMC_BUTTON_PRESS_TYPE_RELEASE){
            buttons[byteA].triggerRelease();
          }
        }
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_BUTTON");
        break;
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
      case BMC_TRIGGER_EVENT_TYPE_GLOBAL_BUTTON:
        // event (bits 08 to 15) = Button Index
        // event (bits 16 to 23) = Type
        if(byteA < BMC_MAX_GLOBAL_BUTTONS){
          if(byteB==0){// auto
            globalButtons[byteA].triggerToggle();
          } else if(byteB==BMC_BUTTON_PRESS_TYPE_PRESS){
            globalButtons[byteA].triggerPress();
          } else if(byteB==BMC_BUTTON_PRESS_TYPE_RELEASE){
            globalButtons[byteA].triggerRelease();
          }
        }
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_GLOBAL_BUTTON");
        break;
#endif

#if BMC_MAX_ENCODERS > 0
      case BMC_TRIGGER_EVENT_TYPE_ENCODER:
        if(byteA < BMC_MAX_ENCODERS){
          if(byteB==0){
            encoders[byteA].triggerDown();
          } else {
            encoders[byteA].triggerUp();
          }
        }
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_ENCODER");
        break;
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
      case BMC_TRIGGER_EVENT_TYPE_GLOBAL_ENCODER:
        if(byteA < BMC_MAX_GLOBAL_ENCODERS){
          if(byteB==0){
            encoders[byteA].triggerDown();
          } else {
            encoders[byteA].triggerUp();
          }
        }
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_GLOBAL_ENCODER");
        break;
#endif

#if BMC_MAX_NL_RELAYS > 0
      case BMC_TRIGGER_EVENT_TYPE_RELAY_NL_CONTROL:
        if(byteA < BMC_MAX_NL_RELAYS){
          relaysNL[byteA].command(byteB);
          BMC_PRINTLN(">>> byteA",byteA,"byteB",byteB);
          BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_RELAY_NL_CONTROL");
        }
        break;
#endif

#if BMC_MAX_L_RELAYS > 0
      case BMC_TRIGGER_EVENT_TYPE_RELAY_L_CONTROL:
        if(byteA < BMC_MAX_L_RELAYS){
          relaysL[byteA].command(byteB);
          BMC_PRINTLN(">>> byteA",byteA,"byteB",byteB);
          BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_RELAY_L_CONTROL");
        }
        break;
#endif

#if BMC_MAX_LIBRARY > 0
      case BMC_TRIGGER_EVENT_TYPE_LIBRARY:
        // event (bits 08 to 17) = Library Index
        library.send(BMC_EVENT_TO_LIBRARY_NUM(event>>8));
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_LIBRARY");
        break;
#endif

#if BMC_MAX_LIBRARY > 1
      case BMC_TRIGGER_EVENT_TYPE_LIBRARY2:
        // event (bits 08 to 17) = Library Index
        // event (bits 18 to 27) = Library Index
        library.send(
          BMC_EVENT_TO_LIBRARY_NUM(event>>8),
          BMC_EVENT_TO_LIBRARY_NUM(event>>18)
        );
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_LIBRARY2");
        break;
#endif

#if BMC_MAX_PRESETS > 0
      case BMC_TRIGGER_EVENT_TYPE_PRESET:
        // event (bits 08 to 17) = Preset Index
        presets.set(BMC_EVENT_TO_PRESET_NUM(event>>8));
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_PRESET");
        break;
#endif

#if BMC_MAX_PRESETS > 1
      case BMC_TRIGGER_EVENT_TYPE_PRESET_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = maximum preset for scrolling
        // byteC = maximum preset for scrolling
        presets.scroll(
          1,
          byteA,
          0,
          BMC_EVENT_TO_PRESET_NUM((byteC<<8) | byteB)
        );
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_PRESET_SCROLL");
        break;
#endif

#if BMC_MAX_SETLISTS > 0
      case BMC_TRIGGER_EVENT_TYPE_SETLIST:
        // event (bits 08 to 15) = setList Index
        setLists.set(byteA);
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_SETLIST");
        break;
#endif

#if BMC_MAX_SETLISTS > 1
      case BMC_TRIGGER_EVENT_TYPE_SETLIST_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum setList for scrolling
        // byteC = maximum setList for scrolling
        setLists.scroll(
          1,
          byteA,
          byteB,
          byteC
        );
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_SETLIST_SCROLL");
        break;
#endif


#if BMC_MAX_SETLISTS_SONGS > 0
      case BMC_TRIGGER_EVENT_TYPE_SETLIST_SONG:
        // event (bits 08 to 15) = SetList Song Index
        setLists.setSong(byteA);
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_SETLIST");
        break;
#endif

#if BMC_MAX_SETLISTS_SONGS > 1
      case BMC_TRIGGER_EVENT_TYPE_SETLIST_SONG_SCROLL:
        // byteA (flags) = bit-0 scroll direction, down (0), up (1)
        // byteA (flags) = bit-1 limit, limited (0), endless (1)
        // byteB = minimum song for scrolling
        // byteC = maximum song for scrolling
        setLists.scrollSong(
          1,
          byteA,
          byteB,
          byteC
        );
        BMC_PRINTLN("processTrigger BMC_TRIGGER_EVENT_TYPE_SETLIST_SCROLL");
        break;
#endif
    }
    if(callback.midiTriggerReceived){
      callback.midiTriggerReceived(
        triggers.getSource(index),
        triggers.getEvent(index)
      );
    }
  }
#endif
