*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Import/Export Build Data
Because BMC is so scalable it has an Import/Export tool thru the Editor App. When the editor connects to your Teensy it will load all the contents of your EEPROM along with a bunch of other data, all that data is organized into a JSON object by the editor app, this data can then be exported as a **backup** of your current EEPROM and BMC can then import that file.

This backup can actually be for a different build with a different number of buttons, leds, ports etc but the Editor will only import the data that your current build allows for, for example, if you import a build that has 2 buttons into a build that has 1 button, only the data for button 1 will be imported. If your backup has names for buttons but your new build doesn't then names will not be imported, if the new build does have names for buttons but they are of a different length, then the length imported will be bound by the length of your current build.

In other words, **you can import/export across different devices!** Additionally you can pick what data you want to import, so your import could only be library items or presets, etc.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### CALLBACKS
```c++
```

##### FUNCTIONS
```c++
```
