#include <stdio.h>
#include <stdlib.h>

typedef struct node *PtrToNode;
struct node {
	int value;
    PtrToNode next;
};


PtrToNode Attach(PtrToNode head, int number);
PtrToNode GenerateList(PtrToNode head);
void Print(PtrToNode P);
PtrToNode reverse_by_zpf(PtrToNode cur);
PtrToNode Reverse(PtrToNode head);

int main()
{	
	
	PtrToNode head = NULL;
	head = GenerateList(head);
	head = Reverse(head);
	//head = reverse_by_zpf(head);
	Print(head);

	return 0;
}


PtrToNode Attach(PtrToNode head, int number)
{
	PtrToNode new;
	new = malloc(sizeof(struct node));
    new->value = number;
    new->next = head;
    return new;
}


PtrToNode GenerateList(PtrToNode head)
{
	int i;
	for (i = 6; i > 0; i--)
		head = Attach(head, i);
	return head;
}


void Print(PtrToNode P)
{
	if (!P) {
		printf("NULL");
		return;
	}
	while (P) {
		printf("%p %d %p\n",P, P->value, P->next);
		P = P->next;
	}
}


// 反转链表自写 可以保证正确 但思考复杂了 ~ o(*￣▽￣*)o
PtrToNode reverse_by_zpf(PtrToNode cur)
{
	int K;
	PtrToNode old, head2, head3;
	scanf("%d", &K);
	if (K == 0) return cur;

	head2 = NULL;
	head2 = Attach(head2, cur->value);
	head3 = head2;
	K -= 1;
	old = cur;
	cur = cur->next;
	free(old);
	
	while (K--) {
		head2 = Attach(head2, cur->value);	
		old = cur;
		cur = cur->next;
		free(old);
	}

	head3->next = cur;
	return head2;
}


// 反转链表标准答案
PtrToNode Reverse(PtrToNode head)
{
	int k;
	scanf("%d", &k);
	if (k == 0 || k == 1) return head;
	PtrToNode Cur = head;
	PtrToNode Next = Cur->next;
	PtrToNode Temp = Next->next;
	
	while (k-1) {
		Next->next = Cur;
		Cur = Next;
		Next = Temp;

		if (!Next && !Temp) {
			head->next = NULL;
			return Cur;
		}                  // 当 K = 6 时 Next 和 Temp 均为 NULL, 再执行 Temp = Next->next; 就会退出，所以要叫一个判断

		Temp = Next->next; // 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面 看上面
		k--;	
	}

	head->next = Next;
	return Cur;
}