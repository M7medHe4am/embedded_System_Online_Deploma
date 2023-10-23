/*
 * linkedList_studentData.c
 *
 *  Created on: Oct 21, 2023
 *      Author: m7med
 */
#include "lL_buf.h"

struct SStudent* g_PfirstStudent= NULL ;
void add_student()
{

	char temp[40];
	struct SStudent* PnewStudent;
	struct SStudent* PlastStudent;
	if(g_PfirstStudent==NULL)
	{
		PnewStudent=(struct SStudent*)malloc(sizeof (struct SStudent));
		g_PfirstStudent=PnewStudent;
	}
	else
	{
		PlastStudent=g_PfirstStudent;
		while(PlastStudent->PnextStudent)
			{
			PlastStudent=PlastStudent->PnextStudent;
			}

	PnewStudent=(struct SStudent*)malloc(sizeof (struct SStudent));
	PlastStudent->PnextStudent=PnewStudent;
	}
	PnewStudent->PnextStudent=NULL;
	DPRINTF("Enter ID:");
	gets(temp);
	int ref=0;
	struct SStudent* Pcheck=g_PfirstStudent;
	while(Pcheck)
	{
		if(Pcheck->data.id==atoi(temp))
			{
			ref++;
			break;
			}
		else
			{
			Pcheck=Pcheck->PnextStudent;
			}
	}

	if(ref==0)
	 {
	PnewStudent->data.id=atoi(temp);
	DPRINTF("Enter Name:");
	gets(PnewStudent->data.name);
	DPRINTF("Enter height:");
	gets(temp);
	PnewStudent->data.height=atof(temp);

	printf("ID: %d is added successfully\n",PnewStudent->data.id);
	}
	else
	{
		printf("ID does EXIST\n");
		free(PnewStudent);
	}
}

void  delete_student()
{
	struct SStudent* PpreviousStudent=NULL;
	struct SStudent* PselectedStudent;
	PselectedStudent=g_PfirstStudent;
	unsigned int selectedId;
	char temp[40];
	int ref=0;
	DPRINTF("Enter the selected id: ");
	gets(temp);
	selectedId=atoi(temp);
	if(g_PfirstStudent)
	{
		while (PselectedStudent)
		{
			if(PselectedStudent->data.id==selectedId)
			{
				ref=1;
				if(PpreviousStudent)
				{
					PpreviousStudent->PnextStudent=PselectedStudent->PnextStudent;
				}
				else
				{
					g_PfirstStudent->PnextStudent=PselectedStudent->PnextStudent;
				}
				free(PselectedStudent);
				DPRINTF("\n==========================\n");
				DPRINTF("ID:%d Deleted successfully",selectedId);
				DPRINTF("\n==========================\n");
			}
			else
			{
				PpreviousStudent=PselectedStudent;
				PselectedStudent=PselectedStudent->PnextStudent;
			}
		}
		if(ref==0)
		{
		DPRINTF("\n=============\n");
		DPRINTF("ID not found");
		DPRINTF("\n=============\n");
		}
	}
	else
	{
		DPRINTF("\n============\n");
		DPRINTF("List is Empty!!!");
		DPRINTF("\n============\n");
	}

}
void view_students()
{
	struct SStudent* pcurrentStudent=g_PfirstStudent;
	int count =1;
	if(pcurrentStudent)
	{
		while (pcurrentStudent)
		{
			DPRINTF("Record number:%d\n",count);
			DPRINTF("ID = %d\n",pcurrentStudent->data.id);
			DPRINTF("Name = %s\n",pcurrentStudent->data.name);
			DPRINTF("Height = %.2f\n",pcurrentStudent->data.height);
			DPRINTF("================================\n");
			pcurrentStudent=pcurrentStudent->PnextStudent;
			count++;
		}
	}
	else
	{
		DPRINTF("\n============\n");
		DPRINTF("List is Empty!!!");
		DPRINTF("\n============\n");
	}
}


void deleteAll_students()
{
	struct SStudent* pcurrentStudent=g_PfirstStudent;
	struct SStudent* ptemp;
	if(pcurrentStudent)
	{
		while(pcurrentStudent)
		{
			ptemp=pcurrentStudent;
			free(pcurrentStudent);
			pcurrentStudent=ptemp->PnextStudent;
		}
		g_PfirstStudent=NULL;
		DPRINTF("\n========================\n");
		DPRINTF("List is Deleted successfully.");
		DPRINTF("\n========================\n");
	}
	else
	{
		DPRINTF("\n============\n");
		DPRINTF("List is already Empty!!!");
		DPRINTF("\n============\n");

	}

}






