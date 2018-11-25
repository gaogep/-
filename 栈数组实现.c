#include <stdio.h>
#include <stdlib.h>

#define MaxSize 5

typedef struct stack *Stack;
struct stack {
	int data[MaxSize];
	int top;
};

Stack Init();
void Push(Stack s, int value);
int Pop(Stack s);
int Isempty(Stack s);


int main()
{
	Stack s = Init();
	Push(s, 5);

	return 0;
}


Stack Init()
{
	Stack s = malloc(sizeof(struct stack));
	s->top = -1;
	return s;
}


void Push(Stack s, int value)
{
	if (s->top == MaxSize-1) {
		printf("Stack is full.");
		exit(EXIT_FAILURE);
	} else {
		s->data[++(s->top)] = value;
		return;
	}
}


int Pop(Stack s)
{
	if (s->top == -1) {
		printf("Stack is empty."); 
		exit(EXIT_FAILURE);
	} else {
		return (s->data[s->top--]);
	}
}


int Isempty(Stack s)
{
	return (s->top == -1);
}