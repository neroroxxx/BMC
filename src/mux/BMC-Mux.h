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
  BMCMuxGpio muxGpio;
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
    muxGpio.begin();
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
    muxGpio.update();
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
    if(n < BMC_MAX_MUX_GPIO){
      return muxGpio.readPin(n);
    }
#endif

#if BMC_MAX_MUX_IN > 0
    return muxIn.getPinValue(n);
#endif

  return 0;
  }
  // digitalWrite equivalent
  void writeDigital(uint8_t n, bool on){
#if BMC_MAX_MUX_GPIO > 0
    if(n < BMC_MAX_MUX_GPIO){
      muxGpio.writePin(n, on);
      return;
    }
#endif

#if BMC_MAX_MUX_OUT > 0
    muxOut.setPinValue(n, on);
#endif
  }





  // when using custom MUX
  void setDigitalValue(uint8_t t_pin, bool t_value){
#if BMC_MAX_MUX_GPIO > 0
    if(t_pin < BMC_MAX_MUX_GPIO){
      muxGpio.setPinValue(t_pin, t_value);
      return;
    }
#endif

#if BMC_MAX_MUX_IN > 0
    muxIn.setPinValues(t_pin, t_value);
#endif
  }

  
  bool getDigitalValue(uint8_t t_pin){
#if BMC_MAX_MUX_GPIO > 0
    if(t_pin < BMC_MAX_MUX_GPIO){
      return muxGpio.getPinValue(t_pin);
    }
#endif

#if BMC_MAX_MUX_OUT > 0
    return muxOut.getPinValue(t_pin);
#endif
    return 0;
  }






  void testDigital(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
    if(n < BMC_MAX_MUX_GPIO){
      muxGpio.test(n);
      return;
    }
#endif

#if BMC_MAX_MUX_OUT > 0
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
