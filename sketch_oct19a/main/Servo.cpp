#include "Servo.h"


/// created 2 object for 2 servo motor 
Servo servoEntry;
Servo servoExit;


void servoInit(void)
{
  servoEntry.attach(SERVO_MOTOR_ENTRY);
  servoExit.attach(SERVO_MOTOR_EXIT);

  servoEntry.write(0);
  servoExit.write(0);
  
}



