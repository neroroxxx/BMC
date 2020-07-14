*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Local MIDI Data
Because BMC runs on Teensy and they have lots of RAM, BMC holds any incoming/outgoing MIDI CC and PC on every channel! if CC#10 comes in with value 5 then BMC will keep that in RAM, with this, BMC can give you options like toggling values or scrolling thru those values with encoders etc.

These values are also be used for LEDs, for example an LED can be turned on when CC#10 has a value of 6 otherwise it would be off.

You can assign a button to send that CC which in turn will turn the led on until another value is received/sent. Additionally you can execute a CC command without sending it to a MIDI Port in which case BMC will just hold it in RAM.

BMC has a local midi data object ***BMCMidiData***, this object uses up about 2KB of RAM, this object holds data for 16 MIDI channels, each with it's own Program value and 128 Control values, basically BMC will remember the last incoming/outgoing MIDI Program Change and Control Change on every channel! this is used for Toggling Control Changes from 0/127 and to scroll thru program changes with encoders or buttons and to show you the current value with LEDs.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### CALLBACKS
```c++
// triggered when MIDI data is updated within the Local MIDI Data Object
// BMC holds 129 bytes for each of the 16 MIDI Channels,
// 1 for Program and 128 for Control Change, when you send or receive
// a Program Change this value is updated for that channel, the same goes for
// Control Changes. This data is also updated if the message isn't actually sent
// to a port, so if a button has a Program Change event but no Ports BMC will
// still update this value.
void onMidiLocalUpdate(void (*fptr)());
```

##### FUNCTIONS
```c++
// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
void setLocalProgram(uint8_t t_channel, uint8_t t_program);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
void setLocalControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
uint8_t getLocalProgram(uint8_t t_channel);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
uint8_t getLocalControl(uint8_t t_channel, uint8_t t_control);
```
