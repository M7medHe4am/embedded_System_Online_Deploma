#include "uart.h"
uint8 String_Buf[100]="Learn-in-depth:Muhammad Hesham";
void main (void)
{
	Send_String (String_Buf);
}