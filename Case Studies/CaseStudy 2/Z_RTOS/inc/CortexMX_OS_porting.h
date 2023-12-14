/*
 * CortexMX_OS_porting.h
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

/*****************************************
-------------   Includes   -------------
*****************************************/
#include "core_cm3.h"


/******************************************************************
---------   User Type Definition || Prebuild Configure   ---------
*******************************************************************/
extern int _estack;


/*****************************************************
---------   Macros Configuration Refrences  --------
******************************************************/
#define MainStackSize	3072

#define OS_SET_PSP(add)				__asm volatile("mov r0,%0 \n\t msr PSP,r0" : : "r" (add) )
#define OS_GET_PSP(add)				__asm volatile("mrs r0,PSP \n\t mov %0,r0"   : "=r" (add) )


#define OS_SWITCH_SP_to_PSP			__asm volatile("mrs r0, CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP			__asm volatile("mrs r0, CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")

//Clear Bit 0 CONTROL register
#define OS_SWITCH_to_privilaged		__asm(" mrs r3, CONTROL  \n\t"	\
										  " lsr r3,r3,#0x1   \n\t"	\
										  " lsl r3,r3,#0x1   \n\t"	\
										  " msr CONTROL, r3");

//Set Bit 0 CONTROL register
#define OS_SWITCH_to_unprivilaged		__asm(" mrs r3, CONTROL  \n\t"	\
										  	  " orr r3,r3,#0x1   \n\t"	\
											  " msr CONTROL, r3");

/*****************************************
----------------- APIs  -----------------
*****************************************/
void HAL_init();
void Trigger_OS_PendSV();
void Start_Ticker();



#endif /* INC_CORTEXMX_OS_PORTING_H_ */
