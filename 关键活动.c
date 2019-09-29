#include<stdio.h>
#include<stdlib.h>
#define maxN 102
typedef struct Gnode* Graph;
struct Gnode {
	int indegree;
	int outdegree;
	int asap;
	int flexible;
	int visited;
	int finished;
};
typedef struct stacknode* Stack;
struct stacknode {
	int s;
	int d;
}s[maxN];
void Init(int(*E)[maxN], Graph G, int N, int M) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			E[i][j] = -1;
		}
	}
	for (int i = 1; i <= N; i++) {
		G[i].indegree = 0;
		G[i].outdegree = 0;
		G[i].asap = 0;
		G[i].flexible = 99999;
		G[i].finished = 0;
		G[i].visited = 0;
	}
	for (int i = 1; i <= M; i++) {
		int p1, p2, t;
		scanf("%d %d %d\n", &p1, &p2, &t);
		G[p2].indegree++;
		G[p1].outdegree++;
		E[p1][p2] = t;
	}
}
int comp(const void* a, const void* b) {
	Stack p1 = (Stack)a;
	Stack p2 = (Stack)b;
	if (p1->s != p2->s) {
		return p2->s - p1->s;
	}
	else {
		return p1->d - p2->d;
	}
}
void Check(int(*E)[maxN], Graph G, int N) {
	int queue[maxN];
	int Q[maxN];
	int front, rear, top, f, r;
	top = front = rear = f = r = -1;
	int count = 0;
	int max = 0;
	for (int i = 1; i <= N; i++) {
		if (G[i].indegree == 0 && G[i].visited == 0) {
			queue[++rear] = i;
			G[i].visited = 1;
		}
	}
	while (front != rear) {
		int current = queue[++front];
		count++;
		for (int i = 1; i <= N; i++) {
			if (E[current][i] != -1) {
				if (G[i].asap < G[current].asap + E[current][i]) {
					G[i].asap = G[current].asap + E[current][i];
				}
				G[i].indegree--;
			}
		}
		/*if (flag == 0) {
			Q[++r] = current;
			G[current].flexible = G[current].asap;
			if (G[current].asap > max) {
				max = G[current].asap;
			}
			G[current].finished = 1;
		}*/
		for (int i = 1; i <= N; i++) {
			if (G[i].indegree == 0 && G[i].visited == 0) {
				queue[++rear] = i;
				G[i].visited = 1;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		if (G[i].outdegree == 0 && G[i].finished == 0) {
			Q[++r] = i;
			if (G[i].asap > max) {
				max = G[i].asap;
			}
			G[i].finished = 1;
		}
	}
	for (int i = 0; i <= N; i++) {
		if (G[i].outdegree == 0) {
			G[i].flexible = max;
		}
	}
	if (count != N) {
		printf("0\n");
		return;
	}
	else {
		printf("%d\n", max);
		while (f != r) {
			int current = Q[++f];
			for (int i = 1; i <= N; i++) {
				if (E[i][current] != -1) {
					if (G[i].flexible > G[current].flexible - E[i][current]) {
						G[i].flexible = G[current].flexible - E[i][current];
					}
					G[i].outdegree--;
					if (G[current].flexible - E[i][current] == G[i].asap) {
						s[++top].s = i;
						s[top].d = current;
					}
					if (G[i].outdegree == 0 && G[i].finished == 0) {
						Q[++r] = i;
						G[i].finished = 1;
					}
				}
			}
		}
		qsort(s, top + 1, sizeof(struct stacknode), comp);
		while (top > -1) {
			printf("%d->%d\n", s[top].s, s[top].d);
			top--;
		}
	}
}
int main() {
	freopen("Text.txt", "r", stdin);
	int N, M;
	int E[maxN][maxN];
	scanf("%d %d\n", &N, &M);
	Graph G = (Graph)malloc(sizeof(struct Gnode) * (N + 1));
	Init(E, G, N, M);
	Check(E, G, N);
	return 0;
}

