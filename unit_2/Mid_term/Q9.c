/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */

#include <stdio.h>
#include<string.h>
void prntstr(char str[],int i);
int main()
{
	char str[100];
	int len,i;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	len=strlen(str);
	for(i=len-1;i>=0;i--)
	{
		if(str[i]==' ')
			prntstr(str,i+1);
		else
			continue ;
	}
	prntstr(str,0);
	return 0;
}
void prntstr(char str[],int i)
{

	for(;str[i]!='\0'&&str[i]!=' ';i++)
		printf("%c",str[i]);
	printf(" ");

}

