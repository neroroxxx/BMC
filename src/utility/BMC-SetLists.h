/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SETLISTS_H
#define BMC_SETLISTS_H
#if BMC_MAX_PRESETS > 0 && BMC_MAX_SETLISTS > 0 && BMC_MAX_SETLISTS_SONGS > 0

#define BMC_FLAG_SETLISTS_CHANGED 0
#define BMC_FLAG_SETLISTS_SONG_CHANGED 1
#define BMC_FLAG_SETLISTS_SONG_PART_CHANGED 2

//song flags
#define BMC_SETLIST_FLAG_EMPTY_SET  0
#define BMC_SETLIST_FLAG_EMPTY_SONG 1
#define BMC_SETLIST_FLAG_EMPTY_PART 2

#include "utility/BMC-Def.h"

class BMCSetLists {
public:
  BMCSetLists(BMCPresets& t_presets):
            presets(t_presets),
            midi(presets.midi),
            // part of globals
            setList(presets.midi.globals.setList),
            song(presets.midi.globals.song),
            songPart(presets.midi.globals.songPart),
            songInLibrary(presets.midi.globals.songInLibrary),
            songFlags(presets.midi.globals.songFlags)

  {
  }
  void set(uint8_t n=0, bool firstSong=false){
    if(n >= BMC_MAX_SETLISTS){
      return;
    }
    if(presets.midi.globals.store.global.setLists[n].settings[0] > 0){
      setList = n;
      BMC_PRINTLN("Set SetList #", n);
      flags.on(BMC_FLAG_SETLISTS_CHANGED);
      if(autoTriggerFirstSong()){
        setSong(0);
      }
    }
  }
  void setSong(uint8_t n=0){
    if(n >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    if(presets.midi.globals.store.global.setLists[setList].settings[0] > n){
      song = n;
      songInLibrary = presets.midi.globals.store.global.setLists[setList].events[song];
      if(setHasSong(n)){
        songEmpty(false); // song has parts
        if(autoTriggerFirstPart()){
          // trigger first part
          setPart(0);
        }
      } else {
        songEmpty(true);
      }
      BMC_PRINTLN("Song #", n);
      flags.on(BMC_FLAG_SETLISTS_SONG_CHANGED);
    }
  }
  void setPart(uint8_t n=0){
    if(n >= BMC_MAX_SETLISTS_SONG_PARTS){
      return;
    }
    if(presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0] > n){
      songPart = n;
      if(songHasPart(songPart)){
        partEmpty(false);
        uint16_t value = presets.midi.globals.store.global.songLibrary[songInLibrary].events[songPart];
        presets.setByIndex(value);
      } else {
        partEmpty(true);
      }
      BMC_PRINTLN("Part #", n);
      flags.on(BMC_FLAG_SETLISTS_SONG_PART_CHANGED);
    }
  }

