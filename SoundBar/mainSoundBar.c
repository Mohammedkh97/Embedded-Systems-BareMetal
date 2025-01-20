/*
* ADC.c
*
* Created: 11/7/2023 2:27:17 AM
* Author : Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "LCD_Private.h"
#include "ADC_int.h"

u8 SoundBar[] = {
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};
int main(void)
{
	DIO_init();
	LCD_Init();
	KEYPAD_init();
	
	//LCD_WriteStr((u8*)"Mohammed Khalaf  ");
	// When using ADC, Make sure the DIO pins are INFREE
	ADC_init(VREF_VCC , ADC_SCALER_64);
	
	u16 AnalogValue, potValue = 0;
	/*LCD_SetCursor(2,1);
	LCD_WriteNumber(AnalogValue);*/
	/* Replace with your application code */

	while (1)
	{
		
		//Sound Bar:
		AnalogValue = ADC_Read(CH_0);
		potValue = (AnalogValue*(u32)100)/1023;
		customChar(SoundBar , 1);
		if (AnalogValue > 10)
		{
			LCD_SetCursor(1,1);
			LCD_WriteChar(1);
		}
		if (AnalogValue > 63)
		{
			u8 BarStart = AnalogValue / 63;
			for (u8 i = 1 ; i < BarStart ; i++)
			{
				LCD_SetCursor(1,i);
				LCD_WriteChar(1);
			}
		}
		else if (AnalogValue == 0)
		{
			LCD_SetCursor(1,1);
			LCD_WriteStr((u8*)"   ");
		}
		LCD_SetCursor(1,(AnalogValue/ 63));
		LCD_WriteChar(1);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,1);
		LCD_WriteStr((u8*)"Analog: ");
		LCD_WriteNumber(AnalogValue);
		LCD_WriteStr((u8*)"   ");
		LCD_SetCursor(2,14);
		LCD_WriteNumber(potValue);
		LCD_WriteChar('%');
		LCD_WriteStr((u8*)"   ");
	}
}

