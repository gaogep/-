#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertex 10

typedef struct EdgeNode *PtrToENode;
struct EdgeNode {
	int Vertex1, Vertex2; // 1为起点 2为终点
	int Weight;
};

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	int End;
	int Weight;
	PtrToAdjVNode Next;
};

typedef struct Vnode {
	PtrToAdjVNode FirstEdge;
	char Data;	
} AdjList;

typedef struct GraphNode *PtrToGNode;
struct GraphNode {
	int VertexNums;
	int EdgeNums;
	AdjList G[MaxVertex];
};

PtrToGNode CreateGraph(int VertexNums);
void InsertEdge(PtrToGNode Graph, PtrToENode E);
PtrToGNode BuildGraph();
void Visit(int Vertex);
void DFS(PtrToGNode Graph, int Vertex, void (*Visit)(int));

bool Visited[MaxVertex] = {false};


int main()
{
	return 0;
}


PtrToGNode CreateGraph(int VertexNums)
{
	int i;
	PtrToGNode Graph;

	Graph = malloc(sizeof(struct GraphNode));
	Graph->VertexNums = VertexNums;
	Graph->EdgeNums = 0;

	for (i = 0; i < Graph->VertexNums; i++)
		Graph->G[i].FirstEdge = NULL;

	return Graph;
}


void InsertEdge(PtrToGNode Graph, PtrToENode E)
{
	PtrToAdjVNode NewNode;
	NewNode = malloc(sizeof(struct AdjVNode));
	NewNode->End = E->Vertex2;
	NewNode->Weight = E->Weight;

	NewNode->Next = Graph->G[E->Vertex1].FirstEdge;
	Graph->G[E->Vertex1].FirstEdge = NewNode;
	// 如果是双向图，则还要泛着插入一遍  
}


PtrToGNode BuildGraph()
{
	PtrToGNode Graph;
	PtrToENode E;
	int V;
	char data;
	int VertexNums, i;

	printf("Input the number of Vertexs: ");
	scanf("%d", &VertexNums);
	Graph = CreateGraph(VertexNums);
	printf("Input the number of Edges: ");
	scanf("%d", &(Graph->EdgeNums));

	if (Graph->EdgeNums != 0) {
		E = malloc(sizeof(struct EdgeNode));
		for (i = 0; i < Graph->EdgeNums; i++) {
			printf("Input the StartNode, the EndNode and the weight: ");
			scanf("%d %d %d", &E->Vertex1, &E->Vertex2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}

	for (V = 0; V < Graph->VertexNums; V++) {
		printf("Input the data of Vertex(Input 'S' to exit): ");
		scanf(" %c", &data);
		if (data == 'S') break;
		Graph->G[V].Data = data;
	}

	return Graph;
}


/* 深度优先搜索 */
void Visit(int Vertex)
{
	printf("The Node you are visiting now is: %d", Vertex);
}


void DFS(PtrToGNode Graph, int Vertex, void (*Visit)(int))
{
	PtrToAdjVNode W;

	Visit(Vertex);
	Visited[Vertex] = true;

	for (W=Graph->G[Vertex].FirstEdge; W; W = W->Next) {
		if (!Visited[Vertex])
			DFS(Graph, W->End, Visti);
	}
}