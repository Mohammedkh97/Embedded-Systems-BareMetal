/*
* GLCD_ST7920.c
*
* Created: 25/07/2024 00:10:46
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "Utils.h"
#include "GLCD_ST7920.h"
#include "GLCD_ST7920_Configuration.h"
#include "LCD_Private.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "UART.h"
#include "UART_Services.h"
#define F_CPU 16000000UL
#include <util/delay.h>

u8 static currentPage = 0;
u8 Graphic_Check = 0;


//#if GLCD_MODE == GLCD_4_BIT

void init_pins(void) {
	// Set RST, CS, SID, and SCLK as output
	DIO_init();
	DIO_initPin1(RST_PIN , OUTPUT);
	DIO_initPin1(RS_PIN , OUTPUT);
	DIO_initPin1(RW_PIN , OUTPUT);
	DIO_initPin1(EN_PIN , OUTPUT);
	// Set the default states
	DIO_WritePin1(RST_PIN , HIGH);
	DIO_WritePin1(RS_PIN , LOW);
	DIO_WritePin1(RW_PIN , LOW);
	DIO_WritePin1(EN_PIN , LOW);
}

void GLCD_SPI_SendData(u8 data)
{
	for (u8 i = 0 ; i < 8 ; i++)
	{
		if ((data << i) & 0x80)
		{
			//PORTB |= (1 << RW_PIN);  // Set SID high
			DIO_WritePin1(RW_PIN , HIGH);
		}
		else
		{
			//PORTB &= ~(1 << RW_PIN);  // Set SID high
			DIO_WritePin1(RW_PIN , LOW);
		}
		// 		PORTB |= (1 << EN_PIN);  // Set SCLK high
		// 		_delay_us(1);               // Small delay
		// 		PORTB &= ~(1 << EN_PIN); // Set SCLK low
		DIO_WritePin1(EN_PIN , HIGH);
		_delay_us(10);
		DIO_WritePin1(EN_PIN , LOW);
	}
}

void GLCD_ST7920_SendCommand(u8 Command)
{
	// 	DIO_WritePin1(RS_PIN , HIGH);    // Pull the RS/ CS High
	// 	GLCD_SPI_SendData(0xF8 + (0<<1));  // Send the SYNC + RS(0)
	// 	//SPI_sendReceiveByte(0xF8 + (0<<1));
	// 	GLCD_SPI_SendData(Command & 0xF0); // Send The Higher Nibble first
	// 	//SPI_sendReceiveByte(Command & 0xF0); // Send The Higher Nibble first
	// 	GLCD_SPI_SendData((Command << 4) & 0xF0); // Send The Lower Nibble
	// 	//SPI_sendReceiveByte((Command << 4) & 0xF0); // Send The Lower Nibble
	// 	_delay_us(100);
	// 	DIO_WritePin1(RS_PIN , LOW);		// Pull the RS / CS LOW
	//
	//PORTB |= (1 << RS_PIN);  // Set CS high (enable chip)
	DIO_WritePin1(RS_PIN , HIGH);    // Pull the RS/ CS High
	GLCD_SPI_SendData(0xF8 | (0 << 1));  // Send the SYNC + RS(0)
	GLCD_SPI_SendData(Command & 0xF0); // Send The Higher Nibble first
	GLCD_SPI_SendData((Command << 4) & 0xF0); // Send The Lower Nibble
	_delay_us(100);
	//PORTB &= ~(1 << RS_PIN);  // Set CS low (disable chip)
	DIO_WritePin1(RS_PIN , LOW);    // Pull the RS/ CS High
}

void GLCD_ST7920_SendData(u8 data)
{
	// 	DIO_WritePin1(RS_PIN , HIGH);    // Pull the RS/ CS High
	// 	GLCD_SPI_SendData(0xF8 + (1<<1));  // Send the SYNC + RS(1)
	// 	//SPI_sendReceiveByte(0xF8 + (1<<1));  // Send the SYNC + RS(0)
	//
	// 	GLCD_SPI_SendData(data & 0xF0); // Send The Higher Nibble first
	// 	//SPI_sendReceiveByte(data & 0xF0); // Send The Higher Nibble first
	//
	// 	GLCD_SPI_SendData((data << 4) & 0xF0); // Send The Lower Nibble
	// 	//SPI_sendReceiveByte((data << 4) & 0xF0); // Send The Lower Nibble
	//
	// 	_delay_us(100);
	// 	DIO_WritePin1(RS_PIN , LOW);		// Pull the RS / CS LOW

	DIO_WritePin1(RS_PIN , HIGH);  // Set CS high (enable chip)
	GLCD_SPI_SendData(0xF8 | (1 << 1));  // Send the SYNC + RS(1)
	GLCD_SPI_SendData(data & 0xF0); // Send The Higher Nibble first
	GLCD_SPI_SendData((data << 4) & 0xF0); // Send The Lower Nibble
	_delay_us(100);
	//PORTB &= ~(1 << RS_PIN);  // Set CS low (disable chip)
	DIO_WritePin1(RS_PIN , LOW);
	
}

void GLCD_ST7920_init()
{
	_delay_ms(80);
	DIO_WritePin1(RST_PIN , HIGH);
	_delay_ms(30);
	DIO_WritePin1(RST_PIN , HIGH);
	_delay_ms(50);

	
	GLCD_ST7920_SendCommand(0x30); // Basic instruction set
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x30); // Repeat
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x08); // Display on  // D = 0 , C = 0 , B = 0
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x01); // Clear display
	_delay_ms(10);
	
	GLCD_ST7920_SendCommand(0x06); // // Entry mode set  Cursor increment Right No Shift
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x0C); // D = 1 . C = 0 , B = 0
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x02); // Return Home
	_delay_ms(1);
}

void GLCD_ST7920_WriteChar(u8 row, u8 col, u8 character)
{
// 	u8 position = 0x80; // Start position for the first row
// 	if (row > 0)
// 	{
// 		position += 0x10; // Move to the second row
// 	}
// 	position += col; // Adjust the column position
// 	
	switch(row)
	{
		case 0:
		col = col | 0x80;
		break;
		case 1:
		col = col | 0x90;
		break;
		case 2:
		col = col | 0x88;
		break;
		case 3:
		col = col | 0x98;
		break;
		default:
		col = col | 0x80;
		break;
	}

	GLCD_ST7920_SendCommand(col); // Set the cursor position
	GLCD_ST7920_SendData(character);   // Write the character to the display
}

void GLCD_ST7920_ClearArea(u8 row, u8 col, u8 length)
{
	switch(row)
	{
		case 0:
		col = col | 0x80;
		break;
		case 1:
		col = col | 0x90;
		break;
		case 2:
		col = col | 0x88;
		break;
		case 3:
		col = col | 0x98;
		break;
		default:
		col = col | 0x80;
		break;
	}

	    GLCD_ST7920_SendCommand(col);
	    for (u8 i = 0; i < length; i++) 
		{
		    GLCD_ST7920_SendData(' ');
	    }
}

void GLCD_ST7920_WriteNumber(u8 row, u8 col, s32 number)
{
	u8 buffer[6]; // Assuming a 5-digit number is the maximum to be displayed
	intoString(number , buffer);			// Convert the number to a string
					 
	GLCD_ST7920_ClearArea(row, col, 4); // Clear the area before displaying the new number
	GLCD_ST7920_SendString(row, col, (u8 *)buffer); // Write the string to the display
	
}

// Function to display a float number at a specific position on the GLCD

void GLCD_ST7920_WriteFloatNumber(u8 row, u8 col, f64 number, u8 decimalPlaces) {
	u8 buffer[6]; // Buffer to hold the float as a string
	floatToString(number, buffer, decimalPlaces); // Convert the float to a string
	GLCD_ST7920_ClearArea(row, col, 4); // Clear the area before displaying the new number
	GLCD_ST7920_SendString(row, col, (u8 *)buffer); // Write the string to the display
}

void GLCD_ST7920_SendString(u8 row , u8 col , u8* string)
{
	u8 i = 0;
	switch(row)
	{
		case 0:
		col = col | 0x80;
		break;
		case 1:
		col = col | 0x90;
		break;
		case 2:
		col = col | 0x88;
		break;
		case 3:
		col = col | 0x98;
		break;
		default:
		col = col | 0x80;
		break;
	}
	GLCD_ST7920_SendCommand(col);
	for (i = 0 ; string[i] ; i++)
	{
		GLCD_ST7920_SendData(string[i]);
	}
	string[i] = 0;
}

void GLCD_ST7920_DisplayPage1()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*)"Page 1:");
	GLCD_ST7920_SendString(1, 0, (u8*)"Hello World!");
}

void GLCD_ST7920_DisplayPage2()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*)"Page 2:");
	GLCD_ST7920_SendString(1, 0, (u8*)"Another Page");
}

void GLCD_ST7920_DisplayPage3()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*)"Page 3:");
	GLCD_ST7920_SendString(1, 0, (u8*)"Yet Another Page");
}

void GLCD_ST7920_DisplayCurrentPage()
{
	switch (currentPage)
	{
		case 0:
		GLCD_ST7920_DisplayPage1();
		break;
		case 1:
		GLCD_ST7920_DisplayPage2();
		break;
		case 2:
		GLCD_ST7920_DisplayPage3();
		break;
		default:
		currentPage = 0;
		GLCD_ST7920_DisplayPage1();
		break;
	}
}

void GLCD_ST7920_NextPage()
{
	currentPage = (currentPage + 1) % TOTAL_PAGES;
	GLCD_ST7920_DisplayCurrentPage();
}

void GLCD_ST7920_PreviousPage()
{
	if (currentPage == 0)
	{
		currentPage = TOTAL_PAGES - 1;
	}
	else
	{
		currentPage--;
	}
	GLCD_ST7920_DisplayCurrentPage();
}


void GLCD_ST7920_LoadCustomChar(u8* pattern, u8 address)
{
	// Set CGRAM address
	GLCD_ST7920_SendCommand(0x40 | (address << 3)); // 0x40 is the base command for CGRAM address set
	
	// Write the 8-byte pattern to CGRAM
	for (u8 i = 0; i < 8; i++)
	{
		GLCD_ST7920_SendData(pattern[i]);
	}
}

void GLCD_ST7920_DisplayCustomChar(u8 row, u8 col, u8 address)
{
	// Set DDRAM address based on the row and column
	u8 ddramAddress = 0;
	switch(row)
	{
		case 0: ddramAddress = col; break;
		case 1: ddramAddress = col | 0x40; break;
		case 2: ddramAddress = col | 0x10; break;
		case 3: ddramAddress = col | 0x50; break;
	}
	
	GLCD_ST7920_SendCommand(0x80 | ddramAddress); // 0x80 is the base command for DDRAM address set
	
	// Write the CGRAM address to DDRAM to display the custom character
	GLCD_ST7920_SendData(address);
}

void GLCD_ST7920_GraphicMode(s16 enable)
{
	if (enable == 1)
	{
		GLCD_ST7920_SendCommand(0x30);
		_delay_ms(1);
		GLCD_ST7920_SendCommand(0x34);
		_delay_ms(1);
		GLCD_ST7920_SendCommand(0x36);
		_delay_ms(1);
		Graphic_Check = 1;
	}
	else if (enable == 0)
	{
		GLCD_ST7920_SendCommand(0x30);
		_delay_ms(1);
		Graphic_Check = 0;
	}
}
void GLCD_ST7920_DrawBitMap(const u8* graphic)
{
	u8 row , col;
	for (col = 0 ; col < 64 ; col++)
	{
		if (col < 32)
		{
			for (row = 0 ; row < 8 ; row++)
			{
				GLCD_ST7920_SendCommand(0x80 | col);
				GLCD_ST7920_SendCommand(0x80 | row);
				GLCD_ST7920_SendData(graphic[2*row + 16*col]);
				GLCD_ST7920_SendData(graphic[2*row + 1 + 16*col]);
			}
		}
		else
		{
			for (row = 0 ; row < 8 ; row++)
			{
				GLCD_ST7920_SendCommand(0x80 | (col-32));
				GLCD_ST7920_SendCommand(0x88 | row);
				GLCD_SPI_SendData(graphic[2*row + 16*col]);
				GLCD_SPI_SendData(graphic[2*row+1 + 16*col]);
			}
		}
	}
}

void GLCD_ST7920_Clear(void)
{
	if (Graphic_Check == 1)
	{
		u8 row , col;
		for (col = 0 ; col < 64 ; col++)
		{
			if (col < 32)
			{
				GLCD_ST7920_SendCommand(0x80 | col);
				GLCD_ST7920_SendCommand(0x80);
			}
			else
			{
				GLCD_ST7920_SendCommand(0x80 | (col-32));
				GLCD_ST7920_SendCommand(0x88);
			}
			for (row = 0 ; row < 8 ; row++)
			{
				GLCD_ST7920_SendData(0);
				_delay_us(10);
				GLCD_ST7920_SendData(0);
			}
		}
	}
	else
	{
		GLCD_ST7920_SendCommand(0x01);
		_delay_us(50);
	}
}

void setPixel(u16 x, u16 y, u8 on) {
	if (x < 0 || x >= LCD_WIDTH || y < 0 || y >= LCD_HEIGHT) {
		return;
	}
	u16 index = x + (y / 8) * LCD_WIDTH;
	if (on) {
		graphicsBuffer[index] |= (1 << (y % 8));
		} else {
		graphicsBuffer[index] &= ~(1 << (y % 8));
	}
}

void updateScreen() {
	for (u16 y = 0; y < 8; y++) {
		for (u16 x = 0; x < 128; x++) {
			u16 index = x + y * 128;
			GLCD_ST7920_SendCommand(0x80 | x);  // Set X address
			GLCD_ST7920_SendCommand(0x80 | y);  // Set Y address
			GLCD_ST7920_SendData(graphicsBuffer[index]);
		}
	}
}

void drawSquare(int x, int y, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			setPixel(x + i, y + j, 1);  // Turn on the pixel
		}
	}
	updateScreen();  // Update the screen to reflect changes
}