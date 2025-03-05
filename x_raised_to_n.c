#include <stdio.h>

int
power(int x, int n)
{
	if (n == 0)
		return 1;
	else if (x == 1)
		return x;
	else
		return x * power(x, n-1);
}

int
main(void)
{
	int x, n;

	x = 3;
	n = 4;
	printf("power(%d, %d) = %d\n", x, n, power(x, n));

	return 0;
}