  // get setlist info
  uint8_t get(){
    return setList;
  }
  uint8_t getSetListLength(){
    return getSetListLength(setList);
  }
  uint8_t getSetListLength(uint8_t n){
    if(n < BMC_MAX_SETLISTS_SONGS){
      return presets.midi.globals.store.global.setLists[n].settings[0];
    }
    return 0;
  }
  uint8_t getSet(){
    return setList;
  }
  uint8_t getSong(){
    return song;
  }
  uint16_t getSongInLibrary(){
    return songInLibrary;
  }
  uint8_t getPart(){
    return songPart;
  }
  // notification
  bool setListChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_CHANGED);
  }
  bool songChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_SONG_CHANGED);
  }
  bool partChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_SONG_PART_CHANGED);
  }
  uint16_t getSongPreset(){
    return presets.midi.globals.store.global.setLists[setList].events[song];
  }
  uint16_t getSongPreset(uint8_t n){
    if(n<BMC_MAX_SETLISTS_SONGS){
      return presets.midi.globals.store.global.setLists[setList].events[n];
    }
    return 0;
  }
  void scrollSet(bool t_direction, bool t_wrap, uint8_t t_amount, bool firstSong=true){
    uint8_t t_max = BMC_MAX_SETLISTS-1;
    //uint8_t t_max = presets.midi.globals.store.global.setLists[n].settings[0];
    BMCScroller <uint8_t> scroller(0, t_max);
    set(scroller.scroll(t_amount, t_direction, t_wrap, setList, 0, t_max), firstSong);
  }
  void scrollSong(bool t_direction, bool t_wrap, uint8_t t_amount){
    uint8_t len = presets.midi.globals.store.global.setLists[setList].settings[0];

    if(len > 1){
      //uint8_t t_max = BMC_MAX_SETLISTS_SONGS-1;
      uint8_t t_max = presets.midi.globals.store.global.setLists[setList].settings[0]-1;
      BMCScroller <uint8_t> scroller(0, t_max);
      setSong(scroller.scroll(t_amount, t_direction, t_wrap, song, 0, t_max));
    }
  }
  void scrollPart(bool t_direction, bool t_wrap, uint8_t t_amount){
    //uint8_t t_max = BMC_MAX_SETLISTS_SONG_PARTS-1;
    uint8_t t_max = presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0]-1;
    BMCScroller <uint8_t> scroller(0, t_max);
    setPart(scroller.scroll(t_amount, t_direction, t_wrap, song, 0, t_max));
  }
  bool autoTriggerFirstSong(){
    return presets.midi.globals.settings.getSetListTriggerFirstSong();
  }
  bool autoTriggerFirstPart(){
    return presets.midi.globals.settings.getSetListTriggerFirstSongPart();
  }


  // check if the current set has any songs
  bool setHasSongs(){
    return presets.midi.globals.store.global.setLists[setList].settings[0] > 0;
  }
  // check if a specific set has any songs
  bool setHasSongs(uint8_t n){
    if(n > BMC_MAX_SETLISTS){
      return false;
    }
    return presets.midi.globals.store.global.setLists[n].settings[0] > 0;
  }
  // check if the current set has a specific song number
  bool setHasSong(uint8_t n){
    if(!setHasSongs()){
      return false;
    }
    return presets.midi.globals.store.global.setLists[setList].settings[0] > n;
  }



  // check if the current song has any parts
  bool songHasParts(){
    return presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0] > 0;
  }
  // check if the current song has any parts
  bool songHasParts(uint8_t n){
    if(n > BMC_MAX_SETLISTS_SONG_PARTS){
      return false;
    }
    n = presets.midi.globals.store.global.setLists[setList].events[n];
    return presets.midi.globals.store.global.songLibrary[n].settings[0] > 0;
  }
  // check if the current song has a specific part number
  bool songHasPart(uint8_t n){
    if(!songHasParts() || n > BMC_MAX_SETLISTS_SONG_PARTS){
      return false;
    }
    return presets.midi.globals.store.global.songLibrary[songInLibrary].events[n] > 0;
  }

  bmcStoreName getSetName(){
    return getSetName(setList);
  }
  bmcStoreName getSetName(uint8_t t_set){
    if(t_set < BMC_MAX_SETLISTS && presets.midi.globals.store.global.setLists[t_set].name != 0){
      return presets.midi.globals.getDeviceName(presets.midi.globals.store.global.setLists[t_set].name);
    }
    bmcStoreName t;
    sprintf(t.name, "Set # %02u", t_set+midi.globals.offset);
    return t;
  }
  bmcStoreName getSetStr(){
    return getSetStr(setList);
  }
  bmcStoreName getSetStr(uint16_t t_setList){
    bmcStoreName t;
    sprintf(t.name, "%u", t_setList+midi.globals.offset);
    return t;
  }

  bmcStoreName getSongName(){
    return getSongName(song);
  }
  bmcStoreName getSongName(uint8_t t_song){
    if(presets.midi.globals.store.global.setLists[setList].settings[0] > t_song){
      uint16_t s = presets.midi.globals.store.global.setLists[setList].events[t_song]-1;
      if(presets.midi.globals.store.global.songLibrary[s].name != 0){
        return presets.midi.globals.getDeviceName(presets.midi.globals.store.global.songLibrary[s].name);
      }
    }
    bmcStoreName t;
    sprintf(t.name, "Song # %02u", t_song+midi.globals.offset);
    return t;
  }

  bmcStoreName getSongStr(){
    return getSongStr(song);
  }
  bmcStoreName getSongStr(uint16_t t_song){
    bmcStoreName t;
    sprintf(t.name, "%u", t_song+midi.globals.offset);
    return t;
  }

  bmcStoreName getPartName(){
    return getPartName(songPart);
  }
  bmcStoreName getPartName(uint8_t t_part){
    if(presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0] > t_part){
      uint16_t p = presets.midi.globals.store.global.songLibrary[songInLibrary].events[t_part]-1;
      if(p < BMC_MAX_PRESETS && presets.midi.globals.store.global.presets[p].name != 0){
        return presets.midi.globals.getDeviceName(presets.midi.globals.store.global.presets[p].name);
      }
    }
    bmcStoreName t;
    sprintf(t.name, "Part # %02u", t_part+midi.globals.offset);
    return t;
  }
  bmcStoreName getPartStr(){
    return getPartStr(songPart);
  }
  bmcStoreName getPartStr(uint16_t t_songPart){
    bmcStoreName t;
    sprintf(t.name, "%u", t_songPart+midi.globals.offset);
    return t;
  }
  // setlist
  bool setListEmpty(bool state){
    bitWrite(songFlags, BMC_SETLIST_FLAG_EMPTY_SET, state);
    songEmpty(state);
    return state;
  }
  bool setListEmpty(){
    return bitRead(songFlags, BMC_SETLIST_FLAG_EMPTY_SET);
  }
  // song
  bool songEmpty(bool state){
    bitWrite(songFlags, BMC_SETLIST_FLAG_EMPTY_SONG, state);
    partEmpty(state);
    return state;
  }
  bool songEmpty(){
    return bitRead(songFlags, BMC_SETLIST_FLAG_EMPTY_SONG);
  }
  // part
  bool partEmpty(bool state){
    bitWrite(songFlags, BMC_SETLIST_FLAG_EMPTY_PART, state);
    return state;
  }
  bool partEmpty(){
    return bitRead(songFlags, BMC_SETLIST_FLAG_EMPTY_PART);
  }



private:
  BMCPresets& presets;
  BMCMidi& midi;
  uint8_t& setList;
  uint16_t& song;
  uint8_t& songPart;
  uint16_t& songInLibrary;
  uint8_t& songFlags;
  BMCFlags <uint8_t> flags;
};

#endif
#endif
