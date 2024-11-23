#include "Servo.h"

// Servo motors
#define SERVO_MOTOR_ENTRY_EXIT              2     
#define SERVO_MOTOR_STATE                   3    


#define SERVO_IDLE                          90u
#define SERVO_LOW_BALANCE                   0u
#define SERVO_ACCESS_DENIED                 45u
#define SERVO_ACCESS_GRANTED                135u
#define SERVO_INSUFFICIENT_BAL              180u

#define SERVO_EE_CLOSE                      0u
#define SERVO_EE_OPEN                       90u

/// created 2 object for 2 servo motor 
Servo servoEntryExit;
Servo servoStateDisplay;


void servoInit(void)
{
  servoEntryExit.attach(SERVO_MOTOR_ENTRY_EXIT);
  servoStateDisplay.attach(SERVO_MOTOR_STATE);

  servoEntryExit.write(0);
  servoStateDisplay.write(0);
}


void setServoState(servoState eState)
{

  switch(eState)
  {
    case eServo_idle:
    {
      servoStateDisplay.write(SERVO_IDLE);
      break;
    }

    case eServo_access_granted:
    {
      servoStateDisplay.write(SERVO_ACCESS_GRANTED);
      break;
    }

    case eServo_access_den:
    {
      servoStateDisplay.write(SERVO_ACCESS_DENIED);
      break;
    }

    case eServo_low_bal:
    {
      servoStateDisplay.write(SERVO_LOW_BALANCE);
      break;
    }

    case eServo_insuf_bal:
    {
      servoStateDisplay.write(SERVO_INSUFFICIENT_BAL);
      break;
    }

    default :
      break;
  }
}


void controlGate(servoEntryExitCommand command)
{
  switch(command)
  {
    case eServoEE_open :
      {
        servoEntryExit.write(SERVO_EE_OPEN);
        break;
      }

      case eServoEE_close :
      {
        servoEntryExit.write(SERVO_EE_CLOSE);
        break;
      }

      default:
      {
        break;
      }

  }
}



