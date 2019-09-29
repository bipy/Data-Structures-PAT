#include<stdio.h>
#include<stdlib.h>
//此处实现快排
void swap(int* a, int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}
int Partition(int* a, int p, int r) {
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
void QuickSort(int* a, int p, int r) {
	if (p < r) {
		int q = Partition(a, p, r);
		QuickSort(a, p, q - 1);
		QuickSort(a, q + 1, r);
	}
}
//重点：---------------------------------------------
void inOrder(int* a, int n, int* in, int N){
	static int i = 0;	//static的作用
	if (n * 2 <= N) {						//因为BST用中序遍历即为由小到大，
		inOrder(a, 2 * n, in, N);			//所以此时反过来将排好序的数组按中序放进BST中	
											//因为是完全二叉树，所以用数组表示更便捷，类似堆
	}
	in[n] = a[i++];
	if (n * 2 + 1 <= N) {
		inOrder(a, n * 2 + 1, in, N);
	}
}
//--------------------------------------------------
int main() {
	int N, i;
	scanf("%d", &N);
	int* a = (int*)malloc(sizeof(int) * N);
	int* b = (int*)malloc(sizeof(int) * (N + 1));
	for (i = 0; i < N; i++) {
		scanf("%d", a + i);
	}
	QuickSort(a, 0, N - 1);
	inOrder(a, 1, b, N);
	for (i = 1; i <= N; i++) {
		i == N ? printf("%d", b[i]) : printf("%d ", b[i]);
	}

	return 0;
}