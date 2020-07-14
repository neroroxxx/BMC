/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_BEATBUDDY_H
#define BMC_BEATBUDDY_H

#include "utility/BMC-Def.h"
#include "midi/BMC-MidiClock.h"

#ifdef BMC_USE_BEATBUDDY

#define BMC_BEATBUDDY_FLAG_SYNC_ENABLED 0
#define BMC_BEATBUDDY_FLAG_SYNCED 1
#define BMC_BEATBUDDY_FLAG_PLAYING 2
#define BMC_BEATBUDDY_FLAG_TIME_SIGN_TRIGGERED 3
#define BMC_BEATBUDDY_FLAG_STOPPED 4
#define BMC_BEATBUDDY_FLAG_HALF_TIME 5
#define BMC_BEATBUDDY_FLAG_DOUBLE_TIME 6

class BMCBeatBuddy {
public:
  BMCBeatBuddy(BMCMidi& t_midi,BMCMidiClock& t_midiClock):
              midi(t_midi),
              midiClock(t_midiClock)
  {
    reset();
  }
  void enableSync(bool t_value){
    flags.write(BMC_BEATBUDDY_FLAG_SYNC_ENABLED,t_value);
    if(!isSyncEnabled()){
      reset();
    }
  }
  void update(){
    if(midiClockTimeout.complete()){
      BMC_PRINTLN("BeatBuddy MIDI Clock not received");
      // beatbuddy was disconnected
      flags.off(BMC_BEATBUDDY_FLAG_SYNCED);
      bbStopped();
    }


    if(timeSignatureTriggered() && midi.callback.beatBuddyBeatLocation){
      // since this is the first bar we need to do the calculation here.
      float x = ((float)100/(float) getTimeSignatureNumerator())*1.0;
      uint8_t y = map(x,0,100,1,32);
      BMC_PRINTLN("timeSignatureTriggered()",getTimeSignatureNumerator(),x,y);
      midi.callback.beatBuddyBeatLocation(y, getTimeSignatureNumerator());
    }
    if(hasStopped() && midi.callback.beatBuddyBeatLocation){
      midi.callback.beatBuddyBeatLocation(0, getTimeSignatureNumerator());
    }

    if(isTimeSignatureAvailable() && beatLocationChanged() && midi.callback.beatBuddyBeatLocation){
      midi.callback.beatBuddyBeatLocation(getBeatLocation(), getTimeSignatureNumerator());
    }
  }
  void reassign(){
    // reset the current expression value so when changing pages BMC won't
    // trigger the pots value immediately
    tExpression = 255;
  }
  // this method should be used with pots only, it expects a value from 0 to 127
  // the idea is to use the BB's tempo increase (CC#80) and decrease (CC#81)
  // these CC expect a value, that value is added to the current Tempo of the BB
  // if the value of the CC is one then BB changes it's tempo by +/- 1, etc.
  // for now this will increase/decrease tempo a maximum of 16 times from heel
  // to toe depending on how fast you rock the expression pedal.
  // the slower the more steps, the faster the less steps
  void tempoExpression(uint8_t value){
    value = map(value, 0, 127, 0, 16);
    if(tExpression==255){
      tExpression = value;
    }
    if(value!=tExpression){
      tempoControl(1, (value>tExpression));
      tExpression = value;
    }
  }

