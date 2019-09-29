#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define maxQQLength 11
#define maxPWLength 17
typedef struct Lnode* List;
struct Lnode {
	char ID[maxQQLength];
	char PW[maxPWLength];
	List next;
};
typedef struct Hnode* HashTable;
struct Hnode {
	List Head;
	int TableSize;
};
int NextPrime(int N) {
	int P = N % 2 ? N + 2 : N + 1;
	int i, flag = 0;
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
	H->Head = (List)malloc(sizeof(struct Lnode) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++) {
		H->Head[i].next = NULL;
	}
	return H;
}
int Hash(HashTable H, int x) {
	return x % H->TableSize;
}
List NewNode(char* QQ, char* PW) {
	List T = (List)malloc(sizeof(struct Lnode));
	strcpy(T->ID, QQ);
	strcpy(T->PW, PW);
	T->next = NULL;
	return T;
}
int Insert(HashTable H, char* QQ, char* PW, int Pos) {
	List p = H->Head[Pos].next;
	while (p != NULL) {
		if (strcmp(p->ID, QQ) == 0) {
			return 0;
		}
		p = p->next;
	}
	List T = NewNode(QQ, PW);
	T->next = H->Head[Pos].next;
	H->Head[Pos].next = T;
	return 1;
}
int Login(HashTable H, char* QQ, char* PW, int Pos) {
	List p = H->Head[Pos].next;
	while (p != NULL) {
		if (strcmp(p->ID, QQ) == 0) {
			if (strcmp(p->PW, PW) == 0) {
				return 1;
			}
			else {
				return 0;
			}
		}
		p = p->next;
	}
	return -1;
}
int main() {
	freopen("Text.txt", "r", stdin);
	int N;
	scanf("%d\n", &N);
	HashTable H = CreateTable(N);
	for (int i = 0; i < N; i++) {
		char command;
		char QQ[maxQQLength];
		char PW[maxPWLength];
		scanf("%c", &command);
		scanf("%s %s\n", QQ, PW);
		int status;
		int Pos = Hash(H, atoi(QQ + (int)(0.4 * strlen(QQ))));
		switch (command)
		{
		case 'N':
			if (Insert(H, QQ, PW, Pos)) {
				printf("New: OK\n");
			}
			else {
				printf("ERROR: Exist\n");
			}
			break;
		case 'L':
			status = Login(H, QQ, PW, Pos);
			if (status == 1) {
				printf("Login: OK\n");
			}
			else if (status == 0) {
				printf("ERROR: Wrong PW\n");
			}
			else if (status == -1) {
				printf("ERROR: Not Exist\n");
			}
		default:
			break;
		}
	}
	return 0;
}