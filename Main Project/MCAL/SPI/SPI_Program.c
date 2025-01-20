/*
 * SPI_Program.c
 *
 *  Created on: Oct 19, 2024
 *  Author: Mohammed Khalaf
 */

#include "stdTypes.h"
#include "SPI_MemoryMap.h"
#include "BitwiseOperations_LIB.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Configuration.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"


#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include <stdlib.h>
#include <stdio.h>
#include "stm32f103xb.h"

void SPI_Init(SPI_Channel_t SPI_ID) {
    // Initialize clocks for the given SPI channel
    void_Enable_SPI_Clocks(SPI_ID);

    // Configure GPIO for the given SPI channel
    void_Configure_SPI_GPIO(SPI_ID);

    // Configure SPI peripheral for the given SPI channel
    void_Configure_SPI_Peripheral(SPI_ID);
}

static void void_Enable_SPI_Clocks(SPI_Channel_t SPI_ID) {
    switch (SPI_ID) {
        case SPI_1:
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
            break;
        case SPI_2:
            RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; // Enable SPI2 clock
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock
            break;
        default:
            // Handle invalid SPI channel
            break;
    }
}

static void void_Configure_SPI_GPIO(SPI_Channel_t SPI_ID) {
    switch (SPI_ID) {
        case SPI_1:
            // Configure GPIO for SPI1 (PA5: SCK, PA6: MISO, PA7: MOSI)
            GPIOA->CRL &= ~((0xF << (4 * 5)) | (0xF << (4 * 6)) | (0xF << (4 * 7)));
            GPIOA->CRL |= ((0xB << (4 * 5)) | (0x4 << (4 * 6)) | (0xB << (4 * 7)));
            break;
        case SPI_2:
            // Configure GPIO for SPI2 (PB13: SCK, PB14: MISO, PB15: MOSI)
            GPIOB->CRH &= ~((0xF << (4 * (13 - 8))) | (0xF << (4 * (14 - 8))) | (0xF << (4 * (15 - 8))));
            GPIOB->CRH |= ((0xB << (4 * (13 - 8))) | (0x4 << (4 * (14 - 8))) | (0xB << (4 * (15 - 8))));
            break;
        default:
            // Handle invalid SPI channel
            break;
    }
}

static void void_Configure_SPI_Peripheral(SPI_Channel_t SPI_ID) {
    SPI_t *SPIx;
    switch (SPI_ID) {
        case SPI_1:
            SPIx = SPI1;
            break;
        case SPI_2:
            SPIx = SPI2;
            break;
        default:
            // Handle invalid SPI channel
            return;
    }

    // Configure SPI settings
    SPIx->CR1 = SPI_CR1_MSTR           // Master mode
              | SPI_CR1_BR_1 | SPI_CR1_BR_0 // Baud rate fPCLK/16
              | SPI_CR1_SSM            // Software NSS management
              | SPI_CR1_SSI;           // Internal NSS signal

    // Enable SPI
    SPIx->CR1 |= SPI_CR1_SPE;
}
/**************************************************************************/

void SPI_void_Initialization(SPI_Channel_t SPI_ID, SPI_Mode_t Mode,
		Direction_Data_Mode_t Direction_Mode, SPI_DataFormat_t DataFormat,
		SPI_Clock_Polarity_t ClockPolarity, SPI_Clock_Phase_t ClockPhase,
		SPI_Baud_Rate_Prescaler_t Prescaler, SPI_NSS_Management_t NSSManagement)
{
	void_SPI_Enable(SPI_ID);
	void_SPI_Mode(SPI_ID, Mode);
	SPI_void_Set_Direction(SPI_ID, Direction_Mode);
	void_SPI_Set_DataFormat(SPI_ID, DataFormat);
	void_SPI_Set_ClockPolarity(SPI_ID, ClockPolarity);
	void_SPI_Set_ClockPhase(SPI_ID, ClockPhase);
	void_SPI_Set_Baud_Rate_Prescaler(SPI_ID, Prescaler);
	void_SPI_NSS_Management(SPI_ID, NSSManagement);
	SPI_void_Pin_Configurations(SPI_ID, Mode);

}

