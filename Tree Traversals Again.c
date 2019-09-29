#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct StackNode {
	int data;
	struct stack* next;
}StackNode, * Ptrs;
typedef struct Stack {
	Ptrs top;
	Ptrs bottom;
}Stack, * pStack;
pStack InitStack() {
	pStack S = (pStack)malloc(sizeof(StackNode));
	S->bottom = S->top = (Ptrs)malloc(sizeof(StackNode));
	S->bottom->next = NULL;
	return S;
}
void Push(pStack S, int x) {
	Ptrs p = (Ptrs)malloc(sizeof(StackNode));
	p->data = x;
	p->next = S->top;
	S->top = p;
}
int Pop(pStack S) {
	if (S->top == S->bottom) {
		return NULL;
	}
	else {
		int e = S->top->data;
		Ptrs p = S->top;
		S->top = S->top->next;
		free(p);
		return e;
	}
}
//void GetPost(int* pre, int* in, int* post, int R, int left, int right) {
//	if (left == right) {
//		/**post = R;
//		post++;*/
//		printf("%d ", R);
//	}
//	else {
//		int i, l, r;
//		for (i = left; i <= R; i++) {	//找到pre的根 i，然后加1得到左树的根
//			if (pre[i] == in[R]) {
//				break;
//			}
//		}
//		for (l = left; l < R; l++) {	//找到in中的左子树根 l
//			if (in[l] == pre[i + 1]) {
//				break;
//			}
//		}
//		
//		if (left < R) {
//			GetPost(pre, in, post, l, left, R - 1);
//		}
//		for (r = R + 1; r <= right; r++) {
//			if (in[r] == pre[R + 1]) {
//				break;
//			}
//		}
//		if (R < right) {
//			GetPost(pre, in, post, r, R + 1, right);
//		}
//	}
//}
void solve(int* pre, int* in, int* post, int preL, int inL, int postL, int n)	//由前序和中序求后序
{
	int i, root, L, R;
	if (n == 0)
		return;
	if (n == 1)
	{
		post[postL] = pre[preL];
		return;
	}
	root = pre[preL];
	post[postL + n - 1] = root;
	for (i = 0; i < n; i++)
		if (in[inL + i] == root)
			break;
	L = i;
	R = n - L - 1;
	solve(pre, in, post, preL + 1, inL, postL, L);
	solve(pre, in, post, preL + L + 1, inL + L + 1, postL + L, R);

}
int main() {
	int N, i, x, j = 0, k = 0;
	char s[5];
	pStack S = InitStack();
	scanf("%d", &N);
	getchar();
	int* pre = (int*)malloc(sizeof(int) * N);
	int* in = (int*)malloc(sizeof(int) * N);
	int* post = (int*)malloc(sizeof(int) * N);
	int* p = post;
	for (i = 0; i < 2*N; i++) {
		scanf("%s", s);
		if (strcmp(s, "Push") == 0) {
			scanf("%d", &x);
			getchar();
			Push(S, x);
			pre[j++] = x;
		}
		else {
			in[k++] = Pop(S);
		}
	}
	for (i = 0; i < N; i++) {
		if (in[i] == pre[0]) {
			break;
		}
	}
	solve(pre, in, post, 0, 0, 0, N);
	/*GetPost(pre, in, post, i, 0, N-1);*/
	for (i = 0; i < N; i++) {
		i == N - 1 ? printf("%d", p[i]) : printf("%d ", p[i]);
	}
	return 0;
}