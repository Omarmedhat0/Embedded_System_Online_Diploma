#include "stdio.h"
void main ()

{
	char x;
	printf("Enter an alphabet : ");
	fflush(stdin);fflush(stdout);
	scanf("%c",&x);
	if('a'<=x && 'z'>= x)
	{
		printf("%c is a vowel",x);
	}
	else if('A'<=x && 'Z'>= x)
	{
		printf("%c is a consonant",x);
	}
}
