/*
* Tasks.c
*
*  Created on: May 7, 2021
*      Author: Zack
*/


#include "Tasks.h"
#include <util/delay.h>
#include "MemoryMap.h"
#include "stdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "ADC_int.h"
#include "Sensors_int.h"
#include "Ex_int.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "SERVO_int.h"
#include "Ultrasonic_Config.h"
#include "UART_Services.h"
#include "UART.h"
#include "SPI.h"


void Task_2S_Blink(void)
{
	DIO_TogglePin(PINB0);
}


void Task_1S_LcdUpdate(void)
{
	static u8 num = 0;
	LCD_Goto_WriteNumber(1 , 6, num);
	num++;
}

void Task_3S_Blink(void)
{
	DIO_TogglePin(PINB2);
}
