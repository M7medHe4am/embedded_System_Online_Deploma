/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	int x,i;
	unsigned long long int fact=1;

	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	if (x<0)
		printf ("ERROR!!! Factorial of negative number doesn't exist");
	else if (x==0)
		printf("Factorial = zero");
	else
	{
		for (i=1;i<=x;i++)
		{
			fact*=i;
		}
		printf("Factorial = %lu",fact);
	}

	return 0;

}


