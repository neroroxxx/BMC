/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SETTINGS_H
#define BMC_SETTINGS_H

#include "utility/BMC-Def.h"

/*
  Settings store data that BMC will need to run or to make certain features
  available thru the desktop editor
  These include a 32-bit unsigned integered called "flags" which will store
  single on/off values each assigned a bit in the integer and an array out
  of eight 32-bit unsigned integers called data
  This one can also use single bits to read data but may also group bits into
  larger data types to be used by BMC

  struct bmcStoreGlobalSettings {
    uint32_t flags = 0;
      bit 0 getFirstEditorConnection
      bit 1 getMasterClock
      bit 2 getDisplayBannerTimeout
      bit 3 getIncomingListenerEnabled
      bit 4 Beatbuddy Sync Enabled
      bit 5 getActiveSenseAtStartup - Active Sensing Master Enabled
      bit 6 getMidiRealTimeBlockInput
      bit 7 getMidiRealTimeBlockOutput
      bit 8 getDisplayOffset
      bit 9 getAppendPresetNumberToPresetName
      bit 10 getDisplayBankWithPreset
      bit 11 getDisplayNames



    uint32_t data[8];
      [0]:
        bits 00-01  *2 bits Available*
        bits 02-06  getListenerChannel, 0=omni, 1-16=listen to specific channel
        bits 07-13  getListenerPorts
        bits 14-17  deviceId
        bits 18-18  getPwmDimWhenOff
        bits 19-19  getTouchScreenIsCalibrated
        bits 20-21  current Store
        bits 22-24  Slave Clock Input (only 1 port) (NOT YET IMPLEMENTED)
        bits 25-27  getChainingPort
        bits 28-31  getAuxJackMode

      [1]:
        bits 00-01  getIncomingProgramType
        bits 02-05  Helix Id
        bits 06-09  Helix Channel
        bits 10-13  Helix Port
        bits 14-15  *2 bits Available*
        bits 16-19  BeatBuddy Channel
        bits 20-23  BeatBuddy Port
        bits 24-24  Click Track Mute State (0-1)
        bits 25-27  Click Track Freq (0-7, where 0=500, 7=4000)
        bits 28-31  Click Track Level

      [2]:
        bits 00-03  Buttons Threshold
        bits 04-04  Trigger first song
        bits 05-05  Trigger first song part
        bits 06-09  Typer Channel

      [3]: *Reserved for future updates*
      [4]: *Reserved for future updates*
      [5]: *Reserved for future updates*
      [6]: *Reserved for future updates*
      [7]: *Reserved for future updates*

    uint16_t startup; startup preset data

    uint16_t routing[7]; routing data for each port
    offsets
    0 BMC_USB
    1 BMC_SERIAL_A
    2 BMC_SERIAL_B
    3 BMC_SERIAL_C
    4 BMC_SERIAL_D
    5 BMC_HOST
    6 BMC_BLE
  };
*/

class BMCSettings {
private:
  bmcStoreGlobalSettings &settings;
  bool readFlag(uint8_t bit){
    return bitRead(settings.flags, bit);
  }
  void writeFlag(uint8_t bit, bool value){
    bitWrite(settings.flags,bit,value);
  }
public:
  BMCSettings(bmcStoreGlobalSettings &t_settings):settings(t_settings){}
  // Send the startup MIDI preset at startup
  uint16_t getStartupPreset(){
    #if BMC_MAX_PRESETS == 0
      return 0;
    #else
      return settings.startup;
    #endif
  }
  void setStartupPreset(uint16_t value=0){
    if(value < BMC_MAX_PRESETS){
      settings.startup = value;
    }
  }
  // SETTINGS FLAGS
  // Sets BMC as a master midi clock
  bool getFirstEditorConnection(){
    return readFlag(0);
  }
  void setFirstEditorConnection(bool value){
    writeFlag(0,value);
  }
  // Sets BMC as a master midi clock
  bool getMasterClock(){
    return readFlag(1);
  }
  void setMasterClock(bool value){
    writeFlag(1,value);
  }
  // Enable incoming MIDI messages to activate certain events
  bool getIncomingListenerEnabled(){
    return readFlag(3);
  }
  void setIncomingListenerEnabled(bool value){
    writeFlag(3,value);
  }
  // Enable BeatBuddy Syncing
  bool getBeatBuddySync(){
    return readFlag(4);
  }
  void setBeatBuddySync(bool value){
    writeFlag(4,value);
  }
  // Enable Active Sensing Master
  bool getActiveSenseAtStartup(){
    return readFlag(5);
  }
  void setActiveSenseAtStartup(bool value){
    writeFlag(5,value);
  }
  // Ignores incoming real time messages
  bool getMidiRealTimeBlockInput(){
    return readFlag(6);
  }
  void setMidiRealTimeBlockInput(bool value){
    writeFlag(6,value);
  }
  // Mutes output of real time Messages
  bool getMidiRealTimeBlockOutput(){
    return readFlag(7);
  }
  void setMidiRealTimeBlockOutput(bool value){
    writeFlag(7,value);
  }
  // typer offset to 0
  uint8_t getDisplayOffset(){
    return readFlag(8);
  }
  void setDisplayOffset(bool value){
    writeFlag(8, value);
  }
  // This option will append the preset number to the preset name on displays.
  bool getAppendPresetNumberToPresetName(){
    return readFlag(9);
  }
  void setAppendPresetNumberToPresetName(bool value){
    writeFlag(9, value);
  }
  // This option will display the bank letter with the preset number
  bool getDisplayBankWithPreset(){
    return readFlag(10);
  }
  void setDisplayBankWithPreset(bool value){
    writeFlag(10, value);
  }
  // typer offset to 0
  uint8_t getDisplayNames(){
    return readFlag(11);
  }
  void setDisplayNames(bool value){
    writeFlag(11, value);
  }

