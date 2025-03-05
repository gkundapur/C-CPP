#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int
partition(int A[], int start, int end)
{
	int pivot = A[end];
	int pIndex = start;
	
	for (int i = start; i < end; i++) {
		if (A[i] <= pivot) {
			swap(&A[i], &A[pIndex]);
			pIndex++;
		}
	}
	swap(&A[pIndex], &A[end]);
	return pIndex;	
}

int
randomizedPartition(int A[], int start, int end)
{
	int pIndex = rand() % (end - start + 1) + start;

	printf("random index between (%d %d) is %d\n", start, end, pIndex);
	swap(&A[pIndex], &A[end]);
	return partition(A, start, end);
}

void quicksort(int A[], int i, int j)
{
	if (i < j) {
		//int pIndex = partition(A, i, j);
		int pIndex = randomizedPartition(A, i, j);
		quicksort(A, i, pIndex - 1);
		quicksort(A, pIndex + 1, j);
	}
}

int
main(void)
{
	int A[] = {7, 2, 1, 6, 8, 5, 3, 4};
	int n = sizeof(A)/sizeof(A[0]);

	quicksort(A, 0, 7);

	printf("sorted array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
	
	printf("\n");
	return 0;
}
