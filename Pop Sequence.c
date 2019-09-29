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
	int size;
}Stack, * pStack;
pStack InitStack() {
	pStack S = (pStack)malloc(sizeof(StackNode));
	S->bottom = S->top = (Ptrs)malloc(sizeof(StackNode));
	S->bottom->next = NULL;
	S->size = 0;
	return S;
}
void Push(pStack S, int x) {
	Ptrs p = (Ptrs)malloc(sizeof(StackNode));
	p->data = x;
	p->next = S->top;
	S->top = p;
	S->size++;
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
		S->size--;
		return e;
	}
}
void delStack(pStack S) {
	while (S->size > 0) {
		Pop(S);
	}
}
int main() {
	int M, N, K;
	int i;
	pStack S = InitStack();
	scanf("%d %d %d", &M, &N, &K);
	
	while (K--) {
		int flag = 1;
		int j = 2;
		int* data = (int*)malloc(sizeof(int) * N);
		Push(S, 1);
		for (i = 0; i < N; i++) {
			scanf("%d", data+i);
		}
		for (i = 0; i < N; i++) {
			/*if (data >= M && data <= N) {
				if (check > data) {
					flag = 0;
					break;
				}
				check = data;
			}*/
			
			while (S->size!=0&&data[i] > S->top->data||S->size==0&&i<N) {
				Push(S, j++);
				if (S->size > M) {
					flag = 0;
					break;
				}
			}
					
			if (data[i] == S->top->data&&S->size>0) {
				Pop(S);
			}
			else if (S->size>0&&data[i] < S->top->data) {
				flag = 0;
				break;
			}
			/*if (S->top == S->bottom && i == N - 1) {
				flag == 1;
			}*/
		}
		if (flag == 0) {
			printf("NO\n");
		}
		else {
			printf("YES\n");
		}
		delStack(S);
		free(data);
	}
	return 0;
}