/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_MUX_IN_ANALOG_74HC40XX_H
#define BMC_MUX_IN_ANALOG_74HC40XX_H

#include "utility/BMC-Def.h"

#if BMC_MAX_MUX_IN_ANALOG > 0 && (BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067 || BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051)

#ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_1
  #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_1 was NOT defined"
#elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_1 >= 64
  #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_1 is not a valid pin"
#endif


#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067
  #if BMC_MAX_MUX_IN_ANALOG > 16
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_2
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 32
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_3
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 48
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_4
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 64
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_5
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 80
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_6
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 is not a valid pin"
    #endif
  #endif

#elif BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051


  #if BMC_MAX_MUX_IN_ANALOG > 8
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_2
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_2 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 16
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_3
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_3 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 24
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_4
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_4 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 32
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_5
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_5 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 40
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_6
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_6 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 48
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_7
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_7 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_7 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_7 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 56
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_8
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_8 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_8 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_8 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 64
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_9
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_9 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_9 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_9 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 72
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_10
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_10 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_10 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_10 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 80
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_11
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_11 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_11 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_11 is not a valid pin"
    #endif
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 88
    #ifndef BMC_MUX_IN_ANALOG_74HC40XX_SIG_12
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_12 was NOT defined"
    #elif BMC_MUX_IN_ANALOG_74HC40XX_SIG_12 >= 64
      #error "BMC_MUX_IN_ANALOG_74HC40XX_SIG_12 is not a valid pin"
    #endif
  #endif

#endif


#ifndef BMC_MUX_IN_ANALOG_74HC40XX_BIT0
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT0 was NOT defined"
#elif BMC_MUX_IN_ANALOG_74HC40XX_BIT0 >= 64
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT0 is not a valid pin"
#endif

#ifndef BMC_MUX_IN_ANALOG_74HC40XX_BIT1
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT1 was NOT defined"
#elif BMC_MUX_IN_ANALOG_74HC40XX_BIT1 >= 64
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT1 is not a valid pin"
#endif

#ifndef BMC_MUX_IN_ANALOG_74HC40XX_BIT2
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT2 was NOT defined"
#elif BMC_MUX_IN_ANALOG_74HC40XX_BIT2 >= 64
  #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT2 is not a valid pin"
#endif




#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067
  #ifndef BMC_MUX_IN_ANALOG_74HC40XX_BIT3
    #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT3 was NOT defined"
  #elif BMC_MUX_IN_ANALOG_74HC40XX_BIT3 >= 64
    #error "BMC_MUX_IN_ANALOG_74HC40XX_BIT3 is not a valid pin"
  #endif

  #if BMC_MAX_MUX_IN_ANALOG == 1
    #define BMC_MUX_IN_ANALOG_74HC40XX_COUNT 1
  #else
    #define BMC_MUX_IN_ANALOG_74HC40XX_COUNT (((BMC_MAX_MUX_IN_ANALOG-1)>>4)+1)
  #endif


  #if BMC_MAX_MUX_IN_ANALOG > 16
    #define BMC_MAX_MUX_IN_ANALOG_LAST 16
  #else
    #define BMC_MAX_MUX_IN_ANALOG_LAST BMC_MAX_MUX_IN_ANALOG
  #endif


  #define BMC_MUX_IN_ANALOG_74HC40XX_CHANNELS 4
  #define BMC_MUX_IN_ANALOG_74HC40XX_PINS 16


#elif BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051

  #if BMC_MAX_MUX_IN_ANALOG == 1
    #define BMC_MUX_IN_ANALOG_74HC40XX_COUNT 1
  #else
    #define BMC_MUX_IN_ANALOG_74HC40XX_COUNT (((BMC_MAX_MUX_IN_ANALOG-1)>>3)+1)
  #endif

  #if BMC_MAX_MUX_IN_ANALOG > 8
    #define BMC_MAX_MUX_IN_ANALOG_LAST 8
  #else
    #define BMC_MAX_MUX_IN_ANALOG_LAST BMC_MAX_MUX_IN_ANALOG
  #endif

  #define BMC_MUX_IN_ANALOG_74HC40XX_CHANNELS 3
  #define BMC_MUX_IN_ANALOG_74HC40XX_PINS 8

#endif




#ifndef BMC_MUX_IN_ANALOG_74HC40XX_DELAY
  #define BMC_MUX_IN_ANALOG_74HC40XX_DELAY 1
#endif


class BMCMuxInAnalog74HC40XX {
private:
  const uint8_t totalMux = BMC_MUX_IN_ANALOG_74HC40XX_COUNT;

