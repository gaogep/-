#include <stdio.h>
#include <stdlib.h>


typedef struct Node *PtrToNode;
struct Node {
    int Data;
    PtrToNode Next;
};
typedef PtrToNode List;


List Read();
List AddToList(List P, int x);
void Print(List P);
List Merge(List *l1, List *l2);


int main()
{
	List L1, L2, L;

	L1 = Read();
	L2 = Read();
	L = Merge(&L1, &L2);
	Print(L);
	Print(L1);
	Print(L2);

	return 0;
}


List Read()
{
	int x, n;
	List P = NULL;
	scanf("%d", &n);

	while (n--) {
		scanf("%d", &x);
		P = AddToList(P, x);
	}

	return P;
}


List AddToList(List P, int x)
{
	List pnew;
	pnew = malloc(sizeof(struct Node));
	pnew->Data = x;
	pnew->Next = P;
	return pnew;
}


void Print(List P)
{
	if (!P) {
		printf("NULL\n");
		return;
	}

	while (P) {
		printf("%d ", P->Data);
		P = P->Next;
	}
    
	printf("\n");
}


List Merge(List *l1, List *l2)
{
	List pmerge;
	pmerge = NULL;

	while ((*l1) && (*l2)) {
		if ((*l1)->Data > (*l2)->Data) {
			pmerge = AddToList(pmerge, (*l1)->Data);
			(*l1) = (*l1)->Next;
		} else {
			pmerge = AddToList(pmerge, (*l2)->Data);
			(*l2) = (*l2)->Next;
		}
	}

	if ((*l1) == NULL) {
		while ((*l2)) {
			pmerge = AddToList(pmerge, (*l2)->Data);
			(*l2) = (*l2)->Next;
		}
	} else {
		while ((*l1)) {
			pmerge = AddToList(pmerge, (*l1)->Data);
			(*l1) = (*l1)->Next;
		}
	}

	return pmerge;
}
