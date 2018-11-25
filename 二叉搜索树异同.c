#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *PtrToTreeNode;
struct TreeNode {
	int NodeValue;
	int flg;
	PtrToTreeNode LeftCh;
	PtrToTreeNode RightCh;
};

void PreOrder(PtrToTreeNode Root);
PtrToTreeNode Insert(PtrToTreeNode T, int x);
PtrToTreeNode MakeTree(int NodeNumbers);
int Check(PtrToTreeNode T, int x);
int Judge(PtrToTreeNode T, int NodeNumbers);
void Reset(PtrToTreeNode T);
void Free(PtrToTreeNode T);


int main()
{
	PtrToTreeNode T;
	int i;
	int NodeNumbers;
	int TreeNumbers;

	while (1) {
		scanf("%d %d", &NodeNumbers, &TreeNumbers);
		T = MakeTree(NodeNumbers);

		for (i = 0; i < TreeNumbers; i++); {
			if (Judge(T, NodeNumbers)) printf("Yes");
			else printf("No");
			Reset(T);
		}
		
		Free(T);
	}

	return 0;
}


void PreOrder(PtrToTreeNode Root)
{
	if (Root) {
		printf("%d ", Root->NodeValue);
		PreOrder(Root->LeftCh);
		PreOrder(Root->RightCh);
	}
}


PtrToTreeNode Insert(PtrToTreeNode T, int x)
{
	if (!T) {
		T = malloc(sizeof(struct TreeNode));
		T->LeftCh = NULL;
		T->RightCh = NULL;
		T->NodeValue = x;
		T->flg = 0;
	} else {
		if (x > T->NodeValue) {
			T->RightCh = Insert(T->RightCh, x);
		} else if (x < T->NodeValue) {
			T->LeftCh = Insert(T->LeftCh, x);
		}
	}

	return T;
}


PtrToTreeNode MakeTree(int NodeNumbers)
{
	int i, x;
	PtrToTreeNode T = NULL;

	for (i = 0; i < NodeNumbers; i++) {
		scanf("%d", &x);
		T = Insert(T, x);
	}

	return T;
}


int Check(PtrToTreeNode T, int x)
{
	if (T->flg) {                                               // 判断根节点是否碰到过
		if (x > T->NodeValue) return Check(T->RightCh, x);      // 大于往右走
		else if (x < T->NodeValue) return Check(T->LeftCh, x);  // 小于往左走
		else return 0;                                          // 相等直接跳出，不允许有重复的
	} else {
		if (x == T->NodeValue) {
			T->flg = 1;
			return 1;
		} else return 0;
	}
}


/**
 * 注意:
 * 加flag的目的是让程序把数字读完 不做check 
 * 如果数不读完 判断第二轮的时候 上一轮没读完的数
 * 会继续进行读入 这样就出bug了
 * 
 */
int Judge(PtrToTreeNode T, int NodeNumbers)
{
	int x, i, flag = 0;                
	scanf("%d", &x);

	if (T->NodeValue != x) flag = 1;
	else T->flg = 1;

	for (i = 1; i < NodeNumbers-1; i++) {
		scanf("%d", &x);
		if (!flag && !Check(T, x)) flag = 1;
	}

	if (flag) return 0;
	else return 1;
}


void Reset(PtrToTreeNode T)
{
	if (T->LeftCh) Reset(T->LeftCh);
	if (T->RightCh) Reset(T->RightCh);
	T->flg = 0;
}


void Free(PtrToTreeNode T)
{
	if (T->LeftCh) Free(T->LeftCh);
	if (T->RightCh) Free(T->RightCh);
	free(T);
}