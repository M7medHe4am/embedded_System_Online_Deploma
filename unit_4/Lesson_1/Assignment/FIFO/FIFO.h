/*
 *	FIFO.h
 * 	CopyRights reserved to: EtCh
 *	LAB PRACTICE
 *
 */
#ifndef FIFO_H_
#define FIFO_H_
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define DPRINTF(...) {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}
//Select The element type here:
typedef struct
{	int ID;
	char c;
} element_type ;
//create Buffer here:
#define width1 5
element_type Buffer1[width1];
/*You can add any number of Buffers the same way
 *
 *
 *
 *
 */

//Type definitions
typedef void (*funcPtr)(element_type*);
typedef struct
{
	element_type* base ;
	unsigned int head  ;
	unsigned int tail    ;
	unsigned int count   ;
	unsigned int capacity;
}FIFO_BUF_t;
//STATUS Definition
typedef enum
{
	FIFO_no_error,
	FIFO_NULL,
	FIFO_Empty,
	FIFO_Full
}FIFO_Status;

//APIs

FIFO_Status FIFO_init(FIFO_BUF_t* fifo, element_type* buffer,unsigned int cap);
FIFO_Status FIFO_enqueue(FIFO_BUF_t* fifo, element_type* item);
FIFO_Status FIFO_dequeue(FIFO_BUF_t* fifo, element_type* item);

FIFO_Status FIFO_Print(FIFO_BUF_t* fifo,funcPtr fp);



#endif /*FIFO.h*/
