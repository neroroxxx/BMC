#ifndef BMC_POT_STATE_MACHINE_H
#define BMC_POT_STATE_MACHINE_H

#include "utility/BMC-Def.h"

class BMCPotStateMachine {
public:
  BMCPotStateMachine() {}

  void begin(uint8_t taperType = BMC_POT_TAPER_LINEAR, uint8_t filterLevel = BMC_POT_FILTER_NORMAL){
    taper = taperType;
    filter = filterLevel;
    position = 255;
    lastPosition = 255;
    rawValue = 255;
    value = 255;
    stableSteps = 0;
    calibrationMin = 0;
    calibrationMax = 1023;
    rangeMin = 0;
    rangeMax = 127;
  }

  bool update(uint16_t raw){
    raw = constrain(raw, calibrationMin, calibrationMax);
    uint16_t norm = map(raw, calibrationMin, calibrationMax, 0, 1023);
    uint8_t currentRaw = (norm * 128 + 511) / 1023;

    if(currentRaw != rawValue){
      stableSteps = 0;
    }

    rawValue = currentRaw;

    if(value == 255){
      value = currentRaw;
    } else {
      value = (value + (rawValue * stableSteps)) / (stableSteps + 1);
      if(abs((int)rawValue - (int)value) > 10){
        value = (value + rawValue) / 2;
      }
    }

    stableSteps++;
    if(stableSteps >= 255){
      stableSteps = 255;
    }

    uint8_t newPos = value;
    uint8_t tapered = applyTaper(newPos);
    uint8_t mapped = map(tapered, 0, 127, rangeMin, rangeMax);

    if(mapped == position){
      return false;
    }

    lastPosition = position;
    position = mapped;
    return true;
  }

  uint8_t read(){
    return applyTaper(position > 127 ? 127 : position);
  }

  uint8_t readPosition(){
    return (position > 127) ? 127 : position;
  }

  uint8_t getLastValue(){
    return applyTaper(lastPosition > 127 ? 127 : lastPosition);
  }

  void setFilter(uint8_t level){
    filter = level;
  }

  void setTaper(uint8_t taperType){
    taper = taperType;
  }

  void setCalibrationRange(uint16_t minVal, uint16_t maxVal){
    calibrationMin = constrain(minVal, 0, 1023);
    calibrationMax = constrain(maxVal, calibrationMin + 1, 1023);
  }

  void setOutputRange(uint8_t minVal, uint8_t maxVal){
    rangeMin = minVal;
    rangeMax = (maxVal > minVal) ? maxVal : minVal + 1;
  }

  void recalculate(uint16_t raw){
    raw = constrain(raw, calibrationMin, calibrationMax);
    uint16_t norm = map(raw, calibrationMin, calibrationMax, 0, 1023);
    rawValue = (norm * 128 + 511) / 1023;
    value = rawValue;
    stableSteps = 0;
  }

  uint16_t getCalibrationMin(){ return calibrationMin; }
  uint16_t getCalibrationMax(){ return calibrationMax; }
  uint8_t getRangeMin(){ return rangeMin; }
  uint8_t getRangeMax(){ return rangeMax; }

private:
  uint8_t position = 255;
  uint8_t lastPosition = 255;
  uint8_t rawValue = 255;
  uint8_t value = 255;
  uint8_t stableSteps = 0;

  uint8_t taper = BMC_POT_TAPER_LINEAR;
  uint8_t filter = BMC_POT_FILTER_NORMAL;

  uint16_t calibrationMin = 0;
  uint16_t calibrationMax = 1023;

  uint8_t rangeMin = 0;
  uint8_t rangeMax = 127;

  uint8_t applyTaper(uint8_t val){
    if(taper == BMC_POT_TAPER_AUDIO){
      float norm = val / 128.0f;
      float curved = powf(norm, 2.5f);
      return (uint8_t)(curved * 127.0f + 0.5f);
    }
    return val > 127 ? 127 : val;
  }
};

#endif
