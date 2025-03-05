#include <stdio.h>

void
bubble_sort(int a[], int n)
{
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1-i; j++) {
			if (a[j] > a[j+1]) {
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void
swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void
rec_bubble_sort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (a[i] > a[i+1])
			swap(&a[i], &a[i+1]);
	rec_bubble_sort(a, n - 1);
}

void
optimized_bublesort(int a[], int n)
{
	int swapped;

	for (int i = 0; i < n; i++) {
		swapped = 0; // false
		for (int j = 0; j < n-i-1; j++) {
			if (a[j] > a[j+1]) {
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swapped = 1; // true
			}
		}
		if (swapped == 0)
			break;
	}
}


void
insertion_sort(int a[], int n)
{
	int i, j;

	for (/*int*/ i = 1; i < n; i++) {
		int key = a[i];
#if 0
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
#endif
		for (/*int*/ j = i - 1; j >= 0 && a[j] > key; j--)
			a[j+1] = a[j];
		a[j+1] = key;
	}
}

void
selection_sort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (a[j] < a[min])
				min = j;
		}

		if (min != i) {
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
}

void 
shell_sort(int a[], int n)
{
	int i, j, gap, temp;

	for (gap = n/2; gap > 0; gap /= 2) 
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0; j -= gap) 
				if (a[j] > a[j+gap]) {
					temp = a[j];
					a[j] = a[j+gap];
					a[j+gap] = temp;
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
	int a[] = {15, 16, 6, 8, 5};
	int an = sizeof(a)/sizeof(a[0]);

	printf("array before sorting:");
	printarray(a, an);

	bubble_sort(a, an);

	printf("array after bubble sort:");
	printarray(a, an);

	int b[] = {15, 16, 6, 8, 5};
	int bn = sizeof(b)/sizeof(b[0]);

	insertion_sort(b, bn);
	printf("array after insertion sort:");
	printarray(b, bn);

	int c[] = {15, 16, 6, 8, 5};
	int cn = sizeof(c)/sizeof(c[0]);

	shell_sort(c, cn);
	printf("array after shell sort:");
	printarray(c, cn);

	int d[] = {15, 16, 6, 8, 5};
	int dn = sizeof(c)/sizeof(c[0]);

	selection_sort(d, dn);
	printf("array after selection sort:");
	printarray(d, dn);

	return 0;
}
