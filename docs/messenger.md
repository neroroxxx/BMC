*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Messenger
The Messenger is a simple utility that lets you send/receive a string and an int to/from the Editor app.

This feature is great for debugging or if you want to retrieve data from your build that is not part of the **Store**

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// with the Messenger you can send a signed long value and a char array
// the string can only be up to 32 characters
// send a value and a string as a char array
void messengerSend(uint16_t status, signed long value, char* str, uint8_t len);

// send a value and a string as a const string
void messengerSend(uint16_t status, signed long value, const char* str);

// send just a value without string
void messengerSend(uint16_t status, signed long value);

// send just a char array string
void messengerSend(uint16_t status, char* str, uint8_t len);

// send just a const string
void messengerSend(uint16_t status, const char* str);
```

##### CALLBACKS
```c++
// triggered when a Messenger message is received from the Editor App.
void onMessenger(void (*fptr)(BMCMessenger t_messenger));
```

The `onMessenger` callback will carry a struct of `BMCMessenger` type, this struct has the following variables:

```c++
uint16_t status = 0;
signed long value = 0;
uint8_t strLen = 0;
char string[33];
```
