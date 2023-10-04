#include<stdio.h>
#define pi 3.14
#define area(r) (pi*r*r)
int main()
{
	float r;
	printf("Enter tha radius:");
	scanf("%f",&r);
	printf("Area= %.2f",area(r));
	return 0;
}