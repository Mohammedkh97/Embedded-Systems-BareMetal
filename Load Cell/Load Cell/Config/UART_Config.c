/*
* UART_Config.c
*
* Created: 6/22/2023 3:14:15 AM
*  Author: Mohamed Khalaf
*/

#include "MemoryMap.h"
#include "UART_Config.h"
#include "Utils.h"


void configureUART() {
	#if Parity_Type == EvenParity
	CLEAR_BIT(UCSR0C, UPM00);
	SET_BIT(UCSR0C, UPM01);

	#elif Parity_Type == OddParity
	SET_BIT(UCSR0C, UPM00);
	SET_BIT(UCSR0C, UPM01);
	#endif

	// Stop bits
	#if Stop_Bits == ONE
	CLEAR_BIT(UCSR0C, USBS0);
	#elif Stop_Bits == TWO
	SET_BIT(UCSR0C, USBS0);
	#endif
}