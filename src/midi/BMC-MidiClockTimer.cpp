#include "midi/BMC-MidiClockTimer.h"

#if defined(BMC_USE_PRECISION_MIDI_CLOCK)
BMCMidiClockTimer* BMCMidiClockTimer::instance = nullptr;

void BMCMidiClockTimer::onTickStaticWrapper(){
  if(instance){
    instance->onTick();
  }
}

void BMCMidiClockTimer::espTimerCallback(void* arg){
  reinterpret_cast<BMCMidiClockTimer*>(arg)->onTick();
}

void BMCMidiClockTimer::setupHardwareTimer(){
  #if defined(BMC_FOR_ESP32)
    if(wasInit) return;
    wasInit = true;
    instance = this;

    BMC_PRINTLN("********** setupHardwareTimer()");

    esp_timer_create_args_t config;
    config.callback = &BMCMidiClockTimer::espTimerCallback;
    config.arg = this;
    config.dispatch_method = ESP_TIMER_TASK;
    config.name = "bmc_midi_clk";

    if(esp_timer_create(&config, &espTimer) == ESP_OK){
      BMC_PRINTLN("     * esp_timer created");
    } else {
      BMC_PRINTLN("     * Failed to create esp_timer");
    }
  #endif
}



void BMCMidiClockTimer::updateHardwareTimer(){
  if(interval > 0){
    BMC_PRINTLN("new interval:", interval);
    if(espTimer){
      esp_timer_stop(espTimer);
      esp_timer_start_periodic(espTimer, interval);
    }
  }
}

void BMCMidiClockTimer::onTick(){
  if(active){
    flag = true;
  }
}
#endif // BMC_USE_PRECISION_MIDI_CLOCK

void BMCMidiClockTimer::start(){
  if(flag) return;

#if defined(BMC_USE_PRECISION_MIDI_CLOCK)
  // for hardware timer
  if(!wasInit){
    setupHardwareTimer();
  }

  active = true;

  if(espTimer){
    esp_timer_start_periodic(espTimer, interval);
  }
#else
  // for software timer
  lastMicros = 0;
#endif

  flag = false;

  BMC_PRINTLN("BMCMidiClockTimer start() interval:", interval);
}

void BMCMidiClockTimer::stop(){
  
  flag = false;

  #if defined(BMC_USE_PRECISION_MIDI_CLOCK)
    active = false;
    if(espTimer){
      esp_timer_stop(espTimer);
    }
  #else
    lastMicros = 0;
  #endif

  BMC_PRINTLN("BMCMidiClockTimer stopped");
}