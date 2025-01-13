#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
	char* name;
	int average;
}STUDENT;

typedef struct linedata {
	int _average;
	int _numofline;
}LINEDATA;

LINEDATA* merge(LINEDATA a1[], short int size1, LINEDATA a2[], short int size2);
void isOpen(FILE* f);
void checkMemoryAllocation(void* ptr);
void Exe5Q3(char* fileName);
LINEDATA getInfo(FILE* f);
void mergeSort(LINEDATA* infoArr, short int n);
void copyArr(LINEDATA* dest, LINEDATA* src, short int size);
char* fileName();
