#include <stdio.h>
int check_prime (int num)
{
	int flag =0 ;
	if ((num==2)||(num==3))
	{
		flag =1 ;
	}
	else
	{
		for (int i=2 ; (i <=(num/2)) ;i++ )
			{
				if (num%i==0)
				{
					flag=0;
					break;
				}
				else
				{
					flag =1;
				}
			}
	}
		return flag ;
}
void main()
{
	int num1 , num2;
	printf("Enter the two numbers(intervals)\n");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&num1 , &num2);
	printf("prime numbers between %d and %d are ", num1 , num2);
	for (int i = num1+1 ;i<num2;i++)
	{
		if (check_prime(i)==1)
		{
			printf("%d ",i);
		}
	}
}


