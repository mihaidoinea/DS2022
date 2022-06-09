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
typedef struct Neighbour
{
	struct Vertex* mainNode;
	struct Neighbour* nextAdj;
}Neighbour;
typedef struct Vertex
{
	NodeInfo* emp;
	struct Vertex* nextNode;
	struct Neighbour* neighbours;
}Vertex;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
void printInfo(NodeInfo* info);
/*functions signatures for Graph structure's operations*/
void addNode(Vertex**, NodeInfo*);
void addEdge(Vertex*, short, short);
void displayGraph(Vertex*);

void main()
{
	Vertex* graph = NULL;
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
			//insert call
			addNode(&graph, info);
		}
		addEdge(graph, 10001, 10002);
		addEdge(graph, 10001, 10003);
		addEdge(graph, 10001, 10010);
		addEdge(graph, 10002, 10003);
		addEdge(graph, 10002, 10004);
		addEdge(graph, 10004, 10005);
		addEdge(graph, 10005, 10006);
		addEdge(graph, 10005, 10008);
		addEdge(graph, 10007, 10010);
		addEdge(graph, 10009, 10010);

		displayGraph(graph);
	}
}

void displayGraph(Vertex* graph)
{
	while (graph)
	{
		printf("\nNeighbours of node %d\n", graph->emp->code);
		Neighbour* adj = graph->neighbours;
		while (adj)
		{
			printInfo(adj->mainNode->emp);
			adj = adj->nextAdj;
		}
		graph = graph->nextNode;
	}
}
Neighbour* createNeighbour(Vertex* dst)
{
	Neighbour* node = (Neighbour*)malloc(sizeof(Neighbour));
	node->mainNode = dst;
	node->nextAdj = NULL;
	return node;
}
void addEdge(Vertex* graph, short src, short dst)
{
	Vertex* srcNode = NULL, * dstNode = NULL;
	while (graph && (srcNode == NULL || dstNode == NULL))
	{
		if (graph->emp->code == src)
			srcNode = graph;
		if (graph->emp->code == dst)
			dstNode = graph;
		graph = graph->nextNode;
	}
	//add 1->2
	Neighbour* node = createNeighbour(dstNode);
	node->nextAdj = srcNode->neighbours;
	srcNode->neighbours = node;
	//add 2->1
	node = createNeighbour(srcNode);
	node->nextAdj = dstNode->neighbours;
	dstNode->neighbours = node;

}
Vertex* createVertex(NodeInfo* emp)
{
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));
	node->emp = emp;
	node->neighbours = NULL;
	node->nextNode = NULL;
	return node;
}
void addNode(Vertex** graph, NodeInfo* emp)
{
	Vertex* node = createVertex(emp);
	node->nextNode = *graph;
	*graph = node;
}

void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s, Salary: %f\n", info->code, info->name, info->salary);
	else
		printf("No data to print!");
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