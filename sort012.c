#include <stdio.h>

void
swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void
sort012(int a[], int n)
{
	int low = 0;
	int mid = 0;
	int high = n - 1;

	while (mid <= high) {
		if (a[mid] == 0)
			swap(&a[low++], &a[mid++]);
		else if (a[mid] == 1)
			mid++;
		else
			swap(&a[mid], &a[high--]);
	}
}

void
printarray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int
main(void)
{
	int a[] = {0, 1, 2, 0, 1, 2};
	int n = sizeof(a)/sizeof(a[0]);

	sort012(a, n);

	printarray(a, n);

	return 0;
}
