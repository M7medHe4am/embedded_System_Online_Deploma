/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/*length of string without strlen()*/
#include "stdio.h"
int main()
{
	char text[100];
	int i,count=0;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	for(i=0;text[i]!=0;i++)
	{
		if(text[i]==' ')
			continue;
		count+=1;
	}
	printf("Length of string is: %d",count);

	return 0;
}
