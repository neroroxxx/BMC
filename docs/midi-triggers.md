*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI Triggers
BMC has MIDI Triggers, the are events that are triggered when the specified MIDI message is received, you can specify the MIDI message type/channel/data1/data2 of the incoming MIDI message, when that message is matched the assigned event is executed. Triggers also have an operator so the message value can be equal to, more than, less than, etc.

Each MIDI Trigger is unique and can be used for a ton of features, one of the best features would be if you create 1 BMC box to act as your MIDI BRAIN, this box can have buttons compiled but no actual buttons connected to the pins, you can then use a MIDI foot controller you already own to send MIDI CCs to your BMC say a value 127 when the button is pressed and value 0 when released, the triggers can then Trigger a button press on BMC when value 127 was received and a release of the button when value 0 is received, basically an external MIDI controller can be used to control your BMC box, this way you don't actually have to find a big enough box to put all your footswitches if you already own a midi foot-controller!

Additionally MIDI Triggers can translate an incoming MIDI Message, for example if BMC receives CC#10 on Channel 5, BMC can send CC#10 on Channel 7 to another one of your devices, you can also convert a Program Change to Control Change etc.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
