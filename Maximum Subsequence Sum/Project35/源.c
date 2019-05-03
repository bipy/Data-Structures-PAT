#include<stdio.h>
#include<stdlib.h>
int main() {
	int K;
	scanf("%d", &K);
	int *seq =(int*)malloc(K*sizeof(int));
	for (int i = 0; i < K; i++)
		scanf("%d", &seq[i]);
	int ThatSum = 0, MaxSum = 0;
	int left = -1, right = -1;
	int temp = 0, j = 0;
	for (int i = 0; i < K; i++) {
		ThatSum += seq[i];
		if (ThatSum > MaxSum) {
			MaxSum = ThatSum;
			left = temp;
			right = i;
		}
		if (ThatSum < 0) {
			ThatSum = 0;
			temp = i + 1;
			j++;
		}
	}
	if (j == K) {
		left = 0, right = K - 1;
	}
	printf("%d %d %d", MaxSum, seq[left], seq[right]);
	return 0;
}