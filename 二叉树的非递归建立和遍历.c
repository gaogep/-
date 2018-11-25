#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef struct TreeNode *PtrToTNode;
struct TreeNode {
	char NodeValue;
	PtrToTNode LeftCh;
	PtrToTNode RightCh;
};

typedef struct stack *Stack;
struct stack {
	PtrToTNode temp[MaxSize];
	int top;
};

/**** 层序建立二叉树 ****/
void CreateBinTree(PtrToTNode *root);

/**** 栈相关函数 ****/
Stack InitStack();
int IsEmpty(Stack s);
void Push(Stack s, PtrToTNode T);
PtrToTNode Pop(Stack s) ;

/**** 二叉树非递归遍历 ****/
void PreOrderTraversal(PtrToTNode Root);
void InOrderTraversal(PtrToTNode Root);
void PostOrederTraversal_DoubleStack(PtrToTNode Root);

/**** 二叉树递归遍历 ****/
void PreOrder(PtrToTNode Root);
void InOrder(PtrToTNode Root);
void PostOrder(PtrToTNode Root);


int main()
{
	PtrToTNode Root = malloc(sizeof(struct TreeNode));
	CreateBinTree(&Root);

	// 先序遍历->递归非递归
	printf("\nPreOrder  (recursive): ");
	PreOrder(Root);
	printf("\nPreOrder  (non-recursive): ");
	PreOrderTraversal(Root);

	printf("\n");

	// 中序遍历->递归非递归
	printf("\nInOrder  (recursive): ");
	InOrder(Root);
	printf("\nInOrder  (non-recursive): ");
	InOrderTraversal(Root);

	printf("\n");

	// 后序遍历->递归非递归
	printf("\nPostOrder  (recursive): ");
	PostOrder(Root);
	printf("\nPostOrder  (non-recursive): ");
	// PostOrederTraversal_DoubleStack(Root);

	return 0;
}


/***** 层序建立二叉树 *****/
void CreateBinTree(PtrToTNode *root)
{
	char ch;
	printf("Input the value of Root node: ");
	scanf(" %c", &ch);
	printf("\n");

    /**
     * 1.判断根节点是否存在
     * 2.若根节点存在，则建立父层节点列表 (指针数组实现)
     * 3.若根节点不存在，函数异常返回
     */
	if (ch == '#') {
		printf("Root node is empty");
		exit(EXIT_FAILURE);
	} else {
		(*root)->NodeValue = ch;
		(*root)->LeftCh = NULL;
		(*root)->RightCh = NULL;
	}

	PtrToTNode *PtrToTNodePar = malloc(sizeof(PtrToTNode));
	PtrToTNodePar[0] = (*root);
	int ParCnt = 1;                                                      // 父层节点个数计数

	/**
	 * 1.根据父层列表中节点的个数 ParCnt 构造当前层列表中节点的个数 
	 *   因为当前层节点个数为父层节点个数 * 2
	 * 2.将父层节点列表与当前层节点列表联系起来  
	 */
	while (1) {
		int CurCnt = ParCnt * 2, NonEmptyTNodeCnt = 0;                   // 初始化当前层节点计数与非空节点计数
		PtrToTNode *PtrToTNodeCur = malloc(sizeof(PtrToTNode) * CurCnt); // 根据当前层节点计数构造当前层节点列表

		int i;
		for (i = 0; i < CurCnt; i++) {      // 以for循环读入当前层节点的数据
			printf("Input a value: ");
			scanf(" %c", &ch);
			if (ch != '#') {
				PtrToTNode new = malloc(sizeof(struct TreeNode));
				new->NodeValue = ch;
				new->LeftCh = NULL;
				new->RightCh = NULL;
				PtrToTNodeCur[NonEmptyTNodeCnt] = new;
				NonEmptyTNodeCnt++;         // 读入一个非空的节点 则非空节点计数加1

				if (i % 2 == 0) {           // 0为左子节点 1为右子节点 例如 / 0 % 2 = 0/ /1 % 2 = 1/
					PtrToTNodePar[i/2]->LeftCh = new;
				} else {
					PtrToTNodePar[i/2]->RightCh = new;
				}
			}
		}

		free(PtrToTNodePar);                // 释放父层节点列表
		PtrToTNodePar = PtrToTNodeCur;      // 将父层节点列表更新为当前层节点列表
		ParCnt = NonEmptyTNodeCnt;          // 将父层节点计数更新为当前层节点计数
		if (NonEmptyTNodeCnt == 0) break;   // 若当前层节点计数为0，则跳出循环，二叉树建立完毕
	}
}


/****** 栈相关函数 ******/
Stack InitStack()
{
	Stack s = malloc(sizeof(struct stack));
	s->top = -1;
	return s;
}


int IsEmpty(Stack s)
{
	return s->top == -1;
}


void Push(Stack s, PtrToTNode T)
{
	if (s->top == MaxSize) {
		printf("The Stack is full");
		exit(EXIT_FAILURE);
	} else {
		s->temp[++(s->top)] = T;
	}
}


PtrToTNode Pop(Stack s) 
{
	if (s->top == -1) {
		printf("The Stack is empty");
		exit(EXIT_FAILURE);
	} else {
		return (s->temp[s->top--]);
	}
}


/**** 二叉树非递归遍历 ****/
// 先序遍历
void PreOrderTraversal(PtrToTNode Root)
{
	PtrToTNode T = Root;
	Stack s = InitStack();

	while (T || !IsEmpty(s)) {
		while (T) {
			printf("%c ", T->NodeValue);
			Push(s, T);
			T = T->LeftCh;
		}	

		if (!IsEmpty(s)) {
			T = Pop(s);
			T = T->RightCh;
		}
	}
}


// 中序遍历
void InOrderTraversal(PtrToTNode Root)
{
	PtrToTNode T = Root;
	Stack s = InitStack();

	while (T || !IsEmpty(s)) {
		while (T) {
			Push(s, T);	
			T = T->LeftCh;
		}	

		if (!IsEmpty(s)) {
			T = Pop(s);
			printf("%c ", T->NodeValue);
			T = T->RightCh;
		}
	}
}


// 后序遍历 —> 利用双栈
void PostOrederTraversal_DoubleStack(PtrToTNode Root)
{
	PtrToTNode T = Root;
	Stack s1 = InitStack();
	Stack s2 = InitStack();

	while (T || !IsEmpty(s1)) {
		while (T) { 
			Push(s1, T);
			Push(s2, T);
			T = T->RightCh;
		}

		if (!IsEmpty(s1)) {
			T = Pop(s1);
			T = T->LeftCh;
		}
	}

	while (!IsEmpty(s2)) {
		T = Pop(s2);
		printf("%c ", T->NodeValue);
	}
}


/**** 二叉树递归遍历 ****/
//先序遍历
void PreOrder(PtrToTNode Root)
{
	if (Root) {
		printf("%c ", Root->NodeValue);
		PreOrder(Root->LeftCh);
		PreOrder(Root->RightCh);
	}
}


//中序遍历
void InOrder(PtrToTNode Root)
{
	if (Root) {
		InOrder(Root->LeftCh);
		printf("%c ", Root->NodeValue);
		InOrder(Root->RightCh);
	}
}


//后序遍历
void PostOrder(PtrToTNode Root)
{
	if (Root) {
		PostOrder(Root->LeftCh);
		PostOrder(Root->RightCh);
		printf("%c ", Root->NodeValue);
	}
}
