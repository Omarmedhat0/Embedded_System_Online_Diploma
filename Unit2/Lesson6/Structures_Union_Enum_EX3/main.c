#include <stdio.h>
struct Scomplexnum{
	float real;
	float imag;
}result , num1 , num2 ;
struct Scomplexnum addcomplex (struct Scomplexnum num1, struct Scomplexnum num2)
{
	struct Scomplexnum sum;
	sum.real = num1.real + num2.real;
	sum.imag = num1.imag + num2.imag;
	return sum;
}
int main()
{

	printf("Enter information 1st number by entering real part then imag part respectively \n");
	fflush(stdout);fflush(stdin);
	scanf("%f%f",&num1.real,&num1.imag);
	printf("Enter information 2nd number by entering real part then imag part respectively \n");
	fflush(stdout);fflush(stdin);
	scanf("%f%f",&num2.real,&num2.imag);
	result=addcomplex(num1,num2);
	printf("sum=%0.2f+%0.2fi",result.real,result.imag);
	return 0;
}
