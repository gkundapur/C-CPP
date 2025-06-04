#include <stdio.h>
#include <math.h>

int isPrime(int n)
{
        if (n <= 1)
                return 0; // 0 = false, 1 = true
        if (n == 2)
                return 1;
        if (n % 2 == 0)
                return 0;

        for (int i = 3; i < sqrt(n); i += 2)
                if (n % i == 0)
                        return 0;
        return 1;
}

int
nearest_prime(int n)
{
        if (isPrime(n))
                return n;

        int lower = n - 1;
        int upper = n + 1;

        while (1) {
                if (lower >= 2 && isPrime(lower))
                        return lower;
                if (isPrime(upper))
                        return upper;

                lower--;
                upper++;
        }
}


int
main(void)
{
        int n;
        printf("Enter any number:\n");
        scanf("%d", &n);

        printf ("Nearest prime to %d = %d\n", n, nearest_prime(n));

        return 0;
}
