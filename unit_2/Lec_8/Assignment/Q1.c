#include <stdio.h>
int main()
{
	int m=29;
	printf("Adress of m: 0x%x\n",&m);
	printf("Value of m: %d\n",m);
	int* ab=&m;
	printf("Adress in pointer ab: 0x%x\n",ab);
	printf("Content of what the pointer point to: %d\n",*ab);
	m=34;
	printf("Adress in pointer ab: 0x%x\n",ab);
	printf("Content of what the pointer point to: %d\n",*ab);
	*ab=7;
	printf("Adress of m: 0x%x\n",&m);
	printf("Value of m: %d\n",m);
	return 0;
}