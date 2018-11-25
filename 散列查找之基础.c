#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXTABLESIZE 10000

typedef struct HashNode *HashTable;
struct HashNode {
	int TableSize;
	int *Table;
};

HashTable CreateTable(int TableSize);
int NextPrime(int value);
int HashFunc(int key, HashTable H);
int Find(int key, HashTable H);
bool Insert(int key, HashTable H);
int isPrime(int num);

int main()
{
	HashTable H = CreateTable(4);

	return 0;
}


int isPrime(int Num)
{
    int PrimeFlg = 1, Judge = 2;
    for (; Judge*Judge <= Num; Judge++)
        if(Num % Judge == 0) { PrimeFlg = 0; break; }   
    return PrimeFlg;
}


int NextPrime(int value)
{
	if (isPrime(value)) return value;
	while (value < MAXTABLESIZE)
		{ if (isPrime(value)) break; else value++; }
	return value;
}


HashTable CreateTable(int TableSize)
{
	int i; TableSize = NextPrime(TableSize); 
	HashTable H = malloc(sizeof(struct HashNode));
	H->TableSize = TableSize;
	H->Table = malloc(sizeof(int) * TableSize);
	for (i = 0; i < TableSize; i++) H->Table[i] = 0;
	printf("A HashTable with %d cells has been created\n", TableSize);
	return H;
}


int HashFunc(int key, HashTable H)
{
	return key % H->TableSize;
}


int Find(int key, HashTable H)
{
	int index = HashFunc(key, H);
	while (H->Table[index] != 0 
		&& index < H->TableSize) index += 1;
	return index;
}


bool Insert(int key, HashTable H)
{
	int index = Find(key, H);
	if (H->Table[index] == 0) {
		H->Table[index] = key;
		return true;
	} else {
		return false;
	}
}
