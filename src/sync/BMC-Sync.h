/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SYNC_H
#define BMC_SYNC_H

#include "utility/BMC-Def.h"
#include "midi/BMC-MidiClock.h"

#if defined(BMC_USE_SYNC)

#if defined(BMC_USE_DAW_LC)
  #include "sync/daw/BMC-DawLogicControl.h"
#endif

#if defined(BMC_USE_BEATBUDDY)
  #include "sync/beatbuddy/BMC-BeatBuddy.h"
#endif

#if defined(BMC_USE_HELIX)
  #include "sync/helix/BMC-Helix.h"
#endif

#if defined(BMC_USE_FAS)
  #include "sync/fas/BMC-Fas.h"
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
#if defined(BMC_USE_BEATBUDDY)
  // handles beatbuddy syncing and commands
  BMCBeatBuddy beatBuddy;
#endif
#if defined(BMC_USE_HELIX)
  // handles helix commands
  BMCHelix helix;
#endif
#if defined(BMC_USE_FAS)
  // handles Fractal devices syncing
  BMCFas fas;
#endif
#if defined(BMC_USE_KEMPER)
// handles Kemper devices see src/sync/BMC-Kemper.h
  BMCKemper kemper;
#endif
  BMCSync(
    BMCMidi& t_midi,
    BMCMidiClock& t_midiClock,
    bmcStoreGlobal& t_global,
    BMCCallbacks& t_callback
  )
  :
  midi(t_midi),
  midiClock(t_midiClock),
  global(t_global),
  callback(t_callback)
  #ifdef BMC_USE_DAW_LC
    ,daw(midi, global, callback)
  #endif
  #ifdef BMC_USE_BEATBUDDY
    ,beatBuddy(midi, midiClock)
  #endif
  #ifdef BMC_USE_HELIX
    ,helix(midi)
  #endif
  #ifdef BMC_USE_FAS
    ,fas(midi)
  #endif
  #ifdef BMC_USE_KEMPER
    ,kemper(midi)
  #endif
  {}

};

#endif

#endif