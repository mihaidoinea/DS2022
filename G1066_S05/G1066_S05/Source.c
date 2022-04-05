#define _CRT_SECURE_NO_WARNINGS
#include "memory.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	char buffer[128];
	int index = 0;
	char* names[100];
	char** catalogue[26];
	char freq[26];
	memset(names, NULL, sizeof(char*) * 100);
	memset(freq, 0, sizeof(char) * 26);
	memset(catalogue, NULL, sizeof(char**) * 26);
	if (pFile) {
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			names[index] = (char*)malloc(strlen(buffer) + 1); //(strlen(buffer)+1) * sizeof(char)
																//malloc returns void *
			strcpy(names[index], buffer); //source is const char* because it needs to ramain unchanged
			
			//names[index][0] <=> *names[index]
			short position = *names[index++] - 'A';
			freq[position]++;
			fscanf(pFile, "%s", buffer);
		}
		char aux[26];
		/*for (int i = 0; i < 26; i++)
			aux[i] = freq[i];*/
		memcpy(aux, freq, 26 * sizeof(char));
		for (int i = 0; i < index; i++)
		{
			int pos = *names[i] - 'A';
			if (catalogue[pos] == NULL)
				catalogue[pos] = (char**)malloc(sizeof(char*) * freq[pos]);
			catalogue[pos][--aux[pos]] = (char*)malloc(strlen(names[i]) + 1);
			strcpy(catalogue[pos][aux[pos]], names[i]);
		}

		for (int i = 0; i < 26; i++)
		{
			if (catalogue[i]) {
				printf("Group %c\n", i + 'A');
				for (int j = 0; j < freq[i]; j++)
					printf("Name: %s\n", catalogue[i][j]);
			}
		}

	}
}