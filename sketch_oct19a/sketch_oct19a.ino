#include "config.h"
#include "Sensors.h"

void setup() {
  // put your setup code here, to run once:
  pinInit();
  
  
}

void loop() {
  
  if (readParkingSensor1() == OBJECT_DETECTED)
  {
    ledOnOff(LED_ON);
  }
  else
  {
    ledOnOff(LED_OFF);
  }
  
}
