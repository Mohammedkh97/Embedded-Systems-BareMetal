/*
 * LCD_private.h
 *
 * Created: 8/20/2022 10:24:12 AM
 *  Author: Mohammed Khalaf
 */


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/* ====================== Private Macros ===================== */
#define _4_BIT_MODE				1
#define _8_BIT_MODE				2

#define LINE_1_ADDRESS			0x80
#define LINE_2_ADDRESS			0xC0
#define LINE_3_ADDRESS			0x94
#define LINE_4_ADDRESS			0xD4

#define CGRAM_ADDRESS			0x40
#define DDRAM_ADDRESS			0x80

#define _4_BIT_MODE_COMMAND		0x02

/* Function Set Mask */
#define DATA_LENGTH_8BIT		0x34
#define DATA_LENGTH_4BIT		0x20

#define NUMBER_LINES_1			0x24
#define NUMBER_LINES_2			0x28

#if LCD_BIT_MODE == _8_BIT_MODE
	#define DATA_LENGTH			DATA_LENGTH_8BIT

#elif LCD_BIT_MODE == _4_BIT_MODE
	#define DATA_LENGTH			DATA_LENGTH_4BIT
#else
	#error	"You chose a wrong Mode !!!"

#endif

#define FUNCTION_SET_MASK		DATA_LENGTH | NUMBER_LINES

/* Clear Screen Mask */
#define CLEAR_SCREEN			0x01

/* Display ON/OFF Mask */
#define DISPLAY_ON				0x0C
#define DISPLAY_OFF				0x08

#define	CURSOR_ON				0xA
#define	CURSOR_OFF				0x8

#define BLINK_CURSOR_ON			0x09
#define BLINK_CURSOR_OFF		0x08

#define DISPLAY_ON_OFF_MASK		DISPLAY_ON_OFF | CURSOR_ON_OFF | BLINK_CURSOR_ON_OFF

/* Entry Mode Set */
#define I_DDRAM_ADDR_SHIFT_LEFT		0x07
#define D_DDRAM_ADDR_SHIFT_RIGHT	0x05

#define I_DDRAM_ADDR_NO_SHIFT		0x06
#define D_DDRAM_ADDR_NO_SHIFT		0x04

/* ======================= Private Functions Prototypes ====================== */

//static void	LCD_WriteCommand(u8 Copy_u8Command);
//static void write_instruction(u8 instruction);

#endif /* LCD_PRIVATE_H_ */
