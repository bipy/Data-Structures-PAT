#include<stdio.h>
#include<stdlib.h>
int count = 0;
void swap(int* array, int a, int b) {
	int t = array[a];
	array[a] = array[b];
	array[b] = t;
}
int main() {
	/*freopen("Text.txt", "r", stdin);*/
	int N, i;
	scanf("%d", &N);
	int* array = (int*)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++) {
		scanf("%d", &array[i]);
	}
	for (i = 1; i < N; i++) {	//此处将大循环套在外面，否则超时
		while (array[0] != 0) {		//对应每一个loop，完成后array[0]==0;
			swap(array, 0, array[0]);
			count++;
		}
		if (i != array[i]) {		//通过大循环依次遍历找没排好的数，与0交换，进行下一个loop
			swap(array, 0, i);
			count++;
		}
	}

	printf("%d", count);
	return 0;
}