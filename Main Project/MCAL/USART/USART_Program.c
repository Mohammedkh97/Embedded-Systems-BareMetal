/*
 * USART_Program.c
 *
 *  Created on: Sep 25, 2024
 *  Author: Mohammed Khalaf
 */


#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "USART_MemoryMap.h"
#include "USART_Interface.h"
#include "USART_Private.h"
#include "USART_Configuration.h"


// initialize the USART with default settings (1start, 8data, 1stop bit) and 115200 baud rate
//void init_USART1(void) {
//	//	enable GPIO port A clock , alternate function I/O clock and USART1 clock
//	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN  | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN);
//	// enable USART, transmitter and receiver
//	USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
//	// 	set baud rate divider to achieve a baud rate of 115200 from the 72MHz PCLK2
//	USART1->BRR = 625;	// alternatively e.g. BRR = 7500 for 9600 baud
//	// 	set PA9 as alternate function push-pull output with max speed of 50MHz
//	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
//	GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1);
//	// 	set PA10 as floating input
//	GPIOA->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1);
//	GPIOA->CRH |= GPIO_CRH_CNF10_0;
//}

void USART_void_Initializtion(USART_Channel_t USART_ID, USART_Mode_t Mode, USART_Parity_t Parity_Bit, USART_StopBits_t Stop_Bits, USART_WordLength_t Word_Length, u32 Baud_Rate)
{
	void_USART_Enable(USART_ID);
	void_Set_Baud_Rate(USART_ID, Baud_Rate);
	void_USART_Mode(USART_ID, Mode);
	void_USART_Parity_Bit_Selection(USART_ID, Parity_Bit);
	void_Stop_Bits_Selection(USART_ID, Stop_Bits);
	void_Set_Word_Length(USART_ID, Word_Length);
}

// Synchronous Function:
void USART_void_Transmit_Byte(USART_Channel_t USART_ID, u8 Data)
{
	// Select the appropriate USART instance based on USART_ID
	switch (USART_ID)
	{
	case USART_1:
		// Wait until TXE (Transmit data register empty) flag is set

		while (!BIT_IS_CLEAR(USART2->SR, TXE));
		// Write data to the DR (Data Register)
		USART1->DR = Data;
		// Wait until TC (Transmission complete) flag is set
		while (!GET_BIT(USART1->SR, TC));
		break;
	case USART_2:
		// Wait until TXE (Transmit data register empty) flag is set
		while (!BIT_IS_CLEAR(USART2->SR, TXE))
			;
		// Write data to the DR (Data Register)
		USART2->DR = Data;
		// Wait until TC (Transmission complete) flag is set
		while (!GET_BIT(USART2->SR, TC));
		break;
	case USART_3:
		// Wait until TXE (Transmit data register empty) flag is set

		while (!BIT_IS_CLEAR(USART3->SR, TXE));
		// Write data to the DR (Data Register)
		USART3->DR = Data;
		// Wait until TC (Transmission complete) flag is set
		while (!GET_BIT(USART3->SR, TC))
			;
		break;
	default:
		// Handle invalid USART_ID error (optional)
		return;
	}
}

u8 USART_void_Receive_Byte(USART_Channel_t USART_ID)
{
	u8 received_Data;

	// Select the appropriate USART instance based on uart
	switch (USART_ID)
	{
	case USART_1:
		// Wait until RXNE (Receive data register not empty) flag is set
		while (!GET_BIT(USART1->SR, RXNE))
			;

		// Read received data from the DR (Data Register)
		received_Data = (u8) USART1->DR;
		break;
	case USART_2:
		// Wait until RXNE (Receive data register not empty) flag is set
		while (!GET_BIT(USART2->SR, RXNE));

		// Read received data from the DR (Data Register)
		received_Data = (u8) USART2->DR;
		break;
	case USART_3:
		// Wait until RXNE (Receive data register not empty) flag is set
		while (!GET_BIT(USART3->SR, RXNE));

		// Read received data from the DR (Data Register)
		received_Data = (u8) USART3->DR;
		break;
	default:
		// Handle invalid UART channel error (optional)
		return 0; // or some error code
	}

	return received_Data; // Return the received byte
}

