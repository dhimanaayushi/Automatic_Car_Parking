#include "Arduino.h"
#include "HardwareSerial.h"
/**
 * ----------------------------------------------------------------------------
 * This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
 * for further details and other examples.
 *
 * NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
 *
 * Released into the public domain.
 * ----------------------------------------------------------------------------
 * This sample shows how to read and write data blocks on a MIFARE Classic PICC
 * (= card/tag).
 *
 * BEWARE: Data will be written to the PICC, in sector #1 (blocks #4 to #7).
 *
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 *
 */
#include "Rfid.h"

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;
unsigned char tempReadTag[10];
unsigned char tempReadBlock[16];

void writeToCard(byte *data);
const unsigned char authoCardIds[3][4] =
                                    {
                                      {0x93, 0x46, 0x0A, 0xDA},
                                      {0x3C, 0x1B, 0x32, 0x02},
                                      {0x84, 0xE5, 0x33, 0x02}
                                    };

static uint8_t cardIndex = 5u ;
rfidTag_sType sRfidData;

// variable for 3 authorizedcard to hold data
static sTagData_sType cards[3] = 
                                  {
                                      {
                                        {0xFF, 0xFF, 0xFF, 0xFF},
                                        eTagInit,
                                        2000u
                                      },
                                      {
                                        {0xFF, 0xFF, 0xFF, 0xFF},
                                        eTagInit,
                                        2000u
                                      },
                                      {
                                        {0xFF, 0xFF, 0xFF, 0xFF},
                                        eTagInit,
                                        2000u
                                      }
                                      
                                  };



void printCardData(void)
{
  for (byte i = 0 ; i < 3; i++)
  {
    Serial.println(cards[i].tagId[0], HEX);
    Serial.println(cards[i].tagId[1], HEX);
    Serial.println(cards[i].tagId[2], HEX);
    Serial.println(cards[i].tagId[3], HEX);
    Serial.println(cards[i].eTagEE);
    Serial.println(cards[i].balance);
    Serial.println();
  }
}

static sTagState_eType eTagAuthState = eTagIdle ;

sTagState_eType getTagAuthState(void)
{
  return eTagAuthState;
}


void setTagAuthState(sTagState_eType eState)
{
  eTagAuthState = eState ; 
}


static void copyTagId(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++) 
  {
    tempReadTag[i] = buffer[i];
  }
}

static readDataFromBlock(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++) 
  {
        tempReadBlock[i] = buffer[i];
    }
}

static void tagAuthorizationCheck(void)
{
  eTagAuthState = eTagIdle; 
  rfidTag_sType cardId = readTagId();
  byte *ptrData = (byte *)&cardId;

  for (byte i = 0; i < 3; i++)
  {
    if ( (ptrData[0] == authoCardIds[i][0] ) && (ptrData[1] == authoCardIds[i][1] ) && (ptrData[2] == authoCardIds[i][2] ) && (ptrData[3] == authoCardIds[i][3] )  )
    {
      eTagAuthState = eTagAuthorized ;
      cardIndex = i;
      break;
    }
    else 
    {
      eTagAuthState = eTagUnauthorized ;
    }
    
  }

}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) 
{
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

rfidTag_sType readTagId(void)
{
  rfidTag_sType temp;
  temp.data_0 = tempReadTag[0];
  temp.data_1 = tempReadTag[1];
  temp.data_2 = tempReadTag[2];
  temp.data_3 = tempReadTag[3];
  
  return temp;
}


void rfidInit(void)
{
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
    Serial.print(F("Using key (for A and B):"));
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();

    Serial.println(F("BEWARE: Data will be written to the PICC, in sector #1"));

}



void scanRfidTag(void)
{
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

    copyTagId(mfrc522.uid.uidByte, mfrc522.uid.size);
    tagAuthorizationCheck();
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }

    // In this sample we use the second sector,
    // that is: sector #1, covering block #4 up to and including block #7
    byte sector         = 1;
    byte blockAddr      = 4;
    byte dataBlock[]    = {
        0x51, 0x22, 0x43, 0x74, //  1,  2,   3,  4,
        0x55, 0x26, 0x47, 0x78, //  5,  6,   7,  8,
        0x59, 0x2a, 0x4f, 0x7b, //  9, 10, 255, 11,
        0x5c, 0x2d, 0x4e, 0x7f  // 12, 13, 14, 15
    };
    byte trailerBlock   = 7;
    MFRC522::StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);

    // Authenticate using key A
    Serial.println(F("Authenticating using key A..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Show the whole sector as it currently is
    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    // Read data from the block
    Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); 
    readDataFromBlock(buffer, 16); 
    Serial.println();
    Serial.println();

    #if 0

    // Authenticate using key B
    Serial.println(F("Authenticating again using key B..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Write data to the block
    Serial.print(F("Writing data into block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    dump_byte_array(dataBlock, 16); Serial.println();
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.println();

    // Read data from the block (again, should now be what we have written)
    Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();

    // Check that data in block is what we have written
    // by counting the number of bytes that are equal
    Serial.println(F("Checking result..."));
    byte count = 0;
    for (byte i = 0; i < 16; i++) {
        // Compare buffer (= what we've read) with dataBlock (= what we've written)
        if (buffer[i] == dataBlock[i])
            count++;
    }
    Serial.print(F("Number of bytes that match = ")); Serial.println(count);
    if (count == 16) {
        Serial.println(F("Success :-)"));
    } else {
        Serial.println(F("Failure, no match :-("));
        Serial.println(F("  perhaps the write didn't work properly..."));
    }
    Serial.println();

    #endif
    // Dump the sector data
    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
    
}

void authorizationProcess(void)
{
  Serial.println("card index : ");
  Serial.println(cardIndex);

  eTagEnrtyExit_eType temp = cards[cardIndex].eTagEE;

  switch(temp)
  {
    case eTagInit:
      {
        Serial.println("Idle");
        
      }

    case eTagEntry :
      {
        cards[cardIndex].eTagEE = eTagEntry ;
        Serial.println("entry");
        break;
      }

    case EtagExit :
      {
        cards[cardIndex].eTagEE = eTagInit ;
        Serial.println("exit");
        break;
      }

    default :
      break;

  }

  // if (cards[cardIndex].balance >=100 )
  // {
  //   cards[cardIndex].balance -= 100u ;
  //   cards[cardIndex].eTagEE = eTagEntry;
  // }
  // else
  // {

  // }

  cardIndex = 5u;
}

