/*
 * USART_Interface.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mohammed Khalaf
 */

#ifndef USART_USART_INTERFACE_H_
#define USART_USART_INTERFACE_H_

typedef enum
{
	USART_1,
	USART_2,
	USART_3
}USART_Channel_t;

typedef enum {
    USART_MODE_RX 		= 0x01,   	// Receive mode
    USART_MODE_TX 		= 0x02,   	// Transmit mode
    USART_MODE_TX_RX 	= 0x03 		// Transmit and receive mode
} USART_Mode_t;

typedef enum {
    USART_PARITY_NONE = 0x00,
    USART_PARITY_EVEN = 0x01,
    USART_PARITY_ODD  = 0x02
} USART_Parity_t;

typedef enum {
    USART_WORDLENGTH_8_BITS,
    USART_WORDLENGTH_9_BITS
} USART_WordLength_t;

typedef enum {
    USART_STOPBITS_1,
    USART_STOPBITS_2,
	USART_HALF_STOPBITS,
	USART_ONE_HALF_STOP_BIT
} USART_StopBits_t;

typedef enum {
	IDLE_LINE,
	ADDRESS_MARK

}USART_WakeupMethod_t;

typedef struct {
    u32 BaudRate;              		 // UART baud rate
    USART_Mode_t Mode;               // UART mode (TX, RX, or both)
    USART_WordLength_t WordLength;   // Word length (8 bits or 9 bits)
    USART_Parity_t Parity;           // Parity (None, Even, Odd)
    USART_StopBits_t StopBits;       // Stop bits (1 or 2)
} USART_Config_t;

void USART_void_Initializtion(USART_Channel_t USART_ID, USART_Mode_t Mode, USART_Parity_t Parity, USART_StopBits_t Stop_Bits, USART_WordLength_t Word_Length, u32 Baud_Rate);
void USART_void_Transmit_Byte(USART_Channel_t USART_ID, u8 Data);
u8 USART_void_Receive_Byte(USART_Channel_t USART_ID);
void USART_receiveStringUntil2term_timeout(u8 *string, USART_Channel_t USART_ID, const u8 *terminator1, const u8 *terminator2, u32 timeout);
void USART_receiveFrame(u8 *string,USART_Channel_t USART_ID,u8 start,u8 Frame_size);
u8 USART_isDataAvailable(USART_Channel_t USART_ID);

#endif /* USART_USART_INTERFACE_H_ */
