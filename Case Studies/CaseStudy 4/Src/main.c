/**
 ******************************************************************************
 * @file           :  MYRTOS OS
 * @author         : Keroles Shenouda
 * @brief          : Create Your RTOS (ARM And RTOS Coure) in Master Embedded System Online Diploma
 * www.learn-in-depth.com
 * eng.keroles.karam@gmail.com
 * Mater Embedded System Online Diploma
 ******************************************************************************
 */

#include <stdint.h>

#include "core_cm3.h"
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/**************************************************************
------------------------- Includes  ---------------------------
 ***************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "STM32F103x8.h"
#include "stm32f103x8_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"
#include "stm32f103x8_EXTI_driver.h"
#include "stm32f103x8_USART_driver.h"
#include "stm32f103x8_SPI_driver.h"
#include "stm32f103x8_I2C_driver.h"
#include "I2C_Slave_EEPROM.h"

#include "Scheduler.h"

/**************************************************************
---------------------- Global Variables  ----------------------
 ***************************************************************/
Task_t Task1, Task2, Task3, Task4;
unsigned char Task1LED, Task2LED, Task3LED, Task4LED;
Mutex_t Mutex1, Mutex2;
unsigned char payload[3] = {1,2,3};
unsigned char payload2[3] = {1,2,3};

/**************************************************************
---------------------- Tasks Functions  ----------------------
 ***************************************************************/
void Task1_fun()
{
	static int count = 0;
	while(1)
	{
		//Task 1 Code
		Task1LED ^= 1;
		count++;
		if(count == 100)
		{
			RTOS_Acquire_Mutex(&Mutex1, &Task1);
			RTOS_Activate_Task(&Task2);
			RTOS_Acquire_Mutex(&Mutex2, &Task1);
		}
		if(count == 200)
		{
			count = 0;
			RTOS_Release_Mutex(&Mutex1);
			RTOS_Release_Mutex(&Mutex2);
		}
	}
}

void Task2_fun()
{
	static int count = 0;
	while(1)
	{
		//Task 2 Code
		Task2LED ^= 1;
		count++;
		if(count == 100)
		{
			RTOS_Activate_Task(&Task3);
		}
		if(count == 200)
		{
			count = 0;
			RTOS_Terminate_Task(&Task2);
		}
	}
}

void Task3_fun()
{
	static int count = 0;
	while(1)
	{
		//Task 2 Code
		Task3LED ^= 1;
		count++;
		if(count == 100)
		{
			RTOS_Activate_Task(&Task4);
		}
		if(count == 200)
		{
			count = 0;
			RTOS_Terminate_Task(&Task3);
		}
	}
}

void Task4_fun()
{
	static int count = 0;
	while(1)
	{
		//Task 4 Code
		Task4LED ^= 1;
		count++;
		if(count == 3)
		{
			RTOS_Acquire_Mutex(&Mutex2, &Task4);
			RTOS_Acquire_Mutex(&Mutex1, &Task4);
		}
		if( count == 200)
		{
			count = 0;
			RTOS_Release_Mutex(&Mutex1);
			RTOS_Release_Mutex(&Mutex2);
			RTOS_Terminate_Task(&Task4);
		}
	}
}

//priority inversion Example
int main(void)
{
	volatile RTOS_ERROR_t error;

	HAL_init();

	if(RTOS_init() != RTOS_OK)
		while(1);

	/* Initialize Mutex1 */
	Mutex1.Ppayload = payload;
	Mutex1.PayloadSize = 3;
	strcpy(Mutex1.MutexName, "Mutex1_Shared_T1_T4");

	/* Initialize Mutex1 */
	Mutex2.Ppayload = payload2;
	Mutex2.PayloadSize = 3;
	strcpy(Mutex2.MutexName, "Mutex2_Shared_T1_T4");

	/* Initialize Tasks */
	Task1.StackSize = 1024;
	Task1.pTaskEntry = Task1_fun;
	Task1.Priority = 4;
	strcpy(Task1.TaskName, "Task_1");

	Task2.StackSize = 1024;
	Task2.pTaskEntry = Task2_fun;
	Task2.Priority = 3;
	strcpy(Task2.TaskName, "Task_2");

	Task3.StackSize = 1024;
	Task3.pTaskEntry = Task3_fun;
	Task3.Priority = 2;
	strcpy(Task3.TaskName, "Task_3");

	Task4.StackSize = 1024;
	Task4.pTaskEntry = Task4_fun;
	Task4.Priority = 1;
	strcpy(Task4.TaskName, "Task_4");

	error += RTOS_Create_Task(&Task1);
	error += RTOS_Create_Task(&Task2);
	error += RTOS_Create_Task(&Task3);
	error += RTOS_Create_Task(&Task4);

	// Activate Tasks
	RTOS_Activate_Task(&Task1);


	// Start OS
	RTOS_StartOS();

	while (1)
	{

	}
}
