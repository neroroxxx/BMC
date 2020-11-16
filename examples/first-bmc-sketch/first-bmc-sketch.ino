/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  READ THE README FILE FIRST AND MAKE SURE YOU DID THE boards.txt MOD!!

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
  to see all messages

  This example is the simplest of all to test the editor app, doesn't use any
  external hardware just the built-in LED on pin 13, this LED is set as a Page LED
*/
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
}

void loop(){
  bmc.update();
}
