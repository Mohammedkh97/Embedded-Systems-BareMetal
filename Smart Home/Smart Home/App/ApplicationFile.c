/*
* ApplicationFile.c
*
* Created: 1/23/2024 1:40:10 AM
* Author: Mohammed Khalaf
*/
#include "stdTypes.h"
#include "ApplicationFile.h"
#include "ApplicationServices.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "SERVO_int.h"
#include "RGB.h"
#include "UART.h"
#include "UART_Services.h"
#include "KEYPAD_int.h"

#define F_CPU 8000000UL
#include <util/delay.h>

static u8 shape[] = {
	0x10,
	0x18,
	0x0C,
	0x06,
	0x0C,
	0x18,
	0x10,
	0x00
};
static u8 requestedString[20];
static u8 splittedString[20];
static u8 Selected_RGB_LED;
static u8 rgb_num;
static u8 Get_RGB_Color;
Room_t Room = None;
color_t RGB_color;
u16 i = 0;

static tasks_t SmartHomeTasks[Num_Of_Tasks] =
{
	{(u8*)"Room Light ON" , LED_Room_ON},
	{(u8*)"Room Light OFF", LED_Room_OFF},
	{(u8*)"Set Servo Angle", SERVO_WriteAngle},
	{(u8*)"Room Light RGB", RGB_Show_Room}
};

void Smart_Home_init()
{
	DIO_init();
	LCD_Init();
	UART_init();
	//Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8);
	//Timer1_OCRA1Mode(OCRA_CLEAR);
	TIMER0_Init(TIMER0_FASTPWM_MODE , TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_SET);
	Timer1_OCRB1Mode(OCRB_CLEAR);
	//TIMER0_OC0Mode(OC0_CLEAR);
	TIMER0_OC0_PWM_Mode(OC0_CLEAR);
	ICR1 = 19999;
	LCD_Goto_WriteString(1,1,((u8*)"      Welcome"));
	LCD_Goto_WriteString(2,1,((u8*)"     Smart Home"));

	
}

void Smart_Home_Runnable()
{
	u8 Task_Function_argument = 0 , i = 0 ;
	UART_ReceiveString((u8*)requestedString);
	//LCD_Goto_WriteString(1,1,(u8*)requestedString);
	//_delay_ms(5000);
	//									         ROOM Light ON 1 , ROOM Light ON
	Task_Function_argument = string_Number_Split(requestedString , splittedString);
	
	for (i = 0 ; i < Num_Of_Tasks ; i++)
	{
		if (stringCompare(splittedString , SmartHomeTasks[i].Function_Name) == MATCHED)
		{
			LCD_Clear();
			LCD_Goto_WriteString(2,2,(u8*)"	  Valid Data!");
			SmartHomeTasks[i].fptr(Task_Function_argument);
			break;
		}
		else
		{
			LCD_Clear();
			LCD_Goto_WriteString(2,2,(u8*)"  Invalid Data!");
		}
	}
}

void LED_Room_ON(u8 LED_NUM)
{
	Room = LED_NUM;
	switch(Room)
	{
		case Room_Light_1:
		DIO_WritePin1(PINC4 , HIGH);
		break;
		case Room_Light_2:
		DIO_WritePin1(PINC5 , HIGH);
		break;
		case Room_Light_3:
		DIO_WritePin1(PINC6 , HIGH);
		break;
		case Room_Light_4:
		DIO_WritePin1(PINC7 , HIGH);
		break;
		case None:
		/*No Room Selected*/
		break;
	}
	
}

void LED_Room_OFF(u8 LED_NUM)
{
	Room = LED_NUM;
	switch(Room)
	{
		case Room_Light_1:
		DIO_WritePin1(PINC4 , LOW);
		break;
		case Room_Light_2:
		DIO_WritePin1(PINC5 , LOW);
		break;
		case Room_Light_3:
		DIO_WritePin1(PINC6 , LOW);
		break;
		case Room_Light_4:
		DIO_WritePin1(PINC7 , LOW);
		break;
		case None:
		/*No Room Selected*/
		break;
	}
}

// SERVO_WriteAngle(u8 angle)

u8 RGB_Select(void)
{
	u8 EnterFlag = 0;
	LCD_Clear();
	LCD_Goto_WriteString(1,1,(u8*)" RGB Light Show");
	LCD_Draw_Character(shape);
	_delay_ms(1000);
	LCD_Clear();
	LCD_Goto_WriteString(1,1, (u8*)"   Please Select");
	LCD_Goto_WriteString(2,1, (u8*)" LED from RGB List");
	
	while(EnterFlag == 0)
	{
		rgb_num = KEYPAD_GetKey();
		if (rgb_num >= '1' && rgb_num <= '7' && rgb_num != NO_KEY)
		{
			// Get the RGB LED from RGB List as an integer number:
			Selected_RGB_LED = (rgb_num - '0') - 1;
			//LCD_Goto_WriteNumber(4,1,Selected_RGB_LED);
			EnterFlag = 1;
		}
	}
	return rgb_num;
}

void RGB_Color_Selection(void)
{
	u8 EnterFlag = 0;
	LCD_Clear();
	LCD_Goto_WriteString(1,1, (u8*)"1. WHITE 2. BLACK");
	LCD_Goto_WriteString(2,1, (u8*)"3. RED   4. GREEN");
	LCD_Goto_WriteString(3,1, (u8*)"5. BLUE  6. YELLOW");
	LCD_Goto_WriteString(4,1, (u8*)"7. CYAN  8. MAGENTA");
	while(EnterFlag == 0)
	{
		Get_RGB_Color = KEYPAD_GetKey();
		if (Get_RGB_Color >= '1' && Get_RGB_Color <= '8' && Get_RGB_Color != NO_KEY)
		{
			// Get the RGB LED Color as RGB Color List arrangement:
			RGB_color = (Get_RGB_Color - '0');
			//LCD_Goto_WriteNumber(4,1,Selected_RGB_LED);
			EnterFlag = 1;
		}
		else if(Get_RGB_Color == '0')
		{
			LCD_Goto_WriteString(1,1, (u8*)"Wrong Entered color");
			
		}
	}
	RGB(Selected_RGB_LED , RGB_color);
}

void RGB_Show_Room(u8 RGB_Room_Num)
{
	RGB_Select();
	RGB_Color_Selection();
	
	Room = RGB_Room_Num;
	switch(Room)
	{
		case Room_Light_1:
		RGB(Selected_RGB_LED , RGB_color);
		break;
		case Room_Light_2:
		RGB(Selected_RGB_LED , RGB_color);
		break;
		case Room_Light_3:
		RGB(Selected_RGB_LED , RGB_color);
		break;
		case Room_Light_4:
		RGB(Selected_RGB_LED , RGB_color);
		break;
		case None:
		/*No Room Selected*/
		break;
	}
}

/*
void RGB_Handler(u8 RGB_Room_Num)
{
Room = RGB_Room_Num;
switch(Room)
{
case Room_Light_1:
RGB_Show_Room(RGB_Room_Num);
break;
case Room_Light_2:
RGB_Show_Room(RGB_Room_Num);
break;
case Room_Light_2:
RGB_Show_Room(RGB_Room_Num);
break;
}


}*/