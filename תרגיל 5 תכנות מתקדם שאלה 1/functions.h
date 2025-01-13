#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void Exe5Q1(char* fname, unsigned int x);
void checkMemoryAllocation(void* ptr);
void  createSTR(char** des, FILE* src, int num);
void isOpen(FILE* f);
bool isSmallCharacter(char c);
char* strFromFile(FILE* f);
char* setFileName(char* name);
void createFile(char* str[], int size, char* filename);
void lexicoMerge(char** strarr, int size);
void merge(char** arr1, int size1, char** arr2, int size2, char** res);
void freeSTRarr(char** strarr, int size);
void Exe5Q1(char* fname, unsigned int x);
char* createName();