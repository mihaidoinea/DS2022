#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "memory.h"
#include "string.h"
struct Student
{
	char* name;
};
typedef struct Student Student;
struct Node //a node from the list
{
	Student* info;
	struct Node* pNext;
};
typedef struct Node Node;

/*function headers for memory manipulation*/
Student* createInfo(char* name);
Node* createNode(Student* info);

/*function headers for list operations*/
//insert - delete - traversal
void insertHead(Node** head, Student* info);
Node* insertTail(Node* head, Student* info);
void deletePosition(Node** head, int pos);
void printList(Node* head);

void main() {
	FILE* pFile = fopen("Data.txt", "r");
	Node* list = NULL;
		
	char* names[100];
	static short freq[26];
	char** agenda[26];
	memset(names, NULL, 100 * sizeof(char*));
	memset(agenda, NULL, 26 * sizeof(char*));
	if (pFile) {
		char buffer[128];
		int index = 0;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			names[index] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(names[index++], buffer);
			int pos = *buffer - 'A';
			freq[pos]++;
			fscanf(pFile, "%s", buffer);
		}
		//for (int i = 0; i < 99; i++)
		//	for (int j = i + 1; j < 100; j++)
		//	{
		//		if (names[j] != NULL)
		//		{
		//			//if (names[i][0] > names[j][0]) {
		//			if (*names[i] > *names[j]) {
		//				char* temp = names[i];
		//				names[i] = names[j];
		//				names[j] = temp;
		//			}
		//		}
		//	}
		short temp[26];
		for (int i = 0; i < 26; i++)
			temp[i] = freq[i];
		for (int i = 0; i < 99; i++)
			if (names[i])
			{
				int pos = *names[i] - 'A';
				if (agenda[pos] == NULL)
					agenda[pos] = (char**)malloc(freq[pos] * sizeof(char*));
				agenda[pos][freq[pos] - 1] = (char*)malloc((strlen(names[i]) + 1) * sizeof(char));
				strcpy(agenda[pos][freq[pos] - 1], names[i]);
				freq[pos]--;
			}
		for (int i = 0; i < 26; i++)
		{
			if (agenda[i]) 
			{
				printf("Group %c\n", i + 'A');
				for (int j = 0; j < temp[i]; j++)
				{
					printf("Name %s\n", agenda[i][j]);

					//insert the name into the list
				}
			}
		}
	}
	int a = 2;
}