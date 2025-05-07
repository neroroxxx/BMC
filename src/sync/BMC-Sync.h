/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SYNC_H
#define BMC_SYNC_H

#include "utility/BMC-Def.h"
#include "midi/BMC-MidiClock.h"

#if defined(BMC_USE_SYNC)

#if defined(BMC_USE_DAW_LC)
  #include "sync/daw/BMC-DawLogicControl.h"
#endif

#if defined(BMC_USE_FAS)
  #if defined(BMC_USE_FAS3)
    #include "sync/fas/BMC-Fas3.h"
  #else
    #include "sync/fas/BMC-Fas.h"
  #endif
#endif

#if defined(BMC_USE_HELIX)
  #include "sync/helix/BMC-Helix.h"
#endif


#if defined(BMC_USE_BEATBUDDY)
  #include "sync/beatbuddy/BMC-BeatBuddy.h"
#endif

#if defined(BMC_USE_KEMPER)
  #include "sync/kemp/BMC-Kemp.h"
#endif


class BMCSync {
private:
  BMCMidi& midi;
  BMCMidiClock& midiClock;
  bmcStoreGlobal& global;
  BMCCallbacks& callback;
public:
#if defined(BMC_USE_DAW_LC)
  BMCDawLogicControl daw;
#endif

#if defined(BMC_USE_FAS)
  BMCFas fas;
#endif

#if defined(BMC_USE_HELIX)
  // handles helix commands
  BMCHelix helix;
#endif

#if defined(BMC_USE_BEATBUDDY)
  // handles beatbuddy syncing and commands
  BMCBeatBuddy beatBuddy;
#endif

#if defined(BMC_USE_KEMPER)
// handles Kemper devices see src/sync/BMC-Kemper.h
  BMCKemper kemper;
#endif
  BMCSync(
    BMCMidi& t_midi,
    BMCMidiClock& t_midiClock,
    BMCCallbacks& t_callback
  )
  :
  midi(t_midi),
  midiClock(t_midiClock),
  global(midi.globals.store.global),
  callback(t_callback)
  #if defined(BMC_USE_DAW_LC)
    ,daw(midi, global, callback)
  #endif
  #if defined(BMC_USE_FAS)
    ,fas(midi)
  #endif
  #if defined(BMC_USE_HELIX)
    ,helix(midi)
  #endif
  #if defined(BMC_USE_BEATBUDDY)
    ,beatBuddy(midi, midiClock)
  #endif
  #if defined(BMC_USE_KEMPER)
    ,kemper(midi)
  #endif
  {
    
  }

  // ---------------------------------------------
  void begin(){
#if defined(BMC_DEBUG)
    printDebug();
#endif

#if defined(BMC_USE_DAW_LC)
  daw.begin();
#endif

#if defined(BMC_USE_FAS)
    fas.begin();
#endif

#if defined(BMC_USE_HELIX)
  
#endif

#if defined(BMC_USE_BEATBUDDY)
  
#endif

#if defined(BMC_USE_KEMPER)
  
#endif
  }

  // ---------------------------------------------
  void update(){
#if defined(BMC_USE_DAW_LC)
    daw.update();
#endif

#if defined(BMC_USE_FAS)
    fas.update();
#endif

#if defined(BMC_USE_HELIX)
    helix.update();
#endif

#if defined(BMC_USE_BEATBUDDY)
    beatBuddy.update();
#endif

#if defined(BMC_USE_KEMPER)
    kemper.update();
#endif
  }
  void reassign(){
#if defined(BMC_USE_DAW_LC)
    // 
#endif

#if defined(BMC_USE_FAS)
    fas.reassign();
#endif

#if defined(BMC_USE_HELIX)
    // 
#endif

#if defined(BMC_USE_BEATBUDDY)
    beatBuddy.reassign();
#endif

#if defined(BMC_USE_KEMPER)
    // 
#endif
  }

  // ---------------------------------------------
  void incoming(BMCMidiMessage& message){
#if defined(BMC_USE_DAW_LC)
    daw.incoming(message);
#endif

#if defined(BMC_USE_FAS)
    fas.incoming(message);
#endif

#if defined(BMC_USE_HELIX)
    
#endif

#if defined(BMC_USE_BEATBUDDY)
    beatBuddy.incoming(message);
#endif

#if defined(BMC_USE_KEMPER)
    kemper.incoming(message);
#endif
  }

  // ---------------------------------------------
  void assignSettings(){
#if defined(BMC_USE_DAW_LC)
    
#endif

#if defined(BMC_USE_FAS)
    #if defined(BMC_USE_FAS3)
      fas.setMidiChannel(midi.globals.settings.getFas3MidiChannel()+1);
    #endif
#endif

#if defined(BMC_USE_HELIX)
    helix.setDeviceId(midi.globals.settings.getHelixId());
    helix.setChannel(midi.globals.settings.getHelixChannel()+1);
    helix.setPortBit(midi.globals.settings.getHelixPort());
#endif

#if defined(BMC_USE_BEATBUDDY)
    beatBuddy.enableSync(midi.globals.settings.getBeatBuddySync());
    beatBuddy.setChannel(midi.globals.settings.getBeatBuddyChannel()+1);
    beatBuddy.setPortBit(midi.globals.settings.getBeatBuddyPort());
#endif

#if defined(BMC_USE_KEMPER)
    
#endif
  }
#if defined(BMC_DEBUG)
  void printDebug(){
    BMC_INFO(
      "SYNC OPTIONS:"
      #if defined(BMC_USE_DAW_LC)
        ," - DAW"
      #endif
  #if defined(BMC_USE_FAS)
      #if defined(BMC_USE_FAS3)
        ," - FAS (Axe FX 3)"
      #else
        ," - FAS (Axe FX 2)"
      #endif
  #endif
      #if defined(BMC_USE_HELIX)
        ," - HELIX"
      #endif
      #if defined(BMC_USE_BEATBUDDY)
        ," - BEATBUDDY"
      #endif
      #if defined(BMC_USE_KEMPER)
        ," - KEMPER"
      #endif
    );
  }
#endif

};

#endif

#endif
