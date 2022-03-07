#include "stdlib.h"
#include "stdio.h"
int c = 8;
void switchInts(int*, int*);
void printArrays(int*, int*);
void main()
{
	int a = 4;
	int b;
	b = 9;
	switchInts(&a, &b);
//	b += c;
	int a1[] = { 1,2,3,4,5 }; //static array of ints
	int* a2 = { &a };		 // dynamic array of only 1 element
	int* a3 = NULL;
	a3 = malloc(5*sizeof(int));
	a3[0] = 1;
	a3[1] = 2;
	a3[2] = 3;
	a3[3] = 4;
	a3[4] = 5;
	printArrays(a1, a3);
}
void printArrays(int* x, int* y)
{
	for (int i = 0; i < 5 + 1000; i++)
		//printf("x[%d]=%d\t", i, x[i]);
		printf("x[%d]=%d\t", i, *(x + i));
}

void switchInts(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}