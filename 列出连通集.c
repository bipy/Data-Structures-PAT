#include<stdio.h>
#include<stdlib.h>
#define MaxN 10
typedef struct Gnode* Graph;
struct Gnode {
	int Nv;
	int Ne;
	int S[MaxN][MaxN];
};
typedef struct queue* PtrQ;
struct queue{
	int v[MaxN];
	int front;
	int rear;
};
PtrQ Creat() {
	PtrQ Q = (PtrQ)malloc(sizeof(struct queue));
	Q->front = Q->rear = 0;
	return Q;
}
int IsEmpty(PtrQ Q) {
	if (Q->front >= Q->rear) {
		return 1;
	}
	return 0;
}
int Dequeue(PtrQ Q) {
	if (!IsEmpty(Q))
		return Q->v[Q->front++];
	else
		return -1;
}
void Enqueue(PtrQ Q, int x) {
	Q->v[Q->rear++] = x;
}
void DFS(Graph G, int i,int* visited) {
	int j;
	visited[i] = 1;
	for (j = 0; j < G->Nv; j++) {
		if (G->S[i][j] == 1 && visited[j] == 0) {
			printf("%d ", j);
			DFS(G, j, visited);
		}
	}
}
void DFS_iterative(Graph G, int i, int* visited) {
	int j;
	int Stack[MaxN];
	int top=-1;
	visited[i] = 1;
	Stack[++top] = i;
	while (top > -1) {
		int current = Stack[top];	//取栈顶元素值，非出栈
		int flag = 0;	//判断参数
		for (j = 0; j < G->Nv; j++) {
			if (G->S[current][j] == 1 && visited[j] == 0) {
				printf("%d ", j);
				visited[j] = 1;
				flag = 1;	//有路可走时
				Stack[++top] = j;
				break;
			}
	}
		if (flag == 0) {		//无路可走则出栈
			top--;
		}
	}
}
void BFS(Graph G, PtrQ Q, int* visited, int i) {
	int j, v;
	Enqueue(Q, i);
	visited[i] = 1;
	while (!IsEmpty(Q)) {
		v = Dequeue(Q);
		printf("%d ", v);
		for (j = 0; j < G->Nv; j++) {
			if (visited[j] == 0 && G->S[v][j] == 1) {
				Enqueue(Q, j);
				visited[j] = 1;
			}
		}
	}
}
int main() {
	freopen("Text.txt", "r", stdin);
	int i, j, v1, v2;	
	Graph G = (Graph)malloc(sizeof(struct Gnode));
	PtrQ Q = Creat();
	scanf("%d %d", &G->Nv, &G->Ne);
	int* visited = (int*)malloc(sizeof(int) * G->Nv);
	for (i = 0; i < G->Nv; i++) {
		visited[i] = 0;
		for (j = 0; j < G->Nv; j++) {
			G->S[i][j] = 0;
		}
	}
	for (i = 0; i < G->Ne; i++) {
		scanf("%d %d", &v1, &v2);
		G->S[v1][v2] = 1;
		G->S[v2][v1] = 1;
	}
	for (i = 0; i < G->Nv; i++) {
		if (visited[i] == 0) {
			printf("{ %d ",i);
			DFS_iterative(G, i, visited);
			printf("}\n");
		}
	}
	for (i = 0; i < G->Nv; i++) {
		visited[i] = 0;
	}
	for (i = 0; i < G->Nv; i++) {
		if (visited[i] == 0) {
			printf("{ ");
			BFS(G, Q, visited, i);
			printf("}\n");
		}
	}
	return 0;
}