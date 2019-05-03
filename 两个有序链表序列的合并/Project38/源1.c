#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	Print(L1);
	Print(L2);
	return 0;
}
List Merge(List L1, List L2) {	
	List P1, P2, L, Head;
	L = (List)malloc(sizeof(struct Node));
	Head = L;
	P1 = L1->Next;
	P2 = L2->Next;
	while (P1!=NULL && P2!=NULL) {
		if (P1->Data < P2->Data) {
			L->Next = P1;
			P1 = P1->Next;
		}
		else{
			L -> Next = P2;
			P2 = P2->Next;
		}
		L = L->Next;
	}
	if (P1 != NULL) {
		L->Next = P1;
	}
	if (P2 != NULL) {
		L->Next = P2;
	}
	L1 ->Next= NULL;
	L2 ->Next= NULL;
	return Head;
}