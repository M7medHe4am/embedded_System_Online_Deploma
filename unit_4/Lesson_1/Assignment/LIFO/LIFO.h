/*
*	LIFO.h
* 	CopyRights reserved to: EtCh
*	LAB PRACTICE
*
*/

#ifndef LIFO_H_
#define LIFO_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define DPRINTF(...) {fflush(stdout);\
					  fflush(stdin);\
					  printf(__VA_ARGS__);\
					  fflush(stdout);\
					  fflush(stdin);}
//Type definitions
typedef struct
{
	unsigned int* Base  ;
	unsigned int* Head  ;
	unsigned int Length ;
	unsigned int count  ;
}LIFO_BUF_t;
//LIFO Returned Status
typedef enum
{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_NULL
}LIFO_STATUS;

//APIs
LIFO_STATUS LIFO_init(LIFO_BUF_t* lifo, unsigned int* buffer ,unsigned int length);
LIFO_STATUS LIFO_add_item(LIFO_BUF_t* lifo,unsigned int item);
LIFO_STATUS LIFO_get_item(LIFO_BUF_t* lifo,unsigned int* item);











#endif /*LIFO.h*/
