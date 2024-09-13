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
#include "hardware/BMC-AuxJackPot.h"
#include "hardware/BMC-AuxJackButton.h"
// 0 = buttons, 1 = pot
#define BMC_AUX_JACK_FLAG_POT_MODE 0
#define BMC_AUX_JACK_FLAG_CONNECTED 1
#define BMC_AUX_JACK_FLAG_STATE_CHANGED 2

#define BMC_AUX_JACK_BUTTON_OPEN HIGH
#define BMC_AUX_JACK_BUTTON_CLOSED LOW

class BMCAuxJack {
public:
  BMCAuxJack(){
    reset();
  }
  void begin(uint8_t t_potPin, uint8_t t_btnPin, uint8_t t_btnEnPin){
    potPin = t_potPin;
    btnPin = t_btnPin;
    btnEnPin = t_btnEnPin;

    if(potPin==255 || btnPin==255 || btnEnPin==255){
      potPin = 255;
      btnPin = 255;
      btnEnPin = 255;
      return;
    }
    button[0].begin(potPin);
    button[1].begin(btnPin);
    pot.begin(potPin);
  }
  uint16_t getAnalogValue(){
    if(isPotMode()){
      return analogRead(potPin);
    }
    return 0;
  }
  void setCalibration(uint16_t t_min, uint16_t t_max){
    pot.setCalibration(t_min, t_max);
  }
  void assignToeSwitch(bmcEvent_t a, bmcEvent_t b, uint8_t settings){
    pot.assignToeSwitch(a>0 && b>0, settings);
  }
  void reassign(){
    assignIO();
    pot.reassign();
    for(uint8_t i=0;i<2;i++){
      button[i].reassign();
    }
  }
  bool stateChanged(){
    if(flags.toggleIfTrue(BMC_AUX_JACK_FLAG_STATE_CHANGED)){
      return true;
    }
    return false;
  }
  // returns true if a device was connected or disconnected...
  bool update(){
    // timer is running which means a plug was plugged in or unplugged
    if(timer.active()){
      if(timer.complete()){
        timer.stop();
        flags.toggle(BMC_AUX_JACK_FLAG_CONNECTED);
        flags.on(BMC_AUX_JACK_FLAG_STATE_CHANGED);
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
  uint8_t read(){
    if(!isConnected()){
      return 0;
    }
    if(isPotMode()){
      // read pot
      if(pot.toeSwitchActive()){
        return pot.toeSwitchGetEvent()+1;
      }
      if(pot.update()){
        return 1; // if pot was moved
      }
    } else {
      // read buttons
      for(uint8_t i=0;i<2;i++){
        if(button[i].update()){
          return i+2;
        }
      }
    }
    return 0;
  }
  uint16_t getPotValue(){
    return pot.getValue();
  }
  void setMode(bool t_mode){
    flags.write(BMC_AUX_JACK_FLAG_POT_MODE, t_mode);
    assignIO();
  }
  bool isPotMode(){
    return flags.read(BMC_AUX_JACK_FLAG_POT_MODE);
  }
  bool isConnected(){
    return flags.read(BMC_AUX_JACK_FLAG_CONNECTED);
  }
private:
  BMCFlags <uint8_t> flags;
  uint8_t potPin = 255;
  uint8_t btnPin = 255;
  uint8_t btnEnPin = 255;
  BMCTimer timer;
  BMCAuxJackPot pot;
  BMCAuxJackButton button[2];

  void assignIO(){
    if(flags.read(BMC_AUX_JACK_FLAG_POT_MODE)){
      // set as pots
      pinMode(potPin,INPUT);
      // set button pin as output & HIGH to pass 3v to pot
      pinMode(btnPin, OUTPUT);
      digitalWrite(btnPin, HIGH);
      pinMode(btnEnPin,BMC_BUTTON_PIN_MODE);
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
