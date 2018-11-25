#include <stdio.h>
#include <stdlib.h>

#define HMaxSize 20

typedef struct HeapNode *PtrToHeap;
struct HeapNode {
	int Capacity;
	int ElementNums;
	int *HeapArray;
};

/* 堆相关函数 */
PtrToHeap InitHeap();
bool IsFull(PtrToHeap H);
bool IsEmpty(PtrToHeap H);
int OutMinHeap(PtrToHeap H);


int main()
{
	return 0;
}


/* 堆相关函数 */
PtrToHeap InitHeap()
{
	PtrToHeap H = malloc(sizeof(struct HeapNode));
	H->HeapArray = malloc(sizeof(int) * HMaxSize+1);
	H->HeapArray[0] = -10;
	H->Capacity = HMaxSize;
	H->ElementNums = 0;
	return H;
}


bool IsFull(PtrToHeap H)
{
	return H->ElementNums == H->Capacity;
}


bool IsEmpty(PtrToHeap H)
{
	return H->ElementNums == 0;
}


void InsertToMinHeap(int Value, PtrToHeap H)
{
	if (IsFull(H)) {
		printf("The Heap is Full.");
		exit(EXIT_FAILURE);
	}

	int n = ++H->ElementNums;
	for (; H->HeapArray[n/2] > Value; n /= 2)
		H->HeapArray[n] = H->HeapArray[n/2];
	H->HeapArray[n] = Value;
}


int OutMinHeap(PtrToHeap H)
{
	if (IsEmpty(H)) {
		printf("The Heap is Empty");
		exit(EXIT_FAILURE);
	}

	int Parent, Child, Min, Temp;
	Min = H->HeapArray[1];
	Temp = H->HeapArray[H->ElementNums--];

	for (Parent = 1; Parent * 2 <= H->ElementNums; Parent = Child) {
		Child = Parent * 2;
		if (Child != H->ElementNums && H->HeapArray[Child+1] < H->HeapArray[Child])
			Child++;

		if (H->HeapArray[Child] > Temp)
			break;
		else
			H->HeapArray[Parent] = H->HeapArray[Child];
	}

	H->HeapArray[Parent] = Temp;
	return Min;
}