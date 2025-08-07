#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int calculate(int sum, int *coins, int count, int *err);

int main()
{
	int err;
	int i;
	int sum, count;
	int *coins;
	int res;
	err = scanf("%d%d", &sum, &count);
	if (err != 2 || sum < 0 || count <= 0)
		abort();
	coins = malloc(count * sizeof(int));
	if (coins == NULL)
		abort();
	for (i = 0; i < count; ++i) {
		err = scanf("%d", coins + i);
		if (err != 1) {
			free(coins);
			abort();
		}
	}
	res = calculate(sum, coins, count, &err);
	if (err == -1) {
		free(coins);
		abort();
	}
	printf("%d\n", res);
	free(coins);
	return 0;
}

static inline int min(int a, int b)
{
	return a < b ? a : b;
}

int calculate(int sum, int *coins, int count, int *err)
{
	int i, j;
	int *dp;
	int ret;
	*err = 0;
	dp = malloc(sizeof(int) * (sum + 1));
	if (dp == NULL) {
		*err = -1;
		return 0;
	}
	dp[0] = 0;
	for (i = 1; i <= sum; ++i) {
		dp[i] = INT_MAX;
		for (j = 0; j < count; ++j) {
			if (i >= coins[j] && dp[i - coins[j]] != INT_MAX)
				dp[i] = min(dp[i], dp[i - coins[j]] + 1);
		}
	}
	ret = dp[sum] == INT_MAX ? -1 : dp[sum];
	free(dp);
	return ret;
}
