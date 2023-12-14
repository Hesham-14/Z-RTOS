/*
 * Z_RTOS_FIFO.h
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */

#ifndef INC_Z_RTOS_FIFO_H_
#define INC_Z_RTOS_FIFO_H_

/*****************************************
-------------   Includes   -------------
 *****************************************/
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "Scheduler.h"

/*****************************************
---------  User Type Definition ---------
 *****************************************/
#define element_type Task_t*

typedef struct{
	unsigned int counter;
	element_type* head;
	element_type* tail;
	element_type* base;
	unsigned int length;
}FIFO_Buf_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL
}Buffer_Status;


/*****************************************
----------------- APIs  -----------------
 *****************************************/
Buffer_Status FIFO_Init (FIFO_Buf_t* fifo, element_type* buf, unsigned int length);
Buffer_Status FIFO_Enqueue (FIFO_Buf_t* fifo, element_type item);
Buffer_Status FIFO_Dequeue (FIFO_Buf_t* fifo, element_type* item);
Buffer_Status FIFO_is_Full (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);

#endif /* INC_Z_RTOS_FIFO_H_ */
