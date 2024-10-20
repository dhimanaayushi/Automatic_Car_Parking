#include "config.h"
#include "Sensors.h"
#include "Servo.h"

void setup() {
  // put your setup code here, to run once:
  pinInit();
  servoInit();
  Serial.begin(9600);
}

void loop() {
    
    
    updateParkingAvailability();
    delay(1000);
}
