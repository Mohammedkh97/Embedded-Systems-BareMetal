/*
 * Temperature Controlled DC Fan.c
 *
 * Created: 4/4/2024 2:41:33 AM
 * Author : Mohammed Khalaf
 */ 


#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "ADC_int.h"
#include "MOTOR_Interface.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"
#include "Sensors_int.h"
#include "Ex_int.h"
#include "SERVO_int.h"
#include "Timers.h"
#include "UART.h"
#include "ConfigFile.h"

#include "Application_File.h"

#define F_CPU 8000000UL
#include <util/delay.h>



int main(void)
{
systemInit();
	
	
	while (1)
	{
		systemRunnable();
	}

}
