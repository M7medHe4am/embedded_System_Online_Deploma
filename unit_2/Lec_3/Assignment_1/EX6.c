/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	float a,b,temp;

	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&a);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&b);
	temp=b;
	b=a;
	a=temp;
	printf ("\r\nAfter swapping , value of a = %f",a);
	printf ("\nAfter swapping , value of b = %f",b);

	return 0;

}


