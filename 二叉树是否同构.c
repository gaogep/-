#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxTree 10
#define Null -1

struct TreeNode {
	char NodeName;
	int left;
	int right;
} T1[MaxTree], T2[MaxTree];

int BuildTree(struct TreeNode T[]);
int IsIsomorphic(int R1, int R2);


int main()
{
	int R1, R2;
	R1 = BuildTree(T1);

	return 0;
}


int BuildTree(struct TreeNode T[])
{
	int N, i, Root;
	char L, R;
	printf("Please input the number of nodes: ");
	scanf("%d", &N);
	int check[N];

	memset(check, 0, sizeof(check));
	printf("\n");

	if (N) {
		for (i = 0; i < N; i++) {
			printf("Please input < NodeName | left | right >: ");
			scanf(" %c %c %c", &T[i].NodeName, &L, &R);
			if (L != '-') {
				T[i].left = L - '0';
				check[T[i].left] = 1;
			} else T[i].left = Null;

			if (R != '-') {
				T[i].right = R - '0';
				check[T[i].right] = 1;
			} else T[i].right = Null;
		}

		for (i = 0; i < N; i++)
			if (!check[i]) break;
		Root = i;

		int flg;
		for (i = 0; i < N; i++) {
			if (check[i] == 0) flg++;
		}
		if (flg == N) Root = Null;
	}

	return Root;
}


int IsIsomorphic(int R1, int R2)
{
	if ((R1 == Null) && (R2 == Null)) // 两棵树都是空的 同构
		return 1;

	if (((R1 != Null) && (R2 == Null)) || ((R1 == Null) && (R2 != Null))) // 两棵树中一棵树是空的 肯定不同构
		return 0;

	if (T1[R1].NodeName != T2[R2].NodeName) // 根节名点不同 肯定不同构
		return 0;

	if ((T1[R1].left == Null) && (T2[R2].left == Null)) // 判断左右节点情况 如果左节点为空 递归判断右节点
		return IsIsomorphic(T1[R1].right, T2[R2].right);

	if ((T1[R1].left != Null) && (T2[R2].left != Null) && (T1[T1[R1].left].NodeName) == (T2[T2[R2].left].NodeName)) // 若左边的节点不空 判断节点名是否相同
		return (IsIsomorphic(T1[R1].left, T2[R2].left) && IsIsomorphic(T1[R1].right, T2[R2].right)); // 如果节点名相同 左左右右判别
	else
		return (IsIsomorphic(T1[R1].left, T2[R2].right) && IsIsomorphic(T1[R1].right, T2[R2].left)); // 如果节点名不同  1左2右  1右2左  判别
}