*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI Routing/Soft-Thru
BMC has the ability to route messages received by the INPUT of one port to the OUTPUT of another port. Also it can route the INPUT of one port to the same port's OUTPUT (effectively acting as a Software-Thru). This messages can be filtered, by message type group and by channel.

MIDI Messages type groups include **Voice/Channel Messages**, **System Exclusive**, **System Common** and **Real Time**

* **Voice/Channel Messages** include: Program Change, Control Change, Pitch Bend, Note On/Off and After-Touch, basically all messages with a MIDI Channel. *For Voice/Channel Messages you can also filter their channel.*
* **System Exclusive** include only System Exclusive messages.
* **System Common** include: Time Code Quarter Note Frame, Song Position, Song Select and Tune Request.
* **Real Time** include: Clock, Start, Continue, Stop, Active Sense and System Reset.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
