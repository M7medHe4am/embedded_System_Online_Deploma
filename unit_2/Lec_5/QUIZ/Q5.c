/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int main()
{
	int n,c,new_n;
	printf("Enter a number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	printf("Enter a bit to clear: ");
		fflush(stdin);fflush(stdout);
		scanf("%d",&c);
		new_n=n&(~(1<<c));
		printf("The number before clear is: %d",n);
		printf("\nThe number after clear is: %d",new_n);
		return 0;
}
