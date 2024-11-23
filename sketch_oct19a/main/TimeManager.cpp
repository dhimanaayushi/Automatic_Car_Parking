#include "Arduino.h"
#include "TimeManager.h"

static uint32_t _timeStamp = 0u ; 


void timeManageInit()
{
  _timeStamp = millis();
}