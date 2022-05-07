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
	int nextIndex; //next available position to insert
}PriorityQueue;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
/*functions signatures for PQ operations*/
void putPQ(PriorityQueue*, NodeInfo*);
NodeInfo* getPQ(PriorityQueue*);
NodeInfo* peek(const PriorityQueue*);
void ReHeapUp(PriorityQueue*, int);
void printInfo(NodeInfo*);

void main()
{
	PriorityQueue pQueue = { .items = NULL, .size = 0, .nextIndex = 0 };

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

			printf("\n------------------------------\n");
			for (int i = 0; i < pQueue.nextIndex; i++)
				printInfo(pQueue.items[i]);

		}
	}
}

void putPQ(PriorityQueue* pQueue, NodeInfo* emp)
{
	//initial allocation of memory
	if (pQueue->items == NULL)
	{
		pQueue->items = (NodeInfo**)malloc(sizeof(NodeInfo*) * 7);
		pQueue->size = 7;
		memset(pQueue->items, NULL, sizeof(NodeInfo*) * 7);
	}
	//resizing PQ structure if it's full
	if (pQueue->nextIndex == pQueue->size) // queue overflow
	{
		NodeInfo** tmp;
		tmp = (NodeInfo**)malloc(sizeof(NodeInfo*) * pQueue->size*2);
		memset(tmp, NULL, sizeof(NodeInfo*) * pQueue->size * 2);
		memcpy(tmp, pQueue->items, pQueue->size * sizeof(NodeInfo*));
		free(pQueue->items);
		pQueue->items = tmp;
		pQueue->size *= 2;
	}
	pQueue->items[pQueue->nextIndex] = emp;
	ReHeapUp(pQueue, pQueue->nextIndex);
	pQueue->nextIndex++;
}
void ReHeapUp(PriorityQueue* pQueue, int childIndex)
{
	if (childIndex > 0)
	{
		int parentIndex = (childIndex - 1) / 2;
		if (pQueue->items[childIndex]->code > pQueue->items[parentIndex]->code)
		{
			NodeInfo* aux = pQueue->items[childIndex];
			pQueue->items[childIndex] = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = aux;
			ReHeapUp(pQueue, parentIndex);
		}
	}
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
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