#include "HardwareSerial.h"
#include "config.h"
#include <stdint.h>

static uint8_t parkingSpaceCount = 3u ;

////////////////////////////// static function declaration //////////////////////////////////
static bool readParkingSensor1(void);
static bool readParkingSensor2(void);
static bool readParkingSensor3(void);
/////////////////////////////////////////////////////////////////////////////////////////////


static bool readParkingSensor1(void)
{
  return digitalRead(PARKING_SEN_1);
  //return (bool)OBJECT_DETECTED;
}


static bool readParkingSensor2(void)
{
  return digitalRead(PARKING_SEN_2);
  //return (bool)OBJECT_DETECTED;
}


static bool readParkingSensor3(void)
{
  return digitalRead(PARKING_SEN_3);
  //return (bool)OBJECT_DETECTED;
}


void updateParkingAvailability(void)
{
  static bool sens1Flag = false;
  static bool sens2Flag = false;
  static bool sens3Flag = false;
  
  if ( (readParkingSensor1() == OBJECT_DETECTED) && (sens1Flag == false) )
  {
    parkingSpaceCount--;
    sens1Flag = true;
    Serial.println({"sensor1 working"});
  }
  else if ( (readParkingSensor1() == OBJECT_NOT_DETECTED) && (sens1Flag == true) )
  {
    parkingSpaceCount++;
    sens1Flag = false;
    Serial.println({"sensor1 not working"});
  }
  else
  {
    // Eat ***** do nothing
  }

  if ((readParkingSensor2() == OBJECT_DETECTED) && (sens2Flag == false))
  {
    parkingSpaceCount--;
    sens2Flag = true;
       Serial.println({"sensor2 working"});
  }
  else if ( (readParkingSensor2() == OBJECT_NOT_DETECTED) && (sens2Flag == true) )
  {
    parkingSpaceCount++;
    sens2Flag = false;
     Serial.println({"sensor2 not working"});
  }
  else
  {
    // Eat ***** do nothing
  }

  if ((readParkingSensor3() == OBJECT_DETECTED) && (sens3Flag == false))
  {
    parkingSpaceCount--;
    sens3Flag = true;
      Serial.println({"sensor3 working"});
  }
  else if ( (readParkingSensor3() == OBJECT_NOT_DETECTED) && (sens3Flag == true) )
  {
    parkingSpaceCount++;
    sens3Flag = false;
    Serial.println({"sensor3 not working"});
  }
  else
  {
    // Eat ***** do nothing
  }

}


uint8_t getParkingSpaceValue(void)
{
  return parkingSpaceCount;
}

bool readEntrySensStart(void)
{
  return digitalRead(ENTRY_SEN_START);
}

bool readEntrySensEnd(void)
{
  return digitalRead(ENTRY_SEN_END);
}

bool readExitSensStart(void)
{
  return digitalRead(EXIT_SEN_START);
}

bool readExitSensEnd(void)
{
  return digitalRead(EXIT_SEN_END);
}


