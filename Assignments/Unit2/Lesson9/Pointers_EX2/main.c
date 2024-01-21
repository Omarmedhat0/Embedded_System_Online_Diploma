#include <stdio.h>
int main()
{
	char alpha[26];
	char* ab  ;
	ab=alpha;
	for (int i=0;i<sizeof(alpha);i++)
	{
		*ab='A'+i;
		printf("%c ",*ab);
		ab++;
	}
	return 0;
}
