/*
* UART.c
*
* Created: 7/21/2023 2:21:17 AM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "UART.h"
#include "Utils.h"
#include "UART_Config.h"
#include "DIO_interface.h"

static void (*UART_RX_Fptr)(void) = (u8)Null_Ptr;
static void (*UART_TX_Fptr)(void) = (u8)Null_Ptr;

#define F_CPU 16000000UL
#include <util/delay.h>
// void UART_init(void)
// {
// 	/* baud rate  9600 with clock 8MHz*/
// 	UBRR0L = 51;
// 	/*frame size*/
// 	// 8 bit data 1 Stop bit No parity bit
// 	// Frame by default value of Registers is set to 8-bit
// 	/* Enable UART Transmitting and Receiving */
// 	// Normal Speed
// 	CLEAR_BIT(UCSR0A , U2X0);
// 	
// 	SET_BIT(UCSR0B , TXEN0);
// 	SET_BIT(UCSR0B , RXEN0);
// }

void UART_Init(u32 baud_rate, UART_Channel_t uart)
{
	u16 ubrr = 0;

	//Asynchronous Normal Mode (U2X = 0)
	/* Calculate the UBRR register value */
	//ubrr = (u16)(((F_CPU / (baud_rate * 16))) - 1);

	//Asynchronous Double Speed Mode (U2X = 1)
	/* Calculate the UBRR register value */
	ubrr = (u16)(((F_CPU / (baud_rate * 8))) - 1);
	
	if(uart == UART0)
	{
		DIO_initPin1(RXD0 , INFREE);
		DIO_initPin1(TXD0 , OUTPUT);
		// Set baud rate for UART0
		UBRR0H = (u8)(ubrr >> 8);
		UBRR0L = (u8)ubrr;
		
		/* U2X = 1 for double transmission speed */
		UCSR0A = (1<<U2X0);
		
		/* U2X = 0 for normal transmission speed */
		//CLEAR_BIT(UCSR0A , U2X0);
		
		/************************** UCSRB Description **************************
		* RXCIE0 = 1 Enable USART RX Complete Interrupt Enable
		* TXCIE0 = 0 Disable USART Tx Complete Interrupt Enable
		* UDRIE0 = 0 Disable USART Data Register Empty Interrupt Enable
		* RXEN0  = 1 Receiver Enable
		* RXEN0  = 1 Transmitter Enable
		* UCSZ2 = 0 For 8-bit data mode
		* RXB8 & TXB8 not used for 8-bit data mode
		***********************************************************************/

		/************************** UCSRC Description **************************
		* URSEL   = 1 The URSEL must be one when writing the UCSRC
		* UMSEL   = 0 Asynchronous Operation
		* UPM1:0  = 00 Disable parity bit
		* USBS    = 0 One stop bit
		* UCSZ1:0 = 11 For 8-bit data mode
		* UCPOL   = 0 Used with the Synchronous operation only
		***********************************************************************/
		// Set frame format: 8 data bits, 1 stop bit, no parity
		// Frame by default value of Registers is set to  8 bit data 1 Stop bit No parity bit
		CLEAR_BIT(UCSR0C, UPM01); // No parity
		CLEAR_BIT(UCSR0C, UPM00);
		CLEAR_BIT(UCSR0C, USBS0); // 1 stop bit
		SET_BIT(UCSR0C, UCSZ01); // 8-bit data
		SET_BIT(UCSR0C, UCSZ00);

		// Enable receiver and transmitter for UART0
		SET_BIT(UCSR0B, TXEN0);
		SET_BIT(UCSR0B, RXEN0);
		
	}
	else if(uart == UART1)
	{
		DIO_initPin1(RXD1 , INFREE);
		DIO_initPin1(TXD1 , OUTPUT);
		// Set baud rate for UART1
		UBRR1H = (u8)(ubrr >> 8);
		UBRR1L = (u8)ubrr;
		u16 ubrr_value = 0;
		
		/* U2X = 1 for double transmission speed */
		UCSR1A = (1<<U2X1);
		
		/* U2X = 0 for normal transmission speed */
		//CLEAR_BIT(UCSR1A , U2X1);
		
		/************************** UCSRB Description **************************
		* RXCIE0 = 1 Enable USART RX Complete Interrupt Enable
		* TXCIE0 = 0 Disable USART Tx Complete Interrupt Enable
		* UDRIE0 = 0 Disable USART Data Register Empty Interrupt Enable
		* RXEN0  = 1 Receiver Enable
		* RXEN0  = 1 Transmitter Enable
		* UCSZ2 = 0 For 8-bit data mode
		* RXB8 & TXB8 not used for 8-bit data mode
		***********************************************************************/
		/************************** UCSRC Description **************************
		* URSEL   = 1 The URSEL must be one when writing the UCSRC
		* UMSEL   = 0 Asynchronous Operation
		* UPM1:0  = 00 Disable parity bit
		* USBS    = 0 One stop bit
		* UCSZ1:0 = 11 For 8-bit data mode
		* UCPOL   = 0 Used with the Synchronous operation only
		***********************************************************************/
		// Set frame format: 8 data bits, 1 stop bit, no parity
		CLEAR_BIT(UCSR1C, UPM11); // No parity
		CLEAR_BIT(UCSR1C, UPM10);
		CLEAR_BIT(UCSR1C, USBS1); // 1 stop bit
		SET_BIT(UCSR1C, UCSZ11); // 8-bit data
		SET_BIT(UCSR1C, UCSZ10);
		UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
		
		// Enable receiver and transmitter for UART1
		SET_BIT(UCSR1B, TXEN1);
		SET_BIT(UCSR1B, RXEN1);
	}

}


