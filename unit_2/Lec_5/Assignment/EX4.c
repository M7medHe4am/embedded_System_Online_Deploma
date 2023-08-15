/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
float func(float x,float y);
int main()
{
	float x , y ;
	printf("Enter the base: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x);
	printf("Enter the power: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&y);
	printf("%.2f ^ %.2f = %.2f",x,y,func(x,y));
	return 0;
}
float func(float x,float y)
{
	if(y>0)
	return x*func(x,y-1);
	else
		return 1;

}


