#include<stdio.h>
#include<stdlib.h>
#define maxN 101

struct {
	int in;		//indegree
	int earliest;
}V[maxN];

int main() {
	/*freopen("text.txt", "r", stdin);*/
	int N, M, i, j, k;
	int queue[maxN];
	int front = -1;
	int rear = -1;
	if (NULL == scanf("%d %d", &N, &M)) {
		return;
	}
	//build graph
	int G[maxN][maxN];
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {		
			G[i][j] = -1;
		}
	}
	for (i = 0; i < N; i++) {
		V[i].in = 0;
		V[i].earliest = 0;
	}
	//get data
	for (i = 0; i < M; i++) {
		int a, b, c;
		if (NULL == scanf("%d %d %d", &a, &b, &c)) {
			return;
		}
		G[a][b] = c;
		V[b].in++;
	}
	//TopSort
	int* end = (int*)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++) {
		if (V[i].in == 0) {
			queue[++rear] = i;
		}
	}
	int count = 0;
	
	k = 0;
	while (rear != front) {
		int x = queue[++front];
		count++;
		for (j = 0; j < N; j++) {
			if (G[x][j] >= 0) {
				V[j].in--;
				if (V[x].earliest + G[x][j] > V[j].earliest) {
					V[j].earliest = V[x].earliest + G[x][j];
				}
				if (V[j].in == 0) {
					queue[++rear] = j;
				}
			}
		}
	}
	int max = -1;
	for (i = 0; i < N; i++) {
		if (max < V[i].earliest) {
			max = V[i].earliest;
		}
	}
	if (count != N) {
		printf("Impossible");
	}
	else {
		printf("%d", max);
	}
}
