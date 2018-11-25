// 将两个有序的子列归并成一个有序的子列
void Merge(int Arr[], int TempArr[], int LeftStart, int RightStart, int RightEnd)
{
	int i;
	int LeftEnd = RightStart - 1;
	int ElementNums = RightEnd - LeftStart + 1;
	int TempStart = LeftStart;

	while (LeftStart <= LeftEnd && RightStart <= RightEnd) {
		if (Arr[LeftStart] <= Arr[RightStart]) TempArr[TempStart++] = Arr[LeftStart++];
		else TempArr[TempStart] = Arr[RightStart++];
	}

	while (LeftStart <= LeftEnd) TempArr[TempStart++] = Arr[LeftStart++];
	while (RightStart <= RightEnd) TempArr[TempStart] = Arr[RightStart++];

	// 把排好序的数组倒回去
	for (i = 0; i < ElementNums; i++, RightEnd--) Arr[RightEnd] = TempArr[RightEnd];
} 


// 核心递归排序函数
void Msort(int Arr[], int TempArr[], int LeftStart, int RightEnd)
{
	int Center;

	if (LeftStart < RightEnd) {
		Center = (LeftStart + RightEnd) / 2;
		Msort(Arr, TempArr, LeftStart, Center);
		Msort(Arr, TempArr, Center+1, RightEnd);
		Merge(Arr, TempArr, LeftStart, Center+1, RightEnd);
	}
}


// 递归归并排序封装好的函数
void MergeSort(int arr[], int n)
{
	int *temparr;
	temparr = malloc(sizeof(int) * n);

	if (temparr != NULL) {
		Msort(arr, temparr, 0, n-1);
		free(temparr);
	} else {
		printf("内存不足");
		exit(EXTI_FAILURE);
	}
}