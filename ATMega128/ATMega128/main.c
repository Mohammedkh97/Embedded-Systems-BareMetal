/*
* ATMega128.c
*
* Created: 6/23/2024 2:59:00 PM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "ADC_int.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "HX711_interface.h"
#include "UART.h"
#include "SPI.h"
#include "GLCD_ST7920.h"
#define F_CPU 16000000UL
#include <util/delay.h>
int main(void)
{
	/* Replace with your application code */
	DIO_init();
	LCD_Init();
	init_pins();
	GLCD_ST7920_init();
	LCD_Goto_WriteString(1,1,(u8*)"Master: ");
	
	while (1)
	{
		
	}

}

