#include <stdio.h>

void
merge(int a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

	// create 2 temp arrays
    int L[n1], R[n2];

	// copy data from left to mid to L[]
    for(i = 0; i < n1; i++)
        L[i] = a[l + i];

	// copy data from mid to right to R[]
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

	// merge the temp arrays back into arr[l...r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    // copy remaining elements of L[]
    while (i < n1)
            a[k++] = L[i++];

    //copy remaining elements of R[]
    while (j < n2)
        a[k++] = R[j++];
}
void
merge_sort(int a[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l)/2;

        merge_sort(a, l, m);
        merge_sort(a, m+1, r);

        merge(a, l, m, r);
    }
}

void
print_array(int a[], int sz)
{
    int i;

    for (i = 0; i < sz; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int
main(void)
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 5};
    int sz = sizeof(arr) / sizeof(arr[0]);

    printf("Given array: ");
    print_array(arr, sz);

    merge_sort(arr, 0, sz-1);

    printf("Sorted array: ");
    print_array(arr, sz);

    return 0;
}
