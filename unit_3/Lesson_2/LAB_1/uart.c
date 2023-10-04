#include "uart.h"
#define UART0DR *((vuint32_t*)((uint32*)0x101f1000))
void Send_String (uint8* Ptr_String)
{
	while (*Ptr_String != '\0')
	{
		UART0DR = (uint32)*Ptr_String;
		Ptr_String++;
	}
}