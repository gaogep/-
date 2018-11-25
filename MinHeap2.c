#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MinValue -100

typedef struct HeapNode *Heap;
struct HeapNode {
	int *Array;
	int ElementNums;
	int Capacity;
};

Heap CreateHeap(int MaxSize);
void ShowHeap(Heap H);
bool IsFull(Heap H);
bool IsEmpty(Heap H);
void ScanfValue(Heap H);
void InsertValueToMin(int value, Heap H);
int DeleteFromMin(Heap H);
void BuildMinHeap(Heap H);
void AdjustNodeInMinHeap(Heap H, int TheLastFNode);


int main()
{
	
	Heap MinHeap = CreateHeap(15);
	ScanfValue(MinHeap);
	BuildMinHeap(MinHeap);
	DeleteFromMin(MinHeap);


	return 0;
}


void ShowHeap(Heap H)
{
	int i;
	for (i = 1; i < H->ElementNums+1; i++)
		printf("%d ", H->Array[i]);
}


Heap CreateHeap(int MaxSize)
{
	Heap H = malloc(sizeof(struct HeapNode));
	H->Array = malloc(sizeof(int) * (MaxSize+1));
	H->ElementNums = 0;
	H->Capacity = MaxSize;
	H->Array[0] = MinValue;
	return H;
}


void ScanfValue(Heap H)
{	
	int numbers, cnt;
	scanf("%d", &numbers);

	while (numbers > H->Capacity) {
		printf("The value must be smaller than %d : ", H->Capacity);
		scanf("%d", &numbers);
	}
	for (cnt = 1; cnt < numbers+1; cnt++) {
		scanf("%d", &H->Array[cnt]);
		H->ElementNums++;
	}
}


bool IsFull(Heap H)
{
	return H->ElementNums == H->Capacity;
}


bool IsEmpty(Heap H)
{
	return H->ElementNums == 0;
}


/**** 向最堆里插入元素使其为最小堆 ****/
void InsertValueToMin(int value, Heap H)
{
	int i;

	if (IsFull(H)) {
		printf("The Heap is Full.");
		exit(EXIT_FAILURE);
	}

	i = ++H->ElementNums;
	for (; H->Array[i/2] > value; i /= 2)
		H->Array[i] = H->Array[i/2];

	H->Array[i] = value;
}


/**** 从最小堆里删除元素 ****/
int DeleteFromMin(Heap H)
{
	int Parent, Child, Min, Temp;

	if (IsEmpty(H)) {
		printf("The Heap is Empty.");
		exit(EXIT_FAILURE);
	}

	Min = H->Array[1];
	Temp = H->Array[H->ElementNums--];

	for (Parent = 1; Parent*2 <= H->ElementNums; Parent = Child) {
		Child = Parent * 2;

		if (Child != H->ElementNums && H->Array[Child] > H->Array[Child+1])
			Child++;

		if (Temp < H->Array[Child])
			break;
		else
			H->Array[Parent] = H->Array[Child];
	}

	H->Array[Parent] = Temp;
	return Min;
}


/**** 将一个乱序二叉树调整为最小堆 ****/
void BuildMinHeap(Heap H)
{
	int i;
	for (i = H->ElementNums/2; i > 0; i--)
		AdjustNodeInMinHeap(H, i);
}


/**** 实际调整算法 ****/
void AdjustNodeInMinHeap(Heap H, int TheLastFNode)
{
	int Parent, Child, Temp;
	
	Temp = H->Array[TheLastFNode];

	for (Parent = TheLastFNode; Parent*2 <= H->ElementNums; Parent = Child) {
		Child = Parent * 2;

		if (Child != H->ElementNums && H->Array[Child] > H->Array[Child+1])
			Child++;

		if (H->Array[Child] > Temp)
			break;
		else
			H->Array[Parent] = H->Array[Child];
	}

	H->Array[Parent] = Temp;
}