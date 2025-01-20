/*
 * ApplicationFile.h
 *
 * Created: 1/23/2024 1:41:01 AM
 *  Author: Mohamed
 */ 

							        
/**************************************************  Header File Guard  **************************************************/
#ifndef APPLICATIONFILE_H_
#define APPLICATIONFILE_H_
/******************************************************** Inclusion ************************************************************/

/* Utils libraries */
#include "stdTypes.h"
#include "MemoryMap.h"

/* MCAL Modules Inclusions */
#include "DIO_interface.h"
#include "ADC_int.h"
#include "Timers.h"
#include "Ex_int.h"
#include "UART.h"

/* HAL Modules Inclusions */
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "MOTOR_Interface.h"

#define		Num_Of_Tasks   4

typedef struct
{
	u8 *Function_Name;
	void (*fptr)(u8 functionNum);
	
}tasks_t;

typedef enum
{
	None,
	Room_Light_1,
	Room_Light_2,
	Room_Light_3,
	Room_Light_4
}Room_t;

void Smart_Home_init();
void Smart_Home_Runnable();
void LED_Room_ON(u8 LED_NUM);
void LED_Room_OFF(u8 LED_NUM);
void RGB_Show_Room(u8 RGB_Room_Num);
void RGB_Color_Selection(void);
u8 RGB_Select(void);
//void RGB_Handler(u8 RGB_Room_Num);

#endif /* APPLICATIONFILE_H_ */