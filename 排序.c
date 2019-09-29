#include<stdio.h>
#include<stdlib.h>
#define maxN 100000
//Quick Sort
void swap(long int* a, int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int Partition(long int* a, int p, int r) {
	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (a[j] <= x) {
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);
	return i + 1;
}

//random
int Randomized_Partition(long int* a, int p, int r) {
	int i = rand() % (r - p + 1) + p;
	swap(a, i, r);
	return Partition(a, p, r);
}

void QuickSort(long int* a, int p, int r) {
	if (p < r) {
		int q = Randomized_Partition(a, p, r);
		QuickSort(a, p, q - 1);
		QuickSort(a, q + 1, r);
	}
}


//HeapSort

//int left(int x) {
//	return 2 * x + 1;
//}
//int right(int x) {
//	return 2 * x + 2;
//}
//int father(int x) {
//	return (x - 1) / 2;
//}
//void swap(long int* array, int x, int y) {
//	int t = array[x];
//	array[x] = array[y];
//	array[y] = t;
//}
//void MaxHeapify(long int* array, int i, int HeapSize) {
//	int max, l, r;
//	l = left(i);
//	r = right(i);
//	if (l < HeapSize && array[i] <= array[l]) {
//		max = l;
//	}
//	else {
//		max = i;
//	}
//	if (r < HeapSize && array[max] <= array[r]) {
//		max = r;
//	}
//	if (max != i) {
//		swap(array, max, i);
//		MaxHeapify(array, max, HeapSize);
//	}
//
//}
//void buildMaxHeap(long int* array, int N) {
//	for (int i = (N - 1) / 2; i >= 0; i--) {
//		MaxHeapify(array, i, N);
//	}
//
//}
//
//void HeapSort(long int* array, int N) {
//	int HeapSize = N;
//	buildMaxHeap(array, N);
//	for (int i = 0; i < N; i++) {
//		swap(array, 0, HeapSize - 1);
//		MaxHeapify(array, 0, --HeapSize);
//	}
//
//}

//MergeSort
//void MergeSort(long int* a, int x, int r, long int* T) {
//	if (r - x > 1) {
//		int m = (x + r) / 2;
//		int i = x, q = m, p = x;
//		MergeSort(a, x, m, T);
//		MergeSort(a, m, r, T);
//		while (p < m || q < r) {
//			if (q >= r || (p < m && a[p] <= a[q]))
//				T[i++] = a[p++];
//			else
//				T[i++] = a[q++];
//		}
//		for (i = x; i < r; i++) {
//			a[i] = T[i];
//		}
//	}
//
//}

//Insertion Sort
//void InsertionSort(long int* a, int N) {
//	int i, j, k;
//	for (i = 1; i < N; i++) {
//		k = a[i];
//		j = i - 1;
//		while (j >= 0 && a[j] > k) {
//			a[j + 1] = a[j];
//			j--;
//		}
//		a[j + 1] = k;
//	}
//}

//BubbleSort
//void BubbleSort(long int* a, int N) {
//	int i, j;
//	for (i = 0; i < N; i++) {
//		for (j = 1; j < N - i; j++) {
//			if (a[j - 1] > a[j]) {
//				int t = a[j - 1];
//				a[j - 1] = a[j];
//				a[j] = t;
//			}
//		}
//	}
//}


int main() {
	int N, i;
	long int data[maxN];
	long int T[maxN];
	if (NULL == scanf("%d", &N)) {
		return;
	}
	for (i = 0; i < N; i++) {
		if (NULL == scanf("%ld", &data[i])) {
			return;
		}
	}
	QuickSort(data, 0, N-1);
	for (i = 0; i < N; i++) {
		i == N - 1 ? printf("%d", data[i]) : printf("%d ", data[i]);
	}
	return 0;
}