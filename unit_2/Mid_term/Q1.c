/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int add(char arr[]);
int main()
{
	char arr[100];
	printf("Enter number: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&arr);
	printf("The sum of digits is: %d",add(arr));
	return 0;
}
int add(char arr[])
{
	int i,sum=0;
	for(i=0;i<strlen(arr);i++)
		arr[i]-='0';
	for(i=0;i<strlen(arr);i++)
		sum+=arr[i];
	return sum;
}
