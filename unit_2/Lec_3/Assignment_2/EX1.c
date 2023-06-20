/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	int x;

	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	if (x%2==0)
	{
		printf ("%d is even",x);
	}
	else
		printf ("%d is odd",x);

	return 0;

}


