*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# DAW Logic Control
BMC now supports Logic Control, allowing you to build your own DAW (Digitial Audio Workstation) controller for any DAW that supports Logic Control.

DAW Logic Control includes events for button, encoders and Leds, these can be
mapped to functions to control your DAW including PLAY, STOP, CH SOLO, CH MUTE, etc.

You can use encoders as V-Pots, Jog Wheel and to emulate Motorized Faders.

Buttons include all transport functions, track specific functions and also functions
for the selected track.

BMC will also has API calls and callbacks to send/receive data from the DAW, these
include Meters, LCD Text, and status LEDs.

You can enable DAW Control within the Config File Maker.


### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
//returns the selected channel number
uint8_t getDawSelectedTrack();
//returns state of a specified LED in the led ring of a VPOT.
// you can use this for a custom led ring to update weather that led should
// be on or off
uint8_t getDawVPotLedState(uint8_t channel, uint8_t ledN);
```
##### CALLBACKS
```c++
// passes the state of the connect, true if a project is loaded
void onDawOnline(void (*fptr)(bool state));
// passes the sysex message containing the updated LCD string
void onDawRecievedLCD(void (*fptr)(BMCMidiMessage data));
// more info to come
void onDawRecievedTimeDisplay(void (*fptr)(uint8_t digit, char character));
// more info to come
void onDawRecievedAssignmentDisplay(void (*fptr)(uint8_t digit, char character));
// passes the meter value for a channel
void onDawRecievedChannelMeter(void (*fptr)(uint8_t channel, uint8_t value));
// passes the meter value for a channel, includes the overload led status
void onDawChannelMeterUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t overload));
// more info to come
void onDawReceivedTimeCodeDigit(void (*fptr)(uint8_t digit, uint8_t value));
// passes the value of the VPOT ring for the specified channel
void onDawChannelVPotUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t centered, uint8_t mode));
// passes the specified channel's fader position
void onDawRecievedChannelFaderPosition(void (*fptr)(uint8_t channel, int value));
// passes the master channel's fader position
void onDawRecievedMasterFaderPosition(void (*fptr)(int value));
// receive the state of a channel, true if the channel is currently selected
void onDawRecievedChannelSelect(void (*fptr)(uint8_t channel, bool state));
// receive the solo state of a channel, true if the channel is currently in solo
void onDawRecievedChannelSolo(void (*fptr)(uint8_t channel, bool state));
// receive the mute state of a channel, true if the channel is currently in mute
void onDawRecievedChannelMute(void (*fptr)(uint8_t channel, bool state));
// receive the rec/ready state of a channel, true if the channel is currently in rec/ready
void onDawRecievedChannelRecReady(void (*fptr)(uint8_t channel, bool state));
// receive the state leds, @cmd will carry the function of the LED, see documentation
void onDawRecievedLedState(void (*fptr)(uint8_t cmd, bool state));
```
