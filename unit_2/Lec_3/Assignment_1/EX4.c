/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	float x=0,y=0;
	printf("Enter two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&x,&y);
	printf("product: %f",x*y);


	return 0;

}


