#include "stdlib.h"
int c = 7;
void switchInts(int* z, int* w)
{
	//int* z = x;
	//int* w = y;
	//correct
	int aux = *z;
	*z = *w;
	*w = aux;

	//wrong
	//int* aux = z;
	//z = w;
	//w = aux;
}
void main()
{
	int a = 5;
	int b;
	b = 8;
	//b += c;
	switchInts(&a, &b);

	int a1[] = { 1,2,3,4,5 };
	int* a2 = { 1 };
	//int* a2 = { &a };
	int* a3 = NULL;
	a3 = (int*)malloc(16); //4 ints / 2 double / 2long / 16 chars = 15 + "string terminator" // 4 pointers // 8 shorts
	a3[0] = 1;
	a3[1] = 2;
	a3[2] = 3;
	a3[3] = 4;
	a3[4] = 5;

	void* a4 = malloc(16);
	int* ia4 = a4;
	short* sa4 = a4;
	char* ca4 = a4;
}