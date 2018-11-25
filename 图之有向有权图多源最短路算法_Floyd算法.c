#include <stdio.h>
#include <stdbool.h>

#define MaxSize 10

int VertexNums, EdgeNums;
int Graph[MaxSize][MaxSize];
int Dist[MaxSize][MaxSize];
int path[MaxSize][MaxSize];

void BuildGraph();
bool Floyed();

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
			if (i == j) Graph[i][j] = 0;
			else Graph[i][j] = 65535;

	printf("Enter the number of Edges: ");
	scanf("%d", &EdgeNums);

	for (i = 0; i < EdgeNums; i++) {
		printf("Enter a Edge: ");
		scanf("%d %d %d", &vs, &ve, &weight);
		Graph[vs][ve] = weight;
	}
}


bool Floyed()
{
	/**
	 * 首先复制Graph中的权重到一个二维数组Dist，并初始化表示距离的二维数组path
	 */
	int i, j, k;
	for (i = 0; i < VertexNums; i++)
		for (j = 0; j < VertexNums; j++) {

			// Dist对角线应该初始化为0，两个点没有直接的边相连的话 二者之间应该被初始化为正无穷
			Dist[i][j] = Graph[i][j];
			path[i][j] = -1;
	}

	/*
	 * 从这里开始，将一个个顶点不断插入点 i j 之间，
	 * 看对二者的最短距离有没有影响，有则更新即可
	 * 
	 **/
	for (k = 0; k < VertexNums; k++)
		for (i = 0; i < VertexNums; i++)
			for (j = 0; j < VertexNums; j++)
				if (Dist[i][k] + Dist[k][j] < Dist[i][j])
					Dist[i][j] = Dist[i][k] + Dist[k][j];
					if (i == j && Dist[i][j] < 0) return false; // 发现负值圈，返回错误标记
					path[i][j] = k;

	return true;
}