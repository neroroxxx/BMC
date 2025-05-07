/*
  See https://www.roxxxtar.com/bmc for more details
  Copyright (c) 2015 - 2025 Roxxxtar.com 
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

void BMC::readMidi(){
  // this is mainly used to update the master midi clock's timer
  handleMidiClock(false);

  if(midiClock.tempoChanged()){
    BMC_PRINTLN("tempoChanged()");
    runBpmChanged();
  }

  midiActiveSense.update();

  incomingMidi(midi.read());// Read the USB MIDI Port

  #ifdef BMC_USB_HOST_ENABLED
    incomingMidi(midi.readHost()); // Read the USB Host MIDI Port
  #endif

  #ifdef BMC_MIDI_BLE_ENABLED
    incomingMidi(midi.readBle()); // Read the BLE MIDI Port
  #endif

  #if defined(BMC_MIDI_SERIAL_A_ENABLED) && !defined(BMC_RX_DISABLE_SERIAL_A)
  incomingMidi(midi.readSerial(0));// Read the Serial MIDI Port
  #endif

  #if defined(BMC_MIDI_SERIAL_B_ENABLED) && !defined(BMC_RX_DISABLE_SERIAL_B)
    incomingMidi(midi.readSerial(1));// Read the Serial B MIDI Port
  #endif

  #if defined(BMC_MIDI_SERIAL_C_ENABLED) && !defined(BMC_RX_DISABLE_SERIAL_C)
    incomingMidi(midi.readSerial(2));// Read the Serial C MIDI Port
  #endif

  #if defined(BMC_MIDI_SERIAL_D_ENABLED) && !defined(BMC_RX_DISABLE_SERIAL_D)
    incomingMidi(midi.readSerial(3));// Read the Serial D MIDI Port
  #endif

  // #ifdef BMC_USE_BEATBUDDY
  //   sync.beatBuddy.update();
  // #endif
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

#if defined(BMC_USE_SYNC)
    sync.incoming(message);
#endif
// #ifdef BMC_USE_DAW_LC
//   sync.daw.incoming(message);
// #endif

// #ifdef BMC_USE_BEATBUDDY
//   sync.beatBuddy.incoming(message);
// #endif

// #ifdef BMC_USE_FAS
//   sync.fas.incoming(message);
// #endif

// #ifdef BMC_USE_KEMPER
//   sync.kemper.incoming(message);
// #endif

  if(midi.isIncoming()){
    if(message.isProgramChange()){
      
      switch(settings.getIncomingProgramType()){
        case BMC_NONE:
          break;
        case 1:
#if BMC_MAX_LAYERS > 127
          setLayer((bank*128) + message.getData1());
#else
          setLayer(message.getData1());
#endif
          break;
        case 2:
#if BMC_MAX_PRESETS > 127
          presets.setByIndex((uint16_t) ((bank*128) + message.getData1()));
#elif BMC_MAX_PRESETS > 0
          presets.setByIndex(message.getData1());
#endif
        case 3:
#if BMC_MAX_SETLISTS > 0
          BMC_PRINTLN("Change song", message.getData1());
          setLists.setSong(message.getData1());
#endif
          break;
      }
    } else if(message.isControlChange()){
      // if BMC is set to listen to incoming messages, MIDI CC#0 on the
      // specified channel is automatically the BANK control change
#if BMC_MAX_LAYERS > 127 || BMC_MAX_PRESETS > 127
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
#if defined(BMC_DEBUG)
  midiInDebug(message);
#endif
}

void BMC::handleMidiClock(bool isClock, bool isStartOrContinue){
  if(midiClock.read(isClock, isStartOrContinue)){
#if (BMC_TOTAL_LEDS + BMC_TOTAL_PIXELS) > 0
    handleClockLeds();
#endif
    if(callback.midiClockBeat){
      callback.midiClockBeat();
    }
  }
#if BMC_MAX_PIXELS > 0 || BMC_MAX_GLOBAL_PIXELS > 0 || BMC_MAX_PIXEL_STRIP > 0
    pixels.clockBeat(midiClock.getBpm());
#endif
}
void BMC::midiProgramBankScroll(bool up, bool wrap, uint8_t amount, uint8_t min, uint8_t max){
  amount = constrain(amount, 1, 64);

  programBank = BMCCycle<uint8_t>(0, 127)
    .withAmount(amount)
    .withDirection(up)
    .withWrap(wrap)
    .withValue(programBank)
    .withRange(min, max)
    .process();

  if(callback.programBankChanged){
    callback.programBankChanged(programBank);
  }
  BMC_PRINTLN("programBank", programBank);
}
void BMC::midiProgramBankTrigger(uint8_t channel, uint8_t ports){
  uint8_t nextProgram = programBank;
  if(nextProgram>127){
    nextProgram = 0;
  }
  if(channel==0 || channel>16 || ports==BMC_NONE){
    return;
  }
  midi.sendProgramChange(ports, channel, nextProgram);
  streamMidi(BMC_MIDI_PROGRAM_CHANGE, channel, nextProgram);
  if(callback.programBankTrigger){
    callback.programBankTrigger(nextProgram);
  }
}