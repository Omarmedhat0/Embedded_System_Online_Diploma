#include <stdio.h>
void main()
{
	int a[50];
	int num ;
	int i , element , location;
	printf("Enter no of elements: " );
	fflush(stdout);fflush(stdin);
	scanf("%d", &num);
	for (i=0;i<num;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Enter the element to be inserted " );
	fflush(stdout);fflush(stdin);
	scanf("%d", &element);
	fflush(stdout);fflush(stdin);
	printf("Enter the Location " );
	fflush(stdout);fflush(stdin);
	scanf("%d", &location);
	for (i=num;i>0;i--)
	{
		if (i!=location)
		{
			a[i]=a[i-1];
		}
		else if (i==location)
		{
			a[i]=a[i-1];
			a[i-1]=element;
			break;
		}
	}
	for (i=0;i<num+1;i++)
	{
		printf ("%d\t",a[i]);
	}
}

