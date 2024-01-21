#include "stdio.h"
void main ()

{
	int x;
	int y=0;
	printf("Enter an integer : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	for (int i=0 ; i<=x ; i++)
	{
		y=i+y;
	}
	printf("sum =%d",y);
}
