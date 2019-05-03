#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode *PTree;
typedef struct TreeNode {
	int data;
	PTree left, right;
	int flag;
}Tree;

PTree NewNode(int v) {
	PTree T = (PTree)malloc(sizeof(Tree));
	T->left = T->right = NULL;
	T->data = v;
	T->flag = 0;
	return T;
}
PTree Insert(PTree T,int v) {
	if (!T) {
		T = NewNode(v);
	}
	else {
		if (v > T->data) {
			T->right = Insert(T->right, v);
		}
		if (v < T->data) {
			T->left = Insert(T->left, v);
		}
	}
	return T;
}
int* GetArray(int N) {
	int* a = (int*)malloc(sizeof(int) * N);
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d", a + i);
	}
	return a;
}
PTree BuildTree(int N) {
	int i;
	int* a = GetArray(N);
	PTree T = NewNode(a[0]);
	for (i = 0; i < N; i++) {
		Insert(T, a[i]);
	}
	return T;	
}
int check(PTree T,int V) {
	if (T->flag) {
		if (V > T->data) {
			return check(T->right, V);
		}
		else if (V < T->data) {
			return check(T->left, V);
		}
		else {
			return 0;
		}
	}
	else {
		if (V == T->data) {
			T->flag = 1;
			return 1;
		}
		else {
			return 0;
		}
	}
}
int Judge(PTree T, int N) {
	int* a = GetArray(N);
	int i;
	for (i = 0; i < N; i++) {
		if (!check(T, a[i])) {
			return 0;
		}
	}
	return 1;
}
void ResetT(PTree T) /* 清除T中各结点的flag标记 */
{
	if (T->left) ResetT(T->left);
	if (T->right) ResetT(T->right);
	T->flag = 0;
}
void FreeTree(PTree T) /* 释放T的空间 */
{
	if (T->left) FreeTree(T->left);
	if (T->right) FreeTree(T->right);
	free(T);
}
int main() {
	int N, L, i;
	scanf("%d", &N);
	while (N) {
		scanf("%d", &L);
		PTree T = BuildTree(N);
		for (i = 0; i < L; i++) {
			if (Judge(T, N)) {
				printf("Yes\n");
			}
			else {
				printf("No\n");
			}
			ResetT(T);
		}
		FreeTree(T);
		scanf("%d", &N);
	}
	return 0;
}