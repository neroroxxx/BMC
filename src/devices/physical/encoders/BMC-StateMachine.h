/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_ENCODER_STATE_MACHINE_H
#define BMC_ENCODER_STATE_MACHINE_H

#include "utility/BMC-Def.h"

// #define BMC_DEBUG_ENCODERS

#if defined(BMC_DEBUG) && defined(BMC_DEBUG_ENCODERS)
  #define BMC_PRINT_ENCODERS BMC_PRINT
  #define BMC_PRINTLN_ENCODERS BMC_PRINTLN
#else
  #define BMC_PRINT_ENCODERS(...)
  #define BMC_PRINTLN_ENCODERS(...)
#endif

class BMCEncoderStateMachine {
public:
  BMCEncoderStateMachine(){}

  // Set mode and fast turn threshold (in microseconds)
  void begin(uint8_t t_mode = BMC_ENCODER_DETENT_MODE, uint16_t t_threshold = 3000){
    mode = t_mode;
    fastTurnThreshold = t_threshold;
    reset();
    BMC_PRINTLN_ENCODERS("Encoder initialized: mode", mode, "threshold", fastTurnThreshold);
  }

  // Call every loop with raw encoder pin values (non-debounced)
  // Returns true if a valid movement occurred
  bool update(bool a, bool b){
    uint8_t state = ((b ? 1 : 0) << 1) | (a ? 1 : 0);
    if(state == lastState){
      return false;
    }

    BMC_PRINTLN_ENCODERS("State changed from", lastState, "to", state);

    uint8_t transition = (lastState << 2) | state;
    lastState = state;

    int8_t step = 0;
    switch(transition){
      case 0b0001:
      case 0b0111:
      case 0b1110:
      case 0b1000:
        step = 1;
        break;
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        step = -1;
        break;
      default:
        BMC_PRINTLN_ENCODERS("Invalid transition", transition);
        return false;
    }

    BMC_PRINTLN_ENCODERS("Valid step detected", step);

    uint32_t now = micros();
    fastTurn = (now - lastMoveMicros) <= fastTurnThreshold;
    lastMoveMicros = now;

    #if defined(BMC_DEBUG) && defined(BMC_DEBUG_ENCODERS)
      if(fastTurn){
        BMC_PRINTLN_ENCODERS("Fast turn detected, delta (us)", (now - lastMoveMicros));
      }
    #endif

    if(mode == BMC_ENCODER_DETENT_MODE){
      if((movement > 0 && step < 0) || (movement < 0 && step > 0)){
        BMC_PRINTLN_ENCODERS("Direction reversed mid-detent, canceling movement", movement);
        movement = 0;
      }

      movement += step;
      BMC_PRINTLN_ENCODERS("Movement accumulation", movement);

      if(movement >= 4){
        direction = fastTurn ? 5 : 1;
        BMC_PRINTLN_ENCODERS("Detent completed: direction", direction);
        movement = 0;
        return true;
      } else if(movement <= -4){
        direction = fastTurn ? -5 : -1;
        BMC_PRINTLN_ENCODERS("Detent completed: direction", direction);
        movement = 0;
        return true;
      }
    } else {
      direction = fastTurn ? (step * 5) : step;
      BMC_PRINTLN_ENCODERS("No-detent mode movement", direction);
      return true;
    }

    return false;
  }

  // Call after update() returns true to get movement value
  // Always returns -1, 0, or 1
  // If fast turn produced ±2 to ±5, extra ticks are stored in `ticks`
  int8_t read(){
    int8_t out = 0;
    if(direction > 1){
      ticks = direction;
      out = 1;
    } else if(direction < -1){
      ticks = -direction;
      out = -1;
    } else {
      ticks = (direction == 0) ? 0 : 1;
      out = direction;
    }
    BMC_PRINTLN_ENCODERS("Read: out", out, "ticks", ticks);
    direction = 0;
    return out;
  }

  uint8_t getTicks(){
    return ticks;
  }

  bool isFastTurn(){
    return fastTurn;
  }

  void reset(){
    lastState = 0;
    movement = 0;
    direction = 0;
    fastTurn = false;
    lastMoveMicros = micros();
    BMC_PRINTLN_ENCODERS("Encoder reset");
  }

  void setMode(uint8_t m){
    mode = m;
    BMC_PRINTLN_ENCODERS("Encoder mode set to", mode);
  }

  // Fast Turn Threshold (in microseconds)

  // This value defines how quickly the encoder must be rotated to trigger "fast turn" detection.
  // Lower values require faster movement between steps; higher values allow slower rotation to qualify.

  // Recommended value range: 1000–5000 µs

  // +---------------+----------------+------------------------------------------------------------+
  // | Threshold (µs)| Name           | Effect                                                     |
  // +---------------+----------------+------------------------------------------------------------+
  // | 0             | Disabled       | Disables fast turn detection entirely                      |
  // | 1000          | Ultra Fast     | Only very fast turns are detected (≤ 1ms)                  |
  // | 2000          | Normal         | Moderate speed is considered "fast"                        |
  // | 3000          | Responsive     | Very forgiving — even slow turns may be marked as fast     |
  // +---------------+----------------+------------------------------------------------------------+
  void setFastTurnThreshold(uint16_t microsVal){
    fastTurnThreshold = microsVal;
    BMC_PRINTLN_ENCODERS("Fast turn threshold set to", fastTurnThreshold, "us");
  }

private:
  uint8_t ticks = 1;
  uint8_t lastState = 0;
  int8_t movement = 0;
  int8_t direction = 0;
  uint8_t mode = BMC_ENCODER_DETENT_MODE;

  bool fastTurn = false;
  uint16_t fastTurnThreshold = 3000;
  uint32_t lastMoveMicros = 0;
};

#endif