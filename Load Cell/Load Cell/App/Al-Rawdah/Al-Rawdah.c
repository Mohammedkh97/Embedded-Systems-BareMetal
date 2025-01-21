/*
* Al-Rawdah.c
*
* Created: 05/07/2024 23:21:09
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

#include "Al-Rawdah.h"
#include "App_Services.h"

/************************************************************************/
/*				Global Variables                                        */
/************************************************************************/
u8 Exit = 1;
//u16 Holded_Weight = 0;

f32 cow_Weight;

/************************************************************************/
/*								 Flags                                  */
/************************************************************************/


#define F_CPU 16000000UL
#include <util/delay.h>

void setupInit()
{
	DIO_init();
	init_pins();
	//SPI_initMaster();
	GLCD_ST7920_init();
	DIO_initPin1(HX711_SCK_PIN, OUTPUT);
	EXI_init();
	EXI_Enable(EX_INT0);
	UART_Init(115200 , UART0);
	
	ENABLE_GLOBAL_INTERRUPT();
	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
	TCNT0 = 0;    // Initialize counter to 0
	TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt

	GLCD_ST7920_SendString(0, 0, (u8*)"Weight");
	GLCD_ST7920_SendString(1, 0, (u8*)"Measurement");

	_delay_ms(200);

	HX711_Calibrate();

}

void Application_Runnable(void) {
	
	cow_Weight = HX711_WeightRead();
	// 	GLCD_ST7920_SendString(0, 0, (u8*)"Measured Weight");
	// 	GLCD_ST7920_SendString(1, 0, (u8*)"Real Time Weight");
	if (cow_Weight < 0)
	{
		cow_Weight = 0;
	}
	GLCD_ST7920_WriteNumber(3,6,cow_Weight);
	f32 weight_in_KG = cow_Weight / 1000.0;
	GLCD_ST7920_WriteFloatNumber(3,0,weight_in_KG , 2);
	
	
	//  	floatToString(weight_KG, buffer, decimalPlaces); // Convert the float to a string
	//  	UART_TransmitString(buffer ,'\n', UART0);
	//Hold Value Using EXTI INT0
	/*
	while(!Exit)
	{
		//Holded_Weight = weight_KG;
		GLCD_ST7920_SendString(3, 0, (u8*)"Hold Val: ");
		GLCD_ST7920_WriteNumber(3,6,weight_in_KG);
		Exit = 1;
	}
	*/
	
	// Reset Calibration
	/*if (!DIO_ReadPin1(RESET_CALIBRATION)) {
	Val = 25.15; // Calibration Factor
	Sample = 0;
	weight = 0;
	counter = 0;
	calibrate();
	}*/
	_delay_ms(300);
}
/*
ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
	Exit = 0;
}
*/