//transformare matrice in liniarizata cu complexitate O(N)
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define BUFFER_SIZE 100
void convert(char*);
struct Letter //1B  0100 0001
{
	int : 5;
	int bit : 1;
	int : 2;
};
void main()
{
	//char* matrix[3][3];
	char matNames[][10] = {"Ion","Ana","George","Popescu"};
	char*** matrix = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	char* buffer = (char*)malloc(BUFFER_SIZE);
	if (pFile)
	{
		int matSize = 0;
		//fscanf(pFile, "%i", &matSize);
		fgets(buffer, BUFFER_SIZE, pFile);
		matSize = atoi(buffer);
		//1.verde
		matrix = (char***)malloc(matSize * sizeof(char**));
		//2.pink
		for (int i = 0; i < matSize; i++)
		{
			matrix[i] = (char**)malloc(matSize * sizeof(char*));
			memset(matrix[i], NULL, matSize * sizeof(char*));
		}
		int i = 0, j = 0, index = 0;
		//O(N*N) >>>>>> O(N)
		while (!feof(pFile))
		{
			i = index / matSize;
			j = index % matSize;
			fgets(buffer, BUFFER_SIZE, pFile);
			matrix[i][j] = (char*)malloc(strlen(buffer) + 1);
			strcpy(matrix[i][j], buffer);
			index++;
		}
		fclose(pFile);
		for (int i = 0; i < matSize; i++)
			for (int j = 0; j < matSize; j++)
				fputs(matrix[i][j], stdout);

		for (int i = 0; i < matSize; i++)
			for (int j = 0; j < matSize; j++)
				convert(matrix[i][j]);

		for (int i = 0; i < matSize; i++)
			for (int j = 0; j < matSize; j++)
				fputs(matrix[i][j], stdout);
	}
}
void convert(char* name)
{
	struct Letter* letter;
	for (int i = 0; i < strlen(name); i++)
		if (name[i] >= 'a' && name[i] <= 'z')
			name[i] = name[i] & 223;
}