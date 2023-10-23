/*
 *	FIFO.c
 * 	CopyRights reserved to: EtCh
 *	LAB PRACTICE
 *
 */
#include "FIFO.h"
static void FIFO_incHead(FIFO_BUF_t* fifo)
{
	if(fifo->head==(fifo->capacity-1))
		{fifo->head=0;}
	else
		{fifo->head++;}

}
static void FIFO_incTail(FIFO_BUF_t* fifo)
{
	if(fifo->tail==(fifo->capacity-1))
			{fifo->tail=0;}
		else
			{fifo->tail++;}
}
FIFO_Status FIFO_init(FIFO_BUF_t* fifo, element_type* buffer,unsigned int cap)
{
	fifo->base=buffer;
	//checks if the buffer is created
	if(fifo->base==NULL)
	{return FIFO_NULL;}
	//Initializing FIFO

	fifo->head=0;
	fifo->tail=0;
	fifo->count=0;
	fifo->capacity=cap;
	return FIFO_no_error;
}
FIFO_Status FIFO_enqueue(FIFO_BUF_t* fifo, element_type* item)
{
	//checking if the FIFO is created
	if(!fifo->base)
	{return FIFO_NULL;}
	fifo->base[fifo->head]=*item;
	FIFO_incHead(fifo);
	if(fifo->count==fifo->capacity)
	{
		FIFO_incTail(fifo);
	}
	else
	{
		fifo->count++;
	}

	return FIFO_no_error;

}
FIFO_Status FIFO_dequeue(FIFO_BUF_t* fifo, element_type* item)
{
	//checking if the FIFO is created
		if(!fifo->base)
		{return FIFO_NULL;}
	//check if empty
		if(fifo->count==0)
		{return FIFO_Empty;}
	*item=fifo->base[fifo->tail];
	FIFO_incTail(fifo);
	fifo->count--;
	return FIFO_no_error;
}

FIFO_Status FIFO_Print(FIFO_BUF_t* fifo,funcPtr fp)
{
	//check if empty
			if(fifo->count==0)
			{return FIFO_Empty;}
			int i;
			unsigned int  temp=fifo->tail;
		for(i=0 ;i<fifo->count;i++)
		{
			fp(&fifo->base[fifo->tail]);
			FIFO_incTail(fifo);
		}
		fifo->tail=temp;
		return FIFO_no_error;
}


