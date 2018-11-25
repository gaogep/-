#include <stdio.h>


void Swap(int *a, int *b)
{
	int t = *a; *a = *b; *b = t;
}


// 将n个元素的数组从根节点r开始调整为最大堆
void PercDown(int a[], int root, int n)
{
	int temp;
	int Parent, Child;

	temp = a[root];

	for (Parent = root; (Parent*2+1) < n; Parent = Child) {
		Child = Parent * 2 + 1;
		if (Child != n-1 && a[Child] < a[Child+1])
			Child++;
		if (a[Child] <= temp) break;
		else a[Parent] = a[Child];
	}

	a[Parent] = temp;
}


void HeapSort(int a[], int n)
{
	int i;

	// 注意了 这里的堆元素是从0开始的，并没有像之前
	// 建立最大堆或者最小堆的时候将0号元素设置为哨兵
	 
	//  这里将数组a从最后一个父节点开始调整为一个最大堆
	for (i = n/2 - 1; i >= 0; i--)
		PercDown(a, i, n);

	// 这里开始先把堆的规模减 1 然后把根节点位置的元素和最后一个位置的元素交换
	// 然后把剩余规模的堆调整成一个最大堆 依此类推
	for (i = n-1; i > 0; i--) {
		Swap(&a[0], &a[n-1]);
		PercDown(a, 0, i);
	}
}

// 堆排序整体思路 先把一个乱序数组调整成一个最大堆
// 然后交换头尾两个元素 再把堆的规模减 1
// 再从头节点开始把数组调整成最大堆 再次交换头尾两个元素 后面的以此类推

int main()
{

	return 0;
}
