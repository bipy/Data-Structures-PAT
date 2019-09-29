#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Lnode* List;
struct Lnode {
	int key;
	int Cnum;
	int suppose;
	int inserted;
};
typedef struct Hnode* HashTable;
struct Hnode {
	List List;
	int TableSize;
	int total;
};
typedef struct comparray* Clist;
struct comparray {
	int key;
	int index;
};
int Hash(HashTable H, int x) {
	return x % H->TableSize;
}
HashTable CreatTable(int N) {
	HashTable H = (HashTable)malloc(sizeof(struct Hnode));
	H->TableSize = N;
	H->total = 0;
	H->List = (List)malloc(sizeof(struct Lnode) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++) {
		int t;
		scanf("%d", &t);
		if (t > -1) {
			H->total++;
		}
		H->List[i].key = t;
		H->List[i].inserted = 0;
		H->List[i].suppose = Hash(H, t);
		if (i < H->List[i].suppose) {
			H->List[i].Cnum = i - H->List[i].suppose + H->TableSize;
		}
		else {
			H->List[i].Cnum = i - H->List[i].suppose;
		}
	}
	return H;
}
int comp(const void* a, const void* b) {
	Clist p1 = (Clist)a;
	Clist p2 = (Clist)b;
	return p1->key - p2->key;
}
Clist CreateCompareArray(HashTable H) {
	Clist P = (Clist)malloc(sizeof(struct comparray) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++) {
		P[i].index = i;
		P[i].key = H->List[i].key;
	}
	qsort(P, H->TableSize, sizeof(struct comparray), comp);
	return P;
}
void Check(HashTable H, Clist P) {
	int* sort = (int*)malloc(sizeof(int) * H->TableSize);
	int current = 0;
	for (int i = 0; i < H->TableSize; i++) {
		P[i].key = -1;
	}
	while (current != H->total) {
		for (int i = 0; i < H->TableSize; i++) {
			int sorted = P[i].index;
			if (H->List[sorted].key > -1 && H->List[sorted].inserted == 0) {
				int flag = 0;
				if (sorted == H->List[sorted].suppose) {
					P[sorted].key = H->List[sorted].key;
				}
				if (sorted < H->List[sorted].suppose) {
					for (int k = H->List[sorted].suppose; k < H->TableSize; k++) {
						if (P[k].key <= -1) {
							flag = 1;
							break;
						}
					}
					if (flag != 1) {
						for (int k = 0; k < sorted; k++) {
							if (P[k].key <= -1) {
								flag = 1;
								break;
							}
						}
					}
				}
				else {
					for (int k = H->List[sorted].suppose; k < sorted; k++) {
						if (P[k].key <= -1) {
							flag = 1;
							break;
						}
					}
				}
				if (flag == 0) {
					P[sorted].key = H->List[sorted].key;
					sort[current++] = H->List[sorted].key;
					H->List[sorted].inserted = 1;
					break;
				}
			}
		}
	}
	for (int i = 0; i < H->total; i++) {
		if (i == H->total - 1) {
			printf("%d", sort[i]);
		}
		else {
			printf("%d ", sort[i]);
		}
	}
}
int main() {
	/*freopen("Text.txt", "r", stdin);*/
	int N;
	scanf("%d", &N);
	HashTable H = CreatTable(N);
	Clist P = CreateCompareArray(H);
	Check(H, P);
	return 0;
}