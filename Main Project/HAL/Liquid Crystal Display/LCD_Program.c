/*
* LCD_Program.c
*
* Created: 10/24/2023 12:44:29 PM
*  Author: Mohammed Khalaf
*/


#include <String_lib.h>
#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "GPIO_Interface.h"
#include "LCD_interface.h"
#include "LCD_Config.h"
#include "LCD_Private.h"
#include "stm32f1xx_hal.h"  // Replace 'f1xx' with your specific STM32 series if different

/****************** define the timer handler below  **************/
#define timer htim1


extern TIM_HandleTypeDef timer;
void delay (u16 us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < us);
}

u8 man[] = {
	0B00100,
	0B01010,
	0B00100,
	0B10101,
	0B11111,
	0B00100,
	0B01010,
	0B10001
};

#if LCD_MODE == _4_BIT

void write_instruction(u8 instruction)
{

	GPIO_void_Write_Pin_Method1(RS , LOW);
	GPIO_void_Write_Pin_Method1(D7 , GET_BIT(instruction , 7));
	GPIO_void_Write_Pin_Method1(D6 , GET_BIT(instruction , 6));
	GPIO_void_Write_Pin_Method1(D5 , GET_BIT(instruction , 5));
	GPIO_void_Write_Pin_Method1(D4 , GET_BIT(instruction , 4));

	GPIO_void_Write_Pin_Method1(EN , HIGH);
	HAL_Delay(1);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	HAL_Delay(1);

	GPIO_void_Write_Pin_Method1(D7 , GET_BIT(instruction , 3));
	GPIO_void_Write_Pin_Method1(D6 , GET_BIT(instruction , 2));
	GPIO_void_Write_Pin_Method1(D5 , GET_BIT(instruction , 1));
	GPIO_void_Write_Pin_Method1(D4 , GET_BIT(instruction , 0));

	GPIO_void_Write_Pin_Method1(EN , HIGH);
	HAL_Delay(1);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	HAL_Delay(1);
}

void write_Data(u8 Data)
{
	GPIO_void_Write_Pin_Method1(RS , HIGH);
	GPIO_void_Write_Pin_Method1(D7 , GET_BIT(Data , 7));
	GPIO_void_Write_Pin_Method1(D6 , GET_BIT(Data , 6));
	GPIO_void_Write_Pin_Method1(D5 , GET_BIT(Data , 5));
	GPIO_void_Write_Pin_Method1(D4 , GET_BIT(Data , 4));

	GPIO_void_Write_Pin_Method1(EN , HIGH);
	HAL_Delay(1);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	HAL_Delay(1);

	GPIO_void_Write_Pin_Method1(D7 , GET_BIT(Data , 3));
	GPIO_void_Write_Pin_Method1(D6 , GET_BIT(Data , 2));
	GPIO_void_Write_Pin_Method1(D5 , GET_BIT(Data , 1));
	GPIO_void_Write_Pin_Method1(D4 , GET_BIT(Data , 0));

	GPIO_void_Write_Pin_Method1(EN , HIGH);
	delay (20);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	delay (20);
}

