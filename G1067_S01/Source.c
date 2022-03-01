#include "stdlib.h"
int c = 4;
void switchints (int* x, int* y, int* v1, int* v3)
{
	int z = *x;
	*x = *y;
	*y = z;
	v1[3] = 9;
	v3[3] = 9;
}
void main()
{
	int a = 2; 
	int b;
	b = 7;
	//switchints(&a, &b, NULL, NULL);

	int v1[] = { 1,2,3,4,5 };
	int* v2 = { &a };
	int* v3 = NULL;
	v3 = (int*)malloc(5*sizeof(int));
	v3[0] = 1;
	v3[1] = 2;
	v3[2] = 3;
	v3[3] = 4;
	v3[4] = 5;
	switchints(&a, &b, v1, v3);
	b += c;
}