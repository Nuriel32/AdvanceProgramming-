#include "functions.h"
void main()
{
	printf("enter file name");
	char* name = createName();
	printf("enter please number");
	 unsigned int n;
	scanf("%d", &n);
	Exe5Q1(name, n);
	free(name);
}