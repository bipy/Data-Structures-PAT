#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT) {
	if (BT) {
		printf("%d ", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}/* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT) {
	if (BT) {		
		InorderTraversal(BT->Left);
		printf("%d ", BT->Data);
		InorderTraversal(BT->Right);
	}

}/* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}
/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X) {
	if (!BST) {
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else {
		if (X > BST->Data) {
			BST->Right = Insert(BST->Right, X);
		}
		else if (X < BST->Data) {
			BST->Left = Insert(BST->Left, X);
		}
	}
	return BST;
}
BinTree Delete(BinTree BST, ElementType X) {
	BinTree T1, T2, T, P, P1;
	int flag = 0;
	P1 = P = BST;
	T = T1 = T2 = Find(BST, X);
	if (!T) {
		printf("Not Found\n");
	}
	else {
		if (T1->Right == NULL && T1->Left == NULL) {
			while (flag==0) {
				flag = 0;
				if (P->Data == X) {
					if (P1->Data == X) {
						return NULL;
					}
					else if (P1->Data > X) {
						P1->Left = NULL;
						flag = 1;
					}
					else if (P1->Data < X) {
						P1->Right = NULL;
						flag = 1;
					}					
				}
				else if (P->Data > X) {
					P1 = P;
					P = P->Left;
				}
				else if (P->Data < X) {
					P1 = P;
					P = P->Right;
				}
			}
			
		}
		else if (T1->Right && T1->Left == NULL) {
			T2 = T2->Right;
			T1->Data = T2->Data;
			T1->Left = T2->Left;
			T1->Right = T2->Right;
			free(T2);
		}
		else if (T1->Left && T1->Right == NULL) {
			T2 = T2->Left;
			T1->Data = T2->Data;
			T1->Left = T2->Left;
			T1->Right = T2->Right;
			free(T2);
		}
		else if (T1->Left && T1->Right) {
			T2 = T2->Left;
			while (T2->Right) {
				T1 = T2;
				T2 = T2->Right;
			}
			if (T1 == T) {
				T1->Data = T2->Data;
				T1->Left = T2->Left;
				free(T2);
			}
			else {
				T->Data = T2->Data;
				T1->Right = T2->Left;		//将找到的节点的左子树接到父亲的右边
				free(T2);
			}
		}		
	}

	return BST;
	
}
Position Find(BinTree BST, ElementType X) {
	if (!BST) {
		return NULL;
	}
	if (BST&&BST->Data == X) {
		return BST;
	}
	else if (BST->Data > X) {
		return Find(BST->Left, X);
	}
	else if (BST->Data < X) {
		return Find(BST->Right, X);
	}
}
Position FindMin(BinTree BST) {
	if (!BST) {
		return NULL;
	}
	while (BST->Left) {
		BST = BST->Left;
	}
	return BST;
}
Position FindMax(BinTree BST) {
	if (!BST) {
		return NULL;
	}
	while (BST->Right) {
		BST = BST->Right;
	}
	return BST;
}