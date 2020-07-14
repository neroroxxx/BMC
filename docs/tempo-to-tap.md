*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Tempo To Tap
Many MIDI Devices have a Tap Tempo feature, usually you send them their specified Control Change and based on the interval between those Control Change Messages your MIDI device will calculate the BPM and set a new BPM. BMC can take it's Master/Slave Clock Tempo as it changes and automatically send a set of Program, Control or Note messages in intervals based on BMC's current BPM, essentially simulating you doing the Tap Tempo.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
