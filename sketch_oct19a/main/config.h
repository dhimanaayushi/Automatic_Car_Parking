#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>

#define LED                   13
#define LED_ON                HIGH
#define LED_OFF               LOW
#define OBJECT_DETECTED       LOW
#define OBJECT_NOT_DETECTED   HIGH

#define BUZZER                19
#define RED_LED_PARKING       18
#define GREEN_LED_PARKING     17
#define RED_LED_ENTRY         16
#define GREEN_LED_ENTRY       15


// Sensors 
#define PARKING_SEN_1         3
#define PARKING_SEN_2         4
#define PARKING_SEN_3         5
#define ENTRY_SEN_START       3
#define ENTRY_SEN_END         4
#define EXIT_SEN_START        5
#define EXIT_SEN_END          6



/////////////////// Functions Declarations ///////////////////
void pinInit(void);
void ledOnOff(bool state);
//////////////////////////////////////////////////////////////


#endif
