/*
 * --------------------------------------------------
 * 集合的简化表示，将集合中的元素映射为一个整型数组的索引
 * 如这两个集合：    2        6
 * 				  /  \     /  \
 * 		         5    4   0    1
 * 		             /
 * 		           3
 * --------------------------------------------------
 * 可以用这样一个数组来表示：
 * 索引: [0] [1] [2] [3] [4] [5] [6]
 * 数组: {6,  6, -4,  4,  2,  2, -3}
 * --------------------------------------------------
 */

#include <stdio.h>

void Initialization(int Set[], int SetElementNums);
int FindRootSet(int Set[], int Value);
int FindRootSet_PathCompression(int Set[], int Value); // 路径压缩查找算法
void UnionDifferentSet(int Set[], int RootX, int RootY);
void Input_Connections(int Set[]);
void Check_Connections(int Set[]);
void Check_NetWork(int Set[], int SetElementNums);
void ShowData(int Set[], int SetElementNums);

int main()
{	
	int SetElementNums;
	printf("Please determine the number of elements: ");
	scanf("%d", &SetElementNums);

	int Set[SetElementNums];
	char instruction;
	Initialization(Set, SetElementNums);

	do {
		printf("Input a instruction now: ");
		scanf(" %c", &instruction);

		switch (instruction) {
			case 'I': Input_Connections(Set); break;
			case 'C': Check_Connections(Set); break;
			case 'S': Check_NetWork(Set, SetElementNums); break;
		}

	} while (1); //instruction != 'S'

	return 0;
}


void Input_Connections(int Set[])
{
	int x, y;
	int root1, root2;
	printf("Input 2 Nodes: ");
	scanf("%d %d", &x, &y);
	root1 = FindRootSet(Set, x-1);
	root2 = FindRootSet(Set, y-1);
	if (root1 != root2) UnionDifferentSet(Set, root1, root2);
}


void Check_Connections(int Set[])
{
	int x, y;
	int set1, set2;
	printf("Input the 2 Nodes you want to check: ");
	scanf("%d %d", &x, &y);
	set1 = FindRootSet(Set, x);
	set2 = FindRootSet(Set, y);
	if (set1 == set2) printf("Yes\n");
	else printf("No\n");
}


void Check_NetWork(int Set[], int SetElementNums)
{
	int i = 0, counter = 0;
	for (; i < SetElementNums; i++) {
		if (Set[i] < 0) counter++;
	}
	ShowData(Set, SetElementNums);
	if (counter == 1) printf("The NetWork is connected.\n");
	else printf("There are %d components.\n", counter);
}


void Initialization(int Set[], int SetElementNums)
{
	int i;
	for (i = 0; i < SetElementNums; i++)
		Set[i] = -1;
}


int FindRootSet(int Set[], int Value)
{
	while (Set[Value] > 0) Value = Set[Value];
	return Value;
}


/* 查找之路径压缩算法 */ /* 缩短查找路径 在查找量极大的时候提高查找的速度 */
int FindRootSet_PathCompression(int Set[], int Value)
{
	if (Set[Value] < 0) 
		return Value;
	else          // 注意此处为尾递归，会在编译的时候自动被优化为循环           
		return Set[Value] = FindRootSet_PathCompression(Set, Set[Value]);
}


void UnionDifferentSet(int Set[], int RootX, int RootY)
{
    if (Set[RootX] < Set[RootY]) {
        Set[RootX] += Set[RootY];
        Set[RootY] = RootX;
    } else {
        Set[RootY] += Set[RootX];
        Set[RootX] = RootY;
    }
}


void ShowData(int Set[], int SetElementNums)
{
	int i;
	for (i = 0; i < SetElementNums; i++)
		printf("%d ", Set[i]);
	printf("\n");
}