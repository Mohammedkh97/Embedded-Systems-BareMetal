/***************************************************************/
/* Author		: Ahmed Hssein                                 */
/* Date         : 1 Jan. 2025    							   */
/* Version		: V01										   */
/***************************************************************/

#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H




#define COLOR_BLACK       0x0000  // Black
#define COLOR_WHITE       0xFFFF  // White
#define COLOR_RED         0xF800  // Red
#define COLOR_GREEN       0x07E0  // Green
#define COLOR_BLUE        0x001F  // Blue
#define COLOR_CYAN        0x07FF  // Cyan
#define COLOR_MAGENTA     0xF81F  // Magenta
#define COLOR_YELLOW      0xFFE0  // Yellow
#define COLOR_ORANGE      0xFC00  // Orange
#define COLOR_PURPLE      0x8010  // Purple
#define COLOR_PINK        0xF81F  // Pink (alternative to Magenta)
#define COLOR_GRAY        0x8410  // Gray
#define COLOR_BROWN       0xA145  // Brown
#define COLOR_LIGHT_BLUE  0x051F  // Light Blue
#define COLOR_LIGHT_GREEN 0x07EF  // Light Green
#define COLOR_LIGHT_GRAY  0xC618  // Light Gray
#define COLOR_DARK_GRAY   0x4208  // Dark Gray
#define COLOR_GOLD        0xFEA0  // Gold
#define COLOR_SILVER      0xC618  // Silver


// Define the pins for the parallel data bus (D0 to D7)
#define LCD_D0    PINA0   // PA0
#define LCD_D1    PINA1   // PA1
#define LCD_D2    PINA2   // PA2
#define LCD_D3    PINA3   // PA3
#define LCD_D4    PINA4   // PA4
#define LCD_D5    PINA5   // PA5
#define LCD_D6    PINA6   // PA6
#define LCD_D7    PINA7   // PA7

// Define the pins for control signals
#define LCD_RST   PINB0   // PB0
#define LCD_CS    PINB1   // PB1
#define LCD_RS    PINB10  // PB10
#define LCD_WR    PINB11  // PB11
#define LCD_RD 	  PINB12  // PB12
/*LCD_RD: Can you connected to PB12 => Low you are reading from TFT 
                                       High you are writing to TFT 
									  (connected to 3.3V for write-only mode) */


/******************************************************************************/
// Function to initialize the GPIOs of TFT
void HTFT_voidGPIOInit(void);                                                         

// Function to write 8-bit data to the TFT display
void HTFT_voidWriteData(u8 data);

 // Function to send command
void HTFT_voidSendCommand(u8 cmd);

 // Function to send data
void HTFT_voidSendData(u8 data);

// Initialization function for the TFT display                                             
void HTFT_voidInit(void);

// Function to draw a pixel
//void HTFT_voidDiaplayImage(void);

// Function to FillScreen
void HTFT_voidFillScreen(u16 color);

// Function to draw rectangle
void HTFT_voidDrawRectangle(u8 x1, u8 x2, u16 y1, u16 y2, u16 color);

/******************************************************************************/
// functions to write string
void HTFT_voidWriteString(u8 x, u16 y, const u8 *str, u16 color, u16 bgColor);

void HTFT_voidDrawChar(u8 x, u16 y, u8 c, u16 color, u16 bgColor);

void HTFT_voidDrawPixel(u8 x, u16 y, u16 color);

void HTFT_voidSetPixelAddress(u8 x1, u16 y1, u8 x2, u16 y2);

u16 reverseTwoBytes(u16 value);

u8 reverseByte(u8 byte);
/******************************************************************************/
#endif
