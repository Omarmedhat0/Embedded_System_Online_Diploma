#include <stdio.h>
int factorial (int num)
{
	if (num!=1)
	{
		return num*factorial(num-1) ;
	}
	else
	{
		return 1;
	}

}


void main()
{
	int num1 ;
	printf("Enter a positive integer\n");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num1 );
	printf("factorial %d ",factorial(num1));

}


