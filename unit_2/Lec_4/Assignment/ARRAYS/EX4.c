/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/*insert an element in an array*/
#include "stdio.h"
int main()
{
	int x,i,l;
	float arr[50],e;
	printf("Enter number of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	for (i=0;i<x;i++)
		arr[i]=i+1;
	printf("The matrix is: \n");
	for (i=0;i<x;i++)
		printf("%.2f\t",arr[i]);
	printf("\nEnter the element to be inserted: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&e);
	printf("Enter the location: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&l);
	for(i=x;i>l;i--)
		arr[i]=arr[i-1];
	arr[l]=e;
	printf("The new matrix is: \n");
	for (i=0;i<=x;i++)
		printf("%.2f\t",arr[i]);
	return 0;
}
