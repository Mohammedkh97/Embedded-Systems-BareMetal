/*
* Keypad_interface_interrupt.c
*
* Created: 03/06/2024 01:48:09
*  Author: Mohammed Khalaf
*/

#define KEYPAD_PROG

#include "stdTypes.h"
#include "MemoryMap.h"
#include "DIO_interface.h"

#include "KEYPAD_Config_Interrupt.h"
#include "Keypad_interface_interrupt.h"
#include "Ex_int.h"

#define F_CPU 8000000UL
#include <util/delay.h>

volatile u8 key = NO_KEY;
volatile u8 keyPressedFlag = 0;


void KEYPAD_init_interrupt(void)
{
	EXI_init();
	// Configure rows as outputs and set them high
	for (u8 row = 0; row < ROW; row++) {
		DIO_WritePin1(FIRST_OUTPUT + row, HIGH);
	}

	// Configure columns as inputs with pull-ups
	for (u8 col = 0; col < COL; col++) {
		DIO_WritePin1(FIRST_INPUT + col, HIGH);
	}

	// Enable external interrupt on the keypad columns (example for INT0)
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0, FALLING_EDGE);
	sei();
}

u8 KEYPAD_Scan(void)
{
	u8 row, col;
	for (row = 0; row < ROW; row++)
	{
		DIO_WritePin1(FIRST_OUTPUT + row, LOW);
		for (col = 0; col < COL; col++)
		{
			if (!DIO_ReadPin1(FIRST_INPUT + col))
			{
				key = KeysArray[row][col];
			}
		}
		DIO_WritePin1(FIRST_OUTPUT + row, HIGH);
		if (key != NO_KEY)
		break;
	}
	return key;
}


u8 KEYPAD_GetKey_interrupt(void)
{
	if (keyPressedFlag) {
		keyPressedFlag = 0;
		return KEYPAD_Scan();
	}
	return NO_KEY;
}
ISR(EXTERNAL_INT_VECTOR)
{
	keyPressedFlag = 1;  // Set the flag to indicate a key press
}
