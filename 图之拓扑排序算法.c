#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GMaxSize 20

typedef struct EdgeNode *PtrToEdge;
struct EdgeNode {
	int VertexS, VertexE, Weight;
};

typedef struct AdjNode *PtrToAdjNode;
struct AdjNode {
	int NodeNumber;
	int Weight;
	PtrToAdjNode Next;
};

typedef struct LGraphNode *PtrToLGraph;
struct LGraphNode {
	int VertexNums;
	int EdgeNums;
	PtrToAdjNode Table[GMaxSize];
};


/* 邻接表图相关函数 */
PtrToLGraph InitLGraph(int vn);
void InsertEdge(PtrToLGraph G, PtrToEdge E);


int main()
{
	return 0;
}


/* 邻接表图相关函数 */
PtrToLGraph InitLGraph(int vn)
{
	int i;
	PtrToLGraph G = malloc(sizeof(struct LGraphNode));
	G->VertexNums = vn;
	G->EdgeNums = 0;

	for (i = 0; i < G->VertexNums; i++)
		G->Table[i] = NULL;

	return G;
}


void InsertEdge(PtrToLGraph G, PtrToEdge E)
{
	PtrToAdjNode New1 = malloc(sizeof(struct AdjNode));
	New1->NodeNumber = E->VertexE;
	New1->Weight = E->Weight;
	New1->Next = G->Table[E->VertexS];
	G->Table[E->VertexS] = New1;
}


PtrToLGraph BuildGraph()
{
	int vn, ve, i; 
	PtrToEdge E;
	PtrToLGraph G;

	printf("Enter the number of vertexs and edges: ");
	scanf("%d %d", &vn, &ve);
	G = InitLGraph(vn);
	G->EdgeNums = ve;
	printf("\n");

	if (G->EdgeNums != 0)
		E = malloc(sizeof(struct EdgeNode));
		for (i = 0; i < G->EdgeNums; i++) {
			printf("Enter a Edge: ");
			scanf("%d %d %d", &E->VertexS, &E->VertexE, &E->Weight);
			InsertEdge(G, E);
		}

	return G;
}


/* 拓扑排序： 如果图中从v到w有一条有向的 Path，且输出的时候v必定排在w之前。
   满足此条件的顶点序列称为一个拓扑序
   获得一个拓扑序的过程称为拓扑排序
   AOV (Activity on Vertex) 如果有合理的拓扑序，则必定是有向无环图 */

/* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
bool TopSort(PtrToLGraph G, int TopOrder)
{	
	// Indegree用于存储顶点v到w的入度
	int Indegree[G->VertexNums] = {0}, cnt = 0;
	int V;
	PtrToAdjNode W;

	// 创建一个队列
	PtrToQNode queue = CreateQueue(G->VertexNums);

	// 遍历图, 得到入度 V->W
	for (V = 0; V < G->VertexNums; V++)
		for (W = G->Table[V]; W; W = W->Next)
			Indegree[W->NodeNumber]++;

	// 将所有入度为0的顶点入列 
	for (V = 0; V < G->VertexNums; V++)
		if (Indegree[V] == 0) AddQueue(V, queue);

	while (!IsEmpty(queue)) {
		V = OutQueue(queue);
		TopOrder[cnt++] = V;

		// 对V的每个邻接点 W->NodeNumber 若删除 V使得W->NodeNumber入度为 0
		for (W = G->Table[V]; W; W = W->Next) {
			if (--Indegree[W->NodeNumber] == 0) AddQueue(W, queue);
		}
	}

	if (cnt != G->VertexNums) return false;
	else return true;
}
