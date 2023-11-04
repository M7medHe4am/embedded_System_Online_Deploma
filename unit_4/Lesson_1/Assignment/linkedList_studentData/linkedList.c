/*
 * linkedList.c
 *
 *  Created on: Nov 4, 2023
 *      Author: m7med
 */


#include "linkedlist.h"
struct studentData* g_pFirst_student = NULL;
void fillRecord(struct studentData* newStudent)
{
	unsigned int ID;
	char temp[20];
	LL_status status;
	DPRINTF("Enter ID: ");
	ID=atoi(gets(temp));
	newStudent->data.ID=ID;
	if(atoi(temp)<0)
		{
		LL_deleteStudent(&ID);
		DPRINTF("WRONG CHOISE !!!\n");
		}
	else {
	status = checkforExistance(newStudent,ID);
	if(status==DONE)
	{
	DPRINTF("Enter Name: ");
	gets(newStudent->data.name);
	DPRINTF("Enter birth date.\n");
	DPRINTF("day:");
	gets(temp);
	newStudent->data.day=atoi(temp);
	DPRINTF("month:");
	gets(temp);
	newStudent->data.month=atoi(temp);
	DPRINTF("year:");
	gets(temp);
	newStudent->data.year=atoi(temp);
	DPRINTF("Enter Height:");
	gets(temp);
	newStudent->data.height=atof(temp);
	}
	else if (status==ID_EXIST)
	{
		DPRINTF("ID does Exist!!!\n");
	}
	}

}
LL_status checkforExistance(struct studentData* newStudent,unsigned int id)
{
	struct studentData* currentStudent=g_pFirst_student;
	int count =0,i;
	unsigned int temp;
	countElements(&count);
	for(i=0;i<(count-1);i++)
	{
		if(currentStudent->data.ID==newStudent->data.ID)
		{
			newStudent->data.ID=-1;
			temp=newStudent->data.ID;
			LL_deleteStudent(&temp);
			return ID_EXIST;
		}
		currentStudent=currentStudent->pNext_student;
	}
	return DONE;



}

void viewstudent(struct studentData*currentStudent)
{
	DPRINTF("ID: %d\n",currentStudent->data.ID);
	DPRINTF("Name: %s\n",currentStudent->data.name);
	DPRINTF("height: %.2f\n",currentStudent->data.height);
	DPRINTF("BirthDate:%d/%d/%d\n",currentStudent->data.day,currentStudent->data.month,currentStudent->data.year);
	DPRINTF("\n===========================\n");
}

void LL_addStudent()
{
	struct studentData* pLastStudent;
	struct studentData* pNewStudent;
	if(g_pFirst_student==NULL)
	{
		pNewStudent=(struct studentData*)malloc(sizeof(struct studentData));
		g_pFirst_student=pNewStudent;
	}
	else
	{
		pLastStudent=g_pFirst_student;
		while(pLastStudent->pNext_student)
			pLastStudent=pLastStudent->pNext_student;
		pNewStudent=(struct studentData*)malloc(sizeof(struct studentData));
		pLastStudent->pNext_student=pNewStudent;
	}
	pNewStudent->pNext_student=NULL;
	fillRecord(pNewStudent);

}


LL_status LL_deleteStudent(unsigned int* ID)
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	struct studentData* previousStudent;
	struct studentData* currentStudent=g_pFirst_student;

	while(currentStudent)
	{
		if(currentStudent->data.ID!=*ID)
		{
			previousStudent=currentStudent;
			currentStudent=currentStudent->pNext_student;

		}
		else
		{
			if(currentStudent==g_pFirst_student)
			{
				g_pFirst_student=currentStudent->pNext_student;

			}
			else
			{

				previousStudent->pNext_student=currentStudent->pNext_student;
			}
			free(currentStudent);
			return DONE;
		}
	}
	return ID_notFound;
}

LL_status LL_viewAll()
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	struct studentData* currentStudent=g_pFirst_student;
	while(currentStudent)
	{
		viewstudent(currentStudent);
		currentStudent=currentStudent->pNext_student;
	}
	return DONE;

}


LL_status LL_deleteAll()
{

	if(g_pFirst_student==NULL)
		return NO_DATA;
	struct studentData* currentStudent=g_pFirst_student;
	struct studentData* temp;

	while(currentStudent)
	{
		temp=currentStudent->pNext_student;
		free(currentStudent);
		currentStudent=temp;
	}
	g_pFirst_student=NULL;
	return DONE;

}
LL_status countElements(int *count)
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	struct studentData* currentstudent=g_pFirst_student;
	while(currentstudent)
	{
		(*count)++;
		currentstudent=currentstudent->pNext_student;
	}
	return DONE;
}


LL_status getNth(unsigned int* index)
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	int count=0;
	countElements(&count);
	struct studentData*currentStudent=g_pFirst_student;
	if((*index>=count)||(*index<0))
	{
		return ID_notFound;
	}
	else
	{
		int i=0;
		for(i=0;i<count;i++)
		{
			if(i==*index)
			{
				viewstudent(currentStudent);
				return DONE;
			}
			else
			{
				currentStudent=currentStudent->pNext_student;
			}
		}
	}
}
LL_status getNthReversed(unsigned int* index)
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	int count=0;
	countElements(&count);
	*index=(count-1)-*index;
	return getNth(index);
}
LL_status getMiddleElement()
{
	if(g_pFirst_student==NULL)
		return NO_DATA;
	int count=0,i=1;
	countElements(&count);
	count=(count/2)+1;
	struct studentData*currentStudent=g_pFirst_student;
	while(i!=count)
	{
		currentStudent=currentStudent->pNext_student;
		i++;
	}
	viewstudent(currentStudent);
	 return DONE;

}





