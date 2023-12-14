/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */

/**************************************************************
------------------------- Includes  ---------------------------
 ***************************************************************/
#include "CortexMX_OS_porting.h"

/**************************************************************
---------------------- Global Variables  ----------------------
 ***************************************************************/
unsigned char SysTickLED;

/*************************************************************
---------------------- Generic Macros  ----------------------
 **************************************************************/


/**************************************************************
---------------------- Handler Functions  ----------------------
 ***************************************************************/
void HardFault_Handler(void)
{
	while(1);
}
void MemManage_Handler(void)
{
	while(1);
}
void BusFault_Handler(void)
{
	while(1);
}
void UsageFault_Handler(void)
{
	while(1);
}

__attribute ((naked)) void SVC_Handler ()
{
	// SWITCH_CPU_Accesslevel (privileged)
	__asm ("tst lr, #4 \n\t"
			"ITE EQ \n\t"	//To execute Thumb instructions conditionally, you can either use an IT instruction, or a conditional branch instruction
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B OS_SVC_Handler");
}


/**************************************************************
------------------ APIs Functions Definitions  -----------------
 ***************************************************************/
void HAL_init()
{
	/* Initialize Clock tree (RCC -> SysTick Timer & CPU) 8 MHz
	 * 8 MHz
	 * 1 count -> 0.125 us
	 * x counts -> 1ms
	 * x = 8000 count
	 */

	/* Init HW */
	/* Clock Tree */
	/* RCC Default values makes CPU clock & SysTick Timer clock = 8 MHz */

	// Decrease PendSV interrupt priority to be smaller or equal to sysTick priority (=14)
	__NVIC_SetPriority(PendSV_IRQn, 15);

}

void Trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


/**===========================================================
 * @Fn			-
 * @brief 		-
 * @param [in]	-
 * @param [in]	-
 * @retval 		- none
 * Note			-
 */
void Start_Ticker()
{
	SysTick_Config(8000);
}






/*************************************************************
------------------------ ISR Functions  -----------------------
 **************************************************************/
void SysTick_Handler(void)
{
	SysTickLED ^= 1;

	//1. Determine Pcurrent & Pnext
	Decide_What_Next();

	//2. Switch Context & restore
	Trigger_OS_PendSV();
}


