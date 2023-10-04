/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
#include<string.h>
void count(int n);
int main()
{
	int n;
	printf("Please enter an integer number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	count(n);
	return 0;
}

void count(int n)
{
	int i=1,counter=0;
	while(i<=65000)
	{
		if(n&i)
			counter++;
		i*=2;
	}
	printf("The sum is: %d",counter);
}


