/******************************************************************************************/
/* Author      : Ahmed Assaf                                                              */
/* Date        : 29 July 2020                                                             */
/* Version     : V01                                                                      */
/* Description : GPIO INTERFACE                                                           */
/******************************************************************************************/


#ifndef _STK_INTERFACE_H
#define _STK_INTERFACE_H
 


 
void MSTK_voidInit(void);
 
 
void MSTK_voidSetBusyWaitMicroSec(u32 Copy_u32Ticks);			//Synchronous function


void MSTK_voidSetBusyWaitMillSec(u32 Copy_u32Ticks);


void MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void));      //ASynchronous function

// void main (void) 
// void func(void)
// {
//	 /* code */
// }

// void MSTK_voidSetIntervalSingle(1000,func );   
// void MSTK_voidSetIntervalSingle(2000,func3 );
// void MSTK_voidSetIntervalSingle(3000,func4 );

void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void));    //ASynchronous function


void MSTK_voidStopInterval(void);


u32 MSTK_u32GetElapsedTime(void);              // load register -value register

         
u32 MSTK_u32GetRemainingTime(void);            // value register






#endif
