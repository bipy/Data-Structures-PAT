#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
void percolateDown(int* heap, int parent) { //��λ��parent��Ԫ������ʹ�����������  
	int temp = heap[parent];
	int child = 2 * parent;
	if (child + 1 <= heap[0] && heap[child + 1] < heap[child])
		++child;
	while (child <= heap[0] && heap[child] < temp) {
		heap[parent] = heap[child];
		parent = child;
		child = 2 * parent;
		if (child + 1 <= heap[0] && heap[child + 1] < heap[child])
			++child;
	}
	heap[parent] = temp;
}
void buildMinHeap(int* heap) {          //������ṹ�ԣ�����Ԫ��λ��ʹ���������  
	for (int i = heap[0] / 2; i > 0; --i)    //���з�Ҷ�ڵ���ݶ���������  
		percolateDown(heap, i);
}
int deleteMin(int* heap) {              //ɾ�������ضѶ�Ԫ�أ�ͬʱ�����ṹά��������  
	int minElem = heap[1];
	heap[1] = heap[heap[0]--];          //�����һ��Ԫ���Ƶ��Ѷ�  
	percolateDown(heap, 1);             //Ψһ����������ԵĶѶ�Ԫ������  
	return minElem;
}
void insertMinHeap(int* heap, int weight) {         //���в���һ��Ԫ��  
	heap[++heap[0]] = weight;           //���뵽��ĩβ  
	//������ڵ�����Ƚڵ��б�����Ľڵ��������ˣ����̵ȼ������ˣ���΢��һ��Ŀ�����  
	for (int i = heap[0] / 2; i > 0 && heap[i] > weight; i /= 2)
		percolateDown(heap, i);
}
int calWPL(int* freq) {
	int heap[100] ;                 //huffman�����öѣ�0λ�ñ���Ԫ�ش�С��1λ�ÿ�ʼ����Ȩֵ  
	int size = 0;
	for (int i = 0; i < 256; ++i) {      //������Ȩֵ����ն��У��ȴ����ѣ�����ʹ�ж����ԣ�  
		if (freq[i]) {
			heap[++size] = freq[i];
		}
	}
	heap[0] = size;                     //0λ�ñ������Ԫ�ظ���  
	buildMinHeap(heap);                 //����  
	//ģ�⹹��huffman�����̣�ÿ�δӶ��е���Ȩֵ��С�������������кϲ����ϲ��������ȨΪ����Ȩ�ͣ�����ѣ�  
	//��wplֵ = ����������wplֵ��Ȩ���������ڵ�·���ͣ� + ����������Ȩ�غͣ�Ȩ�����ڸ��ӽڵ����1��·��������  
	//��˲���Ҫ����huffman����ֻ��Ҫ��������������ֵ������������Ȩ�غͱ����ڶ��У�wpl��������������wplֵ��ͬʱ�����ۼ�  
	int wpl = 0;
	for (int i = 1; i < size; ++i) {
		int weight1 = deleteMin(heap);
		int weight2 = deleteMin(heap);
		wpl += weight1 + weight2;
		insertMinHeap(heap, weight1 + weight2);
	}
	return wpl;
}
int isPrefix(char* s1, char* s2) {      //�ж������ַ����Ƿ�����ǰ׺���ϵ  
	while (s1 && s2 && *s1 == *s2)      //ѭ������һ������ͬ����ĸ�����λ��  
		++s1, ++s2;
	if (*s1 == '\0' || *s2 == '\0')     //�����ʱ��һ���������λ�ã�˵������ַ���һ������һ���ַ�����ǰ׺  
		return 1;
	else
		return 0;
}
int hasPrefixCode(char s[][200], int n) {//�ж�n���ַ����Ƿ���ǰ׺��  
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (isPrefix(s[i], s[j]))   //�������Ա�  
				return 1;
	return 0;
}
int main() {
	/*freopen("test.txt", "r", stdin);*/
	int n;
	scanf("%d", &n);
	int freq[256] ;
	for (int i = 0; i < n; ++i) {
		char ch;
		int num;
		getchar();
		scanf("%c%d", &ch, &num);
		freq[ch] = num;
	}
	int wpl = calWPL(freq);             //ģ�⹹��huffman�����̼���WPL����Ȩ·������  
	int k;      //k����������  
	scanf("%d", &k);
	while (k--) {
		char ch[256];
		char s[256][200];
		int thisWPL = 0;
		for (int i = 0; i < n; ++i) {
			scanf("\n%c %s", &ch[i], s[i]);
			thisWPL += freq[ch[i]] * strlen(s[i]);      //���ݱ����ۼӼ�Ȩ·����  
		}
		if (thisWPL == wpl && !hasPrefixCode(s, n))     //ͬʱ�����Ȩ·������̺Ͳ���ǰ׺�룬������huffman����  
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}