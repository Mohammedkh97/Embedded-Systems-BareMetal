/*
 * USART_Services.c
 *
 *  Created on: Oct 30, 2024
 *  Author: Mohammed Khalaf
 */

#include "stdTypes.h"
#include "USART_Interface.h"

/* Synchronous Functions */

void USART_Transmit_String(USART_Channel_t USART_ID, u8 *String, u8 Terminator)
{
	u8 i = 0;
	while (String[i] != Terminator)
	{
		USART_void_Transmit_Byte(USART_ID, String[i]);
		i++;
	}
}

void USART_ReceiveString	 (USART_Channel_t USART_ID, u8 *String, u8 terminator ,u16 max_length)
{
	u16 i = 0;
	u8 received_char;

	// Receive first character
	received_char = USART_void_Receive_Byte(USART_ID);
	// Continue receiving characters until Enter is received or buffer is full
	while (received_char != terminator/* && i < (max_length - 1)*/) 	// '\r' is carriage return (Enter key)   ===> Enter char 0x0d
	{
		String[i++] = received_char;
		received_char = USART_void_Receive_Byte(USART_ID);
	}

	// Null-terminate the received string
	String[i] = '\0';

}
