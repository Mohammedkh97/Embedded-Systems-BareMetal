/*
 * EXTI_Program.c
 *
 *  Created on: Oct 5, 2024
 *  Author: Mohammed Khalaf
 */

#include "EXTI_MemoryMap.h"
#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "EXTI_Private.h"
#include "EXTI_Interface.h"



/****************************Pointer to functions to be assigned to ISR*********************************/
/************************ Callback Global variable (pointer to function) **********************/

//static void (*EXTI_CallBack[NUMBER_OF_EXTI]) (void);
static EXTI_CallBack_Function_Format_t EXTI_CallBack_Function[NUMBER_OF_EXTI];
//typedef void (*EXTI_CallBack_Function_Format_t) (void);
//static void (*INT0_Fptr) (void)=(u8)Null_Ptr;

void EXTI_void_Initializtion(EXTI_Line_t line, EXTI_Mode_t mode)
{
	EXTI_void_Enable_Interrupt(line);

    switch (mode) {
        case EXTI_MODE_RISING:
            SET_BIT(EXTI->RTSR, line);    // Enable Rising Trigger
            CLEAR_BIT(EXTI->FTSR, line); // Disable Falling Trigger
            break;

        case EXTI_MODE_FALLING:
            SET_BIT(EXTI->FTSR, line);    // Enable Falling Trigger
            CLEAR_BIT(EXTI->RTSR, line); // Disable Rising Trigger
            break;

        case EXTI_MODE_RISING_FALLING:
            SET_BIT(EXTI->RTSR, line);   // Enable Rising Trigger
            SET_BIT(EXTI->FTSR, line);   // Enable Falling Trigger
            break;

        case EXTI_MODE_SOFTWARE:
            SET_BIT(EXTI->SWIER, line);  // Enable Software Interrupt
            break;

        default:
            // Handle invalid mode
            break;
    }
}

void EXTI_void_Enable_Interrupt(EXTI_Line_t Line)
{
	SET_BIT(EXTI->IMR, Line);
}

void EXTI_void_Disable_Interrupt(EXTI_Line_t Line)
{
	CLEAR_BIT(EXTI->IMR, Line);
}

void EXTI_void_Enable_Event_Mask(EXTI_Line_t Line)
{
	SET_BIT(EXTI->EMR, Line);

}

void EXTI_void_Disable_Event_Mask(EXTI_Line_t Line)
{
	CLEAR_BIT(EXTI->EMR, Line);
}

void EXTI_void_Software_Trigger_Interrupt (EXTI_Line_t Line)
{
	SET_BIT(EXTI->SWIER, Line);
}

void EXTI_void_Set_Interrupt_Pending_Flag(EXTI_Line_t Line, u8 MaskState)
{
	BIT_WRITE(EXTI->PR, Line, MaskState);   // This bit is set when the selected edge event arrives on the external interrupt line. This bit is cleared by writing a ‘1’ into the bit.

//	SET_BIT(EXTI->PR, Line);
}

void EXTI_void_Set_Clear_Interrupt_Pending_Flag(EXTI_Line_t Line, u8 MaskState)
{
	if (Line < NUMBER_OF_EXTI)
    {
    	// Write '1' to clear the pending flag for the specified EXTI line
    	if (MaskState == 1)
        {
            SET_BIT(EXTI->PR, Line);  // Set the bit
        }
    	// Write '0' to Set the pending flag for the specified EXTI line
        else if (MaskState == 0)
        {
            CLEAR_BIT(EXTI->PR, Line); // Clear the bit
        }
    }
}

/*************	 Function OF Set CallBack  **********************/

void EXTI_void_Set_CallBack(EXTI_Line_t Line, void (*CallbackFunction)(void))
{
    if (Line < NUMBER_OF_EXTI)
    {
        EXTI_CallBack_Function[Line] = CallbackFunction;
    }
}

