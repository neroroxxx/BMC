/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A wrapper to check the specified number of milliseconds have passed
  Once the number of milliseconds have passed the timer will stop

  This class uses the standard millis() way to check if time has passed

  This file contains 4 classes:

  BMCTimer = a 1 shot timer, it can be started as many times as you want
            but once it reaches the interval you have to start it again
            interval is passed in milliseconds.
            BMCTimer::start(1000) this starts timing for 1000 milliseconds (1 second)
            BMCTimer::complete()/BMCTimer::expired() both these are the same,
            they return true if one second has passed since the timer started.
            once you use complete() or expired() the timer will stop timing, you
            would have to start() it again, hence why it's a 1 shot timer.
            You can restart it at any point.

  BMCMicroTimer = same as BMCTimer but in micros

  BMCEndlessTimer = a timer that will continously run, each time the interval has been
              reached it will restart itself

  BMCMicroEndless = same as BMCEndlessTimer but it uses the micros() function
                  making a little more accurate, this is used by BMC's MIDI Clock
*/
#ifndef BMC_TIMER_H
#define BMC_TIMER_H

#include <Arduino.h>
class BMCTimer {
private:
  uint16_t interval = 1000;
  unsigned long prevTime = 0;
public:
  BMCTimer(){
    stop();
  }
  operator bool(){
    return complete();
  }
  // start the timer, pass number of milliseconds as the parameter
  void start(uint16_t value){
    interval = value;
    prevTime = millis();
  }
  // update the number of milliseconds that need to pass
  void update(uint16_t value){
    if(active()){
      interval = value;
    }
  }
  // trigger the timer as complete,
  // this will make the complete() method return true the next time
  // useful if something you were waiting for happened already
  // elsewhere in your code
  void trigger(){
    start(0);
  }
  // returns true if the timer is currently running
  bool active(){
    return (prevTime>0);
  }
  // returns true if the time specified has been reached
  // after that point the complete() method will return false until
  // start() has been called again
  bool complete(){
    if(active() && (unsigned long)(millis() - prevTime) >= interval) {
      stop();
      return true;
    }
    return false;
  }
  bool reached(){ return complete(); }
  bool expired(){ return complete(); }
  // return the number of milliseconds remaining before complete is triggered
  unsigned long remaining(){
    if(active()){
      return (unsigned long)(millis() - prevTime);
    }
    return 0;
  }
  // stop the timer
  void stop(){
    prevTime = 0;
  }
};
/***************************************************************************/
class BMCMicroTimer {
private:
  unsigned long interval = 1000;
  unsigned long prevTime = 0;
public:
  BMCMicroTimer(){
    stop();
  }
  operator bool(){
    return complete();
  }
  // start the timer, pass number of microseconds as the parameter
  void start(uint32_t value){
    interval = value;
    prevTime = micros();
  }
  // update the number of microseconds that need to pass
  void update(uint32_t value){
    if(active()){
      interval = value;
    }
  }
  // trigger the timer as complete,
  // this will make the complete() method return true the next time
  // useful if something you were waiting for happened already
  // elsewhere in your code
  void trigger(){
    start(0);
  }
  // returns true if the timer is currently running
  bool active(){
    return (prevTime>0);
  }
  // returns true if the time specified has been reached
  // after that point the complete() method will return false until
  // start() has been called again
  bool complete(){
    if(active() && (unsigned long)(micros() - prevTime) >= interval) {
      stop();
      return true;
    }
    return false;
  }
  bool reached(){ return complete(); }
  bool expired(){ return complete(); }
  // return the number of milliseconds remaining before complete is triggered
  unsigned long remaining(){
    if(active()){
      return (unsigned long)(micros() - prevTime);
    }
    return 0;
  }
  // stop the timer
  void stop(){
    prevTime = 0;
  }
};
/***************************************************************************/
class BMCEndlessTimer {
private:
  BMCTimer timer;
  uint16_t interval = 1000;
public:
  BMCEndlessTimer(uint16_t value=0){
    if(value>0){
      start(value);
    }
  }
  operator bool(){
    return complete();
  }
  void start(uint16_t value){
    interval = value;
    timer.start(interval);
  }
  bool reached(){ return complete(); }
  bool expired(){ return complete(); }
  bool complete(){
    if(timer.complete()){
      timer.start(interval);
      return true;
    }
    return false;
  }
  void stop(){
    end();
  }
  void end(){
    timer.stop();
  }
};
/***************************************************************************/
class BMCMicroEndless {
private:
  BMCTimer timer;
  unsigned long interval = 0xF4240;// start at 1 minute
  unsigned long prevTime = 0;
public:
  BMCMicroEndless(unsigned long value=0){
    if(value>0){
      start(value);
    }
  }
  operator bool(){
    return complete();
  }
  void start(unsigned long value){
    interval = value;
    prevTime = micros();
  }
  bool reached(){ return complete(); }
  bool expired(){ return complete(); }
  bool complete(){
    if(active() && (unsigned long)(micros() - prevTime) >= interval) {
      prevTime = micros();
      return true;
    }
    return false;
  }
  bool active(){
    return (prevTime>0);
  }
  void stop(){
    end();
  }
  void end(){
    prevTime = 0;
  }
};
#endif
