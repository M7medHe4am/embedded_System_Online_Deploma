/*
 *	main.c
 * 	CopyRights reserved to: EtCh
 *	LAB PRACTICE
 *
 */


#include "LIFO.h"
unsigned int buffer1[5];

int main()
{
	LIFO_BUF_t uart_buf ;
	LIFO_init(&uart_buf,buffer1,5);
	while(1)
	{
		char item[40];
		DPRINTF("====================================\n");
		DPRINTF("Choose one of the following options.\n");
		DPRINTF("====================================\n");
		DPRINTF("Option 1 : Add item.\n");
		DPRINTF("Option 2 : Get item.\n");
		DPRINTF("Option:");
		gets(item);
		switch (atoi(item))
		{
		case 1 :
		{
			DPRINTF("Add Item: ");
			gets(item);
			LIFO_STATUS status = LIFO_add_item(&uart_buf,atoi(item));
			if(status==LIFO_no_error)
				{DPRINTF("UART_LIFO added :%d\n",atoi(item));}
			else if (status==LIFO_NULL)
				{DPRINTF("LIFO ERROR !!\n");}
			else if (status==LIFO_full)
				{DPRINTF("LIFO is FULL !!\n");}
			break;
		}

		case 2 :
		{
			unsigned int temp;
			LIFO_STATUS status =LIFO_get_item(&uart_buf,&temp);
			if(status==LIFO_no_error)
				{DPRINTF("UART_LIFO got :%d\n",temp);}
			else if (status==LIFO_NULL)
				{DPRINTF("LIFO ERROR !!\n");}
			else if (status==LIFO_empty)
				{DPRINTF("LIFO is Empty !!\n");}
			break;
		}
		default :
			DPRINTF("Wrong choice!\n");
		}
	}
	return 0;
}
