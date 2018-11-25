#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *PtoTreeNode;
struct TreeNode {
	char NodeValue;
	PtoTreeNode LeftCh;
	PtoTreeNode RightCh;
};

PtoTreeNode CreateBinTree();       // 递归先序创建二叉树
void PreOrder(PtoTreeNode root);   // 递归先序遍历
void InOrder(PtoTreeNode root);    // 递归中序遍历
void PostOrder(PtoTreeNode root);  // 递归后序遍历


int main()
{
	PtoTreeNode T1 = CreateBinTree();
	printf("\n");
	PreOrder(T1);
	printf("\n");
	InOrder(T1);
	printf("\n");
	PostOrder(T1);
	
	return 0;
}


PtoTreeNode CreateBinTree()
{
	char value;
	PtoTreeNode treenode;
	printf("Input a value: ");
	scanf(" %c", &value);

	if (value == '#') {
		treenode = NULL;
	} else {
		treenode = malloc(sizeof(struct TreeNode));
		if (treenode == NULL) {
			printf("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		treenode->NodeValue = value;
		treenode->LeftCh = CreateBinTree();
		treenode->RightCh = CreateBinTree();
	}

	return treenode;
}


void PreOrder(PtoTreeNode root)
{
	if (root) {
		printf("%c ", root->NodeValue);
		PreOrder(root->LeftCh);
		PreOrder(root->RightCh);
	}
}


void InOrder(PtoTreeNode root)
{
	if (root) {
		InOrder(root->LeftCh);
		printf("%c ", root->NodeValue);
		InOrder(root->RightCh);
	}
}


void PostOrder(PtoTreeNode root)
{
	if (root) {
		PostOrder(root->LeftCh);
		PostOrder(root->RightCh);
		printf("%c ", root->NodeValue);
	}
}
