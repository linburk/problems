#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sieve_T {
	int n;
	char *s;
};

int fill_sieve(struct sieve_T *sv)
{
	sv->s = calloc(sv->n, sizeof(char));
	if (sv->s == NULL)
		return -1;
	memset(sv->s, 0x01, sv->n * sizeof(char));
	sv->s[0] = sv->s[1] = 0;
	for (int i = 2; i < sv->n; ++i) {
		if (!sv->s[i])
			continue;
		for (int j = i + i; j < sv->n; j += i)
			sv->s[j] = 0;
	}
	return 0;
};

void free_sieve(struct sieve_T *sv)
{
	free(sv->s);
	sv->s = NULL;
	sv->n = 0;
}

int count_primes(int n, struct sieve_T *sv)
{
	if (sv->n <= n)
		return -1;
	int res = 0;
	for (int i = 0; i <= n; ++i) {
		res += sv->s[i];
	}
	return res;
}

int main()
{
	struct sieve_T sv;
	int n, res;
	int tmp = scanf("%d", &n);
	if (tmp != 1)
		abort();
	sv.n = n + 1;
	tmp = fill_sieve(&sv);
	if (tmp == -1)
		abort();
	res = count_primes(n, &sv);
	printf("%d", res);
	free_sieve(&sv);
	assert(sv.s == NULL);
	return 0;
}
