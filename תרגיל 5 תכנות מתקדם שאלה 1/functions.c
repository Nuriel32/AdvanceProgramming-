#include "functions.h"
void Exe5Q1(char* fname, unsigned int x)
{
	int i;
	unsigned int  size = x;
	char** strarr = (char**)malloc(sizeof(char*) * (size));
	checkMemoryAllocation(strarr);
	FILE* f = fopen(fname, "rb");
	isOpen(f);
	createSTR(strarr, f, size);
	char* filename = setFileName(fname);
	fclose(f);
	createFile(strarr, size, filename);
	lexicoMerge(strarr, size);
	freeSTRarr(strarr, size);
}
/*
*This is a void function that set the STR array.
*/
void  createSTR(char** des, FILE* src, int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		des[i] = strFromFile(src);
	}
}
/*
* This is a void function that checks if the file has opened .
*/
void isOpen(FILE* f)
{
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit;
	}
}
/*
* Check if if the character is small.
*/
bool isSmallCharacter(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	return false;
}
/*
* get input from File and set it to string.
*/
char* strFromFile(FILE* f)
{

	int size;
	int i;
	char ch;
	int arrindex = 0;
	fread(&size, sizeof(int), 1, f);
	char* str = (char*)malloc(sizeof(char) * size + 1);
	for (i = 0; i < size; i++)
	{
		fread(&ch, sizeof(char), 1, f);
		if (isSmallCharacter(ch))
		{
			str[arrindex] = ch;
			arrindex++;
		}
	}
	str[arrindex] = '\0';
	str = (char*)realloc(str, size + 2 - arrindex);
	return str;
}
/*
* set a file name.
*/
char* setFileName(char* name)
{
	char txt[] = ".txt";
	char* point = '.';
	char* newname = (char*)malloc(strlen(name) + strlen(txt));
	checkMemoryAllocation(newname);
	strcpy(newname, name);
	strcat(newname, txt);
}
/*
* Create a file name.
*/
void createFile(char* str[], int size, char* filename)
{
	FILE* file;
	int i;
	file = fopen(filename, "wt");
	isOpen(file);
	for (i = 0; i < size; i++)
	{
		fprintf(file, "%s\n", str[i]);
	}
	fclose(file);
}
/*
* check if the memory allocated well
*/
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}
}
/*
* tradinional merge sort..
*/
void merge(char** arr1, int size1, char** arr2, int size2, char** res)
{
	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2)
	{
		if (*(arr1[i]) < *(arr2[j]))
		{
			res[k++] = arr1[i++];
		}
		else
		{
			res[k++] = arr2[j++];
		}
	}

	while (i < size1)
	{
		res[k++] = arr1[i++];
	}

	while (j < size2)
	{
		res[k++] = arr2[j++];
	}
}
/*
* tradinional merge sort..
*/
void lexicoMerge(char** strarr, int size)
{
	char** temp;
	int i;

	if (size == 1)
		return;
	else
	{
		lexicoMerge(strarr, size / 2);
		lexicoMerge(strarr + size / 2, size - size / 2);
		temp = (char**)malloc(sizeof(char*) * size);
		checkMemoryAllocation(temp);
		merge(strarr, size / 2, strarr + size / 2, size - size / 2, temp);

		for (i = 0; i < size; i++)
		{
			strarr[i] = temp[i];
		}

		free(temp);
	}
}

void freeSTRarr(char** strarr, int  size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		free(strarr[i]);
	}
}
char* createName()
{
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
}