#include <stdio.h>

int
power(int x, int n)
{
	if (n == 0) return 1; // x^0 = 1
	if (n == -1) return 1/x; // x^-1 = 1/x

	int temp = power(x, n/2);
	if (n % 2 == 0)     // 2^10 = 2^5 x 2^5
		return temp * temp;

	if (n > 0) 			// 2^11 = 2^5 x 2^5 * 2
		return temp * temp * x;

	return temp * temp * (1/x);  // exporent odd -ve 2^-3 = 
}

int
main(void)
{
	int x = 2;
	//int n = 10;
	//int n = 11;
	int n = -4;

	printf("pow(%d, %d) = %d\n", x, n, power(x, n));

	return 0;
}