//Developed By Mahmoud Rizk & Ahmed Hassan
u8 USART_isDataAvailable(USART_Channel_t USART_ID)
{
	switch(USART_ID)
	{
	case USART_1:
		return GET_BIT(USART1->SR, RXNE) ? 1 : 0;
	case USART_2:
		return GET_BIT(USART2->SR, RXNE) ? 1 : 0;
	case USART_3:
		return GET_BIT(USART3->SR, RXNE) ? 1 : 0;
	default:
		break;
	}
	return 0;
}

//Developed By Mahmoud Rizk & Ahmed Hassan
void USART_receiveStringUntil2term_timeout(u8 *string, USART_Channel_t USART_ID, const u8 *terminator1, const u8 *terminator2, u32 timeout)
{
    u8 i = 0;
    u8 j1 = 0, j2 = 0;  // Separate indices for both terminators
    u8 terminator1Length = strlen((char *)terminator1);
    u8 terminator2Length = strlen((char *)terminator2);
    u32 noDataCounter = 0;  // Counter to track timeout
    u8 matchedTerminator = 0;  // 0 = none, 1 = terminator1, 2 = terminator2

    // Initialize the buffer
    // memset(Str, 0, MAX_STRING_LENGTH);

    // Receive bytes and check against the terminator strings
    while (1)
    {
        // Check if data is available on the UART channel
        if (USART_isDataAvailable(USART_ID))
        {
            string[i] = USART_void_Receive_Byte(USART_ID);  // Receive the next byte
            noDataCounter = 0;  // Reset the timeout counter when data is received

            // Check if the received byte matches the current position of terminator1
            if (string[i] == terminator1[j1])
            {
                j1++;
                // Check if the entire terminator1 has been matched
                if (j1 == terminator1Length)
                {
                	string[i - terminator1Length + 1] = '\0';  // Null-terminate the string
                    matchedTerminator = 1;  // Mark terminator1 as matched
                    break;  // Exit the loop
                }
            }
            else
            {
                j1 = 0;  // Reset if terminator1 match fails
            }

            // Check if the received byte matches the current position of terminator2
            if (string[i] == terminator2[j2])
            {
                j2++;
                // Check if the entire terminator2 has been matched
                if (j2 == terminator2Length)
                {
                	string[i - terminator2Length + 1] = '\0';  // Null-terminate the string
                    matchedTerminator = 2;  // Mark terminator2 as matched
                    break;  // Exit the loop
                }
            }
            else
            {
                j2 = 0;  // Reset if terminator2 match fails
            }

            i++;
            // Check for buffer overflow
            if (i >= MAX_STRING_LENGTH - 1)
            {
            	string[i] = '\0';  // Ensure the string is null-terminated
                break;  // Exit to avoid buffer overflow
            }
        }
        else
        {
            noDataCounter++;  // Increment counter when no data is received

            // Check if timeout has been reached (null response condition)
            if (noDataCounter >= timeout)
            {
            	string[0] = '\0';  // Null-terminate the string to indicate no data was received
                break;  // Exit the loop due to timeout
            }
        }
    }
}

//Developed By Mahmoud Rizk & Ahmed Hassan
void USART_receiveFrame(u8 *string,USART_Channel_t USART_ID,u8 start,u8 Frame_size)
{
	u8 i = 0;

	/* Receive the first byte */
	do
	{
		string[i] = USART_void_Receive_Byte(USART_ID);
	}while(string[i] != start);

	/* Receive the whole string until the '#' */
//		while(Str[i] != TERMINATOR)
	for(i = 1; i < Frame_size ;i++)
	{
		string[i] = USART_void_Receive_Byte(USART_ID);
	}
//	string[i+1] = (u8*)NullPtr;
	string[i+1] = '\0';  // Use '\0' to assign a null character to an unsigned char

}

