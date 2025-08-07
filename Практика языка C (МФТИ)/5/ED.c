#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int distance(char *, int, char *, int, int, int, int, int *err);

int main()
{
	int err;
	int add, del, repl;
	char *a, *b;
	int len_a, len_b;
	int res;
	err = scanf("%d%d%d", &add, &del, &repl);
	if (err != 3)
		abort();
	err = scanf("%d", &len_a);
	if (err != 1)
		abort();
	a = malloc(len_a + 1);
	if (a == NULL)
		abort();
	err = scanf("%s", a);
	if (err != 1) {
		free(a);
		abort();
	}
	err = scanf("%d", &len_b);
	if (err != 1) {
		free(a);
		abort();
	}
	b = malloc(len_b + 1);
	if (b == NULL) {
		free(a);
		abort();
	}
	err = scanf("%s", b);
	if (err != 1) {
		free(a);
		free(b);
		abort();
	}
	res = distance(a, len_a, b, len_b, add, del, repl, &err);
	if (err == -1) {
		free(a);
		free(b);
		abort();
	}
	printf("%d\n", res);
	free(a);
	free(b);
	return 0;
}

void free_2d(int **a, int n)
{
	int i;
	if (a == NULL)
		return;
	for (i = 0; i < n; ++i)
		free(a[i]);
	free(a);
}

int **alloc_2d(int n, int m)
{
	int i;
	int **ret;
	ret = calloc(n, sizeof(int *));
	if (ret == NULL)
		return NULL;
	for (i = 0; i < n; ++i) {
		ret[i] = calloc(m, sizeof(int));
		if (ret[i] == NULL) {
			free_2d(ret, n);
			return NULL;
		}
	}
	return ret;
}

static inline int min(int a, int b)
{
	return a < b ? a : b;
}

int distance(char *a, int len_a, char *b, int len_b, int add, int del, int repl,
			 int *err)
{
	int i, j;
	int **dp;
	int ret;
	*err = 0;
	dp = alloc_2d(len_a + 1, len_b + 1);
	if (dp == NULL) {
		*err = -1;
		return 0;
	}
	dp[0][0] = 0;
	for (i = 0; i <= len_a; ++i) {
		for (j = 0; j <= len_b; ++j) {
			if (i || j)
				dp[i][j] = INT_MAX;
			if (i > 0)
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + add);
			if (j > 0)
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + del);
			if (i > 0 && j > 0)
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] +
											 repl * (a[i - 1] != b[j - 1]));
		}
	}
	ret = dp[len_a][len_b];
	free_2d(dp, len_a + 1);
	return ret;
}
