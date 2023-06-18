#include <stdio.h>
struct sinfo{
	char name[100];
	int roll;
	float marks;
};
int main()
{
	struct sinfo s;
	printf("Enter information of students: \n\n");
	printf("Enter student name: \n");
	fflush(stdout);fflush(stdin);
	scanf("%s",s.name);
	printf("Enter student role: \n");
	fflush(stdout);fflush(stdin);
	scanf("%d",&s.roll);
	printf("Enter student marks \n");
	fflush(stdout);fflush(stdin);
	scanf("%f",&s.marks);
	printf("\nDisplaying Information:\n");
	printf("Name: %s \n",s.name);
	printf("Role: %d \n",s.roll);
	printf("Marks: %0.2f \n",s.marks);
	return 0;

}
