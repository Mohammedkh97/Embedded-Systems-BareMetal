/*
 * GLCD_ST7920_Interface.h
 *
 * Created: 25/07/2024 00:11:12
 * Author: Mohammed Khalaf
 */

#ifndef GLCD_ST7920_GLCD_ST7920_INTERFACE_H_
#define GLCD_ST7920_GLCD_ST7920_INTERFACE_H_

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



// Function prototypes

//void st7920_spi_pins_init();
//void st7920_spi_config();
//void st7920_spi_transmit(uint8_t *data,uint32_t size);
void GLCD_SPI_SendData(u8 data);
//void GLCD_SPI_SendData (u8 data);
void init_pins(void);
void GLCD_ST7920_init(void);
void GLCD_ST7920_Clear(void);

void GLCD_ST7920_SendCommand(u8 Command);
void GLCD_ST7920_SendData(u8 data);
void GLCD_ST7920_ClearArea(u8 row, u8 col, u8 length);

void GLCD_ST7920_WriteChar(u8 row, u8 col, u8 character);
void GLCD_ST7920_WriteNumber(u8 row, u8 col, s32 number , u8 ClearArea);
void GLCD_ST7920_WriteFloatNumber(u8 row, u8 col, f64 number, u8 decimalPlaces, u8 ClearArea);
void GLCD_ST7920_SendString(u8 row , u8 col , u8* string);

//Control GLCD Display:
void GLCD_ST7920_DisplayCurrentPage();
void GLCD_ST7920_DisplayPage1();
void GLCD_ST7920_DisplayPage2();
void GLCD_ST7920_DisplayPage3();
void GLCD_ST7920_NextPage();
void GLCD_ST7920_PreviousPage();

void GLCD_ST7920_GraphicMode(s16 enable);
void GLCD_ST7920_DrawBitMap(const u8* graphic);

// Set a pixel on the display
void SetPixel(u8 x, u8 y);
void DrawLine(u8 x0, u8 y0, u8 x1, u8 y1);
void DrawRectangle(u16 x, u16 y, u16 w, u16 h);
void DrawFilledRectangle(u16 x, u16 y, u16 w, u16 h);
void DrawCircle(u8 x0, u8 y0, u8 radius);
void DrawFilledCircle(s16 x0, s16 y0, s16 r);
void DrawTriangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3);
void DrawFilledTriangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3);
void updateScreen();

#endif /* GLCD_ST7920_GLCD_ST7920_INTERFACE_H_ */
