#include <stdio.h>

#include <stdio.h>
void main()
{
	int mat[50][50];
	int t_mat[50][50];
	int x , y , i , j ;
	printf("Enter rows and column of matrix: " );
	fflush(stdout);fflush(stdin);
	scanf("%d\n%d",&x,&y);
	for (i=0;i<x;i++)
	{
		for (j=0;j<y;j++)
		{
			printf("enter elements a%d%d :",(i+1),(j+1) );
			fflush(stdout);fflush(stdin);
			scanf("%d",&mat[i][j]);
		}
	}
	printf("Entered matrix \n");
	for (i=0;i<x;i++)
	{
		for (j=0;j<y;j++)
		{
			printf ("%d\t",mat[i][j]);
		}
		printf ("\n");
	}
	printf(" \nTranspose matrix \n");
	for (i=0;i<y;i++)
		{
			for (j=0;j<x;j++)
			{
				t_mat[i][j]=mat[j][i];
				printf ("%d\t",t_mat[i][j]);
			}
			printf ("\n");
		}
}


