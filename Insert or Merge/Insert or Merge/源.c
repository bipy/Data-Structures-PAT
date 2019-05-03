#include<stdio.h>
#define maxN 101
int original[maxN];
int Judge(int* a, int* T, int N) {
	for (int i = 0; i < N; i++) {
		if (a[i] != T[i]) {
			return 0;
		}
	}
	return 1;
}
void MergeSort(int* a, int x, int r, int* T) {
	if (r - x > 1) {
		int m = (x + r) / 2;
		int i = x, q = m, p = x;
		MergeSort(a, x, m, T);
		MergeSort(a, m, r, T);
		while (p < m || q < r) {
			if (q >= r || (p < m && a[p] <= a[q]))
				T[i++] = a[p++];
			else
				T[i++] = a[q++];
		}
		for (i = x; i < r; i++) {
			a[i] = T[i];
		}
	}
}
void InsertionSort(int* a, int N) {
	int i, j, k;
	int flag = 0;
	for (i = 1; i < N; i++) {
		k = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > k) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = k;
		if (flag == 1) {
			return;
		}
		if (Judge(original, a, N)) {
			flag = 1;
		}
	}
}
int main() {
	freopen("Text.txt", "r", stdin);
	int data[maxN], T[maxN];
	int N, i;
	if (NULL == scanf("%d", &N)) {
		return;
	}
	for (i = 0; i < N; i++) {
		int x;
		if (NULL == scanf("%d", &x)) {
			return;
		}
		original[i] = x;
	}
	for (i = 0; i < N; i++) {
		int x;
		if (NULL == scanf("%d", &x)) {
			return;
		}
		data[i] = x;
	}


}