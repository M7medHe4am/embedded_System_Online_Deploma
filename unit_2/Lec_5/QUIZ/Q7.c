/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int fun(int n);
int main()
{
	int n;
	printf("Enter a number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	printf("%d",fun(n));
	return 0;
}
int fun(int n)
{
	if(n%3==0)
		return 0;
	else
		return 1;
}
