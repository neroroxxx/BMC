/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

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
#ifndef BMC_AUX_JACKS_H
#define BMC_AUX_JACKS_H
#include "utility/BMC-Def.h"
#include "devices/physical/auxJacks/BMC-AuxJack.h"

class BMCAuxJacks {
public:
  BMCAuxJacks(){}
  void begin(uint8_t n, uint8_t t_potIndex, uint8_t t_btnIndex, uint8_t t_btnEnIndex){
    if(n>=BMC_MAX_AUX_JACKS){
      return;
    }
    aux[n].begin(t_potIndex, t_btnIndex, t_btnEnIndex);
  }
  bool update(uint8_t n){
    if(n>=BMC_MAX_AUX_JACKS){
      return false;
    }
    return aux[n].update();
  }
  void setMode(uint8_t n, bool t_mode){
    if(n>=BMC_MAX_AUX_JACKS){
      return;
    }
    aux[n].setMode(t_mode);
  }
  bool readPot(uint8_t n){
    for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
      if(aux[i].getPotIndex()==n){
        return aux[i].readPot(n);
      }
    }
    return true;
  }
  bool readButton(uint8_t n){
    for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
      if(aux[i].getBtnIndex()==n || aux[i].getBtnEnIndex()==n){
        return aux[i].readButton(n);
      }
    }
    return true;
  }
  uint8_t getPotPin(uint8_t n){
    if(n>=BMC_MAX_AUX_JACKS){
      return 255;
    }
    return aux[n].getPotPin();
  }
  uint8_t getBtnEnIndex(uint8_t n){
    if(n>=BMC_MAX_AUX_JACKS){
      return 255;
    }
    return aux[n].getBtnEnIndex();
  }
  bool isConnected(uint8_t n){
    if(n>=BMC_MAX_AUX_JACKS){
      return false;
    }
    return aux[n].isConnected();
  }
  void reAssignPins(){
    for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
      aux[i].reAssignPins();
    }
  }
private:
  BMCAuxJack aux[BMC_MAX_AUX_JACKS];
};
#endif
