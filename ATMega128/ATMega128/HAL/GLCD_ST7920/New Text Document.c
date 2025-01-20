#define F_CPU 16000000UL // Define the clock speed of your MCU
#include <avr/io.h>
#include <util/delay.h>
// #include "DIO_interface.h"  // Assuming you have a DIO interface library
//  Define the pins connected to the ST7920
#define RST_PIN PB5
#define CS_PIN PB0
#define SID_PIN PB2
#define SCLK_PIN PB1

void init_pins(void)
{
	// Set RST, CS, SID, and SCLK as output
	DDRB |= (1 << RST_PIN) | (1 << CS_PIN) | (1 << SID_PIN) | (1 << SCLK_PIN);
	// Set the default states
	PORTB |= (1 << RST_PIN);   // RST high
	PORTB &= ~(1 << CS_PIN);   // CS low (disable chip)
	PORTB &= ~(1 << SID_PIN);  // SID low
	PORTB &= ~(1 << SCLK_PIN); // SCLK low
}

void GLCD_SPI_SendData(u8 data)
{
	for (u8 i = 0; i < 8; i++)
	{
		if ((data << i) & 0x80)
		{
			PORTB |= (1 << SID_PIN); // Set SID high
		}
		else
		{
			PORTB &= ~(1 << SID_PIN); // Set SID low
		}
		PORTB |= (1 << SCLK_PIN);  // Set SCLK high
		_delay_us(1);			   // Small delay
		PORTB &= ~(1 << SCLK_PIN); // Set SCLK low
	}
}

void GLCD_ST7920_SendCommand(u8 Command)
{
	PORTB |= (1 << CS_PIN);					  // Set CS high (enable chip)
	GLCD_SPI_SendData(0xF8 | (0 << 1));		  // Send the SYNC + RS(0)
	GLCD_SPI_SendData(Command & 0xF0);		  // Send The Higher Nibble first
	GLCD_SPI_SendData((Command << 4) & 0xF0); // Send The Lower Nibble
	_delay_us(100);
	PORTB &= ~(1 << CS_PIN); // Set CS low (disable chip)
}

void GLCD_ST7920_SendData(u8 data)
{
	PORTB |= (1 << CS_PIN);				   // Set CS high (enable chip)
	GLCD_SPI_SendData(0xF8 | (1 << 1));	   // Send the SYNC + RS(1)
	GLCD_SPI_SendData(data & 0xF0);		   // Send The Higher Nibble first
	GLCD_SPI_SendData((data << 4) & 0xF0); // Send The Lower Nibble
	_delay_us(100);
	PORTB &= ~(1 << CS_PIN); // Set CS low (disable chip)
}


void reset_st7920(void)
{
	PORTB &= ~(1 << RST_PIN); // Set RST low
	_delay_ms(10);			  // Wait for 10ms
	PORTB |= (1 << RST_PIN);  // Set RST high
	_delay_ms(10);			  // Wait for 10ms
}

void GLCD_ST7920_init(void)
{
	reset_st7920();
	GLCD_ST7920_SendCommand(0x30); // Basic instruction set
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x30); // Repeat
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x08); // Display off
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x01); // Clear display
	_delay_ms(10);
	GLCD_ST7920_SendCommand(0x06); // Entry mode set: increment mode
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x0C); // Display on
	_delay_ms(1);
	GLCD_ST7920_SendCommand(0x02); // Return Home
	_delay_ms(1);
}

void GLCD_ST7920_WriteChar(u8 row, u8 col, u8 character)
{
	u8 position = 0x80; // Start position for the first row
	if (row > 0)
	{
		position += 0x10; // Move to the second row
	}
	position += col; // Adjust the column position

	GLCD_ST7920_SendCommand(position); // Set the cursor position
	GLCD_ST7920_SendData(character);   // Write the character to the display
}

