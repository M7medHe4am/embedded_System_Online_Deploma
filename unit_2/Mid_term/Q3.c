/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void add(int n1,int n2);
int main()
{
	int n1,n2;
	printf("Enter an 1st number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n1);
	printf("Enter an 2nd number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n2);
	add(n1,n2);
	return 0;
}
void add(int n1,int n2)
{
	int i,j,k=0,arr[50];
	for(i=n1;i<=n2;i++)
	{
		int counter=0;
		for(j=2;j<=(i/2);j++)
		{
			if(i%j==0)
				break;
			else
			{
				counter++;
				continue;
			}
		}
		if (counter==(i/2)-1)
		{
			arr[k]=i;
			k++;
		}
	}
	printf("The Prime numbers between(%d) and (%d) are: ",n1,n2);
	for(i=0;i<k;i++)
	{
		printf("%d\t",arr[i]);
	}
}

