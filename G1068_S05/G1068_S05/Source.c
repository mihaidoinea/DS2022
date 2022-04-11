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
typedef struct node SLinkedList;
#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
Node* insertTail(SLinkedList*, NodeInfo*);
void printList(const SLinkedList*);

double averageSalary(const SLinkedList*);
SLinkedList* addCircularProperty(SLinkedList*);
void printCircularList(SLinkedList*);
double averageCircularSalary(const SLinkedList*);
void deleteHeadList(SLinkedList**);

void main()
{
	SLinkedList* list = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER], *sepList = ",\n";
	char* name = NULL, *dept = NULL; short code = 0; double salary = 0.0;
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

			list = insertTail(list, info);

		}
		printList(list);

		double avg = averageSalary(list);
		printf("Average salary %f\n", avg);

		list = addCircularProperty(list);
		printf("\n----------------------------------------------\n");
		printCircularList(list);
		
		avg = averageCircularSalary(list);
		printf("Average salary %f\n", avg);

		deleteHeadList(&list);
		printf("\n----------------------------------------------\n");
		printCircularList(list);

		printf("\n----------------------------------------------\n");
		while (list)
		{
			printf("\n----------------------------------------------\n");
			deleteHeadList(&list);
			printCircularList(list);
		}		
	}
}

void deleteHeadList(SLinkedList** list)
{
	Node* tmp = *list;
	if (*list)
	{	
		if ((*list)->pNext == *list)
		{
			*list = NULL;
		}
		else
		{
			Node* iterator = *list;
			while (iterator->pNext != *list)
				iterator = iterator->pNext;
			iterator->pNext = (*list)->pNext;
			*list = tmp->pNext;
		}
		free(tmp->info->name);
		free(tmp->info->dept);
		free(tmp->info);
	}
	free(tmp);
}

double averageCircularSalary(const SLinkedList* list)
{
	int counter = 0;
	double average = 0.0;
	Node* tmp = list;
	if (list != NULL)
	{
		do
		{
			average += tmp->info->salary;
			counter++;
			tmp = tmp->pNext;
		} while (tmp != list);
	}
	return average / counter;
}

void printInfo(Node* node)
{
	printf("Code: %d, Name: %s, Dept: %s, Salary: %f\n",
		node->info->code,
		node->info->name,
		node->info->dept,
		node->info->salary);
}

void printCircularList(SLinkedList* list)
{
	Node* tmp = list;
	if (list != NULL)
	{
		do
		{
			printInfo(tmp);
			tmp = tmp->pNext;
		} while (tmp!=list);
	}
	/*while (tmp->pNext != list)
	{
		printInfo(tmp);
		tmp = tmp->pNext;
	}
	printInfo(tmp);*/
}

SLinkedList* addCircularProperty(SLinkedList* list)
{
	Node* head = list;
	while (list->pNext != NULL)
		list = list->pNext;
	list->pNext = head;
	return head;
}

double averageSalary(const SLinkedList* head)
{
	int counter = 0;
	double average = 0.0;
	while (head)
	{
		average += head->info->salary;
		counter++;
		head = head->pNext;
	}
	return average / counter;
}

void printList(const SLinkedList* head)
{
	for (; head; head = head->pNext)
		printf("Code: %d, Name: %s, Dept: %s, Salary: %f\n",
			head->info->code,
			head->info->name,
			head->info->dept,
			head->info->salary);
}

Node* insertTail(SLinkedList* head, NodeInfo* emp)
{
	Node* node = createNode(emp);
	if (head == NULL)
		head = node;
	else
	{
		Node* aux = head;
		while (aux->pNext)
			aux = aux->pNext;
		aux->pNext = node;
	}
	return head;
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