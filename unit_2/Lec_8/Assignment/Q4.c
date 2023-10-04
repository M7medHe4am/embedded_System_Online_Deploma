#include <stdio.h>
#include<string.h>
int main()
{
	int n,i;
	int arr[15];
	int *ptr=arr;
	printf("Enter the number of elemnts to be entered in the array(MAX=15):");
	scanf("%d",&n);
	printf("Input %d number of elements in the array : \n",n);
	for(i=0;i<n;i++)
	{
		printf("element (%d): ",i+1);
		scanf("%d",ptr);
		ptr++;
	}
	printf("The elements of the array in reverse order are: \n");
	for(i=0;i<n;i++)
	{
		ptr--;
		printf("element(%d): ",n-i);
		printf("%d\n",*ptr);
	}
	return 0;
}