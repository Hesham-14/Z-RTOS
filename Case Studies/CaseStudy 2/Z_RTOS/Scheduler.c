/*
 * Scheduler.c
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */


/**************************************************************
------------------------- Includes  ---------------------------
 ***************************************************************/
#include "Scheduler.h"
#include "Z_RTOS_FIFO.h"


/**************************************************************
---------------------- Global Variables  ----------------------
 ***************************************************************/
struct {
	Task_t* OSTasks[100];
	unsigned int _S_MSP_Task;
	unsigned int _E_MSP_Task;
	unsigned int PSP_Task_Locator;
	unsigned int NoofActiveTasks;
	Task_t* CurrentTask;
	Task_t* NextTask;
	enum{OSsuspend, OSrunning} OSModeID;
}S_OS_CONTROL;

typedef enum{
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_TaskWaitingTime
}SVC_ID;

FIFO_Buf_t Glob_Ready_Queue;
Task_t* Glob_Ready_Queue_FIFO[READY_FIFO_SIZE];
Task_t Glob_Idle_Task;

unsigned char IdleTaskLED;


/**************************************************************
-------------------- Functions Decleration --------------------
 ***************************************************************/
void RTOS_Create_MainStack(void);


/**************************************************************
---------------------- Handler Functions  ----------------------
 ***************************************************************/

