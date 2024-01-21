#include <stdio.h>
void main()
{
	int a[50];
	int num ;
	int i , element ;
	printf("Enter no of elements: " );
	fflush(stdout);fflush(stdin);
	scanf("%d", &num);
	for (i=0;i<num;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Enter the element to be searched " );
	fflush(stdout);fflush(stdin);
	scanf("%d", &element);
	fflush(stdout);fflush(stdin);
	for (i=0;i<num;i++)
	{
		if (a[i]==element)
		{
			printf("Number fount at Location = %d", i+1 );
			break;
		}
		else
		{
			continue;

		}
	}
}

