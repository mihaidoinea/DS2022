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

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
Stack* push(Stack*, NodeInfo*);
NodeInfo* pop(Stack**);
NodeInfo* peek(const Stack*);
void printInfo(NodeInfo*);
Stack* printStack(Stack*);

void main()
{
	Stack* stack = NULL;
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

			stack = push(stack, info);
			
		}
		NodeInfo* emp = pop(&stack);
		printInfo(emp);
		stack = printStack(stack);
		printf("\n------------------------\n");
		stack = printStack(stack);
		printf("\n------------------------\n");
		while (stack)
		{
			NodeInfo* emp = pop(&stack);
			printInfo(emp);
			free(emp->name);
			free(emp->dept);
			free(emp);
		}
	}
}
Stack* printStack(Stack* stack)
{
	Stack* tmp = NULL;
	while (stack)
	{
		NodeInfo* emp = pop(&stack);
		printInfo(emp);
		tmp = push(tmp, emp);
	}
	while (tmp)
		stack = push(stack, pop(&tmp));
	return stack;
}
NodeInfo* pop(Stack** stack)
{
	NodeInfo* value = NULL;
	if (*stack != NULL)
	{
		value = (*stack)->info;
		Node* tmp = *stack;
		*stack = tmp->pNext;
		free(tmp);
	}
	return value;
}

Stack* push(Stack* stack, NodeInfo* node)
{
	Stack* newNode = createNode(node);
	newNode->pNext = stack;
	return newNode;
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d, Name: %s, Dept: %s, Salary: %f\n",
		info->code,
		info->name,
		info->dept,
		info->salary);
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