/***************************************************************/
/* Author		: Ahmed Hssein                                 */
/* Date         : 1 Jan. 2025    							   */
/* Version		: V01										   */
/***************************************************************/

#include "stdTypes.h"
#include "delay.h"
#include "BitwiseOperations_LIB.h"

#include"RCC_Interface.h"
#include"GPIO_Interface.h"
#include"STK_Interface.h"

#include "TFT_Interface.h"
#include "TFT_Private.h"
#include "TFT_Config.h"


// Function to initialize the GPIOs
void HTFT_voidGPIOInit(void)
{

	// Enable GPIO clock for data and control pins
//	MRCC_voidEnableClock(RCC_APB2, RCC_IOPA);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
//	MRCC_voidEnableClock(RCC_APB2, RCC_IOPB);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);

	// Initialize Data Pins (D0 to D7)
//	MGPIO_voidSetPinDirection(LCD_D0, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D1, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D2, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D3, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D4, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D5, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D6, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_D7, OUTPUT_SPEED_50MHZ_PUSHPULL);

	GPIO_void_SetPinMode1(LCD_D0,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D1,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D2,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D3,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D4,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D5,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D6,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_D7,DIO_OUTPUT_PUSHPULL_50MHZ);




	// Initialize Control Pins (RST, RS, WR)
//	MGPIO_voidSetPinDirection(LCD_RST, OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_RS , OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_WR , OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_CS , OUTPUT_SPEED_50MHZ_PUSHPULL);
//	MGPIO_voidSetPinDirection(LCD_RD , OUTPUT_SPEED_50MHZ_PUSHPULL);

	GPIO_void_SetPinMode1(LCD_RST,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_RS,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_WR,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_CS,DIO_OUTPUT_PUSHPULL_50MHZ);
	GPIO_void_SetPinMode1(LCD_RD,DIO_OUTPUT_PUSHPULL_50MHZ);

//	MGPIO_voidSetPin(LCD_RD);
//	SET_BIT(GPIOB, LCD_RD % 16);

	GPIO_void_Write_Pin_Method1(LCD_RD, HIGH);

//	MGPIO_voidResetPin(LCD_CS);				          // because i use one TFT
//	CLEAR_BIT(GPIOB, LCD_CS % 16);

	GPIO_void_Write_Pin_Method1(LCD_CS, LOW);

//	MGPIO_voidSetPin(LCD_WR);                         // Idle state of Writing register
//	SET_BIT(GPIOB, LCD_WR % 16);

	GPIO_void_Write_Pin_Method1(LCD_WR, HIGH);

//	MGPIO_voidResetPin(LCD_RST);		       	      // Idle state of Reset
//	CLEAR_BIT(GPIOB, LCD_RST % 16);

	GPIO_void_Write_Pin_Method1(LCD_RST, LOW);

}



// Function to write 8-bit data to the TFT display
void HTFT_voidWriteData(u8 data)
{
	// Write data to the data bus (D0-D7)
//	MGPIO_voidSetPinValue(LCD_D0, (data & 0x01) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D1, (data & 0x02) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D2, (data & 0x04) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D3, (data & 0x08) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D4, (data & 0x10) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D5, (data & 0x20) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D6, (data & 0x40) ? GPIO_HIGH : GPIO_LOW);
//	MGPIO_voidSetPinValue(LCD_D7, (data & 0x80) ? GPIO_HIGH : GPIO_LOW);

	GPIO_void_Write_Pin_Method1(LCD_D0 , (data & 0x01) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D1 , (data & 0x02) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D2 , (data & 0x04) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D3 , (data & 0x08) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D4 , (data & 0x10) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D5 , (data & 0x20) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D6 , (data & 0x40) ? HIGH : LOW);
	GPIO_void_Write_Pin_Method1(LCD_D7 , (data & 0x80) ? HIGH : LOW);

	// Trigger write enable (toggle WR pin)
	// Function to toggle the WR pin (to simulate write clock)
//	MGPIO_voidResetPin(LCD_WR);                       // WR LOW
	GPIO_void_Write_Pin_Method1(LCD_WR, LOW);

//	MGPIO_voidSetPin(LCD_WR);                         // WR HIGH high
	GPIO_void_Write_Pin_Method1(LCD_WR, HIGH);
}


// Function to send a command to the TFT display
void HTFT_voidSendCommand(u8 cmd)
{
//	MGPIO_voidResetPin(LCD_RS);                       // RS low for command
	GPIO_void_Write_Pin_Method1(LCD_RS, LOW);
	HTFT_voidWriteData(cmd);


}


// Function to send data to the TFT display
void HTFT_voidSendData(u8 data)
{
//	MGPIO_voidSetPin(LCD_RS);                         // RS high for data
	GPIO_void_Write_Pin_Method1(LCD_RS, HIGH);
	HTFT_voidWriteData(data);
}


