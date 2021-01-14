*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

* [Example of usage](#print-the-page-number-and-name-when-a-page-changes)

# Callbacks
The BMC API has a **TON** of callbacks, for those who are not familiar, a callback is a function that is triggered when a specific action has taken place, for example you can think of it as a notification, when something you are interested in happens in BMC, BMC will notify the sketch that it has happened.

A good example of usage is with pages, BMC can notify your sketch when a page has changed, this is very useful if you want to display the current page or the name of your page in an LCD display (or any type of display), you can also use the current page to add additional functionality to your hardware.

the idea is that you don't have to constantly use the `.getPage()` which returns the current page, instead you are always notified that a page changed has occured only when it occurs.

**Note:** due to the large number of callbacks available in BMC, it's very difficult to list them all, use this as an example but refer to the *src/BMC-API.h* file in the library and look thru it for Callbacks, also documention for things like buttons/leds/etc have examples of the callbacks available to them.

### Print the page number and name when a page changes
```c++
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
  // always set callbacks after the .begin() method inside the setup() function of your sketch
  bmc.onPageChange(myPageChangeFunction);
}
// declare the callback, evey callback has specific parameters that you must assign
void myPageChangeFunction(uint8_t t_page){
  Serial.println("*******");
  Serial.print("The current page has changed, now we are on page: ");
  Serial.println(i);
  // print the page name only if you have page names compiled
#if BMC_NAME_LEN_PAGES > 0
  char str[BMC_NAME_LEN_PAGES];
  bmc.getPageName(str);
  Serial.print("Current Page Name: ");
  Serial.println(str);
#endif
  Serial.println("*******");
}
void loop(){
  bmc.update();
}
```
