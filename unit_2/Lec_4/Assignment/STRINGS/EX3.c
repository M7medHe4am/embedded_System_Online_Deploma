/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/*REVERSE OF A STRING*/
#include "stdio.h"
#include "string.h"
int main()
{
	char text[100],rev[100];
	int y,x,i;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	x=strlen(text);
	y=x;
	rev[y]=0;
	for(i=0;i<x;i++)
	{
		rev[y-1]=text[i];
		--y;
	}

	printf("Reverse string is: %s",rev);

	return 0;
}
