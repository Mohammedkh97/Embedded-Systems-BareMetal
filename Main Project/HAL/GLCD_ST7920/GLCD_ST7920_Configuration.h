/*
 * GLCD_ST7920_Configuration.h
 *
 * Created: 25/07/2024 00:49:31
 *  Author: Mohammed Khalaf
 */ 


#ifndef GLCD_ST7920_CONFIGURATION_H_
#define GLCD_ST7920_CONFIGURATION_H_

#define EN_PIN		PINA5		//SCLK
#define RS_PIN		PINA6		//CS -- SS
#define RW_PIN		PINA7		//SID (RW)   LCD_SID  MOSI PIN
#define RST_PIN		PINB0

#define LCD_WIDTH		128
#define LCD_HEIGHT		64
#define TOTAL_PAGES		3

#define GLCD_4_BIT     1
#define GLCD_8_BIT     2

#define GLCD_MODE   _4_BIT

#endif /* GLCD_ST7920_CONFIGURATION_H_ */
