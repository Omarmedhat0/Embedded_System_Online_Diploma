#include <stdio.h>
void main()
{
	char str[100];
	int length=0;
	printf("Enter a string");
	fflush(stdout);fflush(stdin);
	gets(str);
	for (int i=0 ; i<sizeof(str);i++)
	{
		if (str[i]!=0)
		{
			length++;
		}
		else
		{
			break;
		}
	}
	printf("Length of string : %d",length);
}
