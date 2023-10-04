/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void printunique(int nare[],int k);
void uniqe(int arr[],int n);
int main()
{
	int n,i;
	printf("Enter the number of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	int arr[n];
	printf("Enter the array elements: ");
	fflush(stdin); fflush(stdout);
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	uniqe(arr,n);
	return 0;
}
void uniqe(int arr[],int n)
{
	int i,j,k=0;
	int nare[n];
	for(i=0;i<n;i++)
	{
		int counter =0;
		for(j=0;j<n;j++)
		{
			if(i==j)
				continue;
			else if(arr[i]!=arr[j])
				continue;
			else
				counter++;
		}
		if(counter==0)
		{
			nare[k]=arr[i];
			k++;
		}
	}
	if(k==0)
		printf("There is No unique number!!!");
	else
		printunique(nare,(k-1));
}
void printunique(int nare[],int k)
{
	int i;
	printf("The Unique number is: {");
	for(i=0;i<k;i++)
		printf("%d,",nare[i]);
	printf("%d}",nare[i]);
}


