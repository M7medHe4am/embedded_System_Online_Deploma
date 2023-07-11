/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/*frequency of a character*/
#include "stdio.h"
#include <string.h>
int main()
{
	char text[100],c;
	int i,freq=0;
	printf("Enter an string: ");
	fflush(stdin); fflush(stdout);
	gets(text);
	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	strlwr(text);
	for(i=0;i<strlen(text);i++)
		if(text[i]==c||text[i]==c+32)
		++freq;
	printf("Frequency of %c = %d",c,freq);
	return 0;
}
