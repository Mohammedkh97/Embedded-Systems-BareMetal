/*
 * USART_Services.h
 *
 *  Created on: Oct 30, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef USART_SERVICES_USART_SERVICES_H_
#define USART_SERVICES_USART_SERVICES_H_

void USART_Transmit_String(USART_Channel_t USART_ID, u8 *String, u8 Terminator);
void USART_ReceiveString	 (USART_Channel_t SUART_ID, u8 *String, u8 terminator ,u16 max_length);
//void USART_ReceiveString_DockLight(u8*str , UART_Channel_t uart);   // Using DockLight
//void USART_SendNumber(u32 num , UART_Channel_t uart);
//u32 USART_ReceiveNumber1(UART_Channel_t uart);
//void USART_ReceiveNumber2(u32*pnum , UART_Channel_t uart);
//
//void USART_SendStringCheckSum(u8 *str, UART_Channel_t uart);
//u8 USART_ReceiveStringCheckSum(u8 *str, UART_Channel_t uart);
//void Tx_Function_Asynchronous(UART_Channel_t uart);
//void UART_SendStringAsynchronous(u8 *str, UART_Channel_t uart);
//void UART_SendStringAsynchronous_NO_BLOCK(u8* str , UART_Channel_t uart);



#endif /* USART_SERVICES_USART_SERVICES_H_ */
