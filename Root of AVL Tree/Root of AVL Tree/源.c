#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode {
	int data;
	Tree left, right;
	int Height;
};
Tree NewNode(int v) {
	Tree p = (Tree)malloc(sizeof(struct TreeNode));
	p->left = p->right = NULL;
	p->data = v;
	p->Height = 0;
	return p;
}
int GetHeight(Tree T) {
	return T == NULL ? 0 : T->Height;
}
int MAX(int a, int b) {
	return a > b ? a : b;
}
void RE_Height(Tree T) {
	T->Height = MAX(GetHeight(T->left), GetHeight(T->right)) + 1;
}


Tree left_left_rotation(Tree T) {
	Tree K;
	K = T->left;
	T->left = K->right;
	K->right = T;
	RE_Height(T);
	RE_Height(K);
	return K;
}
Tree right_right_rotation(Tree T) {
	Tree K;
	K = T->right;
	T->right = K->left;
	K->left = T;
	RE_Height(T);
	RE_Height(K);
	return K;
}
Tree left_right_rotation(Tree T) {
	T->left = right_right_rotation(T->left);
	return left_left_rotation(T);
}
Tree right_left_rotation(Tree T) {
	T->right = left_left_rotation(T->right);
	return right_right_rotation(T);
}
Tree Insert(Tree T, int V) {
	if (!T) {
		T = NewNode(V);
	}
	else {
		if (V > T->data) {
			T->right = Insert(T->right, V);
			if (GetHeight(T->left) - GetHeight(T->right) == -2) {
				if (T->right->data > V) {
					T = right_left_rotation(T);
				}
				else {
					T = right_right_rotation(T);
				}
			}
		}
		else if (V < T->data) {
			T->left = Insert(T->left, V);
			if (GetHeight(T->left) - GetHeight(T->right) == 2) {
				if (T->left->data > V) {
					T = left_left_rotation(T);
				}
				else {
					T = left_right_rotation(T);
				}
			}
		}
	}
	RE_Height(T);
	return T;
}
int main() {
	int N, i,V;
	Tree T = NULL;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &V);
		T=Insert(T,V);
	}
	printf("%d", T->data);	
	return 0;
}