#include <stdio.h>
#include <stdlib.h>


typedef struct node *PtrToNode;
struct node {
	int value;
	PtrToNode next;
};


typedef struct qnode *Quene;
struct qnode {
	PtrToNode front;
	PtrToNode rear;
};


Quene InitQuene(int x);


int main()
{
	Quene q = InitQuene(10);

	return 0;
}


Quene InitQuene(int x)
{
	PtrToNode new = malloc(sizeof(struct node));
	Quene q = malloc(sizeof(struct qnode));
	new->value = x;
	new->next = NULL;
	q->front = new;
	q->rear = q->front;
	return q;
}