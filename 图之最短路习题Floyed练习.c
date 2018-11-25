#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100

typedef struct Graph *PtrToGraph;
struct Graph {
	int VertexNums;
	int EdgeNums;
	int Matrix[MaxSize][MaxSize];
};

PtrToGraph BuildGraph();
bool Floyed(PtrToGraph G);
void Find(int VertexNums);
int FindMax(int i, int VertexNums);

int Dist[MaxSize][MaxSize];

int main()
{
	PtrToGraph G = BuildGraph();
	Floyed(G);
	Find(G->VertexNums);

	return 0;
}


PtrToGraph BuildGraph()
{
	int i, j;
	int e1, e2, w;

	PtrToGraph G = malloc(sizeof(struct Graph));
	printf("Enter the number of Vertexs and Edges: ");
	scanf("%d %d", &G->VertexNums, &G->EdgeNums);

	for (i = 0; i < G->VertexNums; i++)
		for (j = 0; j < G->VertexNums; j++)
			if (i == j) G->Matrix[i][j] = 0;
			else G->Matrix[i][j] = 65535;

	for (i = 0; i < G->EdgeNums; i++) {
		scanf("%d %d %d", &e1, &e2, &w);
		G->Matrix[e1-1][e2-1] = w;
		G->Matrix[e2-1][e1-1] = w;
	}

	return G;
}


bool Floyed(PtrToGraph G)
{
	int i, j, k;

	for (i = 0; i < G->VertexNums; i++)
		for (j = 0; j < G->VertexNums; j++)

			//Dist 初始化对角线为0，其余为无穷大!!!!!!!!!!
			Dist[i][j] = G->Matrix[i][j];

	for (k = 0; k < G->VertexNums; k++)
		for (i = 0; i < G->VertexNums; i++)
			for (j = 0; j < G->VertexNums; j++)
				if (Dist[i][k] + Dist[k][j] < Dist[i][j])
					Dist[i][j] = Dist[i][k] + Dist[k][j];

	return true;
}


void Show(int VertexNums)
{
	int i, j;
	for (i = 0; i < VertexNums; i++)
		for (j = 0; j < VertexNums; j++)
			printf("%d ", Dist[i][j]);
}


void Find(int VertexNums)
{
	int i, max, min, animal;

	min = 65535;
	for (i = 0; i < VertexNums; i++) {
		max = FindMax(i, VertexNums);
		if (max == 65535) {
			printf("%d", 0);
			return;
		}

		if (min > max) {
			min = max;
			animal = i + 1;
		}
	}

	printf("%d %d\n", animal, min);
}


int FindMax(int i, int VertexNums)
{
	int max = 0, j;

	for (j = 0; j < VertexNums; j++)
		if (i != j && Dist[i][j] > max)
			max = Dist[i][j];
	
	return max;
}