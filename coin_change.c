#include <stdio.h>
#include <string.h>
#include <limits.h>

int
count(int coins[], int n, int sum)
{
	if (sum == 0)
		return 1;

	if (sum < 0)
		return 0;

	if (n <= 0)
		return 0;

	return  count(coins, n - 1, sum) + count(coins, n, sum - coins[n - 1]);
}

int minCoin(int coins[], int n, int amount)
{
	if (amount == 0)
		return 0;

	int minCount = INT_MAX;

	for (int i = 0; i < n; i++) {
		if (coins[i] <= amount) {
			int curCount = minCoin(coins, n, amount - coins[i]);
			if (curCount != INT_MAX && curCount + 1 < minCount)
				minCount = curCount + 1;
		}
	}

	if (minCount == INT_MAX)
		return -1;
	else
		return minCount;
}

int minCoin1(int coins[], int n, int amount)
{
	if (amount == 0)
		return 1;

	int res = INT_MAX;
	for (int i = 0; i < n; i++) {
		// try every coin that has value < amount
		if (coins[i] <= amount) {
			int temp = minCoin1(coins, n, n-coins[i]);
			if (temp + 1 < res)
				res = temp + 1;
		}
	}
	return res;
}

int minCoins(int coins[], int n, int amount)
{
	int dp[amount + 1];

	// For amount = 0
	dp[0] = 1;

	// initialize all values to infinity
	for (int i = 1; i <= amount; i++)
		dp[i] = INT_MAX;

	for (int i = 1; i <= amount; i++) {
		for (int j = 0; j < n; j++) // go through all coins
			if (coins[j] <= i) {
				int temp = dp[i-coins[j]];
				if (temp != INT_MAX && temp + 1 < dp[i])
					dp[i] = temp + 1;
			}
	}
	return dp[amount];
}


int
dpminCoins(int coins[], int n, int amount)
{
	int dp[n][amount];

	for (int i = 0; i < n; i++)
		dp[i][0] = 1;

	//dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= amount; j++) {
			if (coins[i-1] > j)
				dp[i][j] = dp[i-1][j];
			else
				dp[i][j] = dp[i-1][j]+dp[i][j-coins[i-1]];

#if 0
			if (coins[i] > j)
				dp[i][j] = dp[i-1][j];
			else
				dp[i][j] = dp[i-1][j]+dp[i][j-coins[i-1]];
#endif
		}
	}

	printf("----------%d\n", dp[n-1][amount-1]);
	return dp[n][amount];
#if 0
	int dp[amount+1];

	dp[0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = coins[i]; j <= amount; j++)
			dp[j] += dp[j-coins[i]];

	return dp[amount];
#endif
}

int count1(int coins[], int n, int amount)
{
    int dp[amount + 1];

    memset(dp, 0, sizeof(dp));

    dp[0] = 1;

    for (int i = 0; i < n; i++)
        for (int j = coins[i]; j <= amount; j++)
            dp[j] += dp[j - coins[i]];
    return dp[amount];
}

int
minCoins_rec(int coins[], int n, int amount)
{
	if (amount == 0)
		return 1;

	if (amount < 0 || n == 0)
		return 0;

		return minCoins_rec(coins, n, amount - coins[n-1]) +
				minCoins_rec(coins, n - 1, amount);
}

int
main(void)
{
	int i, j;
	//int coins[] = {1, 2, 3};
	int coins[] = {25, 10, 5};
	int amount = 30;
	int n = sizeof(coins) / sizeof(coins[0]);
	printf("number of coins = %d for amount = %d\n", minCoin(coins, n, amount), amount);

	//int c[] = {1, 2, 3}; // o/p : 4
	//int k = 4;
	//int c[] = {2, 5, 3, 6}; // o/p: 5
	//int k = 10;
	int c[] = {1, 2, 3}; // o/p: 5
	int k = 5;
	int s = sizeof(coins) / sizeof(coins[0]);
	//printf("number of coins = %d for amount = %d\n", minCoin(c, s, k), k);
	printf("number of coins = %d for amount = %d\n", minCoins_rec(c, s, k), k);


	return 0;
}
