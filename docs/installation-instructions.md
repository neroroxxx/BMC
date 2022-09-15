*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Installing BMC

BMC consist of if a Library and a Custom Boards package.

BMC will require you to have Teensyduino Installed on your Arduino IDE.

You can watch BMC videos at [https://www.youtube.com/channel/UCDl3gSF3X0cuXY3fBwXpQYA/videos](https://www.youtube.com/channel/UCDl3gSF3X0cuXY3fBwXpQYA/videos)

***If you are brand new to Arduino or Teensy, make sure you get your feet wet first before you try BMC.***

If you don't have Teensyduino installed you can follow these instructions:

**For Arduino IDE 2.0.x**

Instal Teensyduino, you can follow the instructions here: [https://www.pjrc.com/arduino-ide-2-0-0-teensy-support/](https://www.pjrc.com/arduino-ide-2-0-0-teensy-support/)

**For Arduino 1.8.19**

First you will need to install the Teensyduino addon for Arduino with all it's libraries, you can download it and follow the installation instructions here [https://www.pjrc.com/teensy/td_download.html](https://www.pjrc.com/teensy/td_download.html)

Once you have Arduino and Teensyduino installed everything is working follow the steps below.

#### Step 1: Install the BMC for Teensy boards

The BMC for Teensy boards are identical to the boards from teensy, they are a reference to the Teensy installation and require you to have teensyduino installed. These boards can only be used with BMC since they will require your sketches to have a config.h file in the sketch's folder, otherwise they will not compile.

On Arduino open **Preferences**, at the bottom of the preferences window you will see **Additional Boards Manager URLs** next to it a text field and next to the text field a button, click that button to open a list of your board manager's urls, there add a new line and copy and paste the url below:

https://raw.githubusercontent.com/neroroxxx/package_badassmidi_index/master/package_badassmidi_index.json

Click Ok and close the Arduino Preferences.

Next go to the Arduino **Tools** menu and select **Board** > **Boards Manager**, in the search field type "BMC for Teensy" and click install.

For more visual instructions of this step visit [https://support.arduino.cc/hc/en-us/articles/360016466340-Add-or-remove-third-party-boards-in-Boards-Manager](https://support.arduino.cc/hc/en-us/articles/360016466340-Add-or-remove-third-party-boards-in-Boards-Manager)


#### Step 2: Install the BMC Library
To Install the library on the Arduino menu go to **Tools** > **Manage Libraries...** and search for BMC, select the latest Version and click Install.

***Note:*** if you are planning on using the nRF8001 for BLE MIDI then you will also need to download the BLEPeripheral library, however you must use this forked version as it's modified to work with BMC and newer Teensy boards [https://github.com/neroroxxx/arduino-BLEPeripheral](https://github.com/neroroxxx/arduino-BLEPeripheral)

#### Step 3
Relaunch Arduino. Create a new sketch in your projects folder and start creating your config file with the Editor App at [https://www.roxxxtar.com/bmc](https://www.roxxxtar.com/bmc) *(make sure you set it to DEBUG so you can see helpful info on the Serial Monitor and to make sure you've set things up properly)*, once you have your config file save it to that new sketch's folder and make sure it's named **config.h**

You can also open one of the BMC Examples and try them, in which case you don't have to write any code. *Just keep in mind that if you use an example with Pots then you must have a Pot wired otherwise the pin will be left floating and constantly send random readings*

#### Step 5
Once it's all done go to **Tools** > **Board** and now you will see **BMC**, select your BMC Compatible Teensy Board.
When you use these boards the USB Types menu will only allow USB MIDI types since USB MIDI is required for BMC.

If you created a new sketch you can replace all the default code with:

```c++
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
}
void loop(){
  bmc.update();
}
```
#### Step 6
Open the Serial Monitor on Arduino and Upload your sketch, you will start seeing messages on the Serial Monitor as soon as the Sketch starts running.

Once you are happy with your build and you are ready to take it to a stage you can disable DEBUG either by opening your config file with the Editor App or just by removing **#define BMC_DEBUG** from your config file.
