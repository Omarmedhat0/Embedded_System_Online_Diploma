#include "stdio.h"
void main ()

{
	float a,b,c ;
	printf("Enter value of a:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&a);
	fflush(stdin);fflush(stdout);
	printf("Enter value of b:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&b);
	c=a;a=b;b=c;
	printf("After swapping, value of a =%f \nAfter swapping, value of b = %f ", a,b );
}
