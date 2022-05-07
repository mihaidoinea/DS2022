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
typedef struct PQ
{
	NodeInfo** items;
	int size;
	int index;
}PriorityQueue;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
/*functions signatures for PQ operations*/
void putPQ(PriorityQueue*, NodeInfo*);
void printInfo(NodeInfo*);

void main()
{
	PriorityQueue pQueue = { .items = NULL, .size = 0, .index = 0 };

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

			putPQ(&pQueue, info);

			printf("\n*****************************\n");
			for (int i = 0; i < pQueue.index; i++)
				printInfo(pQueue.items[i]);

		}
	}
}
void ReHeapUp(PriorityQueue* pQueue, int childIndex)
{
	if (childIndex > 0)
	{
		int pIndex = (childIndex - 1) / 2;
		if (pQueue->items[childIndex]->code > pQueue->items[pIndex]->code)
		{
			NodeInfo* aux = pQueue->items[childIndex];
			pQueue->items[childIndex] = pQueue->items[pIndex];
			pQueue->items[pIndex] = aux;
			ReHeapUp(pQueue, pIndex);
		}
	}
}

void putPQ(PriorityQueue* pQueue, NodeInfo* emp)
{
	//initial PQ allocation
	if (pQueue->items == NULL)
	{
		pQueue->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * 5);
		memset(pQueue->items, NULL, sizeof(NodeInfo*) * 5);
		pQueue->size = 5;
	}
	//resize operation for PQ
	if (pQueue->index >= pQueue->size)
	{
		NodeInfo** aux = pQueue->items;
		pQueue->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * pQueue->size * 2);
		memset(pQueue->items, NULL, sizeof(NodeInfo*) * pQueue->size * 2);
		memcpy(pQueue->items, aux, sizeof(NodeInfo*) * pQueue->size);
		pQueue->size *= 2;
	}
	pQueue->items[pQueue->index] = emp;
	ReHeapUp(pQueue, pQueue->index);
	pQueue->index++;
}

void printInfo(NodeInfo* info)
{
	if (info)
	{
		printf("Code: %d - Name: %s\n", info->code, info->name);
	}
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