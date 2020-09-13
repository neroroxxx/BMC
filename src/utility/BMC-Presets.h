/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_PRESETS_H
#define BMC_PRESETS_H
#if BMC_MAX_LIBRARY > 0 && BMC_MAX_PRESETS > 0

#define BMC_FLAG_PRESETS_CHANGED 0
#define BMC_FLAG_PRESETS_BANK_CHANGED 1

#include "utility/BMC-Def.h"

class BMCPresets {
public:
  BMCPresets(BMCMidi& t_midi, bmcStoreGlobal& t_global, BMCLibrary& t_library):
            midi(t_midi),
            global(t_global),
            library(t_library)
  {
  }
  void set(bmcPreset_t index=0, bool overridePorts=false, uint8_t ports=0){
    send(index, overridePorts, ports);
  }
  void setInBank(uint8_t index=0, bool overridePorts=false, uint8_t ports=0){
    if(index >= BMC_MAX_PRESETS_PER_BANK){
      return;
    }
    bmcPreset_t p = index+(bank*BMC_MAX_PRESETS_PER_BANK);
    if(p<BMC_MAX_PRESETS){
      set(p, overridePorts, ports);
    }
  }
  void setBank(uint8_t t_bank){
    if(t_bank < totalBanks && bank != t_bank){
      bank = t_bank;
      flags.on(BMC_FLAG_PRESETS_BANK_CHANGED);
      BMC_PRINTLN("BMCPresets Bank Set", bank);
    }
  }
  void send(bmcPreset_t index, bool overridePorts=false, uint8_t ports=0){
    if(index >= BMC_MAX_PRESETS){
      BMC_PRINTLN("!!! Invalid Preset", index,"!!!");
      return;
    }
    BMC_PRINTLN("Switch to Preset",index);
    if(preset != index){
      flags.on(BMC_FLAG_PRESETS_CHANGED);
      preset = index;
    }

    if(global.presets[index].length==0){
      return;
    }

    for(uint8_t i = 0, n = global.presets[index].length ; i < n ; i++){
      if(i>=BMC_MAX_PRESET_ITEMS){
        break;
      }
      if(overridePorts){
        library.sendWithDifferentPorts(global.presets[index].events[i],ports);
      } else {
        library.send(global.presets[index].events[i]);
      }
    }
  }
  //
  void scroll(uint8_t t_amount, bool t_up, bool t_endless){
    scroll(t_amount, t_up, t_up, 0, BMC_MAX_PRESETS-1);
  }
  void scroll(uint8_t t_amount, uint8_t t_flags, bmcPreset_t t_min, bmcPreset_t t_max){
    scroll(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scroll(uint8_t t_amount, bool t_up, bool t_endless, bmcPreset_t t_min, bmcPreset_t t_max){
    BMCScroller <bmcPreset_t> scroller(0, BMC_MAX_PRESETS-1);
    set(scroller.scroll(t_amount, t_up, t_endless, preset, t_min, t_max));
  }
  //
  void bankScroll(uint8_t t_amount, bool t_up, bool t_endless){
    bankScroll(t_amount, t_up, t_up, 0, totalBanks-1);
  }
  void bankScroll(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    bankScroll(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void bankScroll(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    BMCScroller <uint8_t> scroller(0, totalBanks-1);
    setBank(scroller.scroll(t_amount, t_up, t_endless, bank, t_min, t_max));
  }
  //
  bmcPreset_t getScrollValue(bmcPreset_t t_value, uint8_t t_amount, uint8_t t_flags, bmcPreset_t t_min, bmcPreset_t t_max){
    return getScrollValue(t_value, t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  bmcPreset_t getScrollValue(bmcPreset_t t_value, uint8_t t_amount, bool t_direction, bool t_endless, bmcPreset_t t_min, bmcPreset_t t_max){
    BMCScroller <bmcPreset_t> scroller(0, BMC_MAX_PRESETS-1);
    return scroller.scroll(t_amount, t_direction, t_endless, t_value, t_min, t_max);
  }
  //
  void scrollInBank(uint8_t t_amount, bool t_up, bool t_endless){
    scrollInBank(t_amount, t_up, t_up, 0, BMC_MAX_PRESETS_PER_BANK-1);
  }
  void scrollInBank(uint8_t t_amount, uint8_t t_flags, uint8_t t_min, uint8_t t_max){
    scrollInBank(t_amount, bitRead(t_flags,0), bitRead(t_flags,1), t_min, t_max);
  }
  void scrollInBank(uint8_t t_amount, bool t_up, bool t_endless, uint8_t t_min, uint8_t t_max){
    // first preset of bank
    uint8_t s = bank * BMC_MAX_PRESETS_PER_BANK;
    t_min += s;
    t_max += t_min;
    BMCScroller <bmcPreset_t> scroller(t_min, t_max);
    bmcPreset_t p = scroller.scroll(t_amount, t_up, t_endless, preset, t_min, t_max);
    if(p<BMC_MAX_PRESETS){
      set(p);
    }
  }
  bool presetChanged(){
    return flags.toggleIfTrue(BMC_FLAG_PRESETS_CHANGED);
  }
  bool peekChanged(){
    return flags.read(BMC_FLAG_PRESETS_CHANGED);
  }
  bool bankChanged(){
    return flags.toggleIfTrue(BMC_FLAG_PRESETS_BANK_CHANGED);
  }
  bmcPreset_t getCurrentPreset(){
    return get();
  }
  bmcPreset_t get(){
    return preset;
  }
  bool isPresetInBank(uint8_t t_value){
    return getPresetInBank() == t_value;
  }
  uint8_t getPresetInBank(){
    uint8_t b = floor((preset*1.0) / BMC_MAX_PRESETS_PER_BANK)* BMC_MAX_PRESETS_PER_BANK;
    return preset-b;
  }
  uint8_t getBank(){
    return bank;
  }
  uint8_t getLength(uint8_t n){
    if(n<BMC_MAX_PRESETS){
      return global.presets[n].length;
    }
    return 0;
  }
  bmcLibrary_t getPresetItem(bmcPreset_t n, uint8_t e){
    if(n<BMC_MAX_PRESETS && e<BMC_MAX_PRESET_ITEMS){
      return global.presets[n].events[e];
    }
    return 0;
  }
  void getName(bmcPreset_t n, char* t_string){
#if BMC_NAME_LEN_PRESETS > 1
    if(n<BMC_MAX_PRESETS){
      strcpy(t_string, global.presets[n].name);
    }
#endif
  }
  uint8_t getTotalBanks(){
    return totalBanks;
  }
private:
  uint8_t bank = 0;
  bmcPreset_t preset = 0;
  BMCMidi& midi;
  bmcStoreGlobal& global;
  BMCLibrary& library;
  BMCFlags <uint8_t> flags;
  const uint8_t totalBanks = (uint8_t) ceil((BMC_MAX_PRESETS * 1.0) / BMC_MAX_PRESETS_PER_BANK);
};

#endif
#endif
