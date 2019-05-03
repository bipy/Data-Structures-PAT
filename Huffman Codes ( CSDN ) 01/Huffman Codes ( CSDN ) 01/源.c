#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxn 64

int N, w[Maxn];
char ch[Maxn];
int codelen, cnt1, cnt2;

typedef struct TreeNode* Tree;
struct TreeNode {
	int Weight;
	Tree Left, Right;
};

typedef struct HeapNode* Heap;
struct HeapNode {
	struct TreeNode Data[Maxn];
	int Size;
};

Tree CreatTree() {
	Tree T;
	T = (Tree)malloc(sizeof(struct TreeNode));
	T->Left = T->Right = NULL;
	T->Weight = 0;
	return T;
}

Heap CreatHeap() {
	Heap H;
	H = (Heap)malloc(sizeof(struct HeapNode));
	H->Size = 0;
	H->Data[0].Weight = -1;
	return H;
}

void Insert(Heap H, struct TreeNode T) {
	int i = ++H->Size;
	for (; T.Weight < H->Data[i / 2].Weight; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = T;
}

Tree Delete(Heap H) {
	int parent, child;
	struct TreeNode Temp = H->Data[H->Size--];
	Tree T = CreatTree();
	*T = H->Data[1];
	for (parent = 1; 2 * parent <= H->Size; parent = child) {
		child = 2 * parent;
		if (child != H->Size && H->Data[child].Weight > H->Data[child + 1].Weight) child++;
		if (Temp.Weight < H->Data[child].Weight) break;
		H->Data[parent] = H->Data[child];
	}
	H->Data[parent] = Temp;
	return T;
}

Tree Huffman(Heap H) {
	Tree T = CreatTree(); //分配空间
	while (H->Size != 1) {
		T->Left = Delete(H);
		T->Right = Delete(H);
		T->Weight = T->Left->Weight + T->Right->Weight;
		//printf("l = %d, r = %d, t = %d\n", T->Left->Weight, T->Right->Weight, T->Weight);
		Insert(H, *T);
	}
	T = Delete(H);
	return T;
}

void PreTravel(Tree T) {
	if (T) {
		printf("%d ", T->Weight);
		PreTravel(T->Left);
		PreTravel(T->Right);
	}
}

int WPL(Tree T, int Depth) {
	if (!T->Left && !T->Right) { /*printf("d = %d w = %d\n", Depth, T->Weight);*/ return Depth * T->Weight; }
	else return WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1);
}

void JudgeTree(Tree T) {
	if (T) {
		if (T->Left && T->Right) cnt2++;
		else if (!T->Left && !T->Right) cnt1++;
		else cnt1 = 0;
		JudgeTree(T->Left);
		JudgeTree(T->Right);
	}
}

int Judge() {
	int i, j, wgh, flag = 1;
	char s1[Maxn], s2[Maxn];
	Tree T = CreatTree(), pt = NULL;
	for (i = 0; i < N; i++) {
		scanf("%s%s", s1, s2);
		if (strlen(s2) > N) return 0;
		for (j = 0; s1[0] != ch[j]; j++); wgh = w[j];
		pt = T;//每次建树前先将指针移动到根节点上；
		for (j = 0; s2[j]; j++) {
			if (s2[j] == '0') {
				if (!pt->Left) pt->Left = CreatTree();
				pt = pt->Left;
			}
			if (s2[j] == '1') {
				if (!pt->Right) pt->Right = CreatTree();
				pt = pt->Right;
			}
			if (pt->Weight) flag = 0;
			if (!s2[j + 1]) {
				if (pt->Left || pt->Right) flag = 0;//判断是否为前缀
				pt->Weight = wgh;
			}
			//printf("w = %d\n", pt->Weight);
		}
	}
	if (!flag) return 0;
	cnt1 = cnt2 = 0;
	JudgeTree(T);//判断是否不存在度数1的节点
	if (cnt1 != cnt2 + 1) return 0;
	//printf("wpl = %d\n", WPL(T, 0));
	if (codelen == WPL(T, 0)) return 1;
	else return 0;
}

int main() {
	int i, n;
	Heap H;
	Tree T;
	H = CreatHeap();
	T = CreatTree();
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		getchar();
		scanf("%c %d", &ch[i], &w[i]);
		H->Data[H->Size].Left = H->Data[H->Size].Right = NULL;
		T->Weight = w[i];
		Insert(H, *T);
	}
	//for(i = 1; i <= H->Size; i++) printf("%d ", H->Data[i].Weight);
	T = Huffman(H);     //PreTravel(T);
	codelen = WPL(T, 0);
	scanf("%d", &n);
	while (n--) {
		if (Judge()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
