/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This struct is used throut BMC to scroll (increase/decrease) numbers
  I'm using a struct instead of a class make it easier to set the value
  required to scroll the number
  There are many parameters used to scroll these numbers including:

  lowest = lowest value we can ever reach
  highest = highest value we can ever reach
  amount = how much to scroll the unmber
  direction = up (true) or down (false)
  endless = true to endlessly scroll from low to high and vice-versa
  value =  the number to scroll

*/
#ifndef BMC_SCROLL_H
#define BMC_SCROLL_H
#include <Arduino.h>

template <typename T>
class BMCScroller {
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



  T up(T t_amount, bool t_endless, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    return scroll(t_amount, BMC_SCROLL_UP, t_endless);
  }
  T down(T t_amount, bool t_endless, T t_value, T t_min, T t_max){
    setValue(t_value, t_min, t_max);
    return scroll(t_amount, BMC_SCROLL_DOWN, t_endless);
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
