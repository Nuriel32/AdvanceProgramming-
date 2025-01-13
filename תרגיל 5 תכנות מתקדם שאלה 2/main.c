#include "functions.h"
void main()
{
	printf("enter name of first  file\n");
	char* filename = CreateName();
	printf("enter name of second file");
	char* filename2 = CreateName();
	
	Exe5Q2(filename,filename2);
}

