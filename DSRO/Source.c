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

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
}Node;

typedef struct Employee NodeInfo;
typedef struct node Stack;
typedef struct node Queue;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
void push(Stack**, NodeInfo*);
NodeInfo* pop(Stack**);
NodeInfo* peek(const Stack*);
void printInfo(NodeInfo*);

Queue* put(Queue*, NodeInfo*);
NodeInfo* get(Queue**);
NodeInfo* peek(const Queue*);

void main()
{
	Queue* queue = NULL;
	Stack* stack = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER];
	const char *sepList = ",\n";
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

			NodeInfo* infoStack = createInfo(code, name, dept, salary);
			push(&stack, infoStack);

			NodeInfo* infoQueue = createInfo(code, name, dept, salary);
			queue = put(queue, infoQueue);
		}
		NodeInfo* emp = peek(stack);
		printInfo(emp);
		while (stack != NULL)
		{
			emp = pop(&stack);
			printInfo(emp);
			free(emp->name);
			free(emp->dept);
			free(emp);
		}
		printf("\n------------------------------\n");
		while (queue != NULL)
		{
			emp = get(&queue);
			printInfo(emp);
			free(emp->name);
			free(emp->dept);
			free(emp);
		}

	}
}

NodeInfo* get(Queue** queueTail)
{
	NodeInfo* value = NULL;
	if (*queueTail != NULL)
	{
		value = (*queueTail)->pNext->info;
		Node* tmp = (*queueTail)->pNext;
		if (tmp == *queueTail)
			*queueTail = NULL;
		else
			(*queueTail)->pNext = tmp->pNext;
		free(tmp);
	}
	return value;
}

Queue* put(Queue* queueTail, NodeInfo* info)
{
	Node* node = createNode(info);
	if (queueTail == NULL)
		node->pNext = node;
	else
	{
		node->pNext = queueTail->pNext;
		queueTail->pNext = node;
	}
	return node;
}

NodeInfo* peek(const Stack* stack)
{
	NodeInfo* value = NULL;
	if (stack != NULL)
		value = stack->info;
	return value;
}

NodeInfo* pop(Stack** stack)
{
	NodeInfo* value = NULL;
	if (*stack != NULL)
	{
		value = (*stack)->info;
		Node* tmp = (*stack);
		(*stack) = tmp->pNext;
		free(tmp);
	}
	return value;
}

void push(Stack** stack, NodeInfo* info)
{
	Node* node = createNode(info);
	node->pNext = *stack;
	*stack = node;
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
Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}