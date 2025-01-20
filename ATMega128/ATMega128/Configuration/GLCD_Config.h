/*
 * GLCD_Config.h
 *
 * Created: 6/24/2024 12:00:36 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef GLCD_CONFIG_H_
#define GLCD_CONFIG_H_

/************************************** MODE SELECTION  *******************************/
#define EIGHT_BIT_MODE			8
#define FOUR_BIT_MODE			4
#define MODE_SERIAL				1 

#define GLCD_MODE				FOUR_BIT_MODE

/************************************************************************/
/*							 PIN CONFIGURATION							*/
/************************************************************************/

#define GLCD_RS				PINC0
#define GLCD_RW				PINC1    // Optional (in normal usage we usually read from LCD only 
#define GLCD_EN				PINC2
#define GLCD_PORT_DATA		PORTD

#if GLCD_MODE == EIGHT_BIT_MODE

#define GLCD_D0     PINC4
#define GLCD_D1     PINC5
#define GLCD_D2     PINC6
#define GLCD_D3     PINC7
#define GLCD_D4     PIND0
#define GLCD_D5     PIND1
#define GLCD_D6     PIND2
#define GLCD_D7     PIND3

#define GLCD_PORT   GLCD_PORT_DATA

#elif GLCD_MODE == FOUR_BIT_MODE

#define GLCD_D4     PIND0
#define GLCD_D5     PIND1
#define GLCD_D6     PIND2
#define GLCD_D7     PIND3


/* Control macros */
/*
#define GLCD_EN_HIGH()      (PORTC |= (1 << GLCD_EN))
#define GLCD_EN_LOW()       (PORTC &= ~(1 << GLCD_EN))

#define GLCD_CMD_MODE()     (PORTC &= ~(1 << GLCD_RS))
#define GLCD_DATA_MODE()    (PORTC |= (1 << GLCD_RS))

#define GLCD_RW_HIGH()      (PORTC |= (1 << GLCD_RW))
#define GLCD_RW_LOW()       (PORTC &= ~(1 << GLCD_RW))

#define GLCD_DATA_DDR_OUTPUT()  DDRD = 0xff
#define GLCD_DATA_DDR_INPUT()   DDRD = 0x00
*/
#endif /* GLCD_CONFIG_H_ */