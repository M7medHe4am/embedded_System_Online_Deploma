#include <stdio.h>
#include <string.h>
struct SStudent scan(int count);
void prnt(struct SStudent info);
struct SStudent
{
	char m_Name[100];
	int m_Roll;
	float m_Marks;
};
int main()
{
	struct SStudent X[10];
	int count =0,i;
	char c;
	printf("Enter Information of students.\n");
	do
	{
		X[count]=scan(count);
		printf("If you want to continue press (y).");
		fflush(stdin);fflush(stdout);
		scanf("%c",&c);
		count++;
	}while( count<10 && c=='y');

	printf("Displaying information of students.\n");
	for(i=0;i<count;i++)
	{
		prnt(X[i]);
	}
	return 0;
}

struct SStudent scan(int count)
{
	struct SStudent X;
	printf("For Roll number %d.\n",++count);
	X.m_Roll=count;
	printf("Enter Name: ");
	fflush(stdin);fflush(stdout);
	gets(X.m_Name);
	printf("Enter Marks:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&X.m_Marks);
	return X;

}
void prnt(struct SStudent info)
{
	printf("Information for roll %d\n",info.m_Roll);
	printf("Name: %s\n",info.m_Name);
	printf("Marks: %.2f\n",info.m_Marks);
}
