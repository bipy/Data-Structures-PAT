#include<stdio.h>
#include<stdlib.h>

#define MaxN 10001

typedef struct GNode* PtrG;
struct GNode {
	int Nv;
	int Ne;
	int Graph[MaxN][MaxN];
};


int Check(PtrG G, int N, int M,int x) {
	int i, front, rear, count = 0, sp = 0, length = 0;
	int queue[MaxN];
	int* visited = (int*)malloc(sizeof(int) * (N+1));
	for (i = 1; i <= N; i++) {
		visited[i] = 0;
	}
	front = rear = -1;
	visited[x] = 1;
	queue[++rear] = x;
	while (front < rear) {
		int V = queue[++front];
		for (i = 1; i <= N; i++) {
			if (visited[i] == 0 && G->Graph[V][i] == 1) {	
				if (count >= 6) {
					sp++;
				}
				visited[i] = 1;
				queue[++rear] = i;
			}
		}
		//计算圈数
		if(length>0) {
			length--;
		}
		if (length == 0) {
			length = rear - front;
			count++;
		}
		//
		
	}
	//不连通
	for (i = 1; i <= N; i++) {
		if (visited[i] == 0) {
			sp++;
		}
	}
	//
	free(visited);
	return sp;
}
int main() {
	int N, M, i, j, p1, p2;
	scanf("%d %d", &N, &M);
	
	PtrG G = (PtrG)malloc(sizeof(struct GNode));
	G->Nv = N;
	G->Ne = M;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			G->Graph[i][j] = 0;
		}
	}
	for (i = 0; i < M; i++) {
		scanf("%d %d", &p1, &p2);
		G->Graph[p1][p2] = 1;
		G->Graph[p2][p1] = 1;
	}
	for (i = 1; i <= N; i++) {
		printf("%d: %.2f%%\n", i, (1 - Check(G, N, M, i) / (double)N) * 100);

	}
	
	return 0;
}