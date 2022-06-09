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

typedef struct BST
{
	struct BST* left;
	NodeInfo* info;
	struct BST* right;
	short bFactor;
}BinarySearchTree;


#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
BinarySearchTree* createNode(NodeInfo*);
void printInfo(NodeInfo* info);
/*functions signatures for BST-AVL operations*/
BinarySearchTree* rebalance(BinarySearchTree*);
void insertBST(BinarySearchTree**, NodeInfo*);
void printLevels(BinarySearchTree*);

void printLeaves(BinarySearchTree* root)
{
	if (root)
	{
		if(root->left == NULL && root->right == NULL)
			printInfo(root->info);
		printLeaves(root->left);
		printLeaves(root->right);
	}
}

void preorder_PLR(BinarySearchTree* root)
{
	if (root)
	{
		printInfo(root->info);
		preorder_PLR(root->left);
		preorder_PLR(root->right);
	}
}
void inorder_LPR(BinarySearchTree* root)
{
	if (root)
	{
		inorder_LPR(root->left);
		printInfo(root->info);
		inorder_LPR(root->right);
	}
}

void main()
{
	BinarySearchTree* bTree = NULL;

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

			insertBST(&bTree, info);
			printf("\n*********************************\n");
			preorder_PLR(bTree);

		}
		printLevels(bTree);
	}
}

short height(BinarySearchTree* root)
{
	if (root)
		return 1 + max(height(root->left), height(root->right));
	else
		return 0;
}
void printLevel(BinarySearchTree* root, int lvl)
{
	if (root)
	{
		if(lvl == 0)
			printInfo(root->info);
		printLevel(root->left, lvl-1);
		printLevel(root->right, lvl-1);
	}
}
void printLevels(BinarySearchTree* root)
{
	int levels = height(root);
	for (int i = 0; i < levels; i++)
	{
		printf("\nLevel %d\n", i);
		printLevel(root, i);
	}
}
void insertBST(BinarySearchTree** root, NodeInfo* emp)
{
	if (*root == NULL)
	{
		*root = createNode(emp);
	}
	else
	{
		if ((*root)->info->code > emp->code)
			insertBST(&(*root)->left, emp);
		else if ((*root)->info->code < emp->code)
			insertBST(&(*root)->right, emp);
		else
			(*root)->info = emp;
	}
	*root = rebalance(*root);
}

BinarySearchTree* rightRotation(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	return desc;
}
BinarySearchTree* leftRotation(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	return desc;
}
BinarySearchTree* rebalance(BinarySearchTree* root)
{
	root->bFactor = height(root->right) - height(root->left);
	if (root->bFactor == -2)
	{
		BinarySearchTree* desc = root->left;
		if (desc->bFactor == -1)
			root = rightRotation(root);
		else
		{
			root->left = leftRotation(desc);
			root = rightRotation(root);
		}
	}
	else if (root->bFactor == 2)
	{
		BinarySearchTree* desc = root->right;
		if (desc->bFactor == -1)
			root->right = rightRotation(desc);
		root = leftRotation(root);
	}
	return root;
}
void printInfo(NodeInfo* info)
{
	if (info)
		printf("Code: %d - Name: %s, Salary: %f\n", info->code, info->name, info->salary);
	else
		printf("No data to print!");
}

BinarySearchTree* createNode(NodeInfo* emp)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = emp;
	node->left = node->right = NULL;
	node->bFactor = 0;
	return node;
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