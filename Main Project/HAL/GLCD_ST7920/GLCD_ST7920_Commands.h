/*
 * GLCD_ST7920_Commands.h
 *
 * Created: 27/07/2024 18:53:06
 *  Author: Mohammed Khalaf
 */ 


#ifndef GLCD_ST7920_COMMANDS_H_
#define GLCD_ST7920_COMMANDS_H_

// GLCD Commands for ST7920

// Basic instruction set
#define GLCD_BASIC_INSTRUCTION_SET     0x30

// Display off (D=0, C=0, B=0)
#define GLCD_DISPLAY_OFF               0x08

// Clear display
#define GLCD_CLEAR_DISPLAY             0x01

// Entry mode set (Cursor increment, No Shift)
#define GLCD_ENTRY_MODE                0x06

// Display ON (D=1, C=0, B=0)
#define GLCD_DISPLAY_ON                0x0C

// Return home
#define GLCD_RETURN_HOME               0x02


#endif /* GLCD_ST7920_COMMANDS_H_ */
