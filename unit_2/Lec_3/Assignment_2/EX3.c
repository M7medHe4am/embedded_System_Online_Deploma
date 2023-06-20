/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	float x,y,z;

	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&x,&y,&z);
	if(x>y && x>z)
		printf ("Largest number = %.3f",x);
	else if(y>x && y>z)
		printf ("Largest number = %.3f",y);
	else
		printf ("Largest number = %.3f",z);

	return 0;


}


