#include <stdio.h>
#include <stdlib.h>

/**
  Pascal triagnle is a triangular array of binomial coefficients in which 
  nth row contains binominal coefficient nC0, nC1

  C(n, r) = C(n, r-1) * (n, r+1) / r
  */
void
printPascal(int n)
{
	for (int line = 1; line <= n; line++) {
		for (int space = 1; space <= n - line; space++) 
			printf(" ");

		int coef = 1;
		for (int i = 1; i <= line; i++) {
			printf("%3d", coef);
			coef = coef * (line - i ) / i;
		}
		printf("\n");
	}
}

int
fact(int n)
{
	if (n == 0 || n == 1)
		return 1;

	return n * fact(n-1);
}

int
ncr(int n, int r)
{
	return fact(n) / (fact(n-r) * fact(r));
}

/******************
ncr = 1 for r = 0
      1 for n = r
	  ncr(n-1, r-1) + ncr(n-1, r), otherwise
*/
int ncr1(int n, int r)
{
	if (n == r || r == 0)
		return 1;

	return ncr1(n-1, r - 1) + ncr1(n-1, r);
}

int
printPascal1(int rows)
{
	for (int n = 0; n <= rows; n++) {
		for (int space = 0; space <= rows - n; space++)
			printf(" ");

		for (int r = 0; r <= n; r++)
			printf("%3d", ncr1(n, r));

		printf("\n");
	}

	return 0;
}

void
printPascal2(int rows)
{
	for (int n = 0; n < rows; n++) {
		int num = 1;
		for (int space = 0; space < rows-n; space++) 
			printf(" ");
		for (int r = 0; r <= n; r++) {
			printf("%d ", num);
			num = num * (n - r)/(r+1);
		}
		printf("\n");
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <number of rows>\n", *argv);
		return 1;
	}

	int n = atoi(argv[1]);

	printf("printPasca1------------\n");
	printPascal(n);
	printf("\nprintPascal1-----------\n");
	printPascal1(n);
	printf("\nprintPascal2-----------\n");
	printPascal2(n);
	return 0;
}



