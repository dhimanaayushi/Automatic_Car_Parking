#include "config.h"
#include <stdint.h>
static uint8_t parkingSpaceCount = 3 ;

////////////////////////////// static function declaration //////////////////////////////////
static bool readParkingSensor1(void);
static bool readParkingSensor2(void);
static bool readParkingSensor3(void);
/////////////////////////////////////////////////////////////////////////////////////////////


static bool readParkingSensor1(void)
{
  return digitalRead(PARKING_SEN_1);
}


static bool readParkingSensor2(void)
{
  return digitalRead(PARKING_SEN_2);
}


static bool readParkingSensor3(void)
{
  return digitalRead(PARKING_SEN_3);
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
  }
  else
  {
    parkingSpaceCount++;
    sens1Flag = false;
  }

  if ((readParkingSensor2() == OBJECT_DETECTED) && (sens2Flag == false))
  {
    parkingSpaceCount--;
    sens2Flag = true;
  }
  else
  {
    parkingSpaceCount++;
    sens2Flag = false;
  }

  if ((readParkingSensor3() == OBJECT_DETECTED) && (sens3Flag == false))
  {
    parkingSpaceCount--;
    sens3Flag = true;
  }
  else
  {
    parkingSpaceCount++;
    sens3Flag = false;
  }

}


uint8_t getParkingSpaceValue(void)
{
  return parkingSpaceCount;
}