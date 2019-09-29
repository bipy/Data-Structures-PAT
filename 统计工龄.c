#include<stdio.h>
#include<stdlib.h>
#define maxAge 51
int main() {
	int N, i;
	int Year[maxAge];
	for (i = 0; i < maxAge; i++) {
		Year[i] = 0;
	}
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		int t;
		scanf("%d", &t);
		Year[t]++;
	}
	for (i = 0; i < maxAge; i++) {
		if (Year[i] != 0) {
			printf("%d:%d\n", i, Year[i]);
		}
	}
	
	return 0;
}
