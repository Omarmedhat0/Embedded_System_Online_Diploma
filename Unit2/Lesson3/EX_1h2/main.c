#include "stdio.h"
void main ()

{
	int x;
	printf("Enter an integer you want to check : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	if(x%2!=0)
	{
		printf("%d is odd",x);
	}
	else
	{
		printf("%d is even",x);
	}
}

