#include <stdio.h>

void
shell_sort(int a[], int n)
{
	int i, j, gap, temp;

	for (gap = n/2; gap > 0; gap /= 2) 
		for (i = gap; i < n; i++) 
			//for (j = i - gap; i >= 0 && a[j] > a[j+gap]; j -= gap) {
			for (j = i - gap; j >= 0; j -= gap) {
				if (a[j] > a[j+gap]) {
					temp = a[j];
					a[j] = a[j+gap];
					a[j+gap] = temp;
				}
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

	shell_sort(arr, n);
	printf("Array after sorting: ");
	printarray(arr, n);

	return 0;
}

