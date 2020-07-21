*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI Clock
BMC can be a Master or Slave MIDI Clock, you can use encoders, pots, buttons or the API to set the BPM in Master Mode and you can sync Leds and Callbacks to keep track of the ticks.

BMC can be set to either Master/Slave, this is editable within the editor's settings.

The Master Clock uses a simple timeout (no hardware timer/interrupt), Teensy's are fast enough to keep accurate timing for the 24 ticks per beat.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// for master or slave clock
// get the current BPM
uint16_t getMidiClockBpm();

// only works when on master clock
// set the Clock's BPM
void setMidiClockBpm(uint16_t t_bpm);

// only works when on master clock
// simulates a Tap Tempo
// the Clock BPM is determined based on how often the function is called
// for example if there's a gap of 500ms between calling this function
// the BPM would be set to 120 BPM, (60000/500) = 120
void midiClockTap();
```

##### CALLBACKS
```c++
// triggered when a MIDI Clock message is received
void onMidiClockTick(void (*fptr)());

// triggered every 24 times a MIDI Clock message is received
void onMidiClockBeat(void (*fptr)());

// triggered when the Master/Slave Clock has changed it's tempo
void onMidiClockBpmChange(void (*fptr)(uint16_t tempo));
```
