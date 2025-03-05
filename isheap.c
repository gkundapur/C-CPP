#include <stdio.h>

int
isheap(int a[], int i, int n)
{
	if (i >= (n-1)/2)
		return 1;

	if (a[i] >= a[2 * i + 1] &&
		a[i] >= a[2 * i + 2] &&
		isheap(a, 2 * i + 1, n) &&
		isheap(a, 2 * i + 2, n))
		return 1;
	return 0;
}

int
main(void)
{
	int a[] = {90, 15, 10, 7, 12, 2, 7, 3};
	int n = sizeof(a)/sizeof(a[0]);

	isheap(a, 0, n) ? printf("Yes\n") : printf("No\n");

	return 0;
}
