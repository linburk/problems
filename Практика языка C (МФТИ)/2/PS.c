#if 1
struct sieve_t {
	int n;
	char *s;
};
#else
#include "u_template.h"
#endif

#include <assert.h>

void fill_sieve(struct sieve_t *sv)
{
	sv->s[0] = sv->s[1] = 1;
	for (int i = 2; i < sv->n; ++i) {
		if (sv->s[i])
			continue;
		for (long long j = 1LL * i * i; j < sv->n; j += i)
			sv->s[j] = 1;
	}
};

int nth_prime(struct sieve_t *sv, int n)
{
	int res = 1, cnt = 0;
	do {
		++res;
		assert(res < sv->n);
		cnt += !sv->s[res];
	} while (cnt < n);
	return res;
}
