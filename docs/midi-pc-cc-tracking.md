*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI PC/CC Tracking

BMC will keep track of the current PC (Program Change) and the value of each of the 128 Control Changes (CC) for each of the 16 Channels in the MIDI protocol.

In other words, if you send or receive Program # 0 on Channel # 5, BMC will remember that. Later in your program you can ask BMC what PC you are in, and use it in a display or to increase the current PC number. This feature is used with Encoders for example to increase/decrease the PC by rotating the Encoder.

These values are also be used for LEDs, for example an LED can be turned on when CC#10 has a value of 6 otherwise it would be off.

**All this data is stored in RAM only so when you restart BMC it will be reset.**

You can assign a button to send that CC which in turn will turn the led on until another value is received/sent. Additionally you can execute a CC command without sending it to a MIDI Port in which case BMC will just hold it in RAM.

BMC has a local midi data object ***BMCMidiData***, this object uses up about 2KB of RAM, this object holds data for 16 MIDI channels, each with it's own Program value and 128 Control values, basically BMC will remember the last incoming/outgoing MIDI Program Change and Control Change on every channel!

If you are using a Teensy LC or if you are planning on your sketch using a lot of RAM for other purposes then you may not want to use that 2K of RAM for MIDI Tracking, for this purpose there's the `BMC_MAX_MIDI_CHANNEL_TRACKING` define in the config file, this parameter will tell BMC to only allocate a specific number of channels to be tracked.

You can `BMC_MAX_MIDI_CHANNEL_TRACKING` with the config file maker, this define must have a value ranging from 1 to 16, the value passed holds the number of channels that will be tracked, for each channel tracked 129 bytes of RAM will be used, exp: if `BMC_MAX_MIDI_CHANNEL_TRACKING` is 1 then only channel 1 is tracked and 129 bytes of RAM will be allocated, if `BMC_MAX_MIDI_CHANNEL_TRACKING` is 3 then channels 1, 2 and 3 will be tracked and 387 (129*3) bytes will be allocated.

**At least 1 channel must be tracked. This data is Global and Port independent.**


The object that holds the data for each channel looks like this:

```c++
struct BMCMidiDataChannel {
  uint8_t program = 0;
  uint8_t control[128];
};
```

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
// if using BMC_MAX_MIDI_CHANNEL_TRACKING, only the allocated number of channels are tracked
void setLocalProgram(uint8_t t_channel, uint8_t t_program);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
// if using BMC_MAX_MIDI_CHANNEL_TRACKING, only the allocated number of channels are tracked
void setLocalControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
// if using BMC_MAX_MIDI_CHANNEL_TRACKING, only the allocated channel value will be returned
// otherwise 0 will be returned
uint8_t getLocalProgram(uint8_t t_channel);

// @t_channel MUST be 1 thru 16, not 0 thru 15
// all other parameters are 0 indexed
// if using BMC_MAX_MIDI_CHANNEL_TRACKING, only the allocated channel value will be returned
// otherwise 0 will be returned
uint8_t getLocalControl(uint8_t t_channel, uint8_t t_control);
```
