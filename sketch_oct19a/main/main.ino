#include "config.h"
#include "Sensors.h"
#include "Servo.h"
#include "Rfid.h"

rfidTag_sType data;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinInit();
  servoInit();
  rfidInit();
  
  //digitalWrite(ORANGE_LED, HIGH);
}

void loop() 
{


    updateParkingAvailability();
    sTagState_eType eTagState;
    scanRfidTag();
    eTagState = getTagAuthState();
    bool isParkingAvailable = false;
    if (getParkingSpaceValue() != 0)
    {
      digitalWrite(GREEN_LED_PARKING, HIGH);
      digitalWrite(RED_LED_PARKING, LOW);
      isParkingAvailable = true;
    }
    else 
    {
      digitalWrite(GREEN_LED_PARKING, LOW);
      digitalWrite(RED_LED_PARKING, HIGH);
      isParkingAvailable = false;
    }

    switch(eTagState)
    {
      case eTagIdle:
        break;

      case eTagUnauthorized :
        for (byte i= 0 ; i < 8; i++)
        {
          digitalWrite(BUZZER, HIGH);
          digitalWrite(RED_LED_ENTRY, HIGH);
          delay(200);
          digitalWrite(BUZZER, LOW);
          digitalWrite(RED_LED_ENTRY, LOW);
          delay(200);
          
        }
        setTagAuthState(eTagIdle);
        break;

      case eTagAuthorized :
        //authorizationProcess();
        if (isParkingAvailable != false)
        {
        digitalWrite(GREEN_LED_ENTRY, HIGH);
        controlGate(eServoEE_open);
        delay(4000);
        digitalWrite(GREEN_LED_ENTRY, LOW);
        controlGate(eServoEE_close);
        
        }
        else
        {
          for (byte i =0; i < 4 ; i++)
          {
            digitalWrite(RED_LED_ENTRY, HIGH);
            delay(200);
            digitalWrite(RED_LED_ENTRY, LOW);
            delay(200);
          }
        }
        setTagAuthState(eTagIdle);
        break;

    }

}
