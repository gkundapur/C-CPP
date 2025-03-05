#include <stdio.h>

double
sq(int n, int prec)
{
	if (n == 0)
		return 0;

	int low = 1;
	int high = n / 2;
	int mid;
	double ans;

	while (low <= high) {
		mid = low+(high - low)/2;

		if (mid * mid == n)
			return mid;
		if (mid * mid < n) {
			low = mid + 1;
			ans = mid;
		} else
			high = mid - 1;

	}

	//return ans;
	// for precision
	double increment = 0.1;
	for (int i = 0; i < prec; i++) {
		while (ans * ans <= n)
			ans += increment;
		ans = ans - increment;
		increment = increment/10;
	}
	return ans;
}

int
main(void)
{
	int n = 9;
	int prec = 2;
	printf("sqrt(%d) = %lf\n", n, sq(n, prec));

	int p = 18;
	printf("sqrt(%d) = %lf\n", p, sq(p, prec));

	return 0;
}
