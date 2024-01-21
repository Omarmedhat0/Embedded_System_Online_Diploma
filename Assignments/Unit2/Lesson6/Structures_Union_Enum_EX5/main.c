#include <stdio.h>

#define Pi 3.14
#define Area(radius) ((Pi)*(radius)*(radius))
int main()
{
	int radius;
	float area;
	printf("Enter the radius: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&radius);
	area = Area(radius);
	printf("Area: %f ",area);
	return 0;
}
