#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GMaxSize 20
#define INFINITY 65535

typedef struct MGraphNode *PtrToMGraph;
struct MGraphNode {
	int VertexNums;
	int EdgeNums;
	int GraphArray[GMaxSize][GMaxSize];
};

//-----------------------------------
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


/* 邻接矩阵图相关函数 */
PtrToMGraph BuildGraph();

/* 邻接表图相关函数 */
PtrToLGraph InitLGraph(int vn);

/* Prim算法相关函数 */
int Prim(PtrToMGraph G, PtrToLGraph MST);
int FindMinDist(PtrToMGraph G, int dist[]);


/*
 * 最小生成树的三条约束：
 * 1.只能用图里有的边
 * 2.只能正好用掉 |V|-1条边
 * 3.不能有回路
 * --------------------------------------------------
 * Prim算法的基本思路 -> 从一个根节点开始，让一棵小树长大
 * --------------------------------------------------
 */


int main()
{

	return 0;
}


/* 邻接矩阵图相关函数 */
PtrToMGraph BuildMGraph()
{
	int i, j;
	int vs, ve, weight;
	PtrToMGraph G = malloc(sizeof(struct GraphNode));

	printf("Enter the number of Vertexs: ");
	scanf("%d", &G->VertexNums);

	for (i = 0; i < G->VertexNums; i++)
		for (j = 0; j< G->VertexNums; j++)
			 G->GraphArray[i][j] = INFINITY;

	printf("Enter the number of Edges: ");
	scanf("%d", &G->EdgeNums);

	if (G->EdgeNums != 0)
		for (i = 0; i < G->EdgeNums; i++) {
			printf("Enter a Edge: ");
			scanf("%d %d %d", &vs, &ve, &weight);
			 G->GraphArray[vs][ve] = weight;
			 G->GraphArray[ve][vs] = weight;
		}

	return G;
}

/* 邻接表图相关函数 */
PtrToLGraph InitLGraph(int vn)
{
	int i;
	PtrToGraph G = malloc(sizeof(struct Graph));
	G->VertexNums = vn;
	G->EdgeNums = 0;

	for (i = 0; i < G->VertexNums; i++)
		G->Table[i].First = NULL;

	return G;
}


void InsertEdge(PtrToLGraph G, PtrToEdge E)
{
	PtrToAdjNode New1 = malloc(sizeof(struct AdjNode));
	PtrToAdjNode New2 = malloc(sizeof(struct AdjNode));
	New1->NodeNumber = E->VertexE;
	New1->Weight = E->Weight;
	New2->NodeNumber = E->VertexS;
	New2->Weight = E->Weight;

	New1->Next = G->Table[E->VertexS]
	G->Table[E->VertexS] = New1;
	New2->Next = G->Table[E->VertexE]
	G->Table[E->VertexE] = New2;
}


/* Prim算法 */
/* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
int Prim(PtrToMGraph G, PtrToLGraph MST)
{
	int v, w; 
	int WeightSum = 0, CvNums = 0;
	int dist[GMaxSize], parent[GMaxSize];

	// dist->代表顶点到最小生成树的距离, 即选一个定点到收录进 MST中所有顶点的距离的最小
	// dist初始化，默认从顶点 0 开始 
	// >-----------------------------------------------------------------------------------
	// 这里假设若 V到 W没有直接的边，则 Graph->G[V][W]定义为无穷大 -> 此步在图初始化的时候就完成了
	// 即将 Graph->G[V][W] 一开始就初始化为 -> INFINITY
	// >-----------------------------------------------------------------------------------
	// 暂且定义所有顶点的父结点都是初始点 0
	for (v = 0; v < G->VertexNums; v++) {
		dist[v] = G->GraphArray[0][v];
		parent[v] = 0;
	}

	MST = InitLGraph();
	PtrToEdge = malloc(sizeof(struct EdgeNode));

	 // 将初始点 0 收录进 MST
	 dist[0] = 0;
	 CvNums++;
	 parent[0] = -1;

	 while (1) {
	 	v = FindMinDist(G, dist);

	 	// V = 未被收录顶点中 dist最小者
	 	// 如果这样的 V 不存在
	 	if (v == -1) break;

	 	// 将 V及相应的边<parent[V], V>收录进MST
	 	E->VertexS = parent[v];
	 	E->VertexE = v;
	 	E->Weight = dist[v];
	 	InsertEdge(MST, E);
	 	WeightSum += dist[v];
	 	dist[v] == 0;
	 	CvNums++;

	 	// 对图中的每个顶点 W 若 W 是 V 的邻接点并且未被收录
	 	// 若收录 V使得 dist[W]变小 更新树
	 	for (w = 0; w < G->VertexNums; w++) {
	 		if (G->GraphArray[v][w] < dist[v]) {
	 			dist[w] = G->GraphArray[v][w];
	 			parent[w] = v;
	 		}
	 	}
	 }

	 if (CvNums < G->VertexNums - 1) WeightSum = -1;
	 return WeightSum
}


int FindMinDist(PtrToMGraph G, int dist[])
{
	int MinVertex, MinDist = INFINITY, Temp;

	for (Temp = 0; Temp < G->VertexNums; Temp++)
		if (dist[Temp] != 0 && dist[Temp] < MinDist) {
			MinDist = dist[Temp];
			MinVertex = Temp;
		}

	if (MinDist < INFINITY) return MinVertex;
	else return -1;
}