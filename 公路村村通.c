#include<stdio.h>
#include<stdlib.h>
#define maxN 1001
#define maxM (3*maxN)
#define Inf 9999

struct {
	int u;		//点1
	int v;		//点2
	int e;		//边
}MST[maxM];		//最小生成树
void swap(int a, int b) {
	int tu, tv, te, tp;
	tu = MST[a].u;
	tv = MST[a].v;
	te = MST[a].e;
	MST[a].u = MST[b].u;
	MST[a].v = MST[b].v;
	MST[a].e = MST[b].e;
	MST[b].u = tu;
	MST[b].v = tv;
	MST[b].e = te;
}
int find(int* set, int x) {
	while (x != set[x]) {
		x = set[x];
	}
	return x;
}
int main() {
	/*freopen("Text.txt", "r", stdin);*/
	int N, M, i, j, k, ans = 0;
	if (NULL == scanf("%d %d", &N, &M)) {
		return;
	}

	//get data
	for (i = 1; i <= M; i++) {
		int a, b, c;
		if (NULL == scanf("%d %d %d", &a, &b, &c)) {
			return;
		}
		MST[i].e = c;
		MST[i].u = a;
		MST[i].v = b;
		//G[a][b] = G[b][a] = c;
	}
	//sort
	for (i = 1; i <= M; i++) {
		for (j = 2; j <= M - i + 1; j++) {
			if (MST[j - 1].e > MST[j].e) {
				swap(j - 1, j);
			}
		}
	}
	/*for (i = 1; i <= M; i++) {
		printf("%d ", MST[i].e);
	}*/
	//set
	int* set = (int*)malloc(sizeof(int) * (N + 1));
	for (i = 1; i <= N; i++) {
		set[i] = i;
	}
	//Kruskal
	for (i = 1; i <= M; i++) {
		int x = find(set, MST[i].u);
		int y = find(set, MST[i].v);
		if (x != y) {
			ans += MST[i].e;
			set[x] = y;
		}
	}
	//有多少个并查集
	for (i = 1, k = 0; i <= N; i++) {
		if (set[i] == i) {
			k++;
		}
	}
	k > 1 ? printf("-1") : printf("%d", ans);
}