void EXTI_Generic_IRQHandler(EXTI_Line_t Line)
{
    // Check if a callback function is registered for the specified line
    if ((EXTI_CallBack_Function[Line] != NullPtr))
    {
        EXTI_CallBack_Function[Line](); // Call the registered callback function
    }

    // Clear the Pending Bit for the specified EXTI line
    SET_BIT(EXTI->PR, Line);
    /*
       Why Clear the Pending Bit?
       Interrupt Acknowledgment:

       The EXTI pending bit indicates that the interrupt request has been triggered for a specific EXTI line. Clearing it acknowledges the interrupt, signaling that it has been handled.
       Avoid Continuous Interrupts:

       If the pending bit remains set, the interrupt handler may continuously be invoked because the interrupt condition is still flagged.
       Software Acknowledgment:

       Unlike NVIC interrupts, which are cleared automatically when the interrupt handler is entered, the EXTI pending bit must be cleared manually in software.
   */

}

//void EXTI0_IRQHandler(void)
//{
//    if((EXTI_CallBack_Function[EXTI_LINE_0] != NullPtr))
//    {
//        EXTI_CallBack_Function[EXTI_LINE_0]();
//    }
// /* Clear the Pending Bit */
//SET_BIT(EXTI->PR, EXTI_LINE_0);
// /*
//    Why Clear the Pending Bit?
//    Interrupt Acknowledgment:
//
//    The EXTI pending bit indicates that the interrupt request has been triggered for a specific EXTI line. Clearing it acknowledges the interrupt, signaling that it has been handled.
//    Avoid Continuous Interrupts:
//
//    If the pending bit remains set, the interrupt handler may continuously be invoked because the interrupt condition is still flagged.
//    Software Acknowledgment:
//
//    Unlike NVIC interrupts, which are cleared automatically when the interrupt handler is entered, the EXTI pending bit must be cleared manually in software.
//*/
//}
//
//void EXTI1_IRQHandler(void)
//{
//    if((EXTI_CallBackFunction[EXTI_LINE_1] != NULL))
//    {
//        EXTI_CallBackFunction[EXTI_LINE_1]();
//    }
//    /* Clear the Pending Bit */
//    SET_BIT(EXTI->PR, EXTI_LINE_1);
//}
//
//void EXTI2_IRQHandler(void)
//{
//    if((EXTI_CallBackFunction[EXTI_LINE_2] != NULL))
//    {
//        EXTI_CallBackFunction[EXTI_LINE_2]();
//    }
//    /* Clear the Pending Bit */
//    SET_BIT(EXTI->PR, EXTI_LINE_2);
//}
//
//void EXTI3_IRQHandler (void)
//{
//    if((EXTI_CallBackFunction[EXTI_LINE_3] != NULL))
//    {
//        EXTI_CallBackFunction[EXTI_LINE_3]();
//    }
//	/* Clear the Pending Bit */
//	SET_BIT(EXTI->PR , EXTI_LINE_3);
//
//}
//
//void EXTI4_IRQHandler (void)
//{
//    if((EXTI_CallBackFunction[EXTI_LINE_4] != NULL))
//    {
//        EXTI_CallBackFunction[EXTI_LINE_4]();
//    }
//	/* Clear the Pending Bit */
//	SET_BIT(EXTI->PR , EXTI_LINE_4);
//
//}


//void EXTI9_5_IRQHandler (void)
//{
//	uint8 Local_ExtiDetect=0;
//	for(uint8 local_i=EXTI_LINE5; local_i<=EXTI_LINE9; local_i++)
//	{
//		Local_ExtiDetect = GET_BIT(EXTI->PR,local_i);
//		if(Local_ExtiDetect == 1)
//		{
//			EXTI_CallBack[local_i]();
//		}
//		Local_ExtiDetect=0;
//	}
//	EXTI->PR |= 0x03E0; /* clear interrupt pending flag 5~9 */
//
//}