  uint16_t values[BMC_MAX_MUX_IN_ANALOG];
  uint8_t currentChannel = 0;
  BMCTimer timer;
  const uint8_t signalPin[BMC_MUX_IN_ANALOG_74HC40XX_COUNT] = {
    BMC_MUX_IN_ANALOG_74HC40XX_SIG_1
#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067

  #if BMC_MAX_MUX_IN_ANALOG > 16
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_2
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 32
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_3
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 48
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_4
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 64
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_5
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 80
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_6
  #endif

#elif BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4051

  #if BMC_MAX_MUX_IN_ANALOG > 8
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_2
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 16
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_3
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 24
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_4
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 32
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_5
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 40
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_6
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 48
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_7
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 56
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_8
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 64
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_9
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 72
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_10
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 80
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_11
  #endif
  #if BMC_MAX_MUX_IN_ANALOG > 88
    ,BMC_MUX_IN_ANALOG_74HC40XX_SIG_12
  #endif
#endif
  };
  const uint8_t channels[BMC_MUX_IN_ANALOG_74HC40XX_CHANNELS] = {
      BMC_MUX_IN_ANALOG_74HC40XX_BIT0,
      BMC_MUX_IN_ANALOG_74HC40XX_BIT1,
      BMC_MUX_IN_ANALOG_74HC40XX_BIT2
#if BMC_MUX_IN_ANALOG_CHIPSET == BMC_MUX_IN_ANALOG_CHIPSET_74HC4067
      ,BMC_MUX_IN_ANALOG_74HC40XX_BIT3
#endif
  };
  // reads all muxes in parallel, one pin at a time
  void readMux(){
    for(uint8_t i = 0 ; i < totalMux ; i++){
      uint8_t index = (i*BMC_MUX_IN_ANALOG_74HC40XX_PINS)+currentChannel;
      if(index < BMC_MAX_MUX_IN_ANALOG){
        values[index] = analogRead(signalPin[i]);
      }
    }
    currentChannel++;
    if(currentChannel >= BMC_MAX_MUX_IN_ANALOG_LAST){
      currentChannel = 0;
    }
#if BMC_MAX_MUX_IN_ANALOG > 1
    for(uint8_t i=0 ; i < BMC_MUX_IN_ANALOG_74HC40XX_CHANNELS ; i++){
      digitalWrite(channels[i], bitRead(currentChannel, i));
    }
#endif

  }
public:
  BMCMuxInAnalog74HC40XX(){}
  void begin(){
    BMC_PRINTLN("BMCMuxInAnalog74HC40XX::begin()");
    BMC_PRINTLN("BMCMuxInAnalog74HC40XX::totalMux", totalMux);
    #if BMC_MUX_IN_ANALOG_CHIPSET==BMC_MUX_IN_ANALOG_CHIPSET_74HC4067
      BMC_PRINTLN("    BMC_MUX_IN_ANALOG_CHIPSET: 74HC4067");
    #elif BMC_MUX_IN_ANALOG_CHIPSET==BMC_MUX_IN_ANALOG_CHIPSET_74HC4051
      BMC_PRINTLN("    BMC_MUX_IN_ANALOG_CHIPSET: 74HC4051");
    #endif

    BMC_PRINTLN("    BMC_MAX_MUX_IN_ANALOG", BMC_MAX_MUX_IN_ANALOG);

    memset(values, 0, sizeof(values[0])*BMC_MAX_MUX_IN_ANALOG);

    for(uint8_t i = 0, n = totalMux ; i < n ; i++){
      // set the signal pins that will read an analog signal from the mux
      if(!BMCBuildData::isAnalogPin(signalPin[i])){
        BMC_ERROR(
          "PIN:", signalPin[i],
          "Can NOT be used with Analog Mux as it is NOT Analog Capable"
        );
        BMC_HALT();
      }
      pinMode(signalPin[i], INPUT_PULLUP);
    }
    // set the channel pins for each mux
    for(uint8_t i = 0 ; i < BMC_MUX_IN_ANALOG_74HC40XX_CHANNELS ; i++){
      if(!BMCBuildData::isDigitalPin(channels[i])){
        BMC_ERROR(
          "74HC4067 Pin:", channels[i],
          "Can NOT be used with Analog Mux as it is NOT Digital capable"
        );
        BMC_HALT();
      }
      pinMode(channels[i], OUTPUT);
      // set the channel of each mux to 0
      digitalWrite(channels[i], LOW);
    }
    timer.start(BMC_MUX_IN_ANALOG_74HC40XX_DELAY);
  }
  void update(){
    if(timer.complete()){
      readMux();
      timer.start(BMC_MUX_IN_ANALOG_74HC40XX_DELAY);
    }
  }
  uint16_t readPin(uint8_t n){
    if(n < BMC_MAX_MUX_IN_ANALOG){
      return values[n];
    }
    return 0;
  }
  uint16_t read(uint8_t n){
    return readPin(n);
  }
};

#endif
#endif
