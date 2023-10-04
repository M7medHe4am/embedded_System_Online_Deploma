/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
void sum(int r,int n);
int main()
{
	int r,n;
	r=1;
	n=100;
	sum(r,n);
	return 0;
}
void sum(int r,int n)
{
	if(n>=r)
		printf("The sum is: %d",((n-r+1)*(n+r))/2);
	else
		printf("ERORR!!!\nFirst Enter the lowest value");
}




