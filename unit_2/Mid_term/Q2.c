/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
#include<math.h>
float root(int n);
int main()
{
	int n;
	printf("Enter an integer number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	printf("The Square root of (%d) is: %.3f",n,root(n));
	return 0;
}
float root(int n)
{
	return sqrt(n);

}
