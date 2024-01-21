#include <stdio.h>
struct SDistance{
	float feet;
	float inch;
}dis1 , dis2 ;
int main()
{

	printf("Enter information 1st distance\n");
	printf("Enter feet: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&dis1.feet);
	printf("Enter inch: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&dis1.inch);
	printf("\nEnter information 2nd distance\n");
	printf("Enter feet: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&dis2.feet);
	printf("Enter inch: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&dis2.inch);
	printf("Sum of distances = %f\'-%f\"\n",(dis1.feet+dis2.feet),(dis1.inch+dis2.inch));
	return 0;

}
