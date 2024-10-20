#ifndef __SENSORS_H__
#define __SENSORS_H__
/////////////////// Functions Declarations ///////////////////
void updateParkingAvailability(void);
uint8_t getParkingSpaceValue(void);

bool readEntrySensStart(void);
bool readEntrySensEnd(void);
bool readExitSensStart(void);
bool readExitSensEnd(void);
//////////////////////////////////////////////////////////////


#endif