#include <stdio.h>
struct student
{
	char name[100];
	float marks;
};
int main()
{
	struct student num[10];
	printf("Enter information of students\n");
	for (int i=0 ; i<3 ; i++)
	{
		printf("\nFor roll number %d\n",i+1);
		printf("Enter Name ");
		fflush(stdout);fflush(stdin);
		scanf("%s",num[i].name);
		printf("Enter Marks ");
		fflush(stdout);fflush(stdin);
		scanf("%f",&num[i].marks);
	}
	printf("\nDisplaying information of students\n");
	for (int i=0 ; i<3 ; i++)
	{
		printf("\nInformation For roll number %d\n",i+1);
		printf("Name: %s\n",num[i].name);
		printf("Marks: %0.2f\n",num[i].marks);
	}
	return 0;
}
