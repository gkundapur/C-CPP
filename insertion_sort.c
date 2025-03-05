#include <stdio.h>

void
insertion_sort(int a[], int n)
{
	int i, j, key;

	for (i = 1; i < n; i++) {
		key = a[i];
		for (j = i-1; a[j] > key; j--)
			a[j+1] = a[j];
		a[j+1] = key;
	}
}

void
printarray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n\n");
}

int
main(void)
{
	int arr[] = {12, 11, 13, 5, 6};
	int n = sizeof(arr)/sizeof(arr[0]);

	printf("Array before sorting: ");
	printarray(arr, n);

	insertion_sort(arr, n);
	printf("Array after sorting: ");
	printarray(arr, n);

	return 0;
}

