#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	char data;
	int left;
	int right;
}Tree;
Tree* T1, * T2;
int BuildTree(Tree T[],int N) {
	int i;
	char cl, cr;
	if (N) {
		int* check = (int*)malloc(sizeof(int) * N);
		for (i = 0; i < N; i++) {
			check[i] = 0;
		}

		for (i = 0; i < N; i++) {
			scanf("%c %c %c\n", &T[i].data, &cl, &cr);
			
			if (cl == '-') {
				T[i].left = -1;
			}
			else {
				T[i].left = cl - '0';
				check[T[i].left] = 1;
			}
			if (cr == '-') {
				T[i].right = -1;
			}
			else {
				T[i].right = cr - '0';
				check[T[i].right] = 1;
			}
		}
		for (i = 0; i < N; i++) {
			if (check[i] == 0)
				break;
		}
		return i;
	}
	else {
		return -1;
	}
}
int Iso(int R1, int R2) {
	if (R1 == -1 && R2 == -1) {
		return 1;
	}
	if (R1 != -1 && R2 == -1) {
		return 0;
	}
	if (R1 == -1 && R2 != -1) {
		return 0;
	}
	if (T1[R1].data != T2[R2].data) {
		return 0;
	}
	if (T1[R1].left == -1 && T2[R2].left == -1) {
		return Iso(T1[R1].right, T2[R2].right);
	}
	if ((T1[R1].left != -1 && T2[R2].left != -1 )&& (T1[T1[R1].left].data == T2[T2[R2].left].data)) {
		return Iso(T1[R1].right, T2[R2].right)&& Iso(T1[R1].left, T2[R2].left);
	}
	else {
		return Iso(T1[R1].left, T2[R2].right) && Iso(T1[R1].right, T2[R2].left);
	}
}
int main() {
	int N, R1, R2;
	scanf("%d\n", &N);
	
	T1 = (Tree*)malloc(sizeof(Tree) * N);
	R1 = BuildTree(T1, N);
	scanf("%d\n", &N);
	
	T2 = (Tree*)malloc(sizeof(Tree) * N);	
	R2 = BuildTree(T2, N);
	if (Iso(R1, R2) == 1) {
		printf("Yes\n");
	}
	else {
		printf("No\n");
	}
	return 0;
}