void UART_Transmit(u8 data , UART_Channel_t uart)
{
	if (uart == UART0) {
		// Wait for empty transmit buffer for UART0
		while (!GET_BIT(UCSR0A, UDRE0));

		// Put data into buffer, sends the data for UART0
		UDR0 = data;
		} else if (uart == UART1) {
		// Wait for empty transmit buffer for UART1
		while (!GET_BIT(UCSR1A, UDRE1));

		// Put data into buffer, sends the data for UART1
		UDR1 = data;
	}
}
u8 UART_ReceiveData(UART_Channel_t uart) {
	if (uart == UART0) {
		// Wait for data to be received for UART0
		while (!GET_BIT(UCSR0A, RXC0));

		// Get and return received data from buffer for UART0
		return UDR0;
		} else if (uart == UART1) {
		// Wait for data to be received for UART1
		while (!GET_BIT(UCSR1A, RXC1));

		// Get and return received data from buffer for UART1
		return UDR1;
	}
	return 0;
}

/*
u8 UART_ReceiveData(UART_Channel_t uart, u16 timeout)
{
	if (uart == UART0) {
		// Wait for data to be received for UART0 with timeout
		while (!GET_BIT(UCSR0A, RXC0)) {
			if (timeout == 0) {
				return 0xFF; // Indicate timeout with a special value
			}
			timeout--;
		}

		// Get and return received data from buffer for UART0
		return UDR0;
		} else if (uart == UART1) {
		// Wait for data to be received for UART1 with timeout
		while (!GET_BIT(UCSR1A, RXC1)) {
			if (timeout == 0) {
				return 0xFF; // Indicate timeout with a special value
			}
			timeout--;
		}

		// Get and return received data from buffer for UART1
		return UDR1;
	}

	return 0xFF; // Return special value if UART channel is invalid
}

*/

u8  UART_ReceiveData_Periodic(u8 *data, UART_Channel_t uart) {  // The advantage of this design is that doesn't delay the rest of code
	if (uart == UART0) {
		if (GET_BIT(UCSR0A, RXC0)) {
			*data = UDR0;
			return 1;
		}
		} else if (uart == UART1) {
		if (GET_BIT(UCSR1A, RXC1)) {
			*data = UDR1;
			return 1;
		}
	}
	return 0;
}

void UART_SendData_NO_BLOCK(u8 data, UART_Channel_t uart) {
	if (uart == UART0) {
		// Put data into buffer, sends the data for UART0
		UDR0 = data;
		} else if (uart == UART1) {
		// Put data into buffer, sends the data for UART1
		UDR1 = data;
	}
}

u8 UART_ReceiveData_NO_BLOCK(UART_Channel_t uart) {
	if (uart == UART0) {
		// Return received data from buffer for UART0
		return UDR0;
		} else if (uart == UART1) {
		// Return received data from buffer for UART1
		return UDR1;
	}
	return 0;
}

