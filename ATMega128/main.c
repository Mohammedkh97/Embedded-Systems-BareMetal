/*
* ATMega128.c
*
* Created: 6/23/2024 2:59:00 PM
* Author : Mohammed Khalaf
*/

//#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/*

#define LCD_RS PC0
#define LCD_E  PC1
#define LCD_D4 PC4
#define LCD_D5 PC5
#define LCD_D6 PC6
#define LCD_D7 PC7

void LCD_init();
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_string(char *str);
void LCD_clear();
void LCD_setCursor(unsigned char row, unsigned char column);
*/

#include "stdTypes.h"
#include "ADC_int.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "GLCD_12864b_Interface.h"
#include "HX711_interface.h"


int main(void)
{
	/* Replace with your application code */
	
	DIO_init();
	LCD_Init();
	ADC_init(VREF_VCC,ADC_SCALER_128);

	u16 adc_value1 , adc_value2;
	
	u8 i = 0;
	while (1)
	{
		adc_value1 = ADC_Read(DIFF_1_0_GAIN_200);
		adc_value2 = ADC_Read(CH_1);
		
		//u16 voltage = (((f32)adc_value1 / 1024) * 5);
		
		LCD_Goto_WriteNumber(1,1,adc_value1);
		LCD_Goto_WriteNumber(2,1,adc_value2);
		_delay_ms(100);

	}
}

