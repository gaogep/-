#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *PtrToTreeNode;
struct TreeNode {
	int NodeValue;
	PtrToTreeNode LeftCh;
	PtrToTreeNode RightCh;
};

PtrToTreeNode Find_NonRecursive(PtrToTreeNode T, int x);
PtrToTreeNode Find_Recursive(PtrToTreeNode T, int x);
PtrToTreeNode FindMin_NonRecursive(PtrToTreeNode T);
PtrToTreeNode FindMin_Recursive(PtrToTreeNode T);
PtrToTreeNode Insert(PtrToTreeNode T, int x);
PtrToTreeNode DeleteNode(PtrToTreeNode T, int x);


int main()
{
	PtrToTreeNode T = NULL;
	T = Insert(T, 1);


	return 0;
}


// 非递归查找节点
PtrToTreeNode Find_NonRecursive(PtrToTreeNode T, int x)
{
	while (T) {
		if (x > T->NodeValue) {
			T = T->RightCh;
		} else if (x < T->NodeValue) {
			T = T->LeftCh;
		} else {
			return T;
		}
	}

	return NULL;
}


// 递归查找节点
PtrToTreeNode Find_Recursive(PtrToTreeNode T, int x)
{
	if (!T) return NULL;
	if (x > T->NodeValue) {
		return Find_Recursive(T->RightCh, x);
	} else if (x < T->NodeValue) {
		return Find_Recursive(T->LeftCh, x);
	} else {
		return T;
	}
}


//非递归查找最小值
PtrToTreeNode FindMin_NonRecursive(PtrToTreeNode T)
{
	if (T) 
		while (T->LeftCh) T = T->LeftCh;
	return T;
}


// 递归查找最小值
PtrToTreeNode FindMin_Recursive(PtrToTreeNode T)
{
	if (!T) {                    // 一开始如果根节点为空，那么直接返回
		return NULL;
	} else if (!T->LeftCh) {     // 如果这个节点的左子树为空 那么就找到了最小值 直接返回
		return T;
	} else {
		return FindMin_Recursive(T->LeftCh);   // 左子树不为空 继续递归查找
	}
}


// 递归插入值
PtrToTreeNode Insert(PtrToTreeNode T, int x)
{
	if (!T) {                                    // 原树为空，新建一棵树
		T = malloc(sizeof(struct TreeNode));
		T->NodeValue = x;
		T->LeftCh = NULL;
		T->RightCh = NULL;
	} else {                                     // 开始找要插入元素的位置
		if(x > T->NodeValue) {                
			T->RightCh = Insert(T->RightCh, x);  // 递归插入右子树
		} else if (x < T->NodeValue) {
			T->LeftCh = Insert(T->LeftCh, x);    // 递归插入左子树
		}
	}

	return T;
}


 /*
 * 删除节点考虑三种情况： 
 * 1.删除叶节点->直接删除—>将其父节点指针置为NULL
 * 2.要删除的节点只有一个孩子节点->将其父节点的指针指向要删除节点的孩子节点
 * 3.要删除的节点有左右两棵子树，用另一节点替代被删除的节点 分两种情况：
 *   <1>.右子树的最小元素    <2>.左子树的最大元素
 */
PtrToTreeNode DeleteNode(PtrToTreeNode T, int x)
{
	PtrToTreeNode Temp;
	if (!T) {
		printf("The Node is empty");
		return T;
	} else if (x < T->NodeValue) {
		T->LeftCh = DeleteNode(T->LeftCh, x);                   // 左子树递归删除
	} else if (x > T->NodeValue) {
		T->RightCh = DeleteNode(T->RightCh, x);                 // 右子树递归删除
	} else {								                    // 找到了要删除的节点
		if (T->LeftCh && T->RightCh) {                          // 被删除的节点有左右两个子节点
			Temp = FindMin_Recursive(T->RightCh);               // 在右子树找最小(或左子树最大)的元素填充节点
			T->NodeValue = Temp->NodeValue;                     // 填充节点
			T->RightCh = DeleteNode(T->RightCh, T->NodeValue);  // 删除节点右子树中的最小元素
		} else {                                                // 被删除的节点有一个或无子节点
			Temp = T;
			if (!T->LeftCh) {                  // 有右孩子或无子节点
				T = T->RightCh;
			} else if (!T->RightCh) {          // 有左孩子或无子节点
				T = T->LeftCh;
			}
			free(Temp);
    	}  
    }

    return T;                             
}