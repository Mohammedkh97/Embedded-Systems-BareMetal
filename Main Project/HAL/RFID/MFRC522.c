/*
 * MFRC255.c
 *
 * Created: 7/14/2024 11:15:13 AM
 *  Author: Mohammed Khalaf
 */
#include "stdio.h"
#include "stdTypes.h"
#include "MFRC522.h"
#include "SPI_Interface.h"
#include "GPIO_MemoryMap.h"
#include "GPIO_Interface.h"
#include "GPIO_Private.h"
#include "GLCD_ST7920/GLCD_ST7920_Interface.h"
#include "MFRC522_Commands.h"
#include "MFRC522_Registers.h"
#include "MFRC522_Config.h"
#include "SPI.h"
#include "delay.h"
#include "BitwiseOperations_LIB.h"
#include "GLCD_ST7920_Interface.h"
//Clones:

// Fudan Semiconductor FM17522 (0x88)
u8 FM17522_firmware_reference[] =
{ 0x00, 0xD6, 0x78, 0x8C, 0xE2, 0xAA, 0x0C, 0x18, 0x2A, 0xB8, 0x7A, 0x7F, 0xD3,
		0x6A, 0xCF, 0x0B, 0xB1, 0x37, 0x63, 0x4B, 0x69, 0xAE, 0x91, 0xC7, 0xC3,
		0x97, 0xAE, 0x77, 0xF4, 0x37, 0xD7, 0x9B, 0x7C, 0xF5, 0x3C, 0x11, 0x8F,
		0x15, 0xC3, 0xD7, 0xC1, 0x5B, 0x00, 0x2A, 0xD0, 0x75, 0xDE, 0x9E, 0x51,
		0x64, 0xAB, 0x3E, 0xE9, 0x15, 0xB5, 0xAB, 0x56, 0x9A, 0x98, 0x82, 0x26,
		0xEA, 0x2A, 0x62 };

// Version 0.0 (0x90)
// Philips Semiconductors; Preliminary Specification Revision 2.0 - 01 August 2005; 16.1 self-test
u8 MFRC522_firmware_referenceV0_0[] =
{ 0x00, 0x87, 0x98, 0x0f, 0x49, 0xFF, 0x07, 0x19, 0xBF, 0x22, 0x30, 0x49, 0x59,
		0x63, 0xAD, 0xCA, 0x7F, 0xE3, 0x4E, 0x03, 0x5C, 0x4E, 0x49, 0x50, 0x47,
		0x9A, 0x37, 0x61, 0xE7, 0xE2, 0xC6, 0x2E, 0x75, 0x5A, 0xED, 0x04, 0x3D,
		0x02, 0x4B, 0x78, 0x32, 0xFF, 0x58, 0x3B, 0x7C, 0xE9, 0x00, 0x94, 0xB4,
		0x4A, 0x59, 0x5B, 0xFD, 0xC9, 0x29, 0xDF, 0x35, 0x96, 0x98, 0x9E, 0x4F,
		0x30, 0x32, 0x8D };
// Version 1.0 (0x91)
// NXP Semiconductors; Rev. 3.8 - 17 September 2014; 16.1.1 self-test
u8 MFRC522_firmware_referenceV1_0[] =
{ 0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C, 0xC2, 0xD8, 0x7C, 0x4D, 0xD9,
		0x70, 0xC7, 0x73, 0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A, 0x14,
		0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E, 0x64, 0x22, 0x72, 0xB5, 0xBD,
		0x65, 0xF4, 0xEC, 0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41, 0x1F,
		0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02, 0xD9, 0x0F, 0xB5, 0x5E, 0x25,
		0x1D, 0x29, 0x79 };
