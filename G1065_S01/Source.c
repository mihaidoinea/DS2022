#include "stdlib.h"
#include "stdio.h"
#include "string.h"
int c = 7;
void switchInts(int*, int*);
void printArrays(int*, int*);
void main()
{
	int a = 5;
	int b;
	b = 9;
	//b += c;
	switchInts(&a, &b);
	int a1[] = { 1,2,3,4,5 };
	int* a2 = { &a };
	int* a3 = { &b };
	switchInts(a2, a3);
	int* a4 = NULL;
	a4 = (int*)malloc(5*sizeof(int));
	a4[0] = 1;
	a4[1] = 2;
	a4[2] = 3;
	a4[3] = 4;
	a4[4] = 5;
	printArrays(a1, a4, 5);
	int na1 = sizeof(a1) / sizeof(int);
	int na4 = sizeof(a4);
}
void printArrays(int x[5], int* y, int noEl)
{
	int nx = sizeof(x);
	int ny = sizeof(y);
	for (int i = 0; i < noEl +1000; i++)
		printf("x[%d]=%d\t",i, x[i]);
}
void switchInts(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}