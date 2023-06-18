#include "stdio.h"
void main ()

{
	int x;
	int y=1;
	printf("Enter an integer : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	if (x<0)
	{
		printf("Error!!! Factorial of negative number doesm't exist ");
	}
	else if (x==0)
	{
		printf("Factorial=1") ;
	}
	else
	{
		for (int i=1 ; i<=x ; i++)
		{
			y=i*y;
		}
		printf("Factorial =%d",y);
	}

}