void void_SPI_Send_Receive(SPI_Channel_t SPI_ID, u8 *pData, u16 size)
{
	switch (SPI_ID)
	{
	case SPI_1:
		for (u16 i = 0; i < size; i++)
		{
			// Wait until the SPI1 is ready to transmit (TXE bit set)
			while (!GET_BIT(SPI1->SR, TXE_SPI))
				; // TXE bit

			// Send a dummy byte to initiate the clock for SPI1
			SPI1->DR = 0xFF;

			// Wait until data is received (RXNE bit set)
			while (!GET_BIT(SPI1->SR, RXNE_SPI))
				; // RXNE bit

			// Read the received data
			pData[i] = SPI1->DR;
		}
		break;

	case SPI_2:
		for (u16 i = 0; i < size; i++)
		{
			// Wait until the SPI2 is ready to transmit (TXE bit set)
			while (!GET_BIT(SPI2->SR, TXE_SPI))
				; // TXE bit

			// Send a dummy byte to initiate the clock for SPI2
			SPI2->DR = 0xFF;

			// Wait until data is received (RXNE bit set)
			while (!GET_BIT(SPI2->SR, RXNE_SPI))
				; // RXNE bit

			// Read the received data
			pData[i] = SPI2->DR;
		}
		break;

	default:
		// Handle invalid SPI channel if needed
		break;
	}
}

void SPI_void_Write_Data(SPI_Channel_t SPI_ID, u8 Data)
{
	switch (SPI_ID)
	{
	case SPI_1:
		// Wait until the transmission buffer of SPI1 is empty (TXE bit set)
		while (!GET_BIT(SPI1->SR, TXE_SPI))
			; // TXE bit check
		SPI1->DR = Data; // Send data to SPI1 Data Register
		while (GET_BIT(SPI1->SR, BSY))
			; // Wait until SPI1 bus is not busy (BSY bit cleared)
		break;

	case SPI_2:
		// Wait until the transmission buffer of SPI2 is empty (TXE bit set)
		while (!GET_BIT(SPI2->SR, TXE_SPI))
			; // TXE bit check
		SPI2->DR = Data; // Send data to SPI2 Data Register
		while (GET_BIT(SPI2->SR, BSY))
			; // Wait until SPI2 bus is not busy (BSY bit cleared)
		break;

	default:
		// Handle invalid SPI channel
		break;
	}
}

u8 SPI_u8_Send_Receive_Byte(SPI_Channel_t SPI_ID, u8 data)
{
	switch (SPI_ID)
	{
	case SPI_1:
		// Send data using SPI1
		SPI1->DR = data;

		// Wait until the SPI1 interrupt flag (SPIF equivalent) indicates transmission completion
		while (!GET_BIT(SPI1->SR, RXNE_SPI))
			; // Wait until RXNE is set, indicating data has been received

		// Return the received data from SPI1
		return SPI1->DR;

	case SPI_2:

		// Send data using SPI2
		SPI2->DR = data;
		GLCD_ST7920_SendString(1, 0, (u8*)"Before SPI RX");
		// Wait until the SPI2 interrupt flag (SPIF equivalent) indicates transmission completion
		while (!GET_BIT(SPI2->SR, RXNE_SPI)); // Wait until RXNE is set, indicating data has been received
		GLCD_ST7920_SendString(1, 0, (u8*)"AFTER SPI RX");
		// Return the received data from SPI2
		return SPI2->DR;

	default:
		// Return 0 if an invalid channel is passed
		return 0;
	}
}

void SPI_sendString(SPI_Channel_t SPI_ID, const u8 *String)
{
	u8 i = 0;
	u8 received_data = 0;

	// Send the entire string until the null terminator
	while (String[i] != '\0')
	{
		// Transmit each byte and store received data (dummy read)
		received_data = SPI_u8_Send_Receive_Byte(SPI_ID, String[i]);
		i++;
	}
}

