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
  BMCPresets(BMCMidi& t_midi):
            midi(t_midi),
            presetIndex(midi.globals.presetIndex),
            bank(midi.globals.bank),
            preset(midi.globals.preset)
  {
  }
  void setByIndex(uint16_t t_presetAndBank, bool forced=false){
    // uint8_t t_bank = (t_presetAndBank >> BMC_PRESET_BANK_MASK) & 0x1F;
    // uint8_t t_preset = t_presetAndBank & (BMC_MAX_PRESETS_PER_BANK-1);
    uint8_t t_bank = getBankFromPresetIndex(t_presetAndBank);
    uint8_t t_preset = getPresetInBankFromPresetIndex(t_presetAndBank);
    set(t_bank, t_preset, forced);
  }
  void setPreset(uint8_t t_preset, bool forced = false){
    set(bank, t_preset, forced);
  }
  void setBank(uint8_t t_bank, bool forced = false){
    set(t_bank, preset, forced);
  }
  void set(uint8_t t_bank, uint8_t t_preset, bool forced = false){
    if(t_bank >= BMC_MAX_PRESET_BANKS || t_preset >= BMC_MAX_PRESETS_PER_BANK){
      BMC_PRINTLN("!!! Invalid Bank/Preset", t_bank, t_preset,"!!!");
      return;
    }
    if((bank != t_bank) || (preset != t_preset) || forced){
      flags.on(BMC_FLAG_PRESETS_CHANGED);
      bank = t_bank;
      preset = t_preset;
      presetIndex = toPresetIndex(bank, preset);
      BMC_PRINTLN("Switch Preset, Bank:", t_bank, "Preset:", t_preset, "presetIndex:", presetIndex);
    }
  }
  uint16_t scrollPresetList(bool t_direction, bool t_wrap, uint8_t amount=1, uint8_t t_min=0, uint8_t t_max=0){
    // if(!midi.globals.onBoardEditorActive()){
    //   if(midi.globals.settings.getDisplayListMode() && !midi.globals.displayListsActive()){
    //     midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET);
    //     return presetIndex;
    //   }
    // }
    if(midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET)){
      return presetIndex;
    }
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_PRESETS-1;
    }
    if(t_max > BMC_MAX_PRESETS-1){
      t_max = BMC_MAX_PRESETS-1;
    }
    if(t_min > BMC_MAX_PRESETS-1){
      t_min = 0;
    }
    amount = (amount >= BMC_MAX_PRESETS || amount==0) ? 1 : amount;
    BMCScroller <uint16_t> scroller(0, BMC_MAX_PRESETS-1);
    uint16_t value = scroller.scroll(amount, t_direction, t_wrap, presetIndex, t_min, t_max);
    setByIndex(value, false);
    return value;
  }
  uint8_t scrollPreset(bool t_direction, bool t_wrap, uint8_t amount=1, uint8_t t_min=0, uint8_t t_max=0){
    // if(!midi.globals.onBoardEditorActive()){
    //   if(midi.globals.settings.getDisplayListMode() && !midi.globals.displayListsActive()){
    //     midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET);
    //     return preset;
    //   }
    // }
    if(midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET)){
      return preset;
    }
    BMC_PRINTLN("*************** SCROLL PRESET ***************");
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_PRESETS_PER_BANK-1;
    }
    if(t_max > BMC_MAX_PRESETS_PER_BANK-1){
      t_max = BMC_MAX_PRESETS_PER_BANK-1;
    }
    if(t_min > BMC_MAX_PRESETS_PER_BANK-1){
      t_min = 0;
    }
    amount = (amount >= BMC_MAX_PRESETS_PER_BANK || amount==0) ? 1 : amount;
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PRESETS_PER_BANK-1);
    uint8_t value = scroller.scroll(amount, t_direction, t_wrap, preset, t_min, t_max);
    set(bank, value);
    return value;
  }
  uint8_t scrollBank(bool t_direction, bool t_wrap, uint8_t amount=1, uint8_t t_min=0, uint8_t t_max=0){
    // if(!midi.globals.onBoardEditorActive()){
    //   if(midi.globals.settings.getDisplayListMode() && !midi.globals.displayListsActive()){
    //     midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET);
    //     return bank;
    //   }
    // }
    if(midi.globals.setRenderDisplayList(BMC_DEVICE_ID_PRESET)){
      return bank;
    }
    if(t_min > t_max){
      uint8_t t_min2 = t_min;
      t_min = t_max;
      t_max = t_min2;
    } else if(t_min == t_max){
      t_min = 0;
      t_max = BMC_MAX_PRESET_BANKS-1;
    }
    if(t_max > BMC_MAX_PRESET_BANKS-1){
      t_max = BMC_MAX_PRESET_BANKS-1;
    }
    if(t_min > BMC_MAX_PRESET_BANKS-1){
      t_min = 0;
    }
    amount = (amount >= BMC_MAX_PRESET_BANKS || amount==0) ? 1 : amount;
    BMCScroller <uint8_t> scroller(0, BMC_MAX_PRESET_BANKS-1);
    uint8_t value = scroller.scroll(amount, t_direction, t_wrap, bank, t_min, t_max);
    set(value, preset);
    return value;
  }
  bmcStoreName getName(){
    return getName(preset);
  }
  bmcStoreName getName(uint16_t t_preset){
    bmcStoreName t;
    if(midi.globals.settings.getAppendPresetNumberToPresetName()){
      char bankBuff[2] = "";
      BMCTools::getBankLetter(bank, bankBuff);
      sprintf(t.name, "%s%u ", bankBuff, t_preset+midi.globals.offset);
    }
    uint16_t p = toPresetIndex(bank, t_preset);
    if(p < BMC_MAX_PRESETS && midi.globals.store.global.presets[p].name > 0){
      bmcName_t n = midi.globals.store.global.presets[p].name;
      if(n <= BMC_MAX_NAMES_LIBRARY){
        strcat(t.name, midi.globals.store.global.names[n-1].name);
        t.name[BMC_MAX_NAMES_LENGTH-1] = 0;
      }
    }
    if(BMC_STR_MATCH(t.name, "")){
      return getPresetStr(t_preset);
    }
    return t;
  }
  bmcStoreName getBankStr(){
    return getBankStr(bank);
  }
  bmcStoreName getBankStr(uint16_t t_bank){
    bmcStoreName t;
    BMCTools::getBankLetter(t_bank, t.name);
    return t;
  }
  bmcStoreName getPresetStr(){
    return getPresetStr(preset);
  }
  bmcStoreName getPresetStr(uint16_t t_preset){
    bmcStoreName t;
    if(midi.globals.settings.getDisplayBankWithPreset()){
      char bankBuff[3] = "";
      BMCTools::getBankLetter(bank, bankBuff);
      sprintf(t.name, "%s%u", bankBuff, t_preset+midi.globals.offset);
    } else {
      sprintf(t.name, "%u", t_preset+midi.globals.offset);
    }
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
    return preset;
  }
  uint8_t getBank(){
    return bank;
  }
  uint8_t getLength(){
    return getLength(bank, preset);
  }
  uint8_t getLength(uint8_t t_bank, uint8_t t_preset){
    uint16_t n = toPresetIndex(t_bank, t_preset);
    if(n < BMC_MAX_PRESETS){
      return midi.globals.store.global.presets[n].settings[0];
    }
    return 0;
  }
  uint8_t getTotalBanks(){
    return BMC_MAX_PRESET_BANKS;
  }
  uint16_t toPresetIndex(uint8_t t_bank, uint8_t t_preset){
    uint16_t p = (t_bank << BMC_PRESET_BANK_MASK) | (t_preset & (BMC_MAX_PRESETS_PER_BANK-1));
    if(p >= BMC_MAX_PRESETS){
      return 0;
    }
    return p;
  }
  uint8_t getBankFromPresetIndex(uint16_t t_presetAndBank){
    return ((t_presetAndBank >> BMC_PRESET_BANK_MASK) & 0x1F);
    
  }
  uint8_t getPresetInBankFromPresetIndex(uint16_t t_presetAndBank){
    return (t_presetAndBank & (BMC_MAX_PRESETS_PER_BANK-1));
  }

public:
  BMCMidi& midi;

private:
  BMCFlags <uint8_t> flags;
  uint16_t& presetIndex;
  uint8_t& bank;
  uint8_t& preset;
};

#endif
#endif
