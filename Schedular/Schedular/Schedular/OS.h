
#ifndef OS_H_
#define OS_H_

#include "stdTypes.h"

#define MAX_NUM_OF_TASKS 	3
#define HYPER_PERIOD 		6



typedef void (*fncPtr)(void);           /**< Function pointer for registering tasks. */


typedef enum
{
	BLOCKED,
	READY,
	SUSPENDED
} OS_state;


/*Task Control Block*/
typedef struct
{
	void (*PointerToFunction)(void);
	u8 task_Periodicity;
	OS_state task_State;
	u8 Task_Counter;
} OS_struct;


typedef enum
{
	OKAY,
	NULL_POINTER,
	OUT_OF_RANGE,
	TIME_LIMIT_EXCEED,
	UNKNOWN
} OS_feedback;


OS_feedback OS_TaskCreate(void (*funcPtr)(void), u8 periodicity, OS_state default_state);

void OS_Task_Handler(void);

void OS_TaskExecution(void);


#endif /* OS_H_ */
