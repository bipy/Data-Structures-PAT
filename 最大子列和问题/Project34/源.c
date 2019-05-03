#include<stdio.h>

int main() {
	int j=0,K;
	while (j<1&& scanf("%d", &K)!=EOF) {
		int i = 0, max = 0, t = 0,m;
		
		j++;
		while (i < K&& scanf("%d", &m)!=EOF) {
			
			t += m;
			if (t >= max)
				max = t;
			else if (t < 0)
				t = 0;
			i++;
		}
		printf("%d", max);
	}
		return 0;
}