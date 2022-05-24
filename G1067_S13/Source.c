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
	short bfactor;
}BinarySearchTree;
#define LINE_BUFFEER 1024

/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
BinarySearchTree* createNode(NodeInfo*);
void printInfo(NodeInfo*);
/*functions signatures for BST-AVL operations*/
BinarySearchTree* rebalance(BinarySearchTree*);
int height(BinarySearchTree*);
void insertBST(BinarySearchTree**, NodeInfo*);
BinarySearchTree* LRP(BinarySearchTree*);
BinarySearchTree* RRP(BinarySearchTree*);
short balanceFactor(BinarySearchTree*);
BinarySearchTree* rebalance(BinarySearchTree*);
void preorder_PLR(BinarySearchTree*);
void inorder_LPR(BinarySearchTree*);
int height(BinarySearchTree*);

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
		//short lvl = 3;
		//printLevel(bTree, lvl);

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
BinarySearchTree* LRP(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	return desc;
}
BinarySearchTree* RRP(BinarySearchTree* pivot)
{
	BinarySearchTree* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	return desc;
}
short balanceFactor(BinarySearchTree* root)
{
	return height(root->right) - height(root->left);
}
BinarySearchTree* rebalance(BinarySearchTree* root)
{
	root->bfactor = balanceFactor(root);
	if (root->bfactor == -2)
	{
		BinarySearchTree* desc = root->left;
		if (desc->bfactor == -1)
			root = RRP(root);//RRP
		else
		{
			//LRP->RRP
			root->left = LRP(desc);
			root = RRP(root);
		}
	}
	else if (root->bfactor == 2)
	{
		BinarySearchTree* desc = root->right;
		if (desc->bfactor == 1)
			root = LRP(root);//LRP
		else
		{
			//RRP -> LRP
			root->right = RRP(desc);
			root = LRP(root);
		}
	}
	return root;
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
int height(BinarySearchTree* root)
{
	if (root)
		return 1 + max(height(root->right), height(root->left));
	else
		return 0;
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
	node->bfactor = 0;
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