#pragma once
#include <Arduino.h>
#include "utility/BMC-Def.h"

#if defined(BMC_FOR_ESP32)
  #include "esp_timer.h"
  #define BMC_IRAM_ATTR IRAM_ATTR
#else
  #define BMC_IRAM_ATTR
#endif

class BMCMidiClockTimer {
public:
  BMCMidiClockTimer() {}

  void begin(){
    BMC_PRINTLN(" - BMCMidiClockTimer::begin");
    setBpm(120);

  #if defined(BMC_USE_PRECISION_MIDI_CLOCK)
    BMC_PRINTLN("Using Hardware Timer");
    setupHardwareTimer();
  #else
    lastMicros = 0;
  #endif
  }

  void start();

  void stop();
  
  void update(){
#if !defined(BMC_USE_PRECISION_MIDI_CLOCK)
    if(interval == 0) return;
    
    if(lastMicros >= interval){
      lastMicros = 0;
      flag = true;
    }
#endif
  }

  void setBpm(uint16_t bpm){
    if(bpm < 30){
      bpm = 30;
    } else if(bpm > 300){
      bpm = 300;
    }
    interval = 60000000UL / (uint32_t)(bpm * 24);

#if defined(BMC_USE_PRECISION_MIDI_CLOCK)
    updateHardwareTimer();
#else
    lastMicros = 0;
#endif
  }

  bool ready(){
    if(flag){
      flag = false;
      return true;
    }
    return false;
  }

#if defined(BMC_USE_PRECISION_MIDI_CLOCK)
  static void onTickStaticWrapper(); // optional legacy support
#endif

private:
  uint32_t interval = 0;
  volatile bool flag = false;

#if defined(BMC_USE_PRECISION_MIDI_CLOCK)

  volatile bool wasInit = false;
  volatile bool active = false;

  #if defined(BMC_FOR_ESP32)
    esp_timer_handle_t espTimer = nullptr;
    static void espTimerCallback(void* arg);
  #elif defined(BMC_FOR_TEENSY)
    IntervalTimer timer;
  #endif

  void setupHardwareTimer();
  void updateHardwareTimer();
  void BMC_IRAM_ATTR onTick();

  static BMCMidiClockTimer* instance;

#else

  BMCElapsedMicros lastMicros;

#endif
};