// Version 2.0 (0x92)
// NXP Semiconductors; Rev. 3.8 - 17 September 2014; 16.1.1 self-test
u8 MFRC522_firmware_referenceV2_0[] =
{ 0x00, 0xEB, 0x66, 0xBA, 0x57, 0xBF, 0x23, 0x95, 0xD0, 0xE3, 0x0D, 0x3D, 0x27,
		0x89, 0x5C, 0xDE, 0x9D, 0x3B, 0xA7, 0x00, 0x21, 0x5B, 0x89, 0x82, 0x51,
		0x3A, 0xEB, 0x02, 0x0C, 0xA5, 0x00, 0x49, 0x7C, 0x84, 0x4D, 0xB3, 0xCC,
		0xD2, 0x1B, 0x81, 0x5D, 0x48, 0x76, 0xD5, 0x71, 0x61, 0x21, 0xA9, 0x86,
		0x96, 0x83, 0x38, 0xCF, 0x9D, 0x5B, 0x6D, 0xDC, 0x15, 0xBA, 0x3E, 0x7D,
		0x95, 0x3B, 0x2F };

/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////

/**
 * Writes a byte to the specified register in the MFRC522 chip.
 * The interface is described in the datasheet section 8.1.2.
 */

void MFRC522_WriteRegister(MFRC522_Register_t reg, u8 value)
{
	// Select the RC522
	GPIO_void_Write_Pin_Method1(ChipSelectPin, LOW);   // Select slave
	// Send address and value
//	SPI_sendReceiveByte((reg << 1) & 0x7E);
//	GLCD_ST7920_SendString(1, 2, (u8*) "Hi");
//	SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, (reg << 1) & 0x7E);
	SPI2_Transfer((reg << 1) & 0x7E);
//	SPI_sendReceiveByte(value);

//	SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, value);
	SPI2_Transfer(value);
	// Deselect the RC522
	GPIO_void_Write_Pin_Method1(ChipSelectPin, HIGH);    // Release slave again
}

void MFRC522_WriteRegisterMulti(MFRC522_Register_t reg, u8 count, u8 *values)
{
//	PORTB &= ~(1 << ChipSelectPin); // Select slave
//	CLEAR_BIT(RFID_PORT, ChipSelectPin);
//	GPIO_Clear_Pin(GPIOB, ChipSelectPin);
	GPIO_void_Write_Pin_Method3(ChipSelectPin, LOW);
//	SPI_sendReceiveByte((reg << 1) & 0x7E); // Send address with write flag (MSB = 0)
//	SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, (reg << 1) & 0x7E);
	SPI2_Transfer((reg << 1) & 0x7E);
	for (u8 index = 0; index < count; index++)
	{
//		SPI_sendReceiveByte(values[index]); // Send the values
//		SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, values[index]);
		SPI2_Transfer(values[index]);
	}
//	PORTB |= (1 << ChipSelectPin); // Release slave

//	SET_BIT(RFID_PORT, ChipSelectPin);	// Release slave
	GPIO_void_Write_Pin_Method3(ChipSelectPin, HIGH);
}

u8 MFRC522_ReadRegister(MFRC522_Register_t reg)
{
	u8 value;
//	DIO_WritePin1(ChipSelectPin , LOW);
//	GPIO_void_Write_Pin_Method1(ChipSelectPin, LOW);
	GPIO_void_Write_Pin_Method3(ChipSelectPin, LOW);
//	SPI_sendReceiveByte(((reg << 1) & 0x7E) | 0x80); // Master Send to RFID
//	SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, ((reg << 1) & 0x7E) | 0x80);	// Master Send to RFID
	SPI2_Transfer(((reg << 1) & 0x7E) | 0x80);
	//SPI_sendReceiveByte(reg | 0x80);

//	value = SPI_sendReceiveByte(0x00); // Master Receive From RFID
//	value = SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, 0x00);
	value = SPI2_Transfer(0x00);
//	DIO_WritePin1(ChipSelectPin, HIGH);
	GPIO_void_Write_Pin_Method1(ChipSelectPin, HIGH);
	return value;
}

