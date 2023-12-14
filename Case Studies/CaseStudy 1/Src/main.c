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
Task_t Task1, Task2, Task3;
unsigned char Task1LED, Task2LED, Task3LED;

/**************************************************************
---------------------- Tasks Functions  ----------------------
***************************************************************/
void Task1_fun()
{
	while(1)
	{
		//Task 1 Code
		Task1LED ^= 1;
	}
}

void Task2_fun()
{
	while(1)
	{
		//Task 2 Code
		Task2LED ^= 1;
	}
}

void Task3_fun()
{
	while(1)
	{
		//Task 2 Code
		Task3LED ^= 1;
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

	error += RTOS_Create_Task(&Task1);
	error += RTOS_Create_Task(&Task2);
	error += RTOS_Create_Task(&Task3);

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
