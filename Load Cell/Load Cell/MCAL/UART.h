/*
 * UART.h
 *
 * Created: 7/21/2023 2:20:48 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UART_H_
#define UART_H_

typedef enum
{
	UART0,
	UART1	
}UART_Channel_t;

//void UART_init(void);
void UART_Init(u32 baud_rate, UART_Channel_t uart);
void UART_Transmit(u8 data , UART_Channel_t uart);
void UART_SendData_NO_BLOCK(u8 data, UART_Channel_t uart);

u8 UART_ReceiveData(UART_Channel_t uart);
u8 UART_ReceiveData_NO_BLOCK(UART_Channel_t uart);
u8 UART_ReceiveData_Periodic(u8 *data, UART_Channel_t uart);


void UART_RX_Interrupt_Enable(UART_Channel_t uart);
void UART_RX_Interrupt_Disable(UART_Channel_t uart);
void UART_TX_Interrupt_Enable(UART_Channel_t uart);
void UART_TX_Interrupt_Disable(UART_Channel_t uart);


void UART_RX_SetCallback(void(*LocalFptr)(void) , UART_Channel_t uart);

void UART_TX_SetCallback(void(*LocalFptr)(void) , UART_Channel_t uart);


#endif /* UART_H_ */