/*
 * KEYPAD_program.c
 *
 * Created: 8/22/2022 6:08:26 PM
 *  Author: Mohammed Khalaf
 */

#define KEYPAD_Program
/* ======================= Inclusions ====================== */
#include "stdTypes.h"
#include "KEYPAD_interface.h"
#include "stm32f1xx_hal.h"
/* ======================= Functions Prototypes ====================== */

void KEYPAD_init(void)
{
	u8 row, col;
	for (row = 0; row < ROWS; row++)
	{
		//GPIO_void_SetPinMode1(FIRST_OUTPUT + row, DIO_OUTPUT_PUSHPULL_10MHZ);
		GPIO_void_Write_Pin_Method1(FIRST_OUTPUT + row, HIGH);
	}

	for (col = 0; col < COLS; col++)
	{
//	    GPIO_void_SetPinMode1(FIRST_INPUT + col, DIO_INPUT_PULL_UP_DOWN);
	    GPIO_void_Write_Pin_Method1(FIRST_INPUT + col, HIGH);
	}



}


u8 KEYPAD_GetKey(void)
{
	//Std_ReturnType Ret = E_OK;

	u8 RowIterator = 0, ColIterator = 0;
	u8 Key = NO_KEY;

	for (RowIterator = 0; RowIterator < ROWS; RowIterator++)
	{
		/* Set each Row Pin to High then Check all Columns */
		GPIO_void_Write_Pin_Method1(FIRST_OUTPUT + RowIterator, LOW);

		for (ColIterator = 0; ColIterator < COLS; ColIterator++)
		{
			if (GPIO_DIO_PinVoltage_Read_Pin_Method1(FIRST_INPUT + ColIterator)== LOW)
			{
				Key = KeysArray[RowIterator][ColIterator];
				HAL_Delay(10);
				while (GPIO_DIO_PinVoltage_Read_Pin_Method1(FIRST_INPUT + ColIterator) == LOW);
				HAL_Delay(10);
			}
		}
		/* Return the Pin to its LOW state */
		GPIO_void_Write_Pin_Method1(FIRST_OUTPUT + RowIterator, HIGH);
	}

	return Key;
}
