/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int recursive(int n);
int main()
{
	int n=1,sum=0;
	sum =recursive(n);
	printf("The sum is: %d",sum);
}

int recursive(int n)
{
	static int sum=0;
	if(n<=100)
	sum=n+recursive(n+1);
	else
		return sum;
}



