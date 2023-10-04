#include <stdio.h>
#include<string.h>
int main()
{
	char str[50];
	char*ptr=NULL;
	int n,i;
	printf("Enter A String: ");
	gets(str);
	n=strlen(str);
	// printf("Enter String lenght: ");
	// scanf("%d",&n);
	ptr=&str[n-1];
	for(i=n-1;i>=0;i--)
	{
		printf("%c",*ptr);
		ptr--;
	}
	return 0;
}