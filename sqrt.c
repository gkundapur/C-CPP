#include <stdio.h>
#include <stdlib.h>

double
Abs(double a, double b)
{
	return (a > b) ? a - b : b - a;
}

double
sq_rt(int n)
{
	double a, o, e = 0.000001;

	for (o = n, a = 1; Abs(o, a) > e; o = n/a, a = (o+a)/2)
		;

	return a;
}

int
mysqrt(int n)
{
	if (n == 0)
		return n;

	int left = 1;
	int right = n;
	while (left <= right) {
		int mid = left + (right-left)/2;
		if (mid == n/mid)
			return mid;
		else if (mid < (1.0 * n)/mid)
			left = mid+1;
		else
			right = mid-1;
	}
	return right;
}

int
main(int argc, char *argv[])
{
	int n = atoi(argv[1]);

	//printf("sqrt(%d) = %lf\n", n, sq_rt(n));
	printf("mysqrt(%d) = %d\n", n, mysqrt(n));

	return 0;
}
