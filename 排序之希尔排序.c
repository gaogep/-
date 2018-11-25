// 希尔排序是一种特殊的插入排序
void ShellSort(int a[], int n)
{
	int Si, D, P, i;
	int Temp;

	// 定义增量序列 初始的增量序列不能超过待排序列的长度
	int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

	for (Si = 0; Sedgewick[Si] >= n; Si++);

	// 插入排序
	 for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
         for ( P=D; P<N; P++ ) { 
             Temp = A[P];
             for ( i=P; i>=D && A[i-D]>Temp; i-=D )
                 A[i] = A[i-D];
             A[i] = Temp;
         }
}