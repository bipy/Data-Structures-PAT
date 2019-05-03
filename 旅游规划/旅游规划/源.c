#include<stdio.h>
#include<stdlib.h>
#define maxN 500
#define Inf 9999
struct {
	int d;	//distance
	int p;	//price
}G[maxN][maxN];

int main() {
	/*freopen("Text.txt", "r", stdin);*/
	int N, M, S, D, i, j, k;
	if (NULL == scanf("%d", &N)) {
		return;
	}
	if (NULL == scanf("%d", &M)) {
		return;
	}
	if (NULL == scanf("%d", &S)) {
		return;
	}
	if (NULL == scanf("%d", &D)) {
		return;
	}
	//build graph
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j) {
				G[i][j].d = 0;
				G[i][j].p = 0;
			}
			else {
				G[i][j].d = Inf;
				G[i][j].p = Inf;
			}
		}
	}
	for (i = 0; i < M; i++) {
		int a, b, distance, price;
		if (NULL == scanf("%d %d %d %d", &a, &b, &distance, &price)) {
			return;
		}
		G[a][b].d = G[b][a].d = distance;
		G[a][b].p = G[b][a].p = price;
	}
	//floyed
	for (k = 0; k < N; k++) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (G[i][k].d + G[k][j].d <= G[i][j].d) {
					//比原来路途短，无条件更新路费
					if (G[i][j].d > G[i][k].d + G[k][j].d) {	
						G[i][j].p = G[i][k].p + G[k][j].p;
					}
					//和原来路途一样远，找最便宜的
					else if (G[i][j].d == G[i][k].d + G[k][j].d && G[i][j].p > G[i][k].p + G[k][j].p) {
						G[i][j].p = G[i][k].p + G[k][j].p;
					}
					G[i][j].d = G[i][k].d + G[k][j].d;
				}
			}
		}
	}
	//print
	printf("%d %d", G[S][D].d, G[S][D].p);
	return 0;
}