/*************************************************** Private Function Definitions ********************************/

static void SPI_void_Pin_Configurations(SPI_Channel_t SPI_ID, SPI_Mode_t Mode)
{
	switch (SPI_ID)
	{
	case SPI_1:
		if (Mode == SPI_MODE_MASTER)
		{
			/* Configure SPI1 pins: SCK (PA5), MISO (PA6), MOSI (PA7) */
			GPIO_void_SetPinMode1(SPI1_SCK_PIN, DIO_OUTPUT_PUSHPULL_50MHZ);
			GPIO_void_SetPinMode1(SPI1_MISO_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI1_MOSI_PIN, DIO_AFIO_PUSHPULL_50MHZ);
			GPIO_void_SetPinMode1(SPI1_NSS_PIN, DIO_OUTPUT_PUSHPULL_50MHZ);

		}
		else if (Mode == SPI_MODE_SLAVE)
		{
			/* Configure SPI1 pins: SCK (PA5), MISO (PA6), MOSI (PA7) */
			GPIO_void_SetPinMode1(SPI1_SCK_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI1_MISO_PIN, DIO_AFIO_PUSHPULL_50MHZ);
			GPIO_void_SetPinMode1(SPI1_MOSI_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI1_NSS_PIN, DIO_INPUT_FLOATING);
		}
		break;
	case SPI_2:
		if (Mode == SPI_MODE_MASTER)
		{
			/* Configure SPI2 pins: SCK (PB13), MISO (PB14), MOSI (PB15) */
			GPIO_void_SetPinMode1(SPI2_SCK_PIN, DIO_AFIO_PUSHPULL_10MHZ);
			GPIO_void_SetPinMode1(SPI2_MISO_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI2_MOSI_PIN, DIO_AFIO_PUSHPULL_10MHZ);
			GPIO_void_SetPinMode1(SPI2_NSS_PIN, DIO_AFIO_PUSHPULL_10MHZ);
		}
		else if (Mode == SPI_MODE_SLAVE)
		{
			/* Configure SPI2 pins: SCK (PB13), MISO (PB14), MOSI (PB15) */
			GPIO_void_SetPinMode1(SPI2_SCK_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI2_MISO_PIN, DIO_AFIO_PUSHPULL_50MHZ);
			GPIO_void_SetPinMode1(SPI2_MOSI_PIN, DIO_INPUT_FLOATING);
			GPIO_void_SetPinMode1(SPI2_NSS_PIN, DIO_INPUT_FLOATING);
		}
		break;

	default:
		// Handle error: Invalid SPI channel

	}
}
static void void_SPI_Enable(SPI_Channel_t SPI_ID)
{
	switch (SPI_ID)
	{
	case SPI_1:
		/* Prepare the SPI1 Peripheral Port and Pins */
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_AFIO_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_SPI1_EN);

		/* Configure SPI1 pins: SCK (PA5), MISO (PA6), MOSI (PA7) */
//		GPIO_void_SetPinMode1(SPI1_SCK_PIN, DIO_AFIO_PUSHPULL_50MHZ);
//		GPIO_void_SetPinMode1(SPI1_MISO_PIN, DIO_INPUT_FLOATING);
//		GPIO_void_SetPinMode1(SPI1_MOSI_PIN, DIO_AFIO_PUSHPULL_50MHZ);
//		GPIO_void_SetPinMode1(SPI1_NSS_PIN, DIO_OUTPUT_PUSHPULL_50MHZ);
		/* Enable the SPI peripheral */
		SET_BIT(SPI1->CR1, SPE); // SPE: SPI enable bit
		break;

	case SPI_2:
		/* Prepare the SPI2 Peripheral Port and Pins */
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_AFIO_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
		RCC_void_Enable_Clock(RCC_APB1ENR, APB1_SPI2_EN);

		/* Configure SPI2 pins: SCK (PB13), MISO (PB14), MOSI (PB15) */
//		GPIO_void_SetPinMode1(SPI2_SCK_PIN, DIO_AFIO_PUSHPULL_50MHZ);
//		GPIO_void_SetPinMode1(SPI2_MISO_PIN, DIO_INPUT_FLOATING);
//		GPIO_void_SetPinMode1(SPI2_MOSI_PIN, DIO_AFIO_PUSHPULL_50MHZ);
//		GPIO_void_SetPinMode1(SPI2_NSS_PIN, DIO_OUTPUT_PUSHPULL_50MHZ);
		/* Enable the SPI peripheral */
		SET_BIT(SPI2->CR1, SPE); // SPE: SPI enable bit
		break;

	default:
		/* Handle invalid SPI ID (default to SPI1 or add error handling) */
		SET_BIT(SPI1->CR1, SPE); // SPE: SPI enable bit
		break;
	}
}

