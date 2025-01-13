#include "functions.h"
void main()
{
	printf("enter please file name");
	char* name = fileName();
	Exe5Q3(name);
	free(name);
}