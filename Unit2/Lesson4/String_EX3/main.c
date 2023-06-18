#include <stdio.h>
#include <string.h>
void main()
{
	char str[100];
	char r_str[100];
	int length , i;
	printf("Enter a string");
	fflush(stdout);fflush(stdin);
	gets(str);
	length=strlen(str);

	for (i=0 ; i<length;i++)
	{
		if (str[i]!=0)
		{
			r_str[i]=str[length-i-1];
		}
		else
		{
			break;
		}

	}
	r_str[i]=0;

	printf("Reverse string : %s",r_str);
}
