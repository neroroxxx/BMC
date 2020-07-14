*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Device ID and Chaining Port
Aside from the SysEx ID of your device, BMC also gives you the option to dynamically change the Device ID for each of your builds, you can have up to 16 unique device IDs, the device ID is part of the SysEx messages used for communication between the Editor and BMC on your Teensy. This Device ID can be updated via **SETTINGS** and if you change the device ID you MUST also update it in the Editor's Connection Window because if the ID on the connection window doesn't match BMC will not respond to those messages.

The device ID is also used when Chaining BMC Devices. Chaining allows you to have 1 BMC device connected to your Computer and then another BMC build (with a different Device ID) connected to the specified Chaining Port under **SETTINGS**. This may seem a bit confusing but it's actually pretty simple, say you have 2 BMC devices, we'll call them "Main" and "Mini", Main has Device ID 0 and Mini has Device ID 1. Connect Main to your computer, and connect Mini to a MIDI IO Port on Main (we'll use USB Host for this example, NOTE: the chaining port must be bi-directional), set the Chaining port to USB HOST on Main.
Now you can disconnect from the editor, set Device ID to 1 on the connection window and the Editor will connect to "Mini", disconnect from the editor and set Device ID to 0 and BMC will now connect to "Main". Get it?

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
