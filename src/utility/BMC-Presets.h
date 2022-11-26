/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_PRESETS_H
#define BMC_PRESETS_H
#if BMC_MAX_PRESETS > 0

#define BMC_FLAG_PRESETS_CHANGED 0
#define BMC_FLAG_PRESETS_BANK_CHANGED 1

#include "utility/BMC-Def.h"

class BMCPresets {
public:
  BMCPresets(BMCGlobals& t_globals):
            globals(t_globals),
            global(globals.store.global),
            presetIndex(globals.presetIndex),
            bank(globals.bank),
            preset(globals.preset)
  {
  }
  void set(uint16_t t_presetAndBank, bool forced=false){
    uint8_t t_bank = (t_presetAndBank >> BMC_PRESET_BANK_MASK) & 31;
    uint8_t t_preset = t_presetAndBank & (BMC_MAX_PRESETS_PER_BANK-1);
    set(t_bank, t_preset, forced);
  }
  void setPreset(uint8_t t_preset, bool forced = false){
    set(bank, t_preset, forced);
  }
  void setBank(uint8_t t_bank, bool forced = false){
    set(t_bank, preset, forced);
  }
  void set(uint8_t t_bank, uint8_t t_preset, bool forced = false){
    if(t_bank >= BMC_MAX_PRESET_BANKS || t_preset >= BMC_MAX_PRESETS){
      BMC_PRINTLN("!!! Invalid Preset", t_preset,"!!!");
      return;
    }
    if((bank != t_bank) || (preset != t_preset) || forced){
      flags.on(BMC_FLAG_PRESETS_CHANGED);
      bank = (t_bank & 31);
      preset = t_preset & (BMC_MAX_PRESETS_PER_BANK-1);
      presetIndex = toPresetIndex(bank, preset);
      BMC_PRINTLN("Switch Preset, Bank:", t_bank, "Preset:", t_preset, "presetIndex:", presetIndex);
      bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS>& device = global.presets[presetIndex];
      if(device.settings[0] == 0){
        return;
      }
    }
  }
  /*
  BMC_MAX_PRESETS = BMC_MIDI_ARRAY_TO_14BITS(i,data); i+=2;
  BMC_MAX_PRESET_BANKS = data[i++];
  BMC_MAX_PRESETS_PER_BANK = data[i++];
  BMC_MAX_PRESET_ITEMS = data[i++];
  */
  uint8_t scrollPreset(bool direction, bool endless, uint8_t amount=1){
    amount = amount >= BMC_MAX_PRESETS_PER_BANK ? 1 : amount;
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PRESETS_PER_BANK-1);
    uint8_t value = scroller.scroll(amount, direction, endless, preset, 0, BMC_MAX_PRESETS_PER_BANK-1);
    set(bank, value);
    return value;
  }
  uint8_t scrollBank(bool direction, bool endless, uint8_t amount=1){
    amount = amount >= BMC_MAX_PRESET_BANKS ? 1 : amount;
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PRESET_BANKS-1);
    uint8_t value = scroller.scroll(amount, direction, endless, bank, 0, BMC_MAX_PRESET_BANKS-1);
    set(value, preset);
    return value;
  }
  bmcStoreName getName(){
    return getName(preset);
  }
  bmcStoreName getName(uint16_t t_preset){
    uint16_t p = toPresetIndex(bank, t_preset);
    if(p < BMC_MAX_PRESETS && global.presets[p].name > 0){
      bmcName_t n = global.presets[p].name;
      // for some reason calling globals.getDeviceName causes a panic and reboot????
      //return globals.getDeviceName(n);
      if(n <= BMC_MAX_NAMES_LIBRARY){
        return global.names[n-1];
      }
    }
    bmcStoreName t;
    sprintf(t.name, "Preset # %02u", t_preset+1);
    return t;
  }

  bmcStoreName getBankName(){
    return getBankName(bank);
  }
  bmcStoreName getBankName(uint8_t t_bank){
    bmcStoreName t;
    sprintf(t.name, "Bank # %02u", t_bank+1);
    return t;
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
  uint8_t getCurrentPreset(){
    return get();
  }
  uint16_t getIndex(){
    return presetIndex;
  }
  uint8_t get(){
    return preset & (BMC_MAX_PRESETS_PER_BANK-1);
  }
  uint8_t getBank(){
    return bank;
  }
  uint8_t getLength(){
    return getLength(bank, preset);
  }
  uint8_t getLength(uint8_t t_bank, uint8_t t_preset){
    uint16_t n = toPresetIndex(bank, preset);
    if(n < BMC_MAX_PRESETS){
      bmcStoreDevice <1, BMC_MAX_PRESET_ITEMS>& device = global.presets[n];
      return device.settings[0];
    }
    return 0;
  }
  uint8_t getTotalBanks(){
    return BMC_MAX_PRESET_BANKS;
  }
  uint16_t toPresetIndex(uint8_t t_bank, uint8_t t_preset){
    return (t_bank << BMC_PRESET_BANK_MASK) | (t_preset & (BMC_MAX_PRESETS_PER_BANK-1));
  }
public:
  BMCGlobals& globals;
  bmcStoreGlobal& global;
private:

  BMCFlags <uint8_t> flags;
  uint16_t& presetIndex;
  uint8_t& bank;
  uint8_t& preset;
};

#endif
#endif
