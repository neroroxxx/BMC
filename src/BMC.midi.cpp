/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

void BMC::readMidi(){
  // this is mainly used to update the midi clocks timer
  handleMidiClock(false);

  midiActiveSense.update();

  incomingMidi(midi.read());// Read the USB MIDI Port

  #ifdef BMC_USB_HOST_ENABLED
    incomingMidi(midi.readHost());// Read the USB Host MIDI Port
  #endif

  #ifdef BMC_MIDI_BLE_ENABLED
    incomingMidi(midi.readBle());// Read the BLE MIDI Port
  #endif

  #ifdef BMC_MIDI_SERIAL_A_ENABLED
    incomingMidi(midi.readSerial(0));// Read the Serial MIDI Port
    #ifdef BMC_MIDI_SERIAL_B_ENABLED
      incomingMidi(midi.readSerial(1));// Read the Serial B MIDI Port
    #endif
    #ifdef BMC_MIDI_SERIAL_C_ENABLED
      incomingMidi(midi.readSerial(2));// Read the Serial C MIDI Port
    #endif
    #ifdef BMC_MIDI_SERIAL_D_ENABLED
      incomingMidi(midi.readSerial(3));// Read the Serial D MIDI Port
    #endif
  #endif
#ifdef BMC_USE_BEATBUDDY
  beatBuddy.update();
#endif
}
void BMC::incomingMidi(BMCMidiMessage message){
  if(message.getStatus()==BMC_NONE){
    return;
  }

  if(!message.isSystemRealTimeStatus()){
    globals.setMidiInActivity();
  }

  handleMidiClock(message.isClock(), message.isStartOrContinue());

  midiActiveSense.received(message.getStatus());

  // if it's an incoming message for the editor
  // the message is reset
  editorRead();

  if(message.getStatus()==BMC_NONE){
    return;
  }

  #if BMC_MAX_TRIGGERS > 0
    readTrigger();
  #endif

  #if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
    checkRelaysMidiInput(message);
  #endif

#ifdef BMC_USE_BEATBUDDY
  beatBuddy.incoming(message);
#endif

#ifdef BMC_USE_FAS
  fas.incoming(message);
#endif

#ifdef BMC_USE_KEMPER
  kemper.incoming(message);
#endif

  if(midi.isIncoming()){
    if(message.isProgramChange()){
      switch(settings.getIncomingProgramType()){
        case BMC_NONE:
          break;
        case 1:
          #if BMC_MAX_PAGE > 127
            setPage((bank*128) + message.getData1());
          #else
            setPage(message.getData1());
          #endif
          break;
        case 2:
          #if BMC_MAX_PRESETS > 127
            presets.send((bank*128) + message.getData1());
          #elif BMC_MAX_PRESETS > 0
            presets.send(message.getData1());
          #endif
          break;
      }
    } else if(message.isControlChange()){
      // if BMC is set to listen to incoming messages, MIDI CC#0 on the
      // specified channel is automatically the BANK control change
      #if BMC_MAX_PAGE > 127 || BMC_MAX_PRESETS > 127
      if(message.getData1() == 0){
        bank = message.getData2() > 0 ? 1 : 0;
        BMC_PRINTLN("MIDI Bank Changed", bank);
      }
      #endif
    }
  }

  if(message.isClock()){
    if(callback.midiClockTickReceived){
      callback.midiClockTickReceived();
    } else if(callback.midiReceived){
      callback.midiReceived(message);
    }
  } else if(message.isValid()){
    if(callback.midiReceived){
      callback.midiReceived(message);
    }
  }
  // only used when debugging
  #ifdef BMC_DEBUG
    midiInDebug(message);
  #endif
}

void BMC::handleMidiClock(bool isClock, bool isStartOrContinue){
  if(midiClock.read(isClock, isStartOrContinue)){

    #if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 0
      handleClockLeds();
    #endif

    if(callback.midiClockBeat){
      callback.midiClockBeat();
    }
    if(midiClock.tempoChanged()){
      #if BMC_MAX_TEMPO_TO_TAP > 0
        tempoToTap.send(midiClock.getBpm());
      #endif
      if(callback.midiClockBpmChange){
        callback.midiClockBpmChange(midiClock.getBpm());
      }
      streamMidiClockBPM(midiClock.getBpm());
    }
  }
}
void BMC::midiProgramBankScroll(bool up, bool endless, uint8_t amount, uint8_t min, uint8_t max){
  amount = constrain(amount, 1, 64);
  BMCScroller <uint8_t> scroller(0, 127);
  programBank = scroller.scroll(amount, up, endless, programBank, min, max);
  if(callback.programBankChanged){
    callback.programBankChanged(programBank);
  }
  BMC_PRINTLN("programBank", programBank);
}
void BMC::midiProgramBankTrigger(uint8_t amount, uint8_t channel, uint8_t ports){
  uint8_t nextProgram = programBank+amount;
  if(nextProgram>127 || channel==0 || channel>16 || ports==BMC_NONE){
    return;
  }
  midi.sendProgramChange(ports, channel, nextProgram);
  streamMidi(BMC_MIDI_PROGRAM_CHANGE, channel, nextProgram);
  if(callback.programBankTrigger){
    callback.programBankTrigger(nextProgram);
  }
}
