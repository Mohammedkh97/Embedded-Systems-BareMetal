/*
* Application_File.c
*
* Created: 3/25/2024 1:12:12 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "DIO_interface.h"
#include "ADC_int.h"
#include "Timers.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "MOTOR_Interface.h"
#include "Application_File.h"
#include "Sensors_int.h"
#include "Sensors_Config.h"

#include "ConfigFile.h"

static u16 speedValue = 0 ,temp = 0;
void systemInit(void)
{
	DIO_init();
	LCD_Init();
	ADC_init(VREF_VCC,ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE , TIMER0_SCALER_8);
	TIMER0_OC0_PWM_Mode(OC0_PWM_CLEAR);
}
void systemRunnable()
{
	temp =LM35_Get_Temp();
	
	LCD_Goto_WriteString(2,1,(u8*)"Temp =");
	LCD_Goto_WriteNumber(2,7,temp);
	if (temp >30)
	{
		// Fan Rotates in Max Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_100) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);

		DIO_WritePin1(PINC0,HIGH);
	}
	
	else if ( temp >= 25 && temp <30)
	{
		// Fan Rotates in Upper Medium Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_80) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	
	else if (temp > 22 && temp <= 25)
	{
		//Fan Rotates in Medium Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_50) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	else if (temp >= 20 && temp <= 22)
	{
		//Fan Rotates in Slow Speed
		speedValue = (((u16)FASTPWM_MODE * Speed_25) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_CW(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	else if (temp < 20)
	{
		speedValue = (((u16)FASTPWM_MODE * Speed_Stop) / MAX_SPEED);
		OCR0 = speedValue;
		Motor_STOP(M1);
		LCD_Goto_WriteString(1,1,(u8*)"Fan Speed =");
		LCD_Goto_WriteNumber(1,13, speedValue);
		DIO_WritePin1(PINC0,HIGH);
	}
	
	
}