/*
* EX_int.c
*
* Created: 11/19/2023 10:28:08 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "Ex_int.h"

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=(u8)Null_Ptr;
static void (*INT1_Fptr) (void)=(u8)Null_Ptr;
static void (*INT2_Fptr) (void)=(u8)Null_Ptr;
static void (*INT3_Fptr) (void)=(u8)Null_Ptr;
static void (*INT4_Fptr) (void)=(u8)Null_Ptr;
static void (*INT5_Fptr) (void)=(u8)Null_Ptr;
static void (*INT6_Fptr) (void)=(u8)Null_Ptr;
static void (*INT7_Fptr) (void)=(u8)Null_Ptr;

/************************************Enable/Disable functions***********************************/

void EXI_init(void)
{
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT3,FALLING_EDGE);
	EXI_TriggerEdge(EX_INT4,RISING_EDGE);
	EXI_TriggerEdge(EX_INT5,RISING_EDGE);
	EXI_TriggerEdge(EX_INT6,RISING_EDGE);
	EXI_TriggerEdge(EX_INT7,RISING_EDGE);
	
}


void EXI_Enable(ExInterruptSource_t Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		SET_BIT(EIMSK,INT0);
		break;
		case EX_INT1:
		SET_BIT(EIMSK,INT1);
		break;
		case EX_INT2:
		SET_BIT(EIMSK,INT2);
		break;
		case EX_INT3:
		SET_BIT(EIMSK,INT3);
		break;
		case EX_INT4:
		SET_BIT(EIMSK,INT4);
		break;
		case EX_INT5:
		SET_BIT(EIMSK,INT5);
		break;
		case EX_INT6:
		SET_BIT(EIMSK,INT6);
		break;
		case EX_INT7:
		SET_BIT(EIMSK,INT7);
		break;
		
	}
}

void EXI_Disable(ExInterruptSource_t Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		CLEAR_BIT(EIMSK,INT0);
		break;
		case EX_INT1:
		CLEAR_BIT(EIMSK,INT1);
		break;
		case EX_INT2:
		CLEAR_BIT(EIMSK,INT2);
		break;
		case EX_INT3:
		CLEAR_BIT(EIMSK,INT3);
		break;
		case EX_INT4:
		CLEAR_BIT(EIMSK,INT4);
		break;
		case EX_INT5:
		CLEAR_BIT(EIMSK,INT5);
		break;
		case EX_INT6:
		CLEAR_BIT(EIMSK,INT6);
		break;
		case EX_INT7:
		CLEAR_BIT(EIMSK,INT7);
		break;
		
	}
}

/************************************Control function*****************************/

void EXI_TriggerEdge(ExInterruptSource_t Interrupt, TriggerEdge_t Edge) {
	switch (Interrupt) {
		case EX_INT0:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRA, ISC00);
			CLEAR_BIT(EICRA, ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRA, ISC00);
			CLEAR_BIT(EICRA, ISC01);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRA, ISC00);
			SET_BIT(EICRA, ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(EICRA, ISC00);
			SET_BIT(EICRA, ISC01);
			break;
		}
		break;
		case EX_INT1:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRA, ISC10);
			CLEAR_BIT(EICRA, ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRA, ISC10);
			CLEAR_BIT(EICRA, ISC11);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRA, ISC10);
			SET_BIT(EICRA, ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(EICRA, ISC10);
			SET_BIT(EICRA, ISC11);
			break;
		}
		break;
		case EX_INT2:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC20);
			CLEAR_BIT(EICRB, ISC21);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC20);
			CLEAR_BIT(EICRB, ISC21);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC20);
			SET_BIT(EICRB, ISC21);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC20);
			SET_BIT(EICRB, ISC21);
			break;
		}
		break;
		case EX_INT3:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC30);
			CLEAR_BIT(EICRB, ISC31);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC30);
			CLEAR_BIT(EICRB, ISC31);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC30);
			SET_BIT(EICRB, ISC31);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC30);
			SET_BIT(EICRB, ISC31);
			break;
		}
		break;
		case EX_INT4:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC40);
			CLEAR_BIT(EICRB, ISC41);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC40);
			CLEAR_BIT(EICRB, ISC41);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC40);
			SET_BIT(EICRB, ISC41);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC40);
			SET_BIT(EICRB, ISC41);
			break;
		}
		break;
		case EX_INT5:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC50);
			CLEAR_BIT(EICRB, ISC51);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC50);
			CLEAR_BIT(EICRB, ISC51);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC50);
			SET_BIT(EICRB, ISC51);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC50);
			SET_BIT(EICRB, ISC51);
			break;
		}
		break;
		case EX_INT6:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC60);
			CLEAR_BIT(EICRB, ISC61);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC60);
			CLEAR_BIT(EICRB, ISC61);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC60);
			SET_BIT(EICRB, ISC61);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC60);
			SET_BIT(EICRB, ISC61);
			break;
		}
		break;
		case EX_INT7:
		switch (Edge) {
			case LOW_LEVEL:
			CLEAR_BIT(EICRB, ISC70);
			CLEAR_BIT(EICRB, ISC71);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(EICRB, ISC70);
			CLEAR_BIT(EICRB, ISC71);
			break;
			case FALLING_EDGE:
			CLEAR_BIT(EICRB, ISC70);
			SET_BIT(EICRB, ISC71);
			break;
			case RISING_EDGE:
			SET_BIT(EICRB, ISC70);
			SET_BIT(EICRB, ISC71);
			break;
		}
		break;
	}
}


/************************************Call back functions*********************************************/

void EXI_SetCallBack(ExInterruptSource_t Interrupt, void(*LocalPtr)(void))
{
	switch(Interrupt){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;
		case EX_INT3:
		INT3_Fptr=LocalPtr;
		break;
		case EX_INT4:
		INT4_Fptr=LocalPtr;
		break;
		case EX_INT5:
		INT5_Fptr=LocalPtr;
		break;
		case EX_INT6:
		INT6_Fptr=LocalPtr;
		break;
		case EX_INT7:
		INT7_Fptr=LocalPtr;
		break;
	}
}

void EXTI_GlobalIntDisable(void)
{
	cli();
}

void EXTI_GlobalIntEnable(void)
{
	sei();
}

/*******************************ISR********************************/

//ISR(INT0_vect)
//{
/*code validate data*/
/* data right address*/
//u8 data=5;
//EXI0_Func(data);  // Call out function
//

//if (INT0_Fptr!=Null_Ptr)   // Without checking if the pointer to function is equal zero the compiler will reset the code
//{
//		INT0_Fptr();
//	}


//}
/*ISR(INT1_vect,ISR_NOBLOCK)
{

if (INT1_Fptr!=Null_Ptr)
{
INT1_Fptr();
}
}
ISR(INT2_vect)
{
if (INT2_Fptr!=Null_Ptr)
{
INT2_Fptr();
}

}*/

