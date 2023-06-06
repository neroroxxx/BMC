//----------------------------------//
// LFO CLASS MODIFIED FOR BMC USE
// all credits to the original developer
// https://github.com/mo-thunderz/lfo
// LFO class for Arduino
// by mo-thunderz
// version 1.1
// last update: 29.12.2020
//----------------------------------//

#include "Arduino.h"

#ifndef BMCLFO_h
#define BMCLFO_h

#define BMC_LFO_MODE_SYNC 0
#define BMC_LFO_MODE_FREE_FORM 1

#define BMC_LFO_SINE 1
#define BMC_LFO_SAW 2
#define BMC_LFO_TRIANGLE 3
#define BMC_LFO_SQUARE 4

#define BMC_LFO_NOTE_DIV_WHOLE       0
#define BMC_LFO_NOTE_DIV_HALF     	 1
#define BMC_LFO_NOTE_DIV_QUARTER  	 2
#define BMC_LFO_NOTE_DIV_EIGHTH   	 3
#define BMC_LFO_NOTE_DIV_SIXTEENTH	 4

#define BMC_LFO_DAC_SIZE 128
#define BMC_LFO_DAC_SIZE_HALF 64
#define BMC_LFO_AMPLITUDE 127
#define BMC_LFO_AMPLITUDE_HALF 63

class BMCLFO {
  public:
    // constructor
    BMCLFO(){
      timeoutSend = millis();
    }
    void start(){
      enabled = true;
      sync();
    }
    void stop(){
      enabled = false;
      sync();
    }
    void toggle(){
      enabled = !enabled;
      sync();
    }
    void setRange(uint8_t t_min, uint8_t t_max){
      if(t_max <= t_min){
        min = 0;
        max = 127;
      } else {
        min = t_min;
        max = t_max;
      }
    }
    bool isEnabled(){
      return enabled;
    }
    bool send(){
      return readyToSend;
    }
    void setWaveForm(uint8_t value){
      waveForm = constrain(value, 0, 4);
    }
    void setMode(uint8_t value){
      mode = value > 1 ? 1 : value;
    }
    void setFreeFormFreq(float value){
      unsigned long m = micros();
      if(value < 0){
        value = 0;
      }
      // synchronize the phase of the old freq with the new freq
      float outputPhase_old = (double)(m - timeout) * freeFormFreq / 1000000 + freeFormPhaseOffset;
      float outputPhase_new = (double)(m - timeout) * value / 1000000;
      outputPhase_old = outputPhase_old - floor(outputPhase_old);
      outputPhase_new = outputPhase_new - floor(outputPhase_new);
      freeFormPhaseOffset = outputPhase_old - outputPhase_new;
      freeFormFreq = value;
    }
    // set BPM of track for sync mode
    void setBpm(float value){
      bpm = (value < 0) ? 0 :value;
    }
    void setSendCycle(uint8_t value){
      sendCycle = (constrain(value, 0, 9)+1) * 10;
    }
    // lmodel_rate represents the lfo cycle duration in quarter notes
    void setBpmRate(uint8_t value){
      value = constrain(value, 0, 4);
      bpmRate = bpmRates[value];
    }
    // function to sync LFO to external trigger -> use sync(micros())
    void sync(){
      timeout = micros();
      freeFormPhaseOffset = 0;
    }
    int getWave(unsigned long l_t){
      uint8_t output = 0;
      readyToSend = false;
      if(((unsigned long)millis()-timeoutSend) >= sendCycle){
        timeoutSend = millis();
        readyToSend = true;
      }
      if(mode == BMC_LFO_MODE_SYNC){
        // LFO synced
        outputPhase = (float)((unsigned long)(l_t - timeout)) * (float)bpmRate * bpm / 60000000;
      } else {
        // LFO free running
        outputPhase = (float)((unsigned long)(l_t - timeout)) * freeFormFreq / 1000000 + freeFormPhaseOffset;
      }
      switch(waveForm){
        case BMC_NONE: // Off
          break;
        case BMC_LFO_SINE: // Sin
          output = (uint8_t) BMC_LFO_AMPLITUDE_HALF * cos(2 * BMC_PI * outputPhase) + BMC_LFO_AMPLITUDE_HALF;
          break;
        case BMC_LFO_SAW: // Saw
          output = BMC_LFO_AMPLITUDE * (1 - fmod(outputPhase, 1)) + BMC_LFO_AMPLITUDE_HALF - BMC_LFO_AMPLITUDE_HALF;
          break;
        case BMC_LFO_TRIANGLE: // Triangle
          if(((uint8_t)(2 * outputPhase))%2){
            // up flank
            output = 2 * BMC_LFO_AMPLITUDE * fmod(outputPhase, 1) + BMC_LFO_AMPLITUDE_HALF - 3 * BMC_LFO_AMPLITUDE_HALF;
          } else {
            // down flank
            output = BMC_LFO_AMPLITUDE * (1.5 - 2 * fmod(outputPhase, 1)) + BMC_LFO_AMPLITUDE_HALF - BMC_LFO_AMPLITUDE;
          }
          break;
        case BMC_LFO_SQUARE: // Square
          if(((int)(2 * outputPhase))%2){
            output = BMC_LFO_AMPLITUDE_HALF - BMC_LFO_AMPLITUDE_HALF;
          } else {
            output = BMC_LFO_AMPLITUDE_HALF + BMC_LFO_AMPLITUDE_HALF;
          }
          break;
      }
      return map(output, 0, 127, min, max);
    }

  private:
    bool enabled = false;
    bool readyToSend = false;
    uint8_t mode = 0;
    uint8_t lastOutput = 5;
    uint16_t sendCycle = 25;
    uint8_t min = 0;
    uint8_t max = 127;
    uint8_t waveForm = 1; // 0 -> off, 1 -> saw, 2 -> triangle, 3 -> sin, 4 -> square [0,4]
    float freeFormFreq = 30; // frequency in Hz
    uint16_t bpm = 120; // BPM of track
    float bpmRate = BMC_LFO_NOTE_DIV_QUARTER; // Rate to link to BPM of track
    // time reference needed for sync waves:
    unsigned long timeout = 0;
    unsigned long timeoutSend = 0;
    // internal value to keep phase with freq changes in free mode:
    // phase offset of LFO in free-running mode -> this parameter is used internally
    // to enable a seamless freq change with this function: 
    // setMode0Freq(float lfreeFormFreq, unsigned long l_t);
    float freeFormPhaseOffset = 0;
    // phase of the signal -> is updated whenever getWave() is called -> this 
    // phase is useful for triggering an LED -> use getPhase() to retrieve.
    // net phase of produced waveform -> used to trigger LEDs
    float outputPhase = 0;
    const float bpmRates[5] = {
      0.25, // 1
      0.5, // 1/2
      1, // 1/4
      2, // 1/8
      4, // 1/16
    };
};

#endif

//---------------------------------
//         .125|   Whole x 2
//         .25 |   Whole
//         .5  |   1/2 note
//         1   |   1/4 note
//         2   |   1/8 note
//         3   |   1/12 note
//         4   |   1/16 note
//         5   |   1/20 note
//         6   |   1/24 note
//         7   |   1/28 note
//         8   |   1/32 note
//         9   |   1/36 note
//        10   |   1/40 note
//        11   |   1/44 note
//        12   |   1/48 note
//        13   |   1/52 note
//        14   |   1/56 note
//        15   |   1/60 note
//        16   |   1/64 note
//
// Big THANKS to othmar52 for providing the table :-)
