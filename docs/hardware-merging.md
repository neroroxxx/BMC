*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Hardware Merging
BMC offers hardware merging, each piece of hardware takes up room in EEPROM and consumes a pin or 2 depending on the hardware, you can then merge these elements into real world elements that the Editor App will display, for example, if you've used encoders before then you know most of them come with a Switch as part of the encoder that is read separately that way you can rotate the encoder or press it to do something else, you would create a button and an encoder on your config file with their pins assigned, without merging them they will each be displayed separately on the editor workspace but by merging them they will be displayed on your workspace as a single unit making it easier to edit them.

Hardware merging also include **AUX JACKS** these are specially awesome and paired with a Switching TRS Jack will give you the ability to have a jack that can switch from an Expression Pedal or Dual Buttons, to create an Aux Jack you need to create a POT and 2 Buttons, wiring is specified in the Config File Maker

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
