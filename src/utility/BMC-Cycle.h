/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
  *
  * BMCCycle is a flexible utility class used to increment or decrement a value
  * within a configurable range, supporting clamped or wrap-around behavior.
  *
  * It is typically instantiated locally with configured bounds and options:
  *   - Type-safe (templated on value type, e.g. uint8_t)
  *   - Configurable minimum and maximum active range
  *   - Supports step amounts or percentage-based scrolls
  *   - Scroll direction and wrap behavior are user-defined
  *
  * Example:
  *   uint8_t result = BMCCycle<uint8_t>(0, 127)
  *     .withRange(32, 96)
  *     .withValue(64)
  *     .withAmount(10)
  *     .withDirection(BMC_UP) // or .withDirection(BMC_DOWN)
  *     .withWrap(BMC_WRAP) // or .withWrap(BMC_NO_WRAP)
  *     .process();
*/

#ifndef BMC_CYCLE_H
#define BMC_CYCLE_H
 
#include <Arduino.h>
 
// Templated class for cycling through numeric ranges with optional wrapping and direction control
template <typename T>
class BMCCycle {
public:
  // Constructor with required absolute bounds
  BMCCycle(T t_lowest, T t_highest)
  : lowest(t_lowest), highest(t_highest), min(t_lowest), max(t_highest) {}

  // Set the active scrolling range (must be within bounds)
  BMCCycle& withRange(T t_min, T t_max) {
    min = constrain(t_min, lowest, highest);
    max = constrain(t_max, min, highest);
    return *this;
  }

  // Set the current value to be cycled
  BMCCycle& withValue(T t_value) {
    value = t_value;
    return *this;
  }

  // Set the amount to increment/decrement by
  BMCCycle& withAmount(T t_amount) {
    amount = t_amount;
    return *this;
  }

  // Alias for withAmount() — more readable in some contexts
  BMCCycle& withStep(T t_step) {
    return withAmount(t_step);
  }

  // Set scroll direction (true = up, false = down)
  BMCCycle& withDirection(bool t_direction) {
    direction = t_direction;
    return *this;
  }

  // Enable or disable wrapping (endless scrolling)
  BMCCycle& withWrap(bool t_wrap) {
    wrap = t_wrap;
    return *this;
  }

  // Enable or disable percentage-based stepping
  BMCCycle& withPercentage(bool t_enable) {
    usePercentage = t_enable;
    return *this;
  }

  // Apply all settings and return the updated value
  T process() {
    T range = max - min + 1;
    T effectiveAmount = amount;
  
    // Convert step amount to percentage if enabled
    if (usePercentage) {
      effectiveAmount = (range * amount) / 100;
      if (effectiveAmount == 0) {
        effectiveAmount = 1;
      }
    }
  
    if (wrap) {
      // Wrap-around behavior
      if (direction) {
        // Scroll up and wrap
        value = min + ((value - min + effectiveAmount) % range);
      } else {
        // Scroll down and wrap
        T delta = effectiveAmount % range;
        value = min + ((value - min + range - delta) % range);
      }
    } else {
      // Clamped behavior
      if (direction) {
        T newValue = value + effectiveAmount;
        value = (newValue > max) ? max : newValue;
      } else {
        value = (value < min + effectiveAmount) ? min : value - effectiveAmount;
      }
    }
  
    return value;
  }
 
private:
  T lowest = 0;             // Absolute lowest bound
  T highest = 0;            // Absolute highest bound
  T value = 0;              // Current value to be processed
  T amount = 1;             // Step amount (or % if enabled)
  T min = 0;                // Active range minimum
  T max = 0;                // Active range maximum
  bool direction = false;   // false = down, true = up
  bool wrap = false;        // Enable wrap-around (endless cycling)
  bool usePercentage = false; // Use percentage for step calculation
 };






 // OLD BMC SCROLLER TO BE REMOVED



template <typename T>
class __attribute__((deprecated("BMCScroller is deprecated and will be removed in future versions. Use BMCCycle instead."))) BMCScroller {
public:
  BMCScroller(){
    reset();
  }
  BMCScroller(T t_value, T t_lowest, T t_highest){
    setBounds(t_lowest, t_highest);
    setValue(t_value);
  }
  BMCScroller(T t_lowest, T t_highest){
    setBounds(t_lowest, t_highest);
  }
  void increaseByPercentage(bool t_value){
    usePercentage = t_value;
  }
  void setBounds(T t_lowest, T t_highest){
    lowest = t_lowest;
    highest = t_highest;
  }
  void set(T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
  }
  void setValue(T t_value){
    value = t_value;
    min = lowest;
    max = highest;
  }
  void setRange(T t_min, T t_max){
    setValue(value, t_min, t_max);
  }
  void setValue(T t_value, T t_min, T t_max){
    value = t_value;
    min = t_min;
    max = t_max;
    if((min < lowest) || (min >= max)){
      min = lowest;
    }
    if((max > highest) || (max <= min)){
      max = highest;
    }
  }

  T up(T t_amount, bool endless){
    return scroll(t_amount, BMC_SCROLL_UP, endless);
  }
  T down(T t_amount, bool endless){
    return scroll(t_amount, BMC_SCROLL_DOWN, endless);
  }
  T scroll(T t_amount, uint8_t t_flags){
    return scroll(t_amount, bitRead(t_flags,0), bitRead(t_flags,1));
  }

  T up(T t_amount, bool t_endless, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    return scroll(t_amount, BMC_SCROLL_UP, t_endless);
  }
  T down(T t_amount, bool t_endless, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    return scroll(t_amount, BMC_SCROLL_DOWN, t_endless);
  }

  T scroll(T t_amount, bool direction, bool endless){
    if(usePercentage){
      t_amount = getPercentage(max, t_amount);
    }
    if(direction==BMC_SCROLL_UP){
      value = (endless) ? upEndless(t_amount) : upLimited(t_amount);
    } else {
      value = (endless) ? downEndless(t_amount) : downLimited(t_amount);
    }
    return value;
  }
  T scroll(T t_amount, uint8_t t_flags, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    return scroll(t_amount, bitRead(t_flags,0), bitRead(t_flags,1));
  }
  T scroll(T t_amount, bool direction, bool t_endless, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    if(direction==BMC_SCROLL_UP){
      value = (t_endless) ? upEndless(t_amount) : upLimited(t_amount);
    } else {
      value = (t_endless) ? downEndless(t_amount) : downLimited(t_amount);
    }
    return value;
  }

  void reset(){
    value = 0;
    min = 0;
    max = 0;
  }
private:
  bool usePercentage = false;
  T value = 0;
  T min = 0;
  T max = 0;
  T lowest = 0;
  T highest = 0;

  T getPercentage(T t_value, T t_amount=1){
    return ((((float)t_value) / 100) * (t_amount==0?1:t_amount));
  }

  T upEndless(T amount){
    long newValue = (value+amount);
    return (newValue > max || newValue < min) ? min : newValue;
  }
  T downEndless(T amount){
    long newValue = (value-amount);
    return (newValue < min) ? max : newValue;
  }
  T upLimited(T amount){
    long newValue = (value+amount);
    if(newValue>max){
      return max;
    } else if(newValue<min){
      return min;
    }
    return newValue;
  }
  T downLimited(T amount){
    long newValue = (value-amount);
    return (newValue < min) ? min : newValue;
  }
};
 







 #endif 