void UART_RX_Interrupt_Enable(UART_Channel_t uart) {
	if (uart == UART0) {
		SET_BIT(UCSR0B, RXCIE0); // Enable RX complete interrupt for UART0
		} else if (uart == UART1) {
		SET_BIT(UCSR1B, RXCIE1); // Enable RX complete interrupt for UART1
	}
}

void UART_RX_Interrupt_Disable(UART_Channel_t uart) {
	if (uart == UART0) {
		CLEAR_BIT(UCSR0B, RXCIE0); // Disable RX complete interrupt for UART0
		} else if (uart == UART1) {
		CLEAR_BIT(UCSR1B, RXCIE1); // Disable RX complete interrupt for UART1
	}
}

void UART_TX_Interrupt_Enable(UART_Channel_t uart) {
	if (uart == UART0) {
		SET_BIT(UCSR0B, TXCIE0); // Enable TX complete interrupt for UART0
		} else if (uart == UART1) {
		SET_BIT(UCSR1B, TXCIE1); // Enable TX complete interrupt for UART1
	}
}

void UART_TX_Interrupt_Disable(UART_Channel_t uart) {
	if (uart == UART0) {
		CLEAR_BIT(UCSR0B, TXCIE0); // Disable TX complete interrupt for UART0
		} else if (uart == UART1) {
		CLEAR_BIT(UCSR1B, TXCIE1); // Disable TX complete interrupt for UART1
	}
}


void UART_RX_SetCallback(void(*LocalFptr)(void) , UART_Channel_t uart)
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallback(void(*LocalFptr)(void) , UART_Channel_t uart)
{
	UART_TX_Fptr = LocalFptr;
}

ISR(UART_RX_vect)
{
	if (UART_RX_Fptr != Null_Ptr)
	{
		UART_RX_Fptr();
	}
}
ISR(UART_TX_vect)
{
	if (UART_TX_Fptr != Null_Ptr)
	{
		UART_TX_Fptr();
	}
}

/*
u16 UART_SendFrame_SW(u8 data)
{
u16 Frame=0;
u8 Parityflag = 0;
Frame = data << 1; // Start bit
// Parity Check Bit:
if (counterSetBits(data) == EVEN && (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1))  // the Second part can be deleted as you can set config file .h and .c
{
// Frame = 00000101 0
Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
Parityflag = 1;
}
else if (counterSetBits(data) == ODD && (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)) // the Second part can be deleted as you can set config file .h and .c
{
Frame = Frame | (ODD << (Data_Length + Start_Bit)) ;
Parityflag = 1;
}
else
{
Parityflag = 0;
Frame = Frame;
}
// Stop Bit:
if (Stop_Bits == 2 && (GET_BIT(UCSRC , USBS)))
{
if (Parityflag == 1)
{
Frame = Frame | (3 << (1 + Data_Length + Start_Bit)) ;
}
else if (Parityflag == 0)
{
Frame = Frame | (3 << (0 + Data_Length + Start_Bit)) ;
}

}
else if (Stop_Bits == 1 && (!GET_BIT(UCSRC , USBS)))  // the Second part can be deleted as you can set config file .h and .c
{
if (Parityflag == 1)
{
Frame = Frame | (1 << (1 + Data_Length + Start_Bit)) ;
}
else if (Parityflag == 0)
{
Frame = Frame | (1 << (0 + Data_Length + Start_Bit)) ;
}
}
return Frame;
}


// Function to counter the number of set bits  (ONES)
u8 counterSetBits(u16 num)
{
u8 counter = 0;
while (num) {
counter += num & 1;  // Add the last bit to the counter if it is 1
num >>= 1;         // Right shift the number to remove the processed bit
}

if (counter % 2 == 0)
{
return EvenParity;
}
else
return OddParity;
}

Parity_t UART_CheckParity(u8 data)
{
if (GET_BIT(UCSRC , UPM0) == 1 && GET_BIT(UCSRC , UPM1) == 1)
{
return ODD;
}
else if (GET_BIT(UCSRC , UPM0) == 0 && GET_BIT(UCSRC , UPM1) == 1)
{
return EVEN;
}
}
*/