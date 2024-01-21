#include "stdio.h"
void main ()
{
	int x;
	printf("Enter a integer:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	fflush(stdin);fflush(stdout);
	printf("You entered: %d",x);
}