void MFRC522_ReadRegisterMulti(MFRC522_Register_t reg, u8 count, u8 *values,
		u8 rxAlign)
{
	if (count == 0)
	{
		return;
	}
	u8 address = 0x80 | reg; // MSB == 1 is for reading. LSB is not used in address.
	u8 index = 0; // Index in values array.
//	CLEAR_BIT(RFID_PORT, ChipSelectPin); // Select slave
	GPIO_void_Write_Pin_Method3(ChipSelectPin, LOW);
	count--; // One read is performed outside of the loop
//	SPI_sendReceiveByte(address); // Tell MFRC522 which address we want to read
//	SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, address);
	SPI2_Transfer(address);
	if (rxAlign)
	{
		// Only update bit positions rxAlign..7 in values[0]
		// Create bit mask for bit positions rxAlign..7
		u8 mask = (0xFF << rxAlign) & 0xFF;
		// Read value and tell that we want to read the same address again.
//		u8 value = SPI_sendReceiveByte(address);
//		u8 value = SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, address);
		u8 value = SPI2_Transfer(address);
		// Apply mask to both current value of values[0] and the new data in value.
		values[0] = (values[0] & ~mask) | (value & mask);
		index++;
	}

	while (index < count)
	{
//		values[index] = SPI_sendReceiveByte(address); // Read value and tell that we want to read the same address again.
//		values[index] = SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, address);
		values[index] = SPI2_Transfer(address);
		index++;
	}
//	values[index] = SPI_sendReceiveByte(0); // Read the final byte. Send 0 to stop reading.
//	values[index] = SPI_u8_Send_Receive_Byte(RFID_SPI_CHANNEL, 0x00); // Read the final byte. Send 0 to stop reading.
	values[index] = SPI2_Transfer(0x00);
//	DIO_WritePin1(ChipSelectPin, HIGH);	 // Release slave
	GPIO_void_Write_Pin_Method1(ChipSelectPin, HIGH);
}

void MFRC522_SetBitMask(MFRC522_Register_t reg, u8 mask)
{
	u8 tmp = MFRC522_ReadRegister(reg);
	MFRC522_WriteRegister(reg, tmp | mask);
}

void MFRC522_ClearBitMask(MFRC522_Register_t reg, u8 mask)
{
	u8 tmp = MFRC522_ReadRegister(reg);
	MFRC522_WriteRegister(reg, tmp & (~mask));
}

void MFRC522_AntennaOn()
{
	u8 value = MFRC522_ReadRegister(TxControlReg);
	if ((value & 0x03) != 0x03)
	{
		MFRC522_SetBitMask(TxControlReg, 0x03);
	}

}
void MFRC522_AntennaOff()
{
	MFRC522_ClearBitMask(TxControlReg, 0X03);
}

void MFRC522_Reset()
{
	MFRC522_WriteRegister(CommandReg, MFRC522_RESETPHASE);
}