  bool checkExpressionBounds(uint8_t prev, uint8_t next, uint8_t tolerance){
    return (prev>=(next+tolerance) || ((prev>=tolerance) && prev<=(next-tolerance)));
  }
  bool inSync(){
    return isSyncEnabled() && flags.read(BMC_BEATBUDDY_FLAG_SYNCED);
  }
  uint8_t getTimeSignatureNumerator(){
    return timeSignature.numerator;
  }
  uint8_t getTimeSignatureDenominator(){
    return timeSignature.denominator;
  }
  bool timeSignatureTriggered(){
    return flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_TIME_SIGN_TRIGGERED);
  }
  bool isTimeSignatureAvailable(){
    return (inSync() && flags.read(BMC_BEATBUDDY_FLAG_PLAYING) && timeSignature.available());
  }
  bool beatLocationChanged(){
    uint8_t bl = timeSignature.getBeatLocation();
    if(beatLocation!= bl){
      beatLocation = bl;
      return true;
    }
    return false;
  }
  uint8_t getBeatLocation(){
    return beatLocation;
  }
  bool hasStopped(){
    return flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_STOPPED);
  }
  void incoming(BMCMidiMessage m){
    if(isSyncEnabled() && m.matchSource(port)){
      // coming from the same port as the beatBuddy
      // check if we've received the current song part
      if(m.isClock()){
        flags.on(BMC_BEATBUDDY_FLAG_SYNCED);
        midiClockTimeout.start(2000);

      } else if(m.isControlChange() && m.matchChannel(channel) && m.isData1(BMC_BEATBUDDY_CC_PART_NUMBER)){

        songPart = m.getData2();
        BMC_PRINTLN("BeatBuddy Part", songPart);

      } else if(m.isStart()){

        // beatbuddy has started
        if(timeSignature.available()){
          // we set the beat to 2 for reasons...
          timeSignature.beat = 2;
          flags.on(BMC_BEATBUDDY_FLAG_TIME_SIGN_TRIGGERED);
        }

        flags.on(BMC_BEATBUDDY_FLAG_PLAYING);
        flags.off(BMC_BEATBUDDY_FLAG_STOPPED);
        BMC_PRINTLN("BeatBuddy Started");

      } else if(m.isStop()){
        // beatbuddy has stopped
        bbStopped();

      } else if(isTimeSignatureMessage(m)){
        timeSignature.setFromMidi(m.sysex[6],m.sysex[7],m.sysex[8],m.sysex[9]);
        BMC_PRINTLN("BeatBuddy Time Signature",timeSignature.numerator,"/",timeSignature.denominator);
      }
    }
  }
  void bbStopped(){
    flags.on(BMC_BEATBUDDY_FLAG_STOPPED);
    flags.off(BMC_BEATBUDDY_FLAG_PLAYING);
    flags.off(BMC_BEATBUDDY_FLAG_HALF_TIME);
    flags.off(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
    timeSignature.beat = 0;
    beatLocation = 0;
    songPart = 0;
    //BMC_PRINTLN("BeatBuddy Stopped");
  }
  void setChannel(uint8_t value){
    channel = isSyncEnabled() ? value : BMC_NONE;
  }
  void setPort(uint8_t value){
    port = isSyncEnabled() ? value : BMC_NONE;
  }
  void setPortBit(uint8_t value){
    uint8_t x = 0;
    port = isSyncEnabled() ? bitWrite(x,value,1) : BMC_NONE;
  }
  uint8_t getSongPart(){
    return isSyncEnabled() ? songPart : 0;
  }
  bool isSongPart(uint8_t value){
    return isPlaying() && (value == songPart);
  }
  bool isPlaying(){
    return isSyncEnabled() && flags.read(BMC_BEATBUDDY_FLAG_PLAYING);
  }
  void sendCommand(uint8_t value, uint8_t data=127){
    if(!isSyncEnabled()){
      return;
    }
    if(value>=BMC_BEATBUDDY_CMD_TRANS_END && value<=BMC_BEATBUDDY_CMD_TRANS_NEXT){
      transition(value-100);
      return;
    }
    switch(value){
      case BMC_BEATBUDDY_CMD_START:
        start();
        break;
      case BMC_BEATBUDDY_CMD_STOP:
        stop();
        break;
      case BMC_BEATBUDDY_CMD_TAP:
        tap();
        break;
      case BMC_BEATBUDDY_CMD_BPM_INC:
        tempoIncrement(data);
        break;
      case BMC_BEATBUDDY_CMD_BPM_DEC:
        tempoDecrement(data);
        break;
      case BMC_BEATBUDDY_CMD_PAUSE:
        pause();
        break;
      case BMC_BEATBUDDY_CMD_UNPAUSE:
        unpause();
        break;
      case BMC_BEATBUDDY_CMD_PAUSE_TOGGLE:
        pauseToggle();
        break;
      case BMC_BEATBUDDY_CMD_DRUM_FILL:
        drumFill();
        break;
      case BMC_BEATBUDDY_CMD_OUTRO:
        outro();
        break;
      case BMC_BEATBUDDY_CMD_MIX_VOL:
        mixVol(data);
        break;
      case BMC_BEATBUDDY_CMD_HP_VOL:
        hpVol(data);
        break;
      case BMC_BEATBUDDY_CMD_ACCENT_HIT:
        accentHit(data);
        break;
      case BMC_BEATBUDDY_CMD_NORMAL_TIME:
        normalTime();
        break;
      case BMC_BEATBUDDY_CMD_HALF_TIME:
        halfTime();
        break;
      case BMC_BEATBUDDY_CMD_DOUBLE_TIME:
        doubleTime();
        break;
      case BMC_BEATBUDDY_CMD_DRUMSET_SELECT:
        drumsetSelect(data);
        break;
      case BMC_BEATBUDDY_CMD_FOLDER_ENTER:
        folderEnter(data);
        break;
      case BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN:
        songScroll(false); // false to scroll down
        break;
      case BMC_BEATBUDDY_CMD_SONG_SCROLL_UP:
        songScroll(true); // true to scroll up
        break;
      case BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE:
        halfTimeToggle();
        break;
      case BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE:
        doubleTimeToggle();
        break;
    }
  }
  void folderEnter(uint8_t value){
    sendControl(BMC_BEATBUDDY_CC_FOLDER_ENTER_EXIT, 1);
  }
  void songScroll(bool up){
    sendControl(BMC_BEATBUDDY_CC_SONG_FOLDER_SCROLL, (up?1:0));
    bbStopped();
  }
  void drumsetSelect(uint8_t value){
    if(!isSyncEnabled() || value==0){
      return;
    }
    sendControl(BMC_BEATBUDDY_CC_DRUMSET_SELECT, value);
  }
  void start(){
    sendControl(BMC_BEATBUDDY_CC_START_PLAYBACK, 127);
    if(songPart==0){
      songPart = isSyncEnabled() ? 1 : 0;
    }
  }
  void stop(){
    sendRealTime(BMC_MIDI_RT_STOP);
  }
  void songSelect(uint16_t folder, uint8_t song){
    if(folder>0x3FFF){
      return;
    }
    sendControl(0, (folder << 7) & 0x7F);
    sendControl(32, folder & 0x7F);
    sendProgram(song & 0x7F);
  }
  void tempo(uint16_t bpm=0){
    if(!isSyncEnabled() || (bpm < 40 || bpm > 300)){
      return;
    }

    uint8_t cc98 = midi.getLocalControl(channel,98);
    uint8_t cc99 = midi.getLocalControl(channel,99);
    uint8_t cc106 = midi.getLocalControl(channel,106);
    uint8_t cc107 = midi.getLocalControl(channel,107);

    sendControl(99, 106);
    sendControl(98, 107);
    sendControl(106, (bpm >> 7) & 0x7F);
    sendControl(107, bpm & 0x7F);
    sendControl(99, 127);
    sendControl(98, 127);

    midi.setLocalControl(channel,98,cc98);
    midi.setLocalControl(channel,99,cc99);
    midi.setLocalControl(channel,106,cc106);
    midi.setLocalControl(channel,107,cc107);
  }

  void tempoControl(uint8_t value, bool up){
    if(value==0){
      return;
    }
    if(up){
      sendControl(BMC_BEATBUDDY_CC_TEMPO_INC, value);
    } else {
      sendControl(BMC_BEATBUDDY_CC_TEMPO_DEC, value);
    }
  }
  void tempoIncrement(uint8_t value){
    if(value>0){
      sendControl(BMC_BEATBUDDY_CC_TEMPO_INC, value);
    }
    // old way to do it, before BB FW 2.7.0
    // we store the current value
    //uint8_t cc96 = midi.getLocalControl(channel,96);
    //uint8_t cc98 = midi.getLocalControl(channel,98);
    //uint8_t cc99 = midi.getLocalControl(channel,99);
    //sendControl(99, 106);
    //sendControl(98, 107);
    //sendControl(96, 1);
    //sendControl(99, 127);
    //sendControl(98, 127);
    //midi.setLocalControl(channel,96,cc96);
    //midi.setLocalControl(channel,98,cc98);
    //midi.setLocalControl(channel,99,cc99);
  }
  void tempoDecrement(uint8_t value){
    if(value>0){
      sendControl(BMC_BEATBUDDY_CC_TEMPO_DEC, value);
    }
    //uint8_t cc97 = midi.getLocalControl(channel,97);
    //uint8_t cc98 = midi.getLocalControl(channel,98);
    //uint8_t cc99 = midi.getLocalControl(channel,99);
    //sendControl(99, 106);
    //sendControl(98, 107);
    //sendControl(97, 1);
    //sendControl(99, 127);
    //sendControl(98, 127);
    //midi.setLocalControl(channel,97,cc97);
    //midi.setLocalControl(channel,98,cc98);
    //midi.setLocalControl(channel,99,cc99);
  }

  // has volume
  void mixVol(uint8_t volume){
    sendControl(BMC_BEATBUDDY_CC_MIX_VOL, volume);
  }
  // has volume
  void hpVol(uint8_t volume){
    sendControl(BMC_BEATBUDDY_CC_HP_VOL, volume);
  }
  // has volume
  void accentHit(uint8_t volume){
    sendControl(BMC_BEATBUDDY_CC_ACCENT_HIT, volume);
  }
  void pause(){
    sendControl(BMC_BEATBUDDY_CC_PAUSE, 0);
  }
  void unpause(){
    sendControl(BMC_BEATBUDDY_CC_PAUSE, 1);
  }
  void pauseToggle(){
    sendControl(BMC_BEATBUDDY_CC_PAUSE, 127);
  }
  void drumFill(){
    sendControl(BMC_BEATBUDDY_CC_DRUM_FILL, 127);
  }
  void transition(uint8_t value){
    sendControl(BMC_BEATBUDDY_CC_TRANSITION, value);
    if(isSyncEnabled() && songPart==0 && !flags.read(BMC_BEATBUDDY_FLAG_PLAYING)){
      songPart = value;
    }
  }
  void outro(){
    sendControl(BMC_BEATBUDDY_CC_OUTRO, 127);
  }
  void tap(){
    sendControl(BMC_BEATBUDDY_CC_TAP, 127);
  }
  bool isHalfTime(){
    return flags.read(BMC_BEATBUDDY_FLAG_HALF_TIME);
  }
  bool isDoubleTime(){
    return flags.read(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
  }
  void normalTime(){
    if(flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_HALF_TIME)){
      sendControl(BMC_BEATBUDDY_CC_HALF_TIME, 0);
    }
    if(flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_DOUBLE_TIME)){
      sendControl(BMC_BEATBUDDY_CC_DOUBLE_TIME, 0);
    }
  }
  void halfTime(){
    sendControl(BMC_BEATBUDDY_CC_HALF_TIME, 127);
    flags.on(BMC_BEATBUDDY_FLAG_HALF_TIME);
    flags.off(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
  }
  void doubleTime(){
    sendControl(BMC_BEATBUDDY_CC_DOUBLE_TIME, 127);
    flags.on(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
    flags.off(BMC_BEATBUDDY_FLAG_HALF_TIME);
  }
  void halfTimeToggle(){
    // toggle the flag
    flags.toggle(BMC_BEATBUDDY_FLAG_HALF_TIME);
    // always turn off double time flag
    flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
    // if the flag is now true then send half time on
    sendControl(BMC_BEATBUDDY_CC_HALF_TIME, flags.read(BMC_BEATBUDDY_FLAG_HALF_TIME)?127:0);
  }
  void doubleTimeToggle(){
    // toggle the flag
    flags.toggle(BMC_BEATBUDDY_FLAG_DOUBLE_TIME);
    flags.toggleIfTrue(BMC_BEATBUDDY_FLAG_HALF_TIME);
    // if the flag is now true then send double time on
    sendControl(BMC_BEATBUDDY_CC_DOUBLE_TIME, flags.read(BMC_BEATBUDDY_FLAG_DOUBLE_TIME)?127:0);
  }

private:
  BMCMidi& midi;
  BMCMidiClock& midiClock;
  BMCMidiTimeSignature timeSignature;
  BMCFlags <uint8_t> flags;
  BMCTimer midiClockTimeout;
  uint8_t channel = 0;
  uint8_t port = 0;
  uint8_t songPart = 0;
  uint8_t beatLocation = 0;
  uint8_t tExpression = 255;

  void sendControl(uint8_t t_control, uint8_t t_value){
    if(isSyncEnabled()){
      midi.sendControlChange(port, channel, t_control, t_value);
    }
  }
  void sendProgram(uint8_t t_program){
    if(isSyncEnabled()){
      midi.sendProgramChange(port, channel, t_program);
    }
  }
  void sendRealTime(uint8_t t_status){
    if(isSyncEnabled()){
      midi.sendRealTime(port, t_status);
    }
  }
  void reset(){
    bool s = isSyncEnabled();
    flags.reset();
    flags.write(BMC_BEATBUDDY_FLAG_SYNC_ENABLED, s);
    beatLocation = 0;
    songPart = 0;
    midiClockTimeout.stop();
    timeSignature.reset();
  }
  bool isSyncEnabled(){
    return flags.read(BMC_BEATBUDDY_FLAG_SYNC_ENABLED);
  }
  bool isTimeSignatureMessage(BMCMidiMessage m){
    if(m.isSysEx() && m.size()>=11){
      return (m.sysex[1]==0x7F&&m.sysex[2]==0x7F&&m.sysex[3]==0x03&&m.sysex[4]==0x02);
    }
    return false;
  }
};

#endif

#endif
