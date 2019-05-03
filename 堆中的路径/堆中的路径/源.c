#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int data[1001];
	int size;
}Heap;
int lchild(int i) {
	return 2 * i;
}
int rchild(int i) {
	return 2 * i + 1;
}
int father(int i) {
	return i / 2;
}
void Insert(Heap* H, int X) {
	int i = ++H->size;
	while (H->data[father(i)] > X) {
		H->data[i] = H->data[father(i)];
		i = father(i);
	}
	H->data[i] = X;
}
void Path(Heap* H, int i) {
	while (i != 1) {
		printf("%d ", H->data[i]);
		i = father(i);
	}
	printf("%d\n", H->data[1]);
}
int main() {
	int N, M, i, j, X;
	scanf("%d %d", &N, &M);
	Heap* H = (Heap*)malloc(sizeof(Heap));
	H->size = 0;
	H->data[0] = -10001;
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		Insert(H, X);
	}
	for (i = 0; i < M; i++) {
		scanf("%d", &j);
		Path(H, j);
	}
	return 0;
}
