#ifndef __RFID_H__
#define __RFID_H__

#include <stdint.h>
#include <Arduino.h>

typedef struct
{
  byte data_0;
  byte data_1;
  byte data_2;
  byte data_3;
}rfidTag_sType;

typedef enum
{
  eTagIdle,
  eTagAuthorized,
  eTagUnauthorized
}sTagState_eType;




void rfidInit(void);
void scanRfidTag(void);
rfidTag_sType readTagId(void);
void readTagSector(void);

sTagState_eType getTagAuthState(void);
void setTagAuthState(sTagState_eType eState);




#endif