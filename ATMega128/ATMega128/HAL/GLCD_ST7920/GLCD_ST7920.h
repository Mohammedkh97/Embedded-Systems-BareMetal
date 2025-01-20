/*
 * GLCD_ST7920.h
 *
 * Created: 25/07/2024 00:11:12
 *  Author: Mohammed Khalaf
 */ 


#ifndef GLCD_ST7920_H_
#define GLCD_ST7920_H_
/* ************************************************************************
 *
 *   driver functions for ST7920 compatible graphic displays
 *   - 128 x 64 pixels
 *   - other resolutions are not supported because of different address
 *     to pixel mappings
 *     (64 x 32 pixels native, with ST7921s up to 256 x 64)
 *   - SPI interface (2-4 line)
 *   - 4 bit parallel interface
 *
 * ************************************************************************ */

/*
 *  hints:
 *  - pin assignment for SPI
 *    /XRESET    LCD_RESET (optional)
 *    CS (RS)    LCD_CS (optional)
 *    SCLK (E)   LCD_SCLK
 *    SID (RW)   LCD_SID
 *    PSB        Gnd (enable serial mode)
 *    For hardware SPI LCD_SCLK and LCD_SID have to be the MCU's SCK and
 *    MOSI pins.
 *  - max. SPI clock: 2.5MHz at 4.5V / 1.6MHz at 2.7V 
 *  - write only when using SPI
 *  - doesn't allow other SPI chips on same bus (says the datasheet)
 *  - pin assignment for 4 bit parallel
 
 *    /XRESET    LCD_RESET (optional)
 *    E          LCD_EN
 *    RS         LCD_RS
 *    RW         Gnd or LCD_RW (optional)
 *    D4         LCD_DB4 (default: LCD_PORT Bit #0)
 *    D5         LCD_DB5 (default: LCD_PORT Bit #1)
 *    D6         LCD_DB6 (default: LCD_PORT Bit #2)
 *    D7         LCD_DB7 (default: LCD_PORT Bit #3)
 *    PSB        pull-up resistor to VCC (enable parallel mode)
 */


#define LCD_WIDTH 128
#define LCD_HEIGHT 64

u8  graphicsBuffer[LCD_WIDTH * LCD_HEIGHT / 8];
// Function prototypes
void init_pins(void);
void GLCD_ST7920_init(void);
void GLCD_ST7920_Clear(void);
void GLCD_SPI_SendData(u8 data);

void GLCD_ST7920_SendCommand(u8 Command);
void GLCD_ST7920_SendData(u8 data);
void GLCD_ST7920_ClearArea(u8 row, u8 col, u8 length);
void GLCD_ST7920_WriteChar(u8 row, u8 col, u8 character);
void GLCD_ST7920_WriteNumber(u8 row, u8 col, u16 number);
void GLCD_ST7920_SendString(u8 row , u8 col , u8* string);
void GLCD_ST7920_GraphicMode(s16 enable);
void setPixel(int x, int y, u8 on);
/*
const uint8_t LcdDisplayClear = 0x01;
const uint8_t LcdHome = 0x02;
const uint8_t LcdEntryModeSet = 0x06;       // move cursor right and increment address when writing data
const uint8_t LcdDisplayOff = 0x08;
const uint8_t LcdDisplayOn = 0x0C;          // add 0x02 for cursor on and/or 0x01 for cursor blink on
const uint8_t LcdFunctionSetBasicAlpha = 0x20;
const uint8_t LcdFunctionSetBasicGraphic = 0x22;
const uint8_t LcdFunctionSetExtendedAlpha = 0x24;
const uint8_t LcdFunctionSetExtendedGraphic = 0x26;
const uint8_t LcdSetDdramAddress = 0x80;    // add the address we want to set

// LCD extended instructions
const uint8_t LcdSetGdramAddress = 0x80;

const unsigned int LcdCommandDelayMicros = 72;		  // 72us required
const unsigned int LcdDataDelayMicros = 6;         	// Delay between sending data bytes
const unsigned int LcdDisplayClearDelayMillis = 3;  // 1.6ms should be enough

const unsigned int numRows = 64;
const unsigned int numCols = 128;
*/

#endif /* GLCD_ST7920_H_ */