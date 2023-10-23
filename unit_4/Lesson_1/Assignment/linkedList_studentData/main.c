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
	while(1)
	{
		DPRINTF("choose one of the following options.\n");
		DPRINTF("====================================\n");
		DPRINTF("Option 1 : ADD student.\n");
		DPRINTF("Option 2 : Delete student.\n");
		DPRINTF("Option 3 : View students.\n");
		DPRINTF("Option 4 : Delete All students.\n");
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
		default :
		{
			DPRINTF("Wrong option\n");
			break;
		}

		}
	}

}