void MFRC522_Init()
{
// Note that the status of RFID Pins changes periodically!
	u8 hardReset = 0; //false

// Set the chipSelectPin as digital output, do not select the slave yet
//	DIO_initPin1(ChipSelectPin, OUTPUT);
	GPIO_void_SetPinMode1(ChipSelectPin, DIO_OUTPUT_PUSHPULL_10MHZ);
//	DIO_WritePin1(ChipSelectPin, HIGH);
	GPIO_void_Write_Pin_Method1(ChipSelectPin, HIGH);

// If a valid pin number has been set, pull device out of power down / reset state.
	if (RESET_PIN != UNUSED_PIN)
	{
		// First set the resetPowerDownPin as digital input, to check the MFRC522 power down mode.
		GPIO_void_SetPinMode1(RESET_PIN, DIO_INPUT_FLOATING);

		if (GPIO_DIO_PinVoltage_Read_Pin_Method1(RESET_PIN) == LOW)
		{    // The MFRC522 chip is in power down mode.

			GPIO_void_SetPinMode1(RESET_PIN, DIO_OUTPUT_PUSHPULL_10MHZ); // Now set the resetPowerDownPin as digital output.
			GPIO_void_Write_Pin_Method1(RESET_PIN, LOW); // Make sure we have a clean LOW state.
			delay_us(2); // 8.8.1 Reset timing requirements says about 100ns. Let us be generous: 2?s
			GPIO_void_Write_Pin_Method1(RESET_PIN, HIGH); // Exit power down mode. This triggers a hard reset.
			// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37.74?s. Let us be generous: 50ms.
			delay_ms(50);
			hardReset = 1;  //true
		}
	}

	if (!hardReset)
	{ // Perform a soft reset if we haven't triggered a hard reset above.
		MFRC522_Reset();
	}

	// Initialize the RC522
	MFRC522_WriteRegister(TModeReg, 0x8D);

	MFRC522_WriteRegister(TPrescalerReg, 0x3E);
	MFRC522_WriteRegister(TReloadRegL, 30);
	MFRC522_WriteRegister(TReloadRegH, 0);
	MFRC522_WriteRegister(TxASKReg, 0x40);
	MFRC522_WriteRegister(ModeReg, 0x3D);

	// Reset baud rates
	MFRC522_WriteRegister(TxModeReg, 0x00);
	MFRC522_WriteRegister(RxModeReg, 0x00);

	// Reset ModWidthReg
	MFRC522_WriteRegister(ModWidthReg, 0x26);

	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	MFRC522_WriteRegister(TModeReg, 0x80); // TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	MFRC522_WriteRegister(TPrescalerReg, 0xA9); // TPreScaler = TModeReg[3..0]:TPrescalerReg, i.e., 0x0A9 = 169 => f_timer=40kHz, i.e., a timer period of 25?s.
	MFRC522_WriteRegister(TReloadRegH, 0x03); // Reload timer with 0x3E8 = 1000, i.e., 25ms before timeout.
	MFRC522_WriteRegister(TReloadRegL, 0xE8);

	MFRC522_AntennaOn(); // Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
}

CardStatus_t MFRC522_Check(u8 *id)
{
	CardStatus_t status = CARD_ERROR;
	u8 str[16];
	u8 i;

	status = MFRC522_Request(PICC_REQIDL, str);
	GLCD_ST7920_WriteNumber(3, 0, status, 1);
	if (status == CARD_OK)
	{
		GLCD_ST7920_SendString(3, 0, "Here");
		status = MFRC522_Anticoll(str);

	}

	for (i = 0; i < 5; i++)
	{
		id[i] = str[i];
	}

	MFRC522_Halt();      //Command card into hibernation
	return status;
}

