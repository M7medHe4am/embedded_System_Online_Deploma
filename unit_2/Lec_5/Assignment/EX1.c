/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
int primno(int num);
int main()
{
	int x,y,i;
	printf("Enter two intervals: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	scanf("%d",&y);
	printf("The prime numbers between %d and %d are :  ",x,y);
	for(i=x;i<y;i++)
	{
		if(primno(i+1)==1)
			printf("%d\t",i+1);
		else
			continue;
	}
	return 0;
}
int primno(int num)
{
	int i,counter=0,flag=0;
	for(i=2;i<num;i++)
	{
		if(num%i==0)
			continue;
		else
			counter++;
	}
	if(counter==num-2)
		flag=1;
	return flag;

}

