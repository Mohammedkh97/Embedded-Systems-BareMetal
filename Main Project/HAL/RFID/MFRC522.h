/*
* MFRC255.h
*
* Created: 7/14/2024 10:25:38 AM
*  Author: Mohammed Khalaf
*/


#ifndef MFRC255_H_
#define MFRC255_H_

#include "MFRC522_Registers.h"

typedef enum {
	STATUS_OK				,	// Success
	STATUS_ERROR			,	// Error in communication
	STATUS_COLLISION		,	// Collission detected
	STATUS_TIMEOUT			,	// Timeout in communication.
	STATUS_NO_ROOM			,	// A buffer is not big enough.
	STATUS_INTERNAL_ERROR	,	// Internal error in the code. Should not happen ;-)
	STATUS_INVALID			,	// Invalid argument.
	STATUS_CRC_WRONG		,	// The CRC_A does not match
	STATUS_MIFARE_NACK		= 0xff	// A MIFARE PICC responded with NAK.
}StatusCode_t;

// Constants for the MFRC522 communication
// #define MI_NOTAGERR           0
// #define MI_OK                 1
// #define MI_ERR                0

typedef enum 
{	
	CARD_ERROR,
	CARD_OK
}CardStatus_t;

/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////


/**
 * Writes a byte to the specified register in the MFRC522 chip.
 * The interface is described in the datasheet section 8.1.2.
 */

/************************************************************************/
/*								Prototypes                              */
/************************************************************************/
void MFRC522_Init();
void MFRC522_Reset();
void MFRC522_WriteRegister(MFRC522_Register_t reg, u8 value);
u8	 MFRC522_ReadRegister(MFRC522_Register_t reg);
void MFRC522_ReadRegisterMulti(MFRC522_Register_t reg, u8 count, u8 *values , u8 rxAlign);
void MFRC522_SetBitMask(MFRC522_Register_t reg, u8 mask);
void MFRC522_ClearBitMask(MFRC522_Register_t reg, u8 mask);
void MFRC522_AntennaOn();
void MFRC522_calculateCRC(u8 *data, u8 length,u8 *result);
CardStatus_t MFRC522_Check(u8* id);
CardStatus_t MFRC522_Request(u8 reqMode, u8* TagType);
CardStatus_t MFRC522_ToCard(u8 command, u8* sendData, u8 sendLen, u8* backData, u16* backLen);
CardStatus_t MFRC522_Anticoll(u8* serNum);
void MFRC522_Halt(void);

u8 MFRC522_PerformSelfTest();
void MFRC522_DumpVersionToSerial();


#endif /* MFRC255_H_ */
