/*
 * EXTI_Interface.h
 *
 *  Created on: Oct 5, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_

/******************  EXTI Modes  ******************************/

typedef enum {
    EXTI_MODE_RISING          = 0x01, // Trigger on Rising Edge
    EXTI_MODE_FALLING         = 0x02, // Trigger on Falling Edge
    EXTI_MODE_RISING_FALLING  = 0x03, // Trigger on Both Edges   ON CHANGE / LEVEL CHANGE
    EXTI_MODE_SOFTWARE        = 0x04  // Software Trigger
} EXTI_Mode_t;

/*******************   LINE Definition     ***************************/
typedef enum {
    EXTI_LINE_0  = 0,  // EXTI Line 0
    EXTI_LINE_1  = 1,  // EXTI Line 1
    EXTI_LINE_2  = 2,  // EXTI Line 2
    EXTI_LINE_3  = 3,  // EXTI Line 3
    EXTI_LINE_4  = 4,  // EXTI Line 4
    EXTI_LINE_5  = 5,  // EXTI Line 5
    EXTI_LINE_6  = 6,  // EXTI Line 6
    EXTI_LINE_7  = 7,  // EXTI Line 7
    EXTI_LINE_8  = 8,  // EXTI Line 8
    EXTI_LINE_9  = 9,  // EXTI Line 9
    EXTI_LINE_10 = 10, // EXTI Line 10
    EXTI_LINE_11 = 11, // EXTI Line 11
    EXTI_LINE_12 = 12, // EXTI Line 12
    EXTI_LINE_13 = 13, // EXTI Line 13
    EXTI_LINE_14 = 14, // EXTI Line 14
    EXTI_LINE_15 = 15  // EXTI Line 15
} EXTI_Line_t;


/*************************** Functions Prototypes ***************************************/

void EXTI_void_Initializtion	(EXTI_Line_t Line, EXTI_Mode_t Mode);
void EXTI_void_Enable_Interrupt (EXTI_Line_t Line);
void EXTI_void_Disable_Interrupt(EXTI_Line_t Line);

void EXTI_void_Software_Trigger_Interrupt (EXTI_Line_t Line);
void EXTI_void_Set_Interrupt_Pending_Flag(EXTI_Line_t Line, u8 MaskState);
void EXTI_void_Set_CallBack(EXTI_Line_t Line, void (*CallbackFunction)(void));
void EXTI_Generic_IRQHandler(EXTI_Line_t Line);

#endif /* EXTI_EXTI_INTERFACE_H_ */
