#include <stdio.h>

int
main(void)
{
	//int arr[] = {44, 75, 23, 43, 55, 12, 64, 77, 33};
	//int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 8};
	int arr[] = {6, 2, 3, 4, 5, 1, 7, 8, 8};
	int n = sizeof(arr)/sizeof(arr[0]);

	int low = 1;
	int high = n;
	int mid = low + (high-low)/2;
	printf("high = %d, mid = %d\n", high, mid);

	int median = (low+high+mid) - low - high;
	printf("median = %d, a[%d] = %d\n", median, median, arr[median]);

	return 0;
}