  // data array

  uint8_t getDisplayBannerTimeout(){
    return settings.data[0] & 0x03;
  }
  void setDisplayBannerTimeout(uint8_t value){
    BMC_WRITE_BITS(settings.data[0], value, 0x03, 0);
  }

  uint8_t getListenerChannel(){
    return (settings.data[0]>>2) & 0x1F;
  }
  void setListenerChannel(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x1F,2);
  }

  uint8_t getListenerPorts(){
    return (settings.data[0]>>7) & 0x7F;
  }
  void setListenerPorts(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x7F,7);
  }

  // device id
  uint8_t getDeviceId(){
    return (settings.data[0]>>14) & 0x0F;
  }
  void setDeviceId(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x0F,14);
  }
  // pwm off value
  uint8_t getPwmDimWhenOff(){
    return (settings.data[0]>>18) & 0x01;
  }
  void setPwmDimWhenOff(uint8_t value){
    bitWrite(settings.data[0],18,value);
  }
  // touch screen is calibrated
  uint8_t getTouchScreenIsCalibrated(){
    return (settings.data[0]>>19) & 0x01;
  }
  void setTouchScreenIsCalibrated(uint8_t value){
    bitWrite(settings.data[0],19,value);
  }
  // store address
  uint8_t getStoreAddress(){
    return (settings.data[0]>>20) & 0x03;
  }
  void setStoreAddress(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x03,20);
  }
  // Slave Clock Input Port (3-bits)
  uint8_t getClockInputPortBit(){
    return (settings.data[0]>>22) & 0x07;
  }
  void setClockInputPortBit(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x07,22);
  }
  // chain port (3-bits)
  uint8_t getChainingPort(){
    return (settings.data[0]>>25) & 0x07;
  }
  void setChainingPort(uint8_t value){
    BMC_WRITE_BITS(settings.data[0],value,0x07,25);
  }
  // get aux jacks mode
  // this function returns each bit
  bool getAuxJackMode(uint8_t n){
    uint8_t modes = (settings.data[0]>>28) & 0x0F;
    if(n<4){
      return bitRead(modes, n);
    }
    return 0;
  }
  void setAuxJackMode(uint8_t n, bool value){
    uint8_t modes = (settings.data[0]>>28) & 0x0F;
    if(n<4){
      bitWrite(modes, n, value);
    }
    modes &= 0x0F;
    BMC_WRITE_BITS(settings.data[0], modes, 0x0F, 28);
  }

  //data[1] used

  // Incoming midi programs
  // @value: 0 do nothing
  //         1 change layers
  //         2 trigger presets
  uint8_t getIncomingProgramType(){
    return settings.data[1] & 0x03;
  }
  void setIncomingProgramType(bool value){
    BMC_WRITE_BITS(settings.data[1],value,0x03,0);
  }
  // Helix Id
  // @value: 0 to 15
  uint8_t getHelixId(){
    return (settings.data[1]>>2) & 0x0F;
  }
  void setHelixId(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,2);
  }
  // Helix Channel
  // @value: 0 to 15
  uint8_t getHelixChannel(){
    return (settings.data[1]>>6) & 0x0F;
  }
  void setHelixChannel(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,6);
  }
  //Helix Port
  //@value: represents the bit of the port
  uint8_t getHelixPort(){
    return (settings.data[1]>>10) & 0x0F;
  }
  void setHelixPort(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,10);
  }
  // BeatBuddy Channel
  // @value: 0 to 15
  uint8_t getBeatBuddyChannel(){
    return (settings.data[1]>>16) & 0x0F;
  }
  void setBeatBuddyChannel(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,16);
  }
  //BeatBuddy Port
  //@value: represents the bit of the port
  uint8_t getBeatBuddyPort(){
    return (settings.data[1]>>20) & 0x0F;
  }
  void setBeatBuddyPort(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,20);
  }

  // Click Track, Initial Mute State
  // @value: 0 to 1, where 1=muted, 0=unmuted
  bool getClickTrackMuteState(){
    return (settings.data[1]>>24) & 0x01;
  }
  void setClickTrackMuteState(uint8_t value){
    bitWrite(settings.data[1],24,value);
  }

  // Click Track, Initial Frequency
  // @value: 0 to 7, where 0 = 500Hz, 1 = 1000Hz, 2= 1500Hz, up to 4000Hz
  uint8_t getClickTrackFrequency(){
    return (settings.data[1]>>25) & 0x07;
  }
  void setClickTrackFrequency(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x07,25);
  }

  // Click Track, Initial Level
  // @value: from 0 to 10
  uint8_t getClickTrackLevel(){
    return (settings.data[1]>>28) & 0x0F;
  }
  void setClickTrackLevel(uint8_t value){
    BMC_WRITE_BITS(settings.data[1],value,0x0F,28);
  }



  // *ROUTING*
  void setUsbRouting(uint16_t value){
    settings.routing[0] = value;
  }
  uint16_t getUsbRouting(){
    return settings.routing[0];
  }
  void setSerialARouting(uint16_t value){
    settings.routing[1] = value;
  }
  uint16_t getSerialARouting(){
    return settings.routing[1];
  }
  void setSerialBRouting(uint16_t value){
    settings.routing[2] = value;
  }
  uint16_t getSerialBRouting(){
    return settings.routing[2];
  }
  void setSerialCRouting(uint16_t value){
    settings.routing[3] = value;
  }
  uint16_t getSerialCRouting(){
    return settings.routing[3];
  }
  void setSerialDRouting(uint16_t value){
    settings.routing[4] = value;
  }
  uint16_t getSerialDRouting(){
    return settings.routing[4];
  }
  void setHostRouting(uint16_t value){
    settings.routing[5] = value;
  }
  uint16_t getHostRouting(){
    return settings.routing[5];
  }
  void setBleRouting(uint16_t value){
    settings.routing[6] = value;
  }
  uint16_t getBleRouting(){
    return settings.routing[6];
  }
  // button hold threshold
  uint8_t getButtonHoldThreshold(){
    return settings.data[2] & 0x0F;
  }
  void setButtonHoldThreshold(uint8_t value){
    BMC_WRITE_BITS(settings.data[2],value, 0x0F, 0); //0-3
  }
  // set lists
  uint8_t getSetListTriggerFirstSong(){
    return bitRead(settings.data[2], 4);
  }
  void setSetListTriggerFirstSong(uint8_t value){
    bitWrite(settings.data[2], value, 4);
  }
  uint8_t getSetListTriggerFirstSongPart(){
    return bitRead(settings.data[2], 5);
  }
  void setSetListTriggerFirstSongPart(uint8_t value){
    bitWrite(settings.data[2], value, 5);
  }
  uint8_t getTyperChannel(){
    return (settings.data[2]>>6) & 0x0F;
  }
  void setTyperChannel(uint8_t value){
    BMC_WRITE_BITS(settings.data[2],value, 0x0F, 6); //0-3
  }
  // tft touch calibration
  float getTouchTftCalibration(uint8_t n){
#ifdef BMC_HAS_TOUCH_SCREEN
    switch(n){
      case 0: return settings.touchCalibration.xM;
      case 1: return settings.touchCalibration.xC;
      case 2: return settings.touchCalibration.yM;
      case 3: return settings.touchCalibration.yC;
    }
#endif
    return 0.0;
  }
  void setTouchTftCalibration(uint8_t n, float value){
#ifdef BMC_HAS_TOUCH_SCREEN
    switch(n){
      case 0: settings.touchCalibration.xM = value; break;
      case 1: settings.touchCalibration.xC = value; break;
      case 2: settings.touchCalibration.yM = value; break;
      case 3: settings.touchCalibration.yC = value; break;
    }
#endif
  }
};

#endif