__attribute ((naked)) void PendSV_Handler()
{
	/* Save The Context of Current Task */
	// 1. Get the current task (current PSP from CPU Registers)
	OS_GET_PSP(S_OS_CONTROL.CurrentTask->Current_PSP);

	// 2. Use Current PSP to Store (r4:r11)
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r4 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r5 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r6 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r7 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r8 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r9 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r10 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP--;
	__asm volatile("mov %0, r11 " : "=r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));


	/* Restore the context of the next task */
	//1. Set next Task as Current task
	S_OS_CONTROL.CurrentTask = S_OS_CONTROL.NextTask;
	S_OS_CONTROL.NextTask = NULL;

	//2. Restore Context for the task
	__asm volatile("mov r11,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r10,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r9,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r8,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r7,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r6,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r5,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;
	__asm volatile("mov r4,%0 " : : "r" (*(S_OS_CONTROL.CurrentTask->Current_PSP)));
	S_OS_CONTROL.CurrentTask->Current_PSP++;

	//3. Update PSP and Exit
	OS_SET_PSP(S_OS_CONTROL.CurrentTask->Current_PSP);
	__asm volatile ("BX LR");

}

void OS_SVC_Set(int a, int b, int SVC_ID)
{
	switch(SVC_ID)
	{
	case 0:	//Activate Task
		__asm("svc #0x00");
		break;

	case 1:	//Terminate Task
		__asm("svc #0x01");
		break;

	case 2:	//OS MULL
		__asm("svc #0x02");
		break;

	case 3:	//OS PENDSV
		__asm("svc #0x03");
		break;

	}
}

void RTOS_Create_MainStack(void)
{
	S_OS_CONTROL._S_MSP_Task = &_estack;
	S_OS_CONTROL._E_MSP_Task = S_OS_CONTROL._S_MSP_Task - MainStackSize;

	//Allign 8 Bytes spaces between Main Stack and PSP tasks
	S_OS_CONTROL.PSP_Task_Locator = (S_OS_CONTROL._E_MSP_Task - 8);

	/* Optional */
	// if(S_OS_CONTROL._E_MSP_Task  < &_eheap) Error: exceeded the available stack size
}


void RTOS_Create_TaskStack(Task_t* Tref)
{
	/*
	 * Task Frame:
	 * ========
	 * XPSR
	 * PC (Next Task Instruction wich should be run)
	 * LR (Return register which is saved in CPU, while Task 1 running, before task switching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 * =======
	 * (Saved / Restore) Manual:
	 * r5
	 * r6
	 * r7
	 * r8
	 * r9
	 * r10
	 * r11
	 */
	Tref->Current_PSP = Tref->_S_PSP_Task;

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0x1000000; //DUMMY XPSR: T = 1 to avoid Bus Fault

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = (unsigned int) Tref->pTaskEntry; //PC

	Tref->Current_PSP--;
	*(Tref->Current_PSP) = 0xFFFFFFFD; //LR

	// ri
	for(int i=0; i<13; i++)
	{
		Tref->Current_PSP--;
		*(Tref->Current_PSP) = 0; //LR
	}
}

void RTOS_IdleTask(void)
{
	while(1)
	{
		IdleTaskLED ^= 1;
		__asm("wfe");
	}
}

/* Handler Mode */
void Bubble_Sort()
{
	unsigned int i,j,n;
	Task_t* temp;
	n = S_OS_CONTROL.NoofActiveTasks;
	for(i = 0; i < n-1; i++)
		//Last i elements are already in place
		for(j=0; j<n-i-1; j++)
			if(S_OS_CONTROL.OSTasks[j]->Priority > S_OS_CONTROL.OSTasks[j+1]->Priority)
			{
				temp = S_OS_CONTROL.OSTasks[j];
				S_OS_CONTROL.OSTasks[j] = S_OS_CONTROL.OSTasks[j+1];
				S_OS_CONTROL.OSTasks[j+1] = temp;
			}
}

/* Handler Mode */
void RTOS_Update_Schedular_Table()
{
	int i=0;
	Task_t* temp = NULL;
	Task_t* PTask;
	Task_t* PNextTask;

	//1. Bubble Sort OSTask[100] (Sch. Table) based on Priority
	Bubble_Sort();

	//2. Free REQDY QUEUE
	while(FIFO_Dequeue(&Glob_Ready_Queue, &temp) != FIFO_EMPTY);

	//3. Update READY QUEUE
	while(i < S_OS_CONTROL.NoofActiveTasks)
	{
		PTask = S_OS_CONTROL.OSTasks[i];
		PNextTask = S_OS_CONTROL.OSTasks[i+1];

		if(PTask->TaskState != Suspend)
		{
			// in case we reached to the end of available OSTasks or
			if(PNextTask->TaskState == Suspend)
			{
				FIFO_Enqueue(&Glob_Ready_Queue, PTask);
				PTask->TaskState = Ready;
				// get out the loop
				break;
			}
			// if the PTask priority higher than PNextTask
			if(PTask->Priority < PNextTask->Priority)
			{
				FIFO_Enqueue(&Glob_Ready_Queue, PTask);
				PTask->TaskState = Ready;
				// get out the loop
				break;
			}
			// both has the same priority
			else if(PTask->Priority == PNextTask->Priority)
			{
				//	if the Ptask priority == nexttask then
				//		push Ptask to ready state
				//	And make the ptask = nexttask  and nexttask++
				FIFO_Enqueue(&Glob_Ready_Queue, PTask);
				PTask->TaskState = Ready;
			}
			else if (PTask->Priority > PNextTask->Priority)
			{
				//not allowed to happen as we already reordered it by bubble sort
				break ;
			}
		}
		i++;
	}
}

/* Handler Mode */
void Decide_What_Next()
{
	// 1. Check if QUEUE is EMBTY && CurrentTask State is suspended
	if(Glob_Ready_Queue.counter == 0 && S_OS_CONTROL.CurrentTask->TaskState != Suspend)
	{
		// So continue running the same Task
		S_OS_CONTROL.CurrentTask->TaskState = Running;

		// Add the current task again to the QUEUE [Round Robin]
		FIFO_Enqueue(&Glob_Ready_Queue, S_OS_CONTROL.CurrentTask);

		// Set Next task = Current task
		S_OS_CONTROL.NextTask = S_OS_CONTROL.CurrentTask;
	}
	else
	{
		// Dequeu from QUEUE and store the task as a next task in OS Control
		FIFO_Dequeue(&Glob_Ready_Queue, &S_OS_CONTROL.NextTask);

		// Set nextTask.State = running
		S_OS_CONTROL.NextTask->TaskState = Running;

		// Update READY QUEUE [Round Robin] + checking that current and next has the same priority
		if((S_OS_CONTROL.CurrentTask->Priority == S_OS_CONTROL.NextTask->Priority) && (S_OS_CONTROL.CurrentTask->TaskState != Suspend))
		{
			FIFO_Enqueue(&Glob_Ready_Queue, S_OS_CONTROL.CurrentTask);
			S_OS_CONTROL.CurrentTask->TaskState = Ready;
		}
	}
}

/* Handler Mode */
void OS_SVC_Handler(int* StackFrame)
{
	//1. Get SVC Number
	unsigned char SVC_number ;
	SVC_number = *((unsigned char*)(((unsigned char*)StackFrame[6])-2)) ;

	//2. check SVC number
	/*
	 * For Both Activate & Terminate:
	 * i) update Scheduler Table, Read Queue
	 * ii) Check if OS is Running State
	 * 		- Decide what State
	 * 		- Trigger OS_pendSV (Switch Context/Restore)
	 */
	switch(SVC_number)
	{
	case SVC_ActivateTask:
	case SVC_TerminateTask:
	{
		//Update Sch. Table, READY QUEUE
		RTOS_Update_Schedular_Table();

		//OS Running or not
		if(S_OS_CONTROL.OSModeID == OSrunning)
		{
			if(strcmp(S_OS_CONTROL.CurrentTask->TaskName, "IdleTask") != 0)
			{
				// Decide what is next
				Decide_What_Next();

				//trigger OS_PendSV (Switch Context/Restore)
				Trigger_OS_PendSV();
			}
		}
		break;
	}
	case SVC_TaskWaitingTime:
		//Update Sch. Table, READY QUEUE
		RTOS_Update_Schedular_Table();
		break;
	}
}

/* Thread Mode */
void RTOS_OS_SVC_Set(SVC_ID ID)
{
	switch(ID)
	{
	case SVC_ActivateTask:
		__asm("svc #0x00");
		break;
	case SVC_TerminateTask:
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime:
		__asm("svc #0x02");
		break;
	}
}


/**************************************************************
------------------ APIs Functions Definitions  -----------------
 ***************************************************************/

/**===========================================================
 * @Fn			- RTOS_init
 * @brief 		- This function initialize the Real-time operating system
 * @param [in]	- none
 * @retval 		- RTOS_Status_t: return a status for the execution of the function call
 * Note			- none
 */
RTOS_ERROR_t RTOS_init()
{
	RTOS_ERROR_t error = RTOS_OK;

	//1. Update OS mode (OSsuspend)
	S_OS_CONTROL.OSModeID = OSsuspend;

	//2. Specify the MAIN Stack for OS
	RTOS_Create_MainStack();

	//3. create OS Ready Queue
	if(FIFO_Init(&Glob_Ready_Queue, Glob_Ready_Queue_FIFO, READY_FIFO_SIZE) != FIFO_NO_ERROR)
	{
		error = READY_QUEUE_INIT_ERROR;
	}

	//4. Configure Idle task
	strcpy(Glob_Idle_Task.TaskName, "IdleTask");
	Glob_Idle_Task.Priority = 255;				// Give it the highest value --> to be the lowest priority
	Glob_Idle_Task.pTaskEntry = RTOS_IdleTask;
	Glob_Idle_Task.StackSize = 300;				// 300 bytes
	error = RTOS_Create_Task(&Glob_Idle_Task);

	return error;
}


/**===========================================================
 * @Fn			- RTOS_Create_Task
 * @brief 		- This function Creates the Task PSP stack
 * @param [in]	- Tref: the passed task parameters to create
 * @retval 		- RTOS_Status_t: return a status for the execution of the function call
 * Note			- none
 */
RTOS_ERROR_t RTOS_Create_Task(Task_t* Tref)
{
	RTOS_ERROR_t error = RTOS_OK;

	//1. Create its own PSP Stack
	Tref->_S_PSP_Task = S_OS_CONTROL.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->StackSize;

	//2. Check if task stack exceeds the PSP stack or not
	//if(Tref->_E_PSP_Task < (unsigned int)(&_eheap));

	//3. Allign 8 bytes space between Task PSP and other
	S_OS_CONTROL.PSP_Task_Locator = Tref->_E_PSP_Task - 8;

	//4. Initialize PSP Task Stack (Task Frame)
	RTOS_Create_TaskStack(Tref);

	//5. Update OS Tasks Array and Num. of Active tasks
	S_OS_CONTROL.OSTasks[S_OS_CONTROL.NoofActiveTasks] = Tref;
	S_OS_CONTROL.NoofActiveTasks++;

	//6. Set task state to suspended
	Tref->TaskState = Suspend;

	return error;
}

/**===========================================================
 * @Fn			- RTOS_Activate_Task
 * @brief 		- This function
 * @param [in]	- Tref: the passed task parameters to Activate
 * @retval 		- RTOS_Status_t: return a status for the execution of the function call
 * Note			- none
 */
RTOS_ERROR_t RTOS_Activate_Task(Task_t* Tref)
{
	//1. Set task state = waiting
	Tref->TaskState = Waiting;
	RTOS_OS_SVC_Set(SVC_ActivateTask);
}

/**===========================================================
 * @Fn			- RTOS_Activate_Task
 * @brief 		- This function
 * @param [in]	- Tref: the passed task parameters to Activate
 * @retval 		- RTOS_Status_t: return a status for the execution of the function call
 * Note			- none
 */
RTOS_ERROR_t RTOS_Terminate_Task(Task_t* Tref)
{
	//1. Set task state = waiting
	Tref->TaskState = Suspend;
	RTOS_OS_SVC_Set(SVC_TerminateTask);
}


/**===========================================================
 * @Fn			- RTOS_StartOS
 * @brief 		- This function
 * @param [in]	- none
 * @retval 		- RTOS_Status_t: return a status for the execution of the function call
 * Note			- none
 */
RTOS_ERROR_t RTOS_StartOS()
{
	//1. Change OS Mode to running
	S_OS_CONTROL.OSModeID = OSrunning;

	//2. Set Idle Task as Current Task
	S_OS_CONTROL.CurrentTask = &Glob_Idle_Task;

	//3. Activate Current Task (idle task)
	RTOS_Activate_Task(S_OS_CONTROL.CurrentTask);

	//4. Start Ticker
	Start_Ticker();

	//5. Set CPU PSP for Current Task (Idle Task)
	OS_SET_PSP(S_OS_CONTROL.CurrentTask->Current_PSP);

	//6. Switch Thread Mode SP (MSP --> PSP) and make it unprivileged
	OS_SWITCH_SP_to_PSP;
	OS_SWITCH_to_unprivilaged;

	//7. Call Current Task Function
	S_OS_CONTROL.CurrentTask->pTaskEntry();

}


/*************************************************************
------------------------ Other Functions  -----------------------
 **************************************************************/





