#include <stdio.h>

int
max_profit(int a[], int n)
{
	int profit = 0;

	for (int i = 0; i < n-1; i++) {
		if (a[i] < a[i+1]) {
			profit += a[i+1] - a[i];
			printf ("profit = %d\n", profit);
		}
	}
	return profit;
}

int
main(void)
{
	int a[] = {1, 4, 5, 2, 6};
	int n = sizeof(a)/sizeof(a[0]);

	printf("max profit = %d\n", max_profit(a, n));

	return 0;
}