/************************************************************* Definition of Private Functions *****************************************/
static void void_USART_Enable(USART_Channel_t USART_ID)
{
	switch (USART_ID)
	{
	case USART_1:
		/*Prepare the USART1 Peripheral Port and Pins */
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_AFIO_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_USART1_EN);


		GPIO_void_SetPinMode1(TXD1, DIO_AFIO_PUSHPULL_50MHZ); // DIO_AFIO_PUSHPULL_10MHZ
		GPIO_void_SetPinMode1(RXD1, DIO_INPUT_PULL_UP_DOWN);
		/*Enable USART BIT in CR1 Register*/

		SET_BIT(USART1->CR1, UE);
		break;
	case USART_2:
		/*Prepare the USART2 Peripheral Port and Pins */
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_AFIO_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
		RCC_void_Enable_Clock(RCC_APB1ENR, APB1_USART2_EN);

		GPIO_void_SetPinMode1(TXD2, DIO_AFIO_PUSHPULL_50MHZ); // DIO_AFIO_PUSHPULL_10MHZ
		GPIO_void_SetPinMode1(RXD2, DIO_INPUT_FLOATING);
		/*Enable USART BIT in CR1 Register*/
		SET_BIT(USART2->CR1, UE);
		break;
	case USART_3:
		/*Prepare the USART3 Peripheral Port and Pins */
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_AFIO_EN);
		RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
		RCC_void_Enable_Clock(RCC_APB1ENR, APB1_USART3_EN);

		GPIO_void_SetPinMode1(TXD3, DIO_AFIO_PUSHPULL_50MHZ); // DIO_AFIO_PUSHPULL_10MHZ
		GPIO_void_SetPinMode1(RXD3, DIO_INPUT_FLOATING);
		/*Enable USART BIT in CR1 Register*/
		SET_BIT(USART1->CR1, RE);
		SET_BIT(USART1->CR1,TE);
		SET_BIT(USART3->CR1, UE);
		break;
	default:
		/*Select USART1 Or Error Handler must be set*/
		SET_BIT(USART1->CR1, UE);
		break;
	}
}


static void void_USART_Disable(USART_Channel_t USART_ID)
{
	switch (USART_ID)
	{
	case USART_1:
		CLEAR_BIT(USART1->CR1, UE);
		break;
	case USART_2:
		CLEAR_BIT(USART2->CR1, UE);
		break;
	case USART_3:
		CLEAR_BIT(USART3->CR1, UE);
		break;
	default:
		/*Select USART1 Or Error Handler must be set*/

		break;
	}
}

static void void_Set_Baud_Rate(USART_Channel_t USART_ID, u32 Baud_Rate) {
    u32 Clock_Frequency;
    u32 Integer_Part;
    u32 Fractional_Part;
    u16 BRR_VALUE = 0;

    // Determine the clock frequency based on the USART channel
    switch (USART_ID) {
        case USART_1:
            // Set the actual PCLK2 frequency for USART1
            Clock_Frequency = PCLK2_FREQUENCY;
            break;
        case USART_2:
            // Set the actual PCLK1 frequency for USART2 and USART3
            Clock_Frequency = PCLK1_FREQUENCY;
            break;
        case USART_3:
            // Set the actual PCLK1 frequency for USART2 and USART3
            Clock_Frequency = PCLK1_FREQUENCY;
            break;
        default:
            // Handle invalid USART_ID
            return;
    }

    // Calculate the USART divider for the BRR register
    f64 UART_Divider = (f64) Clock_Frequency / (Baud_Rate * USART_SCALER);

    // Extract integer and fractional parts
    Integer_Part = (u32) UART_Divider;
    Fractional_Part = (u32) ((UART_Divider - Integer_Part) * USART_SCALER);

    // Combine integer and fractional parts into the BRR register value
    BRR_VALUE = (Integer_Part << 4) | (Fractional_Part & 0x0F);

    // Configure the BRR register based on the USART channel
    switch (USART_ID) {
        case USART_1:
            USART1->BRR = BRR_VALUE;
            break;
        case USART_2:
            USART2->BRR = BRR_VALUE;
            break;
        case USART_3:
            USART3->BRR = BRR_VALUE;
            break;
        default:
            // Optional: Add error handling for unsupported channels
            break;
    }
}



