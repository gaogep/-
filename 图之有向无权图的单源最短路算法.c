#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20

int dist[MaxSize] = {-1};
int path[MaxSize] = {-1}

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

typedef struct QueueNode *Queue;
struct QueueNode {
	int Data[MaxSize];
	int front, rear;
};

PtrToGraph InitializationGraph(int vn);
void InsertEdge(PtrToGraph G, PtrToEdge E);
PtrToGraph BuildGraph();

/* 队列相关函数 */
Queue InitializationQueue();
void AddQueue(int Value, Queue q);
int OutQueue(Queue q);


int main()
{
	PtrToGraph G = BuildGraph();

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
	PtrToAdjNode New = malloc(sizeof(struct AdjNode));
	New->NodeNumber = E->VertexE;

	New->Next = G->Table[E->VertexS].First;
	G->Table[E->VertexS].First = New;
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


/* 此为无权图的单源最短路算法, 针对无向图 */
void ShortestPath(PtrToGraph G, int StartVertex)
{
	int temp;
	PtrToAdjNode TempNode;

	Queue queue = InitializationQueue();
	dist[StartVertex] = 0;
	AddQueue(StartVertex, queue);

	while (queue->rear != queue->front) {
		temp = OutQueue(queue);
		for (TempNode = G->Table[temp].First; TempNode; TempNode = TempNode->Next) 
			if (dist[TempNode->NodeNumber] == -1) {
				dist[TempNode->NodeNumber] = dist[temp]+1;
				path[TempNode->NodeNumber] = temp;
				AddQueue(queue, TempNode->NodeNumber);
			}
	}
}


/* 队列相关函数 */
Queue InitializationQueue()
{
	Queue q = malloc(sizeof(struct QueueNode));
	q->rear = 0;
	q->front = 0;
	return q;
}


void AddQueue(int value, Quune q)
{
	if (q->rear+1 % MaxSize == q->rear) {
		printf("The Queue is Full.");
		exit(EXIT_FAILURE);
	}

	q->rear = q->rear+1 % MaxSize;
	q->Data[q->rear] = value;
}


int OutQueue(Queue)
{
	if (q->rear == q->front) {
		printf("The Queue is Empty.");
		exit(EXIT_FAILURE);
	}

	q->front = q->front+1 % MaxSize;
	return q->Data[front];
}