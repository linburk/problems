#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define CC_GENERATE_MAX 1E6
#define CC_MAX_SIZE 100

#define iabs(x) ((x) < 0 ? -(x) : (x))

struct sieve_T {
	char *data;
	int size;
};

int fill_sieve(struct sieve_T *, int n);
void free_sieve(struct sieve_T *);

int is_prime(struct sieve_T *, int);
int is_circular(struct sieve_T *, int);
int next_circular(int *, int, int);
int fill_circular(struct sieve_T *, int, int, int *);

int main()
{
	int cc[CC_MAX_SIZE];
	struct sieve_T sv;
	int n, res, len;
	int tmp = scanf("%d", &n);
	if (tmp != 1 || n < 0)
		abort();
	tmp = fill_sieve(&sv, CC_GENERATE_MAX);
	if (tmp == -1)
		abort();
	len = fill_circular(&sv, CC_MAX_SIZE, CC_GENERATE_MAX, cc);
	res = next_circular(cc, len, n);
	printf("%d\n", res);
	free_sieve(&sv);
	return 0;
}

int fill_circular(struct sieve_T *sv, int cap, int n, int *cc)
{
	int i = 0;
	for (int j = 0; j < n; ++j) {
		if (is_circular(sv, j)) {
			if (i >= cap)
				return -1;
			cc[i++] = j;
		}
	}
	return i;
}

int next_circular(int *cc, int len, int n)
{
	int res = -1;
	for (int i = 0; i < len; ++i) {
		if (iabs(cc[i] - n) < iabs(res - n))
			res = cc[i];
	}
	return res;
}

int is_circular(struct sieve_T *sv, int n)
{
	if (n <= 0)
		return 0;
	int tmp, hi = 1, len = 0, res = 1;
	tmp = n;
	while (tmp) {
		++len;
		tmp /= 10;
	}
	for (int i = 1; i < len; ++i)
		hi *= 10;
	tmp = n;
	for (int i = 0; res && i < len; ++i) {
		res &= is_prime(sv, tmp);
		tmp = hi * (tmp % 10) + tmp / 10; // shift
	}
	return res;
}

int is_prime(struct sieve_T *sv, int n)
{
	if (n < 0 || n >= sv->size)
		return -1;
	return !sv->data[n];
}


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
