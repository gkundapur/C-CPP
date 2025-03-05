#include <stdio.h>

int
iterative_binsearch(int a[], int n, int key)
{
	int l = 0;
	int r = n-1;
	int mid;

	while (l <= r) {
		mid = l + (r-1)/2;

		if (a[mid] == key)
			return mid;
		else if (key > a[mid])
			l = mid + 1;
		else
			r = mid - 1;
	}
	return -1;
}

int
recursive_binsearch(int a[], int l, int r, int key)
{
	if (l > r)
		return -1;

	int mid = l + (r-l)/2;

	if (a[mid] == key)
		return mid;
	else if (key > a[mid])
		return recursive_binsearch(a, mid+1, r, key);
	else
		return recursive_binsearch(a, l, mid-1, key);
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
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int n = sizeof(a)/sizeof(a[0]);
	int key = 2;
	int result;

	printf("array: ");
	printarray(a, n);
	result = iterative_binsearch(a, n, key);
	if (result >= 0)
		printf("Iterative search: %d found at %d\n", key, iterative_binsearch(a, n, key));
	else
		printf("%d not found in array\n", key);

	key = 8;
	result = recursive_binsearch(a, 0, n, key);
	if (result >= 0)
		printf("Recursive search: %d found at %d\n", key, recursive_binsearch(a, 0, n, key));
	else
		printf("%d not found in array\n", key);

	return 0;
}
