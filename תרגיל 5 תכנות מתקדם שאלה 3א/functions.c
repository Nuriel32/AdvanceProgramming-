#include "functions.h"

/*
* This is a void function that create A file with indexs
* @parm char* filename - > the name of the file .
*/
void Exe5Q3(char* fileName)
{
	FILE* file1, * file2;
	short int n, i;
	LINEDATA* arr;
	char add[] = ".ind";
	char* _fileName;
	int len = strlen(fileName) + 5;
	_fileName = (char*)malloc(len * sizeof(char));
	checkMemoryAllocation(_fileName);
	_fileName[0] = '\0';

	file1 = fopen(fileName, "rb");
	isOpen(file1);
	fread(&n, sizeof(short int), 1, file1);
	arr = (LINEDATA*)malloc(n * sizeof(LINEDATA));
	checkMemoryAllocation(arr);

	for (i = 0; i < n; i++)
	{
		arr[i] = getInfo(file1);
	}

	mergeSort(arr, n);
	strcat(_fileName, fileName);
	strcat(_fileName, add);
	file2 = fopen(_fileName, "wb");
	isOpen(file2);

	for (i = 0; i < n; i++)
	{
		fwrite(&arr[i]._numofline, sizeof(int), 1, file2);
		printf("%d ", arr[i]._numofline);
	}

	free(arr);
	fclose(file1);
	fclose(file2);
}
/*
*
*/
LINEDATA getInfo(FILE* f)
{
	LINEDATA temp;
	short int i;
	temp._numofline = ftell(f);
	fread(&i, sizeof(short int), 1, f);
	fseek(f, i * sizeof(char), SEEK_CUR);
	fread(&temp._average, sizeof(int), 1, f);
	return temp;

}
/*
* Tradional merge sort...
*/
void mergeSort(LINEDATA* infoArr, short int n)
{
	LINEDATA* tempArr = NULL;
	if (n <= 1)
		return;

	mergeSort(infoArr, n / 2);
	mergeSort(infoArr + n / 2, n - n / 2);
	tempArr = merge(infoArr, n / 2, infoArr + n / 2, n - n / 2);

	if (tempArr)
	{
		copyArr(infoArr, tempArr, n);
		free(tempArr);
	}
	else
	{
		printf("Memory allocation failure!!!\n");
		exit(1);
	}
}

LINEDATA* merge(LINEDATA a1[], short int size1, LINEDATA a2[], short int size2)
{
	int ind1, ind2, resInd = 0;
	LINEDATA* res = (LINEDATA*)malloc((size1 + size2) * sizeof(LINEDATA));
	checkMemoryAllocation(res);
	if (res)
	{
		ind1 = ind2 = resInd = 0;

		while ((ind1 < size1) && (ind2 < size2))
		{

			if (a1[ind1]._average <= a2[ind2]._average)
			{
				res[resInd] = a1[ind1];
				ind1++;
			}
			else
			{
				res[resInd] = a2[ind2];
				ind2++;
			}
			resInd++;
		}

		while (ind1 < size1)
		{
			res[resInd] = a1[ind1];
			ind1++;
			resInd++;
		}
		while (ind2 < size2)
		{
			res[resInd] = a2[ind2];
			ind2++;
			resInd++;
		}
	}
	return res;
}
/*
* This is  avoid function that copy one arr to the other one.
* @parm LINEDATA dest -> the arr we want to get a acopy
* @parm LINEDATA*src -> the source we want to get copied.
* @short int size - the size of the arr.
*/
void copyArr(LINEDATA* dest, LINEDATA* src, short int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}
/*
* Check if the file opened well.
* @parm FILE* f -> c
*/
void isOpen(FILE* f)
{
	if (f == NULL)
	{
		printf("Couldnt open the file!\n");
		return;
	}
}
/*
* check if the allocation has done well
* @parm void* ptr -> any kind of pointer.
*/
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		puts("a memory allocation has occured");
		exit(1);
	}
}
char* fileName()
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