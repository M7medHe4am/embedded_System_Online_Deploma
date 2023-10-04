/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
#include<string.h>
void rev(char n[],int x);
int main()
{
	int x;
	char n[100];
	printf("Please enter an integer number: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",n);
	x=strlen(n);
	rev(n,x);
	return 0;
}
void rev(char n[],int x)
{
	int i;
	for(i=0;i<x;i++)
		n[i]-='0';
	printf("the reverse is: ");
	for(i=x-1;i>=0;i--)
		printf("%d",n[i]);
}

