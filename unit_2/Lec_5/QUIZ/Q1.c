/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
#include <string.h>
int main()
{
	char arr1[50],arr2[]="MuhammadHesham";
	int x;
	printf("Enter the username: ");
	fflush(stdin); fflush(stdout);
	gets(arr1);
	x=stricmp(arr1,arr2);
	if(x==0)
		printf("Identical.");
	else
		printf("Not Identical!");
	return 0;
}





