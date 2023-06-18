#include "stdio.h"
void main ()

{
	int z;
	printf("Enter an integer : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&z);
	for (int i=0;i<z;i++)
	{
		for(int y=i;y<z;y++)
		{
			printf("%d ",y);
		}
		printf("\n");
	}
}

