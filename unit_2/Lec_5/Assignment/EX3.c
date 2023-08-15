/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void rev(char arr[],int i);
int main()
{
	int i=1;
	char arr[50];
	printf("Please enter the scentence: ");
	fflush(stdin); fflush(stdout);
	gets(arr);
	rev(arr,i);

	return 0;
}
void rev(char arr[],int i)
{
	if(i<=strlen(arr))
	{
	printf("%c",arr[strlen(arr)-i]);
	i++;
	rev(arr,i);
	}
}

