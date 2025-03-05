
#include <stdio.h>

void print_array(int a[], int n);

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int
partition(int a[], int low, int high)
{
    int i = low+1;
    int j = high;
    int pivot = a[low];

	while (i <= j) {
		if (a[i] < pivot && a[j] > pivot) {
			swap(&a[i], &a[j]);
			i++;
			j--;
		}

		if (a[i] >= pivot)
			i++;
		if (a[j] <= pivot)
			j--;

	}
	swap(&a[low], &a[j]);
	return j;
}

void
printarray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n\n");
}

int
quickselect(int a[], int low, int high, int k)
{
#if 0
	// if k is smaller than number of element in array
    //if (k > 0 && k <= high - low + 1) {
	while (1) {
        int pivot = partition(a, low, high);

		printf("array after partition: ");
		printarray(a, high+1);
		printf("pivot index = %d\n", pivot);

		if (pivot == k-1)
			return a[pivot];
		else if (pivot > k-1) { // if k is smaller, recurse on left subarray 
			//return quickselect(a, low, pivot-1, k);
			high = pivot - 1;
		} else {
        	//return quickselect(a, pivot + 1, high, k); 
			low = pivot+1;
		}
    }
	return -1;
#endif 
	//if (low == high)
	//	return a[low];

	int pivot = partition(a, low, high);
	int i = pivot - low + 1;

	if (pivot == k-1)
		return a[pivot];
	else if (pivot > k-1)
		return quickselect(a, low, pivot - 1, k);
	else
		return quickselect(a, pivot+1, high, k);
}

int 
kthlargest(int a[], int n, int k)
{
	return quickselect(a, 0, n-1, k);
}

int
main(void)
{
    //int arr[] = {44, 75, 23, 43, 55, 12, 64, 77, 33};
    int arr[] = {10, 4, 5, 8, 6, 11, 26};
    int n = sizeof(arr)/sizeof(arr[0]);
	int k = 2;

	
	printf("array: ");
	printarray(arr, n);
    int result = kthlargest(arr, n, k);
	printf("%d-th largest element is %d\n", k, result);

    return 0;
}
