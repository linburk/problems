#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct sieve_T {
	char *data;
	int size;
};

int fill_sieve(struct sieve_T *sv, int n)
{
	sv->size = n;
	sv->data = calloc(sv->size, sizeof(char));
	if (sv->data == NULL)
		return -1;
	sv->data[0] = sv->data[1] = 1;
	for (int i = 2; 1LL * i * i < sv->size; ++i) {
		if (sv->data[i])
			continue;
		for (int j = i * i; j < sv->size; j += i)
			sv->data[j] = 1;
	}
	return n;
}

void free_sieve(struct sieve_T *sv)
{
	free(sv->data);
	sv->data = NULL;
	sv->size = 0;
}

int formula(struct sieve_T *sv, int n, int *a, int *b)
{
	int res = 0;
	for (int i = 2; i < n; ++i) {
		if (sv->data[i])
			continue;
		for (int j = 1; j < n; ++j) {
			for (int k1 = -1; k1 <= 1; k1 += 2) {
				for (int k2 = -1; k2 <= 1; k2 += 2) {
					int f, cnt = 0;
					for (;;) {
						f = cnt * cnt + j * k1 * cnt
						    + i * k2;
						f = f < 0 ? -f : f;
						assert(f < sv->size);
						if (sv->data[f])
							break;
						++cnt;
					}
					if (cnt > res) {
						res = cnt;
						*a = k1 * j;
						*b = k2 * i;
					}
				}
			}
		}
	}
	return res;
}

int main()
{
	struct sieve_T sv;
	int n, res, a = 0, b = 0, tmp;
	tmp = scanf("%d", &n);
	if (tmp != 1)
		abort();
	tmp = fill_sieve(&sv, 2 * (n * n + n));
	if (tmp == -1)
		abort();
	res = formula(&sv, n, &a, &b);
	printf("%d %d %d\n", a, b, res);
	return 0;
}
