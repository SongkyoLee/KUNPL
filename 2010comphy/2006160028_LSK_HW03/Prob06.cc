#include <stdio.h>

int main(void)
{
	int N, n;
	double Combination = 1;
	printf("Input N : ");
	scanf("%d", &N);
	printf("Input n : ");
	scanf("%d", &n);
	int i = N, j = n, k = N-n;
	if(N<n) { printf("GG\n"); return 1; }
	while(i > 0 || j > 0 || k > 0)
	{
		if(i > 0) { Combination = Combination*i; i--; }
		if(j > 0) { Combination = Combination/j; j--; }
		if(k > 0) { Combination = Combination/k; k--; }
	}
	printf("N Combination n : %e\n", Combination);
	return 0;
}
