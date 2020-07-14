/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This is a basic BMC example

  For all examples of the library the pins will be:

       0 => SerialA RX MIDI
       1 => SerialA TX MIDI
      13 => Led (using built in led)
      14 => Button
      15 => Pot
      16 => ENCODER Pin A (CLK)
      17 => ENCODER Pin B (DT)

  The name of each example specifies which hardware is used for the example,
  for example the sketch button-led.ino is setup for a button and an led
  So for that sketch you will need to wire a button to pin 14 and the built in
  LED will act as a BMC Page Led

  All examples will have 2 pages and a 6 character names (including EOL) for all hardware
  2 Button Events
  16 Library Events
  16 Presets with 4 Preset Events
  and everything else in 4s

  When importing an example config to the BMC Config Filer Maker it will always
  use the 3.2 as the board, however all examples are using the minimum
  configuration allowing them to be used accross all supported boards.

  All Examples will be in DEBUG mode so open the Serial monitor before uploading
  to see all messages.
*/
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();

  // when a button is pressed (if button has and event set)
  bmc.onButtonActivity(onButtonActivity);

  // when a midi message is received
  bmc.onMidiRx(onMidiRx);

  // when a MIDI clock message has been received
  // uncomment line below to see all those midi messages
  //bmc.onMidiClockTick(onMidiClockTick);

  // when 24 MIDI clock messages were received
  bmc.onMidiClockBeat(onMidiClockBeat);

  // when the Master/Slave Clock has changed
  bmc.onMidiClockBpmChange(onMidiClockBpmChange);

  // when there's midi activity
  bmc.onMidiActivity(onMidiActivity);

  // when a page has changed
  bmc.onPageChange(onPageChange);

  // when the editor has updated EEPROM
  bmc.onEditorUpdate(onEditorUpdate);

  // when the editor was connected/disconnected
  bmc.onEditorConnection(onEditorConnection);

}

void loop(){
  bmc.update();
}
void onButtonActivity(uint8_t index, uint8_t trigger,
                      bmcStoreButton button, bmcStoreButtonEvent event)
{
  BMC_PRINT("Button", index);
  BMC_PRINT("");
  BMC_PRINTLN(BMCGlobal::getButtonTriggerName(trigger));

}
// BMCMidiMessage class has tons of features, it copies data from any of the
// MIDI ports into a single struct with all MIDI data
// you can find this class under "utility/BMC-MidiMessage.h"
void onMidiRx(BMCMidiMessage midiMessage){
  BMC_PRINTLN("Received MIDI Message");
  BMC_PRINTLN("Status",midiMessage.getStatus());
  BMC_PRINTLN("Channel",midiMessage.getChannel());
  BMC_PRINTLN("Data1",midiMessage.getData1());
  BMC_PRINTLN("Data2",midiMessage.getData2());
  BMC_PRINTLN("Source",midiMessage.getSource());
}
void onMidiClockTick(){
  BMC_PRINTLN("MIDI CLOCK TICK");
}
void onMidiClockBeat(){
  BMC_PRINTLN("MIDI CLOCK BEAT");
}
void onMidiClockBpmChange(uint16_t tempo){
  BMC_PRINTLN("MIDI CLOCK TEMPO CHANGED TO", tempo);
}
void onMidiActivity(bool in, bool out){
  if(in){
    BMC_PRINTLN("INCOMING MIDI");
  } else {
    BMC_PRINTLN("OUTGOING MIDI");
  }
}
void onPageChange(uint8_t page){
  BMC_PRINTLN("Page Changed", page);
}
void onEditorUpdate(){
  BMC_PRINTLN("Editor has Updated EEPROM");
}
void onEditorConnection(bool state){
  if(state){
    BMC_PRINTLN("Editor Connected");
  } else {
    BMC_PRINTLN("Editor Disconnected");
  }
}
