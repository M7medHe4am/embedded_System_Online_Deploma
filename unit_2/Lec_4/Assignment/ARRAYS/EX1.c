/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/* A program to find the sum of two matrices with order of 2*2*/
#include "stdio.h"
int main()
{
	int i,j,k;
	float arra[2][2];
	float arrb[2][2];
	float sum[2][2];
	char a='a';    /* to assign the name of the matrix in the printf scentence*/
	/* THE ARAAYS' INPUT LOOPS.*/
	for(k=0;k<2;k++)
	{
		printf("Enter the elemnets of the(%c)matrix.\n",a);
		if (k==0)
		{
			for(i=0;i<2;i++)
			{
				for(j=0;j<2;j++)
				{
					printf("enter a%d%d: ",i+1,j+1);
					fflush(stdin); fflush(stdout);
					scanf("%f",&arra[i][j]);
				}
			}
		}
		else if (k==1)
		{
			for(i=0;i<2;i++)
			{
				for(j=0;j<2;j++)
				{
					printf("enter b%d%d: ",i+1,j+1);
					fflush(stdin); fflush(stdout);
					scanf("%f",&arrb[i][j]);
				}
			}
		}
		a='b';
	}
	/* THE ARAAYS' SUMMATION LOOP.*/
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			sum[i][j]=arra[i][j]+arrb[i][j];
		}
	}
	/* THE ARAAYS' PRINTING LOOP.*/
	printf("Sum of Matrix: \n\t\t");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%.2f\t",sum[i][j]);
		}
		printf("\n\t\t");
	}
	return 0;
}
