*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI IO Ports
BMC has support for up to 7 MIDI IO Ports, there's USB *(required)*, up to 4 Hardware Serial ports (depending on your Teensy) for MIDI DIN jacks, USB Host (Teensy 3.6/4.0) and Bluetooth LE (using nRF8001).
When you create your Config File you can choose which to compile, you can use any or all of them, then within the editor app you can choose where each MIDI event is sent + you can have **Port Presets**.

Their bit order is:
0. USB `BMC_MIDI_PORT_USB_BIT`
1. Serial A `BMC_MIDI_PORT_USB_BIT`
2. Serial B `BMC_MIDI_PORT_USB_BIT`
3. Serial C `BMC_MIDI_PORT_USB_BIT`
4. Serial D `BMC_MIDI_PORT_USB_BIT`
5. USB Host `BMC_MIDI_PORT_USB_BIT`
6. BLE `BMC_MIDI_PORT_USB_BIT`

```c++
#define BMC_USB       B00000001 // 0x01 (1)
#define BMC_SERIAL_A  B00000010 // 0x02 (2)
#define BMC_SERIAL_B  B00000100 // 0x04 (4)
#define BMC_SERIAL_C  B00001000 // 0x08 (8)
#define BMC_SERIAL_D  B00010000 // 0x10 (16)
#define BMC_HOST      B00100000 // 0x20 (32)
#define BMC_BLE       B01000000 // 0x40 (64)
```

With the BMC API you can send a MIDI port ORing the defines above.


```c++
// Send Program to USB MIDI
bmc.sendProgramChange(BMC_USB, channel, program);

// Send Program to Serial B and USB Host
bmc.sendProgramChange(BMC_SERIAL_B | BMC_HOST, channel, program);

// Send Program to all ports available
bmc.sendProgramChange(BMC_ALL_PORTS, channel, program);

// Bit 7 is the flag that specifies it's a Port Preset.
// Send Program to port presets
bmc.sendProgramChange(BMC_PORTP_0, channel, program);
bmc.sendProgramChange(BMC_PORTP_1, channel, program);
bmc.sendProgramChange(BMC_PORTP_2, channel, program);
bmc.sendProgramChange(BMC_PORTP_3, channel, program);
bmc.sendProgramChange(BMC_PORTP_4, channel, program);
bmc.sendProgramChange(BMC_PORTP_5, channel, program);
bmc.sendProgramChange(BMC_PORTP_6, channel, program);
bmc.sendProgramChange(BMC_PORTP_7, channel, program);
bmc.sendProgramChange(BMC_PORTP_8, channel, program);
bmc.sendProgramChange(BMC_PORTP_9, channel, program);
bmc.sendProgramChange(BMC_PORTP_10, channel, program);
bmc.sendProgramChange(BMC_PORTP_11, channel, program);
bmc.sendProgramChange(BMC_PORTP_12, channel, program);
bmc.sendProgramChange(BMC_PORTP_13, channel, program);
bmc.sendProgramChange(BMC_PORTP_14, channel, program);
bmc.sendProgramChange(BMC_PORTP_15, channel, program);
```

### MIDI Ports Presets
Because BMC can have an arbitrary number of MIDI IO Ports and events can be sent to any combination of these sometimes it can be a pain to have to change what IO Port a message is sent to, specially if originally you wanted the message to be sent to say the USB Host port but you later decide to change that device to the SerialA port now you have to change all your library messages or your button events to send messages to that port! This is where Port Presets Shine! you have up to 16 Port Presets then all your events can be assigned to a Port preset instead of a specific port.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
