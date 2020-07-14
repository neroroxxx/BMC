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

#include "utility/BMC-Def.h"

class BMCSetLists {
public:
  BMCSetLists(bmcStoreGlobal& t_global, BMCPresets& t_presets):
            global(t_global),
            presets(t_presets)
  {
  }
  void set(uint8_t n=0, bool firstSong=false){
    if(n >= BMC_MAX_SETLISTS){
      return;
    }
    setList = n;
    BMC_PRINTLN("SetList #",n);
    flags.on(BMC_FLAG_SETLISTS_CHANGED);
    if(firstSong){
      setSong(0);
    }
  }
  void setSong(uint8_t n=0){
    if(n >= BMC_MAX_SETLISTS_SONGS){
      return;
    }
    song = n;
    if(global.setLists[n].length > n){
      presets.set(global.setLists[setList].songs[n]);
    }
    BMC_PRINTLN("Song #",n);
    flags.on(BMC_FLAG_SETLISTS_SONG_CHANGED);
  }
  // Set List Scrolling
  void scroll(uint8_t t_amount, bool t_up, bool t_endless){
    scroll(t_amount, t_up, t_up, 0, BMC_MAX_SETLISTS-1);
  }
  void scroll(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    scroll(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scroll(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    BMCScroller <uint8_t> scroller(0, BMC_MAX_SETLISTS-1);
    set(scroller.scroll(t_amount, t_up, t_endless, setList, t_min, t_max));
  }
  // Song Scrolling
  void scrollSong(uint8_t t_amount, bool t_up, bool t_endless){
    scrollSong(t_amount, t_up, t_up, 0, BMC_MAX_SETLISTS_SONGS-1);
  }
  void scrollSong(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    scrollSong(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scrollSong(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    BMCScroller <uint8_t> scroller(0, BMC_MAX_SETLISTS_SONGS-1);
    setSong(scroller.scroll(t_amount, t_up, t_endless, song, t_min, t_max));
  }
  void getName(uint8_t n, char* t_string){
#if BMC_NAME_LEN_SETLISTS > 1
    if(n<BMC_MAX_SETLISTS){
      strcpy(t_string, global.setLists[n].name);
    }
#endif
  }
  uint8_t get(){
    return setList;
  }
  uint8_t getSetListLength(){
    return getSetListLength(setList);
  }
  uint8_t getSetListLength(uint8_t n){
    if(n<BMC_MAX_SETLISTS_SONGS){
      return global.setLists[n].length;
    }
    return 0;
  }
  uint8_t getSong(){
    return song;
  }
  uint8_t getSongPreset(){
    return global.setLists[setList].songs[song];
  }
  uint8_t getSongPreset(uint8_t n){
    if(n<BMC_MAX_SETLISTS_SONGS){
      return global.setLists[setList].songs[n];
    }
    return 0;
  }
  // notification
  bool setListChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_CHANGED);
  }
  bool songChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_SONG_CHANGED);
  }
private:
  uint8_t setList = 0;
  uint8_t song = 0;
  bmcStoreGlobal& global;
  BMCPresets& presets;
  BMCFlags <uint8_t> flags;
};

#endif
#endif
