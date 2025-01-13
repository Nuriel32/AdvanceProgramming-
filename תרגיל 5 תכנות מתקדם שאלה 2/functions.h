#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// typedef declatation:
typedef struct employee
{
	int name_length;
	char* name;
	float salary;
}Employee;

Employee** buildEmployeeArrayFromFile(char* fileName);
unsigned int updateEmployeArray(Employee** arr, char* fileName);
void EmployMerge(Employee** pointers, unsigned int size);
void merge(Employee** pointers1, unsigned int size1, Employee** pointers2, unsigned int size2, Employee** temp);
void saveArrayToFile(Employee** arr, unsigned int arrSize, char* fileName);
void checkMemoryAllocation(void* ptr);
void Exe5Q2(char* fname1, char* fname2);
void freeEmployArr(Employee** pointers1, unsigned int n);
char* CreateName();