#include <stdio.h>
int main()
{
	char str[50];
	char revstr[50];
	char* pstr  ;
	char* prevstr  ;
	pstr=str;
	prevstr=revstr;
	printf("Enter a string ");
	fflush(stdout);fflush(stdin);
	scanf("%s",str);
	for ( int i =0 ; str[i]!='\0' ;i++)
	{
		pstr++;
	}
	for ( int i =0 ; str[i]!='\0' ;i++)
	{
		pstr--;
		*prevstr=*pstr;
		prevstr++;
	}
	*prevstr ='\0';
	printf("Reverse of the string is : %s",revstr);
	return 0;
}