static void void_USART_Mode(USART_Channel_t USART_ID, USART_Mode_t USART_Mode)
{
	switch (USART_ID)
	{
	case USART_1:
		void_USART1_Mode(USART_Mode);
		break;
	case USART_2:
		void_USART2_Mode(USART_Mode);
		break;
	case USART_3:
		void_USART3_Mode(USART_Mode);
		break;
	default:
		break;
	}
}
static void void_USART1_Mode(USART_Mode_t Mode)
{
	switch (Mode)
	{
	case USART_MODE_RX:
		SET_BIT(USART1->CR1, RE);
		CLEAR_BIT(USART1->CR1, TE);
		break;
	case USART_MODE_TX:
		CLEAR_BIT(USART1->CR1, RE);
		SET_BIT(USART1->CR1, TE);
		break;
	case USART_MODE_TX_RX:
		SET_BIT(USART1->CR1, RE);
		SET_BIT(USART1->CR1, TE);
		break;
	default:
		break;
	}

}
static void void_USART2_Mode(USART_Mode_t Mode)
{
	switch (Mode)
	{
	case USART_MODE_RX:
		SET_BIT(USART2->CR1, RE);
		CLEAR_BIT(USART2->CR1, TE);
		break;
	case USART_MODE_TX:
		CLEAR_BIT(USART2->CR1, RE);
		SET_BIT(USART2->CR1, TE);
		break;
	case USART_MODE_TX_RX:
		SET_BIT(USART2->CR1, RE);
		SET_BIT(USART2->CR1, TE);
		break;
	default:
		break;
	}

}
static void void_USART3_Mode(USART_Mode_t Mode)
{
	switch (Mode)
	{
	case USART_MODE_RX:
		SET_BIT(USART3->CR1, RE);
		CLEAR_BIT(USART3->CR1, TE);
		break;
	case USART_MODE_TX:
		CLEAR_BIT(USART3->CR1, RE);
		SET_BIT(USART3->CR1, TE);
		break;
	case USART_MODE_TX_RX:
		SET_BIT(USART3->CR1, RE);
		SET_BIT(USART3->CR1, TE);
		break;
	default:
		break;
	}
}

static void void_USART_Parity_Bit_Selection(USART_Channel_t USART_ID, USART_Parity_t Parity_State)
{
	switch (USART_ID)
	{
	case USART_1:
		if (Parity_State == USART_PARITY_NONE)
		{
			CLEAR_BIT(USART1->CR1, PCE);  // Disable parity
		}
		else
		{
			SET_BIT(USART1->CR1, PCE);    // Enable parity
			if (Parity_State == USART_PARITY_EVEN)
			{
				CLEAR_BIT(USART1->CR1, PS); // Even parity
			}
			else if (Parity_State == USART_PARITY_ODD)
			{
				SET_BIT(USART1->CR1, PS);   // Odd parity
			}
		}
		break;

	case USART_2:
		if (Parity_State == USART_PARITY_NONE)
		{
			CLEAR_BIT(USART2->CR1, PCE);  // Disable parity
		}
		else
		{
			SET_BIT(USART2->CR1, PCE);    // Enable parity
			if (Parity_State == USART_PARITY_EVEN)
			{
				CLEAR_BIT(USART2->CR1, PS); // Even parity
			}
			else if (Parity_State == USART_PARITY_ODD)
			{
				SET_BIT(USART2->CR1, PS);   // Odd parity
			}
		}
		break;

	case USART_3:
		if (Parity_State == USART_PARITY_NONE)
		{
			CLEAR_BIT(USART3->CR1, PCE);  // Disable parity
		}
		else
		{
			SET_BIT(USART3->CR1, PCE);    // Enable parity
			if (Parity_State == USART_PARITY_EVEN)
			{
				CLEAR_BIT(USART3->CR1, PS); // Even parity
			}
			else if (Parity_State == USART_PARITY_ODD)
			{
				SET_BIT(USART3->CR1, PS);   // Odd parity
			}
		}
		break;

	default:
		// Error Handler for invalid USART_ID
		break;
	}
}

/*
 *
 1 Stop Bit (default): 00
 2 Stop Bits: 10
 0.5 Stop Bit: 01 (typically for Smartcard mode when receiving data)
 1.5 Stop Bits: 11 (typically for Smartcard mode when transmitting and receiving)

 */
