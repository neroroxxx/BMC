*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Debug
BMC has a **DEBUG** Mode, your config must include #define BMC_DEBUG for it to be activated (this can be set with the Config File Maker). With DEBUG enabled you can open the Serial Monitor on the Arduino IDE and see any error messages at launch, additionally you can type **help** to see a list of commands available. Once you have tested your device you should disable DEBUG mode for better performance.

If you type **metrics** in the serial monitor with DEBUG enabled BMC will print the number of loops per second that are being executed and the amount of Free RAM. This is just a basic way to see how many times the Arduino `loop()` function is being executed per second and to get an idea of much RAM BMC is using. This vary's between Teensy boards and BMC Builds, some hardware runs slower than other.

For example, since LEDs can be assigned to say a MIDI Control Change Value, BMC will constantly update the LED to on/off based on the value of the Control on the specific channel, HOWEVER the actual `digitalWrite()` is only used if the state of the LED is different to keep from constantly doing a `digitalWrite()` HIGH on a pin that's already HIGH speeding up the process

### PRINTING TO THE SERIAL MONITOR DURING DEBUG
BMC also has macros that allow you to easily print to the Serial Monitor during DEBUG, these include `BMC_PRINT` and `BMC_PRINTLN`, what's cool about these is that they you can put them in your code and they are only compiled when in DEBUG mode, when you are done debugging you don't have to remove them from your sketch as they are not compiled.
Another great feature of these is that they are dynamic argument macros, in other words if you want to print something like "Control Change 0 received" you just have to use:
```c++
BMC_PRINTLN("Control Change",ccVariable,"received")
```

This is the equivalent of:

```c++
Serial.print("Control Change");
Serial.print(" ");
Serial.print(ccVariable);
Serial.print(" ");
Serial.println("received")
```
As you can see above a "Space" is added between all variables, `BMC_PRINT` works the same as `BMC_PRINTLN` execept that `BMC_PRINTLN` uses `println` for the last argument.
If you want to print them without spaces between variables you can use `BMC_PRINTLNNS`. These can all take up to 10 variables.
The source for these is in *src/utility/BMC-Debug.h*

### FAST MODE
You can also enable Fast Mode with the Config File Maker, this should only be done once you have already tested your build, this will remove double checking certain flags and certain misconfiguration at run time. This setting is currently very basic but will be expanded over time.


### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// these are only compiled if BMC_DEBUG is enabled
// print up to 10 arguments inline to the serial monitor
// with a space between arguments + new line after last argument
BMC_PRINTLN(...)

// print up to 10 arguments inline to the serial monitor
// with a space between arguments without new line after last argument
BMC_PRINT(...)
```
##### CALLBACKS
```c++
```