// Initialization function for the TFT display
void HTFT_voidInit(void) {
	// Initialize the GPIO pins
	HTFT_voidGPIOInit();

	// I must entering reset chape in the first  
//	MGPIO_voidSetPin  (LCD_RST);
	GPIO_void_Write_Pin_Method1(LCD_RST, HIGH);
//	MSTK_voidSetBusyWaitMicroSec(100);
	delay_us(100);
//	MGPIO_voidResetPin(LCD_RST);

	GPIO_void_Write_Pin_Method1(LCD_RST, LOW);

//	MSTK_voidSetBusyWaitMicroSec(1);
	delay_us(1);
//	MGPIO_voidSetPin  (LCD_RST);
	GPIO_void_Write_Pin_Method1(LCD_RST, HIGH);
//	MSTK_voidSetBusyWaitMicroSec(100);
	delay_us(100);
//	MGPIO_voidResetPin(LCD_RST);
	GPIO_void_Write_Pin_Method1(LCD_RST, LOW);

//	MSTK_voidSetBusyWaitMicroSec(100);
	delay_us(100);
//	MGPIO_voidSetPin  (LCD_RST);
	GPIO_void_Write_Pin_Method1(LCD_RST, HIGH);
//	MSTK_voidSetBusyWaitMillSec(120);
	delay_ms(120);
	// Send initialization commands to the display 
	HTFT_voidSendCommand(0x11);                           // Sleep out
//	MSTK_voidSetBusyWaitMillSec(150);
	delay_ms(150);
#if   MODE_COLOR  == RGB
	HTFT_voidSendCommand(0x36); // Memory Data Access Control (MADCTL)
	HTFT_voidSendData(0x00);    // Set RGB mode
#elif MODE_COLOR == BGR
	HTFT_voidSendCommand(0x36); // Memory Data Access Control (MADCTL)
	HTFT_voidSendData(0x08);    // Set BGR mode
#endif
	// other Command has parameters => Command send by function "LCD_Send_Command" && parameters of function send by function "LCD_Send_Data"    
	// Example: Set pixel format, orientation, etc.
	HTFT_voidSendCommand(0x3A);                           // Interface Pixel Format
	HTFT_voidSendData(0X05);                              // 16-bit color


	// Turn on display
	HTFT_voidSendCommand(0x29);                           // Display on
}

// Function to draw a pixel             
void HTFT_voidFillScreen(u16 color)
{

	u32 Local_u32counter;
	/*  Set X address */
	HTFT_voidSendCommand(0x2A);
	/* Set X address */
	/* Note: In two byte send high byte first then low */
	/* Start point is Two byte */
	HTFT_voidSendData(0);
	HTFT_voidSendData(0);
	/* end point is two byte   */
	HTFT_voidSendData(0);
	HTFT_voidSendData(239);

	/* Set Y address */
	/* Note: In two byte send high byte first then low */
	/* Start point is Two byte */
	HTFT_voidSendCommand(0x2B);
	HTFT_voidSendData(0);
	HTFT_voidSendData(0);
	/* end point  is two byte  */
	HTFT_voidSendData(0x01);
	HTFT_voidSendData(0x3f);

	/* RAM Write: this command because write on display  */
	HTFT_voidSendCommand(0x2C);
	for(Local_u32counter = 0; Local_u32counter <= 76800; Local_u32counter++)
	{
		/* Write the high byte */
		HTFT_voidSendData(color >> 8);
		/* Write the low byte */
		HTFT_voidSendData(color & 0x00ff);
	}
}


void HTFT_voidDrawRectangle(u8 x1, u8 x2, u16 y1, u16 y2, u16 color)
{
	// Validation: Ensure x2 > x1 and y2 > y1
	if (x2 <= x1 || y2 <= y1)
		return;

	// Calculate the size of the rectangle
	u32 size = (x2 - x1 + 1) * (y2 - y1 + 1); // Include boundary pixels

	// Set X address range
	HTFT_voidSendCommand(0x2A); // Set column address
	HTFT_voidSendData(0);       // High byte of x1
	HTFT_voidSendData(x1);      // Low byte of x1
	HTFT_voidSendData(0);       // High byte of x2
	HTFT_voidSendData(x2);      // Low byte of x2

	// Set Y address range
	HTFT_voidSendCommand(0x2B); // Set row address
	HTFT_voidSendData(0);       // High byte of y1
	HTFT_voidSendData(y1);      // Low byte of y1
	HTFT_voidSendData(0);       // High byte of y2
	HTFT_voidSendData(y2);      // Low byte of y2

	// RAM Write
	HTFT_voidSendCommand(0x2C); // Start writing to memory

	// Fill the rectangle with the specified color
	for (u32 i = 0; i < size; i++)
	{
		HTFT_voidSendData(color >> 8);    // Send high byte of color
		HTFT_voidSendData(color & 0x00FF); // Send low byte of color
	}
}
/************************************************************************************/
void HTFT_voidWriteString(u8 x, u16 y, const u8 *str, u16 color, u16 bgColor)
{
	u8 local_u8CountString=0;
	u8 cursorX = x;
	u16 cursorY = y;

	while (*str)
	{
#if FONT == FONT8_16
        if (*str == '\n')
        {
            cursorY += 16;
            cursorX = x;
            local_u8CountString = 0;  // Reset count on newline
        }
        else if (*str != '\r')
        {
            HTFT_voidDrawChar(cursorX, cursorY, *str, color, bgColor);
            cursorX += 8;
            local_u8CountString++;
        }

        // Check for line wrap after 13 characters
        if (local_u8CountString >= 20) // Adjusted for smaller font size
        {
            cursorY += 16;
            cursorX = x;
            local_u8CountString = 0;
        }
        str++;  // Ensure increment after every iteration
#elif FONT == FONT16_32
		if (*str == '\n') // Handle newline character
		{
			cursorY += 32; // Move to the next line (font height)
			cursorX = x;   // Reset to the start of the line
			local_u8CountString = 0;  // Reset count on newline
		}
		else if (*str != '\r')
		{
			HTFT_voidDrawChar(cursorX, cursorY, *str, color, bgColor);
			cursorX += 16;
			local_u8CountString++;
		}
		// Check for line wrap after 13 characters
		if (local_u8CountString >= 13)
		{
			cursorY += 32;
			cursorX = x;
			local_u8CountString = 0;
		}
		str++;  // Ensure increment after every iteration
#endif
	}
}

