#include <stdio.h>
struct SEmployee
{
	char *m_Name;
	int m_ID;
};
int main()
{
	struct SEmployee emp1={"Ahmed",1000},emp2={"Muhammad",1001},emp3={"Alex",1002}; 
	struct SEmployee *arr[]={&emp1,&emp2,&emp3};
	struct SEmployee (*(*ptr)[3])=&arr;
	printf("Employee Name: %s\n",(*(*ptr+2))->m_Name);
	printf("Employee ID: %d",(*(*ptr+2))->m_ID);
	return 0;
}