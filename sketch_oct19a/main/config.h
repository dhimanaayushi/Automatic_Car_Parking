#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>

#define LED                   13
#define LED_ON                HIGH
#define LED_OFF               LOW
#define OBJECT_DETECTED       LOW
#define OBJECT_NOT_DETECTED   HIGH


// Sensors 
#define PARKING_SEN_1         0
#define PARKING_SEN_2         1
#define PARKING_SEN_3         2
#define ENTRY_SEN_START       3
#define ENTRY_SEN_END         4
#define EXIT_SEN_START        5
#define EXIT_SEN_END          6



/////////////////// Functions Declarations ///////////////////
void pinInit(void);
void ledOnOff(bool state);
//////////////////////////////////////////////////////////////


#endif
