#include <stdio.h>
#include <stdlib.h>

int
sum(int n)
{
    if (n == 0)
        return 0;

    if (n <= 1)
        return 1;

    return n + sum(n-1);
    // return (n == 0) ? 0 : ((n == 1) ? 1 : (n + sum(n-1)));
}

int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]);

    printf("sum of first (%d-1) numbers = %d\n", n, sum(n));

    return 0;
}
