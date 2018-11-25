//-------------------
//     
//     -------------> Minimum Spaning Tree!!!!!!!!!!!!!!!!!!
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HMaxSize 20
#define SMaxSize 20
#define GMaxSize 20

//--------------------------------
typedef struct HeapNode *PtrToHeap;
struct HeapNode {
	int Capacity;
	int ElementNums;
	int *HeapArray;
};

//--------------------------------
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

/* 堆相关函数 ->以边构成最小堆 */
void InitEset(PtrToLGraph G, PtrToEdge Eset);
void PercDown(PtrToEdge Eset, int root, int N);
int GetEdge(PtrToEdge Eset, int CurrentSize);

/* 集合相关函数 */
void InitSet(int set[], int n);
void Union(int set[], int root1, int root2);
int FindRoot(int set[], int value);
bool CheckCycle(int set[], int v1, int v2);

/* 邻接表图相关函数 */
PtrToLGraph InitLGraph(int vn);
void InsertEdge(PtrToLGraph G, PtrToEdge E);


int main()
{
	return 0;
}


/* 堆相关函数 */
void InitEset(PtrToLGraph G, PtrToEdge Eset)
{
	int Vertex, Ecnt;
	PtrToAdjNode Temp;

	Ecnt = 0;
	for (Vertex = 0; Vertex < G->VertexNums; Vertex++)
		for (Temp = G->Table[Vertex]; Temp; Temp = Temp->Next) {
			if (Vertex < Temp->NodeNumber) {
				Eset[Ecnt].VertexS = Vertex;
				Eset[Ecnt].VertexE = Temp->NodeNumber;
				Eset[Ecnt++].Weight = Temp->Weight;
			}
		}

	for (Ecnt = G->VertexNums/2; Ecnt >= 0; Ecnt--)
		PercDown(Eset, Ecnt, G->VertexNums);
}


/* 将 N个元素的边数组中以ESet[p]为根的子堆调整为关于Weight的最小堆 */
void PercDown(PtrToEdge Eset, int root, int N)
{
	int Parent, Child;
	struct EdgeNode Temp;

	Temp = Eset[root];
	for (Parent = root; (Parent*2+1) <= N; Parent = Child) {
		Child = Parent * 2;

		if (Child != N-1 && Eset[Child].Weight > Eset[Child+1].Weight)
			Child++;

		if (Eset[Child].Weight > Temp.Weight) {
			break;
		} else {
			Eset[Parent] = Eset[Child];
		}
	}

	Eset[Parent] = Temp;
}


/* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆 */
int GetEdge(PtrToEdge Eset, int CurrentSize)
{
	PtrToEdge Temp = &Eset[0];

	Eset[0] = Eset[CurrentSize-1];
	Eset[CurrentSize-1] = *Temp;
	PercDown(Eset, 0, CurrentSize-1);

	return CurrentSize-1;
}



/* 并查集相关函数 */
void InitSet(int set[], int n)
{
	int i;
	for (i = 0; i < n; i++) set[i] = -1;
} 


void Union(int set[], int root1, int root2)
{
	if (set[root2] < set[root1]) {
		set[root2] += set[root1];
		set[root1] = root2;
	} else {
		set[root1] += set[root2];
		set[root2] = root1;
	}
}


int FindRoot(int set[], int value)
{
	if (set[value] < 0){
		return value;
	} else {
		return set[value] = FindRoot(set, value);
	}
}


// 检查两个节点是否在最小生成树中构成了回路
bool CheckCycle(int set[], int v1, int v2)
{
	int root1, root2;
	root1 = FindRoot(set, v1);
	root2 = FindRoot(set, v2);

	if (root1 == root2) {
		return false;       // 如果两个顶点已经连通，则该边不能要
	} else {
		Union(set, v1, v2); //否则该边可以被收集，同时将 V1和 V2并入同一连通集
		return true;
	}
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
	PtrToAdjNode New2 = malloc(sizeof(struct AdjNode));
	New1->NodeNumber = E->VertexE;
	New1->Weight = E->Weight;
	New2->NodeNumber = E->VertexS;
	New2->Weight = E->Weight;

	New1->Next = G->Table[E->VertexS];
	G->Table[E->VertexS] = New1;
	New2->Next = G->Table[E->VertexE];
 	G->Table[E->VertexE] = New2;
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


/* Kruskal算法 
   将最小生成树保存为邻接表存储的图 MST，返回最小权重和 */
int Kruskal(PtrToLGraph G, PtrToLGraph MST)
{
	int SumWeight, EdgeCnt, NextEdge, VertexSet[G->VertexNums];
    PtrToEdge Eset = malloc(sizeof(struct EdgeNode) * G->VertexNums);
    InitEset(G, Eset);

    // 建包含所有顶点但没有边的图
    // 初始化权重和
    // 初始化收录的边数
    MST = InitLGraph(G->VertexNums);
    SumWeight = 0;
    EdgeCnt = 0;

    // 原始边集的规模
    NextEdge = G->EdgeNums;

    // 当收集的边不足以构成树时
    while (EdgeCnt < G->VertexNums - 1) {
    	NextEdge = GetEdge(Eset, NextEdge);  // 从边集中得到最小边的位置
    	if (NextEdge < 0) break;

    	// 如果该边的加入不构成回路，即两端结点不属于同一连通集
    	if (CheckCycle(VertexSet, Eset[NextEdge].VertexS, Eset[NextEdge].VertexE) == true) {

    		InsertEdge(MST, &Eset[NextEdge]);
    		SumWeight += Eset[NextEdge].Weight;
    		EdgeCnt++;
    	}
    }

    // 图里一共N个顶点，要形成一个最小生成树，即让这些顶点都连通，则至少需要N-1条边
    if (EdgeCnt < G->VertexNums - 1)
    	return -1;

    return SumWeight;
}