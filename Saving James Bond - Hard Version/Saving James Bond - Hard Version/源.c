#include<stdio.h>
#include<stdlib.h>
#define Border 50
#define MaxN 102
#define R 7.5
typedef struct crocodile* PtrC;
struct crocodile {
	int x;
	int y;
	int visited;
	int safe;
	int distance;
	int previous;
}Set[MaxN];
int Heap[MaxN];
void swap(int a, int b)
{
	int t = Heap[a];
	Heap[a] = Heap[b];
	Heap[b] = t;
}
void MinHeapify(int i, int HeapSize) {
	int min, l, r;
	l = 2 * i;
	r = 2 * i + 1;
	if (l <= HeapSize && Set[Heap[i]].distance > Set[Heap[l]].distance) {
		min = l;
	}
	else {
		min = i;
	}
	if (r <= HeapSize && Set[Heap[min]].distance > Set[Heap[r]].distance) {
		min = r;
	}
	if (min != i) {
		swap(min, i);
		MinHeapify(min, HeapSize);
	}
}
void BuildGraph(int N, int D)
{
	int i, x0, y0;
	Set[1].x = 0;
	Set[1].y = 0;
	Set[1].distance = 0;
	Set[1].visited = 0;
	Set[1].previous = -1;
	Set[1].safe = 0;
	for (i = 2; i <= N; i++) {
		scanf("%d %d\n", &x0, &y0);
		Set[i].x = x0;
		Set[i].y = y0;
		Set[i].distance = INT_MAX;
		Set[i].visited = 0;
		Set[i].previous = -1;
		if (Set[i].x >= (Border - D) || Set[i].x <= (D - Border) || Set[i].y >= (Border - D) || Set[i].y <= (D - Border)) {
			Set[i].safe = 1;
		}
		else {
			Set[i].safe = 0;
		}
	}
}
void BuildHeap(int N, int D) {
	int i;
	for (i = 1; i <= N; i++)
	{
		Heap[i] = i;
	}

	for (i = N / 2; i > 0; i--) {
		MinHeapify(i, N);
	}
}
int Delete(int HeapSize) {
	swap(1, HeapSize);
	HeapSize--;
	MinHeapify(1, HeapSize);
	return Heap[HeapSize + 1];
}

int distance(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int Check(int N, int D) {
	if (D >= Border - R) {
		return 1;
	}
	int i ,j=0, x, y, HeapSize,path[MaxN];
	double B;
	x = y = 0;
	HeapSize = N;
	while (HeapSize > 0) {
		int V = Delete(HeapSize--);
		x = Set[V].x;
		y = Set[V].y;
		if (x == 0 && y == 0) {
			B = (D + R) * (D + R);
		}
		else {
			B = D * D;
		}
		Set[V].visited = 1;
		for (i = 1; i <= N; i++) {
			if (Set[i].visited == 0 && B >= distance(Set[i].x, Set[i].y, x, y)) {
				if (Set[i].distance > Set[V].distance + distance(Set[i].x, Set[i].y, x, y))
				{
					Set[i].distance = Set[V].distance + distance(Set[i].x, Set[i].y, x, y);
					Set[i].previous = V;
					MinHeapify(1, HeapSize);
				}
			}
		}
	}
	for(i=1;i<=N;i++)
	{
		if(Set[i].safe==1&&Set[i].distance<INT_MAX)
		{
			path[j++] = i;
		}
	}
	return 0;
}
int main() {
	int N, D;
	scanf("%d %d", &N, &D);
	BuildGraph(N, D);
	BuildHeap(N, D);
	if(Check(N, D))
	{
		
	}
	return 0;
}