#include "config.h"
#include "Sensors.h"
#include "Servo.h"

uint16_t pos = 0u;
Servo servoEntry1;
void setup() {
  // put your setup code here, to run once:
  //pinInit();
  servoInit();
  Serial.begin(9600);
  //servoEntry1.attach(8);
  //servoEntry1.write(20);
}

void loop() {
    
    setServoState(eServo_idle);
    delay(2000);
    setServoState(eServo_access_den);
    delay(2000);
    controlGate(eServoEE_open);
    delay(2000);
    controlGate(eServoEE_close);
    delay(2000);
    //servoEntry1.write(pos);
    
    //pos++;
}
