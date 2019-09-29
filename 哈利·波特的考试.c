#include<stdio.h>
#define maxN 101
#define Inf 65535
int main() {
	/*freopen("Text.txt", "r", stdin);*/	//Testcase
	int N, M, i, j, k;
	int D[maxN][maxN];	//distance
	if (scanf("%d", &N) == NULL) {
		return;
	}
	if (scanf("%d", &M) == NULL) {
		return;
	}
	//build graph
	int G[maxN][maxN];
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (i == j) {
				G[i][j] = 0;
			}
			else {
				G[i][j] = Inf;
			}
		}
	}
	//get test data
	for (i = 0; i < M; i++) {
		int a, b, t;
		if (NULL == scanf("%d %d %d", &a, &b, &t)) {
			return;
		}
		G[a][b] = G[b][a] = t;
	}
	//floyed
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			D[i][j] = G[i][j];

		}
	}
	for (k = 1; k <= N; k++) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					//ÅÐ¶¨¸ºÖµÈ¦
					if (i == j && D[i][j] < 1) {
						return -1;
					}
				}
			}
		}
	}
	//test
	//for (i = 1; i <= N; i++) {
	//	for (j = 1; j <= N; j++) {
	//		printf("%3d ", D[i][j]);
	//	}
	//	printf("\n");
	//}

	//check
	int max[maxN], min;
	for (i = 1; i <= N; i++) {
		max[i] = 0;
		for (j = 1; j <= N; j++) {
			if (i != j && max[i] < D[i][j]) {
				max[i] = D[i][j];
				if (max[i] == Inf) {
					printf("0\n");
					return 0;
				}
			}
		}
	}
	min = 1;
	for (i = 1; i <= N; i++) {
		/*printf("%d ", max[i]);*/
		if (max[i] < max[min]) {
			min = i;
		}
	}
	printf("%d %d", min, max[min]);
	return 0;

}