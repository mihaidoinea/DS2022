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

typedef struct PrioQueue
{
	struct Employee** items;
	int index;
	int size;
}PrioQueue;

typedef struct Employee NodeInfo;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo*);
/*functions signatures for PQ operations*/
void putEmployee(PrioQueue*, NodeInfo*);
NodeInfo* getEmployee(PrioQueue*);

void main()
{
	PrioQueue pQueue = { .items = NULL, .size=0, .index=0 };

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

			putEmployee(&pQueue, info);

			printf("\n----------------------------\n");
			for (int i = 0; i < pQueue.index; i++)
			{
				printInfo(pQueue.items[i]);
			}

		}
	}
}
void ReHeapUp(PrioQueue* pQueue, int childIndex)
{
	if (childIndex > 0)
	{
		int parentIndex = (childIndex - 1) / 2;
		if (pQueue->items[childIndex]->code > pQueue->items[parentIndex]->code)
		{
			NodeInfo* tmp = pQueue->items[childIndex];
			pQueue->items[childIndex] = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = tmp;
			ReHeapUp(pQueue, parentIndex);
		}
	}
}
void putEmployee(PrioQueue* pQueue, NodeInfo* emp)
{
	if (pQueue->items == NULL)
	{
		pQueue->items = (NodeInfo**)malloc(10 * sizeof(NodeInfo*));
		memset(pQueue->items, NULL, 10 * sizeof(NodeInfo*));
		pQueue->size = 10;
	}
	//resize operation
	if (pQueue->index >= pQueue->size)
	{
		NodeInfo** aux = pQueue->items;
		pQueue->items = (NodeInfo**)malloc(pQueue->size * 2 * sizeof(NodeInfo*));
		for (int i = 0; i < pQueue->index; i++)
		{
			pQueue->items[i] = aux[i];
			pQueue->items[pQueue->index + i] = NULL;
		}
		pQueue->size *= 2;
		free(aux);
	}
	pQueue->items[pQueue->index] = emp;
	ReHeapUp(pQueue, pQueue->index);
	pQueue->index++;

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