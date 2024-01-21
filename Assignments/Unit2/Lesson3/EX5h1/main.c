#include "stdio.h"
void main ()
{
	char x ;
	printf("Enter a character:");
	fflush(stdin);fflush(stdout);
	scanf("%c",&x);
	fflush(stdin);fflush(stdout);
	printf("ASCII value of %c = %d",x ,x);
}
