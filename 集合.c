#include <stdio.h>
#include <stdlib.h>

#define MaxSize 50

typedef struct {
	int Value;
	int Parent;   // 以集合中元素的个数 * -1 代表集合的根节点
} Set;

int FindRootSet(Set s[], int x);                 // 找到一个元素所在的集合
void UnionDifferentSet(Set s[], int x, int y);   // 将两个集合做并运算

int main()
{

	return 0;
}


int FindRootSet(Set s[], int x)
{
	int i;
	for (i = 0; i < MaxSize && s[i].Value != x; i++);
	if (i >= MaxSize) exit(EXIT_FAILURE);
	for (; s[i].Parent >= 0; i = s[i].Parent);
	return i;
}


void UnionDifferentSet(Set s[], int x, int y)
{
	int RootX, RootY;

	RootX = FindRootSet(s, x);
	RootY = FindRootSet(s, y);

	if (RootX < RootY) {         // 将元素个数少的集合并到元素个数多的集合中
		RootX += RootY;
		s[RootY].Parent = RootX;
	} else {
		RootY += RootX;
		s[RootX].Parent = RootY;
	}
}