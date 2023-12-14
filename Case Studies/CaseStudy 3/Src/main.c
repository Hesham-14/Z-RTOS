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
//		if(count == 30)
//		{
//			RTOS_Activate_Task(&Task4);
//			count = 0;
//		}
		RTOS_Wait_Task(100, &Task1);		//toggle every 100 ms
	}
}

void Task2_fun()
{
	while(1)
	{
		//Task 2 Code
		Task2LED ^= 1;
		RTOS_Wait_Task(300, &Task2);
	}
}

void Task3_fun()
{
	while(1)
	{
		//Task 2 Code
		Task3LED ^= 1;
		RTOS_Wait_Task(500, &Task3);
	}
}

void Task4_fun()
{
	static int count=0;
	while(1)
	{
		//Task 4 Code
		Task4LED ^= 1;
		count++;
//		if(count == 0xFFF)
//		{
//			RTOS_Terminate_Task(&Task4);
//			count = 0;
//		}
		RTOS_Wait_Task(1000, &Task4);		//toggle every 1 s
	}
}

//priority inversion Example
int main(void)
{
	volatile RTOS_ERROR_t error;

	HAL_init();

	if(RTOS_init() != RTOS_OK)
		while(1);

	/* Initialize Tasks */
	Task1.StackSize = 1024;
	Task1.pTaskEntry = Task1_fun;
	Task1.Priority = 3;
	strcpy(Task1.TaskName, "Task_1");

	Task2.StackSize = 1024;
	Task2.pTaskEntry = Task2_fun;
	Task2.Priority = 3;
	strcpy(Task2.TaskName, "Task_2");

	Task3.StackSize = 1024;
	Task3.pTaskEntry = Task3_fun;
	Task3.Priority = 3;
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
	RTOS_Activate_Task(&Task2);
	RTOS_Activate_Task(&Task3);

	// Start OS
	RTOS_StartOS();

	while (1)
	{

	}
}
