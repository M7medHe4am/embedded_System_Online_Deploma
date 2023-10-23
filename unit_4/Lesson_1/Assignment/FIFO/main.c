/*
 *	main.c
 * 	CopyRights reserved to: EtCh
 *	LAB PRACTICE
 *
 */
#include "FIFO.h"

void printx(element_type* elementPtr)
{
	DPRINTF("\t\telement ID:%d\n",elementPtr->ID);
	DPRINTF("\t\telement c:%c\n",elementPtr->c);

}

int main()
{

	FIFO_BUF_t uart_buf;
	FIFO_init(&uart_buf,Buffer1,width1);
	char temp[40];
	while (1)
	{
		DPRINTF("===================================\n");
		DPRINTF("Choose one of the following options\n");
		DPRINTF("===================================\n");
		DPRINTF("option 1 : Enqueue item.\n");
		DPRINTF("option 2 : Dequeue item.\n");
		DPRINTF("option 3 : print All items.\n");
		DPRINTF("Your option is:");
		gets(temp);
		switch (atoi(temp))
		{
		case 1 :
		{
			DPRINTF("ID : ");
			gets(temp);
			element_type x;
			x.ID=atoi(temp);
			DPRINTF("c : ");
			gets(temp);
			x.c=temp[0];
			if(FIFO_enqueue(&uart_buf,&x)==FIFO_no_error)
			{DPRINTF("FIFO Enqueued item:\n");
			printx(&x);
			}
			else
			{DPRINTF("FIFO doesn't Exist\n");}
			break ;
		}
		case 2 :
		{
			element_type ret;
			FIFO_Status status;
			status = FIFO_dequeue(&uart_buf,&ret);
			if(status==FIFO_no_error)
			{DPRINTF("FIFO Dequeued item:\n");
			printx(&ret);
			}

			else if (status==FIFO_Empty)
			{DPRINTF("FIFO is Empty\n");}
			else if (status==FIFO_NULL)
			{DPRINTF("FIFO doesn't Exist\n");}
			break ;
		}
		case 3 :
		{
			if(FIFO_Print(&uart_buf,printx)==FIFO_Empty)
			{DPRINTF("FIFO is Empty\n");}

			break ;
		}
		default :
			DPRINTF("Wrong choice !!!");
		}

	}

	return 0;
}