CardStatus_t MFRC522_Request(u8 reqMode, u8 *TagType)
{
	CardStatus_t status = CARD_ERROR;
	u16 backBits;

	MFRC522_WriteRegister(BitFramingReg, 0x07);
	TagType[0] = reqMode;

	status = MFRC522_ToCard(MFRC522_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((status != CARD_OK) || (backBits != 0x10))
	{
		status = CARD_ERROR;
	}

	return status;
}

CardStatus_t MFRC522_ToCard(u8 command, u8 *sendData, u8 sendLen, u8 *backData,
		u16 *backLen)
{

	CardStatus_t status = CARD_ERROR;
	u8 irqEn = 0x00;
	u8 waitIRq = 0x00;
	u8 lastBits;
	u8 n;
	u16 i;

	switch (command)
	{
	case MFRC522_AUTHENT:
	{
		irqEn = 0x12;
		waitIRq = 0x10;
		break;
	}
	case MFRC522_TRANSCEIVE:
	{
		irqEn = 0x77;
		waitIRq = 0x30;
		break;
	}
	default:
		break;
	}
	//Interrupt request
	MFRC522_WriteRegister(ComIEnReg, irqEn | 0x80);
	n = MFRC522_ReadRegister(ComIrqReg);
	//clear all interrupt bits
	MFRC522_ClearBitMask(ComIrqReg, 0x80);

	//flush FIFO data
	//n=MFRC522_ReadRegister(FIFOLevelReg);
	MFRC522_SetBitMask(FIFOLevelReg, 0x80);

	//NO action; Cancel the current cmd
	MFRC522_WriteRegister(CommandReg, MFRC522_IDLE);

	for (i = 0; i < sendLen; i++)
	{
		MFRC522_WriteRegister(FIFODataReg, sendData[i]);
	}
	//Execute the command
	MFRC522_WriteRegister(CommandReg, command);
	if (command == MFRC522_TRANSCEIVE)
	{
		MFRC522_SetBitMask(BitFramingReg, 0x80);
		// 		n=MFRC522(BitFramingReg);
		// 		MFRC522_WriteRegister(BitFramingReg,n|0x80);
	}
	i = 100;
	do
	{
		n = MFRC522_ReadRegister(ComIrqReg);
		i--;
	} while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

	MFRC522_ClearBitMask(BitFramingReg, 0x80);

	if (i != 0)
	{
		//LCD_Goto_WriteString(2,1," Here");
		if (!(MFRC522_ReadRegister(ErrorReg) & 0x1B))
		{
			//LCD_Goto_WriteString(2,1,(u8*)" Here");
			status = CARD_OK;
			if (n & irqEn & 0x01)
			{
				//status = MI_NOTAGERR; //CARD_NOT_FOUND;
				status = CARD_ERROR;  //MI_NOTAGERR
			}

			if (command == MFRC522_TRANSCEIVE)
			{
				n = MFRC522_ReadRegister(FIFOLevelReg);
				u8 l = n;
				lastBits = MFRC522_ReadRegister(ControlReg) & 0x07;
				if (lastBits)
				{
					*backLen = (n - 1) * 8 + lastBits;
				}
				else
				{
					*backLen = n * 8;
				}

				if (n == 0)
				{
					n = 1;
				}
				if (n > 16)
				{
					n = 16;
				}
				//Reading the received data in FIFO
				for (i = 0; i < n; i++)
				{
					u8 d = MFRC522_ReadRegister(FIFODataReg);
					//backData[i] = MFRC522_ReadRegister(FIFODataReg);

					if (l == 4)
						printf("%02x ", d);
					backData[i] = d;

				}
				if (l == 4)
					printf("\r\n");
				return status;

			}
		}
		else
		{
			status = 0;
		}
	}

	return status;
}

CardStatus_t MFRC522_Anticoll(u8 *serNum)
{
	CardStatus_t status;
	u8 i;
	u8 serNumCheck = 0;
	u16 unLen;

	MFRC522_WriteRegister(BitFramingReg, 0x00);

	serNum[0] = PICC_ANTICOLL_CL1;
	serNum[1] = 0x20;
	status = MFRC522_ToCard(MFRC522_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (status == CARD_OK)
	{
		for (i = 0; i < 4; i++)
		{
			serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{
			status = CARD_ERROR;
		}
	}

	return status;
}

void MFRC522_Halt(void)
{
	u16 unLen;
	u8 buff[4];

	buff[0] = PICC_HALT;
	buff[1] = 0;
	MFRC522_calculateCRC(buff, 2, &buff[2]);

	MFRC522_ToCard(MFRC522_TRANSCEIVE, buff, 4, buff, &unLen);
}

u8 MFRC522_PerformSelfTest()
{
	MFRC522_Reset();

	u8 ZEROES[25] =
	{ 0x00 };
	MFRC522_WriteRegister(FIFOLevelReg, 0x80);
	MFRC522_WriteRegisterMulti(FIFODataReg, 25, ZEROES);
	MFRC522_WriteRegister(CommandReg, MFRC522_Mem);

	MFRC522_WriteRegister(AutoTestReg, 0x09);
	MFRC522_WriteRegister(FIFODataReg, 0x00);
	MFRC522_WriteRegister(CommandReg, MFRC522_CALCCRC);

	u8 n;
	for (u8 i = 0; i < 0xFF; i++)
	{
		n = MFRC522_ReadRegister(FIFOLevelReg);
		if (n >= 64)
		{
			break;
		}
	}
	MFRC522_WriteRegister(CommandReg, MFRC522_IDLE);
	u8 result[64];
	MFRC522_ReadRegisterMulti(FIFODataReg, 64, result, 0);
	//debugPrintResults(result);
	MFRC522_WriteRegister(AutoTestReg, 0x00);
	u8 version = MFRC522_ReadRegister(VersionReg);
	const u8 *reference;
	switch (version)
	{
	case 0x88:
		reference = FM17522_firmware_reference;
		break;
	case 0x90:
		reference = MFRC522_firmware_referenceV0_0;
		break;
	case 0x91:
		reference = MFRC522_firmware_referenceV1_0;
		break;
	case 0x92:
		reference = MFRC522_firmware_referenceV2_0;
		break;
	default:
		return 0; // false
	}

	// Verify that the results match up to our expectations
	for (u8 i = 0; i < 64; i++)
	{
		if (result[i] != reference[i])
		{
			//return 0; // false
		}
	}
	MFRC522_Init();
	return 1; // true
}
void MFRC522_DumpVersionToSerial()
{

	u8 v = MFRC522_ReadRegister(VersionReg);
	GLCD_ST7920_Clear();

	GLCD_ST7920_SendString(0, 0, (u8*) "Firmware Version");
	GLCD_ST7920_WriteNumber(1, 0, v, 2);
	switch (v)
	{
	case 0x88:
		GLCD_ST7920_SendString(1, 2, (u8*) " = (clone)");
		break;
	case 0x90:
		GLCD_ST7920_SendString(1, 2, (u8*) " = v0.0");
		break;
	case 0x91:
		GLCD_ST7920_SendString(1, 2, (u8*) " = v1.0");
		break;
	case 0x92:
		GLCD_ST7920_SendString(1, 2, (u8*) " = v2.0");
		break;
	case 0x12:
		GLCD_ST7920_SendString(1, 2, (u8*) " = counterfeit chip");
		break;
	default:
		GLCD_ST7920_SendString(1, 2, (u8*) " = (unknown)");
	}
	if ((v == 0x00) || (v == 0xFF))
	{
		GLCD_ST7920_Clear();
		GLCD_ST7920_SendString(0, 0, (u8*) "WARNING!");
		GLCD_ST7920_SendString(1, 0, (u8*) "Communication failure");
	}
}

void MFRC522_calculateCRC(u8 *data, u8 length, u8 *result)
{
	u8 i, n;

	MFRC522_ClearBitMask(ComIrqReg, 0x04);     //CRCIrq = 0
	MFRC522_SetBitMask(FIFOLevelReg, 0x80);      //Clear the FIFO pointer
	//Write_MFRC522(CommandReg, PCD_IDLE);

	//Writing data to the FIFO
	for (i = 0; i < length; i++)
	{
		MFRC522_WriteRegister(FIFODataReg, *(data + i));
	}
	MFRC522_WriteRegister(CommandReg, MFRC522_CALCCRC);

	//Wait CRC calculation is complete
	i = 0xFF;
	do
	{
		n = MFRC522_ReadRegister(DivIrqReg);
		i--;
	} while ((i != 0) && !(n & 0x04));      //CRCIrq = 1

	//Read CRC calculation result
	result[0] = MFRC522_ReadRegister(CRCResultRegL);
	result[1] = MFRC522_ReadRegister(CRCResultRegH);
}

u8 MFRC522_compareIds(u8 *idCurrent, u8 *idReference)
{
	u8 i;
	for (i = 0; i < 4; i++)
	{
		if (idCurrent[i] != idReference[i])
		{
			return 0;
		}
	}
	return 1;
}
