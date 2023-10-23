/*
 *	LIFO.c
 * 	CopyRights reserved to: EtCh
 *	LAB PRACTICE
 *
 */
#include "LIFO.h"


LIFO_STATUS LIFO_init(LIFO_BUF_t* lifo, unsigned int* buffer ,unsigned int length)
{
	if(buffer==NULL)
		return LIFO_NULL;
	lifo->Base  =buffer;
	lifo->Head  =buffer;
	lifo->Length=length;
	lifo->count =0;
	return LIFO_no_error;

}
LIFO_STATUS LIFO_add_item(LIFO_BUF_t* lifo,unsigned int item)
{
	//Check if the LIFO is valid
	if(!lifo->Base||!lifo->Head)
		return LIFO_NULL;
	//Check if the LIFO is FULL
	if(lifo->count==lifo->Length)
		return LIFO_full;
	//Adding the value
	*(lifo->Head)=item;
	lifo->count++;
	lifo->Head++;
	return LIFO_no_error;
}
LIFO_STATUS LIFO_get_item(LIFO_BUF_t* lifo,unsigned int* item)
{
	//Check if the LIFO is valid
	if(!lifo->Base||!lifo->Head)
		return LIFO_NULL;
	//Check if LIFO is Empty
	if(lifo->count == 0)
		return LIFO_empty;
	//Getting the value
	lifo->Head--;
	*(item)=*(lifo->Head);
	lifo->count--;
	return LIFO_no_error;

}
