#include "stdio.h"
typedef struct letter
{
	char : 5;
	char bit : 1;
	char : 2;
}Letter;

void main()
{
	char letter = 'A';
	printf("Value %c\n", letter);
	Letter* ltr = &letter;
	ltr->bit = !ltr->bit;
	printf("Value %c\n", letter);
	letter = letter & 223;
	printf("Value %c\n", letter);
	letter = letter | 32;
	printf("Value %c\n", letter);

}