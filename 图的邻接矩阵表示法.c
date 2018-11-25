#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertex 10
#define INFINITY 65535

typedef int Vertex;
typedef int Weight;

typedef struct EdgeNode *PtrToENode;
struct EdgeNode {
	Vertex v1, v2;      // 有向边 v1 v2
	Weight weight;      // 权重
};

typedef struct GraphNode *PtrToGNode; // 这个是一个有向图
struct GraphNode {
	int VertexNums;					  // 顶点数
	int EdgeNums;					  // 边数
	Weight G[MaxVertex][MaxVertex];   // 矩阵
	int Data[MaxVertex];			  // 存顶点的数据
};

PtrToGNode CreateGraph(int VertexNums);
void InsertEdge(PtrToGNode Graph, PtrToENode E);
PtrToGNode BuildGraph();

bool Visited[MaxVertex] = {false};

int main()
{
	return 0;
}


/* 初始化一个有VertexNum个顶点但没有边的图 */
PtrToGNode CreateGraph(int VertexNums)
{
	Vertex V, W;
	PtrToGNode Graph;

	Graph = malloc(sizeof(struct GraphNode));
	Graph->VertexNums = VertexNums;
	Graph->EdgeNums = 0;
	for (V = 0; V < Graph->VertexNums; V++)
		for (W = 0; W < Graph->VertexNums; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}


/* 插入边 */
void InsertEdge(PtrToGNode Graph, PtrToENode E)
{
	Graph->G[E->v1][E->v2] = E->weight;
	// Graph->G[E->v2][E->v1] = E->weight; 若是无向图，则来回都要插入一次
}


/* 建立图 */
PtrToGNode BuildGraph()
{
	PtrToGNode Graph;
	PtrToENode E;
	Vertex V;
	char data;
	int VertexNums, i;

	printf("Input the number of Vertexs: ");
	scanf("%d", &VertexNums);
	Graph = CreateGraph(VertexNums);
	printf("Input the number of Edges: ");
	scanf("%d", &(Graph->EdgeNums));

	if (Graph->EdgeNums != 0) {
		E = malloc(sizeof(struct EdgeNode));    // 建立边结点
		for (i = 0; i < Graph->EdgeNums; i++) { // 读入边，格式为"起点 终点 权重"，插入邻接矩阵
			printf("Input the StartNode,  the EndNode and the weight: ");
			scanf("%d %d %d", &E->v1, &E->v2, &E->weight);
			InsertEdge(Graph, E);
		}
	}

	// 如果顶点有数据的话，读入数据 
	for (V = 0; V < Graph->VertexNums; V++) {
		printf("Input the data of Vertex(Input 'S' to exit): ");
		scanf(" %c", &data);
		if (data == 'S') break;
		Graph->Data[V] = data;
	}

	return Graph;
}


/* 邻接矩阵存储的图 - BFS */
 
/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
bool IsEdge( PtrToGNode Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W]<INFINITY ? true : false;
}
 
                                     /* Visited[]为全局变量，已经初始化为false */
void BFS ( PtrToGNode Graph, Vertex S, void (*Visit)(Vertex) )
{                                    /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;     
    Vertex V, W;
 
    Q = CreateQueue( MaxSize );      /* 创建空队列, MaxSize为外部定义的常数 */
                                     /* 访问顶点S：此处可根据具体访问需要改写 */
    Visit( S );
    Visited[S] = true;               /* 标记S已访问 */
    AddQ(Q, S);                      /* S入队列 */
     
    while ( !IsEmpty(Q) ) {
        V = DeleteQ(Q);              /* 弹出V */
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
                                     /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                                     /* 访问顶点W */
                Visit( W );
                Visited[W] = true;   /* 标记W已访问 */
                AddQ(Q, W);          /* W入队列 */
            }
    }                                /* while结束*/
}


void Visit(Vertex V)
{
	printf("The Node you are visiting now is: %d", V);
}