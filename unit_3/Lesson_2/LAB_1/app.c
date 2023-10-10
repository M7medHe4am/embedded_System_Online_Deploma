#include "uart.h"
unsigned char String_Buf[100]="Learn-in-depth:Muhammad Hesham";
unsigned char const String_Buf2[100]="Learn-in-depth:Muhammad Hesham";
unsigned char const String_Buf3[100]="Learn-in-depth:Muhammad Hesham";
unsigned char const String_Buf4[100]="Learn-in-depth:Muhammad Hesham";
void main (void)
{
	Send_String (String_Buf);
}