/*
* GLCD_ST7920_Program.c
*
* Created: 25/07/2024 00:10:46
*  Author: Mohammed Khalaf
*/


#include <String_lib.h>
#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "GPIO_Interface.h"
#include "GLCD_ST7920_Commands.h"
#include "GLCD_ST7920_Interface.h"
#include "GLCD_ST7920_Configuration.h"
#include "Delay/delay.h"

#include "stm32f1xx_hal.h"  // Replace 'f1xx' with your specific STM32 series if different

u8 static currentPage = 0;
u8 Graphic_Check = 0;
u8 graphicsBuffer[LCD_WIDTH * LCD_HEIGHT / 8];
u8 startRow, startCol, endRow, endCol; // coordinates of the dirty rectangle
u8 numRows = 64;
u8 numCols = 128;
u8 image[(128 * 64) / 8];
void init_pins(void)
{
	// Set RST, CS, SID, and SCLK as output

	GPIO_void_SetPinMode1(RST_PIN, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(RS_PIN, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(RW_PIN, DIO_OUTPUT_PUSHPULL_10MHZ);
	GPIO_void_SetPinMode1(EN_PIN, DIO_OUTPUT_PUSHPULL_10MHZ);

	// Set the default states
	GPIO_void_Write_Pin_Method1(RST_PIN, HIGH);
	GPIO_void_Write_Pin_Method1(RS_PIN, LOW);
	GPIO_void_Write_Pin_Method1(RW_PIN, LOW);
	GPIO_void_Write_Pin_Method1(EN_PIN, LOW);
}

// SPI Initialization with GLCD ST7920

void GLCD_SPI_SendData(u8 data)
{
	for (u8 i = 0; i < 8; i++)
	{
		if ((data << i) & 0x80)
		{
			GPIO_void_Write_Pin_Method1(RW_PIN, HIGH);		// SID=1  OR MOSI
		}
		else
		{

			GPIO_void_Write_Pin_Method1(RW_PIN, LOW);		// SID = 0
		}

		GPIO_void_Write_Pin_Method1(EN_PIN, HIGH);		   // SCLK = 1  OR SCK
		GPIO_void_Write_Pin_Method1(EN_PIN, LOW);		   // SCLK = 0  OR SCK
	}
}

void GLCD_ST7920_SendCommand(u8 Command)
{
	GPIO_void_Write_Pin_Method1(RS_PIN, HIGH);    // Pull the RS/ CS High

	GLCD_SPI_SendData(0xF8 + (0 << 1));  // Send the SYNC + RS(0)
	GLCD_SPI_SendData(Command & 0xF0); // Send The Higher Nibble first
	GLCD_SPI_SendData((Command << 4) & 0xF0); // Send The Lower Nibble

	delay_us(50);

	GPIO_void_Write_Pin_Method1(RS_PIN, LOW);		// Pull the RS / CS LOW

}

void GLCD_ST7920_SendData(u8 data)
{
//	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET); // PUll the CS high
	GPIO_void_Write_Pin_Method1(RS_PIN, HIGH); // PUll the CS high
	GLCD_SPI_SendData(0xf8 + (1 << 1));  // send the SYNC + RS(1)
	GLCD_SPI_SendData(data & 0xf0);  // send the higher nibble first
	GLCD_SPI_SendData((data << 4) & 0xf0);  // send the lower nibble
	delay_us(50);
//	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);  // PUll the CS LOW
	GPIO_void_Write_Pin_Method1(RS_PIN, LOW);
}

void GLCD_ST7920_init()
{
	init_pins();
//	HAL_GPIO_WritePin(RST_PORT, RST_PIN, GPIO_PIN_RESET);  // RESET=0
	GPIO_void_Write_Pin_Method1(RST_PIN , LOW);
	HAL_Delay(10);   // wait for 10ms
//	HAL_GPIO_WritePin(RST_PORT, RST_PIN, GPIO_PIN_SET);  // RESET=1
	GPIO_void_Write_Pin_Method1(RST_PIN , HIGH);

	HAL_Delay(50);   //wait for >40 ms

	GLCD_ST7920_SendCommand(0x30);  // 8bit mode
	delay_us(110);  //  >100us delay

	GLCD_ST7920_SendCommand(0x30);  // 8bit mode
	delay_us(40);  // >37us delay

	GLCD_ST7920_SendCommand(0x08);  // D=0, C=0, B=0
	delay_us(110);  // >100us delay

	GLCD_ST7920_SendCommand(0x01);  // clear screen
	HAL_Delay(12);  // >10 ms delay

	GLCD_ST7920_SendCommand(0x06);  // cursor increment right no shift
	HAL_Delay(1);  // 1ms delay

	GLCD_ST7920_SendCommand(0x0C);  // D=1, C=0, B=0
	HAL_Delay(1);  // 1ms delay

	GLCD_ST7920_SendCommand(0x02);  // return to home
	HAL_Delay(1);  // 1ms delay

}

void GLCD_ST7920_ClearArea(u8 row, u8 col, u8 length)
{
	switch (row)
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

void GLCD_ST7920_Clear()
{
	if (Graphic_Check == 1)  // if the graphic mode is set
	{
		uint8_t x, y;
		for (y = 0; y < 64; y++)
		{
			if (y < 32)
			{
				GLCD_ST7920_SendCommand(0x80 | y);
				GLCD_ST7920_SendCommand(0x80);
			}
			else
			{
				GLCD_ST7920_SendCommand(0x80 | (y - 32));
				GLCD_ST7920_SendCommand(0x88);
			}
			for (x = 0; x < 8; x++)
			{
				GLCD_ST7920_SendData(0);
				GLCD_ST7920_SendData(0);
			}
		}
	}

	else
	{
		GLCD_ST7920_SendCommand(0x01);   // clear the display using command
		HAL_Delay(2); // delay >1.6 ms
	}
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
	switch (row)
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

void GLCD_ST7920_WriteNumber(u8 row, u8 col, s32 number, u8 ClearArea)
{
	u8 buffer[6]; // Assuming a 5-digit number is the maximum to be displayed
	intoString(number, buffer);			// Convert the number to a string

	GLCD_ST7920_ClearArea(row, col, ClearArea); // Clear the area before displaying the new number
	GLCD_ST7920_SendString(row, col, (u8*) buffer); // Write the string to the display
}

// Function to display a float number at a specific position on the GLCD

void GLCD_ST7920_WriteFloatNumber(u8 row, u8 col, f64 number, u8 decimalPlaces, u8 ClearArea)
{
	u8 buffer[6]; // Buffer to hold the float as a string
	floatToString(number, buffer, decimalPlaces); // Convert the float to a string
	GLCD_ST7920_ClearArea(row, col, ClearArea); // Clear the area before displaying the new number
	GLCD_ST7920_SendString(row, col, (u8*) buffer); // Write the string to the display
}

void GLCD_ST7920_SendString(u8 row, u8 col, u8 *string)
{
	switch (row)
	{
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0x90;
		break;
	case 2:
		col |= 0x88;
		break;
	case 3:
		col |= 0x98;
		break;
	default:
		col |= 0x80;
		break;
	}

	GLCD_ST7920_SendCommand(col);

	while (*string)
	{
		GLCD_ST7920_SendData(*string++);
	}
}

void GLCD_ST7920_DisplayPage1()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 1:");
	GLCD_ST7920_SendString(1, 0, (u8*) "Hello World!");
}

void GLCD_ST7920_DisplayPage2()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 2:");
	GLCD_ST7920_SendString(1, 0, (u8*) "Another Page");
}

void GLCD_ST7920_DisplayPage3()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 3:");
	GLCD_ST7920_SendString(1, 0, (u8*) "Yet Another Page");
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

//void GLCD_ST7920_NextPage()
//{
//	currentPage = (currentPage + 1) % TOTAL_PAGES;
//	GLCD_ST7920_DisplayCurrentPage();
//}
//
//void GLCD_ST7920_PreviousPage()
//{
//	if (currentPage == 0)
//	{
//		currentPage = TOTAL_PAGES - 1;
//	}
//	else
//	{
//		currentPage--;
//	}
//	GLCD_ST7920_DisplayCurrentPage();
//}
//
//
//void GLCD_ST7920_LoadCustomChar(u8* pattern, u8 address)
//{
//	// Set CGRAM address
//	GLCD_ST7920_SendCommand(0x40 | (address << 3)); // 0x40 is the base command for CGRAM address set
//
//	// Write the 8-byte pattern to CGRAM
//	for (u8 i = 0; i < 8; i++)
//	{
//		GLCD_ST7920_SendData(pattern[i]);
//	}
//}
//
//void GLCD_ST7920_DisplayCustomChar(u8 row, u8 col, u8 address)
//{
//	// Set DDRAM address based on the row and column
//	u8 ddramAddress = 0;
//	switch(row)
//	{
//		case 0: ddramAddress = col; break;
//		case 1: ddramAddress = col | 0x40; break;
//		case 2: ddramAddress = col | 0x10; break;
//		case 3: ddramAddress = col | 0x50; break;
//	}
//
//	GLCD_ST7920_SendCommand(0x80 | ddramAddress); // 0x80 is the base command for DDRAM address set
//
//	// Write the CGRAM address to DDRAM to display the custom character
//	GLCD_ST7920_SendData(address);
//}
//

void GLCD_ST7920_GraphicMode(s16 enable)
{
	if (enable == 1)
	{
		GLCD_ST7920_SendCommand(0x30);  // 8 bit mode
		HAL_Delay(1);
		GLCD_ST7920_SendCommand(0x34);  // switch to Extended instructions
		HAL_Delay(1);
		GLCD_ST7920_SendCommand(0x36);  // enable graphics
		HAL_Delay(1);
		Graphic_Check = 1;  // update the variable
	}

	else if (enable == 0)
	{
		GLCD_ST7920_SendCommand(0x30);  // 8 bit mode
		HAL_Delay(1);
		Graphic_Check = 0;  // update the variable
	}
}

void GLCD_ST7920_DrawBitMap(const u8 *graphic)
{
	u8 x, y;
	for (y = 0; y < 64; y++)
	{
		if (y < 32)
		{
			for (x = 0; x < 8; x++)				// Draws top half of the screen.
			{// In extended instruction mode, vertical and horizontal coordinates must be specified before sending data in.
				GLCD_ST7920_SendCommand(0x80 | y);// Vertical coordinate of the screen is specified first. (0-31)
				GLCD_ST7920_SendCommand(0x80 | x);// Then horizontal coordinate of the screen is specified. (0-8)
				GLCD_ST7920_SendData(graphic[2 * x + 16 * y]);// Data to the upper byte is sent to the coordinate.
				GLCD_ST7920_SendData(graphic[2 * x + 1 + 16 * y]);// Data to the lower byte is sent to the coordinate.
			}
		}
		else
		{
			for (x = 0; x < 8; x++)			// Draws bottom half of the screen.
			{			// Actions performed as same as the upper half screen.
				GLCD_ST7920_SendCommand(0x80 | (y - 32));// Vertical coordinate must be scaled back to 0-31 as it is dealing with another half of the screen.
				GLCD_ST7920_SendCommand(0x88 | x);
				GLCD_ST7920_SendData(graphic[2 * x + 16 * y]);
				GLCD_ST7920_SendData(graphic[2 * x + 1 + 16 * y]);
			}
		}

	}
}

// Update the display with the selected graphics
void ST7920_Update(void)
{
	GLCD_ST7920_DrawBitMap(graphicsBuffer);
}

void updateScreen()
{
	for (u16 y = 0; y < 8; y++)
	{
		for (u16 x = 0; x < 128; x++)
		{
			u16 index = x + y * 128;
			GLCD_ST7920_SendCommand(0x80 | x);  // Set X address
			GLCD_ST7920_SendCommand(0x80 | y);  // Set Y address
			GLCD_ST7920_SendData(graphicsBuffer[index]);
		}
	}
}

void SetPixel(u8 x, u8 y)
{
	if (y < numRows && x < numCols)
	{
		u8 *p = image + ((y * (numCols / 8)) + (x / 8));
		*p |= 0x80u >> (x % 8);

		*image = *p;

		// Change the dirty rectangle to account for a pixel being dirty (we assume it was changed)
		if (startRow > y)
		{
			startRow = y;
		}
		if (endRow <= y)
		{
			endRow = y + 1;
		}
		if (startCol > x)
		{
			startCol = x;
		}
		if (endCol <= x)
		{
			endCol = x + 1;
		}

	}

}

/* draw a line
 * start point (X0, Y0)
 * end point (X1, Y1)
 */
void DrawLine(u8 x0, u8 y0, u8 x1, u8 y1)
{
	s16 dx = (x1 >= x0) ? x1 - x0 : x0 - x1;
	s16 dy = (y1 >= y0) ? y1 - y0 : y0 - y1;
	s16 sx = (x0 < x1) ? 1 : -1;
	s16 sy = (y0 < y1) ? 1 : -1;
	s16 err = dx - dy;

	for (;;)
	{
		SetPixel(x0, y0);
		if (x0 == x1 && y0 == y1)
			break;
		s16 e2 = err + err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

/* Draw rectangle
 * start point (x,y)
 * w -> width
 * h -> height
 */
void DrawRectangle(u16 x, u16 y, u16 w, u16 h)
{
	/* Check input parameters */
	if (x >= numCols || y >= numRows)
	{
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= numCols)
	{
		w = numCols - x;
	}
	if ((y + h) >= numRows)
	{
		h = numRows - y;
	}

	/* Draw 4 lines */
	DrawLine(x, y, x + w, y); /* Top line */
	DrawLine(x, y + h, x + w, y + h); /* Bottom line */
	DrawLine(x, y, x, y + h); /* Left line */
	DrawLine(x + w, y, x + w, y + h); /* Right line */
}

/* Draw filled rectangle
 * Start point (x,y)
 * w -> width
 * h -> height
 */
void DrawFilledRectangle(u16 x, u16 y, u16 w, u16 h)
{
	u8 i;

	/* Check input parameters */
	if (x >= numCols || y >= numRows)
	{
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= numCols)
	{
		w = numCols - x;
	}
	if ((y + h) >= numRows)
	{
		h = numRows - y;
	}

	/* Draw lines */
	for (i = 0; i <= h; i++)
	{
		/* Draw lines */
		DrawLine(x, y + i, x + w, y + i);
	}
}

/* draw circle
 * centre (x0,y0)
 * radius = radius
 */
void DrawCircle(u8 x0, u8 y0, u8 radius)
{
	s16 f = 1 - (s16) radius;
	s16 ddF_x = 1;

	s16 ddF_y = -2 * (s16) radius;
	s16 x = 0;

	SetPixel(x0, y0 + radius);
	SetPixel(x0, y0 - radius);
	SetPixel(x0 + radius, y0);
	SetPixel(x0 - radius, y0);

	s16 y = radius;
	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		SetPixel(x0 + x, y0 + y);
		SetPixel(x0 - x, y0 + y);
		SetPixel(x0 + x, y0 - y);
		SetPixel(x0 - x, y0 - y);
		SetPixel(x0 + y, y0 + x);
		SetPixel(x0 - y, y0 + x);
		SetPixel(x0 + y, y0 - x);
		SetPixel(x0 - y, y0 - x);
	}
}

// Draw Filled Circle

void DrawFilledCircle(s16 x0, s16 y0, s16 r)
{
	s16 f = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x = 0;
	s16 y = r;

	SetPixel(x0, y0 + r);
	SetPixel(x0, y0 - r);
	SetPixel(x0 + r, y0);
	SetPixel(x0 - r, y0);
	DrawLine(x0 - r, y0, x0 + r, y0);

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		DrawLine(x0 - x, y0 + y, x0 + x, y0 + y);
		DrawLine(x0 + x, y0 - y, x0 - x, y0 - y);

		DrawLine(x0 + y, y0 + x, x0 - y, y0 + x);
		DrawLine(x0 + y, y0 - x, x0 - y, y0 - x);
	}
}

// Draw Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawTriangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 x3, u16 y3)
{
	/* Draw lines */
	DrawLine(x1, y1, x2, y2);
	DrawLine(x2, y2, x3, y3);
	DrawLine(x3, y3, x1, y1);
}

// Draw Filled Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawFilledTriangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3)
{
	s16 deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, yinc1 =0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,curpixel = 0;

#define ABS(x)   ((x) > 0 ? (x) : -(x))

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		DrawLine(x, y, x3, y3);

		num += numadd;
		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

