*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Custom SysEx
BMC has a library of Custom System Exclusive messages that you can edit and then send them as part of the BMC Library or as part of Button Events.

Each Custom SysEx has 16 Bytes *(BMC will automatically add the 0xF0 and 0xF7 status bytes)* you can then send these or even Merge up to 2 into 1 message if 16 bytes isn't enough.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// send the specified Custom SysEx Message to the specified Ports
// @n the index of the custom sysex
// @ports midi ports mask
void sendCustomSysEx(uint8_t n, uint8_t ports);
// send 2 custom sysex messages merged into 1
// all used bytes of message a are sent first then the used bytes of message b
// @a the index of the first custom sysex
// @b the index of the second custom sysex
// @ports midi ports mask
void sendMergedCustomSysEx(uint8_t a, uint8_t b, uint8_t ports);
```
##### CALLBACKS
```c++
```
