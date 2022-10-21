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

//song flags
#define BMC_SETLIST_FLAG_EMPTY_SET  0
#define BMC_SETLIST_FLAG_EMPTY_SONG 1
#define BMC_SETLIST_FLAG_EMPTY_PART 2

#include "utility/BMC-Def.h"

class BMCSetLists {
public:
  BMCSetLists(BMCGlobals& t_globals, bmcStoreGlobal& t_global, BMCPresets& t_presets):
            globals(t_globals),
            global(t_global),
            presets(t_presets),
            setList(t_globals.setList),
            song(t_globals.song),
            songPart(t_globals.songPart),
            songInLibrary(t_globals.songInLibrary),
            songFlags(t_globals.setListFlags)

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
    songInLibrary = global.setLists[setList].songs[song];
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

  void setPart(uint8_t n=0){
    if(n >= BMC_MAX_SETLISTS_SONG_PARTS){
      return;
    }
    songPart = n;
    //if(songEmpty() && global.songLibrary[songInLibrary].parts[songPart].length==1){
    if(songHasPart(songPart)){
      partEmpty(false);
      bmcPreset_t value = global.songLibrary[songInLibrary].parts[songPart].preset;
      presets.set(value);
    } else {
      partEmpty(true);
    }
    BMC_PRINTLN("Part #", n);
    flags.on(BMC_FLAG_SETLISTS_SONG_CHANGED);
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
      return global.setLists[n].length;
    }
    return 0;
  }
  void getName(char* t_string){
    getName(setList, t_string);
  }
  void getName(uint8_t n, char* t_string){
#if BMC_NAME_LEN_SETLISTS > 1
    if(n < BMC_MAX_SETLISTS){
      strcpy(t_string, global.setLists[n].name);
    }
#endif
  }
  // ****************
  // get song info
  // ****************
  uint8_t getSet(){
    return setList;
  }
  // ****************
  // get song info
  // ****************
  bmcPreset_t getSong(){
    return song;
  }
  // ****************
  // get part info
  // ****************
  uint8_t getPart(){
    return songPart;
  }


  bmcPreset_t getSongPreset(){
    return global.setLists[setList].songs[song];
  }
  bmcPreset_t getSongPreset(uint8_t n){
    if(n<BMC_MAX_SETLISTS_SONGS){
      return global.setLists[setList].songs[n];
    }
    return 0;
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
    uint8_t t_max = BMC_MAX_SETLISTS_SONGS-1;
    if(global.setLists[setList].length > 1){
      t_max = global.setLists[setList].length-1;
    }
    scrollSong(t_amount, t_up, t_up, 0, t_max);
  }
  void scrollSong(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    scrollSong(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scrollSong(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    if(t_min == t_max  || ((t_min==0 && t_max == BMC_MAX_SETLISTS_SONGS-1) && global.setLists[setList].length > 1)){
      t_min = 0;
      t_max = global.setLists[setList].length-1;
    }
    BMCScroller <uint8_t> scroller(0, BMC_MAX_SETLISTS_SONGS-1);
    setSong(scroller.scroll(t_amount, t_up, t_endless, song, t_min, t_max));
  }

  // Part Scrolling
  void scrollPart(uint8_t t_amount, bool t_up, bool t_endless){
    scrollPart(t_amount, t_up, t_up, 0, BMC_MAX_SETLISTS_SONG_PARTS-1);
  }
  void scrollPart(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    scrollPart(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scrollPart(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    BMCScroller <uint8_t> scroller(0, BMC_MAX_SETLISTS_SONG_PARTS-1);
    setPart(scroller.scroll(t_amount, t_up, t_endless, song, t_min, t_max));
  }

  bool autoTriggerFirstPart(){
    return bitRead(global.songLibrary[songInLibrary].settings, 0)==0;
  }

  // notification
  bool setListChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_CHANGED);
  }
  bool songChanged(){
    return flags.toggleIfTrue(BMC_FLAG_SETLISTS_SONG_CHANGED);
  }





  // check if the current set has any songs
  bool setHasSongs(){
    return global.setLists[setList].length > 0;
  }
  // check if a specific set has any songs
  bool setHasSongs(uint8_t n){
    if(n > BMC_MAX_SETLISTS){
      return false;
    }
    return global.setLists[n].length > 0;
  }
  // check if the current set has a specific song number
  bool setHasSong(uint8_t n){
    if(!setHasSongs()){
      return false;
    }
    return global.setLists[setList].length > n;
  }



  // check if the current song has any parts
  bool songHasParts(){
    return global.songLibrary[songInLibrary].length > 0;
  }
  // check if the current song has any parts
  bool songHasParts(uint8_t n){
    if(n > BMC_MAX_SETLISTS_SONG_PARTS){
      return false;
    }
    n = global.setLists[setList].songs[n];
    return global.songLibrary[n].length > 0;
  }
  // check if the current song has a specific part number
  bool songHasPart(uint8_t n){
    if(!songHasParts() || n > BMC_MAX_SETLISTS_SONG_PARTS){
      return false;
    }
    return global.songLibrary[songInLibrary].parts[n].length==1;
  }


  void getSetName(uint8_t n, char * str){
#if BMC_NAME_LEN_SETLISTS > 1
    if(!setHasSongs(n) || n > BMC_MAX_SETLISTS || strlen(global.setLists[n].name)==0){
      strcpy(str, "-");
    } else {
      strcpy(str, global.setLists[n].name);
    }
#else
    strcpy(str, "-");
#endif
  }
  void getSetName(char * str){
#if BMC_NAME_LEN_SETLISTS > 1
    if(!setHasSongs() || strlen(global.setLists[setList].name)==0){
      strcpy(str, "-");
    } else {
      strcpy(str, global.setLists[setList].name);
    }
#else
    strcpy(str, "-");
#endif
  }



  void getSongName(uint8_t n, char * str){
#if BMC_NAME_LEN_SETLIST_SONG > 1
    if(!songHasParts(n) || n > BMC_MAX_SETLISTS_SONGS){
      strcpy(str, "-");
    } else {
      bmcPreset_t s = global.setLists[setList].songs[n];
      if(strlen(global.songLibrary[s].name)==0){
        strcpy(str, "-");
      } else {
        strcpy(str, global.songLibrary[s].name);
      }
    }
#else
    strcpy(str, "-");
#endif
  }
  void getSongName(char * str){
#if BMC_NAME_LEN_SETLIST_SONG > 1
    if(!songHasParts(song)){
      strcpy(str, "-");
    } else {
      bmcPreset_t s = global.setLists[setList].songs[song];
      if(strlen(global.songLibrary[s].name)==0){
        strcpy(str, "-");
      } else {
        strcpy(str, global.songLibrary[s].name);
      }
    }
#else
    strcpy(str, "-");
#endif
  }


  void getPartName(uint8_t n, char * str){
#if BMC_NAME_LEN_SETLIST_SONG_PART > 1
    if(!songHasPart(n) || n > BMC_MAX_SETLISTS_SONG_PARTS || strlen(global.songLibrary[songInLibrary].parts[n].name)==0){
      strcpy(str, "-");
    } else {
      strcpy(str, global.songLibrary[songInLibrary].parts[n].name);
    }
#else
    strcpy(str, "-");
#endif
  }
  void getPartName(char * str){
#if BMC_NAME_LEN_SETLIST_SONG_PART > 1
    if(!songHasPart(songPart) || strlen(global.songLibrary[songInLibrary].parts[songPart].name)==0){
      strcpy(str, "-");
    } else {
      strcpy(str, global.songLibrary[songInLibrary].parts[songPart].name);
    }
#else
    strcpy(str, "-");
#endif
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
  BMCGlobals& globals;
  bmcStoreGlobal& global;
  BMCPresets& presets;
  BMCFlags <uint8_t> flags;
  uint8_t & setList;
  bmcPreset_t & song;
  uint8_t & songPart;
  bmcPreset_t & songInLibrary;
  uint8_t & songFlags;
};

#endif
#endif
