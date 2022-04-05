#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "memory.h"
#include "string.h"
void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	char* names[100];
	memset(names, NULL, 100 * sizeof(char*)); //100*4
	if (pFile)
	{
		char buffer[128];
		int index = 0;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			names[index] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(names[index++], buffer);
			fscanf(pFile, "%s", buffer);
		}
		for (int i = 0; i < 99; i++)
			for (int j = i + 1; j < 100; j++)
			{
				if (names[j] != NULL) {
					if (names[i][0] > names[j][0])
					{
						char* tmp = names[i];
						names[i] = names[j];
						names[j] = tmp;
					}
				}
			}
	}
	int a = 2;
}