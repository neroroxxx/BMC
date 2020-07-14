*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI API
There are many API callbacks and functions available for use, these may not reflect the latest version

### Sending MIDI Messages
```c++
void sendRealTime(uint8_t port, uint8_t type, uint8_t cable=0);

void sendSysEx(uint8_t port, uint8_t *data, uint16_t size, bool hasTerm=false, uint8_t cable=0);

void sendProgramChange(uint8_t port, uint8_t channel, uint8_t program, uint8_t cable=0);

void sendControlChange(uint8_t port, uint8_t channel, uint8_t control, uint8_t value, uint8_t cable=0);

void sendNoteOn(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0);

void sendNoteOff(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0);

void sendPitchBend(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0);

void sendAfterTouch(uint8_t port, uint8_t channel, uint8_t pressure, uint8_t cable=0);

void sendAfterTouchPoly(uint8_t port, uint8_t channel, uint8_t note, uint8_t pressure, uint8_t cable=0);

void sendTimeCodeQuarterFrame(uint8_t port, uint8_t type, uint8_t value, uint8_t cable=0);

void sendSongPosition(uint8_t port, uint16_t beats, uint8_t cable=0);

void sendSongSelect(uint8_t port, uint8_t song, uint8_t cable=0);

void sendTuneRequest(uint8_t port, uint8_t cable=0);

void beginRpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0);

void sendRpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0);

void sendRpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0);

void sendRpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0);

void endRpn(uint8_t port, uint8_t channel, uint8_t cable=0);

void beginNrpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0);

void sendNrpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0);

void sendNrpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0);

void sendNrpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0);

void endNrpn(uint8_t port, uint8_t channel, uint8_t cable=0);
```

### Callbacks
```c++
// triggered when a MIDI message is received
void onMidiRx(void (*fptr)(BMCMidiMessage data));

// triggered when a MIDI Clock (0xF8) message is received
void onMidiClockTick(void (*fptr)());

// triggered when a midi message was sent or received
void onMidiActivity(void (*fptr)(bool in, bool out));

// triggered when MIDI data is updated within the Local MIDI Data
// BMC holds 129 bytes for each of the 16 MIDI Channels,
// 1 for Program and 127 for Control Change, when you send or receive
// a Program Change this value is updated for that channel, the same goes for
// Control Changes. This data is also updated if the message isn't actually sent
// to a port, so if a button has a Program Change event but no Ports BMC will
// still update this value.
void onMidiLocalUpdate(void (*fptr)());
```

### BMCMidiMessage
BMC has an object that is used to hold incoming MIDI messages, this object is passed to the `onMidiRx` callback.

This object is also used by the editor to encode/decode data.

Some of the methods of `BMCMidiMessage` you may use include:

```c++
uint8_t getStatus(bool t_and=false);
uint8_t getChannel();
uint8_t getData1();
uint8_t getData2();
uint8_t getPort();

void setStatus(uint8_t t_status);
void setChannel(uint8_t t_channel);
void setData1(uint8_t t_data1);
void setData2(uint8_t t_data2);
// set the source port(s) to send the message to
void setPort(uint8_t t_port);
// reset all data in the struct
void reset(uint8_t sourcePortBit=0);
// append a byte to the sysex array
// @value the byte to append
// @andByte if true, removes the 8th bit of the byte
// this is because MIDI data is only 7-bit and 8-bit bytes
// are reserved for MIDI Status
void appendSysExByte(uint8_t value, bool andByte=true);
// get the sysex array
uint8_t * getSysEx();
// get the size/length sysex array
uint16_t size();
```
