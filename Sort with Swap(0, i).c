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
	for (i = 1; i < N; i++) {	//�˴�����ѭ���������棬����ʱ
		while (array[0] != 0) {		//��Ӧÿһ��loop����ɺ�array[0]==0;
			swap(array, 0, array[0]);
			count++;
		}
		if (i != array[i]) {		//ͨ����ѭ�����α�����û�źõ�������0������������һ��loop
			swap(array, 0, i);
			count++;
		}
	}

	printf("%d", count);
	return 0;
}