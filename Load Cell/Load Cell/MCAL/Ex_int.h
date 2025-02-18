/*
* Ex_int.h
*
* Created: 11/19/2023 10:28:39 PM
*  Author: Mohammed Khalaf
*/


#ifndef EX_INT_H_
#define EX_INT_H_

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_t;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2,
	EX_INT3,
	EX_INT4,
	EX_INT5,
	EX_INT6,
	EX_INT7
}ExInterruptSource_t;


#define		ENABLE_GLOBAL_INTERRUPT		sei
#define		CLEAR_GLOBAL_INTERRUPT		cli
/************************************************************************/
/*                    Prototypes                                        */
/************************************************************************/
void EXI_init();
void EXI_Enable(ExInterruptSource_t Interrupt);
void EXI_Disable(ExInterruptSource_t Interrupt);
void EXI_TriggerEdge(ExInterruptSource_t Interrupt,TriggerEdge_t Edge);
void EXI_SetCallBack(ExInterruptSource_t Interrupt, void(*LocalPtr)(void));


#endif /* EX_INT_H_ */