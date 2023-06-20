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
	int sum=0;

	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	for (i=x;i>0;i--)
	{
		sum+=i;
	}
	printf("sum = %d",sum);
	return 0;


}


