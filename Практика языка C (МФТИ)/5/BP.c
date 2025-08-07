#include <stdio.h>
#include <stdlib.h>

int calculate(int, int *, int, int *err);

int main()
{
	int err;
	int capacity;
	int *weight;
	int i, n, res;
	err = scanf("%d%d", &capacity, &n);
	if (err != 2 || n < 0 || capacity < 0)
		abort();
	weight = malloc(sizeof(int) * n);
	if (weight == NULL)
		abort();
	for (i = 0; i < n; ++i) {
		err = scanf("%d", weight + i);
		if (err != 1) {
			free(weight);
			abort();
		}
	}
	res = calculate(capacity, weight, n, &err);
	if (err == -1) {
		free(weight);
		abort();
	}
	printf("%d\n", res);
	free(weight);
	return 0;
}

static inline int max(int a, int b)
{
	return a < b ? b : a;
}

int calculate(int capacity, int *weight, int n, int *err)
{
	int ret, i, j;
	int *dp;
	*err = 0;
	dp = malloc(sizeof(int) * (capacity + 1));
	if (dp == NULL) {
		*err = -1;
		return 0;
	}
	dp[0] = 0;
	for (i = 0; i < n; ++i) {
		dp[i] = 0;
		for (j = capacity; j > 0; --j) {
			if (j >= weight[i])
				dp[j] = max(dp[j], dp[j - weight[i]] + 1);
		}
	}
	ret = dp[capacity];
	free(dp);
	return ret;
}
