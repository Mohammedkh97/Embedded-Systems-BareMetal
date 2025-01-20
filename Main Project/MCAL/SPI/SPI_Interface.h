/*
 * SPI_Interface.h
 *
 *  Created on: Oct 19, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef SPI_SPI_INTERFACE_H_
#define SPI_SPI_INTERFACE_H_

typedef enum
{
	SPI_1,
	SPI_2

}SPI_Channel_t;

typedef enum
{
	SPI_MODE_SLAVE,
	SPI_MODE_MASTER

}SPI_Mode_t;

typedef enum
{
	SPI_DIRECTION_2LINES,
	SPI_DIRECTION_1LINE

}Direction_Data_Mode_t;   // Bit 15   ==>  BIDIMODE: Bidirectional data mode enable

typedef enum
{
	SPI_DATAFORMAT_8_BIT,
	SPI_DATAFORMAT_16_BIT
}SPI_DataFormat_t;

typedef enum
{
	PRESCALER_2,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128,
	PRESCALER_256
}SPI_Baud_Rate_Prescaler_t;

typedef enum
{
	SPI_CPOL_LOW,
	SPI_CPOL_HIGH

}SPI_Clock_Polarity_t;

typedef enum
{
	SPI_CPHA_FIRST_EDGE,
	SPI_CPHA_SECOND_EDGE

}SPI_Clock_Phase_t;

typedef enum
{
    SPI_NSS_SOFT,
    SPI_NSS_HARD
} SPI_NSS_Management_t;


typedef enum
{
    SPI_SSI_LOW,  // NSS low (active)
    SPI_SSI_HIGH  // NSS high (inactive)
} SPI_SSI_t;

/*************************************** Function Prototypes ***********************************/

void SPI_void_Initialization(SPI_Channel_t SPI_ID, SPI_Mode_t Mode, Direction_Data_Mode_t Direction_Mode, SPI_DataFormat_t DataFormat, SPI_Clock_Polarity_t ClockPolarity, SPI_Clock_Phase_t ClockPhase, SPI_Baud_Rate_Prescaler_t Prescaler, SPI_NSS_Management_t NSSManagement);
void SPI_void_Write_Data(SPI_Channel_t SPI_ID, u8 Data);
void void_SPI_Send_Receive(SPI_Channel_t SPI_ID, u8 *pData, u16 size);
u8 SPI_u8_Send_Receive_Byte(SPI_Channel_t SPI_ID, u8 data);
void SPI_sendString(SPI_Channel_t SPI_ID, const u8 *String);

/***********************************************************************************************/
void SPI_Init(SPI_Channel_t SPI_ID);
static void void_Enable_SPI_Clocks(SPI_Channel_t SPI_ID);
static void void_Configure_SPI_GPIO(SPI_Channel_t SPI_ID);
static void void_Configure_SPI_Peripheral(SPI_Channel_t SPI_ID);

#endif /* SPI_SPI_INTERFACE_H_ */
