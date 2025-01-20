/*
 * KEYPAD_interface.h
 *
 * Created: 8/22/2022 6:08:43 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/* ======================= Inclusions ====================== */
#include "GPIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"



/* ======================= Functions Prototypes ====================== */
void KEYPAD_init(void);
u8	KEYPAD_GetKey(void);



#endif /* KEYPAD_INTERFACE_H_ */
