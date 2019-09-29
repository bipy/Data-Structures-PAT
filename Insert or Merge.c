#include<stdio.h>
#define maxN 102
void MergeSort(int* T, int N) {
	printf("Merge Sort\n");
	int ans[maxN];
	int length = 2;
	for (int len = length; len < N; len *= 2) {
		int flag = 0;
		for (int i = 0; i < N; i += len) {
			int rear = i + len > N ? N : i + len;
			for (int j = i; j < rear - 1; j++) {
				if (T[j] > T[j + 1]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}
		if (flag == 0) {
			length = len;
		}
	}
	//printf("%d\n", length);
	for (int i = 0; i < N; i++) {
		ans[i] = T[i];
	}
	for (int i = 0; i + length < N; i += 2 * length) {
		int p1 = i;
		int p2 = i + length;
		int rear = p2 + length;
		if (rear > N) {
			rear = N;
		}
		for (int j = p1; j < rear; j++) {
			if (p1 < i + length && p2 < rear) {
				if (T[p1] < T[p2]) {
					ans[j] = T[p1];
					p1++;
				}
				else if (T[p1] > T[p2]) {
					ans[j] = T[p2];
					p2++;
				}
			}
			else if (p1 < i + length && p2 >= rear) {
				ans[j] = T[p1];
				p1++;
			}
			else if (p1 >= i + length && p2 < rear) {
				ans[j] = T[p2];
				p2++;
			}
		}
	}
	for (int i = 0; i < N - 1; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d", ans[N - 1]);
}
void InsertionSort(int* T, int N, int Pos) {
	printf("Insertion Sort\n");
	int ans[maxN];
	int k = 0, t;
	for (int i = 0; i < N; i++) {
		ans[i] = T[i];
	}
	t = ans[Pos];
	while (t > ans[k]) {
		k++;
	}
	for (int i = Pos; i > k; i--) {
		ans[i] = ans[i - 1];
	}
	ans[k] = t;
	for (int i = 0; i < N - 1; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d", ans[N - 1]);
}
void Judge(int* a, int* T, int N) {
	int Pos;
	for (int i = 0; i < N - 1; i++) {
		if (T[i] > T[i + 1]) {
			for (int j = i + 1; j < N; j++) {
				if (T[j] != a[j]) {
					MergeSort(T, N);
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
	int data[maxN], T[maxN];
	int N, i;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &data[i]);
	}
	for (i = 0; i < N; i++) {
		scanf("%d", &T[i]);
	}
	Judge(data, T, N);
	return 0;
}