/*
 * KEYPAD_Config.h
 * Created: 03/06/2024 01:48:09
 *  Author: Mohammed Khalaf
 */ 

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define FIRST_OUTPUT    PIND4

#define FIRST_INPUT     PIND0

#define ROW		4
#define COL		4

#define NO_KEY  'X'

#define EXTERNAL_INT_VECTOR			INT0_vect
#define ENABLE_INTERRUPT			sei
#define DISABLE_INTERRUPT			cli

#ifdef  KEYPAD_PROG
u8 KeysArray[ROW][COL] = {	{'7' , '8' , '9' , '/'},
							{'4' , '5' , '6' , '*'},
							{'1' , '2' , '3' , '-'},
							{'C' , '0' , '=' , '+'}};

#endif



#endif /* KEYPAD_CONFIG_H_ */