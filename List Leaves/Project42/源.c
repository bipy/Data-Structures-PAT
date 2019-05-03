#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef struct TreeNode {
	int left;
	int right;
}Tree;
typedef struct QNODE {
	int data;
	struct QNODE* next;
}QNODE, * QPtr;
typedef struct {
	QPtr front;
	QPtr rear;
}linkqueue;
Tree* T;
int count=0;
linkqueue InitQueue() {
	linkqueue Q;
	Q.front = Q.rear = (QPtr)malloc(sizeof(QNODE));
	Q.front->next = NULL;
	return Q;
}
void Push(linkqueue* Q, int x) {
	QPtr p = (QPtr)malloc(sizeof(QNODE));
	p->data = x;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = Q->rear->next;
}
int Pop(linkqueue* Q) {
	if (Q->front == Q->rear) {
		return NULL;
	}
	else {
		int e;
		QPtr p = Q->front->next;
		Q->front->next = p->next;
		e = p->data;
		if (Q->rear == p)
			Q->rear = Q->front;
		free(p);
		return e;
	}
		

}
int BuildTree(Tree *T, int N) {
	int i;
	char cl, cr;
	if (N) {
		int* check = (int*)malloc(sizeof(int) * N);
		for (i = 0; i < N; i++) {
			check[i] = 0;
		}

		for (i = 0; i < N; i++) {
			scanf("%c %c", &cl, &cr);
			getchar();
			/*printf("next\n");*/
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
void order(Tree* T, int R) {
	int a[MAXSIZE];
	int i = 0,j;
	linkqueue Q = InitQueue();
	Push(&Q, R);
	while (Q.front != Q.rear) {
		int TR = Pop(&Q);
		if (T[TR].left == -1 && T[TR].right == -1) {
			a[i++] = TR;
		}
		if (T[TR].left != -1) {
			Push(&Q, T[TR].left);
		}
		if (T[TR].right != -1) {
			Push(&Q, T[TR].right);
		}		
	}
	for (j=0; j <i; j++) {
		j == i-1 ? printf("%d", a[j]) : printf("%d ", a[j]);
	}

}
int main() {
	int N,R;
	int a[MAXSIZE];
	scanf("%d", &N);
	getchar();
	T = (Tree*)malloc(sizeof(Tree) * N);
	R = BuildTree(T, N);
	order(T, R);
	
	return 0;

}