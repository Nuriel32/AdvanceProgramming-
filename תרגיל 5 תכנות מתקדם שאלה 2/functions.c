#include  "functions.h"
Employee** buildEmployeeArrayFromFile(char* fileName)
{
	FILE* fp;
	unsigned int physSize = 1;
	unsigned int logSize = 0;
	int fileSize;
	Employee** arr;
	fp = fopen(fileName, "rb");
	checkMemoryAllocation(fp);
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	arr = (Employee**)malloc(sizeof(Employee));
	checkMemoryAllocation(arr);
	while (ftell(fp) < fileSize)
	{
	size:
		if (logSize == physSize)
		{
			physSize *= 2;
			arr = (Employee**)realloc(arr,
				physSize * sizeof(Employee*));
			checkMemoryAllocation(arr);
		}
		arr[logSize] = (Employee*)malloc(sizeof(Employee));
		checkMemoryAllocation(arr[logSize]);
		fread(&arr[logSize]->name_length, sizeof(int), 1,
			fp);
		arr[logSize]->name = (char*)malloc((arr[logSize]->
			name_length + 1) * sizeof(char));
		checkMemoryAllocation(arr[logSize]->name);
		fread(arr[logSize]->name, sizeof(char),
			arr[logSize]->name_length, fp);
		arr[logSize]->name[arr[logSize]->name_length] = '\0';
		fread(&arr[logSize]->salary, sizeof(float), 1, fp);
		logSize++;
	}
	arr = (Employee**)realloc(arr, logSize * sizeof(Employee));
	checkMemoryAllocation(arr);
	fclose(fp);
	return arr;
}
unsigned int updateEmployeArray(Employee** arr, char* fileName)
{

	FILE* fp;
	int fileSize;
	unsigned int i = 0;
	float cash;
	fp = fopen(fileName, "rb");
	checkMemoryAllocation(fp);
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	while (ftell(fp) < fileSize)
	{
		fread(&cash, sizeof(float), 1, fp);
		arr[i]->salary += cash;
		i++;
	}
	fclose(fp);
	return i;
}
void EmployMerge(Employee** pointers, unsigned int size)
{
	Employee** temp;
	unsigned int i;
	if (size > 1)
	{
		EmployMerge(pointers, size / 2);
		EmployMerge(pointers + (size / 2), size - (size / 2));
		temp = (Employee**)malloc(size * sizeof(Employee*));
		checkMemoryAllocation(temp);
		merge(pointers, size / 2, pointers + (size / 2),
			size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		free(temp);
	}
}
void merge(Employee** pointers1, unsigned int size1, Employee** pointers2, unsigned int size2, Employee** temp)
{

	unsigned int i1 = 0, i2 = 0, tempIndex = 0;
	while ((i1 < size1) && (i2 < size2))
	{
		if ((pointers1[i1]->salary) > (pointers2[i2]->salary))
		{
			temp[tempIndex] = pointers1[i1];
			i1++;
		}
		else
		{
			temp[tempIndex] = pointers2[i2];
			i2++;
		}
		tempIndex++;
	}
	while (i1 < size1)
	{
		temp[tempIndex] = pointers1[i1];
		i1++;
		tempIndex++;
	}
	while (i2 < size2)
	{
		temp[tempIndex] = pointers2[i2];
		i2++;
		tempIndex++;
	}
}
void saveArrayToFile(Employee** arr, unsigned int arrSize, char* fileName)
{
	FILE* fp;
	unsigned int i;
	fp = fopen(fileName, "wb");
	checkMemoryAllocation(fp);
	for (i = 0; i < arrSize; i++)
	{
		fwrite(&arr[i]->name_length, sizeof(int), 1, fp);
		fwrite(arr[i]->name, sizeof(char), arr[i]->
			name_length, fp);
		fwrite(&arr[i]->salary, sizeof(float), 1, fp);
	}
	fclose(fp);
}
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation error");
		exit(1);
	}
}
void Exe5Q2(char* fname1, char* fname2)
{
	Employee** array;
	unsigned int arrSize;
	array = buildEmployeeArrayFromFile(fname1);
	arrSize = updateEmployeArray(array, fname2);
	EmployMerge(array, arrSize);
	saveArrayToFile(array, arrSize, fname1);
	freeEmployArr(array, arrSize);
}
void freeEmployArr(Employee** pointers1, unsigned int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		free(pointers1[i]);
	}
	free(pointers1);
}

char* CreateName()
{
char ch;
char* string;
int length = 10;
int i = 0;

string = (char*)malloc(length + 1);
checkMemoryAllocation(string);
ch = getchar();
while (ch != '\n')
{
	if (i == length)
	{
		length *= 2;
		string = (char*)realloc(string, length + 1);
		checkMemoryAllocation(string);
	}
	string[i] = ch;
	i++;
	ch = getchar();
}
string[i] = '\0';
string = (char*)realloc(string, i + 1);
checkMemoryAllocation(string);
return string;
}