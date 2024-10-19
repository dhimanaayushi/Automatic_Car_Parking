#include "config.h"


void pinInit(void)
{
  pinMode(PARKING_SEN_1, INPUT);
  pinMode(PARKING_SEN_2, INPUT);
  pinMode(PARKING_SEN_3, INPUT);
  pinMode(ENTRY_SEN_START, INPUT);
  pinMode(ENTRY_SEN_END, INPUT);
  pinMode(EXIT_SEN_START, INPUT);
  pinMode(EXIT_SEN_END, INPUT);
  pinMode(LED, OUTPUT);
}


void ledOnOff(bool state)
{
  digitalWrite(LED, state);
}