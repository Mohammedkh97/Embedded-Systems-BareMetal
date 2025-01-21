/*
* MainApp.c
*
* Created: 01/09/2024 12:42:47
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "DIO_interface.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "GLCD_ST7920.h"
#include "HX711_Load_Cell.h"
#include "HX711_Config.h"
#include "Scale Configurations.h"
#include "Ex_int.h"
#include "LCD_Private.h"
#include "SPI.h"
#include "UART.h"
#include "UART_Services.h"
#include "Timers.h"

#define F_CPU 16000000UL
#include <util/delay.h>

//u8 receivedString[10];

// void UART_SendCommand(const char *cmd)
// {
// 	UART_TransmitString(cmd, UART0);
// 	UART_TransmitString("\r\n", UART0);

void sysInit()
{
	DIO_init();
	init_pins();
	//SPI_initMaster();
	GLCD_ST7920_init();
	DIO_initPin1(HX711_SCK_PIN, OUTPUT);
	EXI_init();
	EXI_Enable(EX_INT0);
	UART_Init(115200 , UART0);
	//
// 	ENABLE_GLOBAL_INTERRUPT();
// 	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
// 	TCNT0 = 156;    // Initialize counter to 0
// 	TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt
// 	HX711_Calibrate();
// 	u8 receivedString[50];
GLCD_ST7920_SendString(0, 0 , (u8*)"Welcome");
}
void sysRunnable()
{
	
}