#include <stdio.h>
void main()
{
	char str[100];
	char character;
	int frequency=0;
	printf("Enter a string");
	fflush(stdout);fflush(stdin);
	gets(str);
	printf("Enter a character to find frequency :");
	fflush(stdout);fflush(stdin);
	scanf("%c",&character);
	for (int i =0 ; i<sizeof(str);i++)
	{
		if (str[i]==character)
		{
			frequency++;
		}
		else
		{
			continue;
		}
	}
	printf("Frequency of %c : %d", character , frequency);
}
