//最大N&M，code长度等于63			答案错误	
//最小N& M						答案错误
//原因未知
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXCODE 64
typedef struct Huffman* HuffmanTree, * Heap;
struct Huffman {
	char c;
	int f;
	HuffmanTree left, right;
}H[MAXCODE];
typedef struct HuffmanCode* CODE;
//struct HuffmanCode {
//	char c;
//	char s[MAXCODE];
//}CODE[MAXCODE];
char C[MAXCODE];
int F[MAXCODE];

void swap(int b, int a) {
	char tc;
	int tf;
	HuffmanTree tl, tr;
	tc = H[a].c;
	tf = H[a].f;
	tl = H[a].left;
	tr = H[a].right;
	H[a].c = H[b].c;
	H[a].f = H[b].f;
	H[a].left = H[b].left;
	H[a].right = H[b].right;
	H[b].c = tc;
	H[b].f = tf;
	H[b].left = tl;
	H[b].right = tr;
}
void MinHeapify(int i, int HeapSize) {
	int min, l, r;
	l = 2 * i;
	r = 2 * i + 1;
	if (l <= HeapSize && H[i].f > H[l].f) {
		min = l;
	}
	else {
		min = i;
	}
	if (r <= HeapSize && H[min].f > H[r].f) {
		min = r;
	}
	if (min != i) {
		swap(min, i);
		MinHeapify(min, HeapSize);
	}
}
void BuildHeap(int N) {
	int i;
	for (i = 1; i <= N; i++) {
		char tc, tf;
		if (NULL == scanf("%c %c ", &tc, &tf)) {
			return;
		}
		C[i] = tc;
		F[i] = (int)(tf - 48);
		H[i].c = tc;
		H[i].f = (int)(tf - 48);
		H[i].left = NULL;
		H[i].right = NULL;
	}
	for (i = N / 2; i > 0; i--) {
		MinHeapify(i, N);
	}
}
HuffmanTree NewNode(int i) {
	HuffmanTree T = (HuffmanTree)malloc(sizeof(struct Huffman));
	T->c = H[i].c;
	T->left = H[i].left;
	T->right = H[i].right;
	T->f = H[i].f;
	return T;
}
HuffmanTree Delete(int HeapSize) {
	swap(1, HeapSize);
	HeapSize--;
	MinHeapify(1, HeapSize);
	return NewNode(HeapSize + 1);
}
void Insert(int HeapSize,HuffmanTree T) {
	int i=HeapSize;
	H[HeapSize].c = T->c;
	H[HeapSize].f = T->f;
	H[HeapSize].left = T->left;
	H[HeapSize].right = T->right;
	free(T);
	while (i / 2 > 0) {
		i /= 2;
		MinHeapify(i, HeapSize);
	}
}
HuffmanTree Huffman(int N) {
	int i;
	int HeapSize = N;
	for (i = 1; i < N; i++) {
		HuffmanTree T= (HuffmanTree)malloc(sizeof(struct Huffman));
		T->left = Delete(HeapSize--);
		T->right = Delete(HeapSize--);
		T->c = NULL;
		T->f = T->left->f + T->right->f;
		Insert(++HeapSize, T);
	}
	return Delete(HeapSize);
}
int WPL(HuffmanTree T,int depth) {
	if (T->left == NULL && T->right == NULL) {
		return depth * T->f;
	}
	else {
		return WPL(T->left, depth + 1) + WPL(T->right, depth + 1);
	}
}
int getmin(int a, int b) {
	return a < b ? a : b;
}
int Check(int M, int N,int codelen) {
	int i, j, k;
	char c[MAXCODE];
	char s[MAXCODE][MAXCODE];
	int thislen=0;
	/*CODE code = (CODE)malloc(sizeof(struct HuffmanCode) * MAXCODE);*/
	for (i = 0; i < N; i++) {
		scanf("%c %s", &c[i], s[i]);
		getchar();
		/*printf("%c %s\n", code[i].c, code[i].s);*/
		for (j = 1; j <= N; j++) {
			if (c[i] == C[j]) {
				thislen += strlen(s[i]) * F[j];
			}
		}
	}
	if (thislen == codelen) {
		for (i = 0; i < N; i++) {
			for (j = i + 1; j < N; j++) {
				int flag = 0;
				for (k = 0; k < getmin(strlen(s[i]), strlen(s[j])); k++) {
					if (s[i][k] != s[j][k]) {
						flag = 1;
					}
					
				}
				if (flag != 1) {
					return 0;
				}
			}
		}
		return 1;
	}
	else {
		return 0;
	}

}
int main() {
	/*freopen("Test.txt","r", stdin);*/
	int N, M, i, codelen;
	H[0].f = -1;
	scanf("%d\n", &N);
	BuildHeap(N);
	codelen = WPL(Huffman(N),0);
	/*printf("\n %d\n", codelen);*/
	scanf("%d\n", &M);
	for (i = 0; i < M; i++) {
		Check(M, N, codelen) ? printf("Yes\n") : printf("No\n");
	}
	return 0;
}