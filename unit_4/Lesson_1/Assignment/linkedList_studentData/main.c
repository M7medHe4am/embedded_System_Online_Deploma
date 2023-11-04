/*
 * main.c
 *
 *  Created on: Nov 4, 2023
 *      Author: m7med
 */


#include "linkedlist.h"


int main()
{
	char temp[20];

	while(1)
	{
		DPRINTF("======================================\n");
		DPRINTF("choose one of the following options.\n");
		DPRINTF("======================================\n");
		DPRINTF("option 1 : Add student.\n");
		DPRINTF("option 2 : Delete student.\n");
		DPRINTF("option 3 : View students.\n");
		DPRINTF("option 4 : Delete ALL student.\n");
		DPRINTF("option 5 : get Nth student.\n");
		DPRINTF("option 6 : get No of students.\n");
		DPRINTF("option 7 : get middle student.\n");
		DPRINTF("======================================\n");
		DPRINTF("your option is: ");
		gets(temp);
		switch (atoi(temp))
		{
		case 1:
		{
			LL_addStudent();
		}
		break;
		case 2:
		{
			unsigned int ID;
			LL_status status;
			DPRINTF("Enter student's ID:");
			gets(temp);
			ID=atoi(temp);
			status=LL_deleteStudent(&ID);
			if(status==NO_DATA)
			{DPRINTF("No Data yet!!!\n");}
			else if(status==ID_notFound)
			{DPRINTF("ID doesn't Exist!!!\n");}
			else
			{DPRINTF("Deletion Succeeded\n");}
		}
		break;
		case 3:
		{
			LL_status status;
			status=LL_viewAll();
			if(status==NO_DATA)
				DPRINTF("No Data yet!!!\n");
		}
		break;
		case 4:
		{
			LL_status status;
			status=LL_deleteAll();
			if(status==NO_DATA)
			{DPRINTF("No Data yet!!!\n");}
			else
				DPRINTF("Deletion Succeeded\n");
		}
		break;
		case 5 :
		{
			LL_status status;
			unsigned int index;
			DPRINTF("Enter index:");
			index = atoi(gets(temp));
			DPRINTF("to get Nth student enter : 1 \n");
			DPRINTF("to get Nth student in reverse  enter : 2 \n");
			DPRINTF("Your option is:");
			switch (atoi(gets(temp)))
			{
			case 1 :
			{status=getNth(&index);}
			break;
			case 2 :
			{status=getNthReversed(&index);}
			break;
			default :
			{DPRINTF("WRONG OPTION!!!\n");}
			break;
			}

			if(status==NO_DATA)
			{DPRINTF("No Data yet!!!\n");}
			else if(status==ID_notFound)
			{DPRINTF("ID doesn't Exist!!!\n");}
		}
		break;
		case 6 :
		{
			int count=0;
			if(countElements(&count)==NO_DATA)
			{DPRINTF("No Data yet!!!\n");}
			else
			{DPRINTF("count is: %d\n",count);}
		}
		break;
		case 7 :
		{
			if(getMiddleElement()==NO_DATA)
			{DPRINTF("No Data yet!!!\n");}
		}
		break;
		default :
		{
			DPRINTF("WRONG OPTION!!!\n");
		}

		}

	}

	return 0;
}

