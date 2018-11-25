#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 10

struct TreeNode {
	int left;
	int right;
};

struct Qnode {
	int data[MaxSize];
	int front;
	int rear;
};
typedef struct Qnode *Quene;

int BuildTree(int n, struct TreeNode T[]);
Quene CreateQuene();
void AddQuene(Quene Q, int value);
int DeleteFromQuene(Quene Q);
int IsEmpty(Quene Q);
void ShowData(int n, struct TreeNode T[]);
void LevelTraversal(struct TreeNode T[], int root);


int main()
{
	int n, Root;
	printf("Please input the number of nodes: ");
	scanf("%d", &n);
	struct TreeNode T[n];
	Root = BuildTree(n, T);
	printf("\n");
	LevelTraversal(T, Root);

	return 0;
}


// 二叉树相关函数
int BuildTree(int n, struct TreeNode T[])
{
	int i;
	int check[n];
	char L, R;
	
	memset(check, 0, sizeof(check));
	printf("\n");
	
	for (i = 0; i < n; i++) {
		printf("input a pair of values: ");
		scanf(" %c %c", &L, &R);
			
		if (L != '-') {
			T[i].left = L-'0';
			check[T[i].left] = 1;
		} else T[i].left = -1;
		
		if (R != '-') {
			T[i].right = R-'0';
			check[T[i].right] = 1;
		} else T[i].right = -1;
	}
	
	for (i = 0; i < n; i++)
		if (!check[i]) break;
			
	return i;
}


void LevelTraversal(struct TreeNode T[], int root)
{
	int temp, flg;
	Quene Q = CreateQuene();
	AddQuene(Q, root);

	while (!IsEmpty(Q)) {
		flg = 0;
		temp = DeleteFromQuene(Q);

		if (T[temp].left != -1) {
			AddQuene(Q, T[temp].left);
			flg++;
		}
		if (T[temp].right != -1) {
			AddQuene(Q, T[temp].right);
			flg++;
		}

		if (flg == 0) printf("%d ", temp);
	}
}


// 队列相关函数
Quene CreateQuene()
{
	Quene q = malloc(sizeof(struct Qnode));
	q->front = 0;
	q->rear = 0;
	return q;
}


void AddQuene(Quene Q, int value)
{
	if ((Q->rear+1) % MaxSize == Q->front){
		printf("The Quene is full!");
		return;
	}
	Q->rear = (Q->rear+1) % MaxSize;
	Q->data[Q->rear] = value;
}


int DeleteFromQuene(Quene Q)
{
	if (Q->rear == Q->front) {
		printf("The Quene is empty!");
		exit(EXIT_FAILURE);
	} else {
		Q->front = (Q->front+1) % MaxSize;
		return Q->data[Q->front];
	}
}


int IsEmpty(Quene Q)
{
	return Q->rear == Q->front;
}


// 展示数据
void ShowData(int n, struct TreeNode T[])
{
	printf("\n"); 
	int i;
	for (i = 0; i < n; i++) {
		printf("left:%2d | right:%2d\n", T[i].left, T[i].right);
	}
}
