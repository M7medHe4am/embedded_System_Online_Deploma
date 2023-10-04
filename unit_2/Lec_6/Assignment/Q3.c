
#include<stdio.h>
struct SComplex scan(char s[]);
struct SComplex Add(struct SComplex X, struct SComplex Y);
struct SComplex
{
	float m_R;
	float m_I;
};

int main()
{
	struct SComplex X,Y,SUM;
	X=scan("1st");
	Y=scan("2nd");
	SUM=Add(X,Y);
	printf("Sum = %.1f+%.1fi",SUM.m_R,SUM.m_I);
	return 0;
}

struct SComplex scan(char s[])
{
	struct SComplex X;
	char c;
	printf("For the %s complex number:\n",s);
	printf("Enter real and IMG (REAL+IMG):");
	scanf("%f",&X.m_R);
	scanf("%c",&c);
	scanf("%f",&X.m_I);
	return X;
}

struct SComplex Add(struct SComplex X, struct SComplex Y )
{
	struct SComplex SUM;
	SUM.m_R=X.m_R+Y.m_R;
	SUM.m_I=X.m_I+Y.m_I;
	return SUM;
}

