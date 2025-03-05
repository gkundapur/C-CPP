#include <stdio.h>
#include <stdlib.h>

int **
allocatez(int n)
{
	int **v;
	int i, j;

	v = (int **)malloc(n * sizeof(int));
	for ( i = 0; i < n; i++)
		v[i] = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			v[i][j] = 0;

	return v;
}

void
GenerateMagicSquare1(int n)
{
	int i, j, newRow, newCol, key;
	int **v;

	v = allocatez(n);

	i = 0;
	j = n / 2;

	for ( key = 1; key <= n * n; key++) {
		v[i][j] = key;

		newRow = (i - 1) >= 0 ? i - 1 : n - 1;
		newCol = (j + 1) % n;

		if (v[newRow][newCol] != 0) 
			i = (i+1) % n;
		else {
			i = newRow;
			j = newCol;
		}
	}
	// display matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf ( "%4d", v[i][j]);
		printf("\n");
	}

	// deallocate array
	for (i = 0; i < n; i++)
		free(v[i]);
	free(v);
}


void
GenerateMagicSquare(int n)
{
	int i, j, k, l, key;
	int **v;

	v = allocatez(n);
	
	i = 0;
	j = (n - 1) / 2;
	v[i][j] = 1;

	for (key = 2; key <= n * n; key++) {
		if (i >= 1)
			k = i - 1;
		else
			k = n - 1;

		if ( j >= 1)
			l = j - 1;
		else
			l = n - 1;
		
		if (v[k][l] >= 1)
			i = (i + 1) % n;
		else {
			i = k;
			j = l;
		}
		v[i][j] = key;
	}

	// display matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf ( "%4d", v[i][j]);
		printf("\n");
	}

	// deallocate array
	for (i = 0; i < n; i++)
		free(v[i]);
	free(v);

}

int
main(void)
{
	int n;

	printf ("Enter the order of the matrix: ");
	if (scanf("%d", &n) != 1) {
		printf("Enter numbers only\n");
		exit(1);
	} else if (n % 2 == 0) {
		printf ("Enter odd number only\n");
		exit(2);
	}

	GenerateMagicSquare1(n);
	//GenerateMagicSquare1(n);
#if 0
	int **v;
	int i, j, k, l, key, n;

	printf ("Enter the order of the matrix: ");
	if (scanf("%d", &n) != 1) {
		printf("Enter numbers only\n");
		exit(1);
	} else if (n % 2 == 0) {
		printf ("Enter odd number only\n");
		exit(2);
	}

	// allocate n*n array
	v = (int **)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) 
		*(v + i) = (int *)malloc(n * sizeof(int));

	// initialize v[n][n]
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			v[i][j] = 0;

	i = 0;
	j = (n - 1)/2;
	v[i][j] = 1;

	for (key = 2; key <= n * n; key++) {
		if ( i >= 1) 
			k = i - 1;
		else
			k = n - 1;

		if (j >= 1) 
			l = j - 1;
		else
			l = n - 1;

		if (v[k][l] >= 1) 
			i = (i + 1) % n;
		else {
			i = k;
			j = l;
		}		
		v[i][j] = key;
	}

	// display matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf ( "%4d", v[i][j]);
		printf("\n");
	}

	// deallocate array
	for (i = 0; i < n; i++)
		free(v[i]);
	free(v);
#endif
	return 0;
}

	

