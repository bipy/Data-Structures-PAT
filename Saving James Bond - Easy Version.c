#include<stdio.h>
#include<stdlib.h>
#define Border 50
#define MaxN 100
#define R 7.5
typedef struct crocodile* PtrC;
struct crocodile {
	int x;
	int y;
	int visited;
	int safe;
};
void location(PtrC Set,int N, int D) {
	int i, x0, y0;
	Set->safe = 0;
	Set->visited = 0;
	Set->x = Set->y = 0;
	for (i = 1; i <= N; i++) {
		scanf("%d %d", &x0, &y0);
		(Set + i)->x = x0; 
		(Set + i)->y = y0;
		(Set + i)->visited = 0;
		if ((Set + i)->x >= (Border - D) || (Set + i)->x <= (D - Border) || (Set + i)->y >= (Border - D) || (Set + i)->y <= (D - Border)) {
			(Set + i)->safe = 1;
		}
		else {
			(Set + i)->safe = 0;
		}
	}
}
int distance(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int Check(PtrC Set, int N, int D) {
	if (D >= Border-R) {
		return 1;
	}
	int i = 0, front, rear, x, y, B;
	int queue[MaxN];
	x = y = 0;
	front = rear = -1;
	Set->visited = 1;
	queue[++rear] = i;
	while (front < rear) {
		int V = queue[++front];
		x = ((Set + V)->x);
		y = ((Set + V)->y);
		if (x == 0 && y == 0) {
			B = (D + R) * (D + R);
		}
		else {
			B = D * D;
		}
		for (i = 0; i <= N; i++) {
			if ((Set + i)->visited == 0 && B >= distance((Set + i)->x, (Set + i)->y, x, y)) {
				if ((Set + i)->safe == 1) {
					return 1;
				}
				(Set + i)->visited = 1;
				queue[++rear] = i;
			}
		}
	}
	return 0;
}
int main() {
	int N, D;
	scanf("%d %d", &N, &D);
	PtrC Set = (PtrC)malloc(sizeof(struct crocodile) * (N+1));
	location(Set, N, D);
	Check(Set, N, D) ? printf("Yes\n") : printf("No\n");
	//此处出现了“.exe出现了一个断点”无法调试
	//解决办法为将第69行(PtrC)malloc(sizeof(struct crocodile) * (N))的N改为N+1
	//推测为内存管理的问题
	return 0;
}