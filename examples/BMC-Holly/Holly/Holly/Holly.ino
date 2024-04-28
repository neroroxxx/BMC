// * This sketch is specific to the BMC Holly
// * It requires external hardware, if you compile it
// * and upload it to your teensy, BMC stop running
// * because this config file requires EEPROM and displays

#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
}
void loop(){
  bmc.update();
}
