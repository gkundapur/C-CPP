#include <stdio.h>
#include <limits.h>


int max2(int a, int b)
{
        return (a > b) ? a : b;
}

int max3(int a, int b, int c)
{
    return max2(max2(a,b), c);
}

int max_cross_sum(int a[], int l, int m, int r)
{
    int sum = 0;
    int left_sum = INT_MIN;
    int i;
    
    // include left half
    for (i = m; i >= l; i--) {
        sum += a[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;

    for (i = m; i <= r; i++) {
        sum += a[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    return max3(left_sum + right_sum - a[m], left_sum, right_sum);
}

int
max_sub_arr_sum(int a[], int l, int r)
{
    if (l > r)
        return INT_MIN;

    // only one element
    if (l == r)
        return a[l];

    // Find middle
    int m = (l+r)/2;

    /*
    Return maximum of 3 cases
        a) max subarray sum in left half
        b) max subarray sum in right half
        c) max subarray sum such that subarray crosses midpoint
    */
    return max3(max_sub_arr_sum(a, l, m-1),
               max_sub_arr_sum(a, m+1, r),
               max_cross_sum(a, l, m, r));
}

int
main(void)
{
    int a[] = {2, 3, 4, 5, 7};
    int sz = sizeof(a)/sizeof(a[0]);

    int max_sum = max_sub_arr_sum(a, 0, sz - 1);
    printf("max contigous sum = %d\n", max_sum);

    return 0;
}
