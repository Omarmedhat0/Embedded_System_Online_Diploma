#include <stdio.h>

#include <stdio.h>
void main()
{
	int x ;
	float z=0 ;
	printf("Enter the numbers of data: " );
	fflush(stdout);fflush(stdin);
	scanf("%d",&x);
	float y[100];
	for (int i=0 ; i<x ; i++)
	{
		printf("Enter the number: " );
		fflush(stdout);fflush(stdin);
		scanf("%f",&y[i]);
		z=z+y[i];
	}
	printf("Average = %f" , z/x );
}
