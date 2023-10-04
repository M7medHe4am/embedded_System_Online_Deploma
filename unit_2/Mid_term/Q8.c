/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void input(int n);
void reverse(int arr[],int n);
int main()
{
	int n;
	printf("Enter the number of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	input(n);
	return 0;
}

void input(int n)
{
	int i;
	int arr[n];
	printf("Enter the array elements: ");
	fflush(stdin); fflush(stdout);
	for (i=0;i<n;i++)
		scanf("%d",&arr[i]);
	reverse(arr,n);

}
void reverse(int arr[],int n)
{
	int i;
	printf("The reversed array is: {");
	for(i=n-1;i>0;i--)
		printf("%d,",arr[i]);
	printf("%d}.",arr[i]);
}




