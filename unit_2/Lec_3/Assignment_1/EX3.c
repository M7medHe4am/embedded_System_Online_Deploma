/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	int x=0,y=0;
	printf("Enter two integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	printf("Sum: %d",x+y);


	return 0;

}


