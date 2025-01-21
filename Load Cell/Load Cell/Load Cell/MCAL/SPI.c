/*
* SPI.c
*
* Created: 1/12/2024 1:02:43 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "LCD_int.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "Utils.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void SPI_init(SPI_Mode_t mode , SCK_Frequency_t frequency)
{
	
	// SPI Enable:
	SET_BIT(SPCR , SPE);
	// By default clk 4MHz  ( Freq / 4 = 16 / 4) :  ====> SPI2x  0   SPR1  0   SPR0  0
	switch(frequency)
	{
		case Fosc_4:
		CLEAR_BIT(SPCR , SPR0);
		CLEAR_BIT(SPCR , SPR1);
		CLEAR_BIT(SPSR , SPI2X);
		break;
		case Fosc_16:
		SET_BIT(SPCR , SPR0);
		CLEAR_BIT(SPCR , SPR1);
		CLEAR_BIT(SPSR , SPI2X);
		break;
		case Fosc_128:
		SET_BIT(SPCR , SPR0);
		SET_BIT(SPCR , SPR1);
		CLEAR_BIT(SPSR , SPI2X);
		break;
		case Fosc_2:
		CLEAR_BIT(SPCR , SPR0);
		CLEAR_BIT(SPCR , SPR1);
		SET_BIT(SPSR , SPI2X);
		break;
		case Fosc_8:
		SET_BIT(SPCR , SPR0);
		CLEAR_BIT(SPCR , SPR1);
		SET_BIT(SPSR , SPI2X);
		break;
		case Fosc_32:
		CLEAR_BIT(SPCR , SPR0);
		SET_BIT(SPCR , SPR1);
		SET_BIT(SPSR , SPI2X);
		break;
		case Fosc_64:
		SET_BIT(SPCR , SPR0);
		SET_BIT(SPCR , SPR1);
		SET_BIT(SPSR , SPI2X);
		break;
	}
	if (mode == MASTER)
	{
		SET_BIT(SPCR , MSTR);
		/******** Configure SPI Master Pins *********
		* SS(PB4)   --> Output
		* MOSI(PB5) --> Output
		* MISO(PB6) --> Input
		* SCK(PB7) --> Output
		********************************************/
		DIO_initPin1(SPI_SS , OUTPUT);
		DIO_initPin1(SPI_MOSI,OUTPUT);
		DIO_initPin1(SPI_MISO,INFREE);
		DIO_initPin1(SPI_SCK,OUTPUT);
	}
	else if (mode == SLAVE)
	{
		CLEAR_BIT(SPCR , MSTR);
		/******** Configure SPI Slave Pins *********
		* SS(PB4)   --> Input
		* MOSI(PB5) --> Input
		* MISO(PB6) --> Output
		* SCK(PB7) --> Input
		********************************************/
		DIO_initPin1(SPI_SS , INFREE);
		DIO_initPin1(SPI_MOSI,INFREE);
		DIO_initPin1(SPI_MISO,OUTPUT);
		DIO_initPin1(SPI_SCK,INFREE);
	}
}

u8 SPI_Send_Receive(u8 data)
{
	SPDR = data;

	while (!(SPSR & (1 << SPIF)));  // Busy wait for the SPI Flag to be set
	return SPDR;
}

void SPI_Send_No_Block(u8 data)
{
	SPDR = data;
}

u8 SPI_Send_Receive_With_runtime_out(u8 data , u8* pData , u16 set_Time)  // This function is ONLY for SPI MASTER
{
	u16 counterer = 0 ;// Comparator with the set runtime out
	SPDR = data;
	while(!GET_BIT(SPSR ,SPIF) && counterer < set_Time)
	{
		counterer++;
		_delay_us(1);
	}
	if (counterer < set_Time)
	{
		*pData = SPDR;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
* Description :
* Initialize the SPI device as Master.
*/
void SPI_initMaster(void)
{
	/******** Configure SPI Master Pins *********
	* SS(PB4)   --> Output
	* MOSI(PB5) --> Output
	* MISO(PB6) --> Input
	* SCK(PB7) --> Output
	********************************************/
	DIO_initPin1(SPI_SS , OUTPUT);
	DIO_initPin1(SPI_MOSI,OUTPUT);
	DIO_initPin1(SPI_MISO,INFREE);
	DIO_initPin1(SPI_SCK,OUTPUT);
	
	/************************** SPCR Description **************************
	* SPIE    = 0 Disable SPI Interrupt
	* SPE     = 1 Enable SPI Driver
	* DORD    = 0 Transmit the MSB first
	* MSTR    = 1 Enable Master
	* CPOL    = 0 SCK is low when idle
	* CPHA    = 0 Sample Data with the raising edge
	* SPR1:0  = 00 Choose SPI clock = Fosc/4
	***********************************************************************/
	SPCR = (1<<SPE) | (1<<MSTR);
	SET_BIT(SPCR , SPE);
	SET_BIT(SPCR , MSTR);
	SET_BIT(SPCR , SPR0);
	/* Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	SPSR &= ~(1<<SPI2X);
}

/*
* Description :
* Initialize the SPI device as Slave.
*/
void SPI_initSlave(void)
{
	/******** Configure SPI Slave Pins *********
	* SS(PB4)   --> Input
	* MOSI(PB5) --> Input
	* MISO(PB6) --> Output
	* SCK(PB7) --> Input
	********************************************/
	DIO_initPin1(SPI_SS , INFREE);
	DIO_initPin1(SPI_MOSI,INFREE);
	DIO_initPin1(SPI_MISO,OUTPUT);
	DIO_initPin1(SPI_SCK,INFREE);

	/************************** SPCR Description **************************
	* SPIE    = 0 Disable SPI Interrupt
	* SPE     = 1 Enable SPI Driver
	* DORD    = 0 Transmit the MSB first
	* MSTR    = 0 Disable Master
	* CPOL    = 0 SCK is low when idle
	* CPHA    = 0 Sample Data with the raising edge
	* SPR1:0  = 00 Choose SPI clock = Fosc/4
	***********************************************************************/
	SPCR = (1<<SPE);
	SET_BIT(SPCR , SPE);
	CLEAR_BIT(SPCR , MSTR);
	//SET_BIT(SPCR , SPR0); // SPI clock = Fosc/16
	//CLEAR_BIT(SPCR , SPR1);
	/* Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	SPSR &= ~(1<<SPI2X);
}

/*
* Description :
* Send the required data through SPI to the other SPI device.
* In the same time data will be received from the other device.
*/
u8 SPI_sendReceiveByte(u8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = data;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while(CLEAR_BIT(SPSR,SPIF)){}

	/*
	* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	* and then accessing SPDR like the below line.
	*/
	return SPDR;
}

/*
* Description :
* Send the required string through SPI to the other SPI device.
*/
void SPI_sendString(const u8 *str)
{
	u8 i = 0;
	u8 received_data = 0;

	/* Send the whole string */
	while(str[i] != '\0')
	{
		/*
		* received_data contains the received data from the other device.
		* It is a dummy data variable as we just need to send the string to other device.
		*/
		received_data = SPI_sendReceiveByte(str[i]);
		i++;
	}
}

/*
* Description :
* Receive the required string until the '#' symbol through SPI from the other SPI device.
*/
void SPI_receiveString(u8 *str)
{
	u8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}



