/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void input(int arr[],int s);
int search(int arr[],int n,int s);
int main()
{
	int arr[100],s,n;
	printf("Enter array size: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&s);
	printf("Enter the array: ");
	fflush(stdin);fflush(stdout);
	input(arr,s);
	printf("The number is: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	printf("the result is : %d",search(arr,n,s));
	return 0;
}
void input(int arr[],int s)
{
	int i;
	for(i=0;i<s;i++)
		scanf("%d",&arr[i]);
}
int search(int arr[],int n,int s)
{
	int i,save;
	for(i=0;i<s;i++)
	{
		if(arr[i]==n)
			save=i;
		else
			continue;
	}
	return save;
}
