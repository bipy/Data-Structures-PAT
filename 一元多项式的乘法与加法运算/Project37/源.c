#include<stdio.h>
#include<stdlib.h>
typedef struct polyNode* poly;
struct polyNode {
	int e;
	int c;
	poly link;
};
void Attach(int c, int e, poly* Rear) {								
	poly P = (poly)malloc(sizeof(struct polyNode));
	P->c = c;
	P->e = e;
	P->link = NULL;
	(*Rear)->link = P;
	*Rear = P;
}
poly polyRead() {
	poly P, Rear, t;
	int c, e, k;
	P = (poly)malloc(sizeof(struct polyNode));
	P->link = NULL;
	Rear = P;
	scanf("%d", &k);
	while (k--) {
		scanf("%d %d", &c, &e);
		Attach(c, e, &Rear);
	}
	t = P;											
	P = P->link;
	free(t);
	return P;
}
poly add(poly p1, poly p2) {
	poly p = (poly)malloc(sizeof(struct polyNode));
	poly Rear = p;
	poly t1 = p1;
	poly t2 = p2;
	p->link = NULL;
	while (t1 && t2) {
		if (t1->e < t2->e) {
			Attach(t2->c, t2->e, &Rear);	
			t2 = t2->link;
		}
		else if (t1->e > t2->e) {
			Attach(t1->c, t1->e, &Rear);
			t1 = t1->link;
		}
		else if (t1->e == t2->e) {
			if(t2->c + t1->c!=0)
				Attach(t2->c+t1->c, t1->e, &Rear);
			t1 = t1->link;
			t2 = t2->link;
		}
	}
	while (t1) {
		Attach(t1->c, t1->e, &Rear);
		t1 = t1->link;
	}
	while (t2) {
		Attach(t2->c, t2->e, &Rear);
		t2 = t2->link;
	}
	p = p->link;
	return p;
}
poly mult(poly p1, poly p2) {
	if (!p1 || !p2) {
		return NULL;
	}
	poly p = (poly)malloc(sizeof(struct polyNode));
	poly Rear = p;
	poly t1 = p1;
	poly t2 = p2;
	p->link = NULL;
	
	while (t2) {
		Attach(t1->c * t2->c, t1->e + t2->e, &Rear);
		t2 = t2->link;
	}
	p = p->link;
	t1 = t1->link;
	while (t1) {
		poly t = (poly)malloc(sizeof(struct polyNode));
		poly r = t;
		t->link = NULL;
		
		t2 = p2;
		while (t2) {
			Attach(t1->c * t2->c, t1->e + t2->e, &r);
			t2 = t2->link;
		}
		t = t->link;
		p = add(p, t);
		t1 = t1->link;		
	}
	return p;

}
void show(poly p) {
	int Tag = 0;
	if (!p) {
		printf("0 0");
	}
	while (p) {
		if (Tag == 0) {
			Tag = 1;
		}
		else {
			printf(" ");
		}
		printf("%d %d", p->c,p->e);
		p = p->link;
	}
	printf("\n");
}
int main() {
	poly p1, p2, pp, ps;
	p1 = polyRead();
	p2 = polyRead();
	pp = mult(p1, p2);
	show(pp);
	ps = add(p1, p2);
	show(ps);
	return 0;
}