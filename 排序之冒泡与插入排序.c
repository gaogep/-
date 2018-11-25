void BubbleSort(int a[], int n)
{
	int flg;
	// 从第一个元素开始两两比较，每比较一轮，减少一个元素
	for (RestEleNums = n-1; RestEleNums >= 0; RestEleNums--) {
		flg = 0;
		for (i = 0; i < RestEleNums; i++) 
			if (a[i] > a[i+1]) {
				Swap(&a[i], &a[i+1]);
				flg = 1;
			}

		// 如果全程无交换
		if (flg == 0) break;
	}
}


void Swap(int *a, int *b)
{
	int t = *a; *a = *b; *b = t;
}


void InsertionSort(int a[], int n)
{
	int rear, front, temp;

	// 从 1号元素开始与已有的 0号元素开始比较
	for (rear = 1; rear < n; rear++) {
		temp = a[rear];
		for (front = rear; front > 0 && a[front-1] > temp; front--) 
			a[front] = a[front-1];
		a[front] = temp;
	}
}