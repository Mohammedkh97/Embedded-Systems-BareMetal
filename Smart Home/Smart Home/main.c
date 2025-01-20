/*
* Smart Home.c
*
* Created: 1/22/2024 10:12:41 PM
* Author : Mohammed Khalaf
*/
#include "stdTypes.h"
#include "MemoryMap.h"
#include "ADC_int.h"
#include "DIO_interface.h"
#include "LCD_int.h"
#include "KEYPAD_int.h"
#include "ApplicationFile.h"
#include "ApplicationServices.h"

#define F_CPU 8000000UL
#include <util/delay.h>

/*
u8 shape[] = {
0x10,
0x18,
0x0C,
0x06,
0x0C,
0x18,
0x10,
0x00
};
*/

int main(void)
{
	Smart_Home_init();
	
	/* Replace with your application code */

	//LCD_Draw_Character(shape);
	
	//RGB_Select();
	//RGB_Color_Selection();
	u8 key;
	while (1)
	{
		Smart_Home_Runnable();
		/*key = KEYPAD_GetKey();
		if (key>='0' && key <= '7' && key != NO_KEY)
		{
		LCD_Goto_WriteCharacter(4,1,key);
		}*/
		/*key = RGB_Select();
		LCD_Goto_WriteCharacter(4,6,key);
		_delay_ms(5000);*/
		//RGB_Color_Selection();
	}
}

