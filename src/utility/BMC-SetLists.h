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
#define BMC_SETLIST_FLAG_PART_RECALL 3

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
  void update(){
    
  }
  void setPartRecall(bool value){
    // BMC_PRINTLN("BMC_SETLIST_FLAG_PART_RECALL", value)
    flags.write(BMC_SETLIST_FLAG_PART_RECALL, value);
  }
  void set(uint8_t n){
    if(n >= BMC_MAX_SETLISTS){
      return;
    }
    
    // allow switching to setlist that has no songs assigned
    if(setList != n){
      setList = n;
      BMC_PRINTLN("Set SetList #", n);
      flags.on(BMC_FLAG_SETLISTS_CHANGED);
      if(autoTriggerFirstSong()){
        setSong(0);
      }
    }
  }
  void setSong(uint8_t n){
    if(n >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    // allow switching to song without parts
    if(song != n || flags.read(BMC_FLAG_SETLISTS_CHANGED)){
      flags.on(BMC_FLAG_SETLISTS_SONG_CHANGED);
      song = n;
      uint16_t s = presets.midi.globals.store.global.setLists[setList].events[song];
      if(s > 0 && s < BMC_MAX_SETLISTS_SONGS_LIBRARY){
        songInLibrary = s-1;
      } else {
        songInLibrary = 0xFFFF;
      }
      songEmpty(setHasSong(n)); // song has parts
      if(autoTriggerFirstPart()){
        // trigger first part
        setPart(0);
      }
      BMC_PRINTLN("Song #", n, "songInLibrary", songInLibrary);
    }
  }
  void setPart(uint8_t n){
    if(n >= BMC_MAX_SETLISTS_SONG_PARTS){
      return;
    }
    if(songPart != n || flags.read(BMC_SETLIST_FLAG_PART_RECALL) || flags.read(BMC_FLAG_SETLISTS_SONG_CHANGED)){
      songPart = n;
      if(songHasPart(songPart)){
        partEmpty(false);
        if(songInLibrary < BMC_MAX_SETLISTS_SONGS_LIBRARY){
          uint16_t value = presets.midi.globals.store.global.songLibrary[songInLibrary].events[songPart];
          if(value > 0){
            presets.setByIndex(value-1, true);
          }
        }
      } else {
        partEmpty(true);
      }
      BMC_PRINTLN("Part #", songPart);
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
  void scrollSet(bool t_direction, bool t_wrap, uint8_t t_amount, uint8_t t_min, uint8_t t_max){
    // if(!presets.midi.globals.onBoardEditorActive()){
    //   if(presets.midi.globals.settings.getDisplayListMode() && !presets.midi.globals.displayListsActive()){
    //     presets.midi.globals.setRenderDisplayList(BMC_DEVICE_ID_SETLIST);
    //     return;
    //   }
    // }
    if(presets.midi.globals.setRenderDisplayList(BMC_DEVICE_ID_SETLIST)){
      return;
    }
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_SETLISTS-1;
    }
    if(t_max > BMC_MAX_SETLISTS-1){
      t_max = BMC_MAX_SETLISTS-1;
    }
    if(t_min > BMC_MAX_SETLISTS-1){
      t_min = 0;
    }
    BMCScroller <uint8_t> scroller(t_min, t_max);
    set(scroller.scroll(t_amount, t_direction, t_wrap, setList, t_min, t_max));
  }
  void scrollSong(bool t_direction, bool t_wrap, uint8_t t_amount, uint8_t t_min, uint8_t t_max){
    // if(!presets.midi.globals.onBoardEditorActive()){
    //   if(presets.midi.globals.settings.getDisplayListMode() && !presets.midi.globals.displayListsActive()){
    //     presets.midi.globals.setRenderDisplayList(BMC_DEVICE_ID_SETLIST_SONG);
    //     return;
    //   }
    // }
    if(presets.midi.globals.setRenderDisplayList(BMC_DEVICE_ID_SETLIST_SONG)){
      return;
    }
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_SETLISTS_SONGS-1;
    }
    if(t_max > BMC_MAX_SETLISTS_SONGS-1){
      t_max = BMC_MAX_SETLISTS_SONGS-1;
    }
    if(t_min > BMC_MAX_SETLISTS_SONGS-1){
      t_min = 0;
    }

    BMCScroller <uint8_t> scroller(t_min, t_max);
    setSong(scroller.scroll(t_amount, t_direction, t_wrap, song, t_min, t_max));
  }
  void scrollPart(bool t_direction, bool t_wrap, uint8_t t_amount, uint8_t t_min, uint8_t t_max){
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_SETLISTS_SONG_PARTS-1;
    }
    if(t_max > BMC_MAX_SETLISTS_SONG_PARTS-1){
      t_max = BMC_MAX_SETLISTS_SONG_PARTS-1;
    }
    if(t_min > BMC_MAX_SETLISTS_SONG_PARTS-1){
      t_min = 0;
    }
    BMCScroller <uint8_t> scroller(t_min, t_max);
    setPart(scroller.scroll(t_amount, t_direction, t_wrap, song, t_min, t_max));
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
    if(songInLibrary > BMC_MAX_SETLISTS_SONGS_LIBRARY){
      return false;
    }
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
    if(songHasParts() && presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0] > t_part){
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



  void getSetName(char * str){
    getSetName(setList, str);
  }
  void getSetName(uint8_t t_set, char * str){
    if(t_set < BMC_MAX_SETLISTS && presets.midi.globals.store.global.setLists[t_set].name != 0){
      bmcStoreName t;
      t = presets.midi.globals.getDeviceName(presets.midi.globals.store.global.setLists[t_set].name);
      strcpy(str, t.name);
      return;
    }
    sprintf(str, "Set # %02u", t_set+midi.globals.offset);
  }
  void getSetStr(char * str){
    getSetStr(setList, str);
  }
  void getSetStr(uint16_t t_setList, char * str){
    sprintf(str, "%u", t_setList+midi.globals.offset);
  }

  void getSongName(char * str){
    getSongName(song, str);
  }
  void getSongName(uint8_t t_song, char * str){
    if(presets.midi.globals.store.global.setLists[setList].settings[0] > t_song){
      uint16_t s = presets.midi.globals.store.global.setLists[setList].events[t_song]-1;
      if(presets.midi.globals.store.global.songLibrary[s].name != 0){
        uint16_t nameIndex = presets.midi.globals.store.global.songLibrary[s].name;
        bmcStoreName t = presets.midi.globals.getDeviceName(nameIndex);
        strcpy(str, t.name);
        return;
      }
    }
    sprintf(str, "Song # %02u", t_song+midi.globals.offset);
  }

  void getSongStr(char * str){
    getSongStr(song, str);
  }
  void getSongStr(uint16_t t_song, char * str){
    sprintf(str, "%u", t_song+midi.globals.offset);
  }

  void getPartName(char * str){
    getPartName(songPart, str);
  }
  void getPartName(uint8_t t_part, char * str){
    if(songHasParts() && presets.midi.globals.store.global.songLibrary[songInLibrary].settings[0] > t_part){
      uint16_t p = presets.midi.globals.store.global.songLibrary[songInLibrary].events[t_part]-1;
      if(p < BMC_MAX_PRESETS && presets.midi.globals.store.global.presets[p].name != 0){
        uint16_t nameIndex = presets.midi.globals.store.global.presets[p].name;
        bmcStoreName t = presets.midi.globals.getDeviceName(nameIndex);
        strcpy(str, t.name);
        return;
      }
    }
    sprintf(str, "Part # %02u", t_part+midi.globals.offset);
  }
  void getPartStr(char * str){
    getPartStr(songPart, str);
  }
  void getPartStr(uint16_t t_songPart, char * str){
    sprintf(str, "%u", t_songPart+midi.globals.offset);
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
