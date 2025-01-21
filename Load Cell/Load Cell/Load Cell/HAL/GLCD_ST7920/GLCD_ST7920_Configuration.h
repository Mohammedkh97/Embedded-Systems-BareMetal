/*
 * GLCD_ST7920_Configuration.h
 *
 * Created: 25/07/2024 00:49:31
 *  Author: Mohammed Khalaf
 */ 


#ifndef GLCD_ST7920_CONFIGURATION_H_
#define GLCD_ST7920_CONFIGURATION_H_

#define EN_PIN		PINB1		//SCLK
#define RS_PIN		PINB0		//CS -- SS 
#define RW_PIN		PINB2		//SID (RW)   LCD_SID  MOSI PIN
#define RST_PIN		PINB5

#define RST_PIN		PINB5
#define CS_PIN		PINB0
#define SID_PIN		PINB2
#define SCLK_PIN	PINB1

#define GLCD_4_BIT     1
#define GLCD_8_BIT     2

#define GLCD_MODE   _4_BIT

#endif /* GLCD_ST7920_CONFIGURATION_H_ */