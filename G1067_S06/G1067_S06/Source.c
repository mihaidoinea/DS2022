#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
//keyboad - stdin
//console - stdout
#define LINE_BUFFER 128
typedef struct Employee {
	short code;
	char* name;
	char* department;
	double salary;
}Employee;
//typedef struct Employee Employee;
typedef struct Node
{
	Employee* info;
	struct Node* pNext;
}Node;

/*functions' signatures for memory management*/
Employee* createInfo(short, char*, char*, double);
Node* createNode(Employee*);
/*functions' signatures for list operations*/
void printList(Node*);

void main()
{
	Node* list = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	char lineBuffer[LINE_BUFFER], * token, sep_list[] = ",\n";
	Employee* emp = NULL;
	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			emp = (Employee*)malloc(sizeof(Employee));
			//parsing the code
			token = strtok(lineBuffer, sep_list);
			emp->code = atoi(token);

			//parsing the name
			token = strtok(NULL, sep_list);
			emp->name = (char*)malloc(strlen(token) + 1);
			strcpy(emp->name, token);

			//parsing the dept
			token = strtok(NULL, sep_list);
			emp->department = (char*)malloc(strlen(token) + 1);
			strcpy(emp->department, token);

			//parsing the salary
			token = strtok(NULL, sep_list);
			emp->salary = atof(token);

		}

		printList(list);

	}
}

void printInfo(Employee* emp)
{
	printf("Code: %d - Name: %s - Dept: %s - Salary: %f\n",
		emp->code,
		emp->name,
		emp->department,
		emp->salary);
}
void printList(const Node* head)
{
	while (head)
	{
		printInfo(head->info);
		head = head->pNext;
	}
}
Employee* createInfo(short code, char* name, char* dept, double salary)
{
	Employee* emp = (Employee*)malloc(sizeof(Employee));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->department = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->department, dept);
	emp->salary = salary;
	return emp;
}

Node* createNode(Employee* emp)
{
	//declare and allocate memory
	Node* node = (Node*)malloc(sizeof(Node));
	//initialize variable
	node->info = emp;
	node->pNext = NULL;
	//return value
	return node;
}