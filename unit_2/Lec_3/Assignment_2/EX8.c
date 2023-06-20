/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include<stdio.h>
int main ()
{
	char op;
	float x,y;
	printf("Enter operator (+,-,*,/):- ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&op);
	printf("Enter two operands:- ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&x,&y);
	switch (op)
	{
	case '+':
		printf("%.3f + %.3f = %.3f",x,y,x+y);
		break;
	case '-':
		printf("%.3f - %.3f = %.3f",x,y,x-y);
		break;
	case '*':
		printf("%.3f * %.3f = %.3f",x,y,x*y);
		break;
	case '/':
		printf("%.3f / %.3f = %.3f",x,y,x/y);
		break;
	default :
		printf("ERROR!!!Operand isn't correct");
	}
	return 0;

}


