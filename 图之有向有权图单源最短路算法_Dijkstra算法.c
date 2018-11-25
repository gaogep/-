#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

int path[MaxSize] = {-1};
unsigned dist[MaxSize] = {65535};
bool collected[MaxSize] = {false};

int Graph[MaxSize][MaxSize];
int VertexNums, EdgeNums;

void BuildGraph();
int FindMin(unsigned dist[], bool collected[]);
void Dijkstra(int StartVertex);
int FindMin(unsigned d[], bool c[]);


int main()
{
	BuildGraph();
	
	return 0;
}


void BuildGraph()
{
	int i, j;
	int vs, ve, weight;

	printf("Enter the number of Vertexs: ");
	scanf("%d", &VertexNums);

	for (i = 0; i < VertexNums; i++)
		for (j = 0; j< VertexNums; j++)
			Graph[i][j] = 0;

	printf("Enter the number of Edges: ");
	scanf("%d", &EdgeNums);

	for (i = 0; i < EdgeNums; i++) {
		printf("Enter a Edge: ");
		scanf("%d %d %d", &vs, &ve, &weight);
		Graph[vs][ve] = weight;
	}
}


void Dijkstra(int StartVertex)
{
	int Neighbor, UclMin;
	dist[StartVertex] = 0;
	collected[StartVertex] = true;

	for (Neighbor = 0; Neighbor < VertexNums; Neighbor++)
		if (Graph[StartVertex][Neighbor] != 0) {
			dist[Neighbor] = Graph[StartVertex][Neighbor];
			path[Neighbor] = StartVertex;
		}

	while (1) {
		UclMin = FindMin(dist, collected);
		if (UclMin == -1) break;
		collected[UclMin] = true;

		for (Neighbor = 0; Neighbor < VertexNums; Neighbor++)
			if (Graph[UclMin][Neighbor] != 0 && collected[Neighbor] == false)
				if (dist[UclMin] + Graph[UclMin][Neighbor] < dist[Neighbor]) {
					dist[Neighbor] = dist[UclMin] + Graph[UclMin][Neighbor];
					path[Neighbor] = UclMin;
				}
	}
}


int FindMin(unsigned dist[], bool collected[])
{
	int i, cnt, minvertex, mindist = 65535;

	for (i = 0; i < VertexNums; i++) {
		if (collected[i] == true) {
			cnt++;
			continue;
		}

		if (dist[i] < mindist) {
			mindist = dist[i];
			minvertex = i;
		}
	}

	if (cnt == VertexNums) return -1;
	else return minvertex;
}