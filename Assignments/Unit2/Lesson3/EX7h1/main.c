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
	a=a+b;b=a-b;a=a-b;
	printf("After swapping, value of a =%f \nAfter swapping, value of b = %f ", a,b );
}
//comment
