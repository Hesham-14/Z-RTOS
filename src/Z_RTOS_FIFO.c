/*
 * Z_RTOS_FIFO.c
 *
 *  Created on: Dec 7, 2023
 *      Author: hesham mohamed
 */

/**************************************************************
------------------------- Includes  ---------------------------
 ***************************************************************/
#include "Z_RTOS_FIFO.h"

/**************************************************************
---------------------- Global Variables  ----------------------
 ***************************************************************/

/**************************************************************
---------------------- Handler Functions  ----------------------
 ***************************************************************/


/**************************************************************
------------------ APIs Functions Definitions  -----------------
 ***************************************************************/

/**===========================================================
 * @Fn			-
 * @brief 		-
 * @param [in]	- none
 * @retval 		-
 * Note			- none
 */
Buffer_Status FIFO_Init (FIFO_Buf_t* fifo, element_type* buf, unsigned int length)
{
	if(!buf)
		return FIFO_NULL;

	fifo->base = buf;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length = length;
	fifo->counter = 0;

	return FIFO_NO_ERROR;
}


Buffer_Status FIFO_Enqueue (FIFO_Buf_t* fifo, element_type item)
{
	/* fifo null */
	if(!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo full */
	if((fifo->head == fifo->tail) && (fifo->counter == fifo->length))
		return FIFO_FULL;

	/* add item */
	*(fifo->tail) = item;
	fifo->counter++;

	/* For Circular fifo again */
	/* circular enqueue */
	if(fifo->tail == (((unsigned int)fifo->base + (4*fifo->length)) - 4 ))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_NO_ERROR;
}


Buffer_Status FIFO_Dequeue (FIFO_Buf_t* fifo, element_type* item)
{
	/* fifo null */
	if(!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo empty */
	if(fifo->head == fifo->tail)
		return FIFO_EMPTY;

	*item = *(fifo->head);
	fifo->counter--;

	/* For Circular fifo again */
	/* circular enqueue */
	if(fifo->head == (((unsigned int)fifo->base + (4*fifo->length)) - 4 ))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_NO_ERROR;
}


Buffer_Status FIFO_is_Full (FIFO_Buf_t* fifo)
{
	/* fifo null */
	if(!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo full */
	if((fifo->head == fifo->tail) && (fifo->counter == fifo->length))
		return FIFO_FULL;

	return FIFO_NO_ERROR;
}
void FIFO_print (FIFO_Buf_t* fifo)
{

}

/*************************************************************
------------------------ Other Functions  -----------------------
 **************************************************************/