// Set the SPI mode (Master/Slave)
static void void_SPI_Mode(SPI_Channel_t SPI_ID, SPI_Mode_t SPI_Mode)
{
	switch (SPI_ID)
	{
	case SPI_1:
		void_SPI1_Mode(SPI_Mode);
		break;
	case SPI_2:
		void_SPI2_Mode(SPI_Mode);
		break;
	default:
		// Handle error: Invalid SPI channel
		break;
	}
}

static void void_SPI1_Mode(SPI_Mode_t Mode)
{
	switch (Mode)
	{
	case SPI_MODE_MASTER:
		SET_BIT(SPI1->CR1, MSTR); // Set MSTR bit for Master mode
		break;
	case SPI_MODE_SLAVE:
		CLEAR_BIT(SPI1->CR1, MSTR); // Clear MSTR bit for Slave mode
		break;
	default:
		// Handle error: Invalid SPI channel
		break;
	}
}

static void void_SPI2_Mode(SPI_Mode_t Mode)
{
	switch (Mode)
	{
	case SPI_MODE_MASTER:
		SET_BIT(SPI2->CR1, MSTR); // Set MSTR bit for Master mode
		break;
	case SPI_MODE_SLAVE:
		CLEAR_BIT(SPI2->CR1, MSTR); // Clear MSTR bit for Slave mode
		break;
	default:
		// Handle error: Invalid SPI channel
		break;
	}
}

//Select Bidirectional Data Mode

static void SPI_void_Set_Direction(SPI_Channel_t SPI_ID,
		Direction_Data_Mode_t Direction_Mode)
{
	switch (SPI_ID)
	{
	case SPI_1:
		// Configure SPI1's communication direction
		SPI1_Set_Direction(Direction_Mode);
		break;

	case SPI_2:
		// Configure SPI2's communication direction
		SPI2_Set_Direction(Direction_Mode);
		break;

	default:
		// Handle invalid SPI channel input
		break;
	}
}

static void SPI1_Set_Direction(Direction_Data_Mode_t Direction_Mode)
{
	switch (Direction_Mode)
	{
	case SPI_DIRECTION_2LINES:
		// Configure SPI1 for full-duplex (2-line) mode
		CLEAR_BIT(SPI1->CR1, BIDIMODE); // Clear the BIDIMODE bit
		break;

	case SPI_DIRECTION_1LINE:
		// Configure SPI1 for half-duplex (1-line) mode
		SET_BIT(SPI1->CR1, BIDIMODE); // Set the BIDIMODE bit
		break;

	default:
		// Handle invalid direction mode
		break;
	}
}

static void SPI2_Set_Direction(Direction_Data_Mode_t Direction_Mode)
{
	switch (Direction_Mode)
	{
	case SPI_DIRECTION_2LINES:
		// Configure SPI2 for full-duplex (2-line) mode
		CLEAR_BIT(SPI2->CR1, BIDIMODE); // Clear the BIDIMODE bit
		break;

	case SPI_DIRECTION_1LINE:
		// Configure SPI2 for half-duplex (1-line) mode
		SET_BIT(SPI2->CR1, BIDIMODE); // Set the BIDIMODE bit
		break;

	default:
		// Handle invalid direction mode
		break;
	}
}

