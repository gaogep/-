#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HeapNode *Heap;
struct HeapNode {
	int capacity;
	int size;
	int *data;
};

#define MaxData 100

Heap CreateHeap(int MaxSize);    // 建立一个堆
bool IsFull(Heap H);             // 判断堆是否为满
bool IsEmpty(Heap H);	         // 判断堆是否为空
bool Insert(Heap H, int x);      // 向堆中插入元素
int DeleteMax(Heap H);


int main()
{
	Heap H = CreateHeap(10);
	Insert(H, 20);
	Insert(H, 14);
	Insert(H, 15);
	Insert(H, 16);
	Insert(H, 17);
	Insert(H, 25);


	return 0;
}


Heap CreateHeap(int MaxSize)
{
	Heap H = malloc(sizeof(struct HeapNode));
	H->data = malloc((MaxSize+1) * sizeof(int));
	H->size = 0;
	H->capacity = MaxSize;
	H->data[0] = MaxData;    // 定义哨兵为大于堆中所有可能元素的值

	return H;
}


bool IsFull(Heap H)
{
	return (H->size == H->capacity);
}


bool IsEmpty(Heap H)
{
	return (H->size == 0);
}


bool Insert(Heap H, int x)
{
	int i;

	if (IsFull(H)) {
		printf("The heap is full"); 
		exit(EXIT_FAILURE);
	}

	i = ++H->size;
	for (; H->data[i/2] < x; i /= 2)
		H->data[i] = H->data[i/2];
	H->data[i] = x;
}


int DeleteMax(Heap H)
{
	int Parent, Child;
	int Max, x;

	if (IsEmpty(H)) {
		printf("The heap is empty");
		exit(EXIT_FAILURE);
	}

	Max = H->data[1];      // 取出根节点存放的最大值
	x = H->data[H->size--];   // 取最后一个元素开始自下向上过滤节点 由于上边删掉了根节点 所以size要减去1
                           // Parent*2判断是否有左儿子 例如有三个节点的完全二叉树：
                           //  [   5   ] 
                           //  [ 3    2]  3的编号为2 如果有左儿子 其左儿子编号为 2*2=4 > 节点个数3 所以说明
                           //   这个完全二叉树 3这个节点没有左儿子  
	for (Parent = 1; Parent*2 <= H->size; Parent = Child) {
		Child = Parent * 2;
		// 试想，如果Child(子二叉树节点编号)==size 那么说明这个完全二叉树没有右儿子
		if (Child != H->size && H->data[Child] < H->data[Child+1])
			Child++;

		if (x >= H->data[Child]) // 如果此时临时节点比左右儿子中最大的那个还大，那就不需要调整了
			break;
		else                     // 如果临时节点比左右儿子中大的那个小，那就要互换位置
			H->data[Parent] = H->data[Child];
	}

	H->data[Parent] = x;         // 跳出循环，直接赋值
	return Max;
}


/*  建造最大堆  */
void BuildHeap(Heap H)
{
	int i;

	/* 从最后一个父节点开始 到根节点1 进行调整 */
	for (i = H->size/2; i > 0; i--)
		PerDown(H, i)
}


void PerDown(Heap H, int p)
{
	int Parent, Child;
	int x

	x = H->data[p];
	for (Parent = p; Parent*2 <= H->size; Parent = Child) {
		Child = Parent * 2;
		
		if (Child != H->size && H->data[Child] < H->data[Child+1])
			Child++;

		if (x >= H->data[Child])
			break;
		else                  
			H->data[Parent] = H->data[Child];
	}

	H->data[Parent] = x;
}