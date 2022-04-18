#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
#include "stdbool.h"
struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};

typedef struct Node
{
	struct Employee* info;
	struct Node* pNext;
}Queue;

typedef struct Employee NodeInfo;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Queue* createNode(NodeInfo*);
/*functions signatures for list operations*/
void printInfo(NodeInfo*);
Queue* put(Queue*, NodeInfo*);
NodeInfo* get(Queue**);
void deleteQueue(Queue**);
bool isEmpty(Queue*);
void printQueue(Queue**);

void main()
{
	Queue* queueTail = NULL;

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
			queueTail = put(queueTail, info);
		}
		printQueue(&queueTail);
		printf("\n--------------------------------\n");
		deleteQueue(&queueTail);

	}
}
void printQueue(Queue** tail)
{
	Queue* tmp = NULL;
	while (!isEmpty(*tail))
	{
		NodeInfo* info = get(tail);
		printInfo(info);
		tmp = put(tmp, info);
	}
	*tail = tmp;
}

bool isEmpty(Queue* queue)
{
	return (queue == NULL);
}
void deleteQueue(Queue** tail)
{
	while (!isEmpty(*tail))
	{
		//NodeInfo* emp = get(&*tail); //queueTail == *tail
		NodeInfo* emp = get(tail);
		printInfo(emp);
		free(emp->name);
		free(emp->dept);
		free(emp);		
	}
}

NodeInfo* get(Queue** tail)
{
	NodeInfo* value = NULL;
	if (!isEmpty(*tail))
	{
		value = (*tail)->pNext->info;
		Queue* tmp = (*tail)->pNext;
		if (tmp->pNext == tmp)
			(*tail) = NULL;
		else
			(*tail)->pNext = tmp->pNext;
		free(tmp);
	}
	return value;
}

Queue* put(Queue* tail, NodeInfo* info)
{
	Queue* node = createNode(info);
	if (isEmpty(tail))
		node->pNext = node;
	else
	{
		node->pNext = tail->pNext;
		tail->pNext = node;
	}
	return node;
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
Queue* createNode(NodeInfo* info)
{
	Queue* node = (Queue*)malloc(sizeof(Queue));
	node->info = info;
	node->pNext = NULL;
	return node;
}