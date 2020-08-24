/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MUX_H
#define BMC_MUX_H

#include "utility/BMC-Def.h"

#if defined(BMC_MUX_AVAILABLE)

#if BMC_MAX_MUX_GPIO > 0
  #include "mux/BMC-MuxGPIO.h"
#endif

#if BMC_MAX_MUX_IN > 0
  #include "mux/BMC-MuxIn.h"
#endif

#if BMC_MAX_MUX_OUT > 0
  #include "mux/BMC-MuxOut.h"
#endif

#if BMC_MAX_MUX_IN_ANALOG > 0
  #include "mux/BMC-MuxInAnalog.h"
#endif

class BMCMux {
private:
#if BMC_MAX_MUX_GPIO > 0
  BMCMuxGPIO muxGPIO;
#endif
#if BMC_MAX_MUX_IN > 0
  BMCMuxIn muxIn;
#endif
#if BMC_MAX_MUX_OUT > 0
  BMCMuxOut muxOut;
#endif
#if BMC_MAX_MUX_IN_ANALOG > 0
  BMCMuxInAnalog muxInAnalog;
#endif
public:
  BMCMux(){

  }
  void begin(){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.begin();
#endif
#if BMC_MAX_MUX_IN > 0
    muxIn.begin();
#endif
#if BMC_MAX_MUX_OUT > 0
    muxOut.begin();
#endif
#if BMC_MAX_MUX_IN_ANALOG > 0
    muxInAnalog.begin();
#endif
  }
  // update the muxes
  void update(){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.update();
#endif
#if BMC_MAX_MUX_IN > 0
    muxIn.update();
#endif
#if BMC_MAX_MUX_OUT > 0
    muxOut.update();
#endif
#if BMC_MAX_MUX_IN_ANALOG > 0
    muxInAnalog.update();
#endif
  }

  // digitalRead equivalent
  bool readDigital(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.readPin(n);
#elif BMC_MAX_MUX_IN > 0
    return muxIn.getPinValue(n);
#else
    return 0;
#endif
  }
  // digitalWrite equivalent
  void writeDigital(uint8_t n, bool on){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.writePin(n, on);
#elif BMC_MAX_MUX_OUT > 0
    muxOut.setPinValue(n, on);
#endif
  }

  // when using custom MUX
  void setDigitalValue(uint8_t t_pin, bool t_value){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.setPinValue(t_pin, t_value);
#elif BMC_MAX_MUX_IN > 0
    muxIn.setPinValues(t_pin, t_value);
#endif
  }
  bool getDigitalValue(uint8_t t_pin){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.getPinValue(t_pin);
#elif BMC_MAX_MUX_OUT > 0
    return muxOut.getPinValue(t_pin);
#else
    return 0;
#endif
  }

  void testDigital(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
    muxGPIO.test(n);
#elif BMC_MAX_MUX_OUT > 0
    muxOut.test(n);
#endif
  }

  // read an analog mux input pin
  uint16_t readAnalog(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
    return muxInAnalog.getPinValue(n);
#else
    return 0;
#endif
  }
  // read an analog mux input pin
  void setAnalogValue(uint8_t n, uint16_t t_value){
#if BMC_MAX_MUX_IN_ANALOG > 0
    muxInAnalog.setPinValue(n, t_value);
#endif
  }
};
#endif
#endif
