#include "config.h"


void pinInit(void)
{
  pinMode(PARKING_SEN_1, INPUT_PULLUP);
  pinMode(PARKING_SEN_2, INPUT_PULLUP);
  pinMode(PARKING_SEN_3, INPUT_PULLUP);
  // pinMode(ENTRY_SEN_START, INPUT);
  // pinMode(ENTRY_SEN_END, INPUT);
  // pinMode(EXIT_SEN_START, INPUT);
  // pinMode(EXIT_SEN_END, INPUT);
  // pinMode(LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED_ENTRY, OUTPUT);
  pinMode(GREEN_LED_ENTRY, OUTPUT);
  pinMode(RED_LED_PARKING, OUTPUT);
  pinMode(GREEN_LED_PARKING, OUTPUT);
}


void ledOnOff(bool state)
{
  digitalWrite(LED, state);
}