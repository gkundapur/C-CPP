#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int i = low + 1;
    int j = high;
    int pivot = a[low];

    while (i <= j) {
        while (a[i] < pivot)
            i++;

        while (a[j]  > pivot)
            j--;

        if (i <= j)
            swap(&a[i], &a[j]);

    }
    swap(&a[low], &a[j]);
	return j;
}

int
partition_r(int a[], int low, int high)
{
    int random;

    srand(time(0));
    random = low + rand() % (high-low);
	printf("random index = %d\n", random);

	// exchange a[random] with a[low]
    int temp = a[random];
    a[random] = a[low];
    a[low] =  temp;
	printf("array after swapinng %d <-> %d : ", a[random], a[low]);
	print_array(a, high);
	return partition(a, low, high);
}


void
quicksort(int a[], int low, int high)
{
    if (low < high) {
        int pivot = partition_r(a, low, high);

        printf("pivot= %d is at = %d\n\n", a[pivot], pivot);

        quicksort(a, low, pivot);

        quicksort(a, pivot + 1, high);
    }
}

void
print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int
main(void)
{
    int arr[] = {44, 75, 23, 43, 55, 12, 64, 77, 33};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Array before sorting: ");
    print_array(arr, n);

    quicksort(arr, 0, n-1);

    printf("Array after sorting: ");
    print_array(arr, n);

    return 0;
}
