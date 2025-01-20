/*
 * Keypad_interface_interrupt.h
 *
 * Created: 03/06/2024 01:56:28
 *  Author: Mohammed Khalaf
 */ 


#ifndef KEYPAD_INTERFACE_INTERRUPT_H_
#define KEYPAD_INTERFACE_INTERRUPT_H_


#include "KEYPAD_Config_Interrupt.h"

void KEYPAD_init_interrupt(void);
u8 KEYPAD_Scan(void);
u8 KEYPAD_GetKey_interrupt(void);




#endif /* KEYPAD_INTERFACE_INTERRUPT_H_ */