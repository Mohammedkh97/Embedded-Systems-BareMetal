/*
* LCD_TFT_Config.h
*
* Created: 04/06/2024 14:13:29
*  Author: Mohammed Khalaf
*/


#ifndef LCD_TFT_CONFIG_H_
#define LCD_TFT_CONFIG_H_

/************************************************************************/
/*						HARDWARE DEFINITION                             */
/************************************************************************/

  #define PORT_DATA     PORTD
  #define DDR_DATA      DDRD
  #define PIN_DATA      PIND

/************************************************************************/
/*					Control Pins Definitions                            */
/************************************************************************/

#define DDR_CONTROL   DDRA
#define PORT_CONTROL  PORTA

#define PIN_RST       PINA0		// Reset LCD MCU
#define PIN_CS        PINA1     // Chip Select
#define PIN_RS        PINA2     // Register Select -> D/C
#define PIN_WR        PINA3     // Write Data
#define PIN_RD        PINA4     // Read Data 

// LCD Dimensions
// ---------------------------------------------------------------

// max columns
#define ILI9341_MAX_X         240
// max rows
#define ILI9341_MAX_Y         320
// columns max counterer
#define ILI9341_SIZE_X        ILI9341_MAX_X - 1
// rows max counterer
#define ILI9341_SIZE_Y        ILI9341_MAX_Y - 1
// whole pixels
#define ILI9341_CACHE_MEM     (ILI9341_MAX_X * ILI9341_MAX_Y)



#endif /* LCD_TFT_CONFIG_H_ */