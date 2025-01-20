/*
* Schedular.c
*
* Created: 2/21/2024 9:08:46 PM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "ADC_int.h"

#include "SegmentDisplay.h"
#include "MOTOR_Interface.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "KEYPAD_int.h"
#include "Sensors_int.h"

#include "Ex_int.h"
#include "SERVO_int.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Ultrasoinc.h"
#include "UART.h"
#include "UART_Services.h"
#include "UART_Stack.h"

#include "OS.h"
#include "Tasks.h"

#define F_CPU 8000000UL
#include <util/delay.h>

volatile static u16 interrupt_Counter = 1;
volatile static u16 MillisCounter = 1;

void vMillisIncrement(void)
{
	if(interrupt_Counter >= 10)
	{
		interrupt_Counter = 1;
		MillisCounter++;
	}
	if (MillisCounter >= 1000)
	{
		MillisCounter = 1;
		OS_Task_Handler();
	}
	interrupt_Counter++;
}

void init_Scheduler(void)
{
	/*Initialize TIMER0 at: 1M Hz, Prescaler: 8, OverFlow every 100uSec */
	TIMER0_Init(TIMER0_NORMAL_MODE , TIMER0_SCALER_8);
	TIMER0_OC0_non_PWM_Mode(OC0_DISCONNECTED);
	TIMER0_OV_InterruptEnable();
	TIMER0_OV_SetCallBack(vMillisIncrement);
	
	/*Creation of Tasks*/
	OS_TaskCreate(Task_1S_LcdUpdate,  1 , BLOCKED);
	OS_TaskCreate(Task_2S_Blink ,     2 , BLOCKED);
	OS_TaskCreate(Task_3S_Blink ,     3 , BLOCKED);
		
}
void vInitEcu(void)
{
	u8 *str = "Seconds: ";
	sei();
	DIO_init();
	DIO_initPin1(PINB0,OUTPUT);
	DIO_initPin1(PINB2,OUTPUT);

	DIO_WritePin1(PINB0,LOW);
	DIO_WritePin1(PINB2,LOW);



	LCD_Init();
	LCD_Goto_WriteString(1,1,str);

}

int main(void)
{
	vInitEcu();
	//init_Scheduler();	
	
	/* Replace with your application code */
	while (1)
	{
		//OS_TaskExecution();
	}
}

