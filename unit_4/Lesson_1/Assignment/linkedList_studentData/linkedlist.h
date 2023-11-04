/*
 * linkedlist.h
 *
 *  Created on: Nov 4, 2023
 *      Author: m7med
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


#define DPRINTF(...) {fflush(stdout);\
					  fflush(stdin);\
					  printf(__VA_ARGS__);\
					  fflush(stdout);\
					  fflush(stdin);}

typedef struct
{
	char name[40];
	int ID;
	float height;
	unsigned int day;
	unsigned int month;
	unsigned int year;

}Sdata;


struct studentData
{
	Sdata data;
	struct studentData *pNext_student;
};

typedef enum
{
	NO_DATA,
	DONE,
	ID_notFound,
	ID_EXIST
}LL_status;

//APIS
void fillRecord(struct studentData* newStudent);
void LL_addStudent();
LL_status LL_deleteStudent(unsigned int* ID);
LL_status LL_viewAll();
LL_status LL_deleteAll();
LL_status getNth(unsigned int* index);
void viewstudent(struct studentData*currentStudent);
LL_status countElements(int *count);

LL_status checkforExistance(struct studentData* newstudent,unsigned int id);
LL_status getNthReversed(unsigned int* index);
LL_status getMiddleElement();





#endif /* LINKEDLIST_H_ */
