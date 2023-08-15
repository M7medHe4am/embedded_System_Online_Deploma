/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
/*
 * defining the 3 arrays
 * prototypes of the i/o ,swap functions
 * */
int arr1[50],arr2[50],arr3[50];
void input(int arr[],int s);
void output(int arr[],int s);
void swap(int s1,int s2);
int main()
{
	int s1,s2;
	/*obtaining the sizes of the arrays from user*/
	printf("Enter the size of 1st array (max=50): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s1);
	printf("Enter the size of 2nd array (max=50): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s2);
	/*obtaining 1st array from user*/
	printf("Enter the 1st array elements: ");
	input(arr1,s1);
	/*obtaining 2nd array from user*/
	printf("Enter the 2nd array elements: ");
	input(arr2,s2);
	/* printing the 1st array before swap*/
	printf("the 1st array before swap is: ");
	output(arr1,s1);
	/* printing the 2nd array before swap*/
	printf("\nthe 2nd array before swap is: ");
	output(arr2,s2);
	/* Swapping function*/
	swap(s1,s2);
	/* printing the 1st array after swap*/
	printf("\nthe 1st array after swap is: ");
	output(arr1,s2);
	/* printing the 2nd array after swap*/
	printf("\nthe 2nd array after swap is: ");
	output(arr2,s1);
	return 0;
}
void input(int arr[],int s)
{
	int i;
	fflush(stdin); fflush(stdout);
	for(i=0;i<s;i++)
		scanf("%d",&arr[i]);
}
void swap(int s1,int s2)
{
	int i;
	for (i=0;i<(s1>s2?s1:s2);i++)
	{
		arr3[i]=arr2[i];
		arr2[i]=arr1[i];
		arr1[i]=arr3[i];
	}

}

void output(int arr[],int s)
{
	int i;
	for(i=0;i<s;i++)
		printf("%d\t",arr[i]);
}


