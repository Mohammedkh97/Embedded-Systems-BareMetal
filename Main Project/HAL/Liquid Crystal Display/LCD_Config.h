/*
* LCD_Config.h
*
* Created: 10/24/2023 12:48:43 PM
*  Author: Mohammed Khalaf
*/


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* _4_BIT MODE, _8_BIT MODE */

#define _4_BIT     1
#define _8_BIT     2

#define LCD_MODE   _4_BIT


#define RS     PINA11
#define EN     PINA10

#define D4     PINA12
#define D5     PINA13
#define D6     PINA14
#define D7     PINA15

//#define LCD_PORT PD


/*KIT Connections */
/*
#define D4     PINA3
#define D5     PINA4
#define D6     PINA5
#define D7     PINA6

#define RS     PINA1
#define EN     PINA2

*/
//#define LCD_PORT PA



/*#if LCD_MODE == _4_BIT

#define RS    PIND5
#define EN    PIND7

#define D7     PIND3
#define D6     PIND2
#define D5     PIND1
#define D4     PIND0

#elif LCD_MODE _8_BIT

#define RS    PINB1
#define EN    PINB0

#define LCD_PORT PA
#endif*/


/* ====================== LCD Configurations  ===================== */
/*
	Options :
			- _4_BIT_MODE
			- _8_BIT_MODE
*/
#define LCD_BIT_MODE		_4_BIT_MODE

/* Pins Configurations */
#define LCD_DATA_PORT		PORTD_INDEX

#define RS_PORT				PORTA_INDEX
#define RS_PIN				PIN1_INDEX

#define EN_PORT				PORTA_INDEX
#define EN_PIN				PIN2_INDEX

/* 4 Bit Configurations */
#define D7_PIN				PIN6_INDEX
#define D7_PORT				PORTA_INDEX

#define D6_PIN				PIN5_INDEX
#define D6_PORT				PORTA_INDEX

#define D5_PIN				PIN4_INDEX
#define D5_PORT				PORTA_INDEX

#define D4_PIN				PIN3_INDEX
#define D4_PORT				PORTA_INDEX

/* ====================== Function Set Configurations ===================== */

/*
	Options :
			- NUMBER_LINES_1
			- NUMBER_LINES_2
*/
#define NUMBER_LINES		NUMBER_LINES_2

/* ====================== Display ON/OFF Configurations ====================== */
/*
	Options :
			- DISPLAY_ON
			- DISPLAY_OFF
*/

#define DISPLAY_ON_OFF		DISPLAY_ON

/*
	Options :
			- CURSOR_ON
			- CURSOR_OFF
*/
#define CURSOR_ON_OFF		CURSOR_OFF

/*
	Options :
			- BLINK_CURSOR_ON
			- BLINK_CURSOR_OFF
*/
#define BLINK_CURSOR_ON_OFF		BLINK_CURSOR_OFF

/*
	Options :
			- I_DDRAM_ADDR_SHIFT_LEFT
			- D_DDRAM_ADDR_SHIFT_RIGHT

			- I_DDRAM_ADDR_NO_SHIFT
			- D_DDRAM_ADDR_NO_SHIFT
*/

#define ENTRY_MODE_SET		I_DDRAM_ADDR_NO_SHIFT

#endif /* LCD_CONFIG_H_ */


