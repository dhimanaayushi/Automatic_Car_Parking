#include "config.h"

bool readParkingSensor1(void)
{
  bool temp;
  temp = digitalRead(PARKING_SEN_1);
  return temp;
}


bool readParkingSensor2(void)
{
  bool temp;
  temp = digitalRead(PARKING_SEN_2);
  return temp;
}


bool readParkingSensor3(void)
{
  bool temp;
  temp = digitalRead(PARKING_SEN_3);
  return temp;
}