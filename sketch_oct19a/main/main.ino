#include "config.h"
#include "Sensors.h"
#include "Servo.h"
#include "Rfid.h"

rfidTag_sType data;



void setup() {
  // put your setup code here, to run once:
  pinInit();
  //servoInit();
  rfidInit();
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);

}

void loop() {
    sTagState_eType eTagState;
    scanRfidTag();
    eTagState = getTagAuthState();

    switch(eTagState)
    {
      case eTagIdle:
        break;

      case eTagUnauthorized :
        for (byte i= 0 ; i < 10; i++)
        {
          digitalWrite(BUZZER, HIGH);
          delay(200);
          digitalWrite(BUZZER, lowByte(LOW));
          delay(200);
          
        }
        setTagAuthState(eTagIdle);
        break;

      case eTagAuthorized :
        break;

    }


   

}
