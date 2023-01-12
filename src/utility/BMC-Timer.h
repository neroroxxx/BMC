/*
  See https://www.BMCXxtar.com/bmc for more details
  Copyright (c) 2020 BMCXxtar.com
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
#ifndef BMCTimer_h
#define BMCTimer_h
#include <Arduino.h>
// classes used to get the time in milliseconds or microseconds
class BMCTimingMillis {
  public: static unsigned long get(){ return (unsigned long) millis(); }
};
class BMCTimingMicros {
  public: static unsigned long get(){ return (unsigned long) micros(); }
};

// ***************************************
// ***************************************
//                BMCTimerBase
// base class for timers
// ***************************************
// ***************************************
template <typename _BMCTiming, typename intervalType_t>
class BMCTimerBase {
private:
  intervalType_t interval = 1000;
  unsigned long  prevTime = 0;
public:
  BMCTimerBase(){
    stop();
  }
  operator bool(){
    return complete();
  }
  // start the timer, pass number of milliseconds as the parameter
  void start(intervalType_t value){
    interval = value;
    prevTime = (unsigned long) _BMCTiming::get();
  }
  // update the number of milliseconds that need to pass
  void update(intervalType_t value){
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
    if(active() && (unsigned long)(_BMCTiming::get() - prevTime) >= interval) {
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
      return (unsigned long)(_BMCTiming::get() - prevTime);
    }
    return 0;
  }
  // stop the timer
  void stop(){
    prevTime = 0;
  }
};

// ***************************************
// ***************************************
//          BMCEndlessTimerBase
// ***************************************
// ***************************************
template <typename _BMCTiming, typename intervalType_t>
class BMCEndlessTimerBase {
private:
  BMCTimerBase <_BMCTiming, intervalType_t> timer;
  intervalType_t interval = 1000;
public:
  BMCEndlessTimerBase(){}
  operator bool(){
    return complete();
  }
  void start(intervalType_t value){
    interval = value;
    timer.start(interval);
  }
  intervalType_t getInterval(){
    return interval;
  }
  void restart(){
    start(interval);
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


// uses millis() for timing
class BMCTimer : public BMCTimerBase <BMCTimingMillis, uint16_t> {};
// uses millis() for timing but allows for times longer than 1 minute
class BMCTimerLong : public BMCTimerBase <BMCTimingMillis, uint32_t> {};
// uses micros() for timing
class BMCMicroTimer : public BMCTimerBase <BMCTimingMicros, unsigned long> {};

// uses millis() for timing
class BMCEndlessTimer : public BMCEndlessTimerBase <BMCTimingMillis, uint16_t> {};
// uses millis() for timing but allows for times longer than 1 minute
class BMCEndlessTimerLong : public BMCEndlessTimerBase <BMCTimingMillis, uint32_t> {};
// uses micros() for timing
class BMCMicroEndless : public BMCEndlessTimerBase <BMCTimingMicros, unsigned long> {};


#endif
