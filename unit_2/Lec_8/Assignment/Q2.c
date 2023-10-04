#include <stdio.h>
int main()
{
	int i;
    char X[26];
	char *ptr=X;
	for(i=0;i<26;i++)
	{
		*ptr=i+'A';
		ptr++;
	}
	ptr=X;
	printf("The Alphabet are:\n");
	for(i=0;i<26;i++)
	{
		printf("%c  ",*ptr);
		ptr++;
	}
	return 0;
}