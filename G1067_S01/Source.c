#include "stdio.h"
#include "stdlib.h"

int c = 4;
void switchints(int*, int*);
void changeArrays(int*, int*);
void main()
{
	int a = 2; 
	int b;
	b = 7;
	//switchints(&a, &b, NULL, NULL);

	int v1[] = { 1,2,3,4,5 };
	int* v2 = NULL;
	v2 = (int*)malloc(5*sizeof(int));
	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;
	v2[3] = 4;
	v2[4] = 5;
	switchints(&a, &b);
	b += c;
	int* v3 = { &a };
	int* v4 = { &b };
	int* v5 = { &a };
	//changeArrays(&v3, &v4);
	changeArrays(v3, v4);

	FILE* pFile = NULL;


}
//float -> double // short -> int //
void switchints(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}
//v1[0], v1[1], v1[2], v1[3], v1[4]
//*(v1+0), *(v1+1), *(v1+2), *(v1+3), *(v1+4)
void changeArrays(int* x, int* y)
{
	/*int z = **x;
	**x = **y;
	**y = z;*/

	int z = *x;
	*x = *y;
	*y = z;
}