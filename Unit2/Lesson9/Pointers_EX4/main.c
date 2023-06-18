#include <stdio.h>
int main()
{

	char arr[15];
	char revarr[15];
	char* parr  ;
	char* prevarr  ;
	parr=arr;
	prevarr=revarr;
	char i ;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&i);
	printf("Input %d number of elements in the array: \n",i);

	for ( char s =0 ; s<i ;s++)
	{
		printf("element - %d : ",s+1);
		fflush(stdout);fflush(stdin);
		scanf("%d",parr);
		parr++;
	}
	printf("\nExpected Output :\n ");

	printf("The elements of array in reverse order are : \n");

	for ( char s =0 ; s<i ;s++)
	{
		parr--;
		*prevarr=*parr;
		printf("element - %d : %d\n",i-s,*prevarr);
		prevarr++;
	}
	return 0;
}
