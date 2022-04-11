#include "stdio.h"
int sum(int a, int b)
{
	return a + b;
}
int product(int a, int b)
{
	return a * b;
}
void main()
{
	int (*fct)(int, int) = NULL;
	fct = sum;
	fct = product;
	int result = fct(4, 5);


	static char a = 7;
	static char b = 9;
	static int c = 0;
	c = a + b;

	int* pc = malloc(4);
	*pc = c;
	//free(pc);
	if (pc)
	{
		printf("value=%d", *pc);
	}
	
}