void LCD_Init(void)
{
	u8 pinNumber;

	GPIO_void_SetPinMode1(RS, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(EN, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(D4, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(D5, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(D6, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(D7, DIO_OUTPUT_PUSHPULL_10MHZ);


	HAL_Delay(50); // to make sure that Micro-controller starts first
	write_instruction(_4_BIT_MODE_COMMAND); 	// Set LCD to 4-bit mode
	HAL_Delay(5);
	write_instruction(FUNCTION_SET_MASK);		// Function set: 4-bit, 2 lines, 5x8 dots
	HAL_Delay(1);
	write_instruction(DISPLAY_ON_OFF_MASK);  	// Display on, cursor off
	HAL_Delay(1);
	write_instruction(CLEAR_SCREEN);  			// Clear LCD
	HAL_Delay(2);
	write_instruction(I_DDRAM_ADDR_NO_SHIFT);	// Entry mode set: Increment cursor
	HAL_Delay(1);
	write_instruction (DISPLAY_ON); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

	for (pinNumber = D4; pinNumber <= D7; pinNumber++)
	{
		GPIO_void_SetPinMode1(pinNumber, DIO_OUTPUT_PUSHPULL_10MHZ);
	}

	GPIO_void_SetPinMode1(EN , DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(RS , DIO_OUTPUT_PUSHPULL_10MHZ);

}

#elif LCD_MODE == _8_BIT

void write_instruction(u8 instruction)
{

	GPIO_void_Write_Pin_Method1(RS , LOW);
	GPIO_void_Write_Port(LCD_PORT , instruction);
	GPIO_void_Write_Pin_Method1(EN , HIGH);
	HAL_Delay(1);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	HAL_Delay(1);

}
void write_Data(u8 data)
{
	GPIO_void_Write_Pin_Method1(RS , HIGH);
	GPIO_void_Write_Pin_Method1(LCD_PORT , data);
	GPIO_void_Write_Pin_Method1(EN , HIGH);
	HAL_Delay(1);
	GPIO_void_Write_Pin_Method1(EN , LOW);
	HAL_Delay(1);

}

void LCD_Init(void)
{
	HAL_Delay(50); // to make sure that Micro-controller starts first
	/*                       */
	/* DIO_WritePin1(RS , LOW);
	DIO_Write_Port(LCD_PORT , 0x38); // 0x38 from data sheet page 18 function set 0 0 0 1 1 1 0 0 0  (Back to Data sheet)
	DIO_WritePin1(EN , HIGH);
	_delay_ms(1);
	DIO_WritePin1(EN , LOW);
	_delay_ms(1);*/
	write_instruction(FUNCTION_SET_MASK);		// Function set: 8-bit, 2 lines, 5x8 dots
	write_instruction(DISPLAY_ON_OFF_MASK);  	// Display on, cursor off
	write_instruction(CLEAR_SCREEN);  			// Clear LCD
	HAL_Delay(1);
	write_instruction(ENTRY_MODE_SET);			// Entry mode set: Increment cursor
}

#endif


/*******************************************************************************/



/*
-Data ON PORTA = 01101101;
-New Data you want to write on PORTA: 11001110
You want to write Data on the second half of PORTA
1. Get the second four bits:
Data & 0xF0 :	11001110
11110000
= 	11000000
2. Clear the Data of PORTA for the the second four bits only
PA = PA & 0x0F: 01101101
00001111
=	00001101
3. Set the New you want to write on PORTA
PA = PA | data & 0xF0:
00001110
| ( 11001110
&   11110000)  // For the second data four bits:
PA = PA | data<<4 & 0xF0:
00001110
| ( 11001110
&   11110000)  // For the first data four bits:				PA = PA | data & 0xF0:


*/



void LCD_WriteChar(u8 data)
{
	write_Data(data);
}
void LCD_WriteString(u8* string)
{
	u8 i;
	for (i = 0 ; string[i] ; i++)
	{
		write_Data(string[i]);
	}
	string[i] = 0;

}

void LCD_WriteNumber(s32 num)
{
	u8 string[10];
	intoString(num , string);
	LCD_WriteString(string);

}


void LCD_Clear(void)
{
	write_instruction(CLEAR_SCREEN);  // Clear LCD
	HAL_Delay(1);
	// Keep in mind, clear command sets DDRAM address to 00H "From the begin"
}

void LCD_SetCursor(u8 line, u8 cell)
{
    /*
    line: 1 - 4
    cell: 1 - 16
    */
    if (line == 1)
    {
        write_instruction(LINE_1_ADDRESS + (cell - 1));  // 0b10000000 = 0x80 for line 1
        HAL_Delay(1);  // Replaced _delay_us with HAL_Delay (in milliseconds)
    }
    else if (line == 2)
    {
        write_instruction(LINE_2_ADDRESS + (cell - 1));  // 0xC0 for line 2
        HAL_Delay(1);
    }
    else if (line == 3)
    {
        write_instruction(LINE_3_ADDRESS + (cell - 1));  // Addressing line 3
        HAL_Delay(1);
    }
    else if (line == 4)
    {
        write_instruction(LINE_4_ADDRESS + (cell - 1));  // Addressing line 4
        HAL_Delay(1);
    }
}

/*
void LCD_SetCursor(u8 line, u8 cell)
{

    switch (line)
    {
        case 1:
            write_instruction(0x80 + (cell - 1));  // Line 1, 0x80 base address
            break;

        case 2:
            write_instruction(0xC0 + (cell - 1));  // Line 2, 0xC0 base address
            break;

        case 3:
            write_instruction(0x94 + (cell - 1));  // Line 3, 0x94 base address
            break;

        case 4:
            write_instruction(0xD4 + (cell - 1));  // Line 4, 0xD4 base address
            break;

        default:
            // Handle invalid line number if needed
            return;
    }

    HAL_Delay(1);  // 1 ms delay after setting the cursor
}
*/


void LCD_Binary_Number_Display(s32 num)
{
		u8 Flag = 0;
		s32 i;
		for (i = 7; i >= 0; i--)
		{
			if ((num >> i) & 1)
			{
				Flag = 1;
				LCD_WriteNumber(1);
			}
			else
			{
				if (Flag == 1)
				LCD_WriteNumber(0);
			}
		}
}

void LCD_Hex_Number_Display(s32 num)
{
	// 0001 0001 = 1 1 == 17

	s8 firstDigit = num%16;
	s8 secondDigit = num/16;
	if (secondDigit<10)
	{
		LCD_WriteChar(secondDigit +'0');
	}
	else
	{
		LCD_WriteChar(secondDigit+'A'-10);
	}
	if (firstDigit<10)
	{
		LCD_WriteChar(firstDigit +'0');
	}
	else
	{
		LCD_WriteChar(firstDigit+'A'-10);
	}

}
void LCD_ASCII_Number_Display(u8 ascii)
{
	LCD_WriteNumber(ascii);
}

void LCD_Goto_WriteNumber(u8 line,u8 cell,u32 num)
{
	LCD_SetCursor(line , cell);
	LCD_WriteNumber(num);
}
void LCD_Goto_WriteCharacter(u8 line,u8 cell,u8 character)
{
	LCD_SetCursor(line , cell);
	LCD_WriteChar(character);
}
void LCD_Goto_WriteString(u8 line, u8 cell, u8* str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);

}
void LCD_GoTo_WriteFloatNumber(u8 line, u8 cell,f32 num, u8 decimalPlaces)
{
	char buffer[20]; // Adjust the size according to your needs
	floatToString(num, (u8*)buffer, decimalPlaces);
	LCD_Goto_WriteString(line , cell , (u8*)buffer);
}

void SnakeWord(u8* name)
{
	u8 i ;
	for (i = 1 ; i < string_len(name); i++)
	{
		LCD_WriteString((u8*)name + string_len(name) - i);
		HAL_Delay(10);
		LCD_Clear();
	}
	for (i = 1 ; i<=16 ; i++)
	{
		LCD_Clear();
		LCD_SetCursor(1,i);
		LCD_WriteString((u8*)name);
		HAL_Delay(10);
	}
	/*for (i = 16 ; i>=1 ; i--)
	{
		LCD_Clear();
		LCD_SetCursor(1,i);
		LCD_WriteStr((u8*)name);
		LCD_WriteStr("  ");
		//LCD_WriteChar(name[j]);
		_delay_ms(10);
	}*/
	for (i = 1 ; i < string_len(name); i++)
	{
		LCD_SetCursor(2,1);
		LCD_WriteString((u8*)name + string_len(name) - i);
		HAL_Delay(10);
		LCD_Clear();
	}
	for (i = 1; i<=16; i++)
	{
		LCD_Clear();
		LCD_SetCursor(2,i);
		LCD_WriteString((u8*)name);
		HAL_Delay(10);
	}
}

// Here, you need to store the shape of this pattern in the memory of LCD.
void customChar(u8* pattern , u8 address)
{

	write_instruction(0x40 + address*8);
	for (u8 i = 0 ; i < 8 ; i++)
	{
		write_Data(pattern[i]);
		//LCD_WriteStr((u8*)man);
	}
	write_instruction(0x80);
}

