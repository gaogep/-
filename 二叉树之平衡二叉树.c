#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *PtrToTreeNode;
struct TreeNode {
	int NodeValue;
	int Height;
	PtrToTreeNode LeftCh, RightCh;
};

int Height(PtrToTreeNode T);                            // 得到节点的高度
int Max(int x, int y);                                  // 求最大值
PtrToTreeNode Insert(int x, PtrToTreeNode T);           // 插入平衡二叉树
PtrToTreeNode SingleRotateWithLeft(PtrToTreeNode T);    // 左左旋转
PtrToTreeNode SingleRotateWithRight(PtrToTreeNode T);   // 右右旋转
PtrToTreeNode DoubleRotateWithLeft(PtrToTreeNode T);    // 左右旋转
PtrToTreeNode DoubleRotateWithRight(PtrToTreeNode T);   // 右左旋转
void ShowHead(PtrToTreeNode AvlTree);                   // 展示开头


int main()
{
 	PtrToTreeNode AvlTree = NULL;
 	AvlTree = Insert(88, AvlTree);
 	AvlTree = Insert(70, AvlTree);
 	AvlTree = Insert(61, AvlTree);
 	AvlTree = Insert(96, AvlTree);
 	AvlTree = Insert(120, AvlTree);
 	AvlTree = Insert(90, AvlTree);
 	AvlTree = Insert(65, AvlTree);
 	ShowHead(AvlTree);

	return 0;
}


int Height(PtrToTreeNode T)
{
	if (T == NULL)
		return -1;
	else
		return T->Height;
}


int Max(int x, int y)
{
	return (x>y)?x:y;
}


PtrToTreeNode Insert(int x, PtrToTreeNode T)
{
	if (T == NULL) {
		T = malloc(sizeof(struct TreeNode));
		if (T == NULL) {
			printf("Out of space");
			exit(EXIT_FAILURE);
		}
		T->NodeValue = x;
		T->Height = 0;
		T->LeftCh = T->RightCh = NULL; 
	}

	if (x < T->NodeValue) {
		T->LeftCh = Insert(x, T->LeftCh);
		if(Height(T->LeftCh) - Height(T->RightCh) == 2) {
			if (x < T->LeftCh->NodeValue)    // 如果麻烦节点在发现者左子树的左边 进行左旋调整
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T); // 否则麻烦节点必发现者在左子树的右边 进行左右旋调整
		}
	} else if (x > T->NodeValue) {
		T->RightCh = Insert(x, T->RightCh);
		if (Height(T->RightCh) - Height(T->LeftCh) == 2) {
			if (x > T->RightCh->NodeValue)
				T = SingleRotateWithRight(T); // 如果麻烦节点在发现者右子树的右边 进行右旋调整
			else
				T = DoubleRotateWithRight(T); // 否则麻烦节点必发现者在右子树的左边 进行左右旋调整
		}
	}

	T->Height = Max(Height(T->LeftCh), Height(T->RightCh)) + 1;
	return T;
}


PtrToTreeNode SingleRotateWithLeft(PtrToTreeNode T)
{
	PtrToTreeNode Temp;

	Temp = T->LeftCh;
	T->LeftCh = Temp->RightCh;
	Temp->RightCh = T;

	T->Height = Max(Height(T->LeftCh), Height(T->RightCh)) + 1;
	Temp->Height = Max(Height(Temp->LeftCh), T->Height) + 1;

	return Temp;
}


PtrToTreeNode SingleRotateWithRight(PtrToTreeNode T)
{
	PtrToTreeNode Temp;

	Temp = T->RightCh;
	T->RightCh = Temp->LeftCh;
	Temp->LeftCh = T;

	T->Height = Max(Height(T->LeftCh), Height(T->RightCh)) + 1;
	Temp->Height = Max(Height(Temp->RightCh), T->Height) + 1;

	return Temp;
}


PtrToTreeNode DoubleRotateWithLeft(PtrToTreeNode T)
{
	T->LeftCh = SingleRotateWithRight(T->LeftCh);
	return SingleRotateWithLeft(T);
}


PtrToTreeNode DoubleRotateWithRight(PtrToTreeNode T)
{
	T->RightCh = SingleRotateWithLeft(T->RightCh);
	return SingleRotateWithRight(T);
}


void ShowHead(PtrToTreeNode AvlTree)
{
	printf("%7d\n", AvlTree->NodeValue);
 	printf("  /      \\\n");
 	printf("%d   ", AvlTree->LeftCh->NodeValue);
 	printf("     %d", AvlTree->RightCh->NodeValue);
}