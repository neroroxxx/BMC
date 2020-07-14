/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Read Potentiometer values
  Pots must be connected to Analog Capable pins
  The output value of Pots is limited to 0 to 127 specifically for MIDI use

  Calibration data can be set for the pot, normally analogRead() will get a
  value from 0 to 1023, however some pots will never hit 1023 or 0
  for this reason you can set the calibration value, BMC can initialize
  potentiometer calibration and automatically do this with the Editor and
  it's API.

  Pots can also use a Range min/max, this will lower the resolution further
  for example a pot could be set to have a range min of 1 and a max of 3
  in this case the pots range is divided into 3 sections, as soon as each
  section is reached the pot will trigger the value for that section.
  NOTE: setting the range values uses the map() function to convert the range
  So in other words the pot will not have preset values, for example if the pot
  has the range above of 1 to 3 you may expect the pot to send a value of 1
  when the actual pot value is 0, a value of 2 when actual pot value is 64 and
  a value of 3 when the actual pot value is 127, however this is not the case,
  the value 1 would be triggered when the actual value of the pot is within
  0 and 42, value 2 is sent when the pot value is between 43 and 86 etc.

  To try and keep readings as noise-free as possible I have 2 ways to clean up
  readings, first each reading is mapped down to 0 to 127 and then we do an
  average of those readings, the numbers of readings for the average is set by
  BMC_POT_AVG_TOTAL the default value is 16, from my testing 16 is the best value
  and should not exceed 255 as the counter is only a 8-bit value.
  The average readings are not held by an array but instead by adding each value
*/
#ifndef BMC_AUX_JACK_H
#define BMC_AUX_JACK_H
#include "utility/BMC-Def.h"
// 0 = buttons, 1 = pot
#define BMC_AUX_JACK_FLAG_POT_MODE 0
#define BMC_AUX_JACK_FLAG_CONNECTED 1

#define BMC_AUX_JACK_BUTTON_OPEN HIGH
#define BMC_AUX_JACK_BUTTON_CLOSED LOW

class BMCAuxJack {
public:
  BMCAuxJack(){
    reset();
  }
  void begin(uint8_t t_potIndex, uint8_t t_btnIndex, uint8_t t_btnEnIndex){
    if(t_potIndex==255 || t_btnIndex==255 || t_btnEnIndex==255){
      return;
    }
    if(potPin!=255 || btnPin!=255 || btnEnPin!=255){
      return;
    }
    if(potIndex!=255 || btnIndex!=255 || btnEnIndex!=255){
      return;
    }
    potIndex = t_potIndex;
    btnIndex = t_btnIndex;
    btnEnIndex = t_btnEnIndex;

    potPin = BMCBuildData::getPotPin(potIndex);
    btnPin = BMCBuildData::getButtonPin(btnIndex);
    btnEnPin = BMCBuildData::getButtonPin(btnEnIndex);

    if(potPin==255 || btnPin==255 || btnEnPin==255){
      potPin = 255;
      btnPin = 255;
      btnEnPin = 255;
      potIndex = 255;
      btnIndex = 255;
      btnEnIndex = 255;
      return;
    }
  }
  // returns true if a device was connected or disconnected...
  bool update(){
    // timer is running which means a plug was plugged in or unplugged
    if(timer.active()){
      if(timer.complete()){
        flags.toggle(BMC_AUX_JACK_FLAG_CONNECTED);
        BMC_PRINTLN(">>> BMCAuxJack::update() Aux Jack",isConnected()?"Connected":"Disconnected");
        return true;
      }
      return false;
    }
    bool enable = digitalRead(btnEnPin)==BMC_AUX_JACK_BUTTON_OPEN;
    if(isConnected() != enable){
      // if we disconnected, set timer to 500ms to debounce plug coming out
      // if we have a new connection we wait 1,000ms to wait before
      // reading the buttons or pot
      timer.start(enable ? 1000 : 500);
    }
    return false;
  }
  // used mainly when pages change
  void reAssignPins(){
    assignIO();
  }
  void setMode(bool t_mode){
    flags.write(BMC_AUX_JACK_FLAG_POT_MODE, t_mode);
    assignIO();
  }
  bool isPotMode(){
    return flags.read(BMC_AUX_JACK_FLAG_POT_MODE);
  }
  bool readPot(uint8_t n){
    if(potIndex==n){
      return isPotMode() && isConnected();
    }
    return true;
  }
  bool readButton(uint8_t n){
    if(btnIndex==n || btnEnIndex==n){
      return !isPotMode() && isConnected();
    }
    return true;
  }
  uint8_t getPotIndex(){
    return potIndex;
  }
  uint8_t getBtnIndex(){
    return btnIndex;
  }
  uint8_t getBtnEnIndex(){
    return btnEnIndex;
  }
  uint8_t getPotPin(){
    return potPin;
  }
  uint8_t getBtnPin(){
    return btnPin;
  }
  uint8_t getBtnEnPin(){
    return btnEnPin;
  }
  bool isConnected(){
    return flags.read(BMC_AUX_JACK_FLAG_CONNECTED);
  }
private:
  BMCFlags <uint8_t> flags;
  uint8_t potIndex = 255;
  uint8_t btnIndex = 255;
  uint8_t btnEnIndex = 255;
  uint8_t potPin = 255;
  uint8_t btnPin = 255;
  uint8_t btnEnPin = 255;
  BMCTimer timer;

  void assignIO(){
    if(flags.read(BMC_AUX_JACK_FLAG_POT_MODE)){
      // set as pots
      // we don't change the pot's pinMode since that will always stay as input
      // set button pin as output to pass 3v to pot
      pinMode(potPin,INPUT);
      pinMode(btnPin, OUTPUT);
      pinMode(btnEnPin,BMC_BUTTON_PIN_MODE);
      digitalWrite(btnPin, HIGH);
    } else {
      // set as buttons
      pinMode(potPin,BMC_BUTTON_PIN_MODE);
      pinMode(btnPin,BMC_BUTTON_PIN_MODE);
      pinMode(btnEnPin,BMC_BUTTON_PIN_MODE);
    }
  }
  void reset(){
    flags.reset();
  }
};
#endif
