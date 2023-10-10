#include "uart.h"
#define UART0DR *((volatile unsigned int*)((unsigned int*)0x101f1000))
void Send_String (unsigned char* Ptr_String)
{
	while (*Ptr_String != '\0')
	{
		UART0DR = (unsigned int)*Ptr_String;
		Ptr_String++;
	}
}