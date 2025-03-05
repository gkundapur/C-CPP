#include <stdio.h>

void
swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void
minHeapify(int a[], int n, int i)
{
	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && a[l] < a[smallest])
		smallest = l;
	if (r < n && a[r] < a[smallest])
		smallest = r;

	if (smallest != i) {
		swap(&a[i], &a[smallest]);
		minHeapify(a, n, smallest);
	}
}

void
buildMinHeap(int a[], int n)
{
	for (int i = n/2; i >= 0; i--)
		minHeapify(a, n, i);
}

void
printarray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int
kthlargest_minheap(int a[], int n, int k)
{
	int minHeap[k];
	int i;

	for (i = 0; i < k; i++)
		minHeap[i] = a[i];

	printf("minHeap: ");
	printarray(minHeap, k);

	buildMinHeap(minHeap, k);

	for (i = k; i < n; i++) {
		if (a[i] > minHeap[0]) {
			minHeap[0] = a[i];
			minHeapify(minHeap, k, 0);
		}
	}

	return minHeap[0];
}

int partition(int a[], int low, int high)
{
	int pivot = a[low];
	int i = low;
	int j = high;

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

int kthlargest_quickselect(int a[], int low, int high, int k)
{
	int pivot_idx = partition(a, low, high);
	if (pivot_idx == k - 1) 
		return a[pivot_idx];
	else if (pivot_idx > k - 1) 
		return kthlargest_quickselect(a, low, pivot_idx-1, k);
	else
		return kthlargest_quickselect(a, pivot_idx+1, high, k);
}

int
main(void) 
{
	//int a[] = {20, 8, 22, 4, 12, 10, 14};
	int k, n;
	int a[] = {3, 2, 1, 5, 6, 4};
	n = sizeof(a)/sizeof(a[0]);
	k = 2;

	printarray(a, n);
	printf("%dth largest(minheap) = %d\n", k, kthlargest_minheap(a, n, k));
	printf("%dth largest(quickselect) = %d\n", k, kthlargest_quickselect(a, 0, n, k));

	printf("\n----------------------------\n");
	int b[] = {3,2,3,1,2,4,5,5,6};
	n = sizeof(b)/sizeof(b[0]);
	k = 4;
	printarray(b, n);
	printf("%dth largest(minheap) = %d\n", k, kthlargest_minheap(a, n, k));
	printf("%dth largest(quickselect) = %d\n", k, kthlargest_quickselect(a, 0, n, k));

	return 0;
}
