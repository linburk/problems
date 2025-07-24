#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#if 1
struct sieve_t {
	int n;
	unsigned char *s;
};
#else
#include "u_template.h"
#endif

static inline void set1(struct sieve_t *sv, int n)
{
	assert(n < CHAR_BIT * sv->n);
	sv->s[n / CHAR_BIT] |= 1 << (n % CHAR_BIT);
}
static inline int get(struct sieve_t *sv, int n)
{
	assert(n < CHAR_BIT * sv->n);
	return (sv->s[n / CHAR_BIT] >> (n % CHAR_BIT)) & 1;
}
int is_prime(struct sieve_t *sv, unsigned n)
{
	return !get(sv, n);
}

void fill_sieve(struct sieve_t *sv)
{
	if (sv->n == 0)
		return;
	set1(sv, 0);
	set1(sv, 1);
	for (int i = 2; 1LL * i * i < CHAR_BIT * sv->n; ++i) {
		if (is_prime(sv, i)) {
			for (int j = i * i; j < CHAR_BIT * sv->n; j += i)
				set1(sv, j);
		}
	}
}
