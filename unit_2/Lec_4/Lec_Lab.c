/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	float degrees [10];
	int i;
	for (i=0;i<10;i++)
	{
		printf("Enter student (%d) degree: ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&degrees[i]);
	}
	for (i=0;i<10;i++)
		printf("Enter student (%d) degree is: %0.2f\n",i+1,degrees[i]);
	return 0;
}


