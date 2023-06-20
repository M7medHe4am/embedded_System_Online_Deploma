/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	char x;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	printf("ASCII value of %c = %d ",x,x);


	return 0;

}


