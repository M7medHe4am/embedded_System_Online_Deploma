/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void input(int arr[],int s);
void output(int arr[],int s);
void reverse(int arr[],int s);
int main()
{
	int s,arr[100];
	printf("Enter the array size: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s);
	printf("Enter the array elements: ");
	fflush(stdin); fflush(stdout);
	input(arr,s);
	printf("the array before reverse: ");
	output(arr,s);
	printf("\nthe array after reverse: ");
	reverse(arr,s);
	return 0;
}
void input(int arr[],int s)
{
	int i;
	for(i=0;i<s;i++)
	scanf("%d",&arr[i]);
}
void reverse(int arr[],int s)
{
	int i;
	for(i=s-1;i>=0;i--)
	printf("%d\t",arr[i]);
}
void output(int arr[],int s)
{
	int i;
	for(i=0;i<s;i++)
	printf("%d\t",arr[i]);
}
