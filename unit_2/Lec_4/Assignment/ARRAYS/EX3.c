/*
 * main.c
 *
 *  Created on: Jun 19, 2023
 *      Author: m7med
 */
/* A matrix and its transpose*/
#include "stdio.h"
int main()
{
	int x,y,i,j;
	float arr[50][50],trns[50][50];
	/* accepting No. of rows and columns from user*/
	printf("Enter the rows and column of matrix:\n");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x,&y);
	/*checking if the entered values are true
	 * (equal for matrix to be transposed)*/
	if(x!=y)
		printf("Error!!! The matrix should be square.");
	else
	{
		/*accepting the matrix values from the user*/
		printf("Enter the elements of the matrix.\n");
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
			{
				printf("Enter element a%d%d:",i+1,j+1);
				fflush(stdin); fflush(stdout);
				scanf("%f",&arr[i][j]);
			}
		/*displaying the entered matrix
		 *and making the transpose operation at the same time*/
		printf("Entered matrix:\n");
		for (i=0;i<x;i++)
		{
			for(j=0;j<y;j++)
			{
				printf("%.2f\t",arr[i][j]);
				trns[i][j]=arr[j][i];
			}
			printf("\n");
		}
		/*displaying the entered matrix*/
		printf("Transpose of the matrix:\n");
		for (i=0;i<y;i++)
		{
			for(j=0;j<x;j++)
			{
				printf("%.2f\t",trns[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}
