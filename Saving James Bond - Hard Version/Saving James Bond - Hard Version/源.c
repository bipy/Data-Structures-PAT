#include<stdio.h>
#include<stdlib.h>
#define Border 50
#define MaxN 101
#define R 7.5
typedef struct crocodile* PtrC;
struct crocodile {
	int x;
	int y;
	int visited;
	int safe;
	int distance;
}Set[MaxN];
void MinHeapify(int i, int HeapSize) {
	int min, l, r;
	l = 2 * i;
	r = 2 * i + 1;
	if (l <= HeapSize && Set[i].distance > Set[l].distance) {
		min = l;
	}
	else {
		min = i;
	}
	if (r <= HeapSize && H[min].f > H[r].f) {
		min = r;
	}
	if (min != i) {
		swap(min, i);
		MinHeapify(min, HeapSize);
	}
}
void BuildHeap(int N) {
	int i;
	for (i = 1; i <= N; i++) {
		char tc, tf;
		if (NULL == scanf("%c %c ", &tc, &tf)) {
			return;
		}
		C[i] = tc;
		F[i] = (int)(tf - 48);
		H[i].c = tc;
		H[i].f = (int)(tf - 48);
		H[i].left = NULL;
		H[i].right = NULL;
	}
	for (i = N / 2; i > 0; i--) {
		MinHeapify(i, N);
	}
}
HuffmanTree NewNode(int i) {
	HuffmanTree T = (HuffmanTree)malloc(sizeof(struct Huffman));
	T->c = H[i].c;
	T->left = H[i].left;
	T->right = H[i].right;
	T->f = H[i].f;
	return T;
}
HuffmanTree Delete(int HeapSize) {
	swap(1, HeapSize);
	HeapSize--;
	MinHeapify(1, HeapSize);
	return NewNode(HeapSize + 1);
}
void Insert(int HeapSize, HuffmanTree T) {
	int i = HeapSize;
	H[HeapSize].c = T->c;
	H[HeapSize].f = T->f;
	H[HeapSize].left = T->left;
	H[HeapSize].right = T->right;
	free(T);
	while (i / 2 > 0) {
		i /= 2;
		MinHeapify(i, HeapSize);
	}
}
void location(PtrC Set, int N, int D) {
	int i, x0, y0;
	Set->safe = 0;
	Set->visited = 0;
	Set->x = Set->y = 0;
	for (i = 1; i <= N; i++) {
		scanf("%d %d", &x0, &y0);
		(Set + i)->x = x0;
		(Set + i)->y = y0;
		(Set + i)->visited = 0;
		if ((Set + i)->x >= (Border - D) || (Set + i)->x <= (D - Border) || (Set + i)->y >= (Border - D) || (Set + i)->y <= (D - Border)) {
			(Set + i)->safe = 1;
		}
		else {
			(Set + i)->safe = 0;
		}
	}
}
int distance(int x1, int y1, int x2, int y2) {
	return (x1 - x2)* (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int Check(PtrC Set, int N, int D) {
	if (D >= Border - R) {
		return 1;
	}
	int i = 0, front, rear, x, y, B;
	int queue[MaxN];
	x = y = 0;
	front = rear = -1;
	Set->visited = 1;
	queue[++rear] = i;
	while (front < rear) {
		int V = queue[++front];
		x = ((Set + V)->x);
		y = ((Set + V)->y);
		if (x == 0 && y == 0) {
			B = (D + R) * (D + R);
		}
		else {
			B = D * D;
		}
		for (i = 0; i <= N; i++) {
			if ((Set + i)->visited == 0 && B >= distance((Set + i)->x, (Set + i)->y, x, y)) {
				if ((Set + i)->safe == 1) {
					return 1;
				}
				(Set + i)->visited = 1;
				queue[++rear] = i;
			}
		}
	}
	return 0;
}
int main() {
	int N, D;
	scanf("%d %d", &N, &D);
	location(N, D);
	Check(N, D) ? printf("Yes\n") : printf("No\n");
	return 0;
}