*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# SetLists
BMC has SetLists which are a collection of Songs, you can up to 32 SetLists and each SetList can have up to 32 songs.

SetLists are meant to be a better way to organize your presets for live shows.

## Songs
Songs are pointers to BMC Presets, you can have up to 32 Songs in a SetList and each song ties directly to a BMC Preset.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// get the name of the current setlist
void getSetListName(char* t_string);

// get the name of a specific setlist
void getSetListName(uint8_t n, char* t_string);

// get the name of the current song in the current setlist
void getSetListSongName(char* t_string);

// get the name of a specific song in the current setlist
void getSetListSongName(uint8_t n, char* t_string);

// get the current SetList number
uint8_t getSetList();

// get the number of songs in the current setlist
uint8_t getSetListLength();

// get the number of songs in the specified setlist
uint8_t getSetListLength(uint8_t n);

// go to a specific SetList
void setSetList(uint8_t n);

// go to next song in the list
// @endless if true, after reaching the last setlist
// the next setlist will be the first setlist
// otherwise once the last setlist is reached BMC will
// ignore this function
void setListUp(bool endless);

// go to the previous setlist
// @endless if true, after reaching the first setlist
// the previous setlist will be the last setlist
// otherwise once the first setlist is reached BMC will
// ignore this function
void setListDown(bool endless);

// get the current song number in the setlist
uint8_t getSetListSong();

// go to a specific song number in the setlist
void setSetListSong(uint8_t n);

// go to next song in the list
// @endless if true, after reaching the last song
// the next song will be the first song
// otherwise once the last song is reached BMC will
// ignore this function
void setListSongUp(bool endless);

// go to previous song in the list
// @endless if true, after reaching the first song
// the previous song will be the last song
// otherwise once the first song is reached BMC will
// ignore this function
void setListSongDown(bool endless);

// swap songs inside setlists, returns true if successful, automatically saves
// to EEPROM
// @s = setlist index
// @a = song to swap
// @b = song to swap
bool setListSwapSong(uint8_t s, uint8_t a, uint8_t b);

// move a song to new position and shift all songs after the new position
// to the next position, useful to rearrange songs in setlists. returns true
// if successful, automatically saves to EEPROM
// @s = setlist index
// @n = song index
// @newPost = new song position
bool setListShiftSong(uint8_t s, uint8_t n, uint8_t newPos);
```

##### CALLBACKS

```c++
// triggered when the current BMC SetList has changed
void onSetListChange(void (*fptr)(uint8_t n));

// triggered when the current BMC SetList Song has changed
void onSetListSongChange(void (*fptr)(uint8_t n));
```
