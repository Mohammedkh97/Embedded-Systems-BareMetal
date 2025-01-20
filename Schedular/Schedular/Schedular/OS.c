

#include "OS.h"


/* Create an array of struct to hold the data of each created task*/
/*Create Your Own TCBs*/
static OS_struct TCB_Array[MAX_NUM_OF_TASKS];

static u8 taskCounter = 1;


OS_feedback OS_TaskCreate(void (*pointerToFun)(void), u8 periodicity, OS_state default_state)
{
	OS_feedback feedBack = UNKNOWN;
	/*Check if pointer is to Function not Null Pointer*/
	if (pointerToFun == Null_Ptr)
	{
		feedBack = NULL_POINTER;
	}
	/*Check if the Task counter exceeded Max number of Tasks or not*/
	if (taskCounter > MAX_NUM_OF_TASKS)
	{
		feedBack = EXCEED_MAX_COUNT;
	}
	
	/*Check if Periodicity Exceeds Hyper period or not*/
	if (periodicity > HYPER_PERIOD)
	{
		feedBack = TIME_LIMIT_EXCEED;
	}
	
	for (taskCounter = 0 ; taskCounter < MAX_NUM_OF_TASKS ; taskCounter++)
	{
		TCB_Array[taskCounter].PointerToFunction = pointerToFun;
		TCB_Array[taskCounter].task_Periodicity  = periodicity;
		TCB_Array[taskCounter].task_State		 = default_state;
		TCB_Array[taskCounter].Task_Counter		 = 1;
		
		taskCounter++;
		feedBack = OKAY;
	}
	return feedBack;
	
}

void OS_TaskExecution(void)
{
	/*Check the Ready Task to be Executed*/
	u8 task_id = 0;
	for (task_id = 0 ; task_id < taskCounter ; task_id++)
	{
		if (TCB_Array[task_id].task_State == READY)
		{
			TCB_Array[task_id].PointerToFunction();
			TCB_Array[task_id].task_State = BLOCKED;
		}
		
	}

}


void OS_Task_Handler(void)
{
	u8 task_id = 0;
	for (task_id = 0 ; task_id < taskCounter ; task_id++)
	{
		if (TCB_Array[task_id].Task_Counter >= TCB_Array[task_id].task_Periodicity)
		{
			TCB_Array[task_id].task_State	= READY;
			TCB_Array[task_id].Task_Counter = 1;
		}
		else
		{
			TCB_Array[task_id].Task_Counter++;
		}
	}
	
}
