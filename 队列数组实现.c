#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef struct Qnode *Quene;
struct Qnode {
	int data[MaxSize];
	int front;
	int rear;
};


Quene CreateQuene();
void AddQuene(Quene Q, int value);
int DeleteFromQuene(Quene Q);
int IsEmpty(Quene Q);


int main()
{
	Quene q;
	q = CreateQuene();
	AddQuene(q, 5);
	AddQuene(q, 6);
	AddQuene(q, 7);
	AddQuene(q, 8);

	return 0;
}


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
		return 1;
	} else {
		Q->front = (Q->front+1) % MaxSize;
		return Q->data[Q->front];
	}
}


int IsEmpty(Quene Q)
{
	return Q->rear == Q->front;
}
