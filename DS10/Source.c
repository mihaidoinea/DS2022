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

typedef struct node
{
	NodeInfo* info;
	struct node* pNext;
}Node;

typedef struct HT
{
	Node** items;
	int size;
}HashTable;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo* info);
void printInfo(NodeInfo* info);
/*functions signatures for PQ operations*/
void initHashTable(HashTable* ht, int size)
{
	ht->items = (Node**)malloc(sizeof(Node*) * size);
	memset(ht->items, NULL, sizeof(Node*) * size);
	ht->size = size;
}
int fhash(char* key)
{
	return key[0] % 26;
}
void insertHT(HashTable ht, NodeInfo* emp)
{
	int index = fhash(emp->name);
	Node* node = createNode(emp);
	if (ht.items[index] == NULL)
		ht.items[index] = node;
	else
	{
		node->pNext = ht.items[index];
		ht.items[index] = node;
	}

}
NodeInfo* searchHT(HashTable* hTable, char* key)
{
	NodeInfo* value = NULL;
	int index = fhash(key);
	if (hTable->items[index] != NULL)
	{
		Node* aux = hTable->items[index];
		while (aux && (strcmp(key, aux->info->name) != 0))
			aux = aux->pNext;
		if (aux != NULL)
			value = aux->info;
	}
	return value;

}
void main()
{
	HashTable hTable = {.items = NULL, .size=0};
	initHashTable(&hTable, 26);
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
			insertHT(hTable, info);

		}

		NodeInfo* emp = searchHT(&hTable, "Cazacu Robert1");
		printInfo(emp);

	}
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
Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}