/**
 * 开放地址法：一旦发生了散列冲突，就切换位置存放元素
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxTableSize 100

typedef enum { Legitimate, Empty, Deleted } EntryType;

typedef struct HashCell Cell;
sturct HashCell {
	int Value;
	int Info;
};

typedef struct HTB *HashTable;
struct HTB {
	int TableSize;
	Cell *Table;
};


HashTable CreateTable(int TableSize)
{
	int i;
	HashTable H;

	H = malloc(sizeof(struct HTB));
	// 此处确保散列表的最大长度是素数
	H->TableSize = NextPrime(TableSize);
	H->Table = malloc(sizeof(Cell) * H->TableSize);
	for (i = 0; i < H->TableSize; i++) H->Table[i].Info = Empty;

	return H;
}

// 返回大于 value 且不超过 MaxTableSize 的最小素数
int NextPrime(int value)
{
	int i, p = (value % 2)? value+2:value+1;

	while (p < MaxTableSize) {
		for (i = (int)sqrt(p); i > 2; i--) if (!(p%i)) break;
		if (i == 2) break;
		else p += 2;
	}

	return p;
}