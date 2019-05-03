#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode* List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main()
{
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	scanf("%d", &X);
	P = BinarySearch(L, X);
	printf("%d\n", P);

	return 0;
}
Position BinarySearch(List L, ElementType X) {
	int i,j=0;

	i = L->Last / 2;

	while (i > 0&&j!=i) {
		
		if (X == L->Data[i]) {
			return i;
		}
		else if (X > L->Data[i]) {
			j = i;
			if (i == L->Last - 1) 
				i++;
			
			i = (L->Last - i) / 2 + i;
		}
		else if (X < L->Data[i]) {
			i = (i-j) / 2;
		}
	}
	return NotFound;
}