// Set the data format (8-bit/16-bit)
static void void_SPI_Set_DataFormat(SPI_Channel_t SPI_ID,
		SPI_DataFormat_t DataFormat)
{
	switch (SPI_ID)
	{
	case SPI_1:
		void_SPI1_DataFormat(DataFormat);
		break;
	case SPI_2:
		void_SPI2_DataFormat(DataFormat);
		break;
	default:
		// Handle error: Invalid SPI Channel
		break;
	}
}

static void void_SPI1_DataFormat(SPI_DataFormat_t DataFormat)
{
	switch (DataFormat)
	{
	case SPI_DATAFORMAT_8_BIT:
		CLEAR_BIT(SPI1->CR1, DFF); // Set the DFF bit to 0 for 8-bit data format
		break;
	case SPI_DATAFORMAT_16_BIT:
		SET_BIT(SPI1->CR1, DFF); // Set the DFF bit to 1 for 16-bit data format
		break;
	default:
		// Handle error: Invalid Data Format
		break;
	}
}

void void_SPI2_DataFormat(SPI_DataFormat_t DataFormat)
{
	switch (DataFormat)
	{
	case SPI_DATAFORMAT_8_BIT:
		CLEAR_BIT(SPI2->CR1, DFF); // Set the DFF bit to 0 for 8-bit data format
		break;
	case SPI_DATAFORMAT_16_BIT:
		SET_BIT(SPI2->CR1, DFF); // Set the DFF bit to 1 for 16-bit data format
		break;
	default:
		// Handle error: Invalid Data Format
		break;
	}
}

// Set the clock polarity (CPOL)
void void_SPI_Set_ClockPolarity(SPI_Channel_t SPI_ID,
		SPI_Clock_Polarity_t ClockPolarity)
{
	switch (SPI_ID)
	{
	case SPI_1:
		void_SPI1_Set_ClockPolarity(ClockPolarity);
		break;
	case SPI_2:
		void_SPI2_Set_ClockPolarity(ClockPolarity);
		break;
	default:
		// Handle error: Invalid SPI Channel
		break;
	}
}

void void_SPI1_Set_ClockPolarity(SPI_Clock_Polarity_t ClockPolarity)
{
	switch (ClockPolarity)
	{
	case SPI_CPOL_LOW:
		CLEAR_BIT(SPI1->CR1, CPOL_SPI); // Clear CPOL bit for low polarity
		break;
	case SPI_CPOL_HIGH:
		SET_BIT(SPI1->CR1, CPOL_SPI); // Set CPOL bit for high polarity
		break;
	default:
		// Handle error: Invalid clock polarity selection
		break;
	}
}
void void_SPI2_Set_ClockPolarity(SPI_Clock_Polarity_t ClockPolarity)
{
	switch (ClockPolarity)
	{
	case SPI_CPOL_LOW:
		CLEAR_BIT(SPI2->CR1, CPOL_SPI); // Clear CPOL bit for low polarity
		break;
	case SPI_CPOL_HIGH:
		SET_BIT(SPI2->CR1, CPOL_SPI); // Set CPOL bit for high polarity
		break;
	default:
		// Handle error: Invalid clock polarity selection
		break;
	}
}

// Set the clock phase (CPHA)
void void_SPI_Set_ClockPhase(SPI_Channel_t SPI_ID, SPI_Clock_Phase_t ClockPhase)
{
	switch (SPI_ID)
	{
	case SPI_1:
		void_SPI1_Set_ClockPhase(ClockPhase);
		break;
	case SPI_2:
		void_SPI2_Set_ClockPhase(ClockPhase);
		break;
	default:
		// Handle error: Invalid SPI Channel
		break;
	}
}

void void_SPI1_Set_ClockPhase(SPI_Clock_Phase_t ClockPhase)
{
	switch (ClockPhase)
	{
	case SPI_CPHA_FIRST_EDGE:
		CLEAR_BIT(SPI1->CR1, CPHA_SPI); // Clear CPHA bit for first clock edge
		break;
	case SPI_CPHA_SECOND_EDGE:
		SET_BIT(SPI1->CR1, CPHA_SPI);   // Set CPHA bit for second clock edge
		break;
	default:
		break; // Handle unexpected cases, if needed
	}
}

