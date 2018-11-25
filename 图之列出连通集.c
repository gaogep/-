#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20

int VisitedDFS[MaxSize] = {0};
int VisitedBFS[MaxSize] = {0};

typedef struct Edge *PtrToEdge;
struct Edge {
	int VertexS, VertexE;
};

typedef struct AdjNode *PtrToAdjNode;
struct AdjNode {
	int NodeNumber;
	PtrToAdjNode Next;
};

typedef struct TableNode {
	PtrToAdjNode First;
} AdjTable;

typedef struct Graph *PtrToGraph;
struct Graph {
	int VertexNums;
	int EdgeNums;
	AdjTable Table[MaxSize];
};

typedef struct QueneNode *Quene;
struct QueneNode {
	int Data[MaxSize];
	int front, rear;
};

/* 图相关函数 */
PtrToGraph InitializationGraph(int vn);
void InsertEdge(PtrToGraph G, PtrToEdge E);
PtrToGraph BuildGraph();
void DFS(PtrToGraph G, int StartVertex);
void BFS(PtrToGraph G, int StartVertex);

/* 队列相关函数 */
Quene InitializationQuene();
void AddQuene(int Value, Quene q);
int OutQuene(Quene q);


int main()
{
	PtrToGraph G = BuildGraph();
	printf("\n");
	DFS(G, 0);
	printf("\n");
	BFS(G, 0);

	return 0;
}


PtrToGraph InitializationGraph(int vn)
{
	int i;
	PtrToGraph G = malloc(sizeof(struct Graph));
	G->VertexNums = vn;
	G->EdgeNums = 0;

	for (i = 0; i < G->VertexNums; i++)
		G->Table[i].First = NULL;

	return G;
}


void InsertEdge(PtrToGraph G, PtrToEdge E)
{
	PtrToAdjNode New1 = malloc(sizeof(struct AdjNode));
	PtrToAdjNode New2 = malloc(sizeof(struct AdjNode));
	New1->NodeNumber = E->VertexE;
	New2->NodeNumber = E->VertexS;

	New1->Next = G->Table[E->VertexS].First;
	G->Table[E->VertexS].First = New1;
	New2->Next = G->Table[E->VertexE].First;
	G->Table[E->VertexE].First = New2;
}


PtrToGraph BuildGraph()
{
	int vn, ve, i; 
	PtrToEdge E;
	PtrToGraph G;

	printf("Enter the number of vertexs and edges: ");
	scanf("%d %d", &vn, &ve);
	G = InitializationGraph(vn);
	G->EdgeNums = ve;
	printf("\n");

	if (G->EdgeNums != 0)
		E = malloc(sizeof(struct Edge));
		for (i = 0; i < G->EdgeNums; i++) {
			printf("Enter a Edge: ");
			scanf("%d %d", &E->VertexS, &E->VertexE);
			InsertEdge(G, E);
		}

	return G;
}


/**
 * 示例数据: 8 6 
 *          0 7
 *          0 1
 *          2 0
 *          4 1
 *          2 4
 *          3 5
 *          
 */
void DFS(PtrToGraph G, int StartVertex)
{
	PtrToAdjNode TempNode = G->Table[StartVertex].First;
	VisitedDFS[StartVertex] = 1;
	printf("You are visiting [%d]\n", StartVertex);

	while (TempNode) {
		if (!VisitedDFS[TempNode->NodeNumber])
			DFS(G, TempNode->NodeNumber);
			TempNode = TempNode->Next;
	}
}


void BFS(PtrToGraph G, int StartVertex)
{
	int TempVertex;
	PtrToAdjNode TempNode;

	Quene quene = InitializationQuene();
	printf("You are visiting [%d]\n", StartVertex);
	VisitedBFS[StartVertex] = 1;
	AddQuene(StartVertex, quene);

	while (quene->front != quene->rear) {
		TempVertex = OutQuene(quene);
		TempNode = G->Table[TempVertex].First;
		while (TempNode) {
			if (!VisitedBFS[TempNode->NodeNumber]) {
				printf("You are visiting [%d]\n", TempNode->NodeNumber);
				VisitedBFS[TempNode->NodeNumber] = 1;
				AddQuene(TempNode->NodeNumber, quene);
			}

			TempNode = TempNode->Next;
		}
	}
}


/* 队列相关函数 */
Quene InitializationQuene()
{
	Quene q = malloc(sizeof(struct QueneNode));
	q->front = 0;
	q->rear = 0;
	return q;
}


void AddQuene(int Value, Quene q)
{
	if (q->rear+1 % MaxSize == q->front) {
		printf("The Quene is Full.");
		exit(EXIT_FAILURE);
	}

	q->rear = (q->rear+1) % MaxSize;
	q->Data[q->rear] = Value;
}


int OutQuene(Quene q)
{
	if (q->rear == q->front) {
		printf("The Quene is Empty.");
		exit(EXIT_FAILURE);
	}

	q->front = (q->front+1) % MaxSize;
	return q->Data[q->front];
}