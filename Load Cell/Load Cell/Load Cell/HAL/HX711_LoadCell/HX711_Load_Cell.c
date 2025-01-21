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
#include "HX711_Config.h"
#include "Scale Configurations.h"

/************************************************************************/
/*            Determined Configurations                                 */
/************************************************************************/

#if CALIBTRAION_MODE == MANUAL_CALIBRATION_MODE
static volatile f32 Val = NONE_ZERO_CALIBRATION;
static volatile f32 Calibration_Factor = CALIBRATION_FACTOR;
#elif CALIBTRAION_MODE == ZERO_CALIBRATION_MODE
static volatile f32 Val = SCALE_TYPE;
#endif

static volatile s32 Sample = 0;
static volatile s32 Count = 0;

#define F_CPU 16000000UL
#include <util/delay.h>

#if CALIBTRAION_MODE == MANUAL_CALIBRATION_MODE

u32 HX711_Read(void) {
	u32 counter;
	DIO_initPin1(HX711_DATA_PIN, OUTPUT);
	DIO_WritePin1(HX711_DATA_PIN, HIGH);
	DIO_WritePin1(HX711_SCK_PIN, LOW);
	counter = 0;
	DIO_initPin1(HX711_DATA_PIN, INFREE);
	while (DIO_ReadPin1(HX711_DATA_PIN));
	for (u8 i = 0; i < 24; i++) {
		DIO_WritePin1(HX711_SCK_PIN, HIGH);
		counter = counter << 1;
		DIO_WritePin1(HX711_SCK_PIN, LOW);
		if (DIO_ReadPin1(HX711_DATA_PIN))
		counter++;
	}
	DIO_WritePin1(HX711_SCK_PIN, HIGH);
	counter = counter ^ 0x800000;
	DIO_WritePin1(HX711_SCK_PIN, LOW);
	return (counter);
}
void HX711_Calibrate(void) {
	GLCD_ST7920_SendString(0, 0, (u8*)"Calibrating...           ");
	GLCD_ST7920_SendString(1, 0, (u8*)"Please Wait...           ");
	for (u8 i = 0; i < 100; i++) {
		Count = HX711_Read();
		Sample += Count;
	}
	Sample /= 100;
	GLCD_ST7920_SendString(0, 0, (u8*)"                ");
	GLCD_ST7920_SendString(1, 0, (u8*)"                ");
	GLCD_ST7920_SendString(0, 0, (u8*)"Put 1kg & wait");
	Count = 0;
	while (Count < 1000) {
		Count = HX711_Read();
		Count = Sample - Count;
	}
	//	LCD_Clear();
	GLCD_ST7920_SendString(1,0, (u8*)"Please Wait....       ");
	_delay_ms(2000);
	for (int i = 0; i < 100; i++)
	{
		Count = HX711_Read();
		Val += Sample - Count;
	}
	Val = Val / 100.0;
	Val = Val / Calibration_Factor;  // put here your calibrating weight
	//LCD_Clear();
}f32 HX711_WeightRead(){	f32 weight = 0;	Count = HX711_Read();
	weight = (((Count - Sample) / Val) - 2 * ((Count - Sample) / Val));		return weight;}#elif CALIBTRAION_MODE == ZERO_CALIBRATION_MODE

u32 HX711_Read(void) {
	u32 counter;
	DIO_initPin1(HX711_DATA_PIN, OUTPUT);
	DIO_WritePin1(HX711_DATA_PIN, HIGH);
	DIO_WritePin1(HX711_SCK_PIN, LOW);
	counter = 0;
	DIO_initPin1(HX711_DATA_PIN, INFREE);
	while (DIO_ReadPin1(HX711_DATA_PIN));
	for (u8 i = 0; i < 24; i++) {
		DIO_WritePin1(HX711_SCK_PIN, HIGH);
		counter = counter << 1;
		DIO_WritePin1(HX711_SCK_PIN, LOW);
		if (DIO_ReadPin1(HX711_DATA_PIN))
		counter++;
	}
	DIO_WritePin1(HX711_SCK_PIN, HIGH);
	counter = counter ^ 0x800000;
	DIO_WritePin1(HX711_SCK_PIN, LOW);
	return (counter);
}

void HX711_Calibrate(void) {
	// Zero Calibration (Tare)
	//LCD_Goto_WriteString(1,1,(u8*)"Calibrating....");
	//LCD_Goto_WriteString(2,1,(u8*)"Please Wait");
	GLCD_ST7920_SendString(0, 0, (u8*)"Calibrating...");
	GLCD_ST7920_SendString(1, 0, (u8*)"Please Wait...");
	Sample = 0;
	for (u8 i = 0; i < 100; i++) 
	{
		Count = HX711_Read();
		Sample += Count;
	}
	
	Sample /= 100.0;
	
	//LCD_Goto_WriteString(1, 1, (u8*)"Zero Calibration");
	//LCD_Goto_WriteString(2, 1, (u8*)"Done!");
	GLCD_ST7920_SendString(0, 0, (u8*)"Zero Calibration");
	GLCD_ST7920_SendString(1, 0, (u8*)"Done!");
	_delay_ms(500);
	GLCD_ST7920_Clear();
}f32 HX711_WeightRead(){	f32 weight = 0;	Count = HX711_Read();
	weight = (((Count - Sample) / Val) - 2 * ((Count - Sample) / Val));		return weight;}
#endif