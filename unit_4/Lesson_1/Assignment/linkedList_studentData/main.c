/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: m7med
 */

#include "lL_buf.h"


int main()
{
	char temp[5];
	int count;
	while(1)
	{
		DPRINTF("====================================\n");
		DPRINTF("choose one of the following options.\n");
		DPRINTF("====================================\n");
		DPRINTF("Option 1 : ADD student.\n");
		DPRINTF("Option 2 : Delete student.\n");
		DPRINTF("Option 3 : View students.\n");
		DPRINTF("Option 4 : Delete All students.\n");
		DPRINTF("Option 5 : Display Specific student.\n");
		DPRINTF("Option 6 : Display No. of students.\n");
		DPRINTF("Option 7 : Display Specific student(in reverse order.)\n");
		DPRINTF("Option 8 : Display the middle student.\n");
		DPRINTF("Option 9 : Reverse the list.\n");
		DPRINTF("====================================\n");
		DPRINTF("Your option is: ");
		gets(temp);
		switch(atoi(temp))
		{
		case 1:
		{
			add_student();
			break;
		}

		case 2:
		{
			delete_student();
			break;
		}
		case 3:
		{
			view_students();
			break;
		}
		case 4:
		{
			deleteAll_students();
			break;
		}
		case 5:
		{
			get_studentid();
			break;
		}
		case 6:
		{
			no_ofStudents(&count);
			break;
		}
		case 7:
		{
			get_reverseIndex();
			break;
		}
		case 8:
				{
					findMiddle();
					break;
				}
		case 9:
		{
			reverse();
			break;
		}
		default :
		{
			DPRINTF("Wrong option!!!\n");
			break;
		}

		}
	}

}
