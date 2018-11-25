// 选出基准元素
int MedianThree(int Arr[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (Arr[Left] > Arr[Center]) Swap(&Arr[Center], &Arr[Right]);
	if (Arr[Left] > Arr[Right])  Swap(&Arr[Left], &Arr[Right]);
	if (Arr[Center] > Arr[Right]) Swap(&Arr[Center], &Arr[Right]);

	// 将基准 pivot 放到倒数第二个位置
	Swap(&Arr[Center], &Arr[Right-1]);

	// 返回基准 pivot
	return Arr[Right-1];
}


void quicksort(int Arr[], int Left, int Right)
{
	int Pivot, Cutoff, Low, High;

	// 如果元素充分多 进入快速排序 否则利用插入排序即可
	if (Cutoff <= Right - Left) {
		Pivot = MedianThree(Arr, Left, Right);

		Low = Left;
		High = Right-1;

		// 子集划分
		while (1) {
			while (Arr[++Low] < Pivot);
			while (Arr[--High]) > Pivot);

			if (Low < High)  {
				Swap(&Arr[Low], &Arr[High]);
			} else break;
		}

		// 把 Pivot 放到正确的位置
		Swap(&Arr[Low], &Arr[Right-1]);

		// 递归调用快速排序
		QuickSort(Arr, Left, Low-1);
		QuickSort(Arr, Low+1, Right);

	} else InsertionSort(Arr+Left, Right-Left+1); // 元素太少 进行简单排序

}