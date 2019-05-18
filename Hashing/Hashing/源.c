#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Hnode* HashTable;
struct Hnode {
	int* List;
	int TableSize;
};
int NextPrime(int N) {
	if (N == 1) {
		return 2;
	}
	else {
		int P = N % 2 ? N : N + 1;
		int flag = 0, i;
		while (flag == 0) {
			for (i = (int)sqrt(P); i > 1; i--) {
				if (P % i == 0) {
					P += 2;
					break;
				}
			}
			if (i == 1 || P == 2 || P == 3) {
				flag = 1;
			}
		}
		return P;
	}
}
int Hash(HashTable H, int x) {
	return x % H->TableSize;
}
HashTable CreatTable(int N) {
	HashTable H = (HashTable)malloc(sizeof(struct Hnode) * N);
	H->TableSize = NextPrime(N);
	H->List = (int*)malloc(sizeof(int) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++) {
		H->List[i] = -1;
	}
	return H;
}
int Insert(HashTable H, int x) {
	int Position = Hash(H, x);
	if (H->List[Position] == -1) {
		H->List[Position] = x;
		return Position;
	}
	else {
		for (int i = 1; i <= H->TableSize / 2; i++) {
			int Pos = Position + i * i;
			while (Pos >= H->TableSize) {
				Pos -= H->TableSize;
			}
			if (H->List[Pos] == -1) {
				H->List[Pos] = x;
				return Pos;
			}
		}
		return -1;
	}
}
int main() {
	/*freopen("Text.txt", "r", stdin);*/
	int N, Msize;
	scanf("%d %d", &Msize, &N);
	HashTable H = CreatTable(Msize);
	for (int i = 0; i < N; i++) {
		int t, p;
		scanf("%d", &t);
		p = Insert(H, t);
		if (i != N - 1) {
			if (p != -1) {
				printf("%d ", p);
			}
			else {
				printf("- ");
			}
		}
		else {
			if (p != -1) {
				printf("%d", p);
			}
			else {
				printf("-");
			}
		}
	}
	return 0;
}