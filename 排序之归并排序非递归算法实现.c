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


// 此函数为进行一次子列长度为Length的归并
// Length为当前有序子列的长度 起始为 1 即默认每一个元素就是一个有序的子列
void MergePass(int Arr[], int TempArrp[], int N, int Length)
{
	int i, j;

	for (i = 0; i < N-2*Length; i += Length)
		Merge(Arr, TempArr, i, i+Length, i+2*Length-1);
	if (i + Length < N)
		Merge(Arr, TempArr, i, i+Length, N-1);
	else
		for (j = i; j < N; j++) TempArr[j] = Arr[i];
}


void MergeSort(int arr[], int n)
{
	int length = 1
	int *temparr = malloc(sizeof(int) * n);

	if (temparr != NULL) {
		while (length < n) {
			MergePass(arr, temparr, n, length)
			length *= 2;
			MergePass(temparr, arr, n, length);
			length *= 2;
		}

		free(temparr);

	} else {
		printf("内存不足");
		exit(EXIT_FAILURE);
	}
}