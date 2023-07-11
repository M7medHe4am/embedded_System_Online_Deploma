/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/* calculating average of numbers stored in array*/
#include "stdio.h"
int main()
{
	float arr[50], sum=0;
	int i,n,j;
	for(i=0;i<2;i++)
	{
		printf("Enter the number of data: ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&n);
		if(n>50 || n<=0)
			printf("Error! number is out of range (1~50)\n");
		else
		{
			for(j=0;j<n;j++)
			{
				printf("%d. Enter a number: ",i+1);
				fflush(stdin); fflush(stdout);
				scanf("%f",&arr[i]);
				sum+=arr[i];
			}
			printf("Average = %.2f",sum/n);
			break;
		}
	}
	return 0;
}
