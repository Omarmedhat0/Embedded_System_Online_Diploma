#include "stdio.h"
void main ()

{
	char x;
	printf("Enter an character : ");
	fflush(stdin);fflush(stdout);
	scanf("%c",&x);
	if(('a'<=x && 'z'>= x) ||('A'<=x && 'Z'>= x) )
	{
		printf("%c is an alphabet",x);
	}
	else
	{
		printf("%c is not an alphabet",x);
	}
}
