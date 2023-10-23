/*
 * linkedList_studentData.h
 *
 *  Created on: Oct 21, 2023
 *      Author: m7med
 */


#ifndef LL_BUF_H_
#define LL_BUF_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#define DPRINTF(...) {fflush(stdout);\
					  fflush(stdin);\
					  printf(__VA_ARGS__);\
					  fflush(stdout);\
					  fflush(stdin);}




typedef struct
{
	int id;
	unsigned char name[40];
	float height ;
}SData;
struct SStudent
{
	SData data;
	struct SStudent* PnextStudent;
};




//APIs

void add_student();
void  delete_student();
void view_students();
void deleteAll_students();
void get_studentid();
void no_ofStudents(int* count);
void get_reverseIndex();
void findMiddle();
void reverse();

#endif /* LL_BUF_H_ */
