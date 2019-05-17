#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define TelLength 12
#define maxN 100010
#define scode 5
typedef struct Lnode* List, * PtrL;
struct Lnode {
	char tel[TelLength];
	PtrL next;
	int count;
};
typedef struct Hnode* HashTable;
struct Hnode {
	List Heads;
	int TableSize;
};
int Hash(int Tel, int N) {
	return Tel % N;
}
PtrL Find(HashTable H, char* Tel) {
	int Pos = Hash(atoi(Tel + TelLength - scode), H->TableSize);
	PtrL P = H->Heads[Pos].next;
	while (P != NULL && strcmp(P->tel, Tel) != 0) {
		P = P->next;
	}
	return P;
}
PtrL NewNode(char* Tel) {
	PtrL P = (PtrL)malloc(sizeof(struct Lnode));
	P->count = 1;
	P->next = NULL;
	strcpy(P->tel, Tel);
	return P;
}
void Insert(HashTable H, char* Tel) {
	PtrL P = Find(H, Tel);
	if (!P) {
		PtrL T = NewNode(Tel);
		int Pos = Hash(atoi(Tel + TelLength - scode), H->TableSize);
		T->next = H->Heads[Pos].next;
		H->Heads[Pos].next = T;
	}
	else {
		P->count++;
	}
}
int NextPrime(int N) {
	int P = N % 2 ? N + 2 : N + 1;
	int i;
	int flag = 0;
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
HashTable CreateTable(int N) {
	HashTable H = (HashTable)malloc(sizeof(struct Hnode));
	H->TableSize = NextPrime(N);
	H->Heads = (List)malloc(H->TableSize * sizeof(struct Lnode));
	for (int i = 0; i < H->TableSize; i++) {
		H->Heads[i].tel[0] = '\0';
		H->Heads[i].next = NULL;
		H->Heads[i].count = 0;
	}
	return H;


}
void Check(HashTable H) {
	PtrL Final = NULL;
	int Pcount = 0;
	for (int i = 0; i < H->TableSize; i++) {
		PtrL P = H->Heads[i].next;
		if (!Final) {
			Final = P;
		}
		while (P != NULL) {
			if (Final->count < P->count) {
				Final = P;
				Pcount = 1;
			}
			else if (Final->count == P->count) {
				Pcount++;
				if (strcmp(Final->tel, P->tel) > 0) {
					Final = P;
				}
			}
			P = P->next;
		}
	}
	printf("%s %d", Final->tel, Final->count);
	if (Pcount > 1) {
		printf(" %d", Pcount);
	}
}
int main() {
	freopen("Text.txt", "r", stdin);
	int N, i;
	char tel[TelLength];
	scanf("%d", &N);
	HashTable H = CreateTable(2 * N);
	for (i = 0; i < 2 * N; i++) {
		scanf("%s", tel);
		Insert(H, tel);
	}
	Check(H);
	return 0;
}