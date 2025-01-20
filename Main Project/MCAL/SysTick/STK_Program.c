/******************************************************************************************/
/* Author      : Ahmed Assaf                                                              */
/* Date        : 29 July 2020                                                             */
/* Version     : V01                                                                      */
/* Description : Function implementation For SYSTICK Timer                                */
/******************************************************************************************/



#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"

#include "STK_Interface.h"
#include "STK_Private.h"
#include "STK_Config.h"




//void SysTick_Handler(void)                                          //Interrupt request for systick
//{
//
//	if( Flag_BusyWait_I == 1)
//	{
//		Flag_Busywait++;                                              // Increment millisecond counter
//	}
//	else if (Flag_SetIntervalSingle_I == 1)
//	{
//		Callback();
//		ActionIntervalSingle();
//	}
//	else if (Flag_SetIntervalPeriodic_I == 1)
//	{
//		Callback();
//	}
//	GET_BIT(MSTK -> CTRL,COUNT_FLAG);
//}
//
//
//void MSTK_voidInit(void)
//{
//	/*
//	   Apply Clock choice configuration file
//       Disable Systick interrupt
//       Disable Systick
//	 */
//
//	/* the clock source special with AHB BUS */
//#if     SYSTICK_CLKSOURCE == AHB_BUS_DIRECT
//	MSTK -> CTRL = 0x00000004;
//	MSTK -> LOAD     = 0;
//	MSTK -> VAL      = 0;
//	/*  the clock source special with AHB BUS/8 */
//	/*  RCC => 7*8= 56 MHZ                      */
//	/*  Not work on 64 or 72 MHZ*/
//	/*  SysTick_CLKSOURCE => 7 MHZ              */
//#elif   SYSTICK_CLKSOURCE == AHB_BUS_OVER_8
//	MSTK -> CTRL = 0x00000000;
//	MSTK -> LOAD     = 0;
//	MSTK -> VAL      = 0;
//#endif
//}
//
//
//void MSTK_voidSetBusyWaitMicroSec(u32 Copy_u32Ticks)
//{
//	/* NOTE :  This Function for Microseconds with 1 MHZ*/
//
//	/*
//	   Enable  Systick interrupt
//       Ensable Systick
//	 */
//	u64 Local_u64MicroSec = Copy_u32Ticks*7;
//	SET_BIT(MSTK -> CTRL,0);
//	SET_BIT(MSTK -> CTRL,1);
//
//	if ( Local_u64MicroSec <= 16000000)
//	{
//		Flag_BusyWait_I = 1;
//
//		/* Load ticks to load register */
//		MSTK -> LOAD = Local_u64MicroSec;
//
//		while (	Flag_Busywait  == 0);
//		if(Flag_Busywait > 0)
//		{
//			/* Apply Clock choice configuration file
//              Disable Systick interrupt
//              Disable Systick
//			 */
//			MSTK_voidInit();
//			Flag_Busywait    = 0;
//			Flag_BusyWait_I  = 0;
//		}
//	}
//	else if (Local_u64MicroSec > 16000000)
//	{
//		while ( Local_u64MicroSec > 16000000)
//		{
//			Flag_BusyWait_I   = 1;
//			if (SYSTICK_LOAD_one == 0)
//			{
//				MSTK -> LOAD     = 10000000;
//				SYSTICK_LOAD_one = 1;
//			}
//			while (Flag_Busywait == 0)
//			{
//			}
//			if(Flag_Busywait > 0)
//			{
//				Flag_Busywait = 0;
//			}
//			Local_u64MicroSec -= 10000000;
//		}
//		MSTK -> LOAD = Local_u64MicroSec;
//		while (Flag_Busywait  == 0);
//		if(Flag_Busywait > 0)
//		{
//			/*
//			    Apply Clock choice configuration file
//                Disable Systick interrupt
//                Disable Systick
//			 */
//			MSTK_voidInit();
//			Flag_Busywait   = 0;
//			Flag_BusyWait_I = 0;
//			SYSTICK_LOAD_one= 0;
//		}
//	}
//}
//
//
//void MSTK_voidSetBusyWaitMillSec(u32 Copy_u32Ticks)
//{
//	/* NOTE :  This Function for Microseconds with 1 MHZ*/
//
//		/*
//		   Enable  Systick interrupt
//	       Ensable Systick
//		 */
//		u64 Local_u64MicroSec = Copy_u32Ticks*7000;
//		SET_BIT(MSTK -> CTRL,0);
//		SET_BIT(MSTK -> CTRL,1);
//
//		if ( Local_u64MicroSec <= 16000000)
//		{
//			Flag_BusyWait_I = 1;
//
//			/* Load ticks to load register */
//			MSTK -> LOAD = Local_u64MicroSec;
//
//			while (	Flag_Busywait  == 0);
//			if(Flag_Busywait > 0)
//			{
//				/* Apply Clock choice configuration file
//	              Disable Systick interrupt
//	              Disable Systick
//				 */
//				MSTK_voidInit();
//				Flag_Busywait    = 0;
//				Flag_BusyWait_I  = 0;
//			}
//		}
//		else if (Local_u64MicroSec > 16000000)
//		{
//			while ( Local_u64MicroSec > 16000000)
//			{
//				Flag_BusyWait_I   = 1;
//				if (SYSTICK_LOAD_one == 0)
//				{
//					MSTK -> LOAD     = 10000000;
//					SYSTICK_LOAD_one = 1;
//				}
//				while (Flag_Busywait == 0)
//				{
//				}
//				if(Flag_Busywait > 0)
//				{
//					Flag_Busywait = 0;
//				}
//				Local_u64MicroSec -= 10000000;
//			}
//			MSTK -> LOAD = Local_u64MicroSec;
//			while (Flag_Busywait  == 0);
//			if(Flag_Busywait > 0)
//			{
//				/*
//				    Apply Clock choice configuration file
//	                Disable Systick interrupt
//	                Disable Systick
//				 */
//				MSTK_voidInit();
//				Flag_Busywait   = 0;
//				Flag_BusyWait_I = 0;
//				SYSTICK_LOAD_one= 0;
//			}
//		}
//}
//
//
//void MSTK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
//{
//	/* NOTE :  This Function for Microseconds with 1 MHZ*/
//	Flag_SetIntervalSingle_I = 1;
//
//	/*
//	    Apply Clock choice configuration file
//        Disable Systick interrupt
//        Disable Systick
//	*/
//	MSTK_voidInit();
//
//
//	/* Load ticks to load register */
//	MSTK -> LOAD = Copy_u32Ticks;
//
//	/*  Ensable Systick */
//	SET_BIT(MSTK -> CTRL,0);
//
//	Callback = Copy_ptr;
//
//	/* Enable  Systick interrupt */
//	SET_BIT(MSTK -> CTRL,1);
//}
//
//
//void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
//{
//
//	/* NOTE :  This Function for Microseconds with 1 MHZ*/
//	Flag_SetIntervalPeriodic_I = 1;
//
//	/*
//	    Apply Clock choice configuration file
//        Disable Systick interrupt
//        Disable Systick
//	*/
//	MSTK_voidInit();
//
//	/* Load ticks to load register */
//	MSTK -> LOAD = Copy_u32Ticks;
//
//	/*  Ensable Systick */
//	SET_BIT(MSTK -> CTRL,0);
//
//	Callback = Copy_ptr;
//
//	/* Enable  Systick interrupt */
//	SET_BIT(MSTK -> CTRL,1);
//}
//
//
//void MSTK_voidStopInterval(void)
//{
//	MSTK_voidInit();
//	Flag_SetIntervalPeriodic_I = 0;
//}
//
//
//u32 MSTK_u32GetElapsedTime(void)
//{
//	u32 Local_u32ElapsedTime = 0;
//	Local_u32ElapsedTime = MSTK -> LOAD - MSTK -> VAL ;
//	return Local_u32ElapsedTime;
//}
//
//
//u32 MSTK_u32GetRemainingTime(void)
//{
//	u32 Local_u32RemainingTime = 0;
//	Local_u32RemainingTime =  MSTK -> VAL;
//	return Local_u32RemainingTime;
//}
