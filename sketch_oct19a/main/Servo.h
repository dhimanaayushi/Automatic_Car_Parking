#ifndef __SERVO_H__
#define __SERVO_H__


#include <Servo.h>
#include "config.h"

typedef enum
{
  eServo_init,
  eServo_idle,
  eServo_low_bal,
  eServo_access_den ,
  eServo_access_granted ,
  eServo_insuf_bal ,
  eServo_total_state
}servoState;



typedef enum
{
  eServoEE_open,
  eServoEE_close
}servoEntryExitCommand;





void servoInit(void);
void setServoState(servoState eState);
void controlGate(servoEntryExitCommand command);

#endif
