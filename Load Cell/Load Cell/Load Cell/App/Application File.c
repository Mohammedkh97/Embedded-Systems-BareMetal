/*
* Application_File.c
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
#include "Application File.h"
#include "App_Consideration.h"


/************************************************************************/
/*				Global Variables                                        */
/************************************************************************/
u8 exitFlag = 1;
//u16 Holded_Weight = 0;
u8 buffer[16];
u8 decimalPlaces = 3;

f32 weight;
f32 currentWeight = 0;
f32 previousWeight = 0;

f32 avgSpecies= SPEC_AVG;
u16 countAvg = 0;
u16 tempCountAvg = 0;
s32 Strange_Spec_Weight = 0;
u16 Strange_Spec_Count  = 0;
u16 totalCounts = 0;
/************************************************************************/
/*								 Flags                                  */
/************************************************************************/
u8 normalFlag = 0;
u8 i = 0;
#define F_CPU 16000000UL
#include <util/delay.h>

void setup()
{
	DIO_init();
	LCD_Init(); // Assuming LCD_Init() initializes the LCD
	init_pins();
	//SPI_initMaster();
	GLCD_ST7920_init();
	DIO_initPin1(HX711_SCK_PIN, OUTPUT);
	EXI_init();
	EXI_Enable(EX_INT0);
	UART_Init(9600 , UART0);
	ENABLE_GLOBAL_INTERRUPT();
	
	// 	LCD_Clear();
	// 	_delay_ms(1000);
	// 	LCD_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*)"Weight");
	GLCD_ST7920_SendString(1, 0, (u8*)"Measurement");
	//LCD_Goto_WriteString(1,1,(u8*)"Weight Meausure");
	_delay_ms(300);
	// 	LCD_Clear();
	
	HX711_Calibrate();

}

void systemRunnable(void) {
	
	weight = HX711_WeightRead();
// 	GLCD_ST7920_SendString(0, 0, (u8*)"Measured Weight");
// 	GLCD_ST7920_SendString(1, 0, (u8*)"Real Time Weight");
	if (weight < 0)
	{
		weight = 0;
	}
 	GLCD_ST7920_WriteNumber(3,6,weight);
 	f32 weight_KG = weight / 1000.0;
 	GLCD_ST7920_WriteFloatNumber(3,0,weight_KG , 2);

 	countAvg = normalCountSpecies(weight);
 	GLCD_ST7920_SendString(0, 0, (u8*)"NormalSpec= ");
 	GLCD_ST7920_WriteNumber(0, 6, countAvg);
 	
 	Strange_Spec_Count = detectStrangeSpecies(weight);
 	GLCD_ST7920_SendString(1, 0, (u8*)"Strange = ");
 	GLCD_ST7920_WriteNumber(1, 6, Strange_Spec_Count);
	
 	totalCounts = countAvg + Strange_Spec_Count;
 	GLCD_ST7920_SendString(2,0,(u8*)"Total = ");
 	GLCD_ST7920_WriteNumber(2,6,totalCounts);
	
 	floatToString(weight_KG, buffer, decimalPlaces); // Convert the float to a string
 	UART_TransmitString(buffer ,'\n', UART0);
	
	//Hold Value Using EXTI INT0
	while(!exitFlag)
	{
		//Holded_Weight = weight_KG;
		GLCD_ST7920_SendString(3, 0, (u8*)"Hold Val: ");
		GLCD_ST7920_WriteNumber(3,6,weight_KG);
		exitFlag = 1;
	}
	
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

u16 normalCountSpecies(f32 currentWeight)
{
	u16 Counts = 0;
	//Counts = currentWeight / (avgSpecies - SPEC_VARIANCE);
	//if ((((avgSpecies - SPEC_VARIANCE) <= currentWeight) || (currentWeight <= (avgSpecies + SPEC_VARIANCE))) || (currentWeight <= (avgSpecies + SPEC_VARIANCE)) || (currentWeight <= (avgSpecies - SPEC_VARIANCE)))
	while((currentWeight > (avgSpecies + SPEC_VARIANCE )) /*|| (currentWeight > (avgSpecies - SPEC_VARIANCE))*/)
	{
		tempCountAvg = currentWeight / (avgSpecies - SPEC_VARIANCE);
		Counts = Counts + 1;
		currentWeight = currentWeight - avgSpecies;
		
		if (currentWeight >= (avgSpecies + STRANGE_VARIANCE_0) && currentWeight <= (avgSpecies + STRANGE_VARIANCE_1))
		{
			Counts = Counts - 1;
		}
		
		
	}
	return Counts;
}

u16 detectStrangeSpecies(f32 currentWeight)
{
	u16 strangeSpecCount = 0;
	//weight = HX711_WeightRead();
	while(currentWeight >= (avgSpecies + STRANGE_VARIANCE_1) || currentWeight >= (avgSpecies + STRANGE_VARIANCE_0))
	{
		if ((currentWeight >= (avgSpecies + STRANGE_VARIANCE_0)) && (currentWeight <= (avgSpecies + STRANGE_VARIANCE_1)))
		{
			strangeSpecCount = strangeSpecCount + 1;
		}
		currentWeight = currentWeight - (avgSpecies + SPEC_VARIANCE);
	}
	return strangeSpecCount;
}

ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
	exitFlag = 0;
}
