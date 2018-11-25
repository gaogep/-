#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxTableSize 10000

typedef struct Node *PtrToNode;
typedef PtrToNode *PtrToList;
struct Node {
	char PhoneNumber[12];
	int cnt;
	PtrToNode Next;
};

typedef struct HTB *HashTable;
struct HTB {
	int TableSize;
	PtrToList Table;
};

PtrToNode Find(char number[], HashTable H);
PtrToNode Attach(PtrToNode head, char number[]);
HashTable CreateTable(int size);
int NextPrime(int value);
int Hash(char number[], int size);
bool  Insert(char number[], HashTable H);


int main()
{
	HashTable H; int CallNums, size, i;
	char number1[12], number2[12];

	scanf("%d", &CallNums);
	size = NextPrime(CallNums*2);
	H = CreateTable(size);

	for (i = 0; i < CallNums; i++) {
		scanf("%s %s", number1, number2);
		Insert(number1, H); Insert(number2, H);
	}

	return 0;
}


// 建立散列表
HashTable CreateTable(int size)
{
	HashTable H = malloc(sizeof(struct HTB));
	H->TableSize = size;
	H->Table = malloc(sizeof(PtrToNode) * size);

	int i;
	for (i = 0; i < size; i++)
		H->Table[i] = NULL;

	return H;
}


// 计算素数
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


// 链表添加项
PtrToNode Attach(PtrToNode head, char number[])
{
	PtrToNode NewNode = malloc(sizeof(struct Node));
	NewNode->Next = head;
	strcpy(NewNode->PhoneNumber, number);
	return NewNode;
}


// 散列函数
int Hash(char number[], int size)
{
	int i, sum, cnt = 10000;

	for (i = 6; i < 11; i++) {
		sum += (number[i] - '0') * cnt;
		cnt /= 10;
	}

	return sum % size;
}


//散列查找
PtrToNode Find(char number[], HashTable H)
{
	int Pos = Hash(number, H->TableSize);
	PtrToNode temp = H->Table[Pos];

	while (temp) {
		if (strcmp(temp->PhoneNumber, number)) break;
		else temp = temp->Next;
	}

	return temp;
}


//插入散列表
bool Insert(char number[], HashTable H)
{
	PtrToNode Loc; int Pos;

	Loc = Find(number, H);

	if (!Loc) {
		Pos = Hash(number, H->TableSize);
		H->Table[Pos] = Attach(H->Table[Pos], number);
		return true;
	} else {
		printf("KeyWord already exists");
		return false;
	}
}