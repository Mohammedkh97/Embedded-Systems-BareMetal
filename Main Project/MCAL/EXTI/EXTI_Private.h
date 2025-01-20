/*
 * EXTI_Private.h
 *
 *  Created on: Oct 5, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef EXTI_EXTI_PRIVATE_H_
#define EXTI_EXTI_PRIVATE_H_

/****************************   EXTI Registers Definition     ******************************/

typedef struct
{
    volatile u32  IMR;    // Interrupt mask register (EXTI_IMR)
    volatile u32  EMR;    // Event mask register (EXTI_EMR)
    volatile u32  RTSR;   // Rising trigger selection register (EXTI_RTSR)
    volatile u32  FTSR;   // Falling trigger selection register (EXTI_FTSR)
    volatile u32  SWIER;  // Software interrupt event register (EXTI_SWIER)
    volatile u32  PR;     // Pending register (EXTI_PR)

}EXTI_t;


#define NUMBER_OF_EXTI              (16)

typedef void (*EXTI_CallBack_Function_Format_t) (void);

#endif /* EXTI_EXTI_PRIVATE_H_ */
