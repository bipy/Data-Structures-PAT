#include<stdio.h>
#include<stdlib.h>
#define maxK 6
#define maxN 10000
#define maxM 100000
typedef struct user* PtrU;
struct user {
	int score[maxK];
	int total;
	int full;
};
void swap(int* rank, int i, int j) {
	int t = rank[i];
	rank[i] = rank[j];
	rank[j] = t;
}
int Partition(int* rank, PtrU U, int p, int r) {
	int x = U[rank[r]].total;
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (U[rank[j]].total > x) {
			i++;
			swap(rank, i, j);
		}
		else if (U[rank[j]].total == x) {
			if (U[rank[j]].full > U[rank[r]].full) {
				i++;
				swap(rank, i, j);
			}
			else if (U[rank[j]].full == U[rank[r]].full) {
				if (rank[j] < rank[r]) {
					i++;
					swap(rank, i, j);
				}
			}
		}
	}
	swap(rank, i + 1, r);
	return i + 1;
}
int Randomized_Partition(int* rank, PtrU U, int p, int r) {
	int i = rand() % (r - p + 1) + p;
	swap(rank, i, r);
	return Partition(rank, U, p, r);
}

void QuickSort(int* rank, PtrU U, int p, int r) {
	if (p < r) {
		int q = Randomized_Partition(rank, U, p, r);
		QuickSort(rank, U, p, q - 1);
		QuickSort(rank, U, q + 1, r);
	}
}
int main() {
	freopen("Text.txt", "r", stdin);
	int N, K, M, i, j;
	scanf("%d %d %d", &N, &K, &M);
	getchar();
	PtrU U = (PtrU)malloc(sizeof(struct user) * (N + 1));
	int* fullscore = (int*)malloc(sizeof(int) * (K + 1));
	int* rank = (int*)malloc(sizeof(int) * (N + 1));
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= K; j++) {
			U[i].score[j] = -2;
		}
		U[i].total = -1;
		U[i].full = 0;
		rank[i] = i;
	}
	for (i = 1; i <= K; i++) {
		scanf("%d", &fullscore[i]);
	}
	for (i = 0; i < M; i++) {
		char user_id[6];
		int problem_id;
		int score;
		scanf("%s %d %d\n", user_id, &problem_id, &score);
		if (U[atoi(user_id)].score[problem_id] < score) {
			U[atoi(user_id)].score[problem_id] = score;
		}
	}
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= K; j++) {
			if (U[i].score[j] == fullscore[j]) {
				U[i].full++;
			}
			if (U[i].score[j] > -1) {
				if (U[i].total < 0) {
					U[i].total++;
				}
				U[i].total += U[i].score[j];
			}
		}

	}
	QuickSort(rank, U, 1, N);
	int c1 = 0;
	int c2 = 0;
	for (i = 1; i <= N; i++) {
		if (U[rank[i]].total > -1) {
			if (i > 1 && U[rank[i]].total == U[rank[i - 1]].total) {
				printf("%d ", c1);
				c2++;
			}
			else {
				c1 = c2++;
				printf("%d ", ++c1);
			}
			
			printf("%05d %d ", rank[i], U[rank[i]].total);
			for (j = 1; j <= K; j++) {
				if (j == K) {
					if (U[rank[i]].score[j] == -2) {
						printf("-\n");
					}
					else if (U[rank[i]].score[j] == -1) {
						printf("0\n");
					}
					else {
						printf("%d\n", U[rank[i]].score[j]);
					}
				}
				else {
					if (U[rank[i]].score[j] == -2) {
						printf("- ");
					}
					else if (U[rank[i]].score[j] == -1) {
						printf("0 ");
					}
					else {
						printf("%d ", U[rank[i]].score[j]);
					}
				}
			}
		}
	}
	return 0;
}