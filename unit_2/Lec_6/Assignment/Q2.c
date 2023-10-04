
#include <stdio.h>
#include <string.h>
struct SDis info(char s[]);
struct SDis Add(struct SDis X,struct SDis Y);
struct SDis{
	float feet;
	float inche;
};

int main ()
{
	struct SDis X,Y,SUM;
	X=info("1st");
	Y=info("2nd");
	SUM=Add(X,Y);
	printf("Sum of Distances = %0.f'-%.1f\" ",SUM.feet,SUM.inche);
	return 0;
}
struct SDis info(char s[])
{
	struct SDis X;
	printf("Enter The information of the (%s) distance.",s);
	printf("\nEnter Feet: ");
	scanf("%f",&X.feet);
	printf("Enter inches: ");
	scanf("%f",&X.inche);
	return X;
}
struct SDis Add(struct SDis X,struct SDis Y)
{
	struct SDis SUM;
	SUM.feet=X.feet+Y.feet;
	SUM.inche=X.inche+Y.inche;
	for(;SUM.inche>=12;SUM.inche-=12)
		SUM.feet++;
	return SUM;
}

