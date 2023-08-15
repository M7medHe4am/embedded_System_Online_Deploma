/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int factorial(int x);
int main()
{
	int x;
	printf("Enter a positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf("Factorial of %d = %d",x,factorial(x));
	return 0;
}

int factorial(int x)
{
	if(x!=1&&x!=0)
	return x*factorial(x-1);
	else if(x==0)
		return 0;
}
