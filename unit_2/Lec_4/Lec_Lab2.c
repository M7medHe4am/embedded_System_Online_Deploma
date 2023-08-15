/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	int i,j;
	float arr[3][3];
	float tr[3][3];
	for (i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			printf("enter the item(%d,%d): ",i,j);
			fflush(stdin); fflush(stdout);
			scanf("%f",&arr[i][j]);
		}
	printf("The Matrix is: \r\n");
	for (i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%.2f\t",arr[i][j]);
		printf("\r\n");
	}
	printf("The transpose is: \r\n");
	for (i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			tr[i][j]=arr[j][i];
			printf("%.2f\t",tr[i][j]);
		}
		printf("\r\n");
	}
	return 0;
}


