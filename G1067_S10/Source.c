#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};
typedef struct Employee NodeInfo;

typedef struct HT
{
	NodeInfo** items;
	int size;
	int noEl;
}HashTable;


#define LINE_BUFFEER 1024
#define HT_INITIAL_CAPACITY 3
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);
/*functions signatures for HT operations*/
void putHT(HashTable*, NodeInfo*);
int probing(HashTable* hTable, int index, char* key);
void resizeHT(HashTable* hTable);
NodeInfo* getHT(HashTable, char*);

void main()
{
	HashTable hTable = { .items = NULL, .size = 0, .noEl = 0 };
	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], * sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			token = strtok(lineBuffer, sepList);
			code = atoi(token);
			name = strtok(NULL, sepList);
			dept = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			salary = atof(token);

			NodeInfo* info = createInfo(code, name, dept, salary);
			putHT(&hTable, info);

			printf("\n**********************************\n");
			printf("\nHT capacity: %d\n", hTable.size);
			for (int i = 0; i < hTable.size; i++)
				if (hTable.items[i])
				{
					printf("Index: %d --", i);
					printInfo(hTable.items[i]);
				}
			NodeInfo* emp = getHT(hTable, "Cazacu Robert");
			printInfo(emp);
 		}

	}
}
int fHash(char* key, int size)
{
	return key[0] % size;
}

NodeInfo* getHT(HashTable hTable, char* key)
{
	NodeInfo* result = NULL;
	if (hTable.items != NULL)
	{
		int index = fHash(key, hTable.size);
		while (index < hTable.size && hTable.items[index] != NULL && strcmp(key, hTable.items[index]->name) != 0)
			index++;
		if (index < hTable.size && hTable.items[index] != NULL)
			result = hTable.items[index];
	}
	return result;
}


void resizeHT(HashTable* hTable)
{
	NodeInfo** aux = hTable->items;
	hTable->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * hTable->size * 2);
	memset(hTable->items, NULL, sizeof(NodeInfo*) * hTable->size * 2);
	hTable->size *= 2;
	for (int i = 0; i< hTable->size / 2; i++)
	{
		if (aux[i] != NULL)
			putHT(hTable, aux[i]);
	}
	free(aux);
}
int probing(HashTable* hTable, int index, char* key)
{
	do
	{
		index++;
		if (index == hTable->size)
		{
			resizeHT(hTable);
			index = fHash(key, hTable->size);
		}
	} while (hTable->items[index] != NULL && strcmp(hTable->items[index]->name, key) != 0);
	return index;
}
void putHT(HashTable* hTable, NodeInfo* emp)
{
	if (hTable->items == NULL)
	{
		hTable->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * HT_INITIAL_CAPACITY);
		hTable->size = HT_INITIAL_CAPACITY;
		memset(hTable->items, NULL, sizeof(NodeInfo*) * HT_INITIAL_CAPACITY);
	}
	int index = fHash(emp->name, hTable->size);
	if (hTable->items[index] != NULL)
	{
		index = probing(hTable, index, emp->name);
	}
	hTable->items[index] = emp;
}


void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s\n", info->code, info->name);
	else
		printf("No data to print!");
}

NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}