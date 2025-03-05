#include <stdio.h>

#define MAX 500

int
multiply(int res[], int x, int res_size)
{
	int carry = 0;

	for (int i = 0; i < res_size; i++) {
		int prod = res[i] * x + carry;

		res[i] = prod % 10;
		carry = prod/10;
	}

	while (carry) {
		res[res_size] = carry % 10;
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}

void
factorial(int n)
{
	int res[MAX];

	res[0] = 1;
	int res_size = 1;

	for (int x = 2; x <= n; x++)
		res_size = multiply(res, x, res_size);

	printf("Fact(%d) = ", n);
	for (int i = res_size - 1; i >= 0; i--)
		printf("%d", res[i]);
	printf("\n");
}

int
main(void)
{
	//factorial(10);
	factorial(50);

	return 0;
}
