/*
* Application_File.c
*
* Created: 05/06/2024 23:21:09
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "GPIO_interface.h"
#include "GLCD_ST7920_Interface.h"
#include "HX711_Config.h"
#include "Scale Configurations.h"
#include "../../HAL/LCD_TFT_ST7789v/TFT_Interface.h"


#include "stm32f1xx.h"


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

#if CALIBTRAION_MODE == MANUAL_CALIBRATION_MODE

//void hx711_delay_us(uint32_t us) {
//    uint32_t timer_ticks = (SystemCoreClock / 1000000) * us;
//    __HAL_TIM_SET_COUNTER(&htim1, 0);
//    HAL_TIM_Base_Start(&htim1);
//    while (__HAL_TIM_GET_COUNTER(&htim1) < timer_ticks);
//    HAL_TIM_Base_Stop(&htim1);
//}

u32 HX711_Read(void) {
	u32 counter;
	GPIO_void_SetPinMode1(HX711_DATA_PIN, DIO_OUTPUT_PUSHPULL_2MHZ);
	GPIO_void_Write_Pin_Method1(HX711_DATA_PIN, HIGH);
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
	counter = 0;
	GPIO_void_SetPinMode1(HX711_DATA_PIN, DIO_INPUT_FLOATING);
	while (GPIO_DIO_PinVoltage_Read_Pin_Method1(HX711_DATA_PIN));
	for (u8 i = 0; i < 24; i++) {
		GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, HIGH);
		counter = counter << 1;
		GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
		if (GPIO_DIO_PinVoltage_Read_Pin_Method1(HX711_DATA_PIN))
		counter++;
	}
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, HIGH);
	counter = counter ^ 0x800000;
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
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
	while (Count < 1000)
	{
		Count = HX711_Read();
		Count = Sample - Count;
	}
	//	LCD_Clear();
	GLCD_ST7920_SendString(1,0, (u8*)"Please Wait....       ");
	HAL_Delay(2000);
	for (int i = 0; i < 100; i++)
	{
		Count = HX711_Read();
		Val += Sample - Count;
	}
	Val = Val / 100.0;
	Val = Val / Calibration_Factor;  // put here your calibrating weight
	//LCD_Clear();
}f32 HX711_WeightRead(){	f32 weight = 0;	Count = HX711_Read();
	weight = (((Count - Sample) / Val) - 2 * ((Count - Sample) / Val));	return weight;}
#elif CALIBTRAION_MODE == ZERO_CALIBRATION_MODE

u32 HX711_Read(void) {
	u32 counter;
	GPIO_void_SetPinMode1(HX711_DATA_PIN, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_Write_Pin_Method1(HX711_DATA_PIN, HIGH);
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
	counter = 0;
	GPIO_void_SetPinMode1(HX711_DATA_PIN, DIO_INPUT_FLOATING);

	while (GPIO_DIO_PinVoltage_Read_Pin_Method1(HX711_DATA_PIN));
	for (u8 i = 0; i < 24; i++) {
		GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, HIGH);
//		HAL_Delay(1);
		counter = counter << 1;
		GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
//		HAL_Delay(1);
		if (GPIO_DIO_PinVoltage_Read_Pin_Method1(HX711_DATA_PIN))
		counter++;
	}
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, HIGH);
	counter = counter ^ 0x800000;
	GPIO_void_Write_Pin_Method1(HX711_SCK_PIN, LOW);
	return (counter);
}

void HX711_Calibrate(void) {
	// Zero Calibration (Tare)
	//LCD_Goto_WriteString(1,1,(u8*)"Calibrating....");
	//LCD_Goto_WriteString(2,1,(u8*)"Please Wait");

	GLCD_ST7920_SendString(0, 0, (u8*)"Calibrating...");
//	HTFT_voidWriteString(15, 0, (u8*) "Calibrating    ", COLOR_BLACK, COLOR_RED);
	GLCD_ST7920_SendString(1, 0, (u8*)"Please Wait...");
//	HTFT_voidWriteString(15, 5, (u8*) "\nPlease Wait..    ", COLOR_BLACK, COLOR_RED);
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
//	HTFT_voidWriteString(15, 5, (u8*) "\nPlease Wait..", COLOR_BLACK, COLOR_RED);
	GLCD_ST7920_SendString(1, 0, (u8*)"Done!");
//	HTFT_voidWriteString(15, 5, (u8*) "\nDone!        ", COLOR_BLACK, COLOR_RED);
	HAL_Delay(500);
	GLCD_ST7920_Clear();
}f32 HX711_WeightRead(){	f32 weight = 0;	Count = HX711_Read();
	weight = (((Count - Sample) / Val) - 2 * ((Count - Sample) / Val));	return weight;}
#endif
