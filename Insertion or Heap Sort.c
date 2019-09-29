#include<stdio.h>
#include<stdlib.h>
#define maxN 102
void swap(int* H, int a, int b) {
	int t = H[a];
	H[a] = H[b];
	H[b] = t;
}
void MaxHeapify(int* H, int i,int HeapSize) {
	int max;
	int l = i * 2;
	int r = i * 2 + 1;
	if (l <= HeapSize && H[l] > H[i]) {
		max = l;
	}
	else {
		max = i;
	}
	if (r <= HeapSize && H[r] > H[max]) {
		max = r;
	}
	if (max != i) {
		swap(H, max, i);
		MaxHeapify(H, max, HeapSize);
	}
}
void HeapSort(int* T, int N) {
	printf("Heap Sort\n");
	int ans[maxN];
	int Pos = N;
	for (int i = 1; i <= N; i++) {
		ans[i] = T[i];
	}
	for (int i = N; i > 0; i--) {
		if (ans[i] < ans[1]) {
			Pos = i;
			break;
		}
	}
	swap(ans, 1, Pos);
	MaxHeapify(ans, 1, --Pos);
	for (int i = 1; i < N; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d", ans[N]);

}
void InsertionSort(int* T, int N, int Pos) {
	printf("Insertion Sort\n");
	int ans[maxN];
	int t = T[Pos];
	int k = 1;
	for (int i = 1; i <= N; i++) {
		ans[i] = T[i];
	}
	while (ans[k] < t) {
		k++;
	}
	for (int i = Pos; i > k; i--) {
		ans[i] = ans[i - 1];
	}
	ans[k] = t;
	for (int i = 1; i < N; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d", ans[N]);

}
void Judge(int* data, int* T, int N) {
	int Pos = 1;
	for (int i = 1; i < N; i++) {
		if (T[i] > T[i + 1]) {
			for (int j = i + 1; j <= N; j++) {
				if (T[j] != data[j]) {
					HeapSort(T, N);
					return;
				}
			}
			Pos = i + 1;
			break;
		}
	}
	InsertionSort(T, N, Pos);
}
int main() {
	freopen("Text.txt", "r", stdin);
	int N;
	int original[maxN];
	int temp[maxN];
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &original[i]);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &temp[i]);
	}
	Judge(original, temp, N);
	return 0;
}