void HTFT_voidDrawChar(u8 x, u16 y, u8 c, u16 color, u16 bgColor)
{

#if FONT == FONT8_16
	const u8 *charBitmap = font8x16[c - ' ']; // Assume font data starts at ASCII space (32)
	u8 reversedBitmap[16];  // To store the reversed bitmap
	for (int i = 0; i < 16; i++) {
		reversedBitmap[i] = reverseByte(charBitmap[i]);  // Reverse each byte
	}
	for (u8 row = 0; row < 16; row++) // Font height is 16 pixels
	{
		for (u8 col = 0; col < 8; col++) // Font width is 8 pixels
		{
			if (reversedBitmap[row] & (1 << col))
			{
				HTFT_voidDrawPixel(x + col, y + row, color); // Draw pixel in foreground color
			}
			else
			{
				HTFT_voidDrawPixel(x + col, y + row, bgColor); // Draw pixel in background color
			}
		}
	}


#elif FONT == FONT16_32
	const u16 *charBitmap = font16x32[c - ' '];  // Get the bitmap pointer
	u16 reversedBitmap[64];  // To store the reversed bitmap
	for (int i = 0; i < 64; i++)
	{
	    reversedBitmap[i] = reverseTwoBytes(charBitmap[i]);  // Reverse each byte
	}

	for (u8 row = 0; row < 32; row++) // Font height is 32 pixels
	{
		for (u8 col = 0; col < 16; col++) // Font width is 16 pixels
		{
			if (reversedBitmap[row] & (1 << col))
			{
				HTFT_voidDrawPixel(x + col, y + row, color); // Draw pixel in foreground color
			}
			else
			{
				HTFT_voidDrawPixel(x + col, y + row, bgColor); // Draw pixel in background color
			}
		}
	}
#endif
}

void HTFT_voidDrawPixel(u8 x, u16 y, u16 color)
{
	// Set address range and draw a single pixel at (x, y) with the given color
	HTFT_voidSetPixelAddress(x, y, x, y);
	// RAM Write
	HTFT_voidSendCommand(0x2C);		// Start writing to memory
	HTFT_voidSendData(color >> 8);
	HTFT_voidSendData(color & 0x00FF);
}

void HTFT_voidSetPixelAddress(u8 x1, u16 y1, u8 x2, u16 y2)
{

	HTFT_voidSendCommand(0x2A); // Set X address
	HTFT_voidSendData(0);
	HTFT_voidSendData(x1);
	HTFT_voidSendData(0);
	HTFT_voidSendData(x2);
	if(y1<256)
	{
		HTFT_voidSendCommand(0x2B); // Set Y address
		HTFT_voidSendData(0);
		HTFT_voidSendData(y1);
		HTFT_voidSendData(0);
		HTFT_voidSendData(y2);
	}
	else if(y1>255)
	{
		u8 local_u8NewY1;
		u8 local_u8NewY2;
		local_u8NewY1 = y1-255;
		local_u8NewY2 = y2-255;
		HTFT_voidSendCommand(0x2B); // Set Y address
		HTFT_voidSendData(0X01);
		HTFT_voidSendData(local_u8NewY1);
		HTFT_voidSendData(0x01);
		HTFT_voidSendData(local_u8NewY2);

	}
}

u16 reverseTwoBytes(u16 value) {
    value = (value & 0xFF00) >> 8 | (value & 0x00FF) << 8;  // Swap bytes
    value = (value & 0xF0F0) >> 4 | (value & 0x0F0F) << 4;  // Swap nibbles
    value = (value & 0xCCCC) >> 2 | (value & 0x3333) << 2;  // Swap pairs
    value = (value & 0xAAAA) >> 1 | (value & 0x5555) << 1;  // Swap bits
    return value;
}

u8 reverseByte(u8 byte) {
 byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
 byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
 byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
 return byte;
 }
/*****************************************************************************************/

