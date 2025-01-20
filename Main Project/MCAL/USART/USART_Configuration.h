/*
 * USART_Configuration.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mohammmed Khalaf
 */

#ifndef USART_USART_CONFIGURATION_H_
#define USART_USART_CONFIGURATION_H_

// Assuming a system clock frequency of 72 MHz (for STM32F103C8)
#define F_CPU 						(72000000U)

#define USART_OVERSAMPLING_BY_8			8
#define USART_OVERSAMPLING_BY_16		16

#define USART_SCALER		USART_OVERSAMPLING_BY_16      // The oversampling factor used by the USART hardware.


#define PCLK2_FREQUENCY 72000000 // Example for 72 MHz PCLK2
#define PCLK1_FREQUENCY 36000000 // Example for 36 MHz PCLK1 (with a prescaler of 2)

/************************************************************************/
/*						USART PINS DESCRIBTION                           */
/************************************************************************/

#define RXD1		PINA10
#define TXD1		PINA9

//#define RXD1		PINB7
//#define TXD1		PINB6

#define RXD2		PINA3
#define TXD2		PINA2

#define RXD3		PINB11
#define TXD3		PINB10


#define TERMINATOR '='
//#define NULL '\0'

#define Start_of_frame 0
#define frame_size 18

#define MAX_STRING_LENGTH 500  // Define a maximum length for the received string
#endif /* USART_USART_CONFIGURATION_H_ */