static void void_Stop_Bits_Selection(USART_Channel_t USART_ID, USART_StopBits_t Stop_Bits)
{
	switch (USART_ID)
	{
	case USART_1:
		switch (Stop_Bits)
		{
		case USART_STOPBITS_1:
			CLEAR_BIT(USART1->CR2, STOP0);
			CLEAR_BIT(USART1->CR2, STOP1);
			break;
		case USART_STOPBITS_2:
			CLEAR_BIT(USART1->CR2, STOP0);
			SET_BIT(USART1->CR2, STOP1);
			break;
		case USART_HALF_STOPBITS:
			SET_BIT(USART1->CR2, STOP0);
			CLEAR_BIT(USART1->CR2, STOP1);
			break;
		case USART_ONE_HALF_STOP_BIT:
			SET_BIT(USART1->CR2, STOP0);
			SET_BIT(USART1->CR2, STOP1);
			break;
		default:
			/*Error Handler*/
			break;
		}
		break;
	case USART_2:
		switch (Stop_Bits)
		{
		case USART_STOPBITS_1:
			CLEAR_BIT(USART2->CR2, STOP0);
			CLEAR_BIT(USART2->CR2, STOP1);
			break;
		case USART_STOPBITS_2:
			CLEAR_BIT(USART2->CR2, STOP0);
			SET_BIT(USART2->CR2, STOP1);
			break;
		case USART_HALF_STOPBITS:
			SET_BIT(USART2->CR2, STOP0);
			CLEAR_BIT(USART2->CR2, STOP1);
			break;
		case USART_ONE_HALF_STOP_BIT:
			SET_BIT(USART2->CR2, STOP0);
			SET_BIT(USART2->CR2, STOP1);
			break;
		default:
			/*Error Handler*/
			break;
		}
		break;
	case USART_3:
		switch (Stop_Bits)
		{
		case USART_STOPBITS_1:
			CLEAR_BIT(USART3->CR2, STOP0);
			CLEAR_BIT(USART3->CR2, STOP1);
			break;
		case USART_STOPBITS_2:
			CLEAR_BIT(USART3->CR2, STOP0);
			SET_BIT(USART3->CR2, STOP1);
			break;
		case USART_HALF_STOPBITS:
			SET_BIT(USART3->CR2, STOP0);
			CLEAR_BIT(USART3->CR2, STOP1);
			break;
		case USART_ONE_HALF_STOP_BIT:
			SET_BIT(USART3->CR2, STOP0);
			SET_BIT(USART3->CR2, STOP1);
			break;
		default:
			/*Error Handler*/
			break;
		}

		break;
	default:
		break;
		/*Error Handler*/

	}
}

static void void_Set_Word_Length(USART_Channel_t USART_ID, USART_WordLength_t Data_Word)
{
	switch (USART_ID)
	{
	case USART_1:
		if (Data_Word == USART_WORDLENGTH_8_BITS)
		{
			CLEAR_BIT(USART1->CR1, M);  // Set word length to 8 bits
		}
		else if (Data_Word == USART_WORDLENGTH_9_BITS)
		{
			SET_BIT(USART1->CR1, M);    // Set word length to 9 bits
		}
		break;

	case USART_2:
		if (Data_Word == USART_WORDLENGTH_8_BITS)
		{
			CLEAR_BIT(USART2->CR1, M);  // Set word length to 8 bits
		}
		else if (Data_Word == USART_WORDLENGTH_9_BITS)
		{
			SET_BIT(USART2->CR1, M);    // Set word length to 9 bits
		}
		break;

	case USART_3:
		if (Data_Word == USART_WORDLENGTH_8_BITS)
		{
			CLEAR_BIT(USART3->CR1, M);  // Set word length to 8 bits
		}
		else if (Data_Word == USART_WORDLENGTH_9_BITS)
		{
			SET_BIT(USART3->CR1, M);    // Set word length to 9 bits
		}
		break;

	default:
		// Error handler for invalid USART_ID
		break;
	}
}

static void void_Set_Wakeup_Method(USART_Channel_t USART_ID, USART_WakeupMethod_t WakeupMethod)
{
    switch (USART_ID)
    {
        case USART_1:
            if (WakeupMethod == ADDRESS_MARK)
            {
                // Set to Address Mark Wakeup
                SET_BIT(USART1->CR1, WAKE);
            }
            else if (WakeupMethod == IDLE_LINE)
            {
                // Set to Idle Line Wakeup (clear WAKE bit)
                CLEAR_BIT(USART1->CR1, WAKE);
            }
            break;

        case USART_2:
            if (WakeupMethod == ADDRESS_MARK)
            {
                // Set to Address Mark Wakeup
                SET_BIT(USART2->CR1, WAKE);
            }
            else if (WakeupMethod == IDLE_LINE)
            {
                // Set to Idle Line Wakeup (clear WAKE bit)
                CLEAR_BIT(USART2->CR1, WAKE);
            }
            break;

        case USART_3:
            if (WakeupMethod == ADDRESS_MARK)
            {
                // Set to Address Mark Wakeup
                SET_BIT(USART3->CR1, WAKE);
            }
            else if (WakeupMethod == IDLE_LINE)
            {
                // Set to Idle Line Wakeup (clear WAKE bit)
                CLEAR_BIT(USART3->CR1, WAKE);
            }
            break;

        default:
            // Error Handler: Invalid USART Channel
            break;
    }
}

