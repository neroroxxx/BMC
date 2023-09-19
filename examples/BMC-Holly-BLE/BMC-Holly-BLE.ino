#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
}
void loop(){
  bmc.update();
}
