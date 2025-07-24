#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#if 1
struct sieve_t {
	int n;
	unsigned char *mod1;
	unsigned char *mod5;
};
#else
#include "u_template.h"
#endif

int is_prime(struct sieve_t *sv, unsigned n)
{
	unsigned k, mod, i, j;
	if (n == 2 || n == 3)
		return 1;
	k = n / 6;
	mod = n % 6;
	i = k / CHAR_BIT;
	j = k % CHAR_BIT;
	assert(i < sv->n);
	switch (mod) {
	case 1:
		return (~sv->mod1[i] >> j) & 1;
	case 5:
		return (~sv->mod5[i] >> j) & 1;
	default:
		return 0;
	}
}

void set1(struct sieve_t *sv, unsigned n)
{
	unsigned k, mod, i, j;
	k = n / 6;
	mod = n % 6;
	i = k / CHAR_BIT;
	j = k % CHAR_BIT;
	assert(i < sv->n);
	if (mod != 1 && mod != 5)
		return;
	switch (mod) {
	case 1:
		sv->mod1[i] |= 1 << j;
		break;
	case 5:
		sv->mod5[i] |= 1 << j;
		break;
	default:
		break;
	}
};

void fill_sieve(struct sieve_t *sv)
{
	int max_k, cap;
	if (sv->n == 0)
		return;
	max_k = CHAR_BIT * sv->n;
	cap = max_k * 6;
	set1(sv, 1);
	for (int i = 0; i < max_k; ++i) {
		int p1, p2;
		p1 = i * 6 + 1;
		p2 = i * 6 + 5;
		if (1LL * p1 * p1 >= cap)
			break;
		if (is_prime(sv, p1)) {
			for (int j = p1 * p1; j < cap; j += 2 * p1)
				set1(sv, j);
		}
		if (is_prime(sv, p2)) {
			for (int j = p2 * p2; j < cap; j += 2 * p2)
				set1(sv, j);
		}
	}
}
