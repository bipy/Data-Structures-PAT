#include<stdio.h>
#include<stdlib.h>
int Find(int* Set, int c) {
	while (Set[c] >= 0) {
		c = Set[c];
	}
	return c;
}
//路径压缩：
//int Find(int* S,int X){
//	if (S[X] < 0) /* 找到集合的根*/
//		return X;
//	else
//		return S[X] = Find(S, S[X]);
//}
void Input(int* Set,int c1,int c2) {
	c1 = Find(Set, c1);
	c2 = Find(Set, c2);
	if (Set[c1] < Set[c2]) {
		Set[c2] = c1;
		Set[c1]--;
	}
	else {
		Set[c1] = c2;
		Set[c2]--;
	}	
}
void Check(int* Set,int c1,int c2) {
	c1 = Find(Set, c1);
	c2 = Find(Set, c2);
	if (c1 != c2) {
		printf("no\n");
	}
	else {
		printf("yes\n");
	}
}
int main() {
	int N, i, c1, c2, flag = 0, count = 0;
	char sign;
	scanf("%d", &N);
	getchar();
	int* Set = (int*)malloc(sizeof(int) * N);
	for (i = 0; i < N; i++) {
		Set[i] = -1;
	}
	while (flag != 1) {
		scanf("%c", &sign);
		switch (sign)
		{
		case 'S':
			flag = 1;
			break;
		case 'I':
			scanf("%d %d", &c1, &c2);
			Input(Set, c1 - 1, c2 - 1);
			break;
		case 'C':
			scanf("%d %d", &c1, &c2);
			Check(Set, c1 - 1, c2 - 1);
			break;

		}
	}
	for (i = 0; i < N; i++) {
		if (Set[i] < 0) {
			count++;
		}
	}
	if (count == 1){
		printf("The network is connected.\n");
	}
	else {
		printf("There are %d components.", count);
	}
}