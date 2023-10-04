
#include <stdio.h>
struct SInfo{
	char m_Name[50];
	int m_Roll;
	float m_Marks;
};

int main ()
{
	struct SInfo X;
	printf("Enter Your name: ");
	gets(X.m_Name);
	printf("Enter the roll: ");
	scanf("%d",&X.m_Roll);
	printf("Enter the mark");
	scanf("%f",&X.m_Marks);
	printf("Your name is: %s\r\n",X.m_Name);
	printf("YOur Roll is: %d\r\n",X.m_Roll);
	printf("The Mark is: %.3f\r\n",X.m_Marks);
	return 0;
}