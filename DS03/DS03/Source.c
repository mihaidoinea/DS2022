#define _CRT_SECURE_NO_WARNINGS 
#include "stdio.h"
#include "stdlib.h"
typedef struct Node
{
	char* data;
	struct Node* next;
}List;
//typedef struct Node List;

void insertHead(List**, char*);
List* insertTail(List*, char*);
void printList(List*);

void main()
{
	List* list = NULL; char buffer[128];
	scanf("%s", buffer);
	while (!feof(stdin))
	{
		insertHead(&list, buffer);
		scanf("%s", buffer);
	}
	printList(list);
}

void insertHead(List** head, char* data)
{
	List* node = malloc(sizeof(List));
	node->data = malloc(strlen(data) + 1);
	strcpy(node->data, data);
	node->next = NULL;

	node->next = *head;
	*head = node;
}

void printList(List* head)
{
	//List* tmp = head;
	while (head)
	{
		printf("Value: %s\n", head->data);
		head = head->next;
	}
}