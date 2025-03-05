#include <stdio.h>
#include <stdlib.h>

struct Item {
	int profit;
	int weight;
};

int
compare(const void *a, const void *b)
{
	double r1 = (double)(((struct Item *)b)->profit) /
				(((struct Item *)b)->weight);
	double r2 = (double)(((struct Item *)a)->profit) / 
				(((struct Item *)a)->weight);

	return r1 > r2;
}

double
fractionalKnapsack(int M, struct Item arr[], int n)
{
	// sort on pi/wi
	qsort(arr, n, sizeof(arr[0]), compare);

	//int currentWeight = 0;
	double finalValue = 0.0;
	int rc = M; // remaining capacity

	for (int i = 0; i < n; i++) {
		if (arr[i].weight <= rc) {
			rc -= arr[i].weight;
			printf("Added object %d(%d, %d) completely, rc = %d\n",
				i, arr[i].profit, arr[i].weight, rc);
			finalValue += arr[i].profit;
		} else {
			double x = ((double) rc / (double) arr[i].weight);
			double profit = x * arr[i].profit;
			rc -= arr[i].weight * x;
			printf("Added %.2f (%d, %d) of object %d, rc = %d\n",
				x, arr[i].profit, arr[i].weight, i, rc);
			finalValue += x * arr[i].profit;
			break;
		}
			
#if 0
		if (currentWeight + arr[i].weight <= M) {
			currentWeight += arr[i].weight;
			finalValue += arr[i].profit;
		} else {
			int rc = M - currentWeight;
			finalValue += arr[i].profit * ((double) rc / arr[i].weight);
			break;
		}
#endif
	}

	return finalValue;
}

int
main(void)
{
	//struct Item arr[] = {{60, 10}, {100, 20}, {120, 30}};
	struct Item arr[] = {{30, 20}, {40, 25}, {35, 10}}; // {profit, weight}

	int n = sizeof(arr)/ sizeof(arr[0]);
	//int W = 50;
	int W = 40;

	printf("Items:\n");
	for (int i = 0; i < n; i++)
		printf("%d\t%d\n", arr[i].weight, arr[i].profit);
	printf("Capacity of knapsack(rc): %d\n\n", W);

	double profit = fractionalKnapsack(W, arr, n);
	printf("Max profit = %.2f\n", profit);

	return 0;
}

