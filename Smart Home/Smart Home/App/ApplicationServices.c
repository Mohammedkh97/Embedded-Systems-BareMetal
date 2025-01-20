/*
* ApplicationServices.c
*
* Created: 1/30/2024 11:41:51 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "LCD_int.h"
#include "LCD_Private.h"
#include "ApplicationServices.h"
#include "ApplicationFile.h"

#define F_CPU 8000000UL
#include <util/delay.h>


u8 string_Number_Split(u8 *requestedString , u8 *splittedString)
{
	u8 num = 0;
	u8 string[20] , spaceFlag = 0;
	u16 i = 0;
	for (i = 0; requestedString[i]; i++)   // ROOM Light ON 1
	{
		if (requestedString[i] == ' ')
		{
			spaceFlag++;
		}
		if (requestedString[i]>='0' && requestedString[i] <= '9')
		{
			num = num*10 + (requestedString[i] - '0');
		}
		else
		{
			if (spaceFlag == 3)
			{
				string[i] = 0;
			}
			else
			{
				string[i] = requestedString[i];
			}
		}
	}
	for (i = 0; requestedString[i]; i++)
	{
		splittedString[i] = string[i];
	}
	splittedString[i] = 0;
	return num;

}


status_t stringCompare(u8 *requested_Function_Name , u8 *given_Function_Name)
{
	status_t status = NOT_MATCHED;
	u16 i = 0;
	for ( i = 0; requested_Function_Name[i] || given_Function_Name[i]; i++)
	{
		if (requested_Function_Name[i] == given_Function_Name[i])
		{
			status = MATCHED;
		}
		else
		{
			status = NOT_MATCHED;
			break;
		}
	}
	return status;
}

void LCD_Draw_Character(u8* shape)
{
	customChar(shape , 1);
	for (u8 i = 1 ; i < 20 ; i++)
	{
		LCD_Goto_WriteCharacter(2, i, 1);
		_delay_ms(50);
		LCD_Goto_WriteCharacter(2, i, ' ');
		_delay_ms(50);
	}
}