void void_SPI2_Set_ClockPhase(SPI_Clock_Phase_t ClockPhase)
{
	switch (ClockPhase)
	{
	case SPI_CPHA_FIRST_EDGE:
		CLEAR_BIT(SPI2->CR1, CPHA_SPI); // Clear CPHA bit for first clock edge
		break;
	case SPI_CPHA_SECOND_EDGE:
		SET_BIT(SPI2->CR1, CPHA_SPI);   // Set CPHA bit for second clock edge
		break;
	default:
		break; // Handle unexpected cases, if needed
	}
}
// Set the baud rate prescaler
void void_SPI_Set_Baud_Rate_Prescaler(SPI_Channel_t SPI_ID,
		SPI_Baud_Rate_Prescaler_t Prescaler)
{
	switch (SPI_ID)
	{
	case SPI_1:
		// Clear the BR bits (bits 5:3) in the CR1 register
		CLEAR_BIT(SPI1->CR1, BR0);
		CLEAR_BIT(SPI1->CR1, BR1);
		CLEAR_BIT(SPI1->CR1, BR2);
		// Set the baud rate prescaler (BR bits)
		BIT_WRITE(SPI1->CR1, BR0, Prescaler & 0x07); // Assuming Prescaler fits in the lower 3 bits
		break;
	case SPI_2:
		// Clear the BR bits (bits 5:3) in the CR1 register
		CLEAR_BIT(SPI1->CR1, BR0);
		CLEAR_BIT(SPI1->CR1, BR1);
		CLEAR_BIT(SPI1->CR1, BR2);
		// Set the baud rate prescaler (BR bits)
		BIT_WRITE(SPI2->CR1, BR0, Prescaler & 0x07); // Assuming Prescaler fits in the lower 3 bits
		break;
	default:
		// Handle error: Invalid SPI Channel
		break;
	}
}

//// Manage NSS (chip select) configuration
static void void_SPI_NSS_Management(SPI_Channel_t SPI_ID,
		SPI_NSS_Management_t NSSManagement)
{
	switch (SPI_ID)
	{
	case SPI_1:
		void_SPI1_NSS_Management(NSSManagement);
		break;
	case SPI_2:
		void_SPI2_NSS_Management(NSSManagement);
		break;

	default:
		// Optionally handle error for unsupported SPI channel
		break;
	}
}

static void void_SPI1_NSS_Management(SPI_NSS_Management_t NSSManagement)
{
	switch (NSSManagement)
	{
	case SPI_NSS_SOFT:
		SET_BIT(SPI1->CR1, SSM); // Set SSM bit for software NSS management
		if (SPI_SSI == SPI_SSI_HIGH)
			SET_BIT(SPI1->CR1, SSI); // Set NSS high
		else
			CLEAR_BIT(SPI1->CR1, SSI); // Set NSS low
		break;

	case SPI_NSS_HARD:
		CLEAR_BIT(SPI1->CR1, SSM); // Clear SSM bit for hardware NSS management
		break;

	default:
		// Optionally handle unexpected values
		// This can be a no-op or an error logging mechanism
		break;
	}
}
static void void_SPI2_NSS_Management(SPI_NSS_Management_t NSSManagement)
{
	switch (NSSManagement)
	{
	case SPI_NSS_SOFT:
		SET_BIT(SPI2->CR1, SSM); // Set SSM bit for software NSS management
		if (SPI_SSI == SPI_SSI_HIGH)
			SET_BIT(SPI2->CR1, SSI); // Set NSS high
		else
			CLEAR_BIT(SPI2->CR1, SSI); // Set NSS low
		break;

	case SPI_NSS_HARD:
		CLEAR_BIT(SPI2->CR1, SSM); // Clear SSM bit for hardware NSS management
		break;

	default:
		// Optionally handle unexpected values
		// This can be a no-op or an error logging mechanism
		break;
	}
}
