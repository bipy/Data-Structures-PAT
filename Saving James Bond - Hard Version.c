#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Border 50
#define MaxN 102
#define R 7.5
#define MAXD 99999
struct crocodile {
	int x;
	int y;
	int visited;
	int safe;
	double distance;
	int previous;
}Set[MaxN];
int Heap[MaxN];
int path[MaxN];
int N, D;
void swap(int a, int b)
{
	int t = Heap[a];
	Heap[a] = Heap[b];
	Heap[b] = t;
}
double distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
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
void BuildGraph()
{
	int i, x0, y0;
	Set[1].x = 0;
	Set[1].y = 0;
	Set[1].distance = 0;
	Set[1].visited = 0;
	Set[1].previous = -1;
	Set[1].safe = 0;
	for (i = 2; i <= N; i++) {
		scanf("%d %d", &x0, &y0);
		if (distance(x0,y0,0,0)<=R || abs(x0) >= Border || abs(y0) >= Border) {
			N--;
			i--;
			continue;
		}
		Set[i].x = x0;
		Set[i].y = y0;
		Set[i].distance = MAXD;
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
void BuildHeap() {
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
int Check() {
	int i, j = 0, x, y, HeapSize;
	double B;
	x = y = 0;
	HeapSize = N;
	while (HeapSize > 0) {
		int V = Delete(HeapSize--);
		x = Set[V].x;
		y = Set[V].y;
		if (x == 0 && y == 0) {
			B = D + R;
		}
		else {
			B = D;
		}
		Set[V].visited = 1;
		for (i = 1; i <= N; i++) {
			if (Set[i].visited == 0 && B >= distance(Set[i].x, Set[i].y, x, y)) {
				if (Set[i].distance > Set[V].distance + distance(Set[i].x, Set[i].y, x, y) - (B - D))
				{
					Set[i].distance = Set[V].distance + distance(Set[i].x, Set[i].y, x, y) - (B - D);
					Set[i].previous = V;
					for (int i = HeapSize / 2; i > 0; i--) {
						MinHeapify(i, HeapSize);
					}
				}
			}
		}
	}
	for (i = 1; i <= N; i++)
	{
		if (Set[i].safe == 1 && Set[i].distance < MAXD)
		{
			path[j++] = i;
		}
	}
	return j;
}
void showpath(int paths) {
	if (paths != 0) {
		double min = -1;
		int stack[MaxN];
		int top = -1, c = 0;
		for (int i = 0; i < paths; i++) {
			int k = path[i];
			while (Set[k].previous != 1) {
				k = Set[k].previous;
			}
			if (min == -1) {
				min = Set[k].distance;
			}
			if (min >= Set[k].distance) {
				min = Set[k].distance;
				c = path[i];
			}
		}
		while (Set[c].previous != -1) {
			stack[++top] = c;
			c = Set[c].previous;
		}
		printf("%d\n", top + 2);
		while (top > -1) {
			int t = stack[top--];
			printf("%d %d\n", Set[t].x, Set[t].y);
		}
	}
	else {
		printf("0");
	}
}
int main() {
	/*freopen("Text.txt", "r", stdin);*/
	scanf("%d %d", &N, &D);
	N++;
	if (D >= Border - R) {
		printf("1");
	}
	else {
		BuildGraph();
		BuildHeap();
		showpath(Check());
	}
	return 0;
}