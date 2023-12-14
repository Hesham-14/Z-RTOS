/*
 * Scheduler.h
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

/*****************************************
-------------   Includes   -------------
 *****************************************/
#include "CortexMX_OS_porting.h"


/*****************************************
---------  User Type Definition ---------
 *****************************************/
typedef enum
{
	RTOS_OK       			= 0x00U,
	RTOS_ERROR    			= 0x01U,
	RTOS_BUSY     			= 0x02U,
	RTOS_TIMEOUT  			= 0x03U,
	READY_QUEUE_INIT_ERROR 	= 0x04U
} RTOS_ERROR_t;

typedef struct
{
	unsigned int StackSize;
	char TaskName[30];
	enum{ON, OFF} AutoStart;
	unsigned int Priority;
	void (*pTaskEntry)(void);	//pointer to Task function
	unsigned int _S_PSP_Task;	//Not Entered by User
	unsigned int _E_PSP_Task;	//Not Entered by User
	unsigned int* Current_PSP;	//Not Entered by User
	enum{Suspend, Waiting, Ready, Running} TaskState;	//Not Entered by User
	struct{
		unsigned int TicksCount;
		enum{BlockEnable, BlockDisable} Blocking;
	} TimingWaiting;
}Task_t;


/*****************************************************
---------   Macros Configuration Refrences  --------
 ******************************************************/
#define READY_FIFO_SIZE		100


/*****************************************
----------------- APIs  -----------------
 *****************************************/
RTOS_ERROR_t RTOS_init();
RTOS_ERROR_t RTOS_Create_Task(Task_t* Tref);
RTOS_ERROR_t RTOS_Activate_Task(Task_t* Tref);
RTOS_ERROR_t RTOS_Terminate_Task(Task_t* Tref);
RTOS_ERROR_t RTOS_Wait_Task(unsigned int NoTicks, Task_t* Tref);
RTOS_ERROR_t RTOS_Update_Task_Waiting_Time(void);
RTOS_ERROR_t RTOS_StartOS();



#endif /* INC_SCHEDULER_H_ */
