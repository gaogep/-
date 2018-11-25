#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode *PtrToSnode;
struct StackNode {
    int value;
    PtrToSnode next;
}; 

PtrToSnode Init();
PtrToSnode Push(PtrToSnode top, int value);
int Pop(PtrToSnode *top);
int Isempty(top);
void Destory(PtrToSnode *top);


int main()
{
    PtrToSnode top = Init();
    top = Push(top, 5);
    top = Push(top, 7);
    top = Push(top, 8);
    top = Push(top, 9);
    Pop(&top);

    return 0;
}


PtrToSnode Init()
{
	PtrToSnode t = NULL;
	return t;
}


PtrToSnode Push(PtrToSnode top, int value)
{
    PtrToSnode snew = malloc(sizeof(struct StackNode));
    snew->next = top;
    snew->value = value;
    return snew;
}


int Pop(PtrToSnode *top)
{
	if (!Isempty()) {
		printf("The Stack is empty");
		exit(EXIT_FAILURE);
	}
	
    int PopValue;
    PtrToSnode temp = (*top);
    PopValue = (*top)->value;
    (*top) = (*top)->next;
    free(temp);
    return PopValue;
}


int Isempty(top)
{
	return (top == NULL);
}


void Destory(PtrToSnode *top)
{
	while (*top) {
		PtrToSnode temp = (*top);
		(*top) = (*top)->next;
		free(temp);
	}
}