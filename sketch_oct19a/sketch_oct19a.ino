#include "config.h"
#include "Sensors.h"
#include "Servo.h"

void setup() {
  // put your setup code here, to run once:
  pinInit();
  servoInit();
  
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
