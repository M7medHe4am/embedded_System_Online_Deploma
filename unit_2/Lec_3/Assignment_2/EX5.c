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
	if ((x>='a' && x<='z')||(x>='A'&&x<='Z'))
		printf ("%c is an alphabet",x);
	else
		printf ("%c is not an alphabet",x);

	return 0;


}


