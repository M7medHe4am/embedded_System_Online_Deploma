/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/*search an element in an array*/
#include "stdio.h"
int main()
{
	int n,i;
	float arr[50],s;
	char a='f';
	printf("Enter the number of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the element No. (%d): ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&arr[i]);
	}
	printf("Enter the element you are searching for: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&s);
	for (i=0;i<n;i++)
	{
		if(arr[i]==s)
		{
			printf("\nThe No. is found at location = %d",i+1);
			a='t';
		}
	}
	if(a=='f')
		printf("The No.is not found.");
	return 0;
}