void GLCD_ST7920_WriteNumber(u8 row, u8 col, u16 number)
{
	char buffer[6]; // Assuming a 5-digit number is the maximum to be displayed
	// intoString(number , buffer);
	itoa(number, buffer, 10);							 // Convert the number to a string
	GLCD_ST7920_SendString(row, col, (uint8_t *)buffer); // Write the string to the display
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

int main(void)
{
	init_pins();
	GLCD_ST7920_init();
	while (1)
	{
		GLCD_ST7920_WriteNumber(2, 1, -65);
	}
}

/*
void init_pins(void) {
// Set RST, CS, SID, and SCLK as output
DIO_init();
// Set the default states
DIO_WritePin1(RST_PIN , HIGH);
DIO_WritePin1(RS_PIN , LOW);
DIO_WritePin1(RW_PIN , LOW);
DIO_WritePin1(EN_PIN , LOW);
}
void GLCD_SPI_SendData(u8 data)
{
for (u8 i = 0; i < 8; i++)
{
if ((data << i) & 0x80)
{
PORTB |= (1 << SID_PIN); // Set SID high
}
else
{
PORTB &= ~(1 << SID_PIN); // Set SID low
}
PORTB |= (1 << SCLK_PIN);  // Set SCLK high
_delay_us(1);			   // Small delay
PORTB &= ~(1 << SCLK_PIN); // Set SCLK low
}
}

void GLCD_ST7920_SendCommand(u8 Command)
{
PORTB |= (1 << CS_PIN);					  // Set CS high (enable chip)
GLCD_SPI_SendData(0xF8 | (0 << 1));		  // Send the SYNC + RS(0)
GLCD_SPI_SendData(Command & 0xF0);		  // Send The Higher Nibble first
GLCD_SPI_SendData((Command << 4) & 0xF0); // Send The Lower Nibble
_delay_us(100);
PORTB &= ~(1 << CS_PIN); // Set CS low (disable chip)
}

void GLCD_ST7920_SendData(u8 data)
{
PORTB |= (1 << CS_PIN);				   // Set CS high (enable chip)
GLCD_SPI_SendData(0xF8 | (1 << 1));	   // Send the SYNC + RS(1)
GLCD_SPI_SendData(data & 0xF0);		   // Send The Higher Nibble first
GLCD_SPI_SendData((data << 4) & 0xF0); // Send The Lower Nibble
_delay_us(100);
PORTB &= ~(1 << CS_PIN); // Set CS low (disable chip)
}


void reset_st7920(void)
{
PORTB &= ~(1 << RST_PIN); // Set RST low
_delay_ms(10);			  // Wait for 10ms
PORTB |= (1 << RST_PIN);  // Set RST high
_delay_ms(10);			  // Wait for 10ms
}

void GLCD_ST7920_init(void)
{
reset_st7920();
GLCD_ST7920_SendCommand(0x30); // Basic instruction set
_delay_ms(1);
GLCD_ST7920_SendCommand(0x30); // Repeat
_delay_ms(1);
GLCD_ST7920_SendCommand(0x08); // Display off
_delay_ms(1);
GLCD_ST7920_SendCommand(0x01); // Clear display
_delay_ms(10);
GLCD_ST7920_SendCommand(0x06); // Entry mode set: increment mode
_delay_ms(1);
GLCD_ST7920_SendCommand(0x0C); // Display on
_delay_ms(1);
GLCD_ST7920_SendCommand(0x02); // Return Home
_delay_ms(1);
}

void GLCD_ST7920_WriteChar(u8 row, u8 col, u8 character)
{
u8 position = 0x80; // Start position for the first row
if (row > 0)
{
position += 0x10; // Move to the second row
}
position += col; // Adjust the column position

GLCD_ST7920_SendCommand(position); // Set the cursor position
GLCD_ST7920_SendData(character);   // Write the character to the display
}

void GLCD_ST7920_WriteNumber(u8 row, u8 col, u16 number)
{
char buffer[6]; // Assuming a 5-digit number is the maximum to be displayed
// intoString(number , buffer);
itoa(number, buffer, 10);							 // Convert the number to a string
GLCD_ST7920_SendString(row, col, (uint8_t *)buffer); // Write the string to the display
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

int main(void)
{
DIO_init();
init_pins();
GLCD_ST7920_init();
GLCD_ST7920_SendString(1,4,(u8*)"Welcome");
GLCD_ST7920_WriteNumber(2,0,1);
_delay_ms(10);
GLCD_ST7920_WriteNumber(2,1,2);
_delay_ms(10);
GLCD_ST7920_WriteNumber(2,7,3);
_delay_ms(10);

while (1)
{

}
}*/