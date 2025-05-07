/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Class holding mainly flags that are used across BMC
  For example when there's MIDI IN activity a MIDI IN flag is set,
  Leds will then read that flag and if an LED has a MIDI IN event it will pulse
  the led, every time BMC::update() happens the MIDI IN and OUT flags are cleared
  by this point the LEDs will have read that flag and they won't need to read it again.
  This object is decleared by the main BMC class, then passed as a reference to
  objects that may use it.

*/
#ifndef BMC_METRICS_H
#define BMC_METRICS_H
#include <Arduino.h>

class BMCMetrics {
public:
  void begin(uint32_t reportIntervalMs = 2000, uint16_t minLps = 500, uint16_t maxLoopTimeUs = 1000) {
    reportInterval = reportIntervalMs;
    minLoopsPerSecond = minLps;
    maxAllowedLoopTimeUs = maxLoopTimeUs;
    lastReportMillis = millis();
    loopTimer = 0;
    enabled = true;
  }

  uint32_t getLoopsPerSecond() {
    return loopsPerSecond;
  }

  void enableLogging(bool enable) {
    enabled = enable;
  }

  void update() {
    uint32_t loopTime = loopTimer;
    loopTimer = 0;
    loopCounter++;

    if(loopTime > maxAllowedLoopTimeUs) {
      spikeDetected = true;
      if(loopTime > worstCaseLoopTime) {
        worstCaseLoopTime = loopTime;
      }
    }

    uint32_t now = (uint32_t) millis();
    if(now - lastReportMillis >= reportInterval) {
      loopsPerSecond = (loopCounter * 1000UL) / (now - lastReportMillis);
    
      if(enabled){
        BMC_PRINT("[BMCMetrics] Loop/sec:", loopsPerSecond, "| Max Loop Time:", worstCaseLoopTime, "us ");

        if(loopsPerSecond < minLoopsPerSecond) {
          BMC_PRINT(" !!! DIP");
        }

        if(spikeDetected) {
          BMC_PRINT(" !!! SPIKE");
        }

        BMC_PRINTLN("");

        #if defined(BMC_DEBUG)
          printRamStats();
        #endif
      }
      
      loopCounter = 0;
      lastReportMillis = now;
      worstCaseLoopTime = 0;
      spikeDetected = false;
    }
  }

#if defined(BMC_DEBUG)
  void printRamStats() {
    // BMC_PRINTLN(F("[BMCMetrics] RAM Usage:"));
  
    // #if defined(BMC_FOR_ESP32)
    //   BMC_PRINT("  Free Heap:", ESP.getFreeHeap(), "bytes");
    //   BMC_PRINT("  Min Ever Free Heap:", ESP.getMinFreeHeap(), "bytes");
    //   BMC_PRINT("  Max Allocatable Block:", ESP.getMaxAllocHeap(), "bytes");
  
    // #elif defined(BMC_FOR_TEENSY)
  
    //   #if BMC_MCU_MODEL >= 32 && BMC_MCU_MODEL < 40
    //     extern "C" char *__brkval;
    //     extern "C" char __bss_end;
    //     char top;
    //     uint32_t freeRam = &top - (__brkval ? __brkval : &__bss_end);
  
    //     BMC_PRINTLN("  Free RAM (est.):", freeRam, "bytes");
  
    //   #elif BMC_MCU_MODEL >= 40 && BMC_MCU_MODEL < 50
    //     uint32_t total = 0;
    //     for (int size = 1024; size <= 16384; size *= 2) {
    //       void *ptr = malloc(size);
    //       if (ptr) {
    //         total += size;
    //         free(ptr);
    //       } else {
    //         break;
    //       }
    //     }
  
    //     BMC_PRINTLN("  Approx Free Heap:", total, "bytes");
    //   #endif
    // #endif
  }
#endif
  

  void stop() {
    enabled = false;
    reset();
  }

  void toggle() {
    enabled = !enabled;
    if(enabled) {
      lastReportMillis = (uint32_t) millis();
      loopTimer = 0;
    } else {
      reset();
    }
  }

  bool isEnabled() {
    return enabled;
  }

  void reset() {
    loopCounter = 0;
    worstCaseLoopTime = 0;
    spikeDetected = false;
    loopTimer = 0;
    lastReportMillis = (uint32_t) millis();
  }

private:

  BMCElapsedMicros loopTimer;
  uint32_t loopCounter = 0;
  uint32_t lastReportMillis = 0;
  uint32_t worstCaseLoopTime = 0;
  uint32_t loopsPerSecond = 0;
  uint16_t reportInterval = 2000;
  uint16_t minLoopsPerSecond = 500;
  uint16_t maxAllowedLoopTimeUs = 1000;
  
  bool spikeDetected = false;
  bool enabled = false